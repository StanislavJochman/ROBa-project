#!/usr/bin/env python

import rospy
from std_msgs.msg import String

def callback(data):
    rospy.loginfo("Received message: %s", data.data)

def listener():
    rospy.init_node('listener', anonymous=True)

    # Subscribe to the topic 'chatter' with the message type 'String'
    rospy.Subscriber('chatter', String, callback)

    # Spin to keep the script from exiting
    rospy.spin()

if __name__ == '__main__':
    print("Starting")
    listener()
