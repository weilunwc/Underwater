#include <iostream>

#include "ros/ros.h"
#include "std_msgs/Int16.h"
#include "sensor_msgs/Joy.h"

using namespace std;


/* functions */
void read_joystick(const sensor_msgs::Joy &joyInfo);
/* global variables */
std_msgs::Int16 usb0_speed,usb1_speed,usb2_speed,usb3_speed;


int main(int argc, char **argv){
	/* Initialize global variables */		
	usb0_speed.data = 0;
	usb1_speed.data = 0;
	usb2_speed.data = 0;
	usb3_speed.data = 0;

	/* Initialize the node */
	ros::init(argc, argv, "check_usb");

	ros::NodeHandle n;
	
	/* Publish control commands */
	ros::Publisher usb0_pub = n.advertise<std_msgs::Int16>("usb0", 1000);
	ros::Publisher usb1_pub = n.advertise<std_msgs::Int16>("usb1", 1000);	
	ros::Publisher usb2_pub = n.advertise<std_msgs::Int16>("usb2", 1000);	
	ros::Publisher usb3_pub = n.advertise<std_msgs::Int16>("usb3", 1000);	
	

	/* Subscribe to sensor and state information */
	ros::Subscriber joy_sub = n.subscribe("joy", 1000, read_joystick);
	/* Set up frequency */
	ros::Rate loop_rate(10);
	


	while(ros::ok()){
	

		
		usb0_pub.publish(usb0_speed);
		usb1_pub.publish(usb1_speed);		
		usb2_pub.publish(usb2_speed);		
		usb3_pub.publish(usb3_speed);		
		
		//ROS_INFO("center speed: %d", center_speed.data);	
		//ROS_INFO("depth: %lf", depth);	
		
		ros::spinOnce();
		loop_rate.sleep();
		
	}
	
	
	return 0;
}

/* move motor based on joystick command to check the usb corrsespondence */
void read_joystick(const sensor_msgs::Joy &joyInfo){
	ROS_INFO("%d,%d,%d,%d",joyInfo.buttons[0],joyInfo.buttons[1],
											   joyInfo.buttons[2],joyInfo.buttons[3]);
	bool usb_command_0,usb_command_1,usb_command_2,usb_command_3;
	usb_command_0 = joyInfo.buttons[0];
	usb_command_1 = joyInfo.buttons[1];
	usb_command_2 = joyInfo.buttons[2];
	usb_command_3 = joyInfo.buttons[3];
	int speed = 30;

	if(usb_command_0)usb0_speed.data = speed;
	else usb0_speed.data = 0;

	if(usb_command_1)usb1_speed.data = speed;
	else usb1_speed.data = 0;
	
	if(usb_command_2)usb2_speed.data = speed;
	else usb2_speed.data = 0;
	
	if(usb_command_3)usb3_speed.data = speed;
	else usb3_speed.data = 0;
	
	
}









