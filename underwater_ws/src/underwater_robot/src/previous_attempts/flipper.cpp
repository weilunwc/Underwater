#include <iostream>

#include "ros/ros.h"
#include "std_msgs/Int16.h"
#include "sensor_msgs/Joy.h"

using namespace std;


/* functions */
void read_joystick(const sensor_msgs::Joy &joyInfo);
/* global variables */
std_msgs::Int16 motor_1_angle,motor_2_angle,motor_3_angle;

int mode;


int main(int argc, char **argv){
	/* Initialize global variables */		
	mode = 100;
	motor_1_angle.data = 0;
	motor_2_angle.data = 0;
	motor_3_angle.data = 0;


	/* Initialize the node */
	ros::init(argc, argv, "joystick_control");

	ros::NodeHandle n;
	
	/* Publish control commands */
	ros::Publisher motor_1_pub = n.advertise<std_msgs::Int16>("motor_1", 1000);	
	ros::Publisher motor_2_pub = n.advertise<std_msgs::Int16>("motor_2", 1000);	
	ros::Publisher motor_3_pub = n.advertise<std_msgs::Int16>("motor_3", 1000);	
	

	/* Subscribe to sensor and state information */
	ros::Subscriber joy_sub = n.subscribe("joy", 1000, read_joystick);
	/* Set up frequency */
	ros::Rate loop_rate(10);
	
	/* 
	 * message type explained 
	 * center_motor: Int16 angle
	 * motor_x: Point32 mode, angle, angle
	 */


	while(ros::ok()){
	

		
		motor_1_pub.publish(motor_1_angle);		
		motor_2_pub.publish(motor_2_angle);		
		motor_3_pub.publish(motor_3_angle);		
		
		//ROS_INFO("center angle: %d", center_angle.data);	
		//ROS_INFO("depth: %lf", depth);	
		
		ros::spinOnce();
		loop_rate.sleep();
		
	}
	
	
	return 0;
}


void read_joystick(const sensor_msgs::Joy &joyInfo){
	//ROS_INFO("%d,%d,%d,%d",joyInfo.buttons[0],joyInfo.buttons[1],
	//										   joyInfo.buttons[2],joyInfo.buttons[3]);
	bool motor_command_0;
	motor_command_0 = joyInfo.buttons[0];

	float angle = joyInfo.axes[0];
	float center_angle = angle*90;
	if(angle < 0) angle = -angle;
	ROS_INFO("%lf",joyInfo.axes[0]);	
	angle = angle*90;

	if(motor_command_0){
		ROS_INFO("center_motor\t");
		center_motor_angle.data = center_angle;
	}
	else center_motor_angle.data = 0;

	if(motor_command_1) {
		ROS_INFO("motor_1\t");
		motor_1_angle.data = angle;
	}
	else motor_1_angle.data = 0;
	
	if(motor_command_2){
		ROS_INFO("motor_2\t");
		motor_2_angle.data = angle;
	}
	else motor_2_angle.data = 0;
	
	if(motor_command_3){
		ROS_INFO("motor_3\t");
		motor_3_angle.data = angle;
	}
	else motor_3_angle.data = 0;



	
	
	/*	

		
	switch(mode){
		case 0:
			ROS_INFO("center motor");	
			center_motor_angle.data = angle*30;
			motor_1_angle.data = 0;
			motor_2_angle.data = 0;
			motor_3_angle.data = 0;
			break;
		case 1:
			ROS_INFO("motor 1");	
			center_motor_angle.data = 0;
			motor_1_angle.data = angle*30; 
			motor_2_angle.data = 0;
			motor_3_angle.data = 0;
			break;
		case 2:
			ROS_INFO("motor 2");	
			center_motor_angle.data = 0;
			motor_1_angle.data = 0; 
			motor_2_angle.data = angle*30;
			motor_3_angle.data = 0;
			break;
		case 3:
			ROS_INFO("motor 3");	
			center_motor_angle.data = 0;
			motor_1_angle.data = 0;
			motor_2_angle.data = 0;
			motor_3_angle.data = angle*30; 
			break;
		case 4:
			ROS_INFO("motor 1 and 2");	
			center_motor_angle.data = 0;
			motor_1_angle.data = angle*30;
			motor_2_angle.data = angle*30;
			motor_3_angle.data = 0; 
			break;
	}
	*/
}









