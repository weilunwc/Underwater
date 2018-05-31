This program helps us calibrate the encoder values to the origin

To do this, run `make upload` to upload the arduino code
Then type `roslaunch underwater_robot encoder_calibrate.launch` to activate the ros-arduino interface
Open another terminal, and type `rosrun underwater_robot encoder_calibrate`

Move the flippers to the origin, then stop the code.
The values in the text file encoder_calibration.txt should be updated.
Now the encoder values could be uploaded by loading this text file!
