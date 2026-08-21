#pragma once

#include <algorithm>
#include <stdexcept>
#include <string>
#include <string_view>

// Message includes
#include "servo_robot_board_interface/msg/config.hpp"
#include "servo_robot_board_interface/msg/device_info.hpp"
#include "servo_robot_board_interface/msg/diagnostic.hpp"
#include "servo_robot_board_interface/msg/event.hpp"
#include "servo_robot_board_interface/msg/log.hpp"
#include "servo_robot_board_interface/msg/power.hpp"
#include "servo_robot_board_interface/msg/response.hpp"
#include "servo_robot_board_interface/msg/servo_target.hpp"
#include "servo_robot_board_interface/msg/config_type.hpp"
#include "servo_robot_board_interface/msg/request_type.hpp"

// Service includes
#include "servo_robot_board_interface/srv/send_command.hpp"
#include "servo_robot_board_interface/srv/query_all_config.hpp"
#include "servo_robot_board_interface/srv/query_config.hpp"
#include "servo_robot_board_interface/srv/query_device_info.hpp"
#include "servo_robot_board_interface/srv/send_request.hpp"
#include "servo_robot_board_interface/srv/write_config_switch.hpp"
#include "servo_robot_board_interface/srv/write_config.hpp"
#include "servo_robot_board_interface/srv/servo_forward.hpp"

// Action includes
#include "servo_robot_board_interface/action/firmware_update.hpp"

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
    inline constexpr std::string_view kPrivateTopicPower = "~/robot/board/power";
    inline constexpr std::string_view kPrivateTopicDiagnostic = "~/robot/board/diagnostic";
    inline constexpr std::string_view kPrivateTopicEvent = "~/robot/board/event";
    inline constexpr std::string_view kPrivateTopicLog = "~/robot/board/log";
    inline constexpr std::string_view kPrivateTopicConfig = "~/robot/board/config";
    inline constexpr std::string_view kPrivateTopicImu = "~/robot/board/imu";
    inline constexpr std::string_view kPrivateTopicBatteryState = "~/robot/board/battery_state";
    inline constexpr std::string_view kPrivateTopicServoTarget = "~/robot/board/servo/target";

    // kPrivateSrv names
    inline constexpr std::string_view kPrivateSrvRequest = "~/robot/board/request";
    inline constexpr std::string_view kPrivateSrvQueryConfig = "~/robot/board/query/config";
    inline constexpr std::string_view kPrivateSrvQueryAllConfig = "~/robot/board/query/all_config";
    inline constexpr std::string_view kPrivateSrvWriteConfig = "~/robot/board/write/config";
    inline constexpr std::string_view kPrivateSrvSwitch = "~/robot/board/write/config_switch";
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
    topic_board_diagnostic(const std::string_view node_fqn = detail::nodeName) {
        return detail::endpoint_name(node_fqn, "robot/board/diagnostic");
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
        return detail::endpoint_name(node_fqn, "robot/board/query/config");
    }

    [[nodiscard]] inline std::string
    srv_query_all_config(const std::string_view node_fqn = detail::nodeName) {
        return detail::endpoint_name(node_fqn, "robot/board/query/all_config");
    }

    [[nodiscard]] inline std::string
    srv_write_config(const std::string_view node_fqn = detail::nodeName) {
        return detail::endpoint_name(node_fqn, "robot/board/write/config");
    }

    [[nodiscard]] inline std::string
    srv_switch(const std::string_view node_fqn = detail::nodeName) {
        return detail::endpoint_name(node_fqn, "robot/board/write/config_switch");
    }

    [[nodiscard]] inline std::string
    srv_servo_forward(const std::string_view node_fqn = detail::nodeName) {
        return detail::endpoint_name(node_fqn, "robot/board/servo/forward");
    }

    [[nodiscard]] inline std::string
    srv_servo_command(const std::string_view node_fqn = detail::nodeName) {
        return detail::endpoint_name(node_fqn, "robot/board/command");
    }

    [[nodiscard]] inline std::string
    srv_query_device_info(const std::string_view node_fqn = detail::nodeName) {
        return detail::endpoint_name(node_fqn, "robot/board/device_info");
    }

    [[nodiscard]] inline std::string
    srv_request(const std::string_view node_fqn = detail::nodeName) {
        return detail::endpoint_name(node_fqn, "robot/board/request");
    }

    // Action functions
    [[nodiscard]] inline std::string
    action_firmware_update(const std::string_view node_fqn = detail::nodeName) {
        return detail::endpoint_name(node_fqn, "robot/board/firmware_update");
    }

    // Type aliases
    using MsgPower = msg::Power;
    using MsgDevice = msg::DeviceInfo;
    using MsgDiagnostic = msg::Diagnostic;
    using MsgEvent = msg::Event;
    using MsgConfig = msg::Config;
    using MsgResponse = msg::Response;
    using MsgServoTarget = msg::ServoTarget;
    using MsgLog = msg::Log;

    using SrvQueryConfig = srv::QueryConfig;
    using SrvQueryAllConfig = srv::QueryAllConfig;
    using SrvWriteConfig = srv::WriteConfig;
    using SrvWriteConfigSwitch = srv::WriteConfigSwitch;
    using SrvQueryDeviceInfo = srv::QueryDeviceInfo;
    using SrvSendCommand = srv::SendCommand;
    using SrvSendRequest = srv::SendRequest;
    using ActionFirmwareUpdate = action::FirmwareUpdate;
    using SrvServoForward = srv::ServoForward;

} // namespace servo_robot_board_interface
