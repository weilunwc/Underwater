/*
 * This code is intended to use joystick to perform openloop commands
 */


#include <iostream>
#include "Robot.h"

using namespace std;

int main(int argc, char **argv){


	/* Initialize the node */
	ros::init(argc, argv, "joystick_control");
	
	Robot robot;
	robot.publish_motors();
	robot.subscribe_joystick();
    
    robot.set_spinning_mode();

	/* Set up frequency */
	ros::Rate loop_rate(100);
	
	/* 
	 * message type explained 
	 * center_motor: Int16 speed
	 * motor_x: Point32 mode, speed, angle
	 */
	while(ros::ok()){
		// suspend the robot and wait for start command
		robot.check_suspend();
		
		/* interpret position and orientation to make control commands */
		robot.process_joystick();

		robot.send_motor_commands();		
		ros::spinOnce();
		loop_rate.sleep();
		

	}
	
	
	return 0;
}

