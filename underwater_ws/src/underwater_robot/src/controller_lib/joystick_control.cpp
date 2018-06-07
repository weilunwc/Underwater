/*
 *  This code is intended to use joystick to control the robot open loop
 */

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "Robot.h"
#include "time.h"
#include <std_msgs/Int32.h>
#include <Eigen/Dense>


using namespace std;

enum
{
    MODE_WATER,
    MODE_GROUND
};


class JoyRobot: public Robot{
    public:
        JoyRobot();
        void process_joystick();
        void process_ground();
        void check_suspend();
        int mode;
    protected:
        // override the joystick reading with more complex behavior
        void read_joystick(const sensor_msgs::Joy &joyInfo);

        int head_leg;
        bool start;
};

JoyRobot::JoyRobot(){
    setup();
    head_leg = MOTOR_1;
    start = false;
    mode = MODE_WATER;
}

/* Set a switch that activates and deactivates the system */
void JoyRobot::check_suspend(){
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

/* override tha base read_joystick and add switch modes */
void JoyRobot::read_joystick(const sensor_msgs::Joy &joyInfo){
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
    if(buttons[3] == 1) head_leg = MOTOR_1; // Y
    if(buttons[2] == 1) head_leg = MOTOR_2; // X
    if(buttons[1] == 1) head_leg = MOTOR_3; // B

}


void JoyRobot::process_joystick(){
    /* center motor */    
    center_cmd.mode = MOTOR_SPIN;
    if(axis[2] != 1){
        center_cmd.spinning_speed = 85*(1-axis[2])/2;
    }
    else if(axis[5] != 1){
        center_cmd.spinning_speed = -85*(1-axis[5])/2;
    }
    else{
        center_cmd.spinning_speed = 0;
    }
    //center_cmd.spinning_speed = 80*(1 - axis[2])/2 + -80*(1 - axis[5])/2;

    /* flipping mode */

    /* Change pitch and yaw */
    if(axis[0] > 0.5){
        // flip left clockwise
        motor1_cmd.mode = MOTOR_FLIP;
        motor1_cmd.flipping_angle = 90;
        motor1_cmd.flipping_speed = 40;

        motor2_cmd.mode = MOTOR_FLIP;
        motor2_cmd.flipping_angle = 90;
        motor2_cmd.flipping_speed = 40;

        motor3_cmd.mode = MOTOR_FLIP;
        motor3_cmd.flipping_angle = 90;
        motor3_cmd.flipping_speed = 40;

    }
    else if(axis[0] < -0.5){
        motor1_cmd.mode = MOTOR_FLIP;
        motor1_cmd.flipping_angle = -90;
        motor1_cmd.flipping_speed = 40;

        motor2_cmd.mode = MOTOR_FLIP;;
        motor2_cmd.flipping_angle = -90;
        motor2_cmd.flipping_speed = 40;

        motor3_cmd.mode = MOTOR_FLIP;;
        motor3_cmd.flipping_angle = -90;
        motor3_cmd.flipping_speed = 40;
    }

    else if(axis[1] > 0.5){
        // pitch up

        motor1_cmd.mode = MOTOR_FLIP;;
        motor2_cmd.mode = MOTOR_FLIP;;
        motor3_cmd.mode = MOTOR_FLIP;;

        motor1_cmd.flipping_speed = 40;
        motor2_cmd.flipping_speed = 40;
        motor3_cmd.flipping_speed = 40;

        int angle = -180;
        motor1_cmd.flipping_angle = angle * (head_leg == MOTOR1);
        motor2_cmd.flipping_angle = angle * (head_leg == MOTOR2);
        motor3_cmd.flipping_angle = angle * (head_leg == MOTOR3);

    }

    else if(axis[1] < -0.5){
        // pitch down 
        motor1_cmd.mode = MOTOR_FLIP;;
        motor2_cmd.mode = MOTOR_FLIP;;
        motor3_cmd.mode = MOTOR_FLIP;;

        motor1_cmd.flipping_speed = 40;
        motor2_cmd.flipping_speed = 40;
        motor3_cmd.flipping_speed = 40;

        int angle = -180;
        motor1_cmd.flipping_angle = angle * (head_leg!=1);
        motor2_cmd.flipping_angle = angle * (head_leg!=2);
        motor3_cmd.flipping_angle = angle * (head_leg!=3);

    }
    else{
        // do nothing
        motor1_cmd.flipping_speed = 0;
        motor2_cmd.flipping_speed = 0;
        motor3_cmd.flipping_speed = 0;
    }

    /* Go ahead by flipping */
    if(axis[4] > 0.5){
        motor1_cmd.mode = MOTOR_FLIP;;
        motor2_cmd.mode = MOTOR_FLIP;;
        motor3_cmd.mode = MOTOR_FLIP;;

        motor1_cmd.flipping_speed = 40;
        motor2_cmd.flipping_speed = 40;
        motor3_cmd.flipping_speed = 40;

        switch(head_leg){
            case MOTOR1:
                motor1_cmd.flipping_speed = 0;
                motor2_cmd.flipping_angle = -90;
                motor3_cmd.flipping_angle = 90;
                break;
            case MOTOR2:
                motor1_cmd.flipping_angle = 90;
                motor2_cmd.flipping_speed = 0;
                motor3_cmd.flipping_angle = -90;
                break;
            case MOTOR3:
                motor1_cmd.flipping_angle = -90;
                motor2_cmd.flipping_angle = 90;
                motor3_cmd.flipping_speed = 0;
            default:
                break;
        }
    }

    if(axis[4] < -0.5){
        /* spinning mode */
        motor1_cmd.mode = MOTOR_FLIP;;
        motor2_cmd.mode = MOTOR_FLIP;;
        motor3_cmd.mode = MOTOR_FLIP;;
        int speed = 80;
        
        motor1_cmd.spinning_speed = speed * ( head_leg == 1                     || (head_leg == 2 && buttons[5] == 1) || (head_leg == 3 && buttons[4] == 1));
        motor2_cmd.spinning_speed = speed * ((head_leg == 1 && buttons[4] == 1) ||  head_leg == 2                     || (head_leg == 3 && buttons[5] == 1));
        motor3_cmd.spinning_speed = speed * ((head_leg == 1 && buttons[5] == 1) || (head_leg == 2 && buttons[4] == 1) ||  head_leg == 3);
    }
    else{
        motor1_cmd.spinning_speed = 0;
        motor2_cmd.spinning_speed = 0;
        motor3_cmd.spinning_speed = 0;
    }

}


/* motion on fixed surface such as ground and walls */
void JoyRobot::process_ground(){
    center_cmd.mode = MOTOR_SPIN;
    center_cmd.spinning_speed = 80;

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
    motor1_cmd.mode = MOTOR_SPIN;
    motor1_cmd.spinning_speed = 80*v(0);
    motor2_cmd.mode = MOTOR_SPIN;
    motor2_cmd.spinning_speed = 80*v(1);
    motor3_cmd.mode = MOTOR_SPIN;
    motor3_cmd.spinning_speed = 80*v(2)/1.8;
    cout << v << endl;

}  


int main(int argc, char **argv){

    /* Initialize the node */
    ros::init(argc, argv, "joystick_control");
    JoyRobot robot;

    ros::NodeHandle nh;
    
    int mode = robot.mode;

    
    /* Set up frequency */
    ros::Rate loop_rate(100);

    /* time */
    clock_t t0, t;
    double dt;
    int cum_time = 0;
    t0 = clock();


    while(ros::ok()){
        /* suspend the robot and wait for start command */
        // comment if no joystick
        robot.check_suspend();



        /* Controllers */

        mode = robot.mode;
        cout << mode << endl; 
        /* robot surface motion */
        if(mode == 1) robot.process_ground();
        else robot.process_joystick();


        /* Don't change anything below */
        robot.send_motor_commands();		

        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}


