#include "Robot.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <Eigen/Dense>
using namespace std;



Robot::Robot(){

    /* motor publisher */
    center_motor_pub = n.advertise<underwater_msgs::Cmd>("center_motor", 10);
    motor_1_pub = n.advertise<underwater_msgs::Cmd>("motor_1", 10);
    motor_2_pub = n.advertise<underwater_msgs::Cmd>("motor_2", 10);
    motor_3_pub = n.advertise<underwater_msgs::Cmd>("motor_3", 10);
    
    /* imu subscriber */
    imu_sub = n.subscribe("imu", 10, &Robot::read_imu, this);

    
    /* joystick subscriber */
    head_leg = 1;
    joy_sub = n.subscribe("joy", 10, &Robot::read_joystick, this);
    buttons.resize(11);
    prev_buttons.resize(11);
    axis.resize(8);
    for(int i = 0;i < 8;i++){
        axis[i] = 0;
    }
    for(int i = 0;i < 11;i++){
        buttons[i] = 0;
        prev_buttons[i] = 0;
    }
    //cruise_mode = false;
    //cruise_speed = 0;

    /* position subscriber */
    pos_sub = n.subscribe("position", 10, &Robot::read_pos, this);
       
    
}


void Robot::send_motor_commands(){
    
    center_motor_pub.publish(center_cmd);
    motor_1_pub.publish(motor1_cmd);
    motor_2_pub.publish(motor2_cmd);
    motor_3_pub.publish(motor3_cmd);
}

void Robot::stop_motors(){

    center_cmd.mode = 0;
    motor1_cmd.mode = 0;
    motor2_cmd.mode = 0;
    motor3_cmd.mode = 0;

    send_motor_commands();
}

void Robot::print_motor_commands(){
    printf("center: mode %d, spinning speed %d\n", center_cmd.mode, center_cmd.spinning_speed);
    printf("motor1: mode %d, spinning speed %d, flipping angle %d, flipping speed %d\n",
            motor1_cmd.mode, motor1_cmd.spinning_speed, motor1_cmd.flipping_angle, motor1_cmd.flipping_speed);
    printf("motor2: mode %d, spinning speed %d, flipping angle %d, flipping speed %d\n",
            motor2_cmd.mode, motor2_cmd.spinning_speed, motor2_cmd.flipping_angle, motor2_cmd.flipping_speed);
    printf("motor3: mode %d, spinning speed %d, flipping angle %d, flipping speed %d\n\n",
            motor3_cmd.mode, motor3_cmd.spinning_speed, motor3_cmd.flipping_angle, motor3_cmd.flipping_speed);
}


/*
void Robot::read_imu(const underwater_msgs::Imu &euler_info){
    roll = euler_info.roll;
    pitch = euler_info.pitch;
    yaw = euler_info.yaw;
}
*/

void Robot::read_imu(const geometry_msgs::Quaternion &imu_info){
    
}


void Robot::print_imu(){
    ROS_INFO("roll, pitch, yaw: %lf,\t%lf,\t%lf",roll,pitch,yaw);
}


void Robot::read_joystick(const sensor_msgs::Joy &joyInfo){
    for(int i = 0;i < 8;i++){
        axis[i] = joyInfo.axes[i];
    }
    /* store the previous state of the buttons */
    for(int i = 0;i < 11;i++){
        prev_buttons[i] = buttons[i];
    }
    for(int i = 0;i < 11;i++){
        buttons[i] = joyInfo.buttons[i];
    }
   
    //print_joystick();

    /* use these two buttons as a switch to activate robot*/
    if(buttons[8] == 1){
        start = true;
        cout << "start system" << endl;
    }
    if(buttons[6] == 1) {
        start = false;
        cout << "suspend system" << endl;
    }
    
    if(buttons[7] == 1){
        mode = 1;
    }
    if(buttons[5] == 1){
        mode = 0;
    }
    /* determine head leg */
    if(buttons[3] == 1) head_leg = 1; // Y
    if(buttons[2] == 1) head_leg = 2; // X
    if(buttons[1] == 1) head_leg = 3; // B

}

void Robot::print_joystick(){
    for(int i = 0;i < 11;i++){
        cout << buttons[i] << " ";
    }
    cout << endl;
}

void Robot::read_pos(const geometry_msgs::Point32 &pos_info){
    position.x = pos_info.x;
    position.y = pos_info.y;
    position.z = pos_info.z;
}

void Robot::print_pos(){
    printf("Position x: %lf, y: %lf, z:%lf", position.x, position.y, position.z);    
}

/* Set a switch that activates and deactivates the system */
void Robot::check_suspend(){
    if(!start){
        ros::Rate loop_rate(10);
        while(ros::ok()){
            //ROS_INFO("suspend");
            stop_motors();
            ros::spinOnce();
            loop_rate.sleep();
            if(start) break;
        }
    }
}


