#/bin/bash
./setup_ros_environment.sh
roscore &
rosrun rosserial_python serial_node.py /dev/ttyUSB0 &
rosrun LineFollower PID.py