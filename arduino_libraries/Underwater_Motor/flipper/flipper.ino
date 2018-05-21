#include "Underwater_Motor.h"
#include <Servo.h>

#include <SPI.h>
#include "Underwater_Encoder.h"

#define motor_pin 3
#define encoder_pin 2


/* Our actuators and sensors */
Motor myMotor;
Encoder myEncoder;

/* setup the using functions */
//void flip(int target_angle, unsigned int target_speed);

/*
void flip(int target_angle, unsigned int target_speed){
  int angle = myEncoder.read_angle();
  int dist = angle - target_angle;
  Serial.print("angle: ");Serial.println(angle);
  if(abs(dist) > 180){
    dist = -dist;
  }
  if(dist > 0){
    myMotor.set_speed(-target_speed);
  }
  else{
    myMotor.set_speed(target_speed);
  }
}
*/

void setup(){
  Serial.begin(9600);
  myMotor.attach(motor_pin);
  myEncoder.attach(encoder_pin);
  myEncoder.set_offset(1963);
}

void loop(){
  int angle = myEncoder.read_angle();
  Serial.print("angle: ");Serial.println(angle);
  myMotor.flip(-100,15,myEncoder);
  delay(20);
}






