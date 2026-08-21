import re
from enum import IntEnum
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


# Topic 路径
K_PRIVATE_TOPIC_POWER: str = "~/robot/board/power"
K_PRIVATE_TOPIC_DIAGNOSTIC: str = "~/robot/board/diagnostic"
K_PRIVATE_TOPIC_EVENT: str = "~/robot/board/event"
K_PRIVATE_TOPIC_LOG: str = "~/robot/board/log"
K_PRIVATE_TOPIC_CONFIG: str = "~/robot/board/config"
K_PRIVATE_TOPIC_IMU: str = "~/robot/board/imu"
K_PRIVATE_TOPIC_BATTERY_STATE: str = "~/robot/board/battery_state"
K_PRIVATE_TOPIC_SERVO_TARGET: str = "~/robot/board/servo/target"

# Service 路径
K_PRIVATE_SRV_REQUEST: str = "~/robot/board/request"
K_PRIVATE_SRV_QUERY_CONFIG: str = "~/robot/board/query/config"
K_PRIVATE_SRV_QUERY_ALL_CONFIG: str = "~/robot/board/query/all_config"
K_PRIVATE_SRV_WRITE_CONFIG: str = "~/robot/board/write/config"
K_PRIVATE_SRV_SWITCH: str = "~/robot/board/write/config_switch"
K_PRIVATE_SRV_SERVO_FORWARD: str = "~/robot/board/servo/forward"
K_PRIVATE_SRV_SERVO_COMMAND: str = "~/robot/board/command"

# Action 路径
K_PRIVATE_ACTION_FIRMWARE_UPDATE: str = "~/robot/board/firmware_update"



# ═══ Topic endpoint 函数 ═══

def topic_power(node_fqn: str = Detail.NODE_NAME) -> str:
    return Detail.endpoint_name(node_fqn, "robot/board/power")


def topic_diagnostic(node_fqn: str = Detail.NODE_NAME) -> str:
    return Detail.endpoint_name(node_fqn, "robot/board/diagnostic")


def topic_event(node_fqn: str = Detail.NODE_NAME) -> str:
    return Detail.endpoint_name(node_fqn, "robot/board/event")


def topic_log(node_fqn: str = Detail.NODE_NAME) -> str:
    return Detail.endpoint_name(node_fqn, "robot/board/log")


def topic_config(node_fqn: str = Detail.NODE_NAME) -> str:
    return Detail.endpoint_name(node_fqn, "robot/board/config")


def topic_imu(node_fqn: str = Detail.NODE_NAME) -> str:
    return Detail.endpoint_name(node_fqn, "robot/board/imu")


def topic_battery_state(node_fqn: str = Detail.NODE_NAME) -> str:
    return Detail.endpoint_name(node_fqn, "robot/board/battery_state")


def topic_servo_target(node_fqn: str = Detail.NODE_NAME) -> str:
    return Detail.endpoint_name(node_fqn, "robot/board/servo/target")


# ═══ Service endpoint 函数 ═══

def srv_query_config(node_fqn: str = Detail.NODE_NAME) -> str:
    return Detail.endpoint_name(node_fqn, "robot/board/query/config")


def srv_query_all_config(node_fqn: str = Detail.NODE_NAME) -> str:
    return Detail.endpoint_name(node_fqn, "robot/board/query/all_config")


def srv_write_config(node_fqn: str = Detail.NODE_NAME) -> str:
    return Detail.endpoint_name(node_fqn, "robot/board/write/config")


def srv_switch(node_fqn: str = Detail.NODE_NAME) -> str:
    return Detail.endpoint_name(node_fqn, "robot/board/write/config_switch")


def srv_servo_forward(node_fqn: str = Detail.NODE_NAME) -> str:
    return Detail.endpoint_name(node_fqn, "robot/board/servo/forward")


def srv_servo_command(node_fqn: str = Detail.NODE_NAME) -> str:
    return Detail.endpoint_name(node_fqn, "robot/board/command")


def srv_query_device_info(node_fqn: str = Detail.NODE_NAME) -> str:
    return Detail.endpoint_name(node_fqn, "robot/board/device_info")


def srv_request(node_fqn: str = Detail.NODE_NAME) -> str:
    return Detail.endpoint_name(node_fqn, "robot/board/request")


# ═══ Action endpoint 函数 ═══

def action_firmware_update(node_fqn: str = Detail.NODE_NAME) -> str:
    return Detail.endpoint_name(node_fqn, "robot/board/firmware_update")


# 使用示例
if __name__ == "__main__":
    # 获取主题名称
    print(topic_power())

    # 使用自定义节点名
    print(topic_event("custom_node"))

    # 获取服务名称
    print(srv_query_config())

    # 校验设备ID
    try:
        require_device_id("valid_device_123")
        print("Device ID is valid")
    except ValueError as e:
        print(f"Invalid device ID: {e}")
