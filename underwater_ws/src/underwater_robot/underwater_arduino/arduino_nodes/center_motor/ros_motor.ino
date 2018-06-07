/* Center Motor : Motors and Imu*/

#include <Servo.h>
#include "Underwater_Motor.h"

#include "Underwater_Encoder.h"
#include <SPI.h>

#include "Adafruit_Sensor.h"
#include "Adafruit_BNO055.h"
#include <Wire.h>
#include "Underwater_IMU.h"

#include <ros.h>
#include <underwater_msgs/Cmd.h>
//#include <underwater_msgs/Imu.h>
#include <geometry_msgs/Quaternion.h>

/* Our actuators and senesor */
Motor myMotor;
IMU myIMU;

ros::NodeHandle nh;

/* Set up motor */
int mode, spinning_speed, flipping_angle, flipping_speed;
/* Read the motor control command */
void motor_command(const underwater_msgs::Cmd& cmd_msg){
    mode = cmd_msg.mode;
    spinning_speed = cmd_msg.spinning_speed;
    flipping_angle = cmd_msg.flipping_angle;
    flipping_speed = cmd_msg.flipping_speed;
}
ros::Subscriber<underwater_msgs::Cmd> motor_sub("center_motor", motor_command);

/* Set up Imu */
//underwater_msgs::Imu imu_msg;
geometry_msgs::Quaternion imu_msg;
ros::Publisher imu_pub("imu", &imu_msg);

/* Set up Config 
 * Imu Baro Enc1 Enc2 Enc3 Enc1_off Enc2_off Enc3_off 
 */

bool enable_imu;
void read_configs(){
    /* Set up configsuration from reading ros parameters */
    bool enable_baro, enable_encoder1, enable_encoder2, enable_encoder3;
    int encoder_offset1, encoder_offset2, encoder_offset3;
    int configs[8];
    configs[0] = 0;
    configs[1] = 0;
    configs[2] = 0;
    configs[3] = 0;
    configs[4] = 0;
    configs[5] = 0;
    configs[6] = 0;
    configs[7] = 0;
    
    while(!nh.getParam("arduino_configs", configs, 8)){
        delay(10);
        nh.spinOnce();
    }

    enable_imu = configs[0];
    enable_baro = configs[1];
    enable_encoder1 = configs[2];
    enable_encoder2 = configs[3];
    enable_encoder3 = configs[4];
    encoder_offset1 = configs[5];
    encoder_offset2 = configs[6];
    encoder_offset3 = configs[7];
}

void setup(){
    nh.initNode();
    nh.subscribe(motor_sub);
    nh.advertise(imu_pub); 
    read_configs();

    /* Motor settings */
    myMotor.attach(3);
    myMotor.set_range(0, 91, 91+88);
    mode = 0;
    spinning_speed = 0;
    
    /* IMU settings */
    if(enable_imu){
        myIMU.setup();
    }
}

void loop(){
    /* Send motor commands */
    switch(mode){
        case MOTOR_STOP:
            myMotor.brake();
            break;
        case MOTOR_SPIN:
            myMotor.set_speed(spinning_speed);
            break;
        default:
            /* unknown command type */
            myMotor.brake();
    }
    
    /* Read IMU */
    if(enable_imu){
        /*
        euler_data euler;
        euler = myIMU.get_euler_data();

        imu_msg.roll = -euler.yaw;
        imu_msg.pitch = euler.pitch;
        imu_msg.yaw = 360.0 - euler.roll;
        */
        imu::Quaternion quat = myIMU.get_quaternion_data();
        
        // rotate around yaw
        imu_msg.x = quat.x(); 
        imu_msg.y = quat.y(); 
        imu_msg.z = quat.z(); 
        imu_msg.w = quat.w(); 

        imu_pub.publish(&imu_msg);
    }


    nh.spinOnce();
    delay(1);
}

