# servo_robot_board_interface

[English](README_en.md) | 简体中文

## 概述

ROS2 接口定义包，用于上位机与`ServoRobotBoard`通信，包括：
- **消息（msg）**：上行数据（STM32 → PC）
- **服务（srv）**：下行操作（PC → STM32）

> 协议定义详见：[servo-robot-protocol](https://github.com/greenhand520/servo_robot_board_tools/tree/dev/crates/servo-robot-protocol)

## 消息类型（上行数据）

| 消息 | 说明 | 更新频率 |
|------|------|----------|
| `BoardPower` | 电源数据（舵机/电池电压电流） | 20Hz |
| `BoardThermal` | 温度数据（舵机/5V/MCU/充电/电池） | 5Hz |
| `BoardSystem` | 系统信息（设备ID/运行时间/CPU/内存/固件版本） | 1Hz |
| `BoardEvent` | 事件通知（状态变更/保护标志/错误标志） | 触发式 |
| `BoardConfig` | 配置快照（所有配置参数+开关状态） | 事件触发 |

## 服务类型（下行操作）

| 服务 | 说明 |
|------|------|
| `BoardQueryConfig` | 查询单个配置参数 |
| `BoardQueryAllConfig` | 查询所有配置参数 |
| `BoardWriteConfig` | 写入配置参数 |
| `BoardSwitch` | 开关操作（舵机电源/5V/充电/电池额外输出） |

## 话题和服务名称

### 话题
```
/robot/board/power      # 电源数据
/robot/board/thermal    # 温度数据
/robot/board/system     # 系统信息
/robot/board/event      # 事件通知
/robot/board/config     # 配置快照
/robot/board/log        # 板级日志（rcl_interfaces/Log）
/robot/board/imu		# IMU数据（sensor_msgs/Imu）
/robot/board/battery	# 电池数据（sensor_msgs/BatteryState）
```

### 服务
```
/robot/board/query_config       # 查询单个配置
/robot/board/query_all_config   # 查询所有配置
/robot/board/write_config       # 写入配置
/robot/board/switch             # 开关操作
```

## C++ 使用示例

```cpp
#include "servo_robot_board_interface/ros_msg.hpp"

using namespace servo_robot_board_interface;

// 订阅电源数据
auto sub = node->create_subscription<PowerMsg>(
    TOPIC_BOARD_POWER, 10,
    [](const PowerMsg::SharedPtr msg) {
        RCLCPP_INFO(node->get_logger(), "Voltage: %.1fV", msg->servo_voltage);
    });

// 查询配置
auto client = node->create_client<QueryConfigSrv>(SERVICE_QUERY_CONFIG);
auto request = std::make_shared<QueryConfigSrv::Request>();
request->config_type = static_cast<uint8_t>(ConfigType::POWER_SERVO_CURRENT_LIMIT);
auto result = client->async_send_request(request);
```

## Python 使用示例

```python
from servo_robot_board_interface_msg.ros_msg import *

# 订阅电源数据
sub = node.create_subscription(
    BoardPower,
    TOPIC_BOARD_POWER,
    lambda msg: print(f"Voltage: {msg.servo_voltage:.1f}V"),
    10
)

# 查询配置
client = node.create_client(BoardQueryConfig, SERVICE_QUERY_CONFIG)
request = BoardQueryConfig.Request()
request.config_type = ConfigType.POWER_SERVO_CURRENT_LIMIT
future = client.call_async(request)
```

## 枚举类型

### ChargePhase（充电阶段）
| 值 | 名称 | 说明 |
|----|------|------|
| 1    | NotCharging        | 未充电         |
| 2    | PreCharge          | 预充电         |
| 3    | Cc                 | 恒流充电       |
| 4    | Cv                 | 恒压充电       |
| 5    | Full               | 充满           |
| 6    | PdSinkFault        | PD受电芯片故障 |
| 7    | UnsupportedCharger | 不支持的充电器 |

### StateChangeFlag（状态变更标志）
| 位 | 名称 | 说明 |
|----|------|------|
| 0 | CHARGER_CONNECT | 充电器 连接/拔出 |
| 1 | FAN | 风扇 开启/关闭 |
| 2 | POWER_SERVO | 舵机电源 开启/关闭 |
| 3 | POWER_5V        | 5V输出 开启/关闭 |
| 4 | BAT_EXT_OUT | 电池额外输出 开启/关闭 |

### ProtectionFlag（保护标志）
| 位 | 名称 | 说明 |
|----|------|------|
| 0 | SERVO_OVERCURRENT | 舵机过流 |
| 1 | SERVO_THERMAL | 舵机过热 |
| 2 | DCDC_5V_THERMAL | 5V过热 |
| 3 | CHARGE_DERATING | 充电降流 |
| 4 | CHARGE_THERMAL | 充电过热 |
| 5 | BATTERY_LOW | 电池低电量 |

### ConfigType（配置类型）
| 值 | 名称 | 单位 |
|----|------|------|
| 0x01 | Reset | - |
| 0x02 | Shutdown | - |
| 0x10 | SwitchServoPower | bool |
| 0x11 | Switch5VPower | bool |
| 0x12 | SwitchCharge | bool |
| 0x13 | SwitchBatExtOut | bool |
| 0x21 | PowerServoCurrentLimit | A |
| 0x22 | PowerServoTempLimit | °C |
| 0x23 | Power5vTempLimit | °C |
| 0x24 | ChargeMaxCurrent | A |
| 0x25 | ChargeTempDerating | °C |
| 0x26 | ChargeTempLimit | °C |
| 0x27 | ChargeStopVoltage | V |
| 0x28 | ChargeStopCapacity | % |
| 0x29 | TxLogLevel | - |

### SwitchType（开关类型）
| 值 | 名称 | 说明 |
|----|------|------|
| 0x10 | ServoPower | 舵机电源 |
| 0x11 | 5VPower | 5V电源 |
| 0x12 | Charge | 充电 |
| 0x13 | BatExtOut | 电池额外输出 |

## 构建

```bash
cd your_ros_ws
colcon build --packages-select servo_robot_board_interface 
source install/setup.bash
```

## 依赖

- `std_msgs`
- `rosidl_default_generators`
- `rosidl_default_runtime`

## License

GPL-3.0
