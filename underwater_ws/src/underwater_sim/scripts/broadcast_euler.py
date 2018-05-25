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
    def listener(self, imu_msg):
        self.roll = imu_msg.roll
        self.pitch = imu_msg.pitch
        self.yaw = imu_msg.yaw
    
    def broadcast(self):
        roll = np.deg2rad(self.roll)
        pitch = np.deg2rad(self.pitch)
        yaw = np.deg2rad(self.yaw)

        br = tf2_ros.TransformBroadcaster()
        t = TransformStamped()


        t.header.stamp = rospy.Time.now()
        t.header.frame_id = "world"
        t.child_frame_id = "base_link"
        t.transform.translation.x = 0
        t.transform.translation.y = 0
        t.transform.translation.z = 0
        q = tf.transformations.quaternion_from_euler(roll , pitch, yaw)
        t.transform.rotation.x = q[0]
        t.transform.rotation.y = q[1]
        t.transform.rotation.z = q[2]
        t.transform.rotation.w = q[3]
        br.sendTransform(t)


if __name__ == '__main__':
    imu_broadcast = ImuBroadcast()
    rospy.init_node('imu_broadcast')
    rospy.Subscriber('imu', Imu, imu_broadcast.listener)
    rate = rospy.Rate(10)

    while not rospy.is_shutdown():
        imu_broadcast.broadcast()
        rate.sleep()




