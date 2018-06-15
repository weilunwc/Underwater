all: center_motor motor_1 motor_2 motor_3
	cd ./center_motor; make
	cd ./motor_1; make
	cd ./motor_2; make
	cd ./motor_3; make


clean:
	cd ./center_motor; make clean
	cd ./motor_1; make clean
	cd ./motor_2; make clean
	cd ./motor_3; make clean

upload:
	cd ./center_motor; make upload
	cd ./motor_1; make upload
	cd ./motor_2; make upload
	cd ./motor_3; make upload


run:
	cd ./center_motor; make upload
	cd ./motor_1; make upload
	cd ./motor_2; make upload
	cd ./motor_3; make upload
