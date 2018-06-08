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



  class TestPlug : public ModelPlugin
  {
  public: TestPlug(){};

  private: std::unique_ptr<ros::NodeHandle> rosNode;
  private: ros::NodeHandle n;
  private: ros::Subscriber rosSub;

  private: ros::CallbackQueue rosQueue;

  private: std::thread rosQueueThread;
  private: common::PID pidP;
  private: common::PID pidV;
  private: double force = 0;
  private: double effort = 0;
  

  public: ~TestPlug()
   {
      updateConnection.reset();

    }
  	/// \brief A node use for ROS transport
	

  protected: void setReset(){
  }
  protected: void setPostion(){
    this->model->GetJointController()->SetPositionPID(
          this->joint->GetScopedName(), this->pidP);
  }
  protected: void setVelocity(){
    this->model->GetJointController()->SetVelocityPID(
          this->joint->GetScopedName(), this->pidV);
  }


	public: void OnRosMsg(const underwater_msgs::CmdConstPtr &_msg)
	{   int oldmode = this->mode;
      
  		this->mode = _msg->mode;
      this->spinSpeed = _msg->spinning_speed;
      this->flippAngle = _msg->flipping_angle;
      this->flippSpeed = _msg->flipping_speed;
      this->force = -1*100*(((double)flippSpeed)/90);
      if(this->mode == 2 && oldmode != 2){
        setVelocity();
      }
      else if(this->mode == 1 && oldmode != 1){
        setPostion();
      }
      else if(this->mode == 0 && oldmode != 0){
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
  { this->pidV= common::PID(0.1, 0, 0);
    this->pidP= common::PID(.2, .01, .1);
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

    this->link = this->model->GetLink(link_name);
    this->joint = this->model->GetJoint(joint_name);
    if(!ros::isInitialized())
    {
      return;
    }

    ros::Duration gazebo_period(model->GetWorld()->Physics()->GetMaxStepSize());
    this->rosNode.reset(new ros::NodeHandle(link_name));
    ros::SubscribeOptions so =
        ros::SubscribeOptions::create<underwater_msgs::Cmd>(
          "/" + joint_name + "/cmd",
          1,
         boost::bind(&TestPlug::OnRosMsg, this, _1),
         ros::VoidPtr(), &this->rosQueue);

    this->rosSub = this->rosNode->subscribe(so);
    // Spin up the queue helper thread.
    this->rosQueueThread =
    std::thread(boost::bind(&TestPlug::QueueThread, this));
    this->updateConnection = event::Events::ConnectWorldUpdateEnd(
          boost::bind(&TestPlug::OnUpdate, this));

  }
  


  protected:  virtual void OnUpdate()
    {	
       if(mode == 0){
       }
       else if(mode == 1){
          this->model->GetJointController()->SetPositionTarget(
              this->joint->GetScopedName(),2*3.14*((double)flippAngle)/360.0);
          this->link->AddRelativeForce(ignition::math::Vector3d(0,0,force));
          std::cout << force << std::endl;
       }
       else if(mode == 2){
          double vel = 31.1*((double)spinSpeed)/90;
          this->model->GetJointController()->SetVelocityTarget(
            this->joint->GetScopedName(), vel);
       }
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

        /// \brief A node used for transport
    private: transport::NodePtr node;

    /// \brief A subscriber to a named topic.
    private: transport::SubscriberPtr sub;
  };

  // Register this plugin with the simulator
  GZ_REGISTER_MODEL_PLUGIN(TestPlug);
}
