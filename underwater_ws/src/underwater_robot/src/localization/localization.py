#!/usr/bin/env python

# This node is intended to collect the x,y,z position data from barometer and acoustic locator
# The depth data is collected by subscribing to the barometer on the arduino
# x,y location is collected through the acoustic system through ethernet


from __future__ import print_function

# ros libraries
import rospy
import rosbag


from std_msgs.msg import String
from std_msgs.msg import Float32
from std_msgs.msg import Int32
from geometry_msgs.msg import Point32
from underwater_robot.msg import Baro
from underwater_robot.msg import Euler


import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import random

import sys
import argparse
import requests
import argparse
import json
import time

from locator import Locator

class Localization:
    def __init__(self, url="http://192.168.2.94", external_depth=False, render=False, max_size=100):

        self.pos_pub = rospy.Publisher('position', Point32, queue_size=10) 
        self.position_data = Point32()
        self.position_data.x = 0
        self.position_data.y = 0
        self.position_data.z = 0

        self.orientation_data = Euler()
        self.orientation_data.roll = 0
        self.orientation_data.pitch = 0
        self.orientation_data.yaw = 0
           
        self.url = url
        self.external_depth = external_depth
        self.locator = Locator(url, external_depth) 
        self.render = render
        
        self.start = False

        if render:
            self.plot_traj()
        print("")
    
    def plot_traj(self):
        self.fig = plt.figure()
        self.ax = self.fig.add_subplot(111,projection='3d')
        self.x_data = []
        self.y_data = []
        self.z_data = []
        #self.ax([-10,10,-10,10,-10,10])
        self.ax.set_xlabel('x')
        self.ax.set_ylabel('y')
        self.ax.set_zlabel('z')
        self.ax.set_xlim(-10,10)
        self.ax.set_ylim(-10,10)
        self.ax.set_zlim(-10,10)
        plt.ion()
        plt.show()
        plt.title('trajectory')

    def baro_callback(self, baro_msg):
        # if we recieve info from barometer, send these info to local host 
        self.depth = baro_msg.depth
        self.temp = baro_msg.temp
        self.position_data.z = self.depth
        
        if self.external_depth == True:
            # Send depth to server
            self.locator.set_depth(self.depth, self.temp)
            self.start = True
    
    
    def euler_callback(self, euler_msg):
        self.orientation_data.roll = euler_msg.roll
        self.orientation_data.pitch = euler_msg.pitch
        self.orientation_data.yaw = euler_msg.yaw
    
    
    
    
    def position_publish(self):
        
        # If set external mode, will return error if did not set external depth
        if self.external_depth:
            while self.start == False:
                time.sleep(5)
                pass

        # get position info from the local host of the locator
        if self.external_depth == True: 
            self.position_data.x, self.position_data.y, self.position_data.z = self.locator.get_acoustic_position()
        else:
            self.position_data.x, self.position_data.y = self.locator.get_acoustic_position()
        
        self.pos_pub.publish(self.position_data)
        

        if self.render:
            self.x_data.append(self.position_data.x)
            self.y_data.append(self.position_data.y)
            self.z_data.append(self.position_data.z)
            self.draw()
        print(time.time())
        print(self.position_data.x, self.position_data.y, self.position_data.z)    
        print(self.orientation_data.roll, self.orientation_data.pitch, self.orientation_data.yaw)    
        
        #self.bag.write('position', self.position_data)
        #self.bag.write('imu', self.orientation_data)
    
    
    
    def draw(self):
        try:
            self.ax.lines.remove(self.lines[0])
        except Exception:
            pass
        self.lines = self.ax.plot(self.x_data, self.y_data, self.z_data, 'r')
        plt.pause(0.0001)


def parse_arguments(args):
    parser = argparse.ArgumentParser(description="Position collector for the robot")
    parser.add_argument("--render",type=bool,default=False)
    parser.add_argument("--url", help="base url to use", type=str,
            default="http://192.168.2.94")
    return parser.parse_args()

def main(args):
   
    # Read arguments and build the position class
    args = parse_arguments(args)
    #bag = rosbag.Bag('test.bag', 'w')
    render = args.render
    url = args.url
    external_depth = True
    localizer = Localization(url, external_depth)
    rospy.init_node("position", anonymous=False)
    rospy.Subscriber("barometer", Baro, localizer.baro_callback)
    rospy.Subscriber("imu", Euler, localizer.euler_callback)
    


    rate = rospy.Rate(4)
    
    while not rospy.is_shutdown():
        #rospy.loginfo(baro.depth)
        localizer.position_publish()
        rate.sleep()    
    
    #bag.close()


if __name__ == '__main__':
    main(sys.argv)




