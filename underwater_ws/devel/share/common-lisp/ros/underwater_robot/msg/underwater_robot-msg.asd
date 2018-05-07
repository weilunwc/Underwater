
(cl:in-package :asdf)

(defsystem "underwater_robot-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "Baro" :depends-on ("_package_Baro"))
    (:file "_package_Baro" :depends-on ("_package"))
    (:file "Cmd" :depends-on ("_package_Cmd"))
    (:file "_package_Cmd" :depends-on ("_package"))
    (:file "Config" :depends-on ("_package_Config"))
    (:file "_package_Config" :depends-on ("_package"))
    (:file "Encoder" :depends-on ("_package_Encoder"))
    (:file "_package_Encoder" :depends-on ("_package"))
    (:file "Euler" :depends-on ("_package_Euler"))
    (:file "_package_Euler" :depends-on ("_package"))
    (:file "Imu" :depends-on ("_package_Imu"))
    (:file "_package_Imu" :depends-on ("_package"))
  ))