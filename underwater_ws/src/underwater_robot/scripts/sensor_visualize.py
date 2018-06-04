#!/usr/bin/env python
# Visualize the sensor information
# Topics include Imu, Barometer, Locator and Encoder

import rospy
from underwater_msgs.msg import Encoder, Baro, Imu, Cmd
from geometry_msgs.msg import Point32

from collections import deque
import matplotlib.pyplot as plt
import numpy as np


class EncoderListen():
    def __init__(self, max_size=100):
        rospy.Subscriber('encoder_1', Encoder, self.encoder_1_callback)
        rospy.Subscriber('encoder_2', Encoder, self.encoder_2_callback)
        rospy.Subscriber('encoder_3', Encoder, self.encoder_3_callback)
        rospy.Subscriber('motor_1', Cmd, self.motor_1_callback)
        rospy.Subscriber('motor_2', Cmd, self.motor_2_callback)
        rospy.Subscriber('motor_3', Cmd, self.motor_3_callback)

        self.max_size = max_size
        self.encoder_angle_1 = deque(np.zeros(max_size), maxlen=max_size)
        self.encoder_speed_1 = deque(np.zeros(max_size), maxlen=max_size)
        
        self.encoder_angle_2 = deque(np.zeros(max_size), maxlen=max_size)
        self.encoder_speed_2 = deque(np.zeros(max_size), maxlen=max_size)
        
        self.encoder_angle_3 = deque(np.zeros(max_size), maxlen=max_size)
        self.encoder_speed_3 = deque(np.zeros(max_size), maxlen=max_size)


        self.motor_speed_1 = deque(np.zeros(max_size), maxlen=max_size)
        self.motor_speed_2 = deque(np.zeros(max_size), maxlen=max_size)
        self.motor_speed_3 = deque(np.zeros(max_size), maxlen=max_size)
        
        self.mode = 0

        self.fig = plt.figure()
        self.fig.suptitle('Encoder')        
        self.ax1_1 = self.fig.add_subplot(2,3,1)
        self.ax1_1.grid()
        plt.title('Encoder1 Angle (deg)')
        plt.ylim((-200,200))

        self.ax2_1 = self.fig.add_subplot(2,3,4)
        self.ax2_1.grid()
        plt.title('Encoder1 Speed (rpm)')
        plt.ylim((-350,350))
        
        self.ax1_2 = self.fig.add_subplot(2,3,2)
        self.ax1_2.grid()
        plt.title('Encoder2 Angle (deg)')
        plt.ylim((-200,200))
        
        self.ax2_2 = self.fig.add_subplot(2,3,5)
        self.ax2_2.grid()
        plt.title('Encoder2 Speed (rpm)')
        plt.ylim((-350,350))
        
        self.ax1_3 = self.fig.add_subplot(2,3,3)
        self.ax1_3.grid()
        plt.title('Encoder3 Angle (deg)')
        plt.ylim((-200,200))
        
        self.ax2_3 = self.fig.add_subplot(2,3,6)
        self.ax2_3.grid()
        plt.title('Encoder3 Speed (rpm)')
        plt.ylim((-350,350))
        
        plt.ion()
        plt.show()

    def encoder_1_callback(self, encoder_msg):
        self.encoder_angle_1.append(encoder_msg.encoder_angle)
        if self.mode == 2:
            # Flipping
            self.encoder_speed_1.append(abs(encoder_msg.encoder_speed))
        else:
            self.encoder_speed_1.append(encoder_msg.encoder_speed)
    
    def encoder_2_callback(self, encoder_msg):
        self.encoder_angle_2.append(encoder_msg.encoder_angle)
        if self.mode == 2:
            # Flipping
            self.encoder_speed_2.append(abs(encoder_msg.encoder_speed))
        else:
            self.encoder_speed_2.append(encoder_msg.encoder_speed)
    
    def encoder_3_callback(self, encoder_msg):
        self.encoder_angle_3.append(encoder_msg.encoder_angle)
        if self.mode == 2:
            # Flipping
            self.encoder_speed_3.append(abs(encoder_msg.encoder_speed))
        else:
            self.encoder_speed_3.append(encoder_msg.encoder_speed)
    
    def motor_1_callback(self, cmd_msg):
        self.mode = cmd_msg.mode
        mode = self.mode
        if mode == 0:
            speed = 0
        elif mode == 1:
            speed = cmd_msg.spinning_speed
        elif mode == 2:
            speed = cmd_msg.flipping_speed
        else:
            speed = 0
        self.motor_speed_1.append(speed)
    
    def motor_2_callback(self, cmd_msg):
        self.mode = cmd_msg.mode
        mode = self.mode
        if mode == 0:
            speed = 0
        elif mode == 1:
            speed = cmd_msg.spinning_speed
        elif mode == 2:
            speed = cmd_msg.flipping_speed
        else:
            speed = 0
        self.motor_speed_2.append(speed)

    def motor_3_callback(self, cmd_msg):
        self.mode = cmd_msg.mode
        mode = self.mode
        if mode == 0:
            speed = 0
        elif mode == 1:
            speed = cmd_msg.spinning_speed
        elif mode == 2:
            speed = cmd_msg.flipping_speed
        else:
            speed = 0
        self.motor_speed_3.append(speed)
    
    def draw(self):
        try:
            self.ax1_1.lines.remove(self.lines1_1[0])
            self.ax2_1.lines.remove(self.lines2_1[0])
            
            self.ax1_2.lines.remove(self.lines1_2[0])
            self.ax2_2.lines.remove(self.lines2_2[0])
            
            self.ax1_3.lines.remove(self.lines1_3[0])
            self.ax2_3.lines.remove(self.lines2_3[0])
            

            # Command reference
            self.ax2_1.lines.remove(self.lines2_1_cmd[0])
            
            self.ax2_2.lines.remove(self.lines2_2_cmd[0])
            
            self.ax2_3.lines.remove(self.lines2_3_cmd[0])
        
        except Exception:
            pass
        
        self.lines1_1 = self.ax1_1.plot(self.encoder_angle_1, 'r-')
        self.lines2_1 = self.ax2_1.plot(self.encoder_speed_1, 'r-', label='real')
        self.lines2_1_cmd = self.ax2_1.plot(self.motor_speed_1, 'b-', label='ref') 

        self.lines1_2 = self.ax1_2.plot(self.encoder_angle_2, 'r-')
        self.lines2_2 = self.ax2_2.plot(self.encoder_speed_2, 'r-', label='real')
        self.lines2_2_cmd = self.ax2_2.plot(self.motor_speed_2, 'b-', label='ref') 
        
        self.lines1_3 = self.ax1_3.plot(self.encoder_angle_3, 'r-')
        self.lines2_3 = self.ax2_3.plot(self.encoder_speed_3, 'r-', label='real')
        self.lines2_3_cmd = self.ax2_3.plot(self.motor_speed_3, 'b-', label='ref') 
        self.ax2_3.legend(loc='center left', bbox_to_anchor=(1, 0.5))       
        plt.pause(0.00001)

