; Auto-generated. Do not edit!


(cl:in-package underwater_robot-srv)


;//! \htmlinclude Setup-request.msg.html

(cl:defclass <Setup-request> (roslisp-msg-protocol:ros-message)
  ((dummy
    :reader dummy
    :initarg :dummy
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass Setup-request (<Setup-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Setup-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Setup-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name underwater_robot-srv:<Setup-request> is deprecated: use underwater_robot-srv:Setup-request instead.")))

(cl:ensure-generic-function 'dummy-val :lambda-list '(m))
(cl:defmethod dummy-val ((m <Setup-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader underwater_robot-srv:dummy-val is deprecated.  Use underwater_robot-srv:dummy instead.")
  (dummy m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Setup-request>) ostream)
  "Serializes a message object of type '<Setup-request>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'dummy) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Setup-request>) istream)
  "Deserializes a message object of type '<Setup-request>"
    (cl:setf (cl:slot-value msg 'dummy) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Setup-request>)))
  "Returns string type for a service object of type '<Setup-request>"
  "underwater_robot/SetupRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Setup-request)))
  "Returns string type for a service object of type 'Setup-request"
  "underwater_robot/SetupRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Setup-request>)))
  "Returns md5sum for a message object of type '<Setup-request>"
  "81bdda0e5e12240216c90fa743ee071e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Setup-request)))
  "Returns md5sum for a message object of type 'Setup-request"
  "81bdda0e5e12240216c90fa743ee071e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Setup-request>)))
  "Returns full string definition for message of type '<Setup-request>"
  (cl:format cl:nil "bool dummy~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Setup-request)))
  "Returns full string definition for message of type 'Setup-request"
  (cl:format cl:nil "bool dummy~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Setup-request>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Setup-request>))
  "Converts a ROS message object to a list"
  (cl:list 'Setup-request
    (cl:cons ':dummy (dummy msg))
))
;//! \htmlinclude Setup-response.msg.html

(cl:defclass <Setup-response> (roslisp-msg-protocol:ros-message)
  ((done
    :reader done
    :initarg :done
    :type cl:boolean
    :initform cl:nil)
   (imu
    :reader imu
    :initarg :imu
    :type cl:boolean
    :initform cl:nil)
   (barometer
    :reader barometer
    :initarg :barometer
    :type cl:boolean
    :initform cl:nil)
   (encoder1
    :reader encoder1
    :initarg :encoder1
    :type cl:boolean
    :initform cl:nil)
   (encoder2
    :reader encoder2
    :initarg :encoder2
    :type cl:boolean
    :initform cl:nil)
   (encoder3
    :reader encoder3
    :initarg :encoder3
    :type cl:boolean
    :initform cl:nil)
   (encoder1_offset
    :reader encoder1_offset
    :initarg :encoder1_offset
    :type cl:fixnum
    :initform 0)
   (encoder2_offset
    :reader encoder2_offset
    :initarg :encoder2_offset
    :type cl:fixnum
    :initform 0)
   (encoder3_offset
    :reader encoder3_offset
    :initarg :encoder3_offset
    :type cl:fixnum
    :initform 0))
)

(cl:defclass Setup-response (<Setup-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Setup-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Setup-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name underwater_robot-srv:<Setup-response> is deprecated: use underwater_robot-srv:Setup-response instead.")))

(cl:ensure-generic-function 'done-val :lambda-list '(m))
(cl:defmethod done-val ((m <Setup-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader underwater_robot-srv:done-val is deprecated.  Use underwater_robot-srv:done instead.")
  (done m))

(cl:ensure-generic-function 'imu-val :lambda-list '(m))
(cl:defmethod imu-val ((m <Setup-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader underwater_robot-srv:imu-val is deprecated.  Use underwater_robot-srv:imu instead.")
  (imu m))

(cl:ensure-generic-function 'barometer-val :lambda-list '(m))
(cl:defmethod barometer-val ((m <Setup-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader underwater_robot-srv:barometer-val is deprecated.  Use underwater_robot-srv:barometer instead.")
  (barometer m))

(cl:ensure-generic-function 'encoder1-val :lambda-list '(m))
(cl:defmethod encoder1-val ((m <Setup-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader underwater_robot-srv:encoder1-val is deprecated.  Use underwater_robot-srv:encoder1 instead.")
  (encoder1 m))

(cl:ensure-generic-function 'encoder2-val :lambda-list '(m))
(cl:defmethod encoder2-val ((m <Setup-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader underwater_robot-srv:encoder2-val is deprecated.  Use underwater_robot-srv:encoder2 instead.")
  (encoder2 m))

(cl:ensure-generic-function 'encoder3-val :lambda-list '(m))
(cl:defmethod encoder3-val ((m <Setup-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader underwater_robot-srv:encoder3-val is deprecated.  Use underwater_robot-srv:encoder3 instead.")
  (encoder3 m))

(cl:ensure-generic-function 'encoder1_offset-val :lambda-list '(m))
(cl:defmethod encoder1_offset-val ((m <Setup-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader underwater_robot-srv:encoder1_offset-val is deprecated.  Use underwater_robot-srv:encoder1_offset instead.")
  (encoder1_offset m))

(cl:ensure-generic-function 'encoder2_offset-val :lambda-list '(m))
(cl:defmethod encoder2_offset-val ((m <Setup-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader underwater_robot-srv:encoder2_offset-val is deprecated.  Use underwater_robot-srv:encoder2_offset instead.")
  (encoder2_offset m))

(cl:ensure-generic-function 'encoder3_offset-val :lambda-list '(m))
(cl:defmethod encoder3_offset-val ((m <Setup-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader underwater_robot-srv:encoder3_offset-val is deprecated.  Use underwater_robot-srv:encoder3_offset instead.")
  (encoder3_offset m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Setup-response>) ostream)
  "Serializes a message object of type '<Setup-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'done) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'imu) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'barometer) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'encoder1) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'encoder2) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'encoder3) 1 0)) ostream)
  (cl:let* ((signed (cl:slot-value msg 'encoder1_offset)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'encoder2_offset)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'encoder3_offset)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Setup-response>) istream)
  "Deserializes a message object of type '<Setup-response>"
    (cl:setf (cl:slot-value msg 'done) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'imu) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'barometer) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'encoder1) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'encoder2) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'encoder3) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'encoder1_offset) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'encoder2_offset) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'encoder3_offset) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Setup-response>)))
  "Returns string type for a service object of type '<Setup-response>"
  "underwater_robot/SetupResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Setup-response)))
  "Returns string type for a service object of type 'Setup-response"
  "underwater_robot/SetupResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Setup-response>)))
  "Returns md5sum for a message object of type '<Setup-response>"
  "81bdda0e5e12240216c90fa743ee071e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Setup-response)))
  "Returns md5sum for a message object of type 'Setup-response"
  "81bdda0e5e12240216c90fa743ee071e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Setup-response>)))
  "Returns full string definition for message of type '<Setup-response>"
  (cl:format cl:nil "bool done~%bool imu~%bool barometer~%bool encoder1~%bool encoder2~%bool encoder3~%int16 encoder1_offset~%int16 encoder2_offset~%int16 encoder3_offset~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Setup-response)))
  "Returns full string definition for message of type 'Setup-response"
  (cl:format cl:nil "bool done~%bool imu~%bool barometer~%bool encoder1~%bool encoder2~%bool encoder3~%int16 encoder1_offset~%int16 encoder2_offset~%int16 encoder3_offset~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Setup-response>))
  (cl:+ 0
     1
     1
     1
     1
     1
     1
     2
     2
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Setup-response>))
  "Converts a ROS message object to a list"
  (cl:list 'Setup-response
    (cl:cons ':done (done msg))
    (cl:cons ':imu (imu msg))
    (cl:cons ':barometer (barometer msg))
    (cl:cons ':encoder1 (encoder1 msg))
    (cl:cons ':encoder2 (encoder2 msg))
    (cl:cons ':encoder3 (encoder3 msg))
    (cl:cons ':encoder1_offset (encoder1_offset msg))
    (cl:cons ':encoder2_offset (encoder2_offset msg))
    (cl:cons ':encoder3_offset (encoder3_offset msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'Setup)))
  'Setup-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'Setup)))
  'Setup-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Setup)))
  "Returns string type for a service object of type '<Setup>"
  "underwater_robot/Setup")