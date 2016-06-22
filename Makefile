BOARD_TAG = atmega328
#ARDUINO_LIBS = SPI CAN

ISP_PROG = arduinoisp
include /usr/share/arduino/Arduino.mk

ARDUINO_PORT = /dev/ttyUSB0

burn: $(TARGET_EEP) $(TARGET_HEX) verify_size
	avrdude -V -patmega328p -carduinoisp -Uflash:w:$(TARGET_HEX):i
