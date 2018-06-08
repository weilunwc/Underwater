// Auto-generated. Do not edit!

// (in-package underwater_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class Cmd {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.mode = null;
      this.spinning_speed = null;
      this.flipping_angle = null;
      this.flipping_speed = null;
    }
    else {
      if (initObj.hasOwnProperty('mode')) {
        this.mode = initObj.mode
      }
      else {
        this.mode = 0;
      }
      if (initObj.hasOwnProperty('spinning_speed')) {
        this.spinning_speed = initObj.spinning_speed
      }
      else {
        this.spinning_speed = 0;
      }
      if (initObj.hasOwnProperty('flipping_angle')) {
        this.flipping_angle = initObj.flipping_angle
      }
      else {
        this.flipping_angle = 0;
      }
      if (initObj.hasOwnProperty('flipping_speed')) {
        this.flipping_speed = initObj.flipping_speed
      }
      else {
        this.flipping_speed = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Cmd
    // Serialize message field [mode]
    bufferOffset = _serializer.int16(obj.mode, buffer, bufferOffset);
    // Serialize message field [spinning_speed]
    bufferOffset = _serializer.int16(obj.spinning_speed, buffer, bufferOffset);
    // Serialize message field [flipping_angle]
    bufferOffset = _serializer.int16(obj.flipping_angle, buffer, bufferOffset);
    // Serialize message field [flipping_speed]
    bufferOffset = _serializer.int16(obj.flipping_speed, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Cmd
    let len;
    let data = new Cmd(null);
    // Deserialize message field [mode]
    data.mode = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [spinning_speed]
    data.spinning_speed = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [flipping_angle]
    data.flipping_angle = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [flipping_speed]
    data.flipping_speed = _deserializer.int16(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'underwater_msgs/Cmd';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '26a53f33e9dfd663b81918f42c8e516a';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int16 mode
    int16 spinning_speed
    int16 flipping_angle
    int16 flipping_speed
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Cmd(null);
    if (msg.mode !== undefined) {
      resolved.mode = msg.mode;
    }
    else {
      resolved.mode = 0
    }

    if (msg.spinning_speed !== undefined) {
      resolved.spinning_speed = msg.spinning_speed;
    }
    else {
      resolved.spinning_speed = 0
    }

    if (msg.flipping_angle !== undefined) {
      resolved.flipping_angle = msg.flipping_angle;
    }
    else {
      resolved.flipping_angle = 0
    }

    if (msg.flipping_speed !== undefined) {
      resolved.flipping_speed = msg.flipping_speed;
    }
    else {
      resolved.flipping_speed = 0
    }

    return resolved;
    }
};

module.exports = Cmd;
