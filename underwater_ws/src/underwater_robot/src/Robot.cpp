#include "Robot.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <Eigen/Dense>
#include <tf/transform_broadcaster.h>
using namespace std;

static float rad2deg(float rad){
   return rad*180.0/3.1415926; 
}

Robot::Robot(){
    setup(); 
}

void Robot::setup(){
    /* motor publisher */
    center_motor_pub = n.advertise<underwater_msgs::Cmd>("center_motor", 10);
    motor_1_pub = n.advertise<underwater_msgs::Cmd>("motor_1", 10);
    motor_2_pub = n.advertise<underwater_msgs::Cmd>("motor_2", 10);
    motor_3_pub = n.advertise<underwater_msgs::Cmd>("motor_3", 10);
    
    /* imu subscriber */
    imu_sub = n.subscribe("imu", 10, &Robot::read_imu, this);

    /* joystick subscriber */
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
    
    /* position subscriber */
    pos_sub = n.subscribe("position", 10, &Robot::read_pos, this);
    
    /* encoder subscriber */
    enc1_sub = n.subscribe("encoder_1", 10, &Robot::read_encoder1, this);
    enc2_sub = n.subscribe("encoder_2", 20, &Robot::read_encoder2, this);
    enc3_sub = n.subscribe("encoder_3", 30, &Robot::read_encoder3, this);
}

void Robot::send_motor_commands(){
    
    center_motor_pub.publish(center_cmd);
    motor_1_pub.publish(motor1_cmd);
    motor_2_pub.publish(motor2_cmd);
    motor_3_pub.publish(motor3_cmd);
}

void Robot::stop_motors(){

    center_cmd.mode = MOTOR_STOP;
    motor1_cmd.mode = MOTOR_STOP;
    motor2_cmd.mode = MOTOR_STOP;
    motor3_cmd.mode = MOTOR_STOP;

    send_motor_commands();
}

void Robot::print_motor_commands(){
    dbg_printf("center: mode %d, spinning speed %d\n", center_cmd.mode, center_cmd.spinning_speed);
    dbg_printf("motor1: mode %d, spinning speed %d, flipping angle %d, flipping speed %d\n",
            motor1_cmd.mode, motor1_cmd.spinning_speed, motor1_cmd.flipping_angle, motor1_cmd.flipping_speed);
    dbg_printf("motor2: mode %d, spinning speed %d, flipping angle %d, flipping speed %d\n",
            motor2_cmd.mode, motor2_cmd.spinning_speed, motor2_cmd.flipping_angle, motor2_cmd.flipping_speed);
    dbg_printf("motor3: mode %d, spinning speed %d, flipping angle %d, flipping speed %d\n\n",
            motor3_cmd.mode, motor3_cmd.spinning_speed, motor3_cmd.flipping_angle, motor3_cmd.flipping_speed);
}


/*
void Robot::read_imu(const underwater_msgs::Imu &euler_info){
    euler.roll = euler_info.euler.roll;
    euler.pitch = euler_info.euler.pitch;
    euler.yaw = euler_info.euler.yaw;
}
*/

void Robot::read_imu(const geometry_msgs::Quaternion &imu_info){
    quat.x = imu_info.x;
    quat.y = imu_info.y;
    quat.z = imu_info.z;
    quat.w = imu_info.w;
    
    // transform to euler
    tf::Quaternion quater(quat.x, quat.y, quat.z, quat.w);
    double roll, pitch, yaw;
    tf::Matrix3x3(quater).getRPY(roll, pitch, yaw);
     
    
    euler.roll = rad2deg(roll);
    euler.pitch = rad2deg(pitch);
    euler.yaw = rad2deg(yaw);

}


void Robot::print_imu(){
    dbg_printf("roll pitch yaw: %lf,\t%lf,\t%lf\n", euler.roll, euler.pitch, euler.yaw);
    //dbg_printf("quaternion: %lf,\t%lf,\t%lf,\t%lf\n", quat.x, quat.y, quat.z, quat.w);
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
}

void Robot::print_joystick(){
    for(int i = 0;i < 11;i++){
        dbg_printf("%d ", buttons[i]);
    }
    dbg_printf("\n");
}


/* Position */
void Robot::read_pos(const geometry_msgs::Point &pos_info){
    position.x = pos_info.x;
    position.y = pos_info.y;
    position.z = pos_info.z;
}

void Robot::print_pos(){
    dbg_printf("Position x: %lf, y: %lf, z:%lf\n", position.x, position.y, position.z);    
}

/* Encoder */
void Robot::read_encoder1(const underwater_msgs::Encoder &enc_info){
    enc1.encoder_angle = enc_info.encoder_angle;
    enc1.encoder_speed = enc_info.encoder_speed;
}

void Robot::read_encoder2(const underwater_msgs::Encoder &enc_info){
    enc2.encoder_angle = enc_info.encoder_angle;
    enc2.encoder_speed = enc_info.encoder_speed;
}

void Robot::read_encoder3(const underwater_msgs::Encoder &enc_info){
    enc3.encoder_angle = enc_info.encoder_angle;
    enc3.encoder_speed = enc_info.encoder_speed;
}

