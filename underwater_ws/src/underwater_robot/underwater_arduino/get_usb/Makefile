all: usb0 usb1 usb2 usb3
	cd ./usb0; make
	cd ./usb1; make
	cd ./usb2; make
	cd ./usb3; make


clean:
	cd ./usb0; make clean
	cd ./usb1; make clean
	cd ./usb2; make clean
	cd ./usb3; make clean

upload:
	cd ./usb0; make upload
	cd ./usb1; make upload
	cd ./usb2; make upload
	cd ./usb3; make upload


run:
	cd ./usb0; make upload
	cd ./usb1; make upload
	cd ./usb2; make upload
	cd ./usb3; make upload
	roslaunch underwater_robot underwater.launch
