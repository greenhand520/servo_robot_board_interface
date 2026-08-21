cmake_minimum_required(VERSION 3.8)
set(PROJECT_VERSION 1.0.0)
project(servo_robot_board_interface VERSION ${PROJECT_VERSION})

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(std_msgs REQUIRED)
find_package(builtin_interfaces REQUIRED)
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
        msg/Power.msg
        msg/DeviceInfo.msg
        msg/Diagnostic.msg
        msg/Event.msg
        msg/Log.msg
        msg/Config.msg
        msg/Response.msg
        msg/ServoTarget.msg
        msg/ConfigType.msg
        msg/RequestType.msg
        srv/QueryConfig.srv
        srv/QueryAllConfig.srv
        srv/QueryDeviceInfo.srv
        srv/WriteConfig.srv
        srv/WriteConfigSwitch.srv
        srv/ServoForward.srv
        srv/SendCommand.srv
        srv/SendRequest.srv
        action/FirmwareUpdate.action
        DEPENDENCIES builtin_interfaces std_msgs
)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME})
  install(DIRECTORY include/${PROJECT_NAME}/
          DESTINATION include/${PROJECT_NAME}/${PROJECT_NAME}
  )
  ament_export_include_directories(include/${PROJECT_NAME})
endif()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/python/${PROJECT_NAME}_msg)
  install(DIRECTORY python/${PROJECT_NAME}_msg/
          DESTINATION ${PYTHON_INSTALL_DIR}/${PROJECT_NAME}_msg
  )
endif()


ament_package()
