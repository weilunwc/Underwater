#include <iostream>
#include <fstream>

#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include "std_msgs/Float32.h"
#include "geometry_msgs/Point32.h"
#include "sensor_msgs/Joy.h"


using namespace std;


/* functions */
void read_encoder1(const std_msgs::Int32 &encoder1_info);
void read_encoder2(const std_msgs::Int32 &encoder2_info);
void read_encoder3(const std_msgs::Int32 &encoder3_info);
int angle1,angle2,angle3;

int main(int argc, char **argv){
	/* Initialize global variables */		
	angle1 = 0;
	angle2 = 0;
	angle3 = 0;


	/* Initialize the node */
	ros::init(argc, argv, "encoder_check");

	ros::NodeHandle n;
	
	

	/* Subscribe to sensor and state information */
	ros::Subscriber encoder1_sub = n.subscribe("encoder1", 1000, read_encoder1);
	ros::Subscriber encoder2_sub = n.subscribe("encoder2", 1000, read_encoder2);
	ros::Subscriber encoder3_sub = n.subscribe("encoder3", 1000, read_encoder3);
	
	
	/* Set up frequency */
	ros::Rate loop_rate(10);
	
	/* 
	 * message type explained 
	 * center_motor: Int16 speed
	 * motor_x: Point32 mode, speed, angle
	 */
	


	while(ros::ok()){
	
		ROS_INFO("%d\t%d\t%d",angle1,angle2,angle3);
		
		ros::spinOnce();
		loop_rate.sleep();
		
	}
	
	
	return 0;
}



void read_encoder1(const std_msgs::Int32 &encoder1_info){
	angle1 = encoder1_info.data;
}

void read_encoder2(const std_msgs::Int32 &encoder2_info){
	angle2 = encoder2_info.data;
}
void read_encoder3(const std_msgs::Int32 &encoder3_info){
	angle3 = encoder3_info.data;
}
