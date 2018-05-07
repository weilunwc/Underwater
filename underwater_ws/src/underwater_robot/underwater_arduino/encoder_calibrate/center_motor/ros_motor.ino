#include <Servo.h>
#include "Underwater_Motor.h"
#include "Underwater_Encoder.h"
#include <SPI.h>
#include <ros.h>
#include <std_msgs/Int16.h>
// simply do nothing
//Servo myMotor;
void setup(){

}

void loop(){

  delay(100);
  /*
  int pos;
  for(pos = 0; pos < 80;pos+=1){
    myMotor.set_speed(pos);
    delay(15);
  }
  for(pos = 80; pos > 0;pos--){
    myMotor.set_speed(pos);
    delay(15);
  }
  myMotor.brake();
  delay(3000);
  // Serial.println(myMotor.pin);
  */
}
