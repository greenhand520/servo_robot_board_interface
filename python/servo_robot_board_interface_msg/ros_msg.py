from enum import IntEnum
from servo_robot_board_interface.msg import (
    BoardPower,
    BoardSystem,
    BoardEvent,
    BoardConfig,
    ServoTarget,
)
from servo_robot_board_interface.srv import (
    BoardQueryConfig,
    BoardQueryAllConfig,
    BoardWriteConfig,
    BoardSwitch,
    BoardCommand,
    BoardFirmwareUpdate,
    ServoForward,
)

# Topic names
TOPIC_BOARD_POWER = "/robot/board/power"
TOPIC_BOARD_SYSTEM = "/robot/board/system"
TOPIC_BOARD_EVENT = "/robot/board/event"
TOPIC_BOARD_LOG = "/robot/board/log"
TOPIC_BOARD_CONFIG = "/robot/board/config"
TOPIC_BOARD_IMU = "/robot/board/imu"
TOPIC_BOARD_BATTERY_STATE = "/robot/board/battery_state"
TOPIC_BOARD_SERVO_TARGET = "/robot/board/servo/target"


# Service names
SERVICE_QUERY_CONFIG = "/robot/board/query_config"
SERVICE_QUERY_ALL_CONFIG = "/robot/board/query_all_config"
SERVICE_WRITE_CONFIG = "/robot/board/write_config"
SERVICE_SWITCH = "/robot/board/switch"
SERVICE_SERVO_FORWARD = "/robot/board/servo/forward"
SERVICE_SERVO_COMMAND = "/robot/board/command"
SERVICE_SERVO_FIRMWARE_UPDATE = "/robot/board/firmware_update"


class ChargePhase(IntEnum):
    NOT_CHARGING = 0
    PRE_CHARGE = 1
    CC = 2
    CV = 3
    FULL = 4
    PD_SINK_FAULT = 5
    UNSUPPORTED_CHARGER = 6

    def __str__(self) -> str:
        return self.name

    @staticmethod
    def from_str(s: str) -> "ChargePhase":
        try:
            return ChargePhase[s.upper()]
        except KeyError:
            return ChargePhase.NOT_CHARGING


class ProtectionFlag(IntEnum):
    SERVO_OVERCURRENT = 1 << 0
    SERVO_THERMAL = 1 << 1
    DCDC_5V_THERMAL = 1 << 2
    CHARGE_DERATING = 1 << 3
    CHARGE_THERMAL = 1 << 4
    BATTERY_LOW = 1 << 5


class ConfigType(IntEnum):
    RESET = 0x01
    SHUTDOWN = 0x02
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


