#include "Underwater_IMU.h"
#include "Adafruit_Sensor.h"
#include "Adafruit_BNO055.h"
#include <Wire.h>

IMU myIMU;


void setup(){
  Serial.begin(115200);
  myIMU.setup();

}

void loop(){
  euler_data euler;
  euler = myIMU.get_euler_data();
  Serial.print("roll: ");
  Serial.print(euler.roll);
  Serial.print(", pitch: ");
  Serial.print(euler.pitch);
  Serial.print(", yaw: ");
  Serial.println(euler.yaw);
  delay(100);
}
