java -Djava.library.path=java/kosch/ -jar tool/NanoVMTool.jar -f /dev/ttyUSB0 tool/config/Mega32.config classes LedBlink

avrdude -p m32 -P /dev/ttyUSB1 -c avr910 -v -U eeprom:w:NanoVM_eeprom.hex

fuse calc
