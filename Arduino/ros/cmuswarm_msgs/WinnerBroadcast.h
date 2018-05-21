#ifndef _ROS_cmuswarm_msgs_WinnerBroadcast_h
#define _ROS_cmuswarm_msgs_WinnerBroadcast_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "nav_msgs/Path.h"

namespace cmuswarm_msgs
{

  class WinnerBroadcast : public ros::Msg
  {
    public:
      typedef const char* _winner_name_type;
      _winner_name_type winner_name;
      typedef const char* _sender_id_type;
      _sender_id_type sender_id;
      typedef nav_msgs::Path _waypoints_type;
      _waypoints_type waypoints;
      typedef nav_msgs::Path _emergency_stops_type;
      _emergency_stops_type emergency_stops;

    WinnerBroadcast():
      winner_name(""),
      sender_id(""),
      waypoints(),
      emergency_stops()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_winner_name = strlen(this->winner_name);
      varToArr(outbuffer + offset, length_winner_name);
      offset += 4;
      memcpy(outbuffer + offset, this->winner_name, length_winner_name);
      offset += length_winner_name;
      uint32_t length_sender_id = strlen(this->sender_id);
      varToArr(outbuffer + offset, length_sender_id);
      offset += 4;
      memcpy(outbuffer + offset, this->sender_id, length_sender_id);
      offset += length_sender_id;
      offset += this->waypoints.serialize(outbuffer + offset);
      offset += this->emergency_stops.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_winner_name;
      arrToVar(length_winner_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_winner_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_winner_name-1]=0;
      this->winner_name = (char *)(inbuffer + offset-1);
      offset += length_winner_name;
      uint32_t length_sender_id;
      arrToVar(length_sender_id, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_sender_id; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_sender_id-1]=0;
      this->sender_id = (char *)(inbuffer + offset-1);
      offset += length_sender_id;
      offset += this->waypoints.deserialize(inbuffer + offset);
      offset += this->emergency_stops.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "cmuswarm_msgs/WinnerBroadcast"; };
    const char * getMD5(){ return "7d210e7b0eca7fd8ac16da61923d4b5b"; };

  };

}
#endif