cmake_minimum_required(VERSION 2.8.3)
project(line_follower)

find_package(catkin REQUIRED COMPONENTS
  rospy
  std_msgs
)

catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
)

install(PROGRAMS
  scripts/PID.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
