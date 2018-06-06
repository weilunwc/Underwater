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

#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include "sensor_msgs/Joy.h"
#include "geometry_msgs/Point32.h"
#include "geometry_msgs/Quaternion.h"
#include "underwater_msgs/Cmd.h"
#include "underwater_msgs/Imu.h"

using namespace std;

class Robot{

public:
	Robot();
    
    int mode;
    /* set up publisher and subscriber */
	void publish_motors();		
	void subscribe_joystick();
	void subscribe_imu();
    void subscribe_pos();

	/* debug info */
	void print_motor_commands();
	void print_imu();
	void print_joystick();	
	void print_pos();
    
    /* set mode of the motors */
    void set_spinning_mode();
    void set_flipping_mode();

	/* send motor commands */
	void send_motor_commands();
	void stop_motors();

	/* start and stop command */
	void check_suspend();	
    
    
    /* process data methods */
	void process_joystick();
	void process_Ground();		 
    void process_imu_yaw(double set_yaw);	
    void test_flipping(); 
    void joystick_spin_pid();
    void joystick_flip_pid();
    void joystick_openloop_straight(int max_straight_speed, int max_adjust_speed);
    void joystick_closedloop_straight();
    void planar_straight(int speed);
    void planar_straight_joystick_adjust(int adjust_speed);
    void planar_straight_imu_adjust(int target_yaw);
    
    /* z motion */
    void constant_z(int speed);
    void joystick_z();
    void imu_planar_stable();
    void balance_roll();
    void balance_pitch();

private:
	ros::NodeHandle n;

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
	void read_imu(const underwater_msgs::Imu &euler_info);
    double roll, pitch, yaw;
	
    /* position subscriber */
    ros::Subscriber pos_sub;
    void read_pos(const geometry_msgs::Point32 &pos_msg);
    geometry_msgs::Point32 position; 
    
    /* Code parameters such as pid errors */
    int head_leg; // the leg pointing frontwards 
    
    /* Planar Motion */
    bool cruise_mode; // fix the forward speed
    int cruise_speed;	
    int current_angle;
    bool start_straight;
    /* switch that controls when to start and end the code */
	bool start;

    /* PID error */
    double last_error;
    double cumulate_error;

};

#endif

