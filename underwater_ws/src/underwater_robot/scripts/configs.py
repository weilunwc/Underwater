#!/usr/bin/env python
# Set up the configuration for underwater actuators and sensors
import rospy
import os

if __name__ == '__main__':
    rospy.init_node('set_configuration')
    
    # Set up controller
    controller = 'joystick_control'
    rospy.set_param('controller', controller)

    # Read encoder offset
    encoder_calibrate = []
    user_name = os.environ.get('USER')
    calibrate_file = '/home/' + user_name + \
            '/Underwater/underwater_ws/src/underwater_robot/utilities/encoder_calibrate.txt'
    try:
        f = open(calibrate_file, 'r')
        for line in f:
            x = line.split()
            x = int(x[0][:])
            encoder_calibrate.append(x)
        f.close()
    except IOError:
        print("cant open")
        encoder_calibrate = [0,0,0]
    
    # Set up Arduino configuration
    # IMU Baro Enc1 Enc2 Enc3 Enc1_off Enc2_off Enc3_off
    imu = 1
    baro = 0
    enc1 = 0
    enc2 = 0
    enc3 = 0
    enc1_off = encoder_calibrate[0]
    enc2_off = encoder_calibrate[1]
    enc3_off = encoder_calibrate[2]
    arduino_config = [imu, baro, enc1, enc2, enc3, enc1_off, enc2_off, enc3_off]
    rospy.set_param('arduino_configs', arduino_config)
    
    # Set up visualization options
    visual_config = {'Encoder':True, 'Imu':False, 'Barometer':False, 'Position':False }
    rospy.set_param('visual_configs', visual_config) 

    rospy.spin()
