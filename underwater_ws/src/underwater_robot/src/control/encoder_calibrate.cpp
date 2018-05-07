/*
 * This code is intended to calibrate the encoders to the origin
 */

#include <iostream>
#include "Robot.h"

using namespace std;

int main(int argc, char **argv){


	/* Initialize the node */
	ros::init(argc, argv, "encoder_calibrate");
	
	Robot robot;
    robot.subscribe_encoder();	

	/* Set up frequency */
	ros::Rate loop_rate(100);
	
	/* 
	 * message type explained 
	 * center_motor: Int16 speed
	 * motor_x: Point32 mode, speed, angle
	 */
	while(ros::ok()){
		/* interpret position and orientation to make control commands */
		robot.print_encoder();
        ros::spinOnce();
		loop_rate.sleep();
	}

    /* Move the flippers to the origin and save the calibrated value */
    robot.save_encoder_calibrate();
    
    return 0;
}

