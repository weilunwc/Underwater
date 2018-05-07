#include <Servo.h>
#include "Underwater_Motor.h"
#include "Underwater_Encoder.h"
#include <SPI.h>
#include <ros.h>
#include <std_msgs/Int16.h>
#include <underwater_robot/Cmd.h>

/* Our actuators and senesor */
Motor myMotor;
Encoder myEncoder;

ros::NodeHandle nh;

int mode, spinning_speed, flipping_angle, flipping_speed;


/* Read the control command */
void motor_command(const underwater_robot::Cmd& cmd_msg){
    mode = cmd_msg.mode;
    spinning_speed = cmd_msg.spinning_speed;
    flipping_angle = cmd_msg.flipping_angle;
    flipping_speed = cmd_msg.flipping_speed;
}

//ros::Subscriber<std_msgs::Int16> sub("motor_1", motor_command);
ros::Subscriber<underwater_robot::Cmd> sub("motor_1", motor_command);



void setup(){

    Serial.begin(9600);
    /* Motor settings */
    myMotor.attach(3);
    myMotor.set_range(0,91,91+88);

    /* Encoder settings, make sure to set offset everytime */
    myEncoder.attach(2);
    myEncoder.set_offset(100);
    
    /* global variables initialize */
    mode = 0;
    spinning_speed = 0;
    flipping_angle = 0;
    flipping_speed = 0;

    nh.initNode();
    nh.subscribe(sub);
}

void loop(){
    switch(mode){
        case 0:
            myMotor.brake();
            break;
        case 1:
            myMotor.set_speed(spinning_speed);
            break;
        case 2:
            myMotor.flip(flipping_angle, flipping_speed, myEncoder);
            break;
    }

    nh.spinOnce();
    delay(1);
}









