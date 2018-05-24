#!/usr/bin/env python

import rospy
from geometry_msgs.msg import TransformStamped, Quaternion
import tf
import tf2_ros

from underwater_msg.msg import Imu
import numpy as np


class ImuBroadcast:
    def __init__(self):
        self.roll = 0
        self.pitch = 0
        self.yaw = 0
        self.quat = Quaternion()
    def listener(self, q):
        br = tf2_ros.TransformBroadcaster()
        t = TransformStamped()
    
        t.header.stamp = rospy.Time.now()
        t.header.frame_id = "world"
        t.child_frame_id = "base_link"
        t.transform.translation.x = 0
        t.transform.translation.y = 0
        t.transform.translation.z = 0
        #q = tf.transformations.quaternion_from_euler(self.roll , self.pitch, self.yaw)
        t.transform.rotation.x = q.x
        t.transform.rotation.y = q.y
        t.transform.rotation.z = q.z
        t.transform.rotation.w = q.w
        br.sendTransform(t)
        quat = np.array([q.x, q.y, q.z, q.w])
        euler = tf.transformations.euler_from_quaternion(quat)
        print(np.rad2deg(euler))


if __name__ == '__main__':
    imu_broadcast = ImuBroadcast()
    rospy.init_node('imu_broadcast')
    #rospy.Subscriber('imu', Imu, imu_broadcast.listener)
    rospy.Subscriber('imu', Quaternion, imu_broadcast.listener)
    rospy.spin() 
