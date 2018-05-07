#include <Wire.h>
#include "Underwater_Barometer.h"

#include <ros.h>
#include <std_msgs/Float32.h>

ros::NodeHandle nh;
std_msgs::Float32 depth;
ros::Publisher p("depth",&depth);

Barometer myBarometer;

void setup(){
  Serial.begin(115200);
  myBarometer.setup();

  nh.initNode();
  nh.advertise(p);
}

void loop(){

  myBarometer.display_data();
  float z = myBarometer.depth();
  depth.data = z;
  p.publish(&depth);
  nh.spinOnce();
  delay(100);
}



