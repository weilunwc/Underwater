#!/usr/bin/env python

import rospy
from sensor_msgs.msg import Joy
import numpy as np

def inverse_dynamics(sita):
    sita = np.deg2rad(sita)
    l = 10.0    
    A = np.array([[-2.0/3.0, 0, 1.0/(3.0*l)],
        [1.0/3.0, -np.sqrt(3)/3.0, 1.0/(3.0*l)],
        [1.0/3.0, np.sqrt(3)/3.0, 1.0/(3.0*l)]])
    
    Fx = np.cos(sita)
    Fy = np.sin(sita)
    T = 0
    X = np.array([Fx, Fy, T]).reshape(3,1)
    print(X)

    Force = np.matmul(A ,X)
    print(Force)
    
    return Force    



class Planar:
    def __init__(self):
        self.x = 0.0
        self.y = 0.0
        self.sita = 0.0
        self.r = 0.0
        pass
    def joy_callback(self,joy_msg):
        self.x = -joy_msg.axes[0]
        self.y = joy_msg.axes[1]
        self.r = np.sqrt(self.x**2 + self.y**2)
        self.sita = np.rad2deg(np.arctan2(self.y, self.x))
 
        pass
    def print_joy(self):
        print(self.x, self.y, self.r, self.sita)

if __name__ == '__main__':
    
    planar = Planar()

    rospy.init_node('planar_direction')
    rospy.Subscriber('joy', Joy, planar.joy_callback)
    
    rate = rospy.Rate(10)
    while not rospy.is_shutdown():
        #test.print_joy()
        if planar.r > 0.5:
            Force = inverse_dynamics(planar.sita)
        rate.sleep()
    
