#!/usr/bin/env python
# Spawn the robot controller
import rospy
import subprocess

if __name__ == '__main__':
    rospy.init_node("controller_spawner")
    controller_launch = rospy.get_param("controller", "joystick_control")
    controller_launch += ".launch"

    controller = subprocess.Popen(["roslaunch", "underwater_robot", "joystick_control.launch"]) 

