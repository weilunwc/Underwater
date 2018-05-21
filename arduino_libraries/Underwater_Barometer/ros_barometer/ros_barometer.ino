#include <Wire.h>
#include "Underwater_Barometer.h"

#include <ros.h>
#include <std_msgs/Float32.h>
//#include <std_msgs/Float32MultiArray.h>
//#include <geometry_msgs/Point32.h>
#include <underwater_robot/Baro.h>

ros::NodeHandle nh;
//std_msgs::Float32MultiArray baro_msg;
//std_msgs::Float32 baro_msg;
underwater_robot::Baro baro_msg;
//geometry_msgs::Point32 baro_msg;
ros::Publisher p("barometer",&baro_msg);

Barometer myBarometer;

void setup(){
  Serial.begin(115200);
  myBarometer.setup();

  nh.initNode();
  nh.advertise(p);
}

void loop(){

  myBarometer.display_data();
  float depth = myBarometer.depth();
  float temp = myBarometer.temperature();
	float pressure = myBarometer.pressure();
	float altitude = myBarometer.altitude();
	//baro_msg.data[0] = depth;
	//baro_msg.data = depth;
	baro_msg.depth = depth;
	baro_msg.temp = temp;
	baro_msg.pressure = pressure;
	baro_msg.altitude = altitude;
	p.publish(&baro_msg);
  nh.spinOnce();
  delay(100);
}



