#
# Makefile include for NanoVM core files
#

NIBOBEE_DIR = $(ROOT_DIR)/vm/src/nibobee
NIBOBEE_OBJS = \
  nibobee/base.o \
  nibobee/delay.o \
  nibobee/motpwm.o \
  nibobee/motpid.o \
  nibobee/clock.o \
  nibobee/sens.o \
  nibobee/analog.o \
  nibobee/line.o \
  nibobee/odometry.o \
  nibobee/native_impl.o \
  nibobee/native_bot.o \
  nibobee/native_clock.o \
  nibobee/native_leds.o \
  nibobee/native_linedetector.o \
  nibobee/native_motor.o \
  nibobee/native_sensor.o \
  nibobee/native_wheelencoder.o \
  


OBJS += $(NIBOBEE_OBJS)

# convert and upload a class file

nibobee/%.o:$(NIBOBEE_DIR)/%.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@

nibobee/%.d:$(NIBOBEE_DIR)/%.c
	set -e; $(CC) -MM $(CFLAGS) $< \
	| sed 's#\($*\)\.o[ :]*#\1.o $@ : #g' > $@ ; \
	[ -s $@ ] || rm -f $@
