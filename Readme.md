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

Test if it's working with `roslaunch usb_cam usb_cam-test.launch`

**11. Connect to Blue robotics locator**

Connect computer to the locator ethernet cable and follow the connection settings below
<p align="center">
  <img src="https://github.com/weilunwc/Underwater/blob/master/Images/edit_connection.png"/>
</p>
<p align="center">
  <img src="https://github.com/weilunwc/Underwater/blob/master/Images/settings.png"/>
</p>

**11. Install AR Markers**

Download ar-track-alvar with ```$ sudo apt-get install ros-kinetic-ar-track-alvar``` and then ```rospack profile```

For more info, look at these links:
[Ar-track-alvar setup](https://realitybytes.blog/2017/06/02/detecting-and-tracking-ar-tags/)
[Working with Rviz](https://piazza-resources.s3.amazonaws.com/hysvddrwjpvg5/i252vexju0u5tb/ARTag.pdf?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=ASIAIZJ7B2EHA3UUTDOQ%2F20180612%2Fus-east-1%2Fs3%2Faws4_request&X-Amz-Date=20180612T001038Z&X-Amz-Expires=10800&X-Amz-SignedHeaders=host&X-Amz-Security-Token=FQoDYXdzEDcaDHL5Taop%2FBhUpGROcyK3A8CUgJMf2MKyLQQUPmR%2F4habIAxBdk%2BjHDFrCSxkyvEKCPFvqQ3ZBoeuFnqcsj6PD%2BlE8TVrVIKVr0G2zkL34k%2FleKSBd8uRqfokpZwDRZYhMfDrk%2FnFTvCMtiUfxS02OePIKM43dguivT9A2hIRcFr3o3eZBn5Vtak%2FglzHsPBeC994tw8hpEsGaw0T5egGaCIlsAcCbNvP3bB1wl%2Bs10t3mIPoGFFAvX3PBlp2tRJ5xVWROG1Hgq%2F%2FuUVlorK8mW4fkWZMf2icCmPI%2Fl6OqEYIqALiz94%2FEIKkFpBHC9iXWRZhxDryAJ9EJIWoIUDtDUc2FnTq3eYcQqnmMQfUig0rUphmyC15Hgrvp7A8ePrVDaoOOvI9z1%2FkmG26Bo3dQ5pKc3NKPXfmCOKLDh09h4TrBi2Ud6E0FAN%2Bj6AbxyiRR2%2FvHA4iAtM8ORIk%2BWDcsoJNzIW%2Fb%2BS7Antl9KzI5wKGAVGpnE5cmcY3QnWHLe3rioTx4YHaHMwhB1Ny4l1D%2FjvSzSXc0wP4EF4SMVVCXamak2TAgRD9pXEeidK5FbEdT6veoPY8VJ4%2FoXhu%2FWyxklXko37KH1YomNr72AU%3D&X-Amz-Signature=f3c92bb9d76e08cbce536f8fcac914e8c6d001d8993f71e0d34c67702970b365)

Now We're all set!
