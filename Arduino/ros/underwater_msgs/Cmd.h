#ifndef _ROS_underwater_msgs_Cmd_h
#define _ROS_underwater_msgs_Cmd_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace underwater_msgs
{

  class Cmd : public ros::Msg
  {
    public:
      typedef int16_t _mode_type;
      _mode_type mode;
      typedef int16_t _spinning_speed_type;
      _spinning_speed_type spinning_speed;
      typedef int16_t _flipping_angle_type;
      _flipping_angle_type flipping_angle;
      typedef int16_t _flipping_speed_type;
      _flipping_speed_type flipping_speed;

    Cmd():
      mode(0),
      spinning_speed(0),
      flipping_angle(0),
      flipping_speed(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_mode;
      u_mode.real = this->mode;
      *(outbuffer + offset + 0) = (u_mode.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_mode.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->mode);
      union {
        int16_t real;
        uint16_t base;
      } u_spinning_speed;
      u_spinning_speed.real = this->spinning_speed;
      *(outbuffer + offset + 0) = (u_spinning_speed.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_spinning_speed.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->spinning_speed);
      union {
        int16_t real;
        uint16_t base;
      } u_flipping_angle;
      u_flipping_angle.real = this->flipping_angle;
      *(outbuffer + offset + 0) = (u_flipping_angle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_flipping_angle.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->flipping_angle);
      union {
        int16_t real;
        uint16_t base;
      } u_flipping_speed;
      u_flipping_speed.real = this->flipping_speed;
      *(outbuffer + offset + 0) = (u_flipping_speed.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_flipping_speed.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->flipping_speed);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_mode;
      u_mode.base = 0;
      u_mode.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_mode.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->mode = u_mode.real;
      offset += sizeof(this->mode);
      union {
        int16_t real;
        uint16_t base;
      } u_spinning_speed;
      u_spinning_speed.base = 0;
      u_spinning_speed.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_spinning_speed.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->spinning_speed = u_spinning_speed.real;
      offset += sizeof(this->spinning_speed);
      union {
        int16_t real;
        uint16_t base;
      } u_flipping_angle;
      u_flipping_angle.base = 0;
      u_flipping_angle.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_flipping_angle.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->flipping_angle = u_flipping_angle.real;
      offset += sizeof(this->flipping_angle);
      union {
        int16_t real;
        uint16_t base;
      } u_flipping_speed;
      u_flipping_speed.base = 0;
      u_flipping_speed.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_flipping_speed.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->flipping_speed = u_flipping_speed.real;
      offset += sizeof(this->flipping_speed);
     return offset;
    }

    const char * getType(){ return "underwater_msgs/Cmd"; };
    const char * getMD5(){ return "26a53f33e9dfd663b81918f42c8e516a"; };

  };

}
#endif