#include <Servo.h>
#include "Underwater_Motor.h"

#include <SPI.h>
#include "Underwater_Encoder.h"

#include <Wire.h>
#include "Underwater_Barometer.h"

#include <ros.h>
#include <std_msgs/Int16.h>
#include <underwater_robot/Cmd.h>
#include <underwater_robot/Config.h>
#include <underwater_robot/Baro.h>



/* Our actuators and senesor */
Motor myMotor;
Encoder myEncoder;
Barometer myBarometer;


underwater_robot::Baro baro_msg;
ros::NodeHandle nh;
ros::Publisher baro_pub("barometer", &baro_msg);



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
        if(config_msg.encoder1 == true){
            enable_encoder = true; 
            encoder_offset = config_msg.encoder1_offset;
        }
        if(config_msg.barometer == true){
            enable_barometer = true;
        }
        finish_config = true;
    }
}

ros::Subscriber<underwater_robot::Cmd> motor_sub("motor_1", motor_command);
ros::Subscriber<underwater_robot::Config> config_sub("robot_config", read_config);



void setup(){
    nh.initNode();
    nh.subscribe(motor_sub);
    nh.subscribe(config_sub);
    
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
    } 

    /* Barometer settings */
    if(enable_barometer){
        myBarometer.setup();
        nh.advertise(baro_pub);
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
    
    /* read barometer */
    if(enable_barometer){
        /* read the barometer data */
        myBarometer.display_data();

        float depth = myBarometer.depth();
        float temp = myBarometer.temperature();
        float pressure = myBarometer.pressure();
        float altitude = myBarometer.altitude();
        
        baro_msg.depth = depth;
        baro_msg.temp = temp;
        baro_msg.pressure = pressure;
        baro_msg.altitude = altitude;
        baro_pub.publish(&baro_msg);
    }

    nh.spinOnce();
    delay(1);
}









