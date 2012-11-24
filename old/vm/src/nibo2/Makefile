#
# Makefile include for NanoVM core files
#

NIBO_DIR = $(ROOT_DIR)/vm/src/nibo2
NIBO_OBJS = \
  nibo2/adc.o \
  nibo2/display.o \
  nibo2/copro.o \
  nibo2/gfx.o \
  nibo2/delay.o \
  nibo2/pwm.o \
  nibo2/spi.o \
  nibo2/native_impl.o \
  nibo2/native_bot.o \
  nibo2/native_clock.o \
  nibo2/native_graphicdisplay.o \
  nibo2/native_textdisplay.o \
  nibo2/native_distancesensor.o \
  nibo2/native_edgedetector.o \
  nibo2/native_leds.o \
  nibo2/native_linedetector.o \
  nibo2/native_motor.o \
  nibo2/native_wheelencoder.o \
  nibo2/native_irtransceiver.o \
  


OBJS += $(NIBO_OBJS)

# convert and upload a class file

nibo2/%.o:$(NIBO_DIR)/%.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@

nibo2/%.d:$(NIBO_DIR)/%.c
	set -e; $(CC) -MM $(CFLAGS) $< \
	| sed 's#\($*\)\.o[ :]*#\1.o $@ : #g' > $@ ; \
	[ -s $@ ] || rm -f $@
