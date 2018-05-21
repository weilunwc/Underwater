#include <SPI.h>
#include "Underwater_Encoder.h"
//#include <Math.h>
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

    myEncoder.initialize_speed();
}

void loop(){
    myMotor.set_speed(20);
    float angular_speed = myEncoder.read_speed();
    Serial.print("angular speed:"); Serial.println(angular_speed);
}
