## Underwater robot Installation

**1. Clone this repository and setup system variables**

```
cd ~/
git clone https://github.com/weilunwc/Underwater.git
cd ~/Underwater
cat shell_config.txt >> ~/.bashrc
```

**2. Install Arduino for linux system**

Follow the instructions on https://www.arduino.cc/en/Guide/Linux 

After running `./install.sh` , you should be able to find an Arduino icon on your desktop. Type `cd ~/Underwater; cp -R Arduino ~/` to set up Arduino libraries

**3. Install Arduino Makefile to operate in terminal**

```
sudo apt-get update 
sudo apt-get install arduino-mk
```

To check if this step is successful, let's try to compile a sample code. 

```
cd ~/Underwater/underwater_ws/src/underwater_robot/underwater_arduino/arduino_nodes
make
``` 
If it compiles without error then its installed successfully


Note that there can only be one arduino code within the directory of the makefile

type `make upload` to upload to the board after setting the configuration type 

type `make clean` to clean up the executables

**4. Check the nano firmware**

If `make upload` for Arduino nano gives you a problem

Download nano firmware from [here](https://www.elegoo.com/download/)


**5. Setup C++ Eigen linear algebra library **

In order to run linear algebra opertations in C++, we use the Eigen opensource library

```
hg clone https://bitbucket.org/eigen/eigen/
cp -R eigen/Eigen /usr/local/include
```


**6. Check ROS version**

type `rosversion -d` and remember the version of ros you are using

If ros is not installed, check out [installation](http://wiki.ros.org/ROS/Installation) and [tutorials](http://wiki.ros.org/ROS/Tutorials)

**7. Install joystick package**

Follow tutorials from [here](http://wiki.ros.org/joy/Tutorials/ConfiguringALinuxJoystick)

`sudo apt-get install ros-<version>-joy`

for <version> type in the results from previous step

**8. Install Arduino serrial package to interface ROS with Ardunio**

Follow the instructions on [here](http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup) 

```
sudo apt-get install ros-kinetic-rosserial 
sudo apt-get install ros-kinetic-rosserial-arduino`
```
**9. Generate the ros arduino library**

```
roscd underwater_robot/utilities
./build_arduino_msg
```
Whenever we build any custom message types in ros, make sure you do this again by `build_ros_msg`


**10. Set up ros-usb-cam**

Connect the computer to the usb-camera, and download the ros package `sudo apt-get install ros-<version>-usb-cam`

Test if its working with `roslaunch usb_cam usb_cam-test.launch`


Now We're all set!
