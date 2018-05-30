#include "Robot.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <Eigen/Dense>
using namespace std;

Robot::Robot(){
    start = false;
    start_straight = false;
    cumulate_error = 0;
    last_error = 1;
}

/* Motors */
void Robot::publish_motors(){
    center_motor_pub = n.advertise<underwater_msg::Cmd>("center_motor",10);
    motor_1_pub = n.advertise<underwater_msg::Cmd>("motor_1",10);
    motor_2_pub = n.advertise<underwater_msg::Cmd>("motor_2",10);
    motor_3_pub = n.advertise<underwater_msg::Cmd>("motor_3",10);
}

void Robot::send_motor_commands(){
    center_motor_pub.publish(center_cmd);
    motor_1_pub.publish(motor1_cmd);
    motor_2_pub.publish(motor2_cmd);
    motor_3_pub.publish(motor3_cmd);
}

void Robot::stop_motors(){

    center_cmd.mode = 0;
    motor1_cmd.mode = 0;
    motor2_cmd.mode = 0;
    motor3_cmd.mode = 0;

    send_motor_commands();
}

void Robot::print_motor_commands(){
    printf("center: mode %d, spinning speed %d\n", center_cmd.mode, center_cmd.spinning_speed);
    printf("motor1: mode %d, spinning speed %d, flipping angle %d, flipping speed %d\n",
            motor1_cmd.mode, motor1_cmd.spinning_speed, motor1_cmd.flipping_angle, motor1_cmd.flipping_speed);
    printf("motor2: mode %d, spinning speed %d, flipping angle %d, flipping speed %d\n",
            motor2_cmd.mode, motor2_cmd.spinning_speed, motor2_cmd.flipping_angle, motor2_cmd.flipping_speed);
    printf("motor3: mode %d, spinning speed %d, flipping angle %d, flipping speed %d\n\n",
            motor3_cmd.mode, motor3_cmd.spinning_speed, motor3_cmd.flipping_angle, motor3_cmd.flipping_speed);
}

/* IMU */
void Robot::subscribe_imu(){
    imu_sub = n.subscribe("imu", 1000, &Robot::read_imu, this);
}

void Robot::read_imu(const underwater_msg::Imu &euler_info){
    roll = euler_info.roll;
    pitch = euler_info.pitch;
    yaw = euler_info.yaw;
}

void Robot::print_imu(){
    ROS_INFO("roll, pitch, yaw: %lf,\t%lf,\t%lf",roll,pitch,yaw);
}

/* Barometer */
void Robot::subscribe_baro(){
    depth = 0;
    temp = 0;
    baro_sub = n.subscribe("barometer", 100, &Robot::read_baro, this);
}

void Robot::read_baro(const underwater_msg::Baro &baro_info){
    depth = baro_info.depth;
    temp = baro_info.temp;
}

void Robot::print_baro(){
    ROS_INFO("depth: %lf, temp = %lf\n", depth, temp);
}

/* Joystick */
void Robot::subscribe_joystick(){
    head_leg = 1;

    joy_sub = n.subscribe("joy", 1000, &Robot::read_joystick, this);
    buttons.resize(11);
    prev_buttons.resize(11);
    axis.resize(8);
    for(int i = 0;i < 8;i++){
        axis[i] = 0;
    }
    for(int i = 0;i < 11;i++){
        buttons[i] = 0;
        prev_buttons[i] = 0;
    }
    cruise_mode = false;
    cruise_speed = 0;
}

void Robot::read_joystick(const sensor_msgs::Joy &joyInfo){
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
    
    /* determine head leg */
    if(buttons[3] == 1) head_leg = 1; // Y
    if(buttons[2] == 1) head_leg = 2; // X
    if(buttons[1] == 1) head_leg = 3; // B

}

void Robot::print_joystick(){
    for(int i = 0;i < 11;i++){
        cout << buttons[i] << " ";
    }
    cout << endl;
}

/* Position */
void Robot::subscribe_pos(){
    pos_sub = n.subscribe("position", 100, &Robot::read_pos, this);
}

void Robot::read_pos(const geometry_msgs::Point32 &pos_info){
    position.x = pos_info.x;
    position.y = pos_info.y;
    position.z = pos_info.z;
}

void Robot::print_pos(){
    printf("Position x: %lf, y: %lf, z:%lf", position.x, position.y, position.z);    
}

