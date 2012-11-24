#
#  Makefile for the NIBO2 version of the NanoVM
#

CONFIG = Nibo2.config
DEVICE = atmega128
F_CPU = 16000000

#DEFAULT_FILE = nibo2/LedTest
#DEFAULT_FILE = nibo2/DistTest
#DEFAULT_FILE = nibo2/RemoteTest
#DEFAULT_FILE = nibo2/ClockTest
#DEFAULT_FILE = nibo2/SupplyTest
DEFAULT_FILE = nibo2/FloorTest

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

# MATH lib
MATH = -lm
#MATH =

# build intel hex files
all: NanoVM.hex

include ../../src/Makefile

include ../../src/nibo2/Makefile

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



# Fuse high byte:
# 0xc1 = 1 1 0 0   0 0 0 1 <-- BOOTRST (boot reset vector at 0x0000)
#        ^ ^ ^ ^   ^ ^ ^------ BOOTSZ0
#        | | | |   | +-------- BOOTSZ1
#        | | | |   + --------- EESAVE (0: preserve EEPROM over chip erase)
#        | | | +-------------- CKOPT (0: full output swing)
#        | | +---------------- SPIEN (0: serial programming enabled)
#        | +------------------ JTAGEN (0: JTAG enabled)
#        +-------------------- OCDEN (0: OCD enabled)

# Fuse low byte:
# 0xff = 1 1 1 1   1 1 1 1
#        ^ ^ \ /   \--+--/
#        | |  |       +------- CKSEL 3..0 (external >8M crystal)
#        | |  +--------------- SUT 1..0 (crystal osc, BOD enabled)
#        | +------------------ BODEN (0: BrownOut Detector enabled)
#        +-------------------- BODLEVEL (2.7V)

# Fuse extended byte:
# 0xff = 1 1 1 1   1 1 1 1
#        \           / ^ ^ 
#         \         /  | +---- WDTON (0: watchdog always enabled)
#          \       /   +------ M103C (0: ATmega103 compatibility mode)
#           +-----+----------- RESERVED (always 1)
#  

HFUSE = 0xc1
LFUSE = 0xff
EFUSE = 0xff

# use uisp tool to configure whole cpu
uisp: NanoVM.hex NanoVM_eeprom.hex
	uisp  -dprog=stk500 --erase  --wr_fuse_l=$(LFUSE) --wr_fuse_h=$(HFUSE)
	uisp --segment=flash  -dprog=stk500 --upload if=NanoVM.hex --verify
	uisp --segment=eeprom  -dprog=stk500 --upload if=NanoVM_eeprom.hex --verify

avrdude: NanoVM.hex 
	avrdude -c stk500v2 -p m128 -B 1 -U lfuse:w:$(LFUSE):m -U hfuse:w:$(HFUSE):m -U efuse:w:$(EFUSE):m -U flash:w:NanoVM.hex

clean:
	rm -f *.d *.o *~ nvmdefault.h *.elf nibo/*.d nibo/*.o $(ROOT_DIR)/java/examples/nanovm/nibo/utils/*.class

include $(OBJS:.o=.d)

.PHONY: clean
.SECONDARY: NanoVM.hex $(OBJS)
