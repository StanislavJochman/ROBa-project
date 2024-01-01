#/bin/bash
rsync -avz --exclude-from=exclude.txt . robot@robot-desktop.local:/home/robot/ROS_follower