
## Underwater robot control instructions

**File Structure:** For every task to run on the robot, each has an arduino code that is uploaded into the arduinos on the robot, and a ros launch file on the computer that collects and responds to the robot. 

The arduino code is stored in `underwater_arduino` and each directory name is self-explanatory and corresponds to a similar launch file name.

ROS files are stored in two different places, `src/` stores C++ files (header files in `include/`), and `scripits/` stores the python scripts

#### Everytime we start an experiment must start with this procedure


**1. Check the usb ports to motor correspodence**

- Arduino: `roscd underwater_robot/get_usb/; make upload`
- ROS: `roslaunch underwater_robot usb.launch`

Open .zshrc or .bashrc with text editor to see if the motors are correct
(`cd ~/; vim .bashrc or subl .bashrc`)

If you have made any modifications, reopen terminal to reload settings

**2. Recalibrate encoder values**

- Arduino: `roscd underwater_robot/encoder_calibrate/; make upload`
- ROS: `roslaunch underwater_robot encoder_calibrate.launch --screen`
   
Move the flippers to the origin point, and then shut down the code, now the calibration values should be stored under `underwater_robot/utilites/encoder_calibrate.txt`

**3. Run your experiments with the robot**

- Arduino: `roscd underwater_robot/arduino_nodes/; make upload`
- ROS: `roslaunch underwater_robot joystick_control.launch --screen`

Change your settings in scripts/configs.py
There are three configurations to set: *arduino, visual and control*

Now got to `src/control/joystick_control.cpp`
choose the sensors and actuators you need, and modify the control logic you are testing.

Compile the code by typing  `robo_ck`

Then run the launch file and observe the results

