#ifndef _ROS_cmuswarm_msgs_BatchTwist_h
#define _ROS_cmuswarm_msgs_BatchTwist_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Twist.h"

namespace cmuswarm_msgs
{

  class BatchTwist : public ros::Msg
  {
    public:
      typedef geometry_msgs::Twist _direct_command_type;
      _direct_command_type direct_command;
      uint32_t robots_length;
      typedef int32_t _robots_type;
      _robots_type st_robots;
      _robots_type * robots;

    BatchTwist():
      direct_command(),
      robots_length(0), robots(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->direct_command.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->robots_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->robots_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->robots_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->robots_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->robots_length);
      for( uint32_t i = 0; i < robots_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_robotsi;
      u_robotsi.real = this->robots[i];
      *(outbuffer + offset + 0) = (u_robotsi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_robotsi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_robotsi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_robotsi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->robots[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->direct_command.deserialize(inbuffer + offset);
      uint32_t robots_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      robots_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      robots_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      robots_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->robots_length);
      if(robots_lengthT > robots_length)
        this->robots = (int32_t*)realloc(this->robots, robots_lengthT * sizeof(int32_t));
      robots_length = robots_lengthT;
      for( uint32_t i = 0; i < robots_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_st_robots;
      u_st_robots.base = 0;
      u_st_robots.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_robots.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_robots.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_robots.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_robots = u_st_robots.real;
      offset += sizeof(this->st_robots);
        memcpy( &(this->robots[i]), &(this->st_robots), sizeof(int32_t));
      }
     return offset;
    }

    const char * getType(){ return "cmuswarm_msgs/BatchTwist"; };
    const char * getMD5(){ return "4ba601d0ba0de038cbfe3942bfc0fe3b"; };

  };

}
#endif