#!/usr/bin/env python

import rospy

from std_msgs.msg import Float64
from math import sin,cos,atan2,sqrt,fabs

#Define a RRBot joint positions publisher for joint controllers.
def UGazebo_motor_effort_publisher():

	#Initiate node for controlling joint1 and joint2 positions.
	rospy.init_node('motor_effort_node', anonymous=True)

	#Define publishers for each joint position controller commands.
	pub1 = rospy.Publisher('/UGazebo/motor1_torque_controller/command', Float64, queue_size=10)
	pub2 = rospy.Publisher('/UGazebo/motor2_torque_controller/command', Float64, queue_size=10)
	pub3 = rospy.Publisher('/UGazebo/motor3_torque_controller/command', Float64, queue_size=10)
	print("hello")

	rate = rospy.Rate(100) #100 Hz

	#While loop to have joints follow a certain position, while rospy is not shutdown.
	i = 0
	while not rospy.is_shutdown():
		#print("hello")
		#Have each joint follow a sine movement of sin(i/100).
		sine_movement = sin(i/100.)

		#Publish the same sine movement to each joint.
		pub1.publish(10*sine_movement)
		pub2.publish(10*sine_movement)
		pub3.publish(10*sine_movement)

		i = i+1 #increment i
 
		rate.sleep() #sleep for rest of rospy.Rate(100)

#Main section of code that will continuously run unless rospy receives interuption (ie CTRL+C)
if __name__ == '__main__':
	try: UGazebo_motor_effort_publisher()
	except rospy.ROSInterruptException: pass