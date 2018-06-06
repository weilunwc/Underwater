a=`pwd`
b="/tank_test.bag"
bagfile="$a$b"

water_depth=`cat tank_test.yaml`
echo $water_depth
roslaunch underwater_experiments tank_experiment_replay.launch bagfile:=$bagfile 
