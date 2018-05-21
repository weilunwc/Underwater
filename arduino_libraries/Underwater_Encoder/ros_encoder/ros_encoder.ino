#include <SPI.h>
#include "Underwater_Encoder.h"
#include <ros.h>
#include <std_msgs/Int32.h>

Encoder myEncoder;

ros::NodeHandle nh;
std_msgs::Int32 encoder_msg;
ros::Publisher p("encoder", &encoder_msg);

void setup(){
  //Serial.begin(9600);
  nh.initNode();
  nh.advertise(p);
  myEncoder.attach(2);
  myEncoder.set_offset(1963);
}

void loop(){
  int value = myEncoder.read_value();
  float angle = myEncoder.read_angle();
  //Serial.print("encoder value is : ");Serial.print(value);
  //Serial.print(" encoder angle is : ");Serial.println(angle);
  encoder_msg.data = value;
  p.publish(&encoder_msg);
  nh.spinOnce();
  delay(10);
}
