#include <iostream>
#include <fstream>

#include "ros/ros.h"
#include "std_msgs/Int16.h"
#include "std_msgs/Float32.h"
#include "geometry_msgs/Point32.h"
#include "sensor_msgs/Joy.h"


using namespace std;


/* functions */
void read_barometer(const std_msgs::Float32 &depth_info);
void read_IMU_euler(const geometry_msgs::Point32 &euler_info);
void read_joystick(const sensor_msgs::Joy &joystick_info);
/* global variables */
float depth,roll,pitch,yaw;
vector<float> axes;
vector<int> buttons;
ofstream sensor_file;

int main(int argc, char **argv){
	/* Initialize global variables */		
	depth = 0.0;
	roll = 0.0;
	pitch = 0.0;
	yaw = 0.0;
	sensor_file.open("sensor_log.txt");


	/* Initialize the node */
	ros::init(argc, argv, "sensor_check");

	ros::NodeHandle n;
	
	

	/* Subscribe to sensor and state information */
	ros::Subscriber depth_sub = n.subscribe("depth", 1000, read_barometer);
	//ros::Subscriber euler_sub = n.subscribe("imu", 1000, read_IMU_euler);
	ros::Subscriber joy_sub = n.subscribe("joy", 1000, read_joystick);
	/* Set up frequency */
	ros::Rate loop_rate(10);
	
	/* 
	 * message type explained 
	 * center_motor: Int16 speed
	 * motor_x: Point32 mode, speed, angle
	 */
	std_msgs::Int16 center_speed;
	geometry_msgs::Point32 motor1_speed, motor2_speed, motor3_speed;
	


	while(ros::ok()){
	

		
		
		ros::spinOnce();
		loop_rate.sleep();
		
	}
	
	
	return 0;
}


void read_barometer(const std_msgs::Float32 &depth_info){
	depth = depth_info.data;
	ROS_INFO("depth: %lf", depth);
	sensor_file << "depth:" << depth << endl;;
}

void read_IMU_euler(const geometry_msgs::Point32 &euler_info){
	roll = euler_info.x;
	pitch = euler_info.y;
	yaw = euler_info.z;
	ROS_INFO("roll, pitch, yaw: %lf, %lf, %lf", roll, pitch, yaw);
	sensor_file << "roll,pitch,yaw:" << roll << "\t" << pitch << "\t" << yaw << endl;
}

void read_joystick(const sensor_msgs::Joy &joystick_info){
	ROS_INFO("%d",joystick_info.buttons[100]);
	
}




