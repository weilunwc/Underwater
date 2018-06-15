#!/usr/bin/env python

# ship_broadcast.py -- sends the tf of world to ship

import rospy
from ar_track_alvar_msgs.msg import AlvarMarkers
from geometry_msgs.msg import Point32, TransformStamped, Point, Quaternion
import tf
import tf2_ros

import numpy as np


class PositionBroadcast:
    def __init__(self):
        self.pos = Point()
        self.quat = Quaternion()
        self.quat.w = 1
        self.sub = rospy.Subscriber('ar_pose_marker', AlvarMarkers, 
                                    self.position_sub)

    def position_sub(self, msg, i=0):
        try:
            self.pos.x = msg.markers[i].pose.pose.position.x
            self.pos.y = msg.markers[i].pose.pose.position.y
            self.pos.z = msg.markers[i].pose.pose.position.z

            print('x', self.pos.x)
            print('y', self.pos.y)
            print('z', self.pos.z)
            print('##########################')

            self.quat.x = msg.markers[i].pose.pose.orientation.x
            self.quat.y = msg.markers[i].pose.pose.orientation.y
            self.quat.z = msg.markers[i].pose.pose.orientation.z
            self.quat.w = msg.markers[i].pose.pose.orientation.w

            print('Qx', self.quat.x)
            print('Qy', self.quat.y)
            print('Qz', self.quat.z)
            print('Qw', self.quat.w)
            print('##########################')
        except:
            pass
    
    def broadcast(self):
        br = tf2_ros.TransformBroadcaster()
        t = TransformStamped()

        t.header.stamp = rospy.Time.now()
        t.header.frame_id = "usb_cam"
        t.child_frame_id = "ship_base_link"
        t.transform.translation.x = self.pos.x
        t.transform.translation.y = self.pos.y
        t.transform.translation.z = self.pos.z
        
        t.transform.rotation.x = self.quat.x
        t.transform.rotation.y = self.quat.y
        t.transform.rotation.z = self.quat.z
        t.transform.rotation.w = self.quat.w
        br.sendTransform(t)
        pass

if __name__ == '__main__':
    position_br = PositionBroadcast()
    rospy.init_node('ship_broadcast')
    
    # Load pose from parameter server


    rate = rospy.Rate(10)

    while not rospy.is_shutdown():
        position_br.broadcast()
        rate.sleep()




