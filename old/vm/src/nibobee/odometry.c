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

/*! @file    odometry.c
 *  @brief   Zuordnung der physikalischen Pins zu symbolischen Namen
 *  @author  Nils Springob (nils@nicai-systems.de)
 *  @date    2009-08-19
 */

#include <avr/interrupt.h>
#include <util/atomic.h>
#include "nibobee/iodefs.h"

#ifdef __cplusplus
extern "C" {
#endif


volatile int8_t odometry_pid_left;
volatile int8_t odometry_pid_right;
volatile int16_t odometry_left;
volatile int16_t odometry_right;

void odometry_init() {
  // enable int0 and int1 on rising edge
#ifdef _NIBOBEE_MEGAxx4_
  // ATmega644
  EICRA |= _BV(ISC11) | _BV(ISC10) | _BV(ISC01) | _BV(ISC00);
  EIMSK |= _BV(INT1) |  _BV(INT0);
#else
  // ATmega16
  MCUCR |= _BV(ISC11) | _BV(ISC10) | _BV(ISC01) | _BV(ISC00); 
  GICR |= _BV(INT1) |  _BV(INT0);
#endif

  set_output_groupbitval(IO_MOTOR, DIR_LEFT, 1);
  set_output_groupbitval(IO_MOTOR, DIR_RIGHT, 0);
}


void odometry_reset() {
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    odometry_left = 0;
    odometry_right = 0;
  }
}


int16_t odometry_getLeft(uint8_t reset) {
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    int16_t res = odometry_left;
    if (reset) {
      odometry_left = 0;
    }
    return res;
  }
  return 0;
}


int16_t odometry_getRight(uint8_t reset) {
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    int16_t res = odometry_right;
    if (reset) {
      odometry_right = 0;
    }
    return res;
  }
  return 0;
}



ISR(INT0_vect) {
  if (get_output_groupbit(IO_MOTOR, DIR_LEFT)) odometry_pid_left++, odometry_left++; else odometry_pid_left--, odometry_left--;
}


ISR(INT1_vect) {
  if (get_output_groupbit(IO_MOTOR, DIR_RIGHT)) odometry_pid_right--, odometry_right--; else odometry_pid_right++, odometry_right++;
}


#ifdef __cplusplus
} // extern "C"
#endif

