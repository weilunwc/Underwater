/*
 *  Base class for the underwater robot control, stores all the information
 *  and process the info to control commands
 *  Maintainer : Wei Lun William 
 */

#ifndef ROBOT_H
#define ROBOT_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Quaternion.h"
#include "underwater_msgs/Cmd.h"
#include "underwater_msgs/Imu.h"
#include "underwater_msgs/Encoder.h"
#include "underwater_msgs/Euler.h"

using namespace std;

#define DEBUG
#ifdef DEBUG
#define dbg_printf(...) printf(__VA_ARGS__)
#else
#define dbg_printf(...) 
#endif

// motor mode
enum
{
    MOTOR_STOP,
    MOTOR_SPIN,
    MOTOR_FLIP
};

// head leg
enum
{
    MOTOR_1,
    MOTOR_2,
    MOTOR_3
};

class Robot{
    public:
        Robot();

        /* debug info */
        void print_motor_commands();
        void print_imu();
        void print_joystick();	
        void print_pos();
        
        /* send motor commands */
        void send_motor_commands();
        void stop_motors();

    protected:
        ros::NodeHandle n;
        void setup(); // set up subscribers and publishers

        /* motor publisher */
        ros::Publisher center_motor_pub, motor_1_pub, motor_2_pub, motor_3_pub;
        underwater_msgs::Cmd center_cmd, motor1_cmd, motor2_cmd, motor3_cmd;
        
        /* joystick subscriber */
        ros::Subscriber joy_sub;
        void read_joystick(const sensor_msgs::Joy &joy_info);
        
        vector<bool> buttons;
        vector<bool> prev_buttons;
        vector<double> axis;

        /* IMU subscriber */
        ros::Subscriber imu_sub;
        //void read_imu(const underwater_msgs::Imu &euler_info);
        void read_imu(const geometry_msgs::Quaternion &imu_info);
        underwater_msgs::Euler euler;
        geometry_msgs::Quaternion quat;
                
        /* position subscriber */
        ros::Subscriber pos_sub;
        geometry_msgs::Point position; 
        void read_pos(const geometry_msgs::Point &pos_msg);
         
        /* encoder subscriber */
        ros::Subscriber enc1_sub, enc2_sub, enc3_sub;
        underwater_msgs::Encoder enc1, enc2, enc3;
        void read_encoder1(const underwater_msgs::Encoder &enc_info);
        void read_encoder2(const underwater_msgs::Encoder &enc_info);
        void read_encoder3(const underwater_msgs::Encoder &enc_info);
};

#endif

