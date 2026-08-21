# servo_robot_board_interface

[中文](./README.md)

ROS2 interface definition package for communication between host PC and `ServoRobotBoard`.

> Protocol definition & enum constants: [servo-robot-protocol](https://github.com/servo-robot-520/servo_robot_board_driver/tree/main/crates/servo-robot-protocol)

## Messages (Uplink: STM32 → PC)

| Message | Description | Update Rate |
|---------|-------------|-------------|
| `DeviceInfo` | Device identity & memory layout (static) | On query |
| `Diagnostic` | Runtime diagnostics (CPU, heap, temps, error counts) | 1Hz |
| `Power` | Power data (servo/battery voltage, current) | 20Hz |
| `Event` | Event notifications (charge phase, state change, protection, errors) | Triggered |
| `Config` | Configuration snapshot | Event triggered |
| `Response` | Unified response frame (replaces old ACK types) | Per request |
| `Log` | Board log (level, file, function, message) | Triggered |
| `ServoTarget` | Raw servo command bytes | On demand |
| `sensor_msgs/Imu` | IMU data | — |
| `sensor_msgs/BatteryState` | Battery state | — |

## Services & Actions (Downlink: PC → STM32)

| Type | Name | Description |
|------|------|-------------|
| Service | `QueryDeviceInfo` | Query device identity & memory layout |
| Service | `QueryConfig` | Query single config parameter |
| Service | `QueryAllConfig` | Query all config parameters |
| Service | `WriteConfig` | Write config parameter |
| Service | `WriteConfigSwitch` | Switch operations (servo power, 5V, charge, bat ext out) |
| Service | `SendCommand` | One-shot commands (Reset, Shutdown, OTA) |
| Service | `ServoForward` | Forward raw servo command and wait for response |
| Service | `SendRequest` | Generic request (any RequestType with raw payload) |
| Action | `FirmwareUpdate` | Firmware OTA upload with progress feedback |

## Topics

```
~/robot/board/power           # Power data (Power, 20Hz)
~/robot/board/diagnostic      # Runtime diagnostics (Diagnostic, 1Hz)
~/robot/board/event           # Event notifications (Event)
~/robot/board/config          # Config snapshot (Config)
~/robot/board/log             # Board log (Log)
~/robot/board/imu             # IMU (sensor_msgs/Imu)
~/robot/board/battery_state   # Battery state (sensor_msgs/BatteryState)
~/robot/board/servo/target    # Servo raw command (ServoTarget)
```

## Services

```
~/robot/board/device_info         # Query device info (QueryDeviceInfo)
~/robot/board/query/config        # Query single config (QueryConfig)
~/robot/board/query/all_config    # Query all configs (QueryAllConfig)
~/robot/board/write/config        # Write config (WriteConfig)
~/robot/board/write/config_switch # Switch operations (WriteConfigSwitch)
~/robot/board/command             # One-shot commands (SendCommand: Reset/Shutdown/OTA)
~/robot/board/servo/forward       # Forward servo command (ServoForward)
~/robot/board/request             # Generic request (SendRequest)
~/robot/board/firmware_update     # Firmware OTA (FirmwareUpdate Action)
```

## C++ Usage

```cpp
#include "servo_robot_board_interface/ros_msg.hpp"

using namespace servo_robot_board_interface;

// Subscribe to diagnostic data
auto sub = node->create_subscription<msg::Diagnostic>(
    topic_board_diagnostic(), 10,
    [](const msg::Diagnostic::SharedPtr msg) {
        RCLCPP_INFO(node->get_logger(), "CPU: %u%%  MCU: %.1f°C",
                    msg->cpu_usage_percent, msg->temp_mcu);
    });

// Subscribe to power data
auto power_sub = node->create_subscription<msg::Power>(
    topic_board_power(), 10,
    [](const msg::Power::SharedPtr msg) {
        RCLCPP_INFO(node->get_logger(), "Servo V: %umV  I: %umA",
                    msg->servo_voltage_mv, msg->servo_current_ma);
    });

// Query device info
auto dev_client = node->create_client<srv::QueryDeviceInfo>(srv_query_device_info());
auto dev_req = std::make_shared<srv::QueryDeviceInfo::Request>();
dev_client->async_send_request(dev_req);

// Query config
auto client = node->create_client<srv::QueryConfig>(srv_query_config());
auto request = std::make_shared<srv::QueryConfig::Request>();
request->config_type = static_cast<uint8_t>(ConfigType::POWER_SERVO_CURRENT_LIMIT_MA);
auto result = client->async_send_request(request);
```

## Python Usage

```python
from servo_robot_board_interface_msg.ros_msg import *

# Subscribe to diagnostic data
sub = node.create_subscription(
    Diagnostic,
    topic_board_diagnostic(),
    lambda msg: print(f"CPU: {msg.cpu_usage_percent}%  MCU: {msg.temp_mcu}°C"),
    10
)

# Query config
client = node.create_client(QueryConfig, srv_query_config())
request = QueryConfig.Request()
request.config_type = ConfigType.POWER_SERVO_CURRENT_LIMIT_MA
future = client.call_async(request)
```

## Enums

All enum constants (RequestType, ConfigType, ChargePhase, StateChangeFlag, ProtectionFlag, ErrorFlag, etc.) are defined in the protocol crate: [servo-robot-protocol](https://github.com/servo-robot-520/servo_robot_board_driver/tree/main/crates/servo-robot-protocol)

## Build

```bash
cd your_ros_ws
colcon build --packages-select servo_robot_board_interface
source install/setup.bash
```

## Dependencies

- `std_msgs`
- `builtin_interfaces`
- `rosidl_default_generators`
- `rosidl_default_runtime`

## License

GPL-3.0
