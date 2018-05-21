#include <Servo.h>
#include "Underwater_Motor.h"
#include "Underwater_Encoder.h"
#include <SPI.h>


Motor myMotor;
//Servo myMotor;
void setup(){
  Serial.begin(9600);
  myMotor.attach(3);
  myMotor.set_range(0,91,91+88);
}

void loop(){
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
	*/
  myMotor.brake();
	delay(3000);
	// Serial.println(myMotor.pin);
}
