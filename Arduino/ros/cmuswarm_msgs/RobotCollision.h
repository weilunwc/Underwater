#ifndef _ROS_cmuswarm_msgs_RobotCollision_h
#define _ROS_cmuswarm_msgs_RobotCollision_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Time.h"

namespace cmuswarm_msgs
{

  class RobotCollision : public ros::Msg
  {
    public:
      typedef std_msgs::Time _time_type;
      _time_type time;
      typedef const char* _subject_name_type;
      _subject_name_type subject_name;
      typedef const char* _object_name_type;
      _object_name_type object_name;

    RobotCollision():
      time(),
      subject_name(""),
      object_name("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->time.serialize(outbuffer + offset);
      uint32_t length_subject_name = strlen(this->subject_name);
      varToArr(outbuffer + offset, length_subject_name);
      offset += 4;
      memcpy(outbuffer + offset, this->subject_name, length_subject_name);
      offset += length_subject_name;
      uint32_t length_object_name = strlen(this->object_name);
      varToArr(outbuffer + offset, length_object_name);
      offset += 4;
      memcpy(outbuffer + offset, this->object_name, length_object_name);
      offset += length_object_name;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->time.deserialize(inbuffer + offset);
      uint32_t length_subject_name;
      arrToVar(length_subject_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_subject_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_subject_name-1]=0;
      this->subject_name = (char *)(inbuffer + offset-1);
      offset += length_subject_name;
      uint32_t length_object_name;
      arrToVar(length_object_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_object_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_object_name-1]=0;
      this->object_name = (char *)(inbuffer + offset-1);
      offset += length_object_name;
     return offset;
    }

    const char * getType(){ return "cmuswarm_msgs/RobotCollision"; };
    const char * getMD5(){ return "5457d647a610d64f53c5ef3a1698d859"; };

  };

}
#endif