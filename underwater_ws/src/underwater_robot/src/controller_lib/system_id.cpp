/*
 *  This code is intended to do system identification on paramters
 */

#include <iostream>
#include <vector>
#include <string>
#include "Robot.h"
#include "time.h"

using namespace std;

class SysRobot: public Robot{
    public:
        SysRobot();
        void check_suspend();
        void check_joystick();
        void spin_test(int speed);
        void flip_test(int speed);
        bool start; // suspend system
};

SysRobot::SysRobot(){
    setup();
    start = false;
}

/* Set a switch that activates and deactivates the system */
void SysRobot::check_suspend(){
    if(!start){
        ros::Rate loop_rate(10);
        while(ros::ok()){
            //ROS_INFO("suspend");
            stop_motors();
            ros::spinOnce();
            check_joystick();
            loop_rate.sleep();
            if(start) break;
        }
    }
}

/* override tha base read_joystick and add switch modes */
void SysRobot::check_joystick(){
    /* use these two buttons as a switch to activate robot*/
    if(buttons[8] == 1){
        start = true;
        cout << "start system" << endl;
    }
    if(buttons[6] == 1) {
        start = false;
        cout << "suspend system" << endl;
    }
    
}


void SysRobot::flip_test(int speed){
    motor1_cmd.mode = MOTOR_FLIP;
    motor2_cmd.mode = MOTOR_FLIP;
    motor3_cmd.mode = MOTOR_FLIP;
   
    motor1_cmd.flipping_angle = 0;
    motor2_cmd.flipping_angle = 0;
    motor3_cmd.flipping_angle = 0;

    motor1_cmd.flipping_speed = speed;
    motor2_cmd.flipping_speed = speed;
    motor3_cmd.flipping_speed = speed;
}

void SysRobot::spin_test(int speed){
    motor1_cmd.mode = MOTOR_SPIN;
    motor2_cmd.mode = MOTOR_SPIN;
    motor3_cmd.mode = MOTOR_SPIN;
    
    motor1_cmd.spinning_speed = speed;
    motor2_cmd.spinning_speed = speed;
    motor3_cmd.spinning_speed = speed;
}


int main(int argc, char **argv){

    /* Initialize the node */
    ros::init(argc, argv, "system_id");
    SysRobot robot;

    /* Set up frequency */
    ros::Rate loop_rate(100);
    
    string type= "flip";
    int speed = 10;

    while(ros::ok()){
        /* suspend the robot and wait for start command */
        // comment if no joystick
        robot.check_suspend();
        
        // read the joystick values to deterimine mode
        robot.check_joystick();
        
        if(type == "flip") robot.flip_test(speed);
        else if(type == "spin") robot.spin_test(speed);
    
        /* Don't change anything below */
        robot.send_motor_commands();		

        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}


