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
#include <boost/bind.hpp>

namespace gazebo
{
  class ModelPush : public ModelPlugin
  {
  	public: ModelPush(){};

private: std::unique_ptr<ros::NodeHandle> rosNode;
  ros::NodeHandle n;
  //ros::Publisher central_pub;
/// \brief A ROS subscriber
  private: ros::Subscriber rosSub;

/// \brief A ROS callbackqueue that helps process messages
  private: ros::CallbackQueue rosQueue;

/// \brief A thread the keeps running the rosQueue
  private: std::thread rosQueueThread;

  private: double force = 0;
  public: ~ModelPush()
   {
      updateConnection.reset();

    }
  	/// \brief A node use for ROS transport
	

	public: void SetForce(const double &_for)
	{
  	// Set the joint's target velocity.
  	  force = _for;
	}

	public: void OnRosMsg(const std_msgs::Float32ConstPtr &_msg)
	{
  		this->SetForce(_msg->data);
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


    public: virtual void Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf)
    {
      // Store the pointer to the model
      this->model = _parent;
      this->link_name = _sdf->GetElement("BodyName")->Get<std::string>();
      this->link = model->GetLink(this->link_name);

      if(!ros::isInitialized())
      {
        return;
      }
      ros::Duration gazebo_period(model->GetWorld()->Physics()->GetMaxStepSize());
      // Listen to the update event. This event is broadcast every
      // simulation iteration.

      this->rosNode.reset(new ros::NodeHandle(link_name));
    
      // central_pub = n.advertise<std_msgs::Float32>("force_node_out",10);
      // Create a named topic, and subscribe to it.
      ros::SubscribeOptions so =
          ros::SubscribeOptions::create<std_msgs::Float32>(
            "/" + link_name + "/for_cmd",
            1,
           boost::bind(&ModelPush::OnRosMsg, this, _1),
           ros::VoidPtr(), &this->rosQueue);
       this->rosSub = this->rosNode->subscribe(so);

      // Spin up the queue helper thread.
      this->rosQueueThread =
      std::thread(boost::bind(&ModelPush::QueueThread, this));


      this->updateConnection = event::Events::ConnectWorldUpdateEnd(
          boost::bind(&ModelPush::OnUpdate, this));
      // Initialize ros, if it has not already bee initialized.

	   // Create our ROS node. This acts in a similar manner to
	   // the Gazebo node
		

	  }
    // Called by the world update start event
    public:  void OnUpdate()
    {	//std::cout << "what" << std::endl;
      // Apply a small linear velocity to the model.
      this->link->AddForce(ignition::math::Vector3d(0,0,force));
      std_msgs::Float32 central;
      central.data = force;
      //central_pub.publish(central);
    }

    // Pointer to the model
    private: std::string link_name;
    private: physics::ModelPtr model;
    protected: physics::LinkPtr link;

    // Pointer to the update event connection
    protected: event::ConnectionPtr updateConnection;
    /// \brief A PID controller for the joint.
    private: common::PID pid;

        /// \brief A node used for transport
    private: transport::NodePtr node;

    /// \brief A subscriber to a named topic.
    private: transport::SubscriberPtr sub;
  };

  // Register this plugin with the simulator
  GZ_REGISTER_MODEL_PLUGIN(ModelPush);
}
