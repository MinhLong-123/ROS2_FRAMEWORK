cmake_minimum_required(VERSION 3.8)
project(cpp_pubsub_turtlesim)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)

add_executable(publisher src/publisher_turtlesim.cpp)
add_executable(subscriber src/subscriber_turtlesim.cpp)
ament_target_dependencies(publisher rclcpp geometry_msgs)
ament_target_dependencies(subscriber rclcpp geometry_msgs)
install(TARGETS
  publisher
  subscriber
  DESTINATION lib/${PROJECT_NAME}
)
install(
  DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}/
)

ament_package()
