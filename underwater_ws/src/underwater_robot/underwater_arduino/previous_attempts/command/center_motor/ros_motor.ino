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

ros::Subscriber<underwater_robot::Cmd> sub("center_motor", motor_command);



void setup(){

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
        default:
            // unknown command
            myMotor.brake();
    }

    nh.spinOnce();
    delay(1);
}









