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
#include "underwater_msg/Cmd.h"
#include "underwater_msg/Imu.h"
#include "underwater_msg/Baro.h"

using namespace std;

class Robot{

public:
	Robot(){start = false;};
	
    /* set up publisher and subscriber */
	void publish_motors();		
	void subscribe_joystick();
	void subscribe_imu();
	void subscribe_baro();
    void subscribe_encoder();
    void subscribe_pos();

	/* debug info */
	void print_motor_commands();
	void print_imu();
	void print_baro();
	void print_joystick();	
	void print_encoder();
	void print_pos();
    
    /* set mode of the motors */
    void set_spinning_mode();
    void set_flipping_mode();

	/* send motor commands */
	void send_motor_commands();
	void stop_motors();

	/* start and stop command */
	void check_suspend();	
    
    /* Encoder calibrate */
    void save_encoder_calibrate();
    vector<int> load_encoder_calibrate();
    
    /* process data methods */
	void process_joystick();	 
    void process_imu_yaw(double set_yaw);	
    void test_flipping(); 
    void joystick_spin_pid();
    void joystick_flip_pid();


private:
	ros::NodeHandle n;

	/* motor publisher */
	ros::Publisher center_motor_pub, motor_1_pub, motor_2_pub, motor_3_pub;
    underwater_msg::Cmd center_cmd, motor1_cmd, motor2_cmd, motor3_cmd;
	
	/* joystick subscriber */
	ros::Subscriber joy_sub;

    void read_joystick(const sensor_msgs::Joy &joy_info);
    vector<int> buttons;
	vector<double> axis;

	/* IMU subscriber */
	ros::Subscriber imu_sub;
	void read_imu(const underwater_msg::Imu &euler_info);
    double roll, pitch, yaw;
	
	/* barometer subscriber */
	ros::Subscriber baro_sub;
    void read_baro(const underwater_msg::Baro &baro_info);
    float depth, temp;
    
    /* encoder calibration subscriber */
    ros::Subscriber enc1_cal_sub, enc2_cal_sub, enc3_cal_sub;
    void read_encoder1(const std_msgs::Int32 &encoder1_msg);
    void read_encoder2(const std_msgs::Int32 &encoder2_msg);
    void read_encoder3(const std_msgs::Int32 &encoder3_msg);
    int encoder1_cal, encoder2_cal, encoder3_cal;
    
    /* position subscriber */
    ros::Subscriber pos_sub;
    void read_pos(const geometry_msgs::Point32 &pos_msg);
    geometry_msgs::Point32 position; 
    
    int head_leg; // parameter that determines which leg is the heading leg
    int motor_mode; // flipping mode or spinning mode

	/* switch that controls when to start and end the code */
	bool start;
};

#endif

