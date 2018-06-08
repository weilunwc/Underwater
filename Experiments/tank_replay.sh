a=`pwd`
b="/tank_test.bag"
bagfile="$a$b"

water_depth=`cat tank_test.yaml`
roslaunch underwater_experiments tank_experiment_replay.launch bagfile:=$bagfile water_depth:=$water_depth
