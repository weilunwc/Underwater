// gazebo
#include <functional>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <gazebo/transport/TransportTypes.hh>
#include <ignition/math/Vector3.hh>

// ros
#include <ros/ros.h>
#include <underwater_msg/Encoder.h>
#include <geometry_msgs/Point32.h>

namespace gazebo
{
    class Encoder : public ModelPlugin{
        public:
        Encoder();
        ~Encoder();
        void Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf);
        // Called by the world update start event
        void OnUpdate();

        // Pointer to the model
        private: 
        physics::ModelPtr model;
        // Pointer to the update event connection
        event::ConnectionPtr updateConnection;
        // ros
        ros::NodeHandle* node_handle_; 
        ros::Publisher encoder_publisher_;
        underwater_msg::Encoder enc_;
        gazebo::math::Pose pose;
    };

    // Register this plugin with the simulator
    GZ_REGISTER_MODEL_PLUGIN(Encoder)
    
    Encoder::Encoder(){
       enc_.encoder_angle = 0;
       enc_.encoder_speed = 0;
    }
    
    Encoder::~Encoder(){
        node_handle_->shutdown();
        delete node_handle_;
    }

    void Encoder::Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf){
        this->model = _parent;
        this->updateConnection = event::Events::ConnectWorldUpdateBegin(
               std::bind(&Encoder::OnUpdate, this));
        node_handle_ = new ros::NodeHandle();
        encoder_publisher_ = node_handle_->advertise<underwater_msg::Encoder>("encoder", 10);
    }

    void Encoder::OnUpdate(){
        // Apply a small linear velocity to the model.
        this->model->SetLinearVel(ignition::math::Vector3d(.3, 0, 0));
        encoder_publisher_.publish(enc_);
        pose = this->model->GetWorldPose();
        std::cout << pose << "\n";
    }


}
