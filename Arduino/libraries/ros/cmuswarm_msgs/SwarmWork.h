#ifndef _ROS_cmuswarm_msgs_SwarmWork_h
#define _ROS_cmuswarm_msgs_SwarmWork_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace cmuswarm_msgs
{

  class SwarmWork : public ros::Msg
  {
    public:
      typedef float _distance_travelled_type;
      _distance_travelled_type distance_travelled;

    SwarmWork():
      distance_travelled(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += serializeAvrFloat64(outbuffer + offset, this->distance_travelled);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->distance_travelled));
     return offset;
    }

    const char * getType(){ return "cmuswarm_msgs/SwarmWork"; };
    const char * getMD5(){ return "f127ef884db4d148b4cf450338472b7f"; };

  };

}
#endif