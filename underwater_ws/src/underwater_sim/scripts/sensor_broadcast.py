#!/usr/bin/env python

"""
sensor_broadcast.py -- this python script collects the sensor topics and broadcasts
                       to rviz in real time. 
"""

import rospy
from geometry_msgs.msg import TransformStamped, Quaternion, Point32
import tf
import tf2_ros

from sensor_msgs.msg import JointState
from underwater_msgs.msg import Imu, Encoder
import numpy as np


class SensorBroadcast:
    def __init__(self, imu_version='quaternion'):
        if imu_version == 'euler':
            self.imu_broadcast = EulerBroadcast()
        else:
            self.imu_broadcast = QuaternionBroadcast()
        
        self.encoder_broadcast = EncoderBroadcast() 
        self.position_broadcast = PositionBroadcast()


    def broadcast(self):
        # Send joint states of motors
        self.encoder_broadcast.broadcast()
        
        # Get quaternions values from imu
        q = self.imu_broadcast.quaternion()
        
        # Get position
        p = self.position_broadcast.position()

        # Broad cast base link pose to rviz 
        br = tf2_ros.TransformBroadcaster()
        t = TransformStamped()
    
        t.header.stamp = rospy.Time.now()
        t.header.frame_id = "world"
        t.child_frame_id = "robot_base_link"
        t.transform.translation.x = p.x
        t.transform.translation.y = p.y
        t.transform.translation.z = p.z
        
        t.transform.rotation.x = q.x
        t.transform.rotation.y = q.y
        t.transform.rotation.z = q.z
        t.transform.rotation.w = q.w
        br.sendTransform(t)

        pass

class PositionBroadcast:
    def __init__(self):
        self.pos = Point32() 
        self.sub = rospy.Subscriber('position', Point32, self.position_sub)
    
    def position_sub(self, msg):
        self.pos.x = msg.x
        self.pos.z = msg.z
        self.pos.y = msg.y
    
    def position(self):
        return self.pos


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
        # Broadcasts the joint values to joint state publisher
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


class EulerBroadcast:
    def __init__(self):
        self.roll = 0
        self.pitch = 0
        self.yaw = 0

        rospy.Subscriber('imu', Imu, self.listener)

    def listener(self, imu_msg):
        self.roll = imu_msg.roll
        self.pitch = imu_msg.pitch
        self.yaw = imu_msg.yaw
    
    def quaternion(self):
        # Transform the euler angles to radians
        roll = np.deg2rad(self.roll)
        pitch = np.deg2rad(self.pitch)
        yaw = np.deg2rad(self.yaw)
        
        q = tf.transformations.quaternion_from_euler(roll , pitch, yaw)

        quat = Quaternion()
        quat.x = q[0]
        quat.y = q[1]
        quat.z = q[2]
        quat.w = q[3]
        return quat


class QuaternionBroadcast:
    def __init__(self):
        self.quat = Quaternion()
        q = tf.transformations.quaternion_from_euler(0, 0, 0)
        self.quat.x = q[0]
        self.quat.y = q[1]
        self.quat.z = q[2]
        self.quat.w = q[3]
        
        rospy.Subscriber('imu', Quaternion, self.listener)    

    def listener(self, msg):
        
        # note that the imu yaw should be adjusted 120 degrees
        q_rot = tf.transformations.quaternion_from_euler(0, 0, np.deg2rad(120))
        
        q_imu = np.arange(4, dtype=float)
        q_imu[0] = msg.x
        q_imu[1] = msg.y
        q_imu[2] = msg.z
        q_imu[3] = msg.w
        
        q_new = tf.transformations.quaternion_multiply(q_rot, q_imu)
        print(q_new)
        print(q_imu)
        #q_new = q_imu
        self.quat.x = q_new[0]
        self.quat.y = q_new[1]
        self.quat.z = q_new[2]
        self.quat.w = q_new[3]


    def quaternion(self):
        return self.quat

if __name__ == '__main__':
    sensor_broadcast = SensorBroadcast('quaternion')
    rospy.init_node('sensor_broadcast')
    #rospy.Subscriber('imu', Imu, imu_broadcast.listener)
    rate = rospy.Rate(100)

    while not rospy.is_shutdown():
        sensor_broadcast.broadcast()
        rate.sleep()




