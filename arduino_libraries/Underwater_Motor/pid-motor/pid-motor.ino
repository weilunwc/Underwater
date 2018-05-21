nclude <Servo.h>
#include "Underwater_Motor.h"
#include "Underwater_Encoder.h"
#include <SPI.h>

float pi = 3.1415926;
Motor myMotor;
Encoder myEncoder;

int prev_angle;
int t0;
//Servo myMotor;
void setup(){
		Serial.begin(9600);
		myMotor.attach(3);
		myEncoder.attach(2);
		myEncoder.set_offset(754);
		prev_angle = myEncoder.read_angle();
		//myMotor.set_range(0,91,91+88);
		t0 = millis();
}

float deg2rad(float deg){
		return deg*pi/180.0;
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
		int t1 = millis();
		int dt = t1 - t0;
		t0 = t1;
		int value = myEncoder.read_value();
		int angle = myEncoder.read_angle(); 
		float delta_angle = angle - prev_angle;
		prev_angle = angle;
		if(prev_angle*angle <0){
			delta_angle = 180 - prev_angle + angle - (-180);
		}
		float angle_speed = 1000*delta_angle/(float)dt;
		angle_speed = deg2rad(angle_speed); 
		//Serial.print("encoder
		//value is: ");
		//Serial.println(value);
		//Serial.print("encoder
		//angle is: ");
		//Serial.println(angle);
		//Serial.print("dt:
		//");Serial.println(dt);
		Serial.print("delta angle is :");
		Serial.println(delta_angle);
		Serial.print("angle speed is:");
		Serial.println(angle_speed);
		myMotor.set_speed(30);
		myMotor.brake();
		//delay(dt);
		// Serial.println(myMotor.pin);
}
