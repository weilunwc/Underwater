#ifndef _ROS_SERVICE_SavePerformanceSummary_h
#define _ROS_SERVICE_SavePerformanceSummary_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "dynamic_reconfigure/Config.h"

namespace cmuswarm_msgs
{

static const char SAVEPERFORMANCESUMMARY[] = "cmuswarm_msgs/SavePerformanceSummary";

  class SavePerformanceSummaryRequest : public ros::Msg
  {
    public:
      typedef const char* _metric_name_type;
      _metric_name_type metric_name;
      typedef dynamic_reconfigure::Config _summary_type;
      _summary_type summary;

    SavePerformanceSummaryRequest():
      metric_name(""),
      summary()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_metric_name = strlen(this->metric_name);
      varToArr(outbuffer + offset, length_metric_name);
      offset += 4;
      memcpy(outbuffer + offset, this->metric_name, length_metric_name);
      offset += length_metric_name;
      offset += this->summary.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_metric_name;
      arrToVar(length_metric_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_metric_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_metric_name-1]=0;
      this->metric_name = (char *)(inbuffer + offset-1);
      offset += length_metric_name;
      offset += this->summary.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return SAVEPERFORMANCESUMMARY; };
    const char * getMD5(){ return "72252e699e227f0a54dd273d6036c36f"; };

  };

  class SavePerformanceSummaryResponse : public ros::Msg
  {
    public:
      typedef bool _success_type;
      _success_type success;

    SavePerformanceSummaryResponse():
      success(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_success;
      u_success.real = this->success;
      *(outbuffer + offset + 0) = (u_success.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->success);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_success;
      u_success.base = 0;
      u_success.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->success = u_success.real;
      offset += sizeof(this->success);
     return offset;
    }

    const char * getType(){ return SAVEPERFORMANCESUMMARY; };
    const char * getMD5(){ return "358e233cde0c8a8bcfea4ce193f8fc15"; };

  };

  class SavePerformanceSummary {
    public:
    typedef SavePerformanceSummaryRequest Request;
    typedef SavePerformanceSummaryResponse Response;
  };

}
#endif
