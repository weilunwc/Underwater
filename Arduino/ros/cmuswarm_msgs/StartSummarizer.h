#ifndef _ROS_SERVICE_StartSummarizer_h
#define _ROS_SERVICE_StartSummarizer_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "ros/time.h"

namespace cmuswarm_msgs
{

static const char STARTSUMMARIZER[] = "cmuswarm_msgs/StartSummarizer";

  class StartSummarizerRequest : public ros::Msg
  {
    public:
      typedef ros::Time _start_type;
      _start_type start;

    StartSummarizerRequest():
      start()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->start.sec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->start.sec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->start.sec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->start.sec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->start.sec);
      *(outbuffer + offset + 0) = (this->start.nsec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->start.nsec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->start.nsec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->start.nsec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->start.nsec);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->start.sec =  ((uint32_t) (*(inbuffer + offset)));
      this->start.sec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->start.sec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->start.sec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->start.sec);
      this->start.nsec =  ((uint32_t) (*(inbuffer + offset)));
      this->start.nsec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->start.nsec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->start.nsec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->start.nsec);
     return offset;
    }

    const char * getType(){ return STARTSUMMARIZER; };
    const char * getMD5(){ return "31bd34268aa8683036785238047651c6"; };

  };

  class StartSummarizerResponse : public ros::Msg
  {
    public:

    StartSummarizerResponse()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
     return offset;
    }

    const char * getType(){ return STARTSUMMARIZER; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class StartSummarizer {
    public:
    typedef StartSummarizerRequest Request;
    typedef StartSummarizerResponse Response;
  };

}
#endif
