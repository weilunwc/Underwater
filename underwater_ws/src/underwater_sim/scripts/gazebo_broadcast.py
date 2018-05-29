#!/usr/bin/env python

# gazebo_broadcast.py -- sends the tf from gazebo world to rviz

import rospy
from geometry_msgs.msg import Point, Quaternion, Pose, TransformStamped
from gazebo_msgs.msg import ModelStates
import tf
import tf2_ros

import numpy as np


class GazeboBroadcast:
    def __init__(self):
        self.robot_pose = Pose()
        pass

    def listener(self, msg):
        robot_index = msg.name.index("underwater")
        self.robot_pose = msg.pose[robot_index] 
    
    def broadcast(self):
        # set up transformation
        br = tf2_ros.TransformBroadcaster()
        t = TransformStamped()
        
        p = self.robot_pose.position
        q = self.robot_pose.orientation
    
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


if __name__ == '__main__':
    gz_broad = GazeboBroadcast()

    rospy.init_node("gazebo_broadcast")

    sub = rospy.Subscriber("gazebo/model_states", ModelStates, gz_broad.listener)
    """
    position = rospy.get_param("position")
    orientation = rospy.get_param("orientation")
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
    t.header.frame_id = "world"
    t.child_frame_id = "robot_base_link"
    t.transform.translation.x = x
    t.transform.translation.y = y
    t.transform.translation.z = z
    
    q = tf.transformations.quaternion_from_euler(roll , pitch, yaw)
    
    t.transform.rotation.x = q[0]
    t.transform.rotation.y = q[1]
    t.transform.rotation.z = q[2]
    t.transform.rotation.w = q[3]
    """
    rate = rospy.Rate(10)
    while not rospy.is_shutdown():
        gz_broad.broadcast() 
        
        rate.sleep()


