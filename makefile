all:
	platformio run

upload-small:
	platformio run -e nanoatmega168 -t upload --upload-port=/dev/ttyUSB0
upload-big:
	platformio run -e nanoatmega328 -t upload --upload-port=/dev/ttyUSB0
upload-wireless:
	platformio run -t upload --upload-port=/dev/ttyUSB0
