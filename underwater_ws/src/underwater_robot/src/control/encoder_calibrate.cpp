/*
 * This code is intended to calibrate the encoders to the origin
 */


#include <iostream>
#include <fstream>

#include <ros/ros.h>
#include <std_msgs/Int32.h>

using namespace std;


int encoder1, encoder2, encoder3;


void read_encoder1(const std_msgs::Int32 &msg){
    encoder1 = msg.data;
}
void read_encoder2(const std_msgs::Int32 &msg){
    encoder2 = msg.data;
}
void read_encoder3(const std_msgs::Int32 &msg){
    encoder3 = msg.data;
}

int main(int argc, char **argv){

    encoder1 = encoder2 = encoder3 = 0;

	/* Initialize the node */
	ros::init(argc, argv, "encoder_calibrate");
    
    ros::NodeHandle n;
    ros::Subscriber enc1_sub, enc2_sub, enc3_sub;
    enc1_sub = n.subscribe("encoder1_cal", 10, read_encoder1);
    enc2_sub = n.subscribe("encoder2_cal", 10, read_encoder2);
    enc3_sub = n.subscribe("encoder3_cal", 10, read_encoder3);

	/* Set up frequency */
	ros::Rate loop_rate(10);
	
    while(ros::ok()){
        cout << encoder1 << "\t" << encoder2 << "\t" << encoder3 << endl;
        
        ros::spinOnce();
		loop_rate.sleep();
	}

    /* Move the flippers to the origin and save the calibrated value */
    ofstream myFile;
    myFile.open("/home/william/Underwater/underwater_ws/src/underwater_robot/utilities/encoder_calibrate.txt");
    myFile << encoder1 << "\n" << encoder2 << "\n" << encoder3;
    myFile.close();
    cout << "saved\n";
    

    return 0;
}

