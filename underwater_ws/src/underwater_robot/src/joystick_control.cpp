/*
 *  This code is intended to use joystick to control the robot openloop
 *  and record sensor info in the localization node
 */

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "Robot.h"
#include "time.h"
#include <std_msgs/Int32.h>

using namespace std;




int main(int argc, char **argv){



    /* Initialize the node */
    ros::init(argc, argv, "joystick_control");
    Robot robot;

    map<string, bool> control_config;
    map<string, bool>::iterator it;

    ros::NodeHandle nh;
    
    nh.getParam("control_configs", control_config);
    
    int mode = robot.mode;

    
    /* Set up the topics */
    /*
       if(control_config["Motor"]){
       robot.publish_motors();
       }
       if(control_config["Encoder"]){
       robot.subscribe_encoder();
       }
       if(control_config["Joy"]){
       robot.subscribe_joystick();   
       }
       if(control_config["Position"]){
       robot.subscribe_pos();   
       }
       if(control_config["Barometer"]){
       robot.subscribe_baro();   
       }
       */

    robot.publish_motors();
    robot.subscribe_joystick();

    /* Take what you need
       robot.publish_motors();
       robot.subscribe_joystick();
       robot.subscribe_imu();
       robot.subscribe_baro();
       robot.subscribe_encoder();
       robot.subscribe_pos();
       */


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

        /* openloop with joystick to do openloop control (basic yaw, pitch) */
        //robot.process_joystick();

        /* tune the motor spinning pid which reacts to the joystick commands */ 
        //robot.joystick_spin_pid();

        /* tune the motor flipping pid which reacts to the joystick commands */ 
        //robot.joystick_flip_pid();
        
        mode = robot.mode;
        cout << mode << endl; 
        /* robot surface motion */
        if(mode == 1) robot.process_Ground();
        else robot.process_joystick();

        /* test imu feedback yaw control*/
        // robot.imu_yaw_control();

        /* robot goes straigt and use joystick to calibrate */
        //int max_straight_speed = 50;
        //int max_adjust_speed = 30;
        //robot.joystick_openloop_straight(max_straight_speed, max_adjust_speed);

        /* robot goes straight and uses Imu to calibrate */
        // robot.joysrick_closedloop_straight();


        /* Z motion */
        /*
           robot.constant_z(60);
           robot.joystick_z();

           t = clock();
           dt = (double)(t -t0)/CLOCKS_PER_SEC;
           if(dt > 1){
           cum_time += dt;
           t0 = clock();
           }

           if(cum_time % 20 > 10){
           robot.balance_roll();
           }
           else{
           robot.balance_pitch();
           }
           */







        /* Don't change anything below */
        robot.send_motor_commands();		

        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}


