#pragma once

#include <algorithm>
#include <stdexcept>
#include <string>
#include <string_view>

// Message includes
#include "servo_robot_board_interface/msg/board_config.hpp"
#include "servo_robot_board_interface/msg/board_event.hpp"
#include "servo_robot_board_interface/msg/board_log.hpp"
#include "servo_robot_board_interface/msg/board_power.hpp"
#include "servo_robot_board_interface/msg/board_system.hpp"
#include "servo_robot_board_interface/msg/servo_target.hpp"

// Service includes
#include "servo_robot_board_interface/srv/board_command.hpp"
#include "servo_robot_board_interface/srv/board_query_all_config.hpp"
#include "servo_robot_board_interface/srv/board_query_config.hpp"
#include "servo_robot_board_interface/srv/board_switch.hpp"
#include "servo_robot_board_interface/srv/board_write_config.hpp"
#include "servo_robot_board_interface/srv/servo_forward.hpp"

// Action includes
#include "servo_robot_board_interface/action/board_firmware_update.hpp"

namespace servo_robot_board_interface {

    namespace detail {

        [[nodiscard]] constexpr bool
        is_ascii_whitespace(const char character) noexcept {
            return character == ' ' || (character >= '\t' && character <= '\r');
        }

        [[nodiscard]] inline bool
        is_empty_or_ascii_whitespace(const std::string_view value) noexcept {
            if (value.empty()) {
                return true;
            }
            return std::ranges::all_of(value.begin(), value.end(), is_ascii_whitespace);
        }

        /// 只做 endpoint 拼接所需的最小校验；调用者应提供 ROS 已规范化的 FQN。
        inline void require_prefix(const std::string_view prefix) {
            if (is_empty_or_ascii_whitespace(prefix) || prefix == "~/" ||
                prefix.find_first_of(" \t\n\r\v\f") != std::string_view::npos) {
                throw std::invalid_argument(
                    R"(prefix must be without ASCII whitespace and '\t\n\r\v\f')");
            }
        }

        [[nodiscard]] inline std::string
        normalized_prefix(const std::string_view prefix) {
            require_prefix(prefix);
            auto normalized = prefix;
            while (normalized.size() > 1 && normalized.back() == '/') {
                normalized.remove_suffix(1);
            }
            return std::string{normalized};
        }

        ///
        /// @param prefix 可以是节点名，也可以是节点完全限定名
        /// @param endpoint_suffix 节点后面的路径
        /// @return
        [[nodiscard]] inline std::string
        endpoint_name(const std::string_view prefix,
                      const std::string_view endpoint_suffix) {
            return normalized_prefix(prefix) + "~/" + std::string{endpoint_suffix};
        }

        inline constexpr std::string_view nodeName = "servo_robot_board_bridge";
    } // namespace detail

    /// 校验作为 ROS 路径段使用的稳定设备标识。
    inline void require_device_id(const std::string_view device_id) {
        if (detail::is_empty_or_ascii_whitespace(device_id) ||
            device_id.find_first_of("~/ \t\n\r\v\f") != std::string_view::npos) {
            throw std::invalid_argument(
                R"(device_id must not be empty and not contain '/', ASCII whitespace and \t\n\r\v\f)");
        }
    }

    // kPrivateTopic names
    inline constexpr std::string_view kPrivateTopicBoardPower = "~/robot/board/power";
    inline constexpr std::string_view kPrivateTopicBoardSystem = "~/robot/board/system";
    inline constexpr std::string_view kPrivateTopicBoardEvent = "~/robot/board/event";
    inline constexpr std::string_view kPrivateTopicBoardLog = "~/robot/board/log";
    inline constexpr std::string_view kPrivateTopicBoardConfig = "~/robot/board/config";
    inline constexpr std::string_view kPrivateTopicBoardImu = "~/robot/board/imu";
    inline constexpr std::string_view kPrivateTopicBoardBatteryState = "~/robot/board/battery_state";
    inline constexpr std::string_view kPrivateTopicBoardServoTarget = "~/robot/board/servo/target";

    // kPrivateSrv names
    inline constexpr std::string_view kPrivateSrvQueryConfig = "~/robot/board/query_config";
    inline constexpr std::string_view kPrivateSrvQueryAllConfig = "~/robot/board/query_all_config";
    inline constexpr std::string_view kPrivateSrvWriteConfig = "~/robot/board/write_config";
    inline constexpr std::string_view kPrivateSrvSwitch = "~/robot/board/switch";
    inline constexpr std::string_view kPrivateSrvServoForward = "~/robot/board/servo/forward";
    inline constexpr std::string_view kPrivateSrvServoCommand = "~/robot/board/command";

