// Auto-generated. Do not edit!

// (in-package underwater_msg.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class Encoder {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.encoder_angle = null;
      this.encoder_speed = null;
    }
    else {
      if (initObj.hasOwnProperty('encoder_angle')) {
        this.encoder_angle = initObj.encoder_angle
      }
      else {
        this.encoder_angle = 0.0;
      }
      if (initObj.hasOwnProperty('encoder_speed')) {
        this.encoder_speed = initObj.encoder_speed
      }
      else {
        this.encoder_speed = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Encoder
    // Serialize message field [encoder_angle]
    bufferOffset = _serializer.float32(obj.encoder_angle, buffer, bufferOffset);
    // Serialize message field [encoder_speed]
    bufferOffset = _serializer.float32(obj.encoder_speed, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Encoder
    let len;
    let data = new Encoder(null);
    // Deserialize message field [encoder_angle]
    data.encoder_angle = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [encoder_speed]
    data.encoder_speed = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'underwater_msg/Encoder';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '9991f74e6b5a800497ccb5b53c4ed151';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 encoder_angle
    float32 encoder_speed
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Encoder(null);
    if (msg.encoder_angle !== undefined) {
      resolved.encoder_angle = msg.encoder_angle;
    }
    else {
      resolved.encoder_angle = 0.0
    }

    if (msg.encoder_speed !== undefined) {
      resolved.encoder_speed = msg.encoder_speed;
    }
    else {
      resolved.encoder_speed = 0.0
    }

    return resolved;
    }
};

module.exports = Encoder;
