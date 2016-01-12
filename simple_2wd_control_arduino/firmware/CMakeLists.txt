cmake_minimum_required(VERSION 2.8.3)

include_directories(${ROS_LIB_DIR} ../lib)

# Remove this if using an Arduino without native USB (eg, other than Leonardo)
add_definitions(-DUSB_CON)

generate_arduino_firmware(controller
  SRCS controller.cpp ../lib/AFMotor.cpp ${ROS_LIB_DIR}/time.cpp
  BOARD uno
  PORT /dev/ttyUSB0
)
