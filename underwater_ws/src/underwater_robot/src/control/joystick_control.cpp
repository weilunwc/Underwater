/*
 *  This code is intended to use joystick to control the robot openloop
 *  and record sensor info in the localization node
 */

#include <iostream>
#include <vector>
#include "Robot.h"

using namespace std;

int main(int argc, char **argv){

	/* Initialize the node */
	ros::init(argc, argv, "joystick_control");
	Robot robot;

    /* Set up the topics */
	robot.publish_motors();
    robot.subscribe_joystick();   

	/* Set up frequency */
	ros::Rate loop_rate(100);
    
    while(ros::ok()){
		/* suspend the robot and wait for start command */
		robot.check_suspend();
        
        /* openloop with joystick to do openloop control (basic yaw, pitch) */
        //robot.process_joystick();
        
        /* tune the motor spinning pid which reacts to the joystick commands */ 
        //robot.joystick_spin_pid();
        
        /* tune the motor flipping pid which reacts to the joystick commands */ 
        robot.joystick_flip_pid();
        
		robot.send_motor_commands();		
        
        ros::spinOnce();
		loop_rate.sleep();
	}
	
    return 0;
}


