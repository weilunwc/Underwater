// gazebo
#include <functional>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <gazebo/transport/TransportTypes.hh>
#include <ignition/math/Vector3.hh>     
#include <ignition/math/Pose3.hh>
// ros
#include <ros/ros.h>
#include <geometry_msgs/Point.h>

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
        geometry_msgs::Point position_;

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
        position_publisher_ = node_handle_->advertise<geometry_msgs::Point>("position", 10);
    }

    void Position::OnUpdate(){
        // Apply a small linear velocity to the model.
        //this->model->SetLinearVel(ignition::math::Vector3d(.3, 0, 0));
        
        ignition::math::Pose3d pose = this->model->WorldPose();
        ignition::math::Vector3d v(0, 0, 0);
        v = pose.Pos();
        position_.x = v.X(); 
        position_.y = v.Y(); 
        position_.z = v.Z(); 
        position_publisher_.publish(position_);
    }


}