    // kPrivateAction names
    inline constexpr std::string_view kPrivateActionFirmwareUpdate = "~/robot/board/firmware_update";

    // Topic functions
    [[nodiscard]] inline std::string
    topic_board_power(const std::string_view node_fqn = detail::nodeName) {
        return detail::endpoint_name(node_fqn, "robot/board/power");
    }

    [[nodiscard]] inline std::string
    topic_board_system(const std::string_view node_fqn = detail::nodeName) {
        return detail::endpoint_name(node_fqn, "robot/board/system");
    }

    [[nodiscard]] inline std::string
    topic_board_event(const std::string_view node_fqn = detail::nodeName) {
        return detail::endpoint_name(node_fqn, "robot/board/event");
    }

    [[nodiscard]] inline std::string
    topic_board_log(const std::string_view node_fqn = detail::nodeName) {
        return detail::endpoint_name(node_fqn, "robot/board/log");
    }

    [[nodiscard]] inline std::string
    topic_board_config(const std::string_view node_fqn = detail::nodeName) {
        return detail::endpoint_name(node_fqn, "robot/board/config");
    }

    [[nodiscard]] inline std::string
    topic_board_imu(const std::string_view node_fqn = detail::nodeName) {
        return detail::endpoint_name(node_fqn, "robot/board/imu");
    }

    [[nodiscard]] inline std::string
    topic_board_battery_state(const std::string_view node_fqn = detail::nodeName) {
        return detail::endpoint_name(node_fqn, "robot/board/battery_state");
    }

    [[nodiscard]] inline std::string
    topic_board_servo_target(const std::string_view node_fqn = detail::nodeName) {
        return detail::endpoint_name(node_fqn, "robot/board/servo/target");
    }

    // Service functions
    [[nodiscard]] inline std::string
    srv_query_config(const std::string_view node_fqn = detail::nodeName) {
        return detail::endpoint_name(node_fqn, "robot/board/query_config");
    }

    [[nodiscard]] inline std::string
    srv_query_all_config(const std::string_view node_fqn = detail::nodeName) {
        return detail::endpoint_name(node_fqn, "robot/board/query_all_config");
    }

    [[nodiscard]] inline std::string
    srv_write_config(const std::string_view node_fqn = detail::nodeName) {
        return detail::endpoint_name(node_fqn, "robot/board/write_config");
    }

    [[nodiscard]] inline std::string
    srv_switch(const std::string_view node_fqn = detail::nodeName) {
        return detail::endpoint_name(node_fqn, "robot/board/switch");
    }

    [[nodiscard]] inline std::string
    srv_servo_forward(const std::string_view node_fqn = detail::nodeName) {
        return detail::endpoint_name(node_fqn, "robot/board/servo/forward");
    }

    [[nodiscard]] inline std::string
    srv_servo_command(const std::string_view node_fqn = detail::nodeName) {
        return detail::endpoint_name(node_fqn, "robot/board/command");
    }

    // Action functions
    [[nodiscard]] inline std::string
    action_firmware_update(const std::string_view node_fqn = detail::nodeName) {
        return detail::endpoint_name(node_fqn, "robot/board/firmware_update");
    }

    // Type aliases
    using MsgPower = msg::BoardPower;
    using MsgSystem = msg::BoardSystem;
    using MsgEvent = msg::BoardEvent;
    using MsgConfig = msg::BoardConfig;
    using MsgServoTarget = msg::ServoTarget;
    using MsgLog = msg::BoardLog;

    using SrvQueryConfig = srv::BoardQueryConfig;
    using SrvQueryAllConfig = srv::BoardQueryAllConfig;
    using SrvWriteConfig = srv::BoardWriteConfig;
    using SrvSwitch = srv::BoardSwitch;
    using SrvCommand = srv::BoardCommand;
    using ActionFirmwareUpdate = action::BoardFirmwareUpdate;
    using SrvServoForward = srv::ServoForward;

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
        RESET = 0x01,
        SHUTDOWN = 0x02,
        OTA = 0x03,
    };

} // namespace servo_robot_board_interface
