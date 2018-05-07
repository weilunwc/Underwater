;; Auto-generated. Do not edit!


(when (boundp 'underwater_msg::Cmd)
  (if (not (find-package "UNDERWATER_MSG"))
    (make-package "UNDERWATER_MSG"))
  (shadow 'Cmd (find-package "UNDERWATER_MSG")))
(unless (find-package "UNDERWATER_MSG::CMD")
  (make-package "UNDERWATER_MSG::CMD"))

(in-package "ROS")
;;//! \htmlinclude Cmd.msg.html


(defclass underwater_msg::Cmd
  :super ros::object
  :slots (_mode _spinning_speed _flipping_angle _flipping_speed ))

(defmethod underwater_msg::Cmd
  (:init
   (&key
    ((:mode __mode) 0)
    ((:spinning_speed __spinning_speed) 0)
    ((:flipping_angle __flipping_angle) 0)
    ((:flipping_speed __flipping_speed) 0)
    )
   (send-super :init)
   (setq _mode (round __mode))
   (setq _spinning_speed (round __spinning_speed))
   (setq _flipping_angle (round __flipping_angle))
   (setq _flipping_speed (round __flipping_speed))
   self)
  (:mode
   (&optional __mode)
   (if __mode (setq _mode __mode)) _mode)
  (:spinning_speed
   (&optional __spinning_speed)
   (if __spinning_speed (setq _spinning_speed __spinning_speed)) _spinning_speed)
  (:flipping_angle
   (&optional __flipping_angle)
   (if __flipping_angle (setq _flipping_angle __flipping_angle)) _flipping_angle)
  (:flipping_speed
   (&optional __flipping_speed)
   (if __flipping_speed (setq _flipping_speed __flipping_speed)) _flipping_speed)
  (:serialization-length
   ()
   (+
    ;; int16 _mode
    2
    ;; int16 _spinning_speed
    2
    ;; int16 _flipping_angle
    2
    ;; int16 _flipping_speed
    2
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int16 _mode
       (write-word _mode s)
     ;; int16 _spinning_speed
       (write-word _spinning_speed s)
     ;; int16 _flipping_angle
       (write-word _flipping_angle s)
     ;; int16 _flipping_speed
       (write-word _flipping_speed s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int16 _mode
     (setq _mode (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; int16 _spinning_speed
     (setq _spinning_speed (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; int16 _flipping_angle
     (setq _flipping_angle (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; int16 _flipping_speed
     (setq _flipping_speed (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(setf (get underwater_msg::Cmd :md5sum-) "26a53f33e9dfd663b81918f42c8e516a")
(setf (get underwater_msg::Cmd :datatype-) "underwater_msg/Cmd")
(setf (get underwater_msg::Cmd :definition-)
      "int16 mode
int16 spinning_speed
int16 flipping_angle
int16 flipping_speed

")



(provide :underwater_msg/Cmd "26a53f33e9dfd663b81918f42c8e516a")


