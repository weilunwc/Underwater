time=$(date +%Y-%m-%d-%H-%M)
experiment="tank_test"
param_name="$experiment.yaml"
video_name="$experiment.avi"
bag_name="$experiment.bag"
video_name="$experiment.avi"

experiment_prefix="tank_test_"
dir_name="$experiment_prefix$time"

# pass water depth through terminal
water_depth=$1

trap ' ' INT
roslaunch underwater_experiments tank_experiment.launch record:=true video_name:=$experiment bag_name:=$experiment water_depth:=$water_depth

echo $water_depth > ~/Underwater/Experiments/$param_name
mkdir $dir_name
mv $bag_name $video_name $param_name $dir_name 
cp tank_replay.sh $dir_name
