#ifndef _ROS_cmuswarm_msgs_ObjectCoverageLocations_h
#define _ROS_cmuswarm_msgs_ObjectCoverageLocations_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "cmuswarm_msgs/ObjectCoverageLocation.h"

namespace cmuswarm_msgs
{

  class ObjectCoverageLocations : public ros::Msg
  {
    public:
      uint32_t locations_length;
      typedef cmuswarm_msgs::ObjectCoverageLocation _locations_type;
      _locations_type st_locations;
      _locations_type * locations;

    ObjectCoverageLocations():
      locations_length(0), locations(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->locations_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->locations_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->locations_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->locations_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->locations_length);
      for( uint32_t i = 0; i < locations_length; i++){
      offset += this->locations[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t locations_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      locations_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      locations_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      locations_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->locations_length);
      if(locations_lengthT > locations_length)
        this->locations = (cmuswarm_msgs::ObjectCoverageLocation*)realloc(this->locations, locations_lengthT * sizeof(cmuswarm_msgs::ObjectCoverageLocation));
      locations_length = locations_lengthT;
      for( uint32_t i = 0; i < locations_length; i++){
      offset += this->st_locations.deserialize(inbuffer + offset);
        memcpy( &(this->locations[i]), &(this->st_locations), sizeof(cmuswarm_msgs::ObjectCoverageLocation));
      }
     return offset;
    }

    const char * getType(){ return "cmuswarm_msgs/ObjectCoverageLocations"; };
    const char * getMD5(){ return "ffbff7bc5eaf7b61c86ea236ac37b33e"; };

  };

}
#endif