#
#  Makefile for Mega32 test version of the NanoVM
#

VERSION = 1.0
CONFIG = Mega32.config
DEVICE = atmega32
DEFAULT_FILE = ../kosch/Default
ROOT_DIR = ../../..
# CFLAGS += -DDEBUG

# AVR compiler setup
PREFIX =
CC = $(PREFIX)avr-gcc
OBJCOPY = $(PREFIX)avr-objcopy
OBJDUMP = $(PREFIX)avr-objdump

# AVR compiler and linker flags
CFLAGS += -Os -ffunction-sections -DAVR -I. -mmcu=$(DEVICE) -DVERSION="\"$(VERSION)\""
CLDFLAGS += -mmcu=$(DEVICE)

# build intel hex files
all: NanoVM.hex NanoVM_eeprom.hex

include ../../src/Makefile
include ../../src/avr/Makefile

nvmdefault.h: Makefile

%.o: %.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@

%.d:%.c
	set -e; $(CC) -MM $(CFLAGS) $< \
	| sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@ ; \
	[ -s $@ ] || rm -f $@

# avr specific entries
%.elf: $(OBJS)
	$(CC) $(CLDFLAGS) -o $@ $(OBJS)
	avr-size -A $@

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

%_eeprom.hex: %.elf
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O ihex $< $@

# use uisp tool to configure cpu for external crystal
uisp: NanoVM.hex NanoVM_eeprom.hex
	uisp  -dprog=stk200 --erase  --wr_fuse_l=0xbf --wr_fuse_h=0xd9
	uisp --segment=flash  -dprog=stk200 --upload if=NanoVM.hex --verify
	uisp --segment=eeprom  -dprog=stk200 --upload if=NanoVM_eeprom.hex --verify

# use avrdude tool to configure cpu for external crystal
avrdude: NanoVM.hex NanoVM_eeprom.hex
	avrdude -c usbasp -p atmega32 -U lfuse:w:0xbf:m -U hfuse:w:0xd9:m -U flash:w:NanoVM.hex -U eeprom:w:NanoVM_eeprom.hex

clean::
	rm -f *.d *.o *~ nvmdefault.h *.elf

include $(OBJS:.o=.d)

