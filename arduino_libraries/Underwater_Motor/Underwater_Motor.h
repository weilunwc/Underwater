/*
 *  Underwater_Motor - this library wraps the necessary functions that are necessary
 *  for out underwater project and helps us maintain our code
 */

#include "Arduino.h"
#include "Servo.h"
#include "Underwater_Encoder.h"

#ifndef UNDERWATER_MOTOR_H
#define UNDERWATER_MOTOR_H


class Motor{
public:
  Motor();
  Motor(int);
  void write(int);
  void attach(int);
  void set_range(int,int,int);
  bool set_speed(int);
  void brake();
  void flip(int, int, Encoder&);
  //void write(int);
private:
  // values of the pwm
  int min,middle,max;
  int pin;
  Servo motor;


};

#endif
