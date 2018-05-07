// Auto-generated. Do not edit!

// (in-package underwater_robot.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------


//-----------------------------------------------------------

class SettingRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.imu = null;
      this.barometer = null;
      this.encoder1 = null;
      this.encoder2 = null;
      this.encoder3 = null;
      this.encoder1_offset = null;
      this.encoder2_offset = null;
      this.encoder3_offset = null;
    }
    else {
      if (initObj.hasOwnProperty('imu')) {
        this.imu = initObj.imu
      }
      else {
        this.imu = false;
      }
      if (initObj.hasOwnProperty('barometer')) {
        this.barometer = initObj.barometer
      }
      else {
        this.barometer = false;
      }
      if (initObj.hasOwnProperty('encoder1')) {
        this.encoder1 = initObj.encoder1
      }
      else {
        this.encoder1 = false;
      }
      if (initObj.hasOwnProperty('encoder2')) {
        this.encoder2 = initObj.encoder2
      }
      else {
        this.encoder2 = false;
      }
      if (initObj.hasOwnProperty('encoder3')) {
        this.encoder3 = initObj.encoder3
      }
      else {
        this.encoder3 = false;
      }
      if (initObj.hasOwnProperty('encoder1_offset')) {
        this.encoder1_offset = initObj.encoder1_offset
      }
      else {
        this.encoder1_offset = 0;
      }
      if (initObj.hasOwnProperty('encoder2_offset')) {
        this.encoder2_offset = initObj.encoder2_offset
      }
      else {
        this.encoder2_offset = 0;
      }
      if (initObj.hasOwnProperty('encoder3_offset')) {
        this.encoder3_offset = initObj.encoder3_offset
      }
      else {
        this.encoder3_offset = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SettingRequest
    // Serialize message field [imu]
    bufferOffset = _serializer.bool(obj.imu, buffer, bufferOffset);
    // Serialize message field [barometer]
    bufferOffset = _serializer.bool(obj.barometer, buffer, bufferOffset);
    // Serialize message field [encoder1]
    bufferOffset = _serializer.bool(obj.encoder1, buffer, bufferOffset);
    // Serialize message field [encoder2]
    bufferOffset = _serializer.bool(obj.encoder2, buffer, bufferOffset);
    // Serialize message field [encoder3]
    bufferOffset = _serializer.bool(obj.encoder3, buffer, bufferOffset);
    // Serialize message field [encoder1_offset]
    bufferOffset = _serializer.int16(obj.encoder1_offset, buffer, bufferOffset);
    // Serialize message field [encoder2_offset]
    bufferOffset = _serializer.int16(obj.encoder2_offset, buffer, bufferOffset);
    // Serialize message field [encoder3_offset]
    bufferOffset = _serializer.int16(obj.encoder3_offset, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SettingRequest
    let len;
    let data = new SettingRequest(null);
    // Deserialize message field [imu]
    data.imu = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [barometer]
    data.barometer = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [encoder1]
    data.encoder1 = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [encoder2]
    data.encoder2 = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [encoder3]
    data.encoder3 = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [encoder1_offset]
    data.encoder1_offset = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [encoder2_offset]
    data.encoder2_offset = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [encoder3_offset]
    data.encoder3_offset = _deserializer.int16(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 11;
  }

  static datatype() {
    // Returns string type for a service object
    return 'underwater_robot/SettingRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'd545f84ec040b08d5bf2fc0f795d8d0a';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool imu
    bool barometer
    bool encoder1
    bool encoder2
    bool encoder3
    int16 encoder1_offset
    int16 encoder2_offset
    int16 encoder3_offset
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new SettingRequest(null);
    if (msg.imu !== undefined) {
      resolved.imu = msg.imu;
    }
    else {
      resolved.imu = false
    }

    if (msg.barometer !== undefined) {
      resolved.barometer = msg.barometer;
    }
    else {
      resolved.barometer = false
    }

    if (msg.encoder1 !== undefined) {
      resolved.encoder1 = msg.encoder1;
    }
    else {
      resolved.encoder1 = false
    }

    if (msg.encoder2 !== undefined) {
      resolved.encoder2 = msg.encoder2;
    }
    else {
      resolved.encoder2 = false
    }

    if (msg.encoder3 !== undefined) {
      resolved.encoder3 = msg.encoder3;
    }
    else {
      resolved.encoder3 = false
    }

    if (msg.encoder1_offset !== undefined) {
      resolved.encoder1_offset = msg.encoder1_offset;
    }
    else {
      resolved.encoder1_offset = 0
    }

    if (msg.encoder2_offset !== undefined) {
      resolved.encoder2_offset = msg.encoder2_offset;
    }
    else {
      resolved.encoder2_offset = 0
    }

    if (msg.encoder3_offset !== undefined) {
      resolved.encoder3_offset = msg.encoder3_offset;
    }
    else {
      resolved.encoder3_offset = 0
    }

    return resolved;
    }
};

class SettingResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
    }
    else {
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SettingResponse
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SettingResponse
    let len;
    let data = new SettingResponse(null);
    return data;
  }

  static getMessageSize(object) {
    return 0;
  }

  static datatype() {
    // Returns string type for a service object
    return 'underwater_robot/SettingResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'd41d8cd98f00b204e9800998ecf8427e';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new SettingResponse(null);
    return resolved;
    }
};

module.exports = {
  Request: SettingRequest,
  Response: SettingResponse,
  md5sum() { return 'd545f84ec040b08d5bf2fc0f795d8d0a'; },
  datatype() { return 'underwater_robot/Setting'; }
};
