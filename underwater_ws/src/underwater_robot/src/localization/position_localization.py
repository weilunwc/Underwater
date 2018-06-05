#!/usr/bin/env python

# This node is intended to collect the x,y,z position data from barometer and acoustic locator
# The depth data is collected by subscribing to the barometer on the arduino
# x,y location is collected through the acoustic system through ethernet

from __future__ import print_function

# ros libraries
import rospy

from geometry_msgs.msg import Point32
from underwater_msgs.msg import Baro

import numpy as np
import random

import sys
import requests
import json
import time

from Locator import Locator

class Localization:
    def __init__(self, url="http://192.168.2.94", external_depth=True):

        self.pos_pub = rospy.Publisher('position', Point32, queue_size=10) 
        self.position_data = Point32()
        self.position_data.x = 0
        self.position_data.y = 0
        self.position_data.z = 0

        self.url = url
        self.external_depth = external_depth
        self.locator = Locator(url, external_depth) 
        
        self.start = False

    def baro_callback(self, baro_msg):
        # if we recieve info from barometer, send these info to local host 
        self.depth = baro_msg.depth
        self.temp = baro_msg.temp
        self.position_data.z = self.depth
        
        if self.external_depth == True:
            # Send depth to server
            self.locator.set_depth(self.depth, self.temp)
    
    def position_publish(self):
        
        # get position info from the local host of the locator
        if self.external_depth == True: 
            try:
                self.position_data.x, self.position_data.y, self.position_data.z = self.locator.get_3d_acoustic_position()
            except:
                print("server error")
        else:
            try:
                self.position_data.x, self.position_data.y = self.locator.get_2d_acoustic_position()
            except:
                print("server error")
        
        self.pos_pub.publish(self.position_data)

        

def main(args):
   
    # Read arguments and build the position class
    try:
        url = rospy.get_param("url")
    except:
        url = "http://192.168.2.94"
    
    try:
        external_depth = rospy.get_param("external_depth")
    except:
        external_depth = True

    localizer = Localization(url, external_depth)
    rospy.init_node("position_localization", anonymous=False)
    rospy.Subscriber("barometer", Baro, localizer.baro_callback)

    rate = rospy.Rate(100)
    
    while not rospy.is_shutdown():
        localizer.position_publish()
        rate.sleep()    

if __name__ == '__main__':
    main(sys.argv)

