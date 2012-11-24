/*  BSD-License:

Copyright (c) 2007 by Nils Springob, nicai-systems, Germany

All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.
  * Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.
  * Neither the name nicai-systems nor the names of its contributors may be
    used to endorse or promote products derived from this software without
    specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

/*! @file    line.c
 *  @brief   Zuordnung der physikalischen Pins zu symbolischen Namen
 *  @author  Nils Springob (nils@nicai-systems.de)
 *  @date    2009-08-19
 */

#include "nibobee/iodefs.h"
#include "nibobee/line.h"
#include "nibobee/base.h"
#include "nibobee/delay.h"
#include <avr/eeprom.h>

#define LINE_EEPROM ((void *)0)

#ifdef __cplusplus
extern "C" {
#endif


typedef struct { 
  uint16_t black[3];
  uint16_t white[3];
} line_cal_t;

line_cal_t line_cal;


void line_init() {
  if (!(nibobee_initialization & NIBOBEE_ANALOG_INITIALIZED)) {
    analog_init();
  }
  line_readPersistent();
  activate_output_bit(IO_LINE_EN);
}


void line_writePersistent() {
  eeprom_write_block (&line_cal, LINE_EEPROM, sizeof(line_cal_t));
}


void line_readPersistent() {
  eeprom_read_block (&line_cal, LINE_EEPROM, sizeof(line_cal_t));
  if (line_cal.white[0]==0xffff) {
    line_cal.white[0]=0x200;
    line_cal.white[1]=0x300;
    line_cal.white[2]=0x200;
    line_cal.black[0]=4;
    line_cal.black[1]=4;
    line_cal.black[2]=4;
  }
}


uint16_t line_get(uint8_t idx) {
  if (idx<3) {
    int16_t val16 = (int16_t)analog_getValue(ANALOG_L1+idx)-(int16_t)analog_getValue(ANALOG_L0+idx);
    if (val16<0) val16=0;
    uint32_t val = val16;
    val *= 1024;
    val /= line_cal.white[idx];
    if (val > line_cal.black[idx]) {
      val -= line_cal.black[idx];
    } else {
      return 0;
    }
    if (val>INT16_MAX) {
      return INT16_MAX;
    }
    return val;
  }
  return 0;
}

static void do_calibrateWhite(uint8_t idx) {
  if (idx<3) {
    int16_t val16 = (int16_t)analog_getValue(ANALOG_L1+idx)-(int16_t)analog_getValue(ANALOG_L0+idx);
    if (val16<0) val16=0;
    line_cal.white[idx] = val16;
  }
}

static void do_calibrateBlack(uint8_t idx) {
  if (idx<3) {
    int16_t val16 = (int16_t)analog_getValue(ANALOG_L1+idx)-(int16_t)analog_getValue(ANALOG_L0+idx);
    if (val16<0) val16=0;
    uint32_t val = val16;
    val *= 1024;
    val /= line_cal.white[idx];
    line_cal.black[idx] = val;
  }
}

void line_calibrateWhite() {
  delay(100);
  do_calibrateWhite(LINE_L);
  do_calibrateWhite(LINE_C);
  do_calibrateWhite(LINE_R);
}

void line_calibrateBlack() {
  delay(100);
  do_calibrateBlack(LINE_L);
  do_calibrateBlack(LINE_C);
  do_calibrateBlack(LINE_R);
}


#ifdef __cplusplus
} // extern "C"
#endif