/* Encoder Information */
void Robot::subscribe_encoder(){
    encoder1_cal = 0;
    encoder2_cal = 0;
    encoder3_cal = 0;

    enc1_cal_sub = n.subscribe("encoder1_cal", 100, &Robot::read_encoder1, this);
    enc2_cal_sub = n.subscribe("encoder2_cal", 100, &Robot::read_encoder2, this);
    enc3_cal_sub = n.subscribe("encoder3_cal", 100, &Robot::read_encoder3, this);
}

void Robot::read_encoder1(const std_msgs::Int32 &encoder1_msg){
    encoder1_cal = encoder1_msg.data;    
}

void Robot::read_encoder2(const std_msgs::Int32 &encoder2_msg){
    encoder2_cal = encoder2_msg.data;    
}

void Robot::read_encoder3(const std_msgs::Int32 &encoder3_msg){
    encoder3_cal = encoder3_msg.data;    
}

void Robot::print_encoder(){
    ROS_INFO("%d\t%d\t%d", encoder1_cal, encoder2_cal, encoder3_cal);
}

void Robot::save_encoder_calibrate(){
    ofstream myfile;
    //myfile.open(file_name.c_str());
    myfile.open("/home/william/Underwater/underwater_ws/src/underwater_robot/utilities/encoder_calibrate.txt");
    myfile << encoder1_cal << "\n" << encoder2_cal << "\n" << encoder3_cal;
    myfile.close();
    cout << "saved " << endl;
}

vector<int> Robot::load_encoder_calibrate(){
    ifstream myfile;
    string line;
    myfile.open("/home/william/Underwater/underwater_ws/src/underwater_robot/utilites/encoder_calibrate.txt");
    vector<int> offset;
    if(myfile.is_open()){
        //getline(myfile, line);
        //cout << line << endl;
        myfile >> encoder1_cal;
        myfile >> encoder2_cal;
        myfile >> encoder3_cal;
        /*
        cout << encoder1_cal << ", ";
        cout << encoder2_cal << ", ";
        cout << encoder3_cal << endl;
        */
        offset.push_back(encoder1_cal);
        offset.push_back(encoder2_cal);
        offset.push_back(encoder3_cal);

        myfile.close();
        return offset;
    }
    else{
        cout << "No calibration file" << endl;
        exit(0);
    }

    return offset;
}

