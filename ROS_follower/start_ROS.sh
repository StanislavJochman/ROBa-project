#/bin/bash

sudo nvpmodel -m 1
roslaunch line_follower PID_robot.launch
./setup_ros_environment.sh
roscore &
rosrun rosserial_python serial_node.py /dev/ttyUSB0 &
rosrun line_follower PID.py