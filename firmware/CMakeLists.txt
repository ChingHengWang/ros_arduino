cmake_minimum_required(VERSION 2.8.3)

include_directories(${ROS_LIB_DIR})

# Remove this if using an Arduino without native USB (eg, other than Leonardo)
#add_definitions(-DUSB_CON)

#link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libraries)

generate_arduino_firmware(ros_arduino
  SRCS enc_get.cpp ${ROS_LIB_DIR}/time.cpp
  BOARD mega2560
  PORT /dev/ttyACM0
)
