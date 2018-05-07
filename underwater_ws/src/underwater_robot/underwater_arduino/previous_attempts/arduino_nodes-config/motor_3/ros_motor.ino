#include <Servo.h>
#include "Underwater_Motor.h"

#include <SPI.h>
#include "Underwater_Encoder.h"

#include <Wire.h>
#include "Underwater_Barometer.h"

#include <ros.h>
#include <std_msgs/Int16.h>
#include <std_msgs/String.h>


#include <underwater_robot/Cmd.h>
#include <underwater_robot/Config.h>
#include <underwater_robot/Baro.h>
#include <underwater_robot/Encoder.h>

/* Our actuators and senesor */
Motor myMotor;
Encoder myEncoder;
Barometer myBarometer;

ros::NodeHandle nh;

underwater_robot::Baro baro_msg;
ros::Publisher baro_pub("barometer", &baro_msg);

underwater_robot::Encoder encoder_msg;
ros::Publisher encoder_pub("encoder3", &encoder_msg);


int mode, spinning_speed, flipping_angle, flipping_speed;
bool finish_config = false;
bool enable_encoder = false;
int encoder_offset = 0;

bool enable_barometer = false;


/* Read the control command */

void motor_command(const underwater_robot::Cmd& cmd_msg){
    mode = cmd_msg.mode;
    spinning_speed = cmd_msg.spinning_speed;
    flipping_angle = cmd_msg.flipping_angle;
    flipping_speed = cmd_msg.flipping_speed;
}



void read_config(const underwater_robot::Config &config_msg){
    /* set up config if not yet configured */
    if(!finish_config){
        if(config_msg.encoder3 == true){
            enable_encoder = true; 
            encoder_offset = config_msg.encoder3_offset;
        }
        if(config_msg.barometer == true){
            enable_barometer = true;
        }
        finish_config = true;
    }
}

ros::Subscriber<underwater_robot::Cmd> motor_sub("motor_3", motor_command);
ros::Subscriber<underwater_robot::Config> config_sub("robot_config", read_config);



void setup(){
    nh.initNode();
    nh.subscribe(motor_sub);
    nh.subscribe(config_sub);
    nh.advertise(encoder_pub);
    nh.advertise(baro_pub);
    
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

    /* Barometer settings */
    if(enable_barometer){
        myBarometer.setup();
    }
    
    /* global variables initialize */
    mode = 0;
    spinning_speed = 0;
    flipping_angle = 0;
    flipping_speed = 0;


}

void loop(){
    /* Sending motor signal based on control */
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

    /* read barometer */
    if(enable_barometer){
        /* read the barometer data */
        myBarometer.display_data();

        float depth = myBarometer.depth();
        float temp = myBarometer.temperature();
        
        baro_msg.depth = depth;
        baro_msg.temp = temp;
        baro_pub.publish(&baro_msg);

 
    }

    nh.spinOnce();
    delay(10);
}









