// fake imu for world with no gravity basiclly cheating
// gazebo
#include <functional>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <gazebo/transport/TransportTypes.hh>
#include <ignition/math/Vector3.hh>

// ros
#include <ros/ros.h>
#include <geometry_msgs/Quaternion.h>
#include <underwater_msg/Imu.h>
#include <tf/transform_broadcaster.h>

namespace gazebo
{
    class FakeImu : public ModelPlugin{
        public:
        FakeImu();
        ~FakeImu();
        void Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf);
        // Called by the world update start event
        void OnUpdate();

        // Pointer to the model
        private: 
        physics::ModelPtr model;
        // Pointer to the update event connection
        event::ConnectionPtr updateConnection;
        
        std::string orientationType;

        // ros
        ros::NodeHandle* node_handle_; 
        ros::Publisher imu_publisher_;
        geometry_msgs::Quaternion imu_quat_;
        underwater_msg::Imu imu_euler_; 
    };

    // Register this plugin with the simulator
    GZ_REGISTER_MODEL_PLUGIN(FakeImu)
    
    FakeImu::FakeImu(){
        imu_quat_.x = 0;         
        imu_quat_.y = 0;         
        imu_quat_.z = 0;         
        imu_quat_.w = 1;        

        imu_euler_.roll = 0;
        imu_euler_.pitch = 0;
        imu_euler_.yaw = 0;
    }
    
    FakeImu::~FakeImu(){
        node_handle_->shutdown();
        delete node_handle_;
    }

    void FakeImu::Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf){
        this->model = _parent;
        this->updateConnection = event::Events::ConnectWorldUpdateBegin(
               std::bind(&FakeImu::OnUpdate, this));
        node_handle_ = new ros::NodeHandle();
        
        orientationType = "quaternion";
        if(_sdf->HasElement("orientationType")){
            orientationType = _sdf->GetElement("orientationType")->GetValue()->GetAsString();
            if(orientationType != "quaterion" || orientationType != "euler")
                gzerr << "Invalid orientation type, only excepts euler and quaternion\n";
        }
        if(orientationType == "quaternion")
            imu_publisher_ = node_handle_->advertise<geometry_msgs::Quaternion>("imu", 10);
        else
            imu_publisher_ = node_handle_->advertise<underwater_msg::Imu>("imu", 10);
    }

    void FakeImu::OnUpdate(){
        ignition::math::Pose3d pose = this->model->WorldPose();
        ignition::math::Quaternion<double> q(0,0,0,0);
        q = pose.Rot();
        
        imu_quat_.x = q.X();
        imu_quat_.y = q.Y();
        imu_quat_.z = q.Z();
        imu_quat_.w = q.W();
        
        if(orientationType == "quaternion") imu_publisher_.publish(imu_quat_);
        else{
            tf::Quaternion quat;
            tf::quaternionMsgToTF(imu_quat_, quat);
            double roll, pitch, yaw;
            tf::Matrix3x3(quat).getRPY(roll, pitch, yaw);
            
            imu_euler_.roll = roll;
            imu_euler_.pitch = pitch;
            imu_euler_.yaw = yaw;
            imu_publisher_.publish(imu_euler_);

        }
    }

}
