#include "Underwater_Motor.h"
#include <Servo.h>

#include <SPI.h>
#include "Underwater_Encoder.h"

#include <ros.h>
#include <std_msgs/Int16.h>



/* Our actuators and sensors */
Motor myMotor;
Encoder myEncoder;

ros::NodeHandle nh;

int angle = 0;
bool activate = 0;

void motor_command(const std_msgs::Int16& cmd_msg){
	activate = 1;
	angle = cmd_msg.data;
}

ros::Subscriber<std_msgs::Int16> sub("motor_1", motor_command);





void setup(){
	Serial.begin(9600);
  myMotor.attach(3);
  myEncoder.attach(2);
  myEncoder.set_offset(540);

	nh.initNode();
	nh.subscribe(sub);
}

void loop(){
	if(activate) myMotor.flip(angle, 15, myEncoder);

	nh.spinOnce();
	delay(1);

}










