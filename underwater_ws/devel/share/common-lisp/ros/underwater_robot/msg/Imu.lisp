; Auto-generated. Do not edit!


(cl:in-package underwater_robot-msg)


;//! \htmlinclude Imu.msg.html

(cl:defclass <Imu> (roslisp-msg-protocol:ros-message)
  ((roll
    :reader roll
    :initarg :roll
    :type cl:float
    :initform 0.0)
   (pitch
    :reader pitch
    :initarg :pitch
    :type cl:float
    :initform 0.0)
   (yaw
    :reader yaw
    :initarg :yaw
    :type cl:float
    :initform 0.0))
)

(cl:defclass Imu (<Imu>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Imu>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Imu)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name underwater_robot-msg:<Imu> is deprecated: use underwater_robot-msg:Imu instead.")))

(cl:ensure-generic-function 'roll-val :lambda-list '(m))
(cl:defmethod roll-val ((m <Imu>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader underwater_robot-msg:roll-val is deprecated.  Use underwater_robot-msg:roll instead.")
  (roll m))

(cl:ensure-generic-function 'pitch-val :lambda-list '(m))
(cl:defmethod pitch-val ((m <Imu>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader underwater_robot-msg:pitch-val is deprecated.  Use underwater_robot-msg:pitch instead.")
  (pitch m))

(cl:ensure-generic-function 'yaw-val :lambda-list '(m))
(cl:defmethod yaw-val ((m <Imu>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader underwater_robot-msg:yaw-val is deprecated.  Use underwater_robot-msg:yaw instead.")
  (yaw m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Imu>) ostream)
  "Serializes a message object of type '<Imu>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'roll))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'pitch))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'yaw))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Imu>) istream)
  "Deserializes a message object of type '<Imu>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'roll) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'pitch) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'yaw) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Imu>)))
  "Returns string type for a message object of type '<Imu>"
  "underwater_robot/Imu")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Imu)))
  "Returns string type for a message object of type 'Imu"
  "underwater_robot/Imu")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Imu>)))
  "Returns md5sum for a message object of type '<Imu>"
  "c66f4de7f99199dd8e863fffbef112ad")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Imu)))
  "Returns md5sum for a message object of type 'Imu"
  "c66f4de7f99199dd8e863fffbef112ad")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Imu>)))
  "Returns full string definition for message of type '<Imu>"
  (cl:format cl:nil "float32 roll~%float32 pitch~%float32 yaw~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Imu)))
  "Returns full string definition for message of type 'Imu"
  (cl:format cl:nil "float32 roll~%float32 pitch~%float32 yaw~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Imu>))
  (cl:+ 0
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Imu>))
  "Converts a ROS message object to a list"
  (cl:list 'Imu
    (cl:cons ':roll (roll msg))
    (cl:cons ':pitch (pitch msg))
    (cl:cons ':yaw (yaw msg))
))