/* Set a switch that activates and deactivates the system */
void Robot::check_suspend(){
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


/* Set Mode of the motors */
void Robot::set_spinning_mode(){
    center_cmd.mode = 1;
    motor1_cmd.mode = 1;
    motor2_cmd.mode = 1;
    motor3_cmd.mode = 1;
}


void Robot::set_flipping_mode(){
    // center motor can't flip, shut it down
    center_cmd.mode = 0;
    motor1_cmd.mode = 1;
    motor2_cmd.mode = 1;
    motor3_cmd.mode = 1;
}


/* Control methods */

void Robot::test_flipping(){
    center_cmd.mode = 0;

    motor1_cmd.mode = 2;
    motor1_cmd.flipping_angle = 90;
    motor1_cmd.flipping_speed = 20;

    motor2_cmd.mode = 2;
    motor2_cmd.flipping_angle = 90;
    motor2_cmd.flipping_speed = 20;

    motor3_cmd.mode = 2;
    motor3_cmd.flipping_angle = 90;
    motor3_cmd.flipping_speed = 20;

}



/* Read the imu yaw and control */
void Robot::process_imu_yaw(double set_yaw){

    double pwm=0.0;
    double thresh =1.0;

    double ddiff=0.0;
    double idiff=0.0;
    double diff_prev=0.0;
    int flip_angle= 60;

    // Give dummy height and set height
    // Eventually height will be read form barometer

    double diff=(double)set_yaw-yaw;

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

        diff=(double)set_yaw-yaw;
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

/* Process sensor signal to control command 
 * Basic Openloop Control 
 */

void Robot::process_Ground(){
    center_cmd.mode = 1;
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

    center_cmd.mode = 1;
    double fx = -1*axis[0];
    double fy = axis[1];
    double dtheta = -1*axis[3];

    v << fx, fy, dtheta;
    v = m*v;
    motor1_cmd.mode = 1;
    motor1_cmd.spinning_speed = 80*v(0);
    motor2_cmd.mode = 1;
    motor2_cmd.spinning_speed = 80*v(1);
    motor3_cmd.mode = 1;
    motor3_cmd.spinning_speed = 80*v(2)/1.8;
    cout << v << endl;

}  
void Robot::process_joystick(){
    /* center motor */    
    center_cmd.mode = 1;
    if(axis[2] != 1){
        center_cmd.spinning_speed = 85*(1-axis[2])/2;
    }
    else if(axis[5]!=1){
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
        motor1_cmd.mode = 2;
        motor1_cmd.flipping_angle = 90;
        motor1_cmd.flipping_speed = 30;

        motor2_cmd.mode = 2;
        motor2_cmd.flipping_angle = 90;
        motor2_cmd.flipping_speed = 30;

        motor3_cmd.mode = 2;
        motor3_cmd.flipping_angle = 90;
        motor3_cmd.flipping_speed = 30;

    }
    else if(axis[0] < -0.5){
        motor1_cmd.mode = 2;
        motor1_cmd.flipping_angle = -90;
        motor1_cmd.flipping_speed = 30;

        motor2_cmd.mode = 2;
        motor2_cmd.flipping_angle = -90;
        motor2_cmd.flipping_speed = 30;

        motor3_cmd.mode = 2;
        motor3_cmd.flipping_angle = -90;
        motor3_cmd.flipping_speed = 30;
    }

    else if(axis[1] > 0.5){
        // pitch up

        motor1_cmd.mode = 2;
        motor2_cmd.mode = 2;
        motor3_cmd.mode = 2;

        motor1_cmd.flipping_speed = 30;
        motor2_cmd.flipping_speed = 30;
        motor3_cmd.flipping_speed = 30;

        int angle = -180;
        motor1_cmd.flipping_angle = angle * (head_leg==1);
        motor2_cmd.flipping_angle = angle * (head_leg==2);
        motor3_cmd.flipping_angle = angle * (head_leg==3);


    }
    else if(axis[1] < -0.5){
        // pitch down 
        motor1_cmd.mode = 2;
        motor2_cmd.mode = 2;
        motor3_cmd.mode = 2;

        motor1_cmd.flipping_speed = 30;
        motor2_cmd.flipping_speed = 30;
        motor3_cmd.flipping_speed = 30;

        int angle = -180;
        motor1_cmd.flipping_angle = angle * (head_leg!=1);
        motor2_cmd.flipping_angle = angle * (head_leg!=2);
        motor3_cmd.flipping_angle = angle * (head_leg!=3);

    }
    else{
        motor1_cmd.flipping_speed = 0;
        motor2_cmd.flipping_speed = 0;
        motor3_cmd.flipping_speed = 0;
    }

    /* Go ahead by flipping */
    if(axis[4] > 0.5){
        motor1_cmd.mode = 2;
        motor2_cmd.mode = 2;
        motor3_cmd.mode = 2;

        motor1_cmd.flipping_speed = 30;
        motor2_cmd.flipping_speed = 30;
        motor3_cmd.flipping_speed = 30;

        switch(head_leg){
            case 1:
                motor1_cmd.flipping_speed = 0;
                motor2_cmd.flipping_angle = -90;
                motor3_cmd.flipping_angle = 90;
                break;
            case 2:
                motor1_cmd.flipping_angle = 90;
                motor2_cmd.flipping_speed = 0;
                motor3_cmd.flipping_angle = -90;
                break;
            case 3:
                motor1_cmd.flipping_angle = -90;
                motor2_cmd.flipping_angle = 90;
                motor3_cmd.flipping_speed = 0;
            default:
                break;
        }
    }

    if(axis[4] < -0.5){
        /* spinning mode */
        motor1_cmd.mode = 1;
        motor2_cmd.mode = 1;
        motor3_cmd.mode = 1;
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

void Robot::joystick_spin_pid(){
    center_cmd.mode = 0;
    motor1_cmd.mode = (head_leg == 1);
    motor2_cmd.mode = (head_leg == 2);
    motor3_cmd.mode = (head_leg == 3);
    /* spinning mode */
    float max_speed = 330;
    float speed = axis[0]*max_speed;
    motor1_cmd.spinning_speed = speed;
    motor2_cmd.spinning_speed = speed;
    motor3_cmd.spinning_speed = speed;
}

void Robot::joystick_flip_pid(){
    center_cmd.mode = 0;
    motor1_cmd.mode = 2;
    motor2_cmd.mode = 2;
    motor3_cmd.mode = 2;
    /* spinning mode */
    float max_speed = 330;
    float speed = fabs(axis[0])*max_speed;
    motor1_cmd.flipping_angle = 0;
    motor2_cmd.flipping_angle = 0;
    motor3_cmd.flipping_angle = 0;

    motor1_cmd.flipping_speed = speed*(head_leg == 1);
    motor2_cmd.flipping_speed = speed*(head_leg == 2);
    motor3_cmd.flipping_speed = speed*(head_leg == 3);
}

/* Go straight and use joystick to keep headings straight */
void Robot::joystick_openloop_straight(int max_straight_speed, int max_adjust_speed){
    
    /* go striaght */
    int speed;
    if(cruise_mode) speed = cruise_speed;
    else speed = fabs(axis[4])*50;
    planar_straight(speed);
    
    /* adjust using joystick */
    int adjust_speed = axis[0]*30;
    planar_straight_joystick_adjust(adjust_speed);
    
    /* check cruise mode */
    if(prev_buttons[10] != buttons[10]){
        cruise_mode = !cruise_mode;
        cruise_speed = speed;
        cout << "cruise mode " << cruise_mode << endl;

    }
}

/* Go straight and use imu to keep headings straight */
void Robot::joystick_closedloop_straight(){
    
    /* go striaght */
    int speed;
    if(axis[4] > 0.2){
        if(start_straight == false){
            // save the current angle as the coursing angle
            start_straight = true;
            current_angle = yaw;
        }
        speed = axis[4]*50; 
        planar_straight(speed);
        
        /* adjust using imu */
        int target_yaw = current_angle + 90 * head_leg;
        if(target_yaw > 360) target_yaw -= 360;
        planar_straight_imu_adjust(target_yaw);
    }
    else{
        start_straight = false;
        speed = 0;
    }

}

/* planar motion : go straight */
void Robot::planar_straight(int speed){
    
    /* Go straight */
    center_cmd.mode = 0;
    motor1_cmd.mode = 2;
    motor2_cmd.mode = 2;
    motor3_cmd.mode = 2;
    
    motor1_cmd.flipping_speed = speed;
    motor2_cmd.flipping_speed = speed;
    motor3_cmd.flipping_speed = speed;
    
    switch(head_leg){
        case 1:
            motor1_cmd.flipping_speed = 0;
            motor2_cmd.flipping_angle = -90;
            motor3_cmd.flipping_angle = 90;
            break;
        case 2:
            motor1_cmd.flipping_angle = 90;
            motor2_cmd.flipping_speed = 0;
            motor3_cmd.flipping_angle = -90;
            break;
        case 3:
            motor1_cmd.flipping_angle = -90;
            motor2_cmd.flipping_angle = 90;
            motor3_cmd.flipping_speed = 0;
        default:
            break;
    }
}


/* Use joystick to control the head leg to adjust course angle */
void Robot::planar_straight_joystick_adjust(int adjust_speed){

    int adjust_angle = adjust_speed > 0 ? 90 : -90;
    adjust_speed = fabs(adjust_speed);
    switch(head_leg){
        case 1:
            motor1_cmd.flipping_speed = adjust_speed;
            motor1_cmd.flipping_angle = adjust_angle;
            break;
        case 2:
            motor2_cmd.flipping_speed = adjust_speed;
            motor2_cmd.flipping_angle = adjust_angle;
            break;
        case 3:
            motor3_cmd.flipping_speed = adjust_speed;
            motor3_cmd.flipping_angle = adjust_angle;
            break;
        default:
            break;
    }
}

/* Use Imu feedback to control the head leg to adjust course angle */
void Robot::planar_straight_imu_adjust(int target_yaw){
    
    /* Use the head leg to adjust course angle */
    int error = yaw - target_yaw;
    int adjust_angle = error > 0 ? 90 : -90;
    int adjust_speed = 30;
    switch(head_leg){
        case 1:
            motor1_cmd.flipping_speed = adjust_speed;
            motor1_cmd.flipping_angle = adjust_angle;
            break;
        case 2:
            motor2_cmd.flipping_speed = adjust_speed;
            motor2_cmd.flipping_angle = adjust_angle;
            break;
        case 3:
            motor3_cmd.flipping_speed = adjust_speed;
            motor3_cmd.flipping_angle = adjust_angle;
            break;
        default:
            break;
    }
}

void Robot::constant_z(int target_speed){
    center_cmd.mode = 1; 
    center_cmd.spinning_speed = target_speed; 
}

void Robot::joystick_z(){
    center_cmd.mode = 1;
    if(axis[2] != 1){
        center_cmd.spinning_speed = 85*(1-axis[2])/2;
    }
    else if(axis[5]!=1){
        center_cmd.spinning_speed = -85*(1-axis[5])/2;
    }
    else{
        center_cmd.spinning_speed = 0;
    }
    
}

void Robot::balance_roll(){
}

void Robot::balance_pitch(){
}
/* PID reference 
void Robot::basic_pid(int target){

    double true_value = imu.read();
    double error = target - true_value;
    
    cumulate_error += error;
    double del_error = error - last_error;
    double P,I,D;
    double usage = P*error + I * cumulate_error + D * del_error;

    last_error = error;

}
*/

