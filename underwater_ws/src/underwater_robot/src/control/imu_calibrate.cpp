/*
 * This code is intended to calibrate the imu value
 */


#include <iostream>
#include <vector>
#include "Robot.h"

using namespace std;

int main(int argc, char **argv){


	/* Initialize the node */
	ros::init(argc, argv, "imu_calibrate");
	
	Robot robot;
    


    /* Set up the topics */
	robot.publish_motors();
    robot.subscribe_imu();
        
    double target_yaw = 100;

	/* Set up frequency */
	ros::Rate loop_rate(100);
    
    
    //robot.set_spinning_mode();
	/* 
	 * message type explained 
	 * center_motor: Int16 speed
	 * motor_x: Point32 mode, speed, angle
	 */
    while(ros::ok()){
		// suspend the robot and wait for start command
		//robot.check_suspend();
	    	
        robot.print_imu();		
        // interpret position and orientation to make control commands 
        //robot.process_imu_yaw(target_yaw);
        //robot.test_flipping();

		robot.stop_motors();		
        
        ros::spinOnce();
		loop_rate.sleep();
		

	}
	return 0;
}




