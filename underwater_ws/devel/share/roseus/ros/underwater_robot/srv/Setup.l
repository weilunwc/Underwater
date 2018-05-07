;; Auto-generated. Do not edit!


(when (boundp 'underwater_robot::Setup)
  (if (not (find-package "UNDERWATER_ROBOT"))
    (make-package "UNDERWATER_ROBOT"))
  (shadow 'Setup (find-package "UNDERWATER_ROBOT")))
(unless (find-package "UNDERWATER_ROBOT::SETUP")
  (make-package "UNDERWATER_ROBOT::SETUP"))
(unless (find-package "UNDERWATER_ROBOT::SETUPREQUEST")
  (make-package "UNDERWATER_ROBOT::SETUPREQUEST"))
(unless (find-package "UNDERWATER_ROBOT::SETUPRESPONSE")
  (make-package "UNDERWATER_ROBOT::SETUPRESPONSE"))

(in-package "ROS")





(defclass underwater_robot::SetupRequest
  :super ros::object
  :slots (_dummy ))

(defmethod underwater_robot::SetupRequest
  (:init
   (&key
    ((:dummy __dummy) nil)
    )
   (send-super :init)
   (setq _dummy __dummy)
   self)
  (:dummy
   (&optional __dummy)
   (if __dummy (setq _dummy __dummy)) _dummy)
  (:serialization-length
   ()
   (+
    ;; bool _dummy
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _dummy
       (if _dummy (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _dummy
     (setq _dummy (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass underwater_robot::SetupResponse
  :super ros::object
  :slots (_done _imu _barometer _encoder1 _encoder2 _encoder3 _encoder1_offset _encoder2_offset _encoder3_offset ))

(defmethod underwater_robot::SetupResponse
  (:init
   (&key
    ((:done __done) nil)
    ((:imu __imu) nil)
    ((:barometer __barometer) nil)
    ((:encoder1 __encoder1) nil)
    ((:encoder2 __encoder2) nil)
    ((:encoder3 __encoder3) nil)
    ((:encoder1_offset __encoder1_offset) 0)
    ((:encoder2_offset __encoder2_offset) 0)
    ((:encoder3_offset __encoder3_offset) 0)
    )
   (send-super :init)
   (setq _done __done)
   (setq _imu __imu)
   (setq _barometer __barometer)
   (setq _encoder1 __encoder1)
   (setq _encoder2 __encoder2)
   (setq _encoder3 __encoder3)
   (setq _encoder1_offset (round __encoder1_offset))
   (setq _encoder2_offset (round __encoder2_offset))
   (setq _encoder3_offset (round __encoder3_offset))
   self)
  (:done
   (&optional __done)
   (if __done (setq _done __done)) _done)
  (:imu
   (&optional __imu)
   (if __imu (setq _imu __imu)) _imu)
  (:barometer
   (&optional __barometer)
   (if __barometer (setq _barometer __barometer)) _barometer)
  (:encoder1
   (&optional __encoder1)
   (if __encoder1 (setq _encoder1 __encoder1)) _encoder1)
  (:encoder2
   (&optional __encoder2)
   (if __encoder2 (setq _encoder2 __encoder2)) _encoder2)
  (:encoder3
   (&optional __encoder3)
   (if __encoder3 (setq _encoder3 __encoder3)) _encoder3)
  (:encoder1_offset
   (&optional __encoder1_offset)
   (if __encoder1_offset (setq _encoder1_offset __encoder1_offset)) _encoder1_offset)
  (:encoder2_offset
   (&optional __encoder2_offset)
   (if __encoder2_offset (setq _encoder2_offset __encoder2_offset)) _encoder2_offset)
  (:encoder3_offset
   (&optional __encoder3_offset)
   (if __encoder3_offset (setq _encoder3_offset __encoder3_offset)) _encoder3_offset)
  (:serialization-length
   ()
   (+
    ;; bool _done
    1
    ;; bool _imu
    1
    ;; bool _barometer
    1
    ;; bool _encoder1
    1
    ;; bool _encoder2
    1
    ;; bool _encoder3
    1
    ;; int16 _encoder1_offset
    2
    ;; int16 _encoder2_offset
    2
    ;; int16 _encoder3_offset
    2
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _done
       (if _done (write-byte -1 s) (write-byte 0 s))
     ;; bool _imu
       (if _imu (write-byte -1 s) (write-byte 0 s))
     ;; bool _barometer
       (if _barometer (write-byte -1 s) (write-byte 0 s))
     ;; bool _encoder1
       (if _encoder1 (write-byte -1 s) (write-byte 0 s))
     ;; bool _encoder2
       (if _encoder2 (write-byte -1 s) (write-byte 0 s))
     ;; bool _encoder3
       (if _encoder3 (write-byte -1 s) (write-byte 0 s))
     ;; int16 _encoder1_offset
       (write-word _encoder1_offset s)
     ;; int16 _encoder2_offset
       (write-word _encoder2_offset s)
     ;; int16 _encoder3_offset
       (write-word _encoder3_offset s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _done
     (setq _done (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _imu
     (setq _imu (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _barometer
     (setq _barometer (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _encoder1
     (setq _encoder1 (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _encoder2
     (setq _encoder2 (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _encoder3
     (setq _encoder3 (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; int16 _encoder1_offset
     (setq _encoder1_offset (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; int16 _encoder2_offset
     (setq _encoder2_offset (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; int16 _encoder3_offset
     (setq _encoder3_offset (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(defclass underwater_robot::Setup
  :super ros::object
  :slots ())

(setf (get underwater_robot::Setup :md5sum-) "81bdda0e5e12240216c90fa743ee071e")
(setf (get underwater_robot::Setup :datatype-) "underwater_robot/Setup")
(setf (get underwater_robot::Setup :request) underwater_robot::SetupRequest)
(setf (get underwater_robot::Setup :response) underwater_robot::SetupResponse)

(defmethod underwater_robot::SetupRequest
  (:response () (instance underwater_robot::SetupResponse :init)))

(setf (get underwater_robot::SetupRequest :md5sum-) "81bdda0e5e12240216c90fa743ee071e")
(setf (get underwater_robot::SetupRequest :datatype-) "underwater_robot/SetupRequest")
(setf (get underwater_robot::SetupRequest :definition-)
      "bool dummy
---
bool done
bool imu
bool barometer
bool encoder1
bool encoder2
bool encoder3
int16 encoder1_offset
int16 encoder2_offset
int16 encoder3_offset

")

(setf (get underwater_robot::SetupResponse :md5sum-) "81bdda0e5e12240216c90fa743ee071e")
(setf (get underwater_robot::SetupResponse :datatype-) "underwater_robot/SetupResponse")
(setf (get underwater_robot::SetupResponse :definition-)
      "bool dummy
---
bool done
bool imu
bool barometer
bool encoder1
bool encoder2
bool encoder3
int16 encoder1_offset
int16 encoder2_offset
int16 encoder3_offset

")



(provide :underwater_robot/Setup "81bdda0e5e12240216c90fa743ee071e")


