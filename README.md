# servo_robot_board_interface

[English](README_en.md) | 简体中文

ROS2 接口定义包，用于上位机与 `ServoRobotBoard` 之间的通信。

> 协议定义及枚举常量详见：[servo-robot-protocol](https://github.com/servo-robot-520/servo_robot_board_driver/tree/main/crates/servo-robot-protocol)

## 消息（上行：STM32 → PC）

| 消息 | 说明 | 更新频率 |
|------|------|----------|
| `DeviceInfo` | 设备标识与内存布局（静态） | 查询时   |
| `Diagnostic` | 运行时诊断（CPU、堆、温度、错误计数） | 1Hz      |
| `Power` | 电源数据（舵机/电池电压、电流） | 20Hz     |
| `Event` | 事件通知（充电阶段、状态变化、保护、错误） | 触发式   |
| `Config` | 配置快照 | 事件触发 |
| `Response` | 统一应答帧 | 每次请求 |
| `Log` | 板端日志（级别、文件、函数、消息） | 触发式   |
| `ServoTarget` | 舵机原始指令字节 | 按需     |
| `sensor_msgs/Imu` | IMU 数据 | 100Hz    |
| `sensor_msgs/BatteryState` | 电池状态 | 10Hz     |

## 服务与动作（下行：PC → STM32）

| 类型 | 名称 | 说明 |
|------|------|------|
| Service | `QueryDeviceInfo` | 查询设备标识与内存布局 |
| Service | `QueryConfig` | 查询单个配置参数 |
| Service | `QueryAllConfig` | 查询所有配置参数 |
| Service | `WriteConfig` | 写入配置参数 |
| Service | `WriteConfigSwitch` | 开关操作（舵机电源、5V、充电、电池扩展输出） |
| Service | `SendCommand` | 一次性命令（重启、关机、OTA） |
| Service | `ServoForward` | 转发舵机原始指令并等待响应 |
| Service | `SendRequest` | 通用请求（任意 RequestType + 原始载荷） |
| Action | `FirmwareUpdate` | 固件 OTA 上传（带进度反馈） |

## 话题（Topics）

```
~/robot/board/power           # 电源数据（Power，20Hz）
~/robot/board/diagnostic      # 运行时诊断（Diagnostic，1Hz）
~/robot/board/event           # 事件通知（Event）
~/robot/board/config          # 配置快照（Config）
~/robot/board/log             # 板端日志（Log）
~/robot/board/imu             # IMU（sensor_msgs/Imu）
~/robot/board/battery_state   # 电池状态（sensor_msgs/BatteryState）
~/robot/board/servo/target    # 舵机原始指令（ServoTarget）
```

## 服务（Services）

```
~/robot/board/device_info         # 查询设备信息（QueryDeviceInfo）
~/robot/board/query/config        # 查询单个配置（QueryConfig）
~/robot/board/query/all_config    # 查询所有配置（QueryAllConfig）
~/robot/board/write/config        # 写入配置（WriteConfig）
~/robot/board/write/config_switch # 开关操作（WriteConfigSwitch）
~/robot/board/command             # 一次性命令（SendCommand: 重启/关机/OTA）
~/robot/board/servo/forward       # 转发舵机指令（ServoForward）
~/robot/board/request             # 通用请求（SendRequest）
~/robot/board/firmware_update     # 固件 OTA（FirmwareUpdate Action）
```

## C++ 使用示例

```cpp
#include "servo_robot_board_interface/ros_msg.hpp"

using namespace servo_robot_board_interface;

// 订阅诊断数据
auto sub = node->create_subscription<msg::Diagnostic>(
    topic_board_diagnostic(), 10,
    [](const msg::Diagnostic::SharedPtr msg) {
        RCLCPP_INFO(node->get_logger(), "CPU: %u%%  MCU: %.1f°C",
                    msg->cpu_usage_percent, msg->temp_mcu);
    });

// 订阅电源数据
auto power_sub = node->create_subscription<msg::Power>(
    topic_board_power(), 10,
    [](const msg::Power::SharedPtr msg) {
        RCLCPP_INFO(node->get_logger(), "舵机电压: %umV  电流: %umA",
                    msg->servo_voltage_mv, msg->servo_current_ma);
    });

// 查询设备信息
auto dev_client = node->create_client<srv::QueryDeviceInfo>(srv_query_device_info());
auto dev_req = std::make_shared<srv::QueryDeviceInfo::Request>();
dev_client->async_send_request(dev_req);

// 查询配置
auto client = node->create_client<srv::QueryConfig>(srv_query_config());
auto request = std::make_shared<srv::QueryConfig::Request>();
request->config_type = static_cast<uint8_t>(ConfigType::POWER_SERVO_CURRENT_LIMIT_MA);
auto result = client->async_send_request(request);
```

## Python 使用示例

```python
from servo_robot_board_interface_msg.ros_msg import *

# 订阅诊断数据
sub = node.create_subscription(
    Diagnostic,
    topic_board_diagnostic(),
    lambda msg: print(f"CPU: {msg.cpu_usage_percent}%  MCU: {msg.temp_mcu}°C"),
    10
)

# 查询配置
client = node.create_client(QueryConfig, srv_query_config())
request = QueryConfig.Request()
request.config_type = ConfigType.POWER_SERVO_CURRENT_LIMIT_MA
future = client.call_async(request)
```

## 枚举

所有枚举常量（RequestType、ConfigType、ChargePhase、StateChangeFlag、ProtectionFlag、ErrorFlag 等）均在协议中定义: [servo-robot-protocol](https://github.com/servo-robot-520/servo_robot_board_driver/tree/main/crates/servo-robot-protocol)

## 构建

```bash
cd your_ros_ws
colcon build --packages-select servo_robot_board_interface
source install/setup.bash
```

## 许可证

[GPL-3.0](LICENSE)
