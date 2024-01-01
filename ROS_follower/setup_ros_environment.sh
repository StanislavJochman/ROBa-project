#!/bin/bash

# Set the path to your ROS workspace
ROS_WORKSPACE="/home/robot/ROS_follower"

# Check if the workspace exists
if [ ! -d "$ROS_WORKSPACE" ]; then
  echo "Error: ROS workspace not found at $ROS_WORKSPACE"
  exit 1
fi

# Source ROS setup files
source $ROS_WORKSPACE/devel/setup.bash

# Print a message indicating successful setup
echo "ROS environment is now set up for $ROS_WORKSPACE"