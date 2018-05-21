/*
 * This code is intended to calibrate barometer readings 
 */




#include <iostream>
#include <vector>
#include "Robot.h"

using namespace std;

int main(int argc, char **argv){


	/* Initialize the node */
	ros::init(argc, argv, "baro_calibrate");
	
	Robot robot;

    /* Set up the topics */
	robot.publish_motors();
    robot.subscribe_baro();

	/* Set up frequency */
	ros::Rate loop_rate(10);
    
	/* 
	 * message type explained 
	 * center_motor: Int16 speed
	 * motor_x: Point32 mode, speed, angle
	 */
    while(ros::ok()){
		// suspend the robot and wait for start command
		//robot.check_suspend();
	    	
        // interpret position and orientation to make control commands 
        robot.print_baro();
		robot.stop_motors();		
        
        ros::spinOnce();
		loop_rate.sleep();
		
	}
	
    return 0;
}




