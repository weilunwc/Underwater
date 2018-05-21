#include "Underwater_Motor.h"

Motor::Motor(){
    pin = NULL;
    middle = 90;
    min = 0;
    max = 180;

}

Motor::Motor(int pin){
    this->pin = pin;
    motor.attach(pin);
    middle = 90;
    min = 0;
    max = 180;
}
/*
   void Motor::write(int speed){
   motor.write(speed);
   }
   */
void Motor::attach(int pin){
    if(pin == NULL) return;
    motor.attach(pin);
    this->pin = pin;
}

void Motor::write(int speed){
    motor.write(speed);
}


void Motor::set_range(int min,int middle, int max){
    this->middle = middle;
    this->min = min;
    this->max = max;
}
/*
 * set_speed - sets the motor speed. dir > 0 is CW,
 * < 0 is CCW. 0 sets brake
 *
 */
bool Motor::set_speed(int speed){
    if(pin == NULL) return 0;
    if(speed == 0){
        brake();
        return 1;
    }
    int vel = speed + middle;
    if(vel > max) vel = max;
    motor.write(vel);
    return 1;
}

void Motor::brake(){
    motor.write(middle);
}

void Motor::flip(int target_angle, int target_speed, Encoder& myEncoder){
    // the target speed should be positive
    int max_speed = 50;
    if(abs(target_speed) > max_speed) target_speed = max_speed;

    int angle = myEncoder.read_angle();
    int dist = angle - target_angle;
    if(abs(dist) > 180){
        dist = -dist;
    }
    if(dist > 0){
        set_speed(-target_speed);
    }
    else{
        set_speed(target_speed);
    }
}


