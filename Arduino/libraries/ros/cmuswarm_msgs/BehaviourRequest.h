#ifndef _ROS_cmuswarm_msgs_BehaviourRequest_h
#define _ROS_cmuswarm_msgs_BehaviourRequest_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "dynamic_reconfigure/Config.h"

namespace cmuswarm_msgs
{

  class BehaviourRequest : public ros::Msg
  {
    public:
      typedef const char* _name_type;
      _name_type name;
      typedef dynamic_reconfigure::Config _parameters_type;
      _parameters_type parameters;

    BehaviourRequest():
      name(""),
      parameters()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_name = strlen(this->name);
      varToArr(outbuffer + offset, length_name);
      offset += 4;
      memcpy(outbuffer + offset, this->name, length_name);
      offset += length_name;
      offset += this->parameters.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_name;
      arrToVar(length_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_name-1]=0;
      this->name = (char *)(inbuffer + offset-1);
      offset += length_name;
      offset += this->parameters.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "cmuswarm_msgs/BehaviourRequest"; };
    const char * getMD5(){ return "46e49ac4c99a195f3de62087b526c194"; };

  };

}
#endif