
/* Code parameters such as pid errors */
int head_leg; // the leg pointing frontwards 

/* Planar Motion */
bool cruise_mode; // fix the forward speed
int cruise_speed;	
int current_angle;
bool start_straight;
/* switch that controls when to start and end the code */
bool start;

/* PID error */
double last_error;
double cumulate_error;


start = false;
start_straight = false;
cumulate_error = 0;
last_error = 1;
mode = 0;

/* process data methods */
void process_joystick();
void process_Ground();		 
void process_imu_yaw(double set_yaw);	
void test_flipping(); 
void joystick_spin_pid();
void joystick_flip_pid();
void joystick_openloop_straight(int max_straight_speed, int max_adjust_speed);
void joystick_closedloop_straight();
void planar_straight(int speed);
void planar_straight_joystick_adjust(int adjust_speed);
void planar_straight_imu_adjust(int target_yaw);

/* z motion */
void constant_z(int speed);
void joystick_z();
void imu_planar_stable();
void balance_roll();
void balance_pitch();


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
        motor1_cmd.flipping_speed = 40;

        motor2_cmd.mode = 2;
        motor2_cmd.flipping_angle = 90;
        motor2_cmd.flipping_speed = 40;

        motor3_cmd.mode = 2;
        motor3_cmd.flipping_angle = 90;
        motor3_cmd.flipping_speed = 40;

    }
    else if(axis[0] < -0.5){
        motor1_cmd.mode = 2;
        motor1_cmd.flipping_angle = -90;
        motor1_cmd.flipping_speed = 40;

        motor2_cmd.mode = 2;
        motor2_cmd.flipping_angle = -90;
        motor2_cmd.flipping_speed = 40;

        motor3_cmd.mode = 2;
        motor3_cmd.flipping_angle = -90;
        motor3_cmd.flipping_speed = 40;
    }

    else if(axis[1] > 0.5){
        // pitch up

        motor1_cmd.mode = 2;
        motor2_cmd.mode = 2;
        motor3_cmd.mode = 2;

        motor1_cmd.flipping_speed = 40;
        motor2_cmd.flipping_speed = 40;
        motor3_cmd.flipping_speed = 40;

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

        motor1_cmd.flipping_speed = 40;
        motor2_cmd.flipping_speed = 40;
        motor3_cmd.flipping_speed = 40;

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

        motor1_cmd.flipping_speed = 40;
        motor2_cmd.flipping_speed = 40;
        motor3_cmd.flipping_speed = 40;

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

