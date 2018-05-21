#include <SPI.h>
#include "Underwater_Encoder.h"
#include "Underwater_Motor.h"
#include <Servo.h>

Encoder myEncoder;
Motor myMotor;

int prev_angle;
int max_speed;
int t0;
void setup(){
		Serial.begin(9600);
		myEncoder.attach(2);
		myEncoder.set_offset(495);
		myMotor.attach(3);
		prev_angle = myEncoder.read_angle();
		max_speed = 180;
		t0 = millis();
}

void loop(){
		myMotor.set_speed(20);
		int value = myEncoder.read_value();
		int angle = myEncoder.read_angle();
		float delta_angle = angle - prev_angle;
		if(abs(delta_angle) > max_speed){
				if(angle < 0)delta_angle = 360 + delta_angle;
				else delta_angle = 360 - delta_angle;
		}

		int t1 = millis();
		float dt = t1 - t0;
		float w = 1000*delta_angle/dt;
		Serial.print("prev angle: ");Serial.print(prev_angle);
		Serial.print("\t angle: ");Serial.print(angle);
		Serial.print("\t delta angle:");Serial.print(delta_angle);
		Serial.print("\tangular velocity:");Serial.println(w);

		t0 = t1;
		prev_angle = angle;
}
