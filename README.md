# servo_robot_board_interface

## Overview

ROS2 interface definition package, used for communication between the host computer and `ServoRobotBoard`. Include:
- **Messages (msg)**: Uplink data (STM32 → PC)
- **Services (srv)**: Downlink operations (PC → STM32)

> Protocol definition: [servo-robot-protocol](https://github.com/greenhand520/servo_robot_board_tools/tree/dev/crates/servo-robot-protocol)

## Message Types (Uplink Data)

| Message | Description | Update Rate |
|---------|-------------|-------------|
| `BoardPower` | Power data (servo/battery voltage, current in mV/mA) | 20Hz |
| `BoardSystem` | System info (device ID, uptime, CPU, memory, firmware version, thermal) | 1Hz |
| `BoardEvent` | Event notifications (state change, protection flags, error flags) | Triggered |
| `BoardConfig` | Configuration snapshot with switch states | Event triggered |
| `ServoTarget` | Raw servo command bytes to forward to servo bus | On demand |

## Service Types (Downlink Operations)

| Service | Description |
|---------|-------------|
| `BoardQueryConfig` | Query single configuration parameter |
| `BoardQueryAllConfig` | Query all configuration parameters |
| `BoardWriteConfig` | Write configuration parameter |
| `BoardSwitch` | Switch operations (servo power, 5V, charge, battery extra output) |
| `BoardCommand` | One-shot board commands (Reset, Shutdown, OTA) |
| `BoardFirmwareUpdate` | Send firmware update data chunks for OTA |
| `ServoForward` | Forward raw servo command and wait for response |

## Topic and Service Names

### Topics
```
/robot/board/power          # Power data (mV/mA)
/robot/board/system         # System info + thermal data
/robot/board/event          # Event notifications
/robot/board/config         # Configuration snapshot
/robot/board/log            # Board log (rcl_interfaces/Log)
/robot/board/imu            # IMU (sensor_msgs/Imu)
/robot/board/battery        # Battery state (sensor_msgs/BatteryState)
/robot/board/servo/target   # Servo raw command (ServoTarget)
```

### Services
```
/robot/board/query_config       # Query single config
/robot/board/query_all_config   # Query all configs
/robot/board/write_config       # Write config
/robot/board/switch             # Switch operations
/robot/board/command            # One-shot commands (Reset/Shutdown/OTA)
/robot/board/firmware_update    # Firmware OTA data upload
/robot/board/servo/forward      # Forward servo command and get response
```

## C++ Usage Example

```cpp
#include "servo_robot_board_interface/ros_msg.hpp"

using namespace servo_robot_board_interface;

// Subscribe to power data
auto sub = node->create_subscription<PowerMsg>(
    TOPIC_BOARD_POWER, 10,
    [](const PowerMsg::SharedPtr msg) {
        RCLCPP_INFO(node->get_logger(), "Voltage: %u mV", msg->servo_voltage_mv);
    });

// Query config
auto client = node->create_client<QueryConfigSrv>(SERVICE_QUERY_CONFIG);
auto request = std::make_shared<QueryConfigSrv::Request>();
request->config_type = static_cast<uint8_t>(ConfigType::POWER_SERVO_CURRENT_LIMIT_MA);
auto result = client->async_send_request(request);
```

## Python Usage Example

```python
from servo_robot_board_interface_msg.ros_msg import *

# Subscribe to power data
sub = node.create_subscription(
    BoardPower,
    TOPIC_BOARD_POWER,
    lambda msg: print(f"Voltage: {msg.servo_voltage_mv} mV"),
    10
)

# Query config
client = node.create_client(BoardQueryConfig, SERVICE_QUERY_CONFIG)
request = BoardQueryConfig.Request()
request.config_type = ConfigType.POWER_SERVO_CURRENT_LIMIT_MA
future = client.call_async(request)
```

## Enum Types

### ChargePhase
| Value | Name | Description |
|-------|------|-------------|
| 0     | NotCharging        | Not charging        |
| 1     | PreCharge          | Pre-charge          |
| 2     | Cc                 | Constant Current    |
| 3     | Cv                 | Constant Voltage    |
| 4     | Full               | Full                |
| 5     | PdSinkFault        | pd sink chip fault  |
| 6     | UnsupportedCharger | Unsupported charger |

### StateChangeFlag
| Bit | Name | Description |
|-----|------|-------------|
| 0 | CHARGER_CONNECT | Charger connected/disconnected |
| 1 | FAN | Fan on/off |
| 2 | POWER_SERVO | Servo power on/off |
| 3 | POWER_5V | 5V output power on/off         |
| 4 | BAT_EXT_OUT | Battery extra output on/off |

### ProtectionFlag
| Bit | Name | Description |
|-----|------|-------------|
| 0 | SERVO_OVERCURRENT | Servo overcurrent |
| 1 | SERVO_THERMAL | Servo thermal |
| 2 | DCDC_5V_THERMAL | 5V thermal |
| 3 | CHARGE_DERATING | Charge derating |
| 4 | CHARGE_THERMAL | Charge thermal |
| 5 | BATTERY_LOW | Battery low |

### ConfigType
| Value | Name | Unit |
|-------|------|------|
| 0x01 | Reset | - |
| 0x02 | Shutdown | - |
| 0x10 | SwitchServoPower | bool |
| 0x11 | Switch5VPower | bool |
| 0x12 | SwitchCharge | bool |
| 0x13 | SwitchBatExtOut | bool |
| 0x20 | ChargeStopSOC | % |
| 0x21 | TxLogLevel | - |
| 0x30 | PowerServoCurrentLimitMa | mA |
| 0x31 | PowerServoTempLimit | °C |
| 0x32 | Power5vTempLimit | °C |
| 0x33 | ChargeMaxCurrentMa | mA |
| 0x34 | ChargeTempDerating | °C |
| 0x35 | ChargeTempLimit | °C |
| 0x36 | ChargeStopVoltageMv | mV |
| 0x37 | SetServoBaudRate | - |
| 0x37 | SetServoBaudRate | - |

### SwitchType
| Value | Name | Description |
|-------|------|-------------|
| 0x10 | ServoPower | Servo power |
| 0x11 | 5VPower | 5V power |
| 0x12 | Charge | Charge |
| 0x13 | BatExtOut | Battery extra output |

### BoardPower Fields
| Field | Type | Unit | Description |
|-------|------|------|-------------|
| servo_voltage_mv | uint16 | mV | Servo rail voltage |
| servo_current_ma | uint16 | mA | Servo rail current |
| charge_in_voltage_mv | uint16 | mV | USB-PD input voltage |
| charge_in_current_ma | uint16 | mA | USB-PD input current |
| bat_voltage_mv | uint16 | mV | Battery voltage |
| bat_current_ma | int16 | mA | Battery current (negative=discharging) |

### BoardSystem Fields (Thermal)
| Field | Type | Unit | Description |
|-------|------|------|-------------|
| temp_servo_power | float32 | °C | Servo power MOSFET temperature |
| temp_5v_power | float32 | °C | 5V regulator temperature |
| temp_mcu | float32 | °C | MCU die temperature |
| temp_charge | float32 | °C | Charge circuit temperature |
| temp_battery | float32 | °C | Battery NTC temperature |

## Build

```bash
cd your_ros_ws
colcon build --packages-select servo_robot_board_interface 
# or colcon build --packages-select servo_robot_board_interface --cmake-args -Wno-dev
source install/setup.bash
```

## Dependencies

- `std_msgs`
- `rosidl_default_generators`
- `rosidl_default_runtime`

## License

GPL-3.0
