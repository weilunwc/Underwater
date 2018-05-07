import rospy
from Sensor import Sensor



def main():
    
    # Set up node name
    rospy.init_node("test", anonymous=False)
    
    # Set up sensor configuration
    sensor = Sensor()
    sensor.subscribe_baro()
    sensor.subscribe_imu()
    
    # Set up publisher configuration
    sensor.setup_position_publisher()
    sensor.setup_orientation_publisher()

    rate = rospy.Rate(4)

    while not rospy.is_shutdown():
        rate.sleep()

if __name__ == '__main__':
    main()
