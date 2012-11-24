#
#  Makefile for cc65 version of the NanoVM
#

DEBUG  = 0
TARGET = apple2enh

FILES = arithmetic ArraySize ConsoleEcho count DivByZero Erathostenes Fibonacci FloatTest \
        FloatTest2 HelloWorld icmp Inheritance Int31Test MethodCall OneClass QuickSort \
        Rot13 SelfInstance StaticTest StringAndHeapTest Switch Switch2

DEFAULT_FILE = HelloWorld

ROOT_DIR = ../../..
CONFIG   = cc65.config

# cc65 compiler setup
AS = ca65
CC = cc65
LD = ld65

# cc65 assembler, compiler and linker flags
AFLAGS  = -t $(TARGET)
CFLAGS  = -t $(TARGET) -O --register-vars --static-locals --codesize 400 -I. -DVERSION="\"$(VERSION)\""
LDFLAGS = -t $(TARGET) -m NanoVM.map

ifeq ($(DEBUG),1)
CFLAGS += -DDEBUG
endif

LOWERCASE = abcdefghijklmnopqrstuvwxyz
UPPERCASE = ABCDEFGHIJKLMNOPQRSTUVWXYZ
TOLOWER   = $(shell echo $1 | sed 'y!$(UPPERCASE)!$(LOWERCASE)!')

all: NanoVM

include ../../src/Makefile
include ../../src/cc65/Makefile

nvmdefault.h: Makefile

# define canned command sequences
define COMPILE-CMD
$(CC) $(CFLAGS) --create-dep $< -o $(@:.o=.s)
@$(AS) $(AFLAGS) $(@:.o=.s) -o $@
@sed 's!.s:!.o:!' < $(@:.o=.u) > $(@:.o=.d)
@rm -f $(@:.o=.s) $(@:.o=.u)
endef

define DEP-GEN-CMD
endef

# cc65 specific entries
NanoVM: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS) $(TARGET).lib

%.o: %.c Makefile
	$(COMPILE-CMD)

%.d:%.c
	$(DEP-GEN-CMD)

%.nvm: $(ROOT_DIR)/java/examples/%.java
	javac -classpath "$(ROOT_DIR)/java$(PATH_SEP)$(ROOT_DIR)/java/examples" $(ROOT_DIR)/java/examples/$*.java
	java -jar $(ROOT_DIR)/tool/NanoVMTool.jar $(ROOT_DIR)/tool/config/$(CONFIG) $(ROOT_DIR)/java/examples $*

disk: NanoVM $(addsuffix .nvm,$(FILES))
ifeq ($(TARGET),apple2enh)
	cp ProDOS.dsk NanoVM.dsk
	java -jar $(AC) -cc65 NanoVM.dsk nanovm bin < NanoVM
	$(foreach FILE,$(filter-out NanoVM,$^),java -jar $(AC) -p NanoVM.dsk $(FILE) bin < $(FILE);)
endif
ifeq ($(TARGET),c64)
	$(C1541) -format nanovm,00 d64 NanoVM.d64 $(foreach FILE,$^, -write $(FILE) $(call TOLOWER,$(FILE)))
endif

clean:
	rm -f *.d cc65/*.d *.o cc65/*.o *.map *.nvm *~ nvmdefault.h NanoVM NanoVM.dsk NanoVM.d64

include $(OBJS:.o=.d)
