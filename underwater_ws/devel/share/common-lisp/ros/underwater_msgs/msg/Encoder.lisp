; Auto-generated. Do not edit!


(cl:in-package underwater_msgs-msg)


;//! \htmlinclude Encoder.msg.html

(cl:defclass <Encoder> (roslisp-msg-protocol:ros-message)
  ((encoder_angle
    :reader encoder_angle
    :initarg :encoder_angle
    :type cl:float
    :initform 0.0)
   (encoder_speed
    :reader encoder_speed
    :initarg :encoder_speed
    :type cl:float
    :initform 0.0))
)

(cl:defclass Encoder (<Encoder>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Encoder>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Encoder)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name underwater_msgs-msg:<Encoder> is deprecated: use underwater_msgs-msg:Encoder instead.")))

(cl:ensure-generic-function 'encoder_angle-val :lambda-list '(m))
(cl:defmethod encoder_angle-val ((m <Encoder>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader underwater_msgs-msg:encoder_angle-val is deprecated.  Use underwater_msgs-msg:encoder_angle instead.")
  (encoder_angle m))

(cl:ensure-generic-function 'encoder_speed-val :lambda-list '(m))
(cl:defmethod encoder_speed-val ((m <Encoder>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader underwater_msgs-msg:encoder_speed-val is deprecated.  Use underwater_msgs-msg:encoder_speed instead.")
  (encoder_speed m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Encoder>) ostream)
  "Serializes a message object of type '<Encoder>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'encoder_angle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'encoder_speed))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Encoder>) istream)
  "Deserializes a message object of type '<Encoder>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'encoder_angle) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'encoder_speed) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Encoder>)))
  "Returns string type for a message object of type '<Encoder>"
  "underwater_msgs/Encoder")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Encoder)))
  "Returns string type for a message object of type 'Encoder"
  "underwater_msgs/Encoder")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Encoder>)))
  "Returns md5sum for a message object of type '<Encoder>"
  "9991f74e6b5a800497ccb5b53c4ed151")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Encoder)))
  "Returns md5sum for a message object of type 'Encoder"
  "9991f74e6b5a800497ccb5b53c4ed151")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Encoder>)))
  "Returns full string definition for message of type '<Encoder>"
  (cl:format cl:nil "float32 encoder_angle~%float32 encoder_speed~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Encoder)))
  "Returns full string definition for message of type 'Encoder"
  (cl:format cl:nil "float32 encoder_angle~%float32 encoder_speed~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Encoder>))
  (cl:+ 0
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Encoder>))
  "Converts a ROS message object to a list"
  (cl:list 'Encoder
    (cl:cons ':encoder_angle (encoder_angle msg))
    (cl:cons ':encoder_speed (encoder_speed msg))
))
