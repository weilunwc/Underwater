#include <Servo.h>
#include "Underwater_Motor.h"

#include <SPI.h>
#include "Underwater_Encoder.h"

#include "Adafruit_Sensor.h"
#include "Adafruit_BNO055.h"
#include <Wire.h>
#include "Underwater_IMU.h"

#include <ros.h>
#include <underwater_robot/Cmd.h>
#include <underwater_robot/Config.h>
#include <underwater_robot/Euler.h>


/* Our actuators and senesor */
Motor myMotor;
IMU myIMU;


ros::NodeHandle nh;
//geometry_msgs::Point32 imu_msg;
underwater_robot::Euler imu_msg;
ros::Publisher imu_pub("imu", &imu_msg);

int mode, spinning_speed;
bool finish_config = false;
bool enable_imu = false;

/* Read the control command */

void motor_command(const underwater_robot::Cmd& cmd_msg){
    mode = cmd_msg.mode;
    spinning_speed = cmd_msg.spinning_speed;
}



void read_config(const underwater_robot::Config &config_msg){
    /* set up config if not yet configured */
    if(!finish_config){
        if(config_msg.imu == true){
            enable_imu = true;
        }
        finish_config = true;
    }
}

ros::Subscriber<underwater_robot::Cmd> motor_sub("center_motor", motor_command);
ros::Subscriber<underwater_robot::Config> config_sub("robot_config", read_config);



void setup(){
    nh.initNode();
    nh.subscribe(motor_sub);
    nh.subscribe(config_sub);
    nh.advertise(imu_pub);
    
    /* Wait until recieve config from master */
    while(!finish_config){
        nh.spinOnce();
        delay(1);
    }
    /* Motor settings */
    myMotor.attach(3);
    myMotor.set_range(0,91,91+88);
    
    /* IMU settings */
    if(enable_imu){
        myIMU.setup();

    }
    
    /* global variables initialize */
    mode = 0;
    spinning_speed = 0;


}

void loop(){
    /* Control motor based on command */
    switch(mode){
        case 0:
            myMotor.brake();
            break;
        case 1:
            myMotor.set_speed(spinning_speed);
            break;
        default:
            // unknown command type
            myMotor.brake();
    }
    
    if(enable_imu){
        euler_data euler;
        euler = myIMU.get_euler_data();
        /*
        imu_msg.x = euler.roll;
        imu_msg.y = euler.pitch;
        imu_msg.z = euler.yaw;
        */
        
        /* adjust euler data to robot frame */
        imu_msg.roll = -euler.yaw;
        imu_msg.pitch = euler.pitch;
        imu_msg.yaw = 360.0 - euler.roll;

        imu_pub.publish(&imu_msg);
    }

    nh.spinOnce();
    delay(10);
}


