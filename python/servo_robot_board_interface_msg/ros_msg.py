import re
from typing import Optional, Final
from dataclasses import dataclass


class Detail:
    """内部工具类"""

    def __init__(self):
        pass

    NODE_NAME: Final[str] = "servo_robot_board_bridge"

    @staticmethod
    def is_ascii_whitespace(character: str) -> bool:
        """检查字符是否为ASCII空白字符"""
        return character == ' ' or ('\t' <= character <= '\r')

    @staticmethod
    def is_empty_or_ascii_whitespace(value: str) -> bool:
        """检查字符串是否为空或仅包含ASCII空白字符"""
        if not value:
            return True
        return all(Detail.is_ascii_whitespace(c) for c in value)

    @staticmethod
    def require_prefix(prefix: str) -> None:
        """校验前缀"""
        if (Detail.is_empty_or_ascii_whitespace(prefix) or
                prefix == "~/" or
                any(c in prefix for c in " \t\n\r\v\f")):
            raise ValueError('prefix must be without ASCII whitespace and "\\t\\n\\r\\v\\f"')

    @staticmethod
    def normalized_prefix(prefix: str) -> str:
        """规范化前缀"""
        Detail.require_prefix(prefix)
        normalized = prefix.rstrip('/')
        return normalized

    @staticmethod
    def endpoint_name(prefix: str, endpoint_suffix: str) -> str:
        """
        生成端点名称

        Args:
            prefix: 节点名或节点完全限定名
            endpoint_suffix: 节点后面的路径

        Returns:
            完整的端点名称
        """
        return Detail.normalized_prefix(prefix) + "~/" + endpoint_suffix


def require_device_id(device_id: str) -> None:
    """
    校验作为ROS路径段使用的稳定设备标识

    Args:
        device_id: 设备标识符

    Raises:
        ValueError: 如果device_id无效
    """
    if (Detail.is_empty_or_ascii_whitespace(device_id) or
            any(c in device_id for c in "/~ \t\n\r\v\f")):
        raise ValueError(
            'device_id must not be empty and not contain "/", ASCII whitespace and "\\t\\n\\r\\v\\f"'
        )


# Topic名称常量
PRIVATE_TOPIC_BOARD_POWER: Final[str] = "~/robot/board/power"
PRIVATE_TOPIC_BOARD_SYSTEM: Final[str] = "~/robot/board/system"
PRIVATE_TOPIC_BOARD_EVENT: Final[str] = "~/robot/board/event"
PRIVATE_TOPIC_BOARD_LOG: Final[str] = "~/robot/board/log"
PRIVATE_TOPIC_BOARD_CONFIG: Final[str] = "~/robot/board/config"
PRIVATE_TOPIC_BOARD_IMU: Final[str] = "~/robot/board/imu"
PRIVATE_TOPIC_BOARD_BATTERY_STATE: Final[str] = "~/robot/board/battery_state"
PRIVATE_TOPIC_BOARD_SERVO_TARGET: Final[str] = "~/robot/board/servo/target"

# Service名称常量
PRIVATE_SRV_QUERY_CONFIG: Final[str] = "~/robot/board/query_config"
PRIVATE_SRV_QUERY_ALL_CONFIG: Final[str] = "~/robot/board/query_all_config"
PRIVATE_SRV_WRITE_CONFIG: Final[str] = "~/robot/board/write_config"
PRIVATE_SRV_SWITCH: Final[str] = "~/robot/board/switch"
PRIVATE_SRV_SERVO_FORWARD: Final[str] = "~/robot/board/servo/forward"
PRIVATE_SRV_SERVO_COMMAND: Final[str] = "~/robot/board/command"
PRIVATE_SRV_SERVO_FIRMWARE_UPDATE: Final[str] = "~/robot/board/firmware_update"


# Topic函数
def topic_board_power(node_fqn: str = Detail.NODE_NAME) -> str:
    """获取Board Power主题名称"""
    return Detail.endpoint_name(node_fqn, "robot/board/power")


def topic_board_system(node_fqn: str = Detail.NODE_NAME) -> str:
    """获取Board System主题名称"""
    return Detail.endpoint_name(node_fqn, "robot/board/system")


