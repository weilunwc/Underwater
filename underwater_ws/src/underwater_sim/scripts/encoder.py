#!/usr/bin/env python

import rospy
from sensor_msgs.msg import JointState
from underwater_msg.msg import Encoder
import tf
import tf2_ros

import numpy as np


class EncoderBroadcast:
    def __init__(self):
        self.pub = rospy.Publisher('my_encoder/joint_states', JointState, queue_size=10)
        self.sub1 = rospy.Subscriber('encoder_1', Encoder, self.encoder1_sub)
        self.sub2 = rospy.Subscriber('encoder_2', Encoder, self.encoder2_sub)
        self.sub3 = rospy.Subscriber('encoder_3', Encoder, self.encoder3_sub)
        
        
        self.motor1_angle = 0.0
        self.motor2_angle = 0.0
        self.motor3_angle = 0.0
        self.center_motor_angle = 0.0
        self.sequence = 0.0
    
    def broadcast(self):
        j = JointState()
        j.name = ["motor1", "motor2", "motor3", "center_motor"]
        j.position = [self.motor1_angle, self.motor2_angle, self.motor3_angle, self.center_motor_angle]
        self.pub.publish(j)
        
    def encoder1_sub(self, msg):
        self.motor1_angle = np.deg2rad(msg.encoder_angle)
    
    def encoder2_sub(self, msg):
        self.motor2_angle = np.deg2rad(msg.encoder_angle)
    
    def encoder3_sub(self, msg):
        self.motor3_angle = np.deg2rad(msg.encoder_angle)


if __name__ == '__main__':
    encoder_broadcast = EncoderBroadcast()
    rospy.init_node('encoder_broadcast')
    rate = rospy.Rate(10)
    while not rospy.is_shutdown():
        encoder_broadcast.broadcast()
        rate.sleep()

