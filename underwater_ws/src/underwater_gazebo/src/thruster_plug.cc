#include <functional>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <ignition/math/Vector3.hh>
#include <thread>
#include <iostream>
#include "ros/ros.h"
#include "ros/callback_queue.h"
#include "ros/subscribe_options.h"
#include "std_msgs/Float32.h"
#include "underwater_msg/Cmd.h"
#include <boost/bind.hpp>

namespace gazebo
{
  class SamplePlug : public ModelPlugin
  {
  	public: SamplePlug(){};

  private: std::unique_ptr<ros::NodeHandle> rosNode;
  ros::NodeHandle n;
  //ros::Publisher central_pub;
/// \brief A ROS subscriber
  private: ros::Subscriber rosSub;

/// \brief A ROS callbackqueue that helps process messages
  private: ros::CallbackQueue rosQueue;

/// \brief A thread the keeps running the rosQueue
  private: std::thread rosQueueThread;

  private: double force = 0;\
  private: physics::JointController ConPos;
  private: physics::JointController ConVel;
  
  public: ~SamplePlug()
   {
      updateConnection.reset();

    }
  	/// \brief A node use for ROS transport
	
  

	public: void SetForce(const double &_for)
	{
  	// Set the joint's target velocity.
  	  force = _for;
	}

	public: void OnRosMsg(const underwater_msg::CmdConstPtr &_msg)
	{
  		this->mode = _msg->mode;
      this->spinSpeed = _msg->spinning_speed;
      this->flippAngle = _msg->flipping_angle;
      this->flippSpeed = _msg->flipping_speed;
  		//std::cout << "woop" << std::endl;
      
	}

/// \brief ROS helper function that processes messages
	private: void QueueThread()
	{
  		static const double timeout = 0.01;
  		while (this->rosNode->ok())
		{
    		this->rosQueue.callAvailable(ros::WallDuration(timeout));
  		}
	}


  protected:  void Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf)
  {
    // Store the pointer to the model
    this->model = _parent;
    if (!_sdf->HasElement("linkName"))
    {
       ROS_FATAL_NAMED("force", "force plugin missing <bodyName>, cannot proceed");
       return;
    }
    mode = 0;
    spinSpeed = 0;
    flippAngle = 0;
    flippSpeed = 0;
    this->link_name = _sdf->Get<std::string>("linkName");
    this->joint_name = _sdf->Get<std::string>("jointName"); 
    std::cout << this->link_name << std::endl; 
    std::cout << this->joint_name << std::endl;
    std::cout << "///////////////////////////////////////////////////////////////////" << std::endl;
    std::vector<physics::LinkPtr> Link_V = this->model->GetLinks();
    std::cout << Link_V.size();
    for(int i = 0; i < Link_V.size(); i++){
      std::cout << Link_V[i]->GetName() << std::endl;
    }
    std::cout << "*******************************************************************" << std::endl;
    this->link = this->model->GetLink(link_name);
    this->joint = this->model->GetJoint(joint_name);

    this->ConPos.AddJoint(this->joint);
    this->ConVel.AddJoint(this->joint);

    if(!ros::isInitialized())
    {
      return;
    }
    ros::Duration gazebo_period(model->GetWorld()->Physics()->GetMaxStepSize());
    this->rosNode.reset(new ros::NodeHandle(link_name));
    ros::SubscribeOptions so =
        ros::SubscribeOptions::create<underwater_msg::Cmd>(
          "/" + joint_name + "/cmd",
          1,
         boost::bind(&SamplePlug::OnRosMsg, this, _1),
         ros::VoidPtr(), &this->rosQueue);

    this->rosSub = this->rosNode->subscribe(so);


      // Spin up the queue helper thread.
      this->rosQueueThread =
      std::thread(boost::bind(&SamplePlug::QueueThread, this));

  
      this->updateConnection = event::Events::ConnectWorldUpdateEnd(
          boost::bind(&SamplePlug::OnUpdate, this));
      

	  }
    // Called by the world update start event
    protected:  virtual void OnUpdate()
    {	//std::cout << "what" << std::endl;
      // Apply a small linear velocity to the model.
    }

    // Pointer to the model
    protected: std::string link_name;
    protected: std::string joint_name;
    private: physics::ModelPtr model;
    private: physics::LinkPtr link;
    private: physics::JointPtr joint;


    private: int mode, spinSpeed, flippAngle, flippSpeed;
    // Pointer to the update event connection
    private: event::ConnectionPtr updateConnection;
    /// \brief A PID controller for the joint.
    private: common::PID pid;

        /// \brief A node used for transport
    private: transport::NodePtr node;

    /// \brief A subscriber to a named topic.
    private: transport::SubscriberPtr sub;
  };

  // Register this plugin with the simulator
  GZ_REGISTER_MODEL_PLUGIN(SamplePlug);
}
