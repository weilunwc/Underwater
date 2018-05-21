Tutorial to get underwater robot settled

1. Install Arduino for linux system

Follow the instructions on https://www.arduino.cc/en/Guide/Linux
After running ./install.sh you should be able to find an Arduino icon on 
your desktop and cd ~/ there should be a Arduino directory



2. Install Underwater Arduino dependencies
cd ~/Arduino/libraries
git clone https://github.com/weilunwc/Underwater_Motor.git
git clone https://github.com/weilunwc/Underwater_Barometer.git
git clone https://github.com/weilunwc/Underwater_IMU.git
git clone https://github.com/weilunwc/Underwater_Encoder.git
git clone https://github.com/adafruit/Adafruit_BNO055.git
git clone https://github.com/adafruit/Adafruit_Sensor.git


After running this step, open your Arduino IDE, under examples we should be able to see the examples

3. Install Arduino Makefile to compile and upload under terminal

sudo apt-get update
sudo apt-get install arduino-mk

To check if this step is successful, let's try to compile a sample code 
cd ~/Arduino/libraries/Underwater_Motor/motor
open your favorite text editor, and change the Makefile based on your settings
change the USER_LIB_PATH to the path user name from william to your user name
Note that all of the makefiles under this system should be changed to your name

type 'make' and see if there are any compile errors

A simple walk through of the makefile structure


ARDUINO_DIR = /usr/share/arduino
# The device port that you are using 
# Check the Arduino IDE and you can see the Arduino port names
# nanos have name USBX and unos have name ACMX
ARDUINO_PORT = /dev/ttyUSB3
#ARDUINO_PORT = /dev/ttyAVR*


# Change the lib path to your custom path where you place your downloaded libraries
USER_LIB_PATH = /home/william/Arduino/libraries
# Type of board
BOARD_TAG = nano328
#BOARD_TAG = uno

include /usr/share/arduino/Arduino.mk


Note that there can only be one arduino code within the directory of the makefile

type 'make upload' to upload to the board after setting the configuration
type 'make clean' to clean up the executables


4. Check the nano firmware

type 'make upload' after setting the configuration to use nano as the board

Download nano firmware from this page https://www.elegoo.com/download/ if it's not working

if it's working, then the Arduino is all set!


5. type 'ros version -d' and remember the version of ros you are using

If ros is not installed, follow the tutorail on http://wiki.ros.org/ROS/Installation
and http://wiki.ros.org/ROS/Tutorials


6. Download the Underwater_ROS package under the underwater_ws

cd ~/
mkdir -p ~/Underwater/underwater_ws/src
cd ~/Underwater/underwater_ws/
catkin_make

After making sure there are no erros
type
echo 'source ~/Underwater/underwater_ws/devel/setup.bash' >> ~/.bashrc 
or if you are using zsh
echo 'source ~/Underwater/underwater_ws/devel/setup.zsh' >> ~/.zshrc 
Then type 'source ~/.bashrc' or 'source ~/.zshrc' 

Now type
cd ~/Underwater/underwater_ws/src
git clone https://github.com/weilunwc/Underwater_ROS.git


To speed up the compile, also add this line to your bashrc
alias robo_ck='export ck_dir=`pwd`; cd ~/Underwater/underwater_ws; catkin_make; cd $ck_dir'
source ~/.bashrc

Now whenever you want to compile just type robo_ck


7. Install joystick package

Follow tutorials on http://wiki.ros.org/joy/Tutorials/ConfiguringALinuxJoystick

sudo apt-get install ros-kinetic-joy


8. Install Arduino serrial package so that can use ros with Ardunio

Follow the instructions on http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup

sudo apt-get install ros-kinetic-rosserial
sudo apt-get install ros-kinetic-rosserial-arduino


9. Generate the ros arduino library, run the srcipt code in underwater_robot

roscd underwater_robot/utilities
./build_arduino_msg

Whenever we make a new custom message type, run this command so the message types are synchronized.

10. Set up system variables for the Makefile 
add these lines to your .bashrc or .zshrc

# underwater variables
export center_motor=/dev/ttyUSB2
export motor_1=/dev/ttyUSB0
export motor_2=/dev/ttyUSB3
export motor_3=/dev/ttyUSB1
export arduino_lib_path=/home/william/Arduino/libraries

Then type 
source ~/.zshrc    or     source ~/.bashrc

Now we're all set!