def topic_board_event(node_fqn: str = Detail.NODE_NAME) -> str:
    """获取Board Event主题名称"""
    return Detail.endpoint_name(node_fqn, "robot/board/event")


def topic_board_log(node_fqn: str = Detail.NODE_NAME) -> str:
    """获取Board Log主题名称"""
    return Detail.endpoint_name(node_fqn, "robot/board/log")


def topic_board_config(node_fqn: str = Detail.NODE_NAME) -> str:
    """获取Board Config主题名称"""
    return Detail.endpoint_name(node_fqn, "robot/board/config")


def topic_board_imu(node_fqn: str = Detail.NODE_NAME) -> str:
    """获取Board IMU主题名称"""
    return Detail.endpoint_name(node_fqn, "robot/board/imu")


def topic_board_battery_state(node_fqn: str = Detail.NODE_NAME) -> str:
    """获取Board Battery State主题名称"""
    return Detail.endpoint_name(node_fqn, "robot/board/battery_state")


def topic_board_servo_target(node_fqn: str = Detail.NODE_NAME) -> str:
    """获取Board Servo Target主题名称"""
    return Detail.endpoint_name(node_fqn, "robot/board/servo/target")


# Service函数
def srv_query_config(node_fqn: str = Detail.NODE_NAME) -> str:
    """获取Query Config服务名称"""
    return Detail.endpoint_name(node_fqn, "robot/board/query_config")


def srv_query_all_config(node_fqn: str = Detail.NODE_NAME) -> str:
    """获取Query All Config服务名称"""
    return Detail.endpoint_name(node_fqn, "robot/board/query_all_config")


def srv_write_config(node_fqn: str = Detail.NODE_NAME) -> str:
    """获取Write Config服务名称"""
    return Detail.endpoint_name(node_fqn, "robot/board/write_config")


def srv_switch(node_fqn: str = Detail.NODE_NAME) -> str:
    """获取Switch服务名称"""
    return Detail.endpoint_name(node_fqn, "robot/board/switch")


def srv_servo_forward(node_fqn: str = Detail.NODE_NAME) -> str:
    """获取Servo Forward服务名称"""
    return Detail.endpoint_name(node_fqn, "robot/board/servo/forward")


def srv_servo_command(node_fqn: str = Detail.NODE_NAME) -> str:
    """获取Servo Command服务名称"""
    return Detail.endpoint_name(node_fqn, "robot/board/command")


def srv_servo_firmware_update(node_fqn: str = Detail.NODE_NAME) -> str:
    """获取Firmware Update服务名称"""
    return Detail.endpoint_name(node_fqn, "robot/board/firmware_update")


class ConfigType(IntEnum):
    SWITCH_SERVO_POWER = 0x10
    SWITCH_5V_POWER = 0x11
    SWITCH_CHARGE = 0x12
    SWITCH_BAT_EXT_OUT = 0x13
    CHARGE_STOP_SOC = 0x20
    TX_LOG_LEVEL = 0x21
    POWER_SERVO_CURRENT_LIMIT_MA = 0x30
    POWER_SERVO_TEMP_LIMIT = 0x31
    POWER_5V_TEMP_LIMIT = 0x32
    CHARGE_MAX_CURRENTMA = 0x33
    CHARGE_TEMP_DERATING = 0x34
    CHARGE_TEMP_LIMIT = 0x35
    CHARGE_STOP_VOLTAGE_MV = 0x36
    SERVO_BAUD_RATE = 0x37


class CommandType(IntEnum):
    RESET = 0x01
    SHUTDOWN = 0x02
    OTA = 0x03

    def __str__(self) -> str:
        return self.name


# 使用示例
if __name__ == "__main__":
    # 获取主题名称
    print(topic_board_power())

    # 使用自定义节点名
    print(topic_board_event("custom_node"))

    # 获取服务名称
    print(srv_query_config())

    # 校验设备ID
    try:
        require_device_id("valid_device_123")
        print("Device ID is valid")
    except ValueError as e:
        print(f"Invalid device ID: {e}")
