;; Auto-generated. Do not edit!


(when (boundp 'underwater_msg::Encoder)
  (if (not (find-package "UNDERWATER_MSG"))
    (make-package "UNDERWATER_MSG"))
  (shadow 'Encoder (find-package "UNDERWATER_MSG")))
(unless (find-package "UNDERWATER_MSG::ENCODER")
  (make-package "UNDERWATER_MSG::ENCODER"))

(in-package "ROS")
;;//! \htmlinclude Encoder.msg.html


(defclass underwater_msg::Encoder
  :super ros::object
  :slots (_encoder_angle _encoder_speed ))

(defmethod underwater_msg::Encoder
  (:init
   (&key
    ((:encoder_angle __encoder_angle) 0.0)
    ((:encoder_speed __encoder_speed) 0.0)
    )
   (send-super :init)
   (setq _encoder_angle (float __encoder_angle))
   (setq _encoder_speed (float __encoder_speed))
   self)
  (:encoder_angle
   (&optional __encoder_angle)
   (if __encoder_angle (setq _encoder_angle __encoder_angle)) _encoder_angle)
  (:encoder_speed
   (&optional __encoder_speed)
   (if __encoder_speed (setq _encoder_speed __encoder_speed)) _encoder_speed)
  (:serialization-length
   ()
   (+
    ;; float32 _encoder_angle
    4
    ;; float32 _encoder_speed
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _encoder_angle
       (sys::poke _encoder_angle (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _encoder_speed
       (sys::poke _encoder_speed (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _encoder_angle
     (setq _encoder_angle (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _encoder_speed
     (setq _encoder_speed (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get underwater_msg::Encoder :md5sum-) "9991f74e6b5a800497ccb5b53c4ed151")
(setf (get underwater_msg::Encoder :datatype-) "underwater_msg/Encoder")
(setf (get underwater_msg::Encoder :definition-)
      "float32 encoder_angle
float32 encoder_speed

")



(provide :underwater_msg/Encoder "9991f74e6b5a800497ccb5b53c4ed151")


