cmake_minimum_required(VERSION 3.5)
project(buggy)

# Find packages
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(builtin_interfaces REQUIRED)
find_package(rosidl_default_generators REQUIRED)

# Declare msg and srv generation BEFORE add_executable()
rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/CustomMsg.msg"
  "srv/CustomSrv.srv"
  DEPENDENCIES std_msgs geometry_msgs builtin_interfaces
)

set(dependencies
  rclcpp
  std_msgs
  geometry_msgs
  builtin_interfaces
)

add_executable(pub src/pub.cpp)
ament_target_dependencies(pub ${dependencies})
rosidl_target_interfaces(pub ${PROJECT_NAME} "rosidl_typesupport_cpp")

add_executable(sub src/sub.cpp)
ament_target_dependencies(sub ${dependencies})
rosidl_target_interfaces(sub ${PROJECT_NAME} "rosidl_typesupport_cpp")

# Install
install(TARGETS
  sub
  pub
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch DESTINATION share/${PROJECT_NAME})
ament_export_dependencies(rosidl_default_runtime)
ament_export_dependencies(${dependencies})
ament_package()