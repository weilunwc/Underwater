/*
 * This code is intended to use imu to control yaw motion in planar pose 
 */


#include <iostream>
#include <vector>
#include "Robot.h"

using namespace std;

class ImuRobot: public Robot{
    public:
        void process_imu_yaw(double set_yaw);
};


/* Read the imu yaw and control */
void ImuRobot::process_imu_yaw(double set_yaw){

    double pwm=0.0;
    double thresh =1.0;

    double ddiff=0.0;
    double idiff=0.0;
    double diff_prev=0.0;
    int flip_angle= 60;

    // Give dummy height and set height
    // Eventually height will be read form barometer

    double diff=(double)set_yaw-euler.yaw;

    if (fabs(diff)<=thresh){

        motor1_cmd.mode = 0;
        motor2_cmd.mode = 0;
        motor3_cmd.mode = 0;

    }
    else
    {
        //Proportional gain K_p, Derivative gain K_d, Integrating Gain K_i
        double K_p=2;
        double K_d=0.5;
        double K_i=0.1;

        diff=(double)set_yaw-euler.yaw;
        if(diff > 180){
            diff = diff - 360;
        }
        else if (diff<-180){
            diff=diff+360;
        }
        ddiff=(double)(diff-diff_prev);
        idiff=(double) diff+ddiff;

        // Update pwd for proportional gain controller
        pwm = (double) K_p*diff+K_d*ddiff+K_i*idiff;
        diff_prev=diff;
        // Edge case
        if (pwm>=40.0){
            pwm=40.0;}

        else if (pwm<=-40.0){
            pwm=-40.0;}
        else if (fabs(pwm)<=15.0){
            pwm=15.0;}
        if (pwm>=0){
            for (int i=0; i <= 20; i++){
                motor1_cmd.mode = 2;
                // motor1_cmd.spinning_speed = 0;
                motor1_cmd.flipping_angle = flip_angle;
                motor1_cmd.flipping_speed = pwm;

                motor2_cmd.mode = 2;
                //motor2_cmd.spinning_speed = 0;
                motor2_cmd.flipping_angle = flip_angle;
                motor2_cmd.flipping_speed = pwm;

                motor3_cmd.mode = 2;
                //motor3_cmd.spinning_speed = 0;
                motor3_cmd.flipping_angle = flip_angle;
                motor3_cmd.flipping_speed = pwm;
                //usleep(20);
            }
        }
        else{
            for (int i=0; i <= 20; i++){
                motor1_cmd.mode = 2;
                // motor1_cmd.spinning_speed = 0;
                motor1_cmd.flipping_angle = -flip_angle;
                motor1_cmd.flipping_speed = fabs(pwm);

                motor2_cmd.mode = 2;
                //motor2_cmd.spinning_speed = 0;
                motor2_cmd.flipping_angle = -flip_angle;
                motor2_cmd.flipping_speed = fabs(pwm);

                motor3_cmd.mode = 2;
                //motor3_cmd.spinning_speed = 0;
                motor3_cmd.flipping_angle = -flip_angle;
                motor3_cmd.flipping_speed = fabs(pwm);
                //usleep(20);
            }

        }

        print_motor_commands();	
    }
}



int main(int argc, char **argv){


	/* Initialize the node */
	ros::init(argc, argv, "imu_yaw_control");
	
	ImuRobot robot;
    


        
    double target_yaw = 200;

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
        robot.process_imu_yaw(target_yaw);
        //robot.test_flipping();

		robot.send_motor_commands();		
        
        ros::spinOnce();
		loop_rate.sleep();
		

	}
    cout << "fjidf" << endl;	
	return 0;
}




