#include <Servo.h>
#include "Underwater_Motor.h"
#include "Underwater_Encoder.h"
#include <SPI.h>
#include <ros.h>
#include <std_msgs/Int16.h>
#include <underwater_robot/Cmd.h>
#include <underwater_robot/Config.h>
#include <underwater_robot/Encoder.h>

/* Our actuators and senesor */
Motor myMotor;
Encoder myEncoder;

ros::NodeHandle nh;

underwater_robot::Encoder encoder_msg;
ros::Publisher encoder_pub("encoder2", &encoder_msg);

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



void read_config(const underwater_robot::Config &config_msg){
    /* set up confuration if not yet configed */
    if(!finish_config){
        if(config_msg.encoder2 == true){
            enable_encoder = true; 
            encoder_offset = config_msg.encoder2_offset;
        }
        finish_config = true;
    }
}

ros::Subscriber<underwater_robot::Cmd> motor_sub("motor_2", motor_command);
ros::Subscriber<underwater_robot::Config> config_sub("robot_config", read_config);



void setup(){
    nh.initNode();
    nh.subscribe(motor_sub);
    nh.subscribe(config_sub);
    nh.advertise(encoder_pub);
    /* Wait until recieve config from master */
    while(!finish_config){
        nh.spinOnce();
        delay(1);
    }
    /* Motor settings */
    myMotor.attach(3);
    myMotor.set_range(0,91,91+88);
    
    
    /* Encoder settings, make sure to set offset everytime */
    if(enable_encoder){
        myEncoder.attach(2);
        myEncoder.set_offset(encoder_offset);
        myEncoder.initialize_speed();
    } 
    /* global variables initialize */
    mode = 0;
    spinning_speed = 0;
    flipping_angle = 0;
    flipping_speed = 0;

    
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
            if(enable_encoder) myMotor.flip(flipping_angle, flipping_speed, myEncoder);
            else myMotor.brake();
            break;
        default:
            // unknown command type
            myMotor.brake();
    }
    if(enable_encoder){
        encoder_msg.encoder_angle = myEncoder.read_angle();
        encoder_msg.encoder_speed = myEncoder.read_speed();
        encoder_pub.publish(&encoder_msg);
    }
    nh.spinOnce();
    delay(10);
}









