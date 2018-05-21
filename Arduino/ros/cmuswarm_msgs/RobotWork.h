#ifndef _ROS_cmuswarm_msgs_RobotWork_h
#define _ROS_cmuswarm_msgs_RobotWork_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace cmuswarm_msgs
{

  class RobotWork : public ros::Msg
  {
    public:
      typedef const char* _robot_name_type;
      _robot_name_type robot_name;
      typedef float _distance_travelled_type;
      _distance_travelled_type distance_travelled;

    RobotWork():
      robot_name(""),
      distance_travelled(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_robot_name = strlen(this->robot_name);
      varToArr(outbuffer + offset, length_robot_name);
      offset += 4;
      memcpy(outbuffer + offset, this->robot_name, length_robot_name);
      offset += length_robot_name;
      offset += serializeAvrFloat64(outbuffer + offset, this->distance_travelled);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_robot_name;
      arrToVar(length_robot_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_robot_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_robot_name-1]=0;
      this->robot_name = (char *)(inbuffer + offset-1);
      offset += length_robot_name;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->distance_travelled));
     return offset;
    }

    const char * getType(){ return "cmuswarm_msgs/RobotWork"; };
    const char * getMD5(){ return "ae20d3972dddc3610b7ede670958e6d9"; };

  };

}
#endif