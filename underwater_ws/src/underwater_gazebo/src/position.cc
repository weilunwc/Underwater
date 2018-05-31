// gazebo
#include <functional>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <gazebo/transport/TransportTypes.hh>
#include <ignition/math/Vector3.hh>

// ros
#include <ros/ros.h>
#include <geometry_msgs/Point32.h>

namespace gazebo
{
    class Position : public ModelPlugin{
        public:
        Position();
        ~Position();
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
        ros::Publisher position_publisher_;
        geometry_msgs::Point32 position_;

    };

    // Register this plugin with the simulator
    GZ_REGISTER_MODEL_PLUGIN(Position)
    
    Position::Position(){
        position_.x = 0;        
        position_.y = 0;        
        position_.z = 0;        
    }
    
    Position::~Position(){
        node_handle_->shutdown();
        delete node_handle_;
    }

    void Position::Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf){
        this->model = _parent;
        this->updateConnection = event::Events::ConnectWorldUpdateBegin(
               std::bind(&Position::OnUpdate, this));
        node_handle_ = new ros::NodeHandle();
        position_publisher_ = node_handle_->advertise<geometry_msgs::Point32>("position", 10);
    }

    void Position::OnUpdate(){
        // Apply a small linear velocity to the model.
        this->model->SetLinearVel(ignition::math::Vector3d(.3, 0, 0));
        gazebo::math::Pose pose = this->model->GetWorldPose();
        math::Vector3 v(0, 0, 0);
        v = pose.pos;
        position_.x = v.x; 
        position_.y = v.y; 
        position_.z = v.z; 
         
        position_publisher_.publish(position_);
    }


}
