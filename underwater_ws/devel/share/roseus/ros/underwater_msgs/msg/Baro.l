;; Auto-generated. Do not edit!


(when (boundp 'underwater_msgs::Baro)
  (if (not (find-package "UNDERWATER_MSGS"))
    (make-package "UNDERWATER_MSGS"))
  (shadow 'Baro (find-package "UNDERWATER_MSGS")))
(unless (find-package "UNDERWATER_MSGS::BARO")
  (make-package "UNDERWATER_MSGS::BARO"))

(in-package "ROS")
;;//! \htmlinclude Baro.msg.html


(defclass underwater_msgs::Baro
  :super ros::object
  :slots (_depth _temp ))

(defmethod underwater_msgs::Baro
  (:init
   (&key
    ((:depth __depth) 0.0)
    ((:temp __temp) 0.0)
    )
   (send-super :init)
   (setq _depth (float __depth))
   (setq _temp (float __temp))
   self)
  (:depth
   (&optional __depth)
   (if __depth (setq _depth __depth)) _depth)
  (:temp
   (&optional __temp)
   (if __temp (setq _temp __temp)) _temp)
  (:serialization-length
   ()
   (+
    ;; float32 _depth
    4
    ;; float32 _temp
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _depth
       (sys::poke _depth (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _temp
       (sys::poke _temp (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _depth
     (setq _depth (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _temp
     (setq _temp (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get underwater_msgs::Baro :md5sum-) "b11505eab6c52277745b4ae83c35f503")
(setf (get underwater_msgs::Baro :datatype-) "underwater_msgs/Baro")
(setf (get underwater_msgs::Baro :definition-)
      "float32 depth
float32 temp

")



(provide :underwater_msgs/Baro "b11505eab6c52277745b4ae83c35f503")


