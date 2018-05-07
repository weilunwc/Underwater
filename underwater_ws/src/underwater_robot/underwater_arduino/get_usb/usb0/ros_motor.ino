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

ros::Subscriber<std_msgs::Int16> sub("usb0", motor_command);



//Servo myMotor;
void setup(){

  //Serial.begin(9600);
  myMotor.attach(3);
  myMotor.set_range(0,91,91+88);

  nh.initNode();
  nh.subscribe(sub);
}

void loop(){

  nh.spinOnce();
  delay(1);
  /*
  int pos;
  for(pos = 0; pos < 80;pos+=1){
    myMotor.set_speed(pos);
    delay(15);
  }
  for(pos = 80; pos > 0;pos--){
    myMotor.set_speed(pos);
    delay(15);
  }
  myMotor.brake();
  delay(3000);
  // Serial.println(myMotor.pin);
  */
}
