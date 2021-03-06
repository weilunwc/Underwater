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
#include "underwater_msgs/Cmd.h"
#include <boost/bind.hpp>
#include <gazebo/physics/JointController.hh>
namespace gazebo
{
  float ElectricMotorModel(const float _speed, const float _pwm)
  {
    float stallT = _pwm*.3;
    float noLoadS = 31.1*_pwm;
    if (_speed > noLoadS)
      return 0;
    return stallT-stallT*(_speed/noLoadS);
  }



  class CenterPlug : public ModelPlugin
  {
  public: CenterPlug(){};

  private: std::unique_ptr<ros::NodeHandle> rosNode;
  private: ros::NodeHandle n;
  private: ros::Subscriber rosSub;

  private: ros::CallbackQueue rosQueue;

  private: std::thread rosQueueThread;
  private: common::PID pidP;
  private: common::PID pidV;
  private: double force = 0;
  private: double effort = 0;
  

  public: ~CenterPlug()
   {
      updateConnection.reset();

    }
  	/// \brief A node use for ROS transport
	

  protected: void setReset(){
    this->model->GetJointController()->Reset();

  }

	public: void OnRosMsg(const underwater_msgs::CmdConstPtr &_msg)
	{   int oldmode = this->mode;
      
  		this->mode = _msg->mode;
      this->spinSpeed = _msg->spinning_speed;
      this->flippAngle = _msg->flipping_angle;
      this->flippSpeed = _msg->flipping_speed;
      this->force = 1*5*(((double)flippSpeed));
      if(this->mode == 1 && oldmode != 1){
        setReset();
      }
      else if(this->mode == 0 && oldmode != 0){
        setReset();
      }
      else if(this->mode == 2 && oldmode != 2){
        setReset();
      }
      
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
  { this->pidV= common::PID(.1,0,0);
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
    std::cout << this->link_name << std::endl; 

    this->link = this->model->GetLink(link_name);
    if(!ros::isInitialized())
    {
      return;
    }

    ros::Duration gazebo_period(model->GetWorld()->Physics()->GetMaxStepSize());
    this->rosNode.reset(new ros::NodeHandle(link_name));
    ros::SubscribeOptions so =
        ros::SubscribeOptions::create<underwater_msgs::Cmd>(
          "/" + link_name + "/cmd",
          1,
         boost::bind(&CenterPlug::OnRosMsg, this, _1),
         ros::VoidPtr(), &this->rosQueue);

    this->rosSub = this->rosNode->subscribe(so);
    // Spin up the queue helper thread.
    this->rosQueueThread =
    std::thread(boost::bind(&CenterPlug::QueueThread, this));
    this->updateConnection = event::Events::ConnectWorldUpdateEnd(
          boost::bind(&CenterPlug::OnUpdate, this));
  }
  


  protected:  virtual void OnUpdate()
    {	
       if(mode == 0){
       // this->model->GetJointController()->SetVelocityTarget(
       //     this->joint->GetScopedName(), 0);
       }
       else if (mode == 1){
         double vel = ((double)spinSpeed);
          //this->model->GetJointController()->SetVelocityTarget(
          //  this->joint->GetScopedName(), vel);
          this->link->AddRelativeForce(ignition::math::Vector3d(0,0,force));
       }
       //std::cout << std::endl;
    }

    // Pointer to the model
    protected: std::string link_name;
    protected: std::string joint_name;
    private: physics::ModelPtr model;
    private: physics::LinkPtr link;
    private: physics::JointPtr joint;


    private: int mode = 0, spinSpeed = 0, flippAngle = 0, flippSpeed = 0;
    // Pointer to the update event connection
    private: event::ConnectionPtr updateConnection;
    /// \brief A PID controller for the joint.

        /// \brief A node used for transport
    private: transport::NodePtr node;

    /// \brief A subscriber to a named topic.
    private: transport::SubscriberPtr sub;
  };

  // Register this plugin with the simulator
  GZ_REGISTER_MODEL_PLUGIN(CenterPlug);
}
