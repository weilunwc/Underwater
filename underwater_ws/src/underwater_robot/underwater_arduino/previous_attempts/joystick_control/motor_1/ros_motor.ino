#include <Servo.h>
#include "Underwater_Motor.h"
#include "Underwater_Encoder.h"
#include <SPI.h>
#include <ros.h>
#include <std_msgs/Int16.h>

Motor myMotor;


ros::NodeHandle nh;


void motor_command(const std_msgs::Int16& cmd_msg){
  myMotor.set_speed(cmd_msg.data);
}

ros::Subscriber<std_msgs::Int16> sub("motor_1", motor_command);



//Servo myMotor;
void setup(){

  Serial.begin(9600);
  myMotor.attach(3);
  myMotor.set_range(0,91,91+88);

  nh.initNode();
  nh.subscribe(sub);
}

void loop(){

  nh.spinOnce();
  delay(1);
}
