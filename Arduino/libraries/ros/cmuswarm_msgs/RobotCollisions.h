#ifndef _ROS_cmuswarm_msgs_RobotCollisions_h
#define _ROS_cmuswarm_msgs_RobotCollisions_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "cmuswarm_msgs/RobotCollision.h"

namespace cmuswarm_msgs
{

  class RobotCollisions : public ros::Msg
  {
    public:
      uint32_t collisions_length;
      typedef cmuswarm_msgs::RobotCollision _collisions_type;
      _collisions_type st_collisions;
      _collisions_type * collisions;

    RobotCollisions():
      collisions_length(0), collisions(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->collisions_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->collisions_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->collisions_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->collisions_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->collisions_length);
      for( uint32_t i = 0; i < collisions_length; i++){
      offset += this->collisions[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t collisions_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      collisions_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      collisions_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      collisions_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->collisions_length);
      if(collisions_lengthT > collisions_length)
        this->collisions = (cmuswarm_msgs::RobotCollision*)realloc(this->collisions, collisions_lengthT * sizeof(cmuswarm_msgs::RobotCollision));
      collisions_length = collisions_lengthT;
      for( uint32_t i = 0; i < collisions_length; i++){
      offset += this->st_collisions.deserialize(inbuffer + offset);
        memcpy( &(this->collisions[i]), &(this->st_collisions), sizeof(cmuswarm_msgs::RobotCollision));
      }
     return offset;
    }

    const char * getType(){ return "cmuswarm_msgs/RobotCollisions"; };
    const char * getMD5(){ return "7f13d7825402a2ee8b0286b8317002dc"; };

  };

}
#endif