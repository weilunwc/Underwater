;; Auto-generated. Do not edit!


(when (boundp 'underwater_msg::Imu)
  (if (not (find-package "UNDERWATER_MSG"))
    (make-package "UNDERWATER_MSG"))
  (shadow 'Imu (find-package "UNDERWATER_MSG")))
(unless (find-package "UNDERWATER_MSG::IMU")
  (make-package "UNDERWATER_MSG::IMU"))

(in-package "ROS")
;;//! \htmlinclude Imu.msg.html


(defclass underwater_msg::Imu
  :super ros::object
  :slots (_roll _pitch _yaw ))

(defmethod underwater_msg::Imu
  (:init
   (&key
    ((:roll __roll) 0.0)
    ((:pitch __pitch) 0.0)
    ((:yaw __yaw) 0.0)
    )
   (send-super :init)
   (setq _roll (float __roll))
   (setq _pitch (float __pitch))
   (setq _yaw (float __yaw))
   self)
  (:roll
   (&optional __roll)
   (if __roll (setq _roll __roll)) _roll)
  (:pitch
   (&optional __pitch)
   (if __pitch (setq _pitch __pitch)) _pitch)
  (:yaw
   (&optional __yaw)
   (if __yaw (setq _yaw __yaw)) _yaw)
  (:serialization-length
   ()
   (+
    ;; float32 _roll
    4
    ;; float32 _pitch
    4
    ;; float32 _yaw
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _roll
       (sys::poke _roll (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _pitch
       (sys::poke _pitch (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _yaw
       (sys::poke _yaw (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _roll
     (setq _roll (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _pitch
     (setq _pitch (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _yaw
     (setq _yaw (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get underwater_msg::Imu :md5sum-) "c66f4de7f99199dd8e863fffbef112ad")
(setf (get underwater_msg::Imu :datatype-) "underwater_msg/Imu")
(setf (get underwater_msg::Imu :definition-)
      "float32 roll
float32 pitch
float32 yaw

")



(provide :underwater_msg/Imu "c66f4de7f99199dd8e863fffbef112ad")


