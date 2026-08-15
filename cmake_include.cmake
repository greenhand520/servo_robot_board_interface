if (NOT ROS2_WS_SOURCE_BUILD OR NOT TARGET servo_robot_board_interface)
    find_package(servo_robot_board_interface REQUIRED)
endif ()

if (ROS2_WS_SOURCE_BUILD AND TARGET servo_robot_board_interface)
    rosidl_get_typesupport_target(servo_robot_board_interface_CPP_TYPESUPPORT_TARGET
            servo_robot_board_interface
            "rosidl_typesupport_cpp"
    )
    rosidl_get_typesupport_target(servo_robot_board_interface_FASTRTPS_CPP_TYPESUPPORT_TARGET
            servo_robot_board_interface
            "rosidl_typesupport_fastrtps_cpp"
    )
    rosidl_get_typesupport_target(servo_robot_board_interface_INTROSPECTION_CPP_TYPESUPPORT_TARGET
            servo_robot_board_interface
            "rosidl_typesupport_introspection_cpp"
    )
    if (servo_robot_board_interface_CPP_TYPESUPPORT_TARGET MATCHES "-NOTFOUND$"
            OR servo_robot_board_interface_FASTRTPS_CPP_TYPESUPPORT_TARGET MATCHES "-NOTFOUND$"
            OR servo_robot_board_interface_INTROSPECTION_CPP_TYPESUPPORT_TARGET MATCHES "-NOTFOUND$")
        message(FATAL_ERROR "The in-tree servo_robot_board_interface target does not provide rosidl_typesupport_cpp.")
    endif ()
    if (NOT DEFINED servo_robot_board_interface_SOURCE_DIR
            OR NOT IS_DIRECTORY "${servo_robot_board_interface_SOURCE_DIR}/include")
        message(FATAL_ERROR "The in-tree servo_robot_board_interface source include directory is unavailable.")
    endif ()
    target_link_libraries(${PROJECT_NAME}
            ${servo_robot_board_interface_CPP_TYPESUPPORT_TARGET}
    )
    target_include_directories(${PROJECT_NAME} PUBLIC
            "$<BUILD_INTERFACE:${servo_robot_board_interface_SOURCE_DIR}/include>")
else ()
    ament_target_dependencies(${PROJECT_NAME} servo_robot_board_interface)
endif ()

if (ROS2_WS_SOURCE_BUILD)
    target_link_libraries(${PROJECT_NAME}
            "-Wl,--no-as-needed"
            ${servo_robot_board_interface_FASTRTPS_CPP_TYPESUPPORT_TARGET}
            ${servo_robot_board_interface_INTROSPECTION_CPP_TYPESUPPORT_TARGET}
            "-Wl,--as-needed"
    )
endif ()