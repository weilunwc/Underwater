# underwater variables
export center_motor=/dev/ttyUSB1
export motor_1=/dev/ttyUSB0
export motor_2=/dev/ttyUSB2
export motor_3=/dev/ttyUSB3
export arduino_lib_path=/home/$USER/Underwater/Arduino
alias robo_ck='export ck_dir=`pwd`;  cd ~/Underwater/underwater_ws; catkin_make; cd $ck_dir'
alias build_ros_msg='export ck_dir=`pwd`; roscd underwater_robot/utilities; ./build_arduino_msg.sh; cd $ck_dir'

# source workspace ros parameters to shell
source ~/Underwater/underwater_ws/devel/setup.zsh
source ~/Underwater/underwater_ws/devel/setup.sh
source ~/Underwater/underwater_ws/devel/setup.bash

# clean up resources
alias killgazebo="killall -9 gazebo & killall -9 gzserver  & killall -9 gzclient"
alias killros="killall -9 roscore; kill all rosmaster" 


