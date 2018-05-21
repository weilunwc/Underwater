#ifndef _ROS_underwater_msg_Encoder_h
#define _ROS_underwater_msg_Encoder_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace underwater_msg
{

  class Encoder : public ros::Msg
  {
    public:
      typedef float _encoder_angle_type;
      _encoder_angle_type encoder_angle;
      typedef float _encoder_speed_type;
      _encoder_speed_type encoder_speed;

    Encoder():
      encoder_angle(0),
      encoder_speed(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_encoder_angle;
      u_encoder_angle.real = this->encoder_angle;
      *(outbuffer + offset + 0) = (u_encoder_angle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_encoder_angle.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_encoder_angle.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_encoder_angle.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->encoder_angle);
      union {
        float real;
        uint32_t base;
      } u_encoder_speed;
      u_encoder_speed.real = this->encoder_speed;
      *(outbuffer + offset + 0) = (u_encoder_speed.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_encoder_speed.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_encoder_speed.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_encoder_speed.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->encoder_speed);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_encoder_angle;
      u_encoder_angle.base = 0;
      u_encoder_angle.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_encoder_angle.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_encoder_angle.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_encoder_angle.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->encoder_angle = u_encoder_angle.real;
      offset += sizeof(this->encoder_angle);
      union {
        float real;
        uint32_t base;
      } u_encoder_speed;
      u_encoder_speed.base = 0;
      u_encoder_speed.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_encoder_speed.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_encoder_speed.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_encoder_speed.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->encoder_speed = u_encoder_speed.real;
      offset += sizeof(this->encoder_speed);
     return offset;
    }

    const char * getType(){ return "underwater_msg/Encoder"; };
    const char * getMD5(){ return "9991f74e6b5a800497ccb5b53c4ed151"; };

  };

}
#endif