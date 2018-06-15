

#include <iostream>
#include <vector>
#include <string>

#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include "sensor_msgs/Joy.h"
#include "std_msgs/Float64.h"
#include "std_msgs/Float32.h"
#include <Eigen/Dense>
#include <fstream>
#include "time.h"
#include "underwater_msgs/Cmd.h"
using namespace std;


vector<bool> buttons;
vector<bool> prev_buttons;
vector<double> axis;
bool start1 = false;
bool start2 = false;
void read_joystick(const sensor_msgs::Joy &joyInfo){
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
}


int main(int argc ,char **argv){
    ros::init(argc, argv, "joystick_control");
    ros::Subscriber joy_sub;
    ros::NodeHandle n;

    buttons.resize(11);
    prev_buttons.resize(11);
    axis.resize(8);
    for(int i = 0;i < 8;i++){
        axis[i] = 0;
    }
    axis[2] = 1;
    axis[5] = 1;
    for(int i = 0;i < 11;i++){
        buttons[i] = 0;
        prev_buttons[i] = 0;
    }


    joy_sub = n.subscribe("joy", 1000, &read_joystick);
    ros::Publisher mot1_pub, mot2_pub, mot3_pub, center_pub;
    mot1_pub = n.advertise<underwater_msgs::Cmd>("/motor1/cmd",10);
    mot2_pub = n.advertise<underwater_msgs::Cmd>("/motor2/cmd",10);
    mot3_pub = n.advertise<underwater_msgs::Cmd>("/motor3/cmd",10);
    center_pub = n.advertise<underwater_msgs::Cmd>("/robot_base_link/cmd",10);
    underwater_msgs::Cmd mot1_mes, mot2_mes, mot3_mes, center_mes;
    mot1_mes.mode = 1;
    mot2_mes.mode = 1;
    mot3_mes.mode = 1;
    center_mes.mode = 1;
    bool start = true;
    ros::Rate loop_rate(100);
    while(ros::ok()){
        if(axis[2] == 0 && start){
            axis[2] = 1;
        }
        else if(axis[2] != 0){
            start = false;
        }
        double l = 1.0;    
        Eigen::MatrixXd m(3,3);
        m(0,0) = -2.0/3.0;
        m(0,1) = 0;
        m(0,2) = 1.0/(3.0*l);
            
        m(1,0) = 1.0/3.0;
        m(1,1) = -sqrt(3)/3.0;
        m(1,2) = 1.0/(3.0*l);

        m(2,0) = 1.0/3.0;
        m(2,1) = sqrt(3)/3.0;
        m(2,2) = 1.0/(3.0*l);
        Eigen::VectorXd v(3);
        double fx = -1*axis[0];
        double fy = axis[1];
        double dtheta = -1*axis[3];

        v << fx, fy, dtheta;
        v = m*v;
        if(buttons[0] == 1){
            mot1_mes.mode = 2;
            mot2_mes.mode = 2;
            mot3_mes.mode = 2;
        }
        if(buttons[1] == 1){
            mot1_mes.mode = 1;
            mot2_mes.mode = 1;
            mot3_mes.mode = 1;
            center_mes.mode = 1;
        }
        mot1_mes.spinning_speed = 90*v(0);
        mot2_mes.spinning_speed = 90*v(1);
        mot3_mes.spinning_speed = 90*v(2);
        center_mes.spinning_speed = axis[2]*30;
        //cout << fx << ' '<< fy << ' ' << dtheta;
        //cout << mot1.data << ' ' << mot2.data << ' ' << mot3.data << ' ' << central.data << endl;
        mot1_mes.flipping_angle = axis[1]*180;
        mot2_mes.flipping_angle = axis[1]*180;
        mot3_mes.flipping_angle = axis[1]*180;

        mot1_mes.flipping_speed = axis[3]*90;
        mot2_mes.flipping_speed = axis[3]*90;
        mot3_mes.flipping_speed = axis[3]*90;
        center_mes.flipping_speed = (1-axis[2])*30;
        if(axis[2] == 1){
           center_mes.flipping_speed = -1*(1-axis[5])*30;
        }
        mot1_pub.publish(mot1_mes);
        mot2_pub.publish(mot2_mes);
        mot3_pub.publish(mot3_mes);
        center_pub.publish(center_mes);

        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;

}  