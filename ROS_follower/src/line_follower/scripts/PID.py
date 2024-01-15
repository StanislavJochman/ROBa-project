#!/usr/bin/env python

import rospy
from std_msgs.msg import String, UInt8

class PID:
    def __init__(self, kp, ki, kd, max_error):
        self.kp = kp
        self.ki = ki
        self.kd = kd
        self.max_error = max_error
        
        self.p = 0
        self.i = 0
        self.d = 0

        self.last_error = 0

        self.speed = 0

    def update(self, error):
        # Limit the error to the specified maximum value
        error = max(min(error, self.max_error), -self.max_error)

        self.p = error
        self.i += error
        self.d = error - self.last_error
        self.last_error = error

        self.speed = self.kp * self.p + self.ki * self.i + self.kd * self.d
        self.speed = max(min(self.speed, 127), -127)  # Clamp speed to the range of -127 to 127
        print(self.speed)

def callback(data, pid_controller):
    error = int(data.data)-4
    print(error)
    pid_controller.update(error)

def writer(pid_controller):
    rospy.init_node('writer', anonymous=True)
    pub = rospy.Publisher('writer', UInt8, queue_size=1)

    rate = rospy.Rate(30)  # 30 Hz

    while not rospy.is_shutdown():
        pub.publish(pid_controller.speed+127)
        rate.sleep()

def listener(pid_controller):
    rospy.init_node('listener', anonymous=True)
    rospy.Subscriber('chatter', UInt8, callback, pid_controller)

    # Wait for the first message on the '/chatter' topic
    rospy.wait_for_message('chatter', UInt8)

    rospy.spin()

if __name__ == '__main__':
    print("Node started")
    # Initialize the PID controller PID(kp, ki, kd, max_error)
    PID_controller = PID(10, 1, 1, 3)
    try:
        listener(PID_controller)
    except rospy.ROSInterruptException:
        pass
    writer(PID_controller)
