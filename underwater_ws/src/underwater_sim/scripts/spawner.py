#!/usr/bin/env python
# Spawn the rviz model
import rospy
import subprocess

if __name__ == '__main__':
    rospy.init_node("world_spawner")

    robot_position = rospy.get_param("robot/position")
    # Load pose from parameter server
    x = robot_position['x']
    y = robot_position['y']
    z = robot_position['z']

    robot_child = subprocess.Popen(["roslaunch", "underwater_sim", "robot_gazebo.launch", \
            "x:=" + str(x), "y:=" + str(y), "z:=" + str(z)]) 


    ship_position = rospy.get_param("ship/position")
    # Load pose from parameter server
    x = ship_position['x']
    y = ship_position['y']
    z = ship_position['z']

    ship_child = subprocess.Popen(["roslaunch", "underwater_sim", "ship_gazebo.launch", \
            "x:=" + str(x), "y:=" + str(y), "z:=" + str(z)]) 
