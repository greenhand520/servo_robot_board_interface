#pragma once

#include <cstdint>
#include <string>
#include <array>
#include <algorithm>

// Message includes
#include "servo_robot_board_interface/msg/board_power.hpp"
#include "servo_robot_board_interface/msg/board_thermal.hpp"
#include "servo_robot_board_interface/msg/board_system.hpp"
#include "servo_robot_board_interface/msg/board_event.hpp"
#include "servo_robot_board_interface/msg/board_config.hpp"

// Service includes
#include "servo_robot_board_interface/srv/board_query_config.hpp"
#include "servo_robot_board_interface/srv/board_query_all_config.hpp"
#include "servo_robot_board_interface/srv/board_write_config.hpp"
#include "servo_robot_board_interface/srv/board_switch.hpp"
#include "servo_robot_board_interface/srv/board_command.hpp"
#include "servo_robot_board_interface/srv/board_firmware_update.hpp"
#include "servo_robot_board_interface/srv/servo_forward.hpp"

namespace servo_robot_board_interface {

    // Topic names
    inline const std::string TOPIC_BOARD_POWER = "/robot/board/power";
    inline const std::string TOPIC_BOARD_SYSTEM = "/robot/board/system";
    inline const std::string TOPIC_BOARD_EVENT = "/robot/board/event";
    inline const std::string TOPIC_BOARD_LOG = "/robot/board/log";
    inline const std::string TOPIC_BOARD_CONFIG = "/robot/board/config";
    inline const std::string TOPIC_BOARD_IMU = "/robot/board/imu";
    inline const std::string TOPIC_BOARD_BATTERY_STATE = "/robot/board/battery_state";
    inline const std::string TOPIC_BOARD_SERVO_TARGET = "/robot/board/servo/target";

    // Service names
    inline const std::string SERVICE_QUERY_CONFIG = "/robot/board/query_config";
    inline const std::string SERVICE_QUERY_ALL_CONFIG = "/robot/board/query_all_config";
    inline const std::string SERVICE_WRITE_CONFIG = "/robot/board/write_config";
    inline const std::string SERVICE_SWITCH = "/robot/board/switch";
    inline const std::string SERVICE_SERVO_FORWARD = "/robot/board/servo/forward";
    inline const std::string SERVICE_SERVO_COMMAND = "/robot/board/command";
    inline const std::string SERVICE_SERVO_FIRMWARE_UPDATE = "/robot/board/firmware_update";

    // Type aliases
    using PowerMsg = msg::BoardPower;
    using SystemMsg = msg::BoardSystem;
    using EventMsg = msg::BoardEvent;
    using ConfigMsg = msg::BoardConfig;
    using ServoTargetMsg = msg::ServoTarget;

    using QueryConfigSrv = srv::BoardQueryConfig;
    using QueryAllConfigSrv = srv::BoardQueryAllConfig;
    using WriteConfigSrv = srv::BoardWriteConfig;
    using SwitchSrv = srv::BoardSwitch;
    using CommandSrv = srv::BoardCommand;
    using FirmwareUpdateSrv = srv::BoardFirmwareUpdate;
    using ServoForwardSrv = srv::ServoForward;

    // Charge phase enum
    enum class ChargePhase : uint8_t {
        NOT_CHARGING = 0,
        PRE_CHARGE = 1,
        CC = 2,
        CV = 3,
        FULL = 4,
        PD_SINK_FAULT = 5,
        UNSUPPORTED_CHARGER = 6
    };

    constexpr std::array<const char*, 8> CHARGE_PHASE_NAMES = {
        "NotCharging",
        "PreCharge",
        "Cc",
        "Cv",
        "Full",
        "PdSinkFault",
        "UnsupportedCharger"
    };

    inline const char* charge_phase_to_str(ChargePhase phase) {
        const auto index = static_cast<uint8_t>(phase);
        if (index < CHARGE_PHASE_NAMES.size()) {
            return CHARGE_PHASE_NAMES[index];
        }
        return CHARGE_PHASE_NAMES[0];
    }

    // Protection flags
    enum ProtectionFlag : uint16_t {
        SERVO_OVERCURRENT = 1 << 0,
        SERVO_THERMAL     = 1 << 1,
        DCDC_5V_THERMAL   = 1 << 2,
        CHARGE_DERATING   = 1 << 3,
        CHARGE_THERMAL    = 1 << 4,
        BATTERY_LOW       = 1 << 5,
    };

    // Config type enum
    enum class ConfigType : uint8_t {
		SWITCH_SERVO_POWER = 0x10,
		SWITCH_5V_POWER = 0x11,
		SWITCH_CHARGE = 0x12,
		SWITCH_BAT_EXT_OUT = 0x13,
		CHARGE_STOP_SOC = 0x20,
		TX_LOG_LEVEL = 0x21,
		POWER_SERVO_CURRENT_LIMIT_MA = 0x30,
		POWER_SERVO_TEMP_LIMIT = 0x31,
		POWER_5V_TEMP_LIMIT = 0x32,
		CHARGE_MAX_CURRENTMA = 0x33,
		CHARGE_TEMP_DERATING = 0x34,
		CHARGE_TEMP_LIMIT = 0x35,
		CHARGE_STOP_VOLTAGE_MV = 0x36,
		SERVO_BAUD_RATE = 0x37,
    };

    // Board command type enum
    enum class CommandType : uint8_t {
        RESET   = 0x01,
        SHUTDOWN = 0x02,
        OTA     = 0x03,
    };

}
