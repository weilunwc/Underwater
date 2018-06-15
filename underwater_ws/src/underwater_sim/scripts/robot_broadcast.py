#!/usr/bin/env python

# robot_broadcast.py -- sends the tf of world to robot

import rospy
from geometry_msgs.msg import Point32, TransformStamped
import tf
import tf2_ros

import numpy as np

if __name__ == '__main__':
    rospy.init_node("robot_broadcast")
    
    # Load pose from parameter server
    try:
        position = rospy.get_param("position")
    except:
        position = {'x':0, 'y':0, 'z':0}
    
    try:
        orientation = rospy.get_param("orientation")
    except:
        orientation = {'roll':0, 'pitch':0, 'yaw':0}
    # Load pose from parameter server
    x = position['x']
    y = position['y']
    z = position['z']

    roll = orientation['roll']
    pitch = orientation['pitch']
    yaw = orientation['yaw']
     # set up transformation
    br = tf2_ros.TransformBroadcaster()
    t = TransformStamped()

    t.header.stamp = rospy.Time.now()
    t.header.frame_id = "usb_cam"
    t.child_frame_id = "robot_base_link"
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




