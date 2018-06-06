time=$(date +%Y-%m-%d-%H-%M)
experiment="tank_test"
param_name="$experiment.yaml"
video_name="$experiment.avi"
bag_name="$experiment.bag"

experiment_prefix="tank_test_"
dir_name="$experiment_prefix$time"

video_name="$experiment.avi"
water_depth=$1
echo $time
echo $video_name
echo $param_name

trap ' ' INT
roslaunch underwater_experiments tank_experiment.launch record:=true video_name:=$experiment bag_name:=$experiment

echo {water_depth: $water_depth} > ~/Underwater/Experiments/$param_name
mkdir $dir_name
mv $bag_name $video_name $param_name $dir_name 