class BaroListen():
    def __init__(self, max_size=100):
        rospy.Subscriber('barometer', Baro, self.baro_callback)
        
        self.max_size = max_size
        self.depth_data = deque(np.zeros(max_size), maxlen=max_size)  
        
        self.fig = plt.figure()
        self.fig.suptitle('Barometer')        
        
        self.ax = self.fig.add_subplot(111)
        self.ax.grid()
        plt.title('Baro depth')
        plt.ion()
        plt.show()


    def baro_callback(self, baro_msg):
        self.depth_data.append(baro_msg.depth)
    
    def draw(self):
        try:
            self.ax.lines.remove(self.lines[0])
            
        except Exception:
            pass
        
        self.lines = self.ax.plot(self.depth_data, 'r-')

        plt.pause(0.00001)


class ImuListen():
    def __init__(self, max_size=100):
        rospy.Subscriber('imu', Imu, self.imu_callback)
        
        self.max_size = max_size
        self.roll_data = deque(np.zeros(max_size), maxlen=max_size)  
        self.pitch_data = deque(np.zeros(max_size), maxlen=max_size)  
        self.yaw_data = deque(np.zeros(max_size), maxlen=max_size)  
        
        self.fig = plt.figure()
        self.fig.suptitle('Imu')        
        
        self.ax1 = self.fig.add_subplot(311)
        self.ax1.grid()
        plt.title('Roll')
        plt.ylim((-350,350))
        
        self.ax2 = self.fig.add_subplot(312)
        self.ax2.grid()
        plt.title('Pitch')
        plt.ylim((-350,350))
        
        self.ax3 = self.fig.add_subplot(313)
        self.ax3.grid()
        plt.title('Yaw')
        plt.ylim((-350,350))
        
        plt.ion()
        plt.show()


    def imu_callback(self, imu_msg):
        self.roll_data.append(imu_msg.roll)
        self.pitch_data.append(imu_msg.pitch)
        self.yaw_data.append(imu_msg.yaw)
    
    def draw(self):
        try:
            self.ax1.lines.remove(self.lines1[0])
            self.ax2.lines.remove(self.lines2[0])
            self.ax3.lines.remove(self.lines3[0])
            
        except Exception:
            pass
        
        self.lines1 = self.ax1.plot(self.roll_data, 'r-')
        self.lines2 = self.ax2.plot(self.pitch_data, 'r-')
        self.lines3 = self.ax3.plot(self.yaw_data, 'r-')

        plt.pause(0.00001)

