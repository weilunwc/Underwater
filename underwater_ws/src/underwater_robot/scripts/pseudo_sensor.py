#!/usr/bin/env python
# Write a pseudo sensor info

import rospy
from underwater_msg.msg import Encoder, Baro, Imu, Cmd
from geometry_msgs.msg import Point32

import numpy as np


if __name__ == '__main__':
    rospy.init_node('pseudo_sensor')
    
    enc_pub_1 = rospy.Publisher('encoder_1', Encoder, queue_size=10)
    enc_pub_2 = rospy.Publisher('encoder_2', Encoder, queue_size=10)
    enc_pub_3 = rospy.Publisher('encoder_3', Encoder, queue_size=10)
    
    motor_pub_1 = rospy.Publisher('motor_1', Cmd, queue_size=10)
    motor_pub_2 = rospy.Publisher('motor_2', Cmd, queue_size=10)
    motor_pub_3 = rospy.Publisher('motor_3', Cmd, queue_size=10)
    

    encoder_msg_1 = Encoder()
    encoder_msg_2 = Encoder()
    encoder_msg_3 = Encoder()
    
    motor_msg_1 = Cmd()
    motor_msg_2 = Cmd()
    motor_msg_3 = Cmd()
    
    baro_pub = rospy.Publisher('barometer', Baro, queue_size=10)
    baro_msg = Baro()

    imu_pub = rospy.Publisher('imu', Imu, queue_size=10)
    imu_msg = Imu()
    
    pos_pub = rospy.Publisher('position', Point32, queue_size=10)
    pos_msg = Point32()

    rate = rospy.Rate(10)
    while not rospy.is_shutdown():
        t = rospy.get_time()
        
        motor_msg_1.mode = 2
        motor_msg_1.flipping_speed = 10*np.cos(t)
        motor_pub_1.publish(motor_msg_1)

        encoder_msg_1.encoder_angle = 10*np.sin(t)
        encoder_msg_1.encoder_speed = 10*np.cos(t+0.1)
        enc_pub_1.publish(encoder_msg_1)
        
        motor_msg_2.mode = 2
        motor_msg_2.flipping_speed = 20*np.cos(t)
        motor_pub_2.publish(motor_msg_2)
        
        encoder_msg_2.encoder_angle = 20*np.sin(t)
        encoder_msg_2.encoder_speed = 20*np.cos(t+0.1)
        enc_pub_2.publish(encoder_msg_2)
        
        motor_msg_3.mode = 2
        motor_msg_3.flipping_speed = 30*np.cos(t)
        motor_pub_3.publish(motor_msg_3)
        
        encoder_msg_3.encoder_angle = 30*np.sin(t)
        encoder_msg_3.encoder_speed = 30*np.cos(t+0.1)
        enc_pub_3.publish(encoder_msg_3)
        
        baro_msg.depth = 0.1*np.sin(t)
        baro_msg.temp = 24
        baro_pub.publish(baro_msg)
    
        imu_msg.roll = 10*np.sin(t)
        imu_msg.pitch = 10*np.sin(t+10)
        imu_msg.yaw = 10*np.sin(t+20)
        imu_pub.publish(imu_msg)
        
        pos_msg.x = 10*np.sin(t)
        pos_msg.y = 10*np.sin(t)
        pos_msg.z = 10*np.sin(t)
        pos_pub.publish(pos_msg)

        rate.sleep()
        

