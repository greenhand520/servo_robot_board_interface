# quadhex_robot_board_interface

A ROS 2 interface package for communication with the STM32 main control board of the QuadHex robot.

## Overview

This package defines the message and service interfaces used to communicate with the robot's main control board. It provides real-time monitoring of board state, charging status, and configuration management.

## Messages

### ChargerState.msg

Status information from the BQ24725 charger IC.

| Field | Type | Description |
|-------|------|-------------|
| `header` | `std_msgs/Header` | Standard message header |
| `ac_present` | `bool` | Whether the AC adapter is connected |
| `charging` | `bool` | Whether it is currently charging |
| `charge_current_a` | `float32` | Charging current setpoint (A) |
| `charge_voltage_v` | `float32` | Charging voltage setpoint (V) |
| `input_current_a` | `float32` | AC adapter input current limit (A) |
| `realtime_current_a` | `float32` | Real-time charging current on battery side (A) |
| `realtime_input_voltage_v` | `float32` | Real-time AC adapter input voltage (V) |
| `charge_status` | `uint8` | Charging phase (see ChargeStatus enum) |
| `temp` | `float32` | DC-DC temperature (°C) |

**Charge Status Values:**

| Value | Status |
|-------|--------|
| 0 | Unknown |
| 1 | Not Charged |
| 2 | Pre-Charge |
| 3 | CC (Constant Current) |
| 4 | CV (Constant Voltage) |
| 5 | Full |
| 6 | HUSB238A Fault |
| 7 | Charger Unsupported |

### State.msg

STM32 board information and state.

| Field | Type | Description |
|-------|------|-------------|
| `header` | `std_msgs/Header` | Standard message header |
| `servo_power_temp` | `float32` | Servo DC-DC temperature (°C) |
| `mcu_temp` | `float32` | STM32 MCU temperature (°C) |
| `power_5v_temp` | `float32` | 5V output DC-DC temperature (°C) |
| `servo_power_voltage_v` | `float32` | Servo DC-DC output voltage (V) |
| `servo_power_current_a` | `float32` | Servo DC-DC output current (A) |
| `charger_state` | `ChargerState` | Charger state information |

### Config.msg

Configuration parameters for the board.

| Field | Type | Description |
|-------|------|-------------|
| `charge_current_limit_a` | `float32` | Battery charging current limit (A) |
| `charge_voltage_limit_v` | `float32` | Battery charging voltage limit (V) |
| `charge_protection_temp` | `float32` | Charging protection temperature (°C) |
| `charge_protection_temp_limit` | `float32` | Charging temperature limit (°C) |
| `servo_power_temp_limit` | `float32` | Servo power supply temperature limit (°C) |
| `servo_power_current_limit` | `float32` | Servo power supply current limit (A) |
| `power_5v_temp_limit` | `float32` | 5V power supply temperature limit (°C) |

## Services

### ModifyConfig.srv

Modify the board configuration.

**Request:**
- `new_config` (Config): New configuration to apply

**Response:**
- `success` (bool): Whether the configuration was successfully modified

## Topics

| Topic | Type | Description |
|-------|------|-------------|
| `/robot/board/state` | `State` | Board state information |
| `/robot/board/config` | `Config` | Board configuration |

## Services

| Service | Type | Description |
|---------|------|-------------|
| `/robot/board/modify_config` | `ModifyConfig` | Modify board configuration |

## Helper Utilities

### C++ (Header-only)

```cpp
#include "quadhex_robot_board_interface/ros_msg.hpp"

using namespace quadhex_robot_board_interface;

// Type aliases
Config config_msg;
State state_msg;
ChargeState charge_msg;

// Charge status conversion
ChargeStatus status = ChargeStatus::CC;
const char* status_str = charge_status_to_str(status);  // "CC"

ChargeStatus parsed = str_to_charge_status("FULL");  // ChargeStatus::FULL
```

### Python

```python
from quadhex_robot_board_interface_msg.ros_msg import ChargeStatus

# Enum usage
status = ChargeStatus.CC
print(status)  # "CC"

# Parse from string
parsed = ChargeStatus.from_str("full")  # ChargeStatus.FULL
```

## Dependencies

- ROS 2 (Humble or later)
- `std_msgs`
- `sensor_msgs`
- `builtin_interfaces`
- `rosidl_default_generators`

## Building

```bash
cd ~/quadhex_robot_board_ws
colcon build --packages-select quadhex_robot_board_interface --cmake-args -Wno-dev 
source install/setup.bash
```

## License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE](LICENSE) file for details.
