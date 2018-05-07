#include <Servo.h>
#include "Underwater_Motor.h"
#include "Underwater_Encoder.h"
#include <SPI.h>
#include <ros.h>
#include <std_msgs/Int16.h>
#include <underwater_robot/Cmd.h>
#include <underwater_robot/Setup.h>

using underwater_robot::Setup;
/* Our actuators and senesor */
Motor myMotor;
Encoder myEncoder;

ros::NodeHandle nh;

ros::ServiceClient<Setup::Request, Setup::Response> setup_client("setup");


int mode, spinning_speed, flipping_angle, flipping_speed;
bool finish_config = false;
bool enable_encoder = false;
int encoder_offset = 0;

/* Read the control command */

void motor_command(const underwater_robot::Cmd& cmd_msg){
    mode = cmd_msg.mode;
    spinning_speed = cmd_msg.spinning_speed;
    flipping_angle = cmd_msg.flipping_angle;
    flipping_speed = cmd_msg.flipping_speed;
}




ros::Subscriber<underwater_robot::Cmd> motor_sub("motor_1", motor_command);



void setup(){
    nh.initNode();
    nh.subscribe(motor_sub);
    nh.serviceClient(setup_client);
    
    while(!finish_config){
        nh.spinOnce();
        Setup::Request req;
        Setup::Response res;
        setup_client.call(req, res);
        finish_config = res.done;
        enable_encoder = res.encoder1;
        encoder_offset = res.encoder1_offset;
        delay(1);
    }
    
    /* Motor settings */
    myMotor.attach(3);
    myMotor.set_range(0,91,91+88);
    
    
    /* Encoder settings, make sure to set offset everytime */
    if(enable_encoder){
        myEncoder.attach(2);
        myEncoder.set_offset(encoder_offset);
    } 
    /* global variables initialize */
    mode = 0;
    spinning_speed = 0;
    flipping_angle = 0;
    flipping_speed = 0;


}

void loop(){
    /*
    switch(mode){
        case 0:
            myMotor.brake();
            break;
        case 1:
            myMotor.set_speed(spinning_speed);
            break;
        case 2:
            if(enable_encoder) myMotor.flip(flipping_angle, flipping_speed, myEncoder);
            else myMotor.brake();
            break;
        default:
            // unknown command type
            myMotor.brake();
    }
    */
    myMotor.flip(30,30,myEncoder);
    nh.spinOnce();
    delay(1);
}









