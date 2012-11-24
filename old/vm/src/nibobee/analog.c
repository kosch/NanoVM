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

/*! @file    analog.c
 *  @brief   Zuordnung der physikalischen Pins zu symbolischen Namen
 *  @author  Nils Springob (nils@nicai-systems.de)
 *  @date    2009-08-19
 */

#include <avr/interrupt.h>
#include <util/atomic.h>
#include "nibobee/iodefs.h"
#include "nibobee/analog.h"
#include "nibobee/base.h"


#ifdef __cplusplus
extern "C" {
#endif


uint16_t analog_samples[11];
uint8_t analog_pos;


void analog_init() {
  nibobee_initialization |= NIBOBEE_ANALOG_INITIALIZED;
  ADCSRA = _BV(ADPS2)  // prescale faktor = 128 ADC laeuft
         | _BV(ADPS1)  // mit 15 MHz / 128 = 120 kHz
         | _BV(ADPS0)
         | _BV(ADEN)   // ADC an
         | _BV(ADATE)  // auto trigger
         | _BV(ADIE)   // enable interrupt
         | _BV(ADSC);  // Beginne mit der Konvertierung
  activate_output_bit(IO_LINE_EN);
}


uint16_t analog_getValue(uint8_t idx) {
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    return analog_samples[idx];
  }
  return 0;
}


static inline void analog_storeResult(uint8_t pos) {
  uint16_t value = ADC;
  switch (pos) {
    case  0: analog_samples[ANALOG_EXT0]=value; break;
    case  1: analog_samples[ANALOG_EXT1]=value; break;
    case  2: analog_samples[ANALOG_EXT2]=value; break;
    case  3: analog_samples[ANALOG_EXT3]=value; break;
    case  4: analog_samples[ANALOG_L0]=value; break;
    case  5: analog_samples[ANALOG_C0]=value; break;
    case  6: analog_samples[ANALOG_R0]=value; clear_output_bit(IO_LINE_EN); break;
    case  7: analog_samples[ANALOG_VOLT]=value; break;
    case  8: analog_samples[ANALOG_L1]=value; break;
    case  9: analog_samples[ANALOG_C1]=value; break;
    case 10: analog_samples[ANALOG_R1]=value; set_output_bit(IO_LINE_EN); break;
  }
}


static inline void analog_setupNext(uint8_t pos) {
  switch (pos) {
    case  0: ADMUX = _BV(REFS0) | 1; break;
    case  1: ADMUX = _BV(REFS0) | 2; break;
    case  2: ADMUX = _BV(REFS0) | 3; break;
    case  3: ADMUX = _BV(REFS0) | 5; break;
    case  4: ADMUX = _BV(REFS0) | 6; break;
    case  5: ADMUX = _BV(REFS0) | 7; break;
    case  6: ADMUX = _BV(REFS0) | 4; break;
    case  7: ADMUX = _BV(REFS0) | 5; break;
    case  8: ADMUX = _BV(REFS0) | 6; break;
    case  9: ADMUX = _BV(REFS0) | 7; break;
    case 10: ADMUX = _BV(REFS0) | 0; break;
  }
}


ISR(ADC_vect) {
  analog_storeResult(analog_pos);
  if (++analog_pos>10) {
    analog_pos=0;
  }
  analog_setupNext(analog_pos);
}

#ifdef __cplusplus
} // extern "C"
#endif


