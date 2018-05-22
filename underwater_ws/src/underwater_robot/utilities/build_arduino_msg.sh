cd ~/Underwater/Arduino
rm -rf ros_lib ros
rosrun rosserial_arduino make_libraries.py .
mv ros_lib ros
cp ~/Underwater/underwater_ws/src/underwater_robot/utilities/ros.h ros/
