
(cl:in-package :asdf)

(defsystem "underwater_robot-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "Setting" :depends-on ("_package_Setting"))
    (:file "_package_Setting" :depends-on ("_package"))
    (:file "Setup" :depends-on ("_package_Setup"))
    (:file "_package_Setup" :depends-on ("_package"))
  ))