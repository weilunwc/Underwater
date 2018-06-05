#ifndef _ROS_cmuswarm_msgs_EStopRequest_h
#define _ROS_cmuswarm_msgs_EStopRequest_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace cmuswarm_msgs
{

  class EStopRequest : public ros::Msg
  {
    public:
      typedef const char* _sender_id_type;
      _sender_id_type sender_id;
      typedef const char* _target_id_type;
      _target_id_type target_id;

    EStopRequest():
      sender_id(""),
      target_id("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_sender_id = strlen(this->sender_id);
      varToArr(outbuffer + offset, length_sender_id);
      offset += 4;
      memcpy(outbuffer + offset, this->sender_id, length_sender_id);
      offset += length_sender_id;
      uint32_t length_target_id = strlen(this->target_id);
      varToArr(outbuffer + offset, length_target_id);
      offset += 4;
      memcpy(outbuffer + offset, this->target_id, length_target_id);
      offset += length_target_id;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_sender_id;
      arrToVar(length_sender_id, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_sender_id; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_sender_id-1]=0;
      this->sender_id = (char *)(inbuffer + offset-1);
      offset += length_sender_id;
      uint32_t length_target_id;
      arrToVar(length_target_id, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_target_id; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_target_id-1]=0;
      this->target_id = (char *)(inbuffer + offset-1);
      offset += length_target_id;
     return offset;
    }

    const char * getType(){ return "cmuswarm_msgs/EStopRequest"; };
    const char * getMD5(){ return "6fe507d572e392757e122af2bd9d1cbc"; };

  };

}
#endif