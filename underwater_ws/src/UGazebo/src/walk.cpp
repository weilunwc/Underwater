

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
//#include <gazebo_ros_force.h>
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
    ros::Publisher mot1_pub, mot2_pub, mot3_pub, central_pub, mot1for_pub,mot2for_pub,mot3for_pub;
    mot1_pub = n.advertise<std_msgs::Float64>("UGazebo/motor1_torque_controller/command",10);
    mot2_pub = n.advertise<std_msgs::Float64>("UGazebo/motor2_torque_controller/command",10);
    mot3_pub = n.advertise<std_msgs::Float64>("UGazebo/motor3_torque_controller/command",10);
    central_pub = n.advertise<std_msgs::Float32>("center_motor",10);
    mot1for_pub = n.advertise<std_msgs::Float32>("/shaft1_link_fixed/for_cmd",10);
    mot2for_pub = n.advertise<std_msgs::Float32>("/shaft2_link_fixed/for_cmd",10);
    mot3for_pub = n.advertise<std_msgs::Float32>("/shaft3_link_fixed/for_cmd",10);
    std_msgs::Float64 mot1;
    mot1.data = 0;
    std_msgs::Float64 mot2;
    mot2.data = 0;
    std_msgs::Float64 mot3;
    mot3.data = 0;
    std_msgs::Float32 mot1f;
    mot1f.data = 0;
    std_msgs::Float32 mot2f;
    mot2f.data = 0;
    std_msgs::Float32 mot3f;
    mot3f.data = 0;
    ros::Rate loop_rate(100);
    std_msgs::Float32 central;
    while(ros::ok()){
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
        mot1.data = 15*v(0);
        mot2.data = 15*v(1);
        mot3.data= 15*v(2);
        central.data = (1-axis[2])*100;
        mot1f.data = 100*buttons[0];
        mot2f.data = 100*buttons[1];
        mot3f.data = 100*buttons[2];
        //cout << fx << ' '<< fy << ' ' << dtheta;
        //cout << mot1.data << ' ' << mot2.data << ' ' << mot3.data << ' ' << central.data << endl;
        mot1_pub.publish(mot1);
        mot2_pub.publish(mot2);
        mot3_pub.publish(mot3);
        mot1for_pub.publish(mot1f);
        mot2for_pub.publish(mot2f);
        mot3for_pub.publish(mot3f);
        central_pub.publish(central);
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;

}  
