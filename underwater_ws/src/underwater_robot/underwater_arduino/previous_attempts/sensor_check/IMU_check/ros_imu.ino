#include "Underwater_IMU.h"
#include "Adafruit_Sensor.h"
#include "Adafruit_BNO055.h"
#include <Wire.h>
#include <ros.h>
#include <geometry_msgs/Point32.h>

IMU myIMU;

ros::NodeHandle nh;
geometry_msgs::Point32 imu_msg;
ros::Publisher p("imu", &imu_msg);

void setup(){
  //Serial.begin(115200);
  nh.initNode();
  nh.advertise(p);
  myIMU.setup();

}

void loop(){
  euler_data euler;
  euler = myIMU.get_euler_data();
  /*
  Serial.print("roll: ");
  Serial.print(euler.roll);
  Serial.print(", pitch: ");
  Serial.print(euler.pitch);
  Serial.print(", yaw: ");
  Serial.println(euler.yaw);
  */
  imu_msg.x = euler.roll;
  imu_msg.y = euler.pitch;
  imu_msg.z = euler.yaw;
  p.publish(&imu_msg);
  nh.spinOnce();
  delay(100);
}
