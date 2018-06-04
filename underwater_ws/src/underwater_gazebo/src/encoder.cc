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
#include <underwater_msgs/Encoder.h>
#include <geometry_msgs/Point32.h>

namespace gazebo
{
    double Rad2Deg(double rad){
        return rad*180.0/3.1415926;    
    }

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
        physics::JointPtr joint;
        
        std::string topicName;
        
        // ros
        ros::NodeHandle* node_handle_; 
        ros::Publisher encoder_publisher_;
        underwater_msgs::Encoder enc_;

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
        //std::cout << this->model->GetName() << std::endl;
        
        
        // bind connection
        this->updateConnection = event::Events::ConnectWorldUpdateBegin(
               std::bind(&Encoder::OnUpdate, this));
        
        // find joint encoder is mounted on 
        if(!_sdf->HasElement("jointName")) gzerr << "Encoder missing jointName\n";
        
        this->joint = this->model->GetJoint(_sdf->GetElement("jointName")->Get<std::string>());
        if(!this->joint) gzerr << "Unable to find joint[" << _sdf->GetElement("jointName")->Get<std::string>()
            << "]\n";
        
        // find topic name to publish
        if(!_sdf->HasElement("topicName")) gzerr << _sdf->GetElement("jointName")->Get<std::string>()
            << " missing topic name\n";
        topicName = _sdf->GetElement("topicName")->GetValue()->GetAsString(); 


        /* ros */ 
        node_handle_ = new ros::NodeHandle();
        encoder_publisher_ = node_handle_->advertise<underwater_msgs::Encoder>(topicName, 10);

    }

    void Encoder::OnUpdate(){
        // Apply a small linear velocity to the model.
        //this->model->SetLinearVel(ignition::math::Vector3d(.3, 0, 0));
        
        // read the joint angle
        enc_.encoder_angle = Rad2Deg(this->joint->Position(0));
         
        // read the joint vel
        enc_.encoder_speed = this->joint->GetVelocity(0);


        encoder_publisher_.publish(enc_);
     
    }


}
