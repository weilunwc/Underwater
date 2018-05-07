#!/usr/bin/env python

# This libarary is for configuring the localization information. By setting up which sensors we are
# subscribing to, and then processing the data

# The sensors we have include IMU, Barometer, Encoder and an acoustic locator.

# Position is intended to be collected by barometer and acoustic locator
# The depth data is collected by subscribing to the barometer on the arduino
# x,y location is collected through the acoustic system through ethernet


from __future__ import print_function

# ros libraries
import rospy
import rosbag


from geometry_msgs.msg import Point32
from underwater_robot.msg import Baro
from underwater_robot.msg import Euler
from underwater_robot.msg import Encoder

import time

from Locator import Locator

class Sensor:
    def __init__(self):
        
        self.external_depth = False 
        
        # State variables
        self.position = Point32()
        self.orientation = Euler()
        
        # Sensor variables
        self.encoder1 = Encoder()
        self.encoder2 = Encoder()
        self.encoder3 = Encoder()
        self.baro = Baro()
        
    
    def subscribe_imu(self):
        rospy.Subscriber("imu", Euler, self.imu_callback)

    def imu_callback(self, imu_msg):
        self.orientation.roll = imu_msg.roll
        self.orientation.pitch = imu_msg.pitch
        self.orientation.yaw = imu_msg.yaw
        

    def subscribe_baro(self):
        rospy.Subscriber("barometer", Baro, self.baro_callback)
    
    def baro_callback(self, baro_msg):
        # if we recieve info from barometer, send these info to local host 
        self.baro.depth = baro_msg.depth
        self.baro.temp = baro_msg.temp
        self.position.z = self.baro.depth
        
        if self.external_depth == True:
            # Send depth to server
            self.locator.set_depth(self.baro.depth, self.baro.temp)


    def subsrcibe_encoder(self):
        rospy.Subscriber("encoder1", Encoder, self.encoder1_callback)
        rospy.Subscriber("encoder2", Encoder, self.encoder2_callback)
        rospy.Subscriber("encoder3", Encoder, self.encoder3_callback)
    
    def encoder1_callback(self, encoder_msg):
        self.encoder1.encoder_angle = encoder_msg.encoder_angle
        self.encoder1.encoder_speed = encoder_msg.encoder_speed
    
    def encoder2_callback(self, encoder_msg):
        self.encoder2.encoder_angle = encoder_msg.encoder_angle
        self.encoder2.encoder_speed = encoder_msg.encoder_speed
    
    def encoder3_callback(self, encoder_msg):
        self.encoder3.encoder_angle = encoder_msg.encoder_angle
        self.encoder3.encoder_speed = encoder_msg.encoder_speed

    
    def subscribe_locator(self, url="http://192.168.2.94", external_depth=False):
        self.url = url
        self.external_depth = external_depth
        self.locator = Locator(self.url, self.external_depth)
        
        if external_depth:
            # Set up the locator's external depth and wait for it to config
            self.locator.set_depth(self.baro.depth, self.baro.temp)
            time.sleep(5)
   
    
    def setup_position_publisher(self):
        self.pos_pub = rospy.Publisher("position", Point32, queue_size=10) 

    def publish_position(self):
        
        # get position info from the local host of the locator
        if self.external_depth == True: 
            self.position.x, self.position.y, self.position.z = self.locator.get_acoustic_position()
        else:
            self.position.x, self.position.y = self.locator.get_acoustic_position()
        
        self.pos_pub.publish(self.position)
        

    def setup_orientation_publisher(self):
        self.orient_pub = rospy.Publisher("orientation", Euler, queue_size=10)

    def publish_orientation(self):
        self.orient_pub.publish(self.orientation)

