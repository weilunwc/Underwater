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
        q = tf.transformations.quaternion_from_euler(0, 0, 0)
        self.robot_pose.orientation.x = q[0]
        self.robot_pose.orientation.y = q[1]
        self.robot_pose.orientation.z = q[2]
        self.robot_pose.orientation.w = q[3]
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
    rate = rospy.Rate(100)
    while not rospy.is_shutdown():
        gz_broad.broadcast() 
        rate.sleep()


