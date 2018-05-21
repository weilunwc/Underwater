#ifndef _ROS_cmuswarm_msgs_AgentBid_h
#define _ROS_cmuswarm_msgs_AgentBid_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace cmuswarm_msgs
{

  class AgentBid : public ros::Msg
  {
    public:
      typedef const char* _agent_name_type;
      _agent_name_type agent_name;
      typedef float _bid_value_type;
      _bid_value_type bid_value;

    AgentBid():
      agent_name(""),
      bid_value(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_agent_name = strlen(this->agent_name);
      varToArr(outbuffer + offset, length_agent_name);
      offset += 4;
      memcpy(outbuffer + offset, this->agent_name, length_agent_name);
      offset += length_agent_name;
      offset += serializeAvrFloat64(outbuffer + offset, this->bid_value);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_agent_name;
      arrToVar(length_agent_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_agent_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_agent_name-1]=0;
      this->agent_name = (char *)(inbuffer + offset-1);
      offset += length_agent_name;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->bid_value));
     return offset;
    }

    const char * getType(){ return "cmuswarm_msgs/AgentBid"; };
    const char * getMD5(){ return "ee06016af007e4b12f07a4d33707395f"; };

  };

}
#endif