class PosListen():
    def __init__(self, max_size=100):
        rospy.Subscriber('position', Point32, self.pos_callback)
        
        self.max_size = max_size
        self.x_data = deque(np.zeros(max_size), maxlen=max_size)  
        self.y_data = deque(np.zeros(max_size), maxlen=max_size)  
        self.z_data = deque(np.zeros(max_size), maxlen=max_size)  
        
        self.fig = plt.figure()
        self.fig.suptitle('Position')        
        
        self.ax1 = self.fig.add_subplot(311)
        self.ax1.grid()
        plt.title('X')
        
        self.ax2 = self.fig.add_subplot(312)
        self.ax2.grid()
        plt.title('Y')
        
        self.ax3 = self.fig.add_subplot(313)
        self.ax3.grid()
        plt.title('Z')
        
        plt.ion()
        plt.show()


    def pos_callback(self, pos_msg):
        self.x_data.append(pos_msg.x)
        self.y_data.append(pos_msg.y)
        self.z_data.append(pos_msg.z)
    
    def draw(self):
        try:
            self.ax1.lines.remove(self.lines1[0])
            self.ax2.lines.remove(self.lines2[0])
            self.ax3.lines.remove(self.lines3[0])
            
        except Exception:
            pass
        
        self.lines1 = self.ax1.plot(self.x_data, 'r-')
        self.lines2 = self.ax2.plot(self.y_data, 'r-')
        self.lines3 = self.ax3.plot(self.z_data, 'r-')

        plt.pause(0.00001)




if __name__ == '__main__':

    rospy.init_node('sensor_visulize')
    
    # Encoder Imu Barometer Position
    configs = rospy.get_param('visual_configs')
    
    if configs['Encoder'] is True:
        enc = EncoderListen()
    if configs['Barometer'] is True:
        baro = BaroListen()
    if configs['Imu'] is True: 
        imu = ImuListen()
    if configs['Position'] is True:
        pos = PosListen()
    
    rate = rospy.Rate(100)
    while not rospy.is_shutdown():
        if configs['Encoder'] is True:
            enc.draw()
        if configs['Barometer'] is True:
            baro.draw()
        if configs['Imu'] is True: 
            imu.draw()
        if configs['Position'] is True:
            pos.draw()
        
        rate.sleep() 


