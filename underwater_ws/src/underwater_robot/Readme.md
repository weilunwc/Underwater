Uderwater-
	underwater_ws
		src
			underwater_robot
			underwater_sim
			underwater_msg


1. Check the usb ports to motor correspodence
	Arduino: get_usb/  make upload
	Ros: roslaunch underwater_robot usb.launch
   Open .zshrc or .bashrc with text editor to see if the motors are correct
   ( cd ~/; vim .bashrc or subl .bashrc)
   If you have changed it, reopen terminal to load new settings.


2. Recalibrate encoder values
	Arduino: encoder_calibrate/ make upload
	Ros: roslaunch underwater_robot encoder_calibrate.launch
   Move the flippers to the origin point, and then shut down the code (cntrl_c)

3. Do your controlling tests
	Arduino: arduino_nodes/ make upload
   Change your settings in scripts/configs.py
   There are three configurations to set: arduino, visual and control
   Now got to src/control/joystick_control.cpp
   choose the sensors and actuators you need, and the control you are testing
   and compile the code with robo_ck
   run your desired test with:
   	roslaunch underwater_robot joystick_control.launch --screen
   









