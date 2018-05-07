; Auto-generated. Do not edit!


(cl:in-package underwater_robot-msg)


;//! \htmlinclude Baro.msg.html

(cl:defclass <Baro> (roslisp-msg-protocol:ros-message)
  ((depth
    :reader depth
    :initarg :depth
    :type cl:float
    :initform 0.0)
   (temp
    :reader temp
    :initarg :temp
    :type cl:float
    :initform 0.0))
)

(cl:defclass Baro (<Baro>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Baro>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Baro)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name underwater_robot-msg:<Baro> is deprecated: use underwater_robot-msg:Baro instead.")))

(cl:ensure-generic-function 'depth-val :lambda-list '(m))
(cl:defmethod depth-val ((m <Baro>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader underwater_robot-msg:depth-val is deprecated.  Use underwater_robot-msg:depth instead.")
  (depth m))

(cl:ensure-generic-function 'temp-val :lambda-list '(m))
(cl:defmethod temp-val ((m <Baro>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader underwater_robot-msg:temp-val is deprecated.  Use underwater_robot-msg:temp instead.")
  (temp m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Baro>) ostream)
  "Serializes a message object of type '<Baro>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'depth))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'temp))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Baro>) istream)
  "Deserializes a message object of type '<Baro>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'depth) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'temp) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Baro>)))
  "Returns string type for a message object of type '<Baro>"
  "underwater_robot/Baro")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Baro)))
  "Returns string type for a message object of type 'Baro"
  "underwater_robot/Baro")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Baro>)))
  "Returns md5sum for a message object of type '<Baro>"
  "b11505eab6c52277745b4ae83c35f503")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Baro)))
  "Returns md5sum for a message object of type 'Baro"
  "b11505eab6c52277745b4ae83c35f503")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Baro>)))
  "Returns full string definition for message of type '<Baro>"
  (cl:format cl:nil "float32 depth~%float32 temp~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Baro)))
  "Returns full string definition for message of type 'Baro"
  (cl:format cl:nil "float32 depth~%float32 temp~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Baro>))
  (cl:+ 0
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Baro>))
  "Converts a ROS message object to a list"
  (cl:list 'Baro
    (cl:cons ':depth (depth msg))
    (cl:cons ':temp (temp msg))
))
