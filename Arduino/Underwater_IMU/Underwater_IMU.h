#include "Arduino.h"
#include "Adafruit_Sensor.h"
#include "Adafruit_BNO055.h"
#include "utility/imumaths.h"

#ifndef UNDERWATER_IMU_H
#define UNDERWATER_IMU_H


typedef struct{
  float roll,pitch,yaw;
}euler_data;


class IMU {
public:
	IMU() {};
	void setup();
	// sensor details such as what sensor and id
	void display_sensor_details();
	sensor_t get_sensor_details();

  // basic sensor data info such as roll pitch yaw
	void display_sensor_data(void);
	sensors_event_t get_sensor_data();

  // sensor status such as calib info
	void display_sensor_status(void);
	void display_cal_status(void);

  euler_data get_euler_data();

private:
	Adafruit_BNO055 imu;
};

void IMU::setup() {
	imu = Adafruit_BNO055(55);
	if (!imu.begin()) {
		Serial.print("Not detected, check I2C pins");
		while (1);
	}
	delay(1000);
	imu.setExtCrystalUse(true);

	/* Display some basic information on this sensor */
	display_sensor_details();

	/* Optional: Display current status */
	display_sensor_status();

	imu.setExtCrystalUse(true);

}


/**************************************************************************/
/*
Displays some basic information on this sensor from the unified
sensor API sensor_t type (see Adafruit_Sensor for more information)
*/
/**************************************************************************/
void IMU::display_sensor_details(void) {
	sensor_t sensor;
	imu.getSensor(&sensor);
	Serial.println("------------------------------------");
	Serial.print("Sensor:       "); Serial.println(sensor.name);
	Serial.print("Driver Ver:   "); Serial.println(sensor.version);
	Serial.print("Unique ID:    "); Serial.println(sensor.sensor_id);
	Serial.print("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" xxx");
	Serial.print("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" xxx");
	Serial.print("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" xxx");
	Serial.println("------------------------------------");
	Serial.println("");
	delay(500);
}


/**************************************************************************/
/*
Display some basic info about the sensor status
*/
/**************************************************************************/
void IMU::display_sensor_status(void)
{
	/* Get the system status values (mostly for debugging purposes) */
	uint8_t system_status, self_test_results, system_error;
	system_status = self_test_results = system_error = 0;
	imu.getSystemStatus(&system_status, &self_test_results, &system_error);

	/* Display the results in the Serial Monitor */
	Serial.println("");
	Serial.print("System Status: 0x");
	Serial.println(system_status, HEX);
	Serial.print("Self Test:     0x");
	Serial.println(self_test_results, HEX);
	Serial.print("System Error:  0x");
	Serial.println(system_error, HEX);
	Serial.println("");
	delay(500);
}


/**************************************************************************/
/*
Display sensor calibration status
*/
/**************************************************************************/
void IMU::display_cal_status(void)
{
	/* Get the four calibration values (0..3) */
	/* Any sensor data reporting 0 should be ignored, */
	/* 3 means 'fully calibrated" */
	uint8_t system, gyro, accel, mag;
	system = gyro = accel = mag = 0;
	imu.getCalibration(&system, &gyro, &accel, &mag);

	/* The data should be ignored until the system calibration is > 0 */
	Serial.print("\t");
	if (!system)
	{
		Serial.print("! ");
	}

	/* Display the individual values */
	Serial.print("Sys:");
	Serial.print(system, DEC);
	Serial.print(" G:");
	Serial.print(gyro, DEC);
	Serial.print(" A:");
	Serial.print(accel, DEC);
	Serial.print(" M:");
	Serial.println(mag, DEC);
}


sensor_t IMU::get_sensor_details() {
	sensor_t sensor;
	imu.getSensor(&sensor);
	return sensor;
}

sensors_event_t IMU::get_sensor_data() {
	sensors_event_t event;
	imu.getEvent(&event);
	return event;
}

/**************************************************************************/
/*
Arduino loop_imu function, called once 'setup' is complete (your own code
should go here)
*/
/**************************************************************************/
void IMU::display_sensor_data(void)
{
	/* Get a new sensor event */
	sensors_event_t event;
	imu.getEvent(&event);

	/* Display the floating point data */
	Serial.print("X: ");
	Serial.print(event.orientation.x, 4);
	Serial.print("\tY: ");
	Serial.print(event.orientation.y, 4);
	Serial.print("\tZ: ");
	Serial.print(event.orientation.z, 4);

	/* Optional: Display calibration status */
	display_cal_status();

	/* Optional: Display sensor status (debug only) */
	//displaySensorStatus();

	/* New line for the next sample */
	Serial.println("");

	/* Wait the specified delay before requesting nex data */
	//delay(BNO055_SAMPLERATE_DELAY_MS);
}

/*
 * get_euler_data - this function returns the roll, pitch, yaw info
 * but this euler data should be attached to your own application
 */

euler_data IMU::get_euler_data(){
  sensors_event_t event;
  imu.getEvent(&event);

  euler_data data;
  data.roll = event.orientation.x;
  data.pitch = event.orientation.y;
  data.yaw = event.orientation.z;
  return data;
}


#endif
