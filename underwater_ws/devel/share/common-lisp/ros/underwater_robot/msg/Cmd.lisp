; Auto-generated. Do not edit!


(cl:in-package underwater_robot-msg)


;//! \htmlinclude Cmd.msg.html

(cl:defclass <Cmd> (roslisp-msg-protocol:ros-message)
  ((mode
    :reader mode
    :initarg :mode
    :type cl:fixnum
    :initform 0)
   (spinning_speed
    :reader spinning_speed
    :initarg :spinning_speed
    :type cl:fixnum
    :initform 0)
   (flipping_angle
    :reader flipping_angle
    :initarg :flipping_angle
    :type cl:fixnum
    :initform 0)
   (flipping_speed
    :reader flipping_speed
    :initarg :flipping_speed
    :type cl:fixnum
    :initform 0))
)

(cl:defclass Cmd (<Cmd>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Cmd>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Cmd)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name underwater_robot-msg:<Cmd> is deprecated: use underwater_robot-msg:Cmd instead.")))

(cl:ensure-generic-function 'mode-val :lambda-list '(m))
(cl:defmethod mode-val ((m <Cmd>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader underwater_robot-msg:mode-val is deprecated.  Use underwater_robot-msg:mode instead.")
  (mode m))

(cl:ensure-generic-function 'spinning_speed-val :lambda-list '(m))
(cl:defmethod spinning_speed-val ((m <Cmd>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader underwater_robot-msg:spinning_speed-val is deprecated.  Use underwater_robot-msg:spinning_speed instead.")
  (spinning_speed m))

(cl:ensure-generic-function 'flipping_angle-val :lambda-list '(m))
(cl:defmethod flipping_angle-val ((m <Cmd>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader underwater_robot-msg:flipping_angle-val is deprecated.  Use underwater_robot-msg:flipping_angle instead.")
  (flipping_angle m))

(cl:ensure-generic-function 'flipping_speed-val :lambda-list '(m))
(cl:defmethod flipping_speed-val ((m <Cmd>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader underwater_robot-msg:flipping_speed-val is deprecated.  Use underwater_robot-msg:flipping_speed instead.")
  (flipping_speed m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Cmd>) ostream)
  "Serializes a message object of type '<Cmd>"
  (cl:let* ((signed (cl:slot-value msg 'mode)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'spinning_speed)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'flipping_angle)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'flipping_speed)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Cmd>) istream)
  "Deserializes a message object of type '<Cmd>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'mode) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'spinning_speed) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'flipping_angle) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'flipping_speed) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Cmd>)))
  "Returns string type for a message object of type '<Cmd>"
  "underwater_robot/Cmd")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Cmd)))
  "Returns string type for a message object of type 'Cmd"
  "underwater_robot/Cmd")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Cmd>)))
  "Returns md5sum for a message object of type '<Cmd>"
  "26a53f33e9dfd663b81918f42c8e516a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Cmd)))
  "Returns md5sum for a message object of type 'Cmd"
  "26a53f33e9dfd663b81918f42c8e516a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Cmd>)))
  "Returns full string definition for message of type '<Cmd>"
  (cl:format cl:nil "int16 mode~%int16 spinning_speed~%int16 flipping_angle~%int16 flipping_speed~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Cmd)))
  "Returns full string definition for message of type 'Cmd"
  (cl:format cl:nil "int16 mode~%int16 spinning_speed~%int16 flipping_angle~%int16 flipping_speed~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Cmd>))
  (cl:+ 0
     2
     2
     2
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Cmd>))
  "Converts a ROS message object to a list"
  (cl:list 'Cmd
    (cl:cons ':mode (mode msg))
    (cl:cons ':spinning_speed (spinning_speed msg))
    (cl:cons ':flipping_angle (flipping_angle msg))
    (cl:cons ':flipping_speed (flipping_speed msg))
))
