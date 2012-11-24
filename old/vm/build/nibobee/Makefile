#
#  Makefile for the NIBObee version of the NanoVM
#

CONFIG = NIBObee.config
DEVICE = atmega16
F_CPU = 15000000

#DEFAULT_FILE = nibo2/LedTest
#DEFAULT_FILE = nibo2/DistTest
#DEFAULT_FILE = nibo2/RemoteTest
#DEFAULT_FILE = nibo2/ClockTest
#DEFAULT_FILE = nibo2/SupplyTest
DEFAULT_FILE = nibobee/LedTest

ROOT_DIR = ../../..
# CFLAGS += -DDEBUG

# general GCC compiler flags
CFLAGS += -std=gnu99 -Wall -Werror -pedantic-errors -Wundef -Wno-long-long

# AVR compiler setup
PREFIX =
CC = $(PREFIX)avr-gcc
OBJCOPY = $(PREFIX)avr-objcopy
OBJDUMP = $(PREFIX)avr-objdump

# AVR compiler and linker flags
CFLAGS += -Os -ffunction-sections -I. -mmcu=$(DEVICE) -DVERSION="\"$(VERSION)\"" -DF_CPU=$(F_CPU) -I$(ROOT_DIR)/vm/src
CLDFLAGS += -v -mmcu=$(DEVICE)

CFLAGS += -D_NIBOBEE_

# MATH lib
MATH = -lm
#MATH =

# build intel hex files
all: NanoVM.hex

include ../../src/Makefile

include ../../src/nibobee/Makefile

nvmdefault.h: Makefile

# define canned command sequences
define COMPILE-CMD
$(CC) $(CFLAGS) -c $< -o $@
endef

define DEP-GEN-CMD
set -e; $(CC) -MM $(CFLAGS) $< \
| sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@ ; \
[ -s $@ ] || rm -f $@
endef

%.o: %.c Makefile
	$(COMPILE-CMD)

%.d:%.c
	$(DEP-GEN-CMD)

# avr specific entries
%.elf: $(OBJS)
	$(CC) $(CLDFLAGS) -o $@ $(OBJS) $(MATH)
	avr-size -A NanoVM.elf


%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@


NanoVM.lss: NanoVM.elf
	avr-objdump -h -S NanoVM.elf >NanoVM.lss

lss: NanoVM.lss


#            1  means not!
# 7 BODLEVEL 1  Brown-out Detector trigger level
# 6 BODEN 6  1  Brown-out Detector enable
# 5 SUT1 5   1  Select start-up time
# 4 SUT0 4   0  Select start-up time
# 3 CKSEL3   1  Select Clock source
# 2 CKSEL2   1  Select Clock source
# 1 CKSEL1   1  Select Clock source
# 0 CKSEL0   1  Select Clock source
LFUSE = 0xef

#            1  means not!
# 7 OCDEN    1  Enable OCD
# 6 JTAGEN   1  Enable JTAG
# 5 SPIEN    0  Enable SPI Serial Program and Data Downloading
# 4 CKOPT    1  Oscillator options
# 3 EESAVE   0  EEPROM memory is preserved through the Chip Erase
# 2 BOOTSZ1  0  Select Boot Size
# 1 BOOTSZ0  0  Select Boot Size
# 0 BOOTRST  1  Select reset vector
HFUSE = 0xd1


# use uisp tool to configure whole cpu
uisp: NanoVM.hex NanoVM_eeprom.hex
	uisp  -dprog=stk500 --erase  --wr_fuse_l=$(LFUSE) --wr_fuse_h=$(HFUSE)
	uisp --segment=flash  -dprog=stk500 --upload if=NanoVM.hex --verify
	uisp --segment=eeprom  -dprog=stk500 --upload if=NanoVM_eeprom.hex --verify

avrdude: NanoVM.hex 
	avrdude -c usbasp -p m16 -B 1 -U lfuse:w:$(LFUSE):m -U hfuse:w:$(HFUSE):m -U flash:w:NanoVM.hex

clean:
	rm -f *.d *.o *~ nvmdefault.h *.elf nibobee/*.d nibobee/*.o $(ROOT_DIR)/java/examples/nanovm/nibobee/utils/*.class

include $(OBJS:.o=.d)

.PHONY: clean
.SECONDARY: NanoVM.hex $(OBJS)
