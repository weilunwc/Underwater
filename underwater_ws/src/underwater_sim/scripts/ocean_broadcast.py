#!/usr/bin/env python

# ocean_broadcast.py -- sends the tf of world to ocean

import rospy
from geometry_msgs.msg import Point32, TransformStamped
import tf
import tf2_ros

import numpy as np

if __name__ == '__main__':
    rospy.init_node('ship_broadcast')
    x, y, z, roll, pitch, yaw = (0, 0, 0, 0, 0, 0)
     # set up transformation
    br = tf2_ros.TransformBroadcaster()
    t = TransformStamped()

    t.header.stamp = rospy.Time.now()
    t.header.frame_id = "world"
    t.child_frame_id = "ocean_base_link"
    t.transform.translation.x = x
    t.transform.translation.y = y
    t.transform.translation.z = z
    
    q = tf.transformations.quaternion_from_euler(roll , pitch, yaw)
    
    t.transform.rotation.x = q[0]
    t.transform.rotation.y = q[1]
    t.transform.rotation.z = q[2]
    t.transform.rotation.w = q[3]

    rate = rospy.Rate(1)

    while not rospy.is_shutdown():
        br.sendTransform(t)
        rate.sleep()




