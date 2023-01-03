cmake_minimum_required(VERSION 3.8)
project(first_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

# 4 Añadir todas las dependencias que necesito, mi nodo depende de esos paquetes/librerias y que sin ellas no pueden funcionar
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

# 3 Le digo a ROS que mis includes estan en la carpeta include, aunque los puedo poner en otra carpeta, se recomienda el formato enter
include_directories(
  include
  )

# 1 Me creo un ejecutable llamado ** que esta en el SRC
# add_executable(hello src/hello.cpp)
add_executable(randomController src/randomController.cpp)
add_executable(actuator src/actuator.cpp)
add_executable(keyController src/keyController.cpp)
add_executable(squareController src/squareController.cpp)
#add_executable(randomController src/randomController.cpp src/mimain.cpp) Si tuviera el main en otro fichero, probar en casa

# 2
install(TARGETS
  # hello
  randomController
  actuator
  keyController
  squareController
  DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}/)

ament_target_dependencies(randomController rclcpp std_msgs)
ament_target_dependencies(actuator rclcpp std_msgs geometry_msgs)
ament_target_dependencies(keyController rclcpp std_msgs)
ament_target_dependencies(squareController rclcpp std_msgs)
ament_package()
