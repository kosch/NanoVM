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

/*! @file    motpid.c
 *  @brief   Zuordnung der physikalischen Pins zu symbolischen Namen
 *  @author  Nils Springob (nils@nicai-systems.de)
 *  @date    2009-08-19
 */

#include <avr/interrupt.h>
#include <util/atomic.h>
#include "nibobee/iodefs.h"
#include "nibobee/clock.h"

#ifdef _NIBOBEE_MEGAxx4_
# define PWM_TIMER_IMSK     TIMSK1
#else
# define PWM_TIMER_IMSK     TIMSK
#endif

#define PWM_TIMER_IMSK_OIE   _BV(TOIE1)

// Clock = 15 Mhz
// PS = 1
// freq = 15Mhz/1022 = 14.677 kHz
// call PID with 100 Hz:
#define MOTPID_CALL_CNT 147

#ifdef __cplusplus
extern "C" {
#endif



uint8_t motpid_cnt;

void motpid_init() {
}


void motpid_enable() {
  PWM_TIMER_IMSK |= PWM_TIMER_IMSK_OIE;
}

void motpid_disable() {
  PWM_TIMER_IMSK |= (uint8_t) ~PWM_TIMER_IMSK_OIE;
}



ISR(TIMER1_OVF_vect) {
  static uint8_t counter=0;
  static uint8_t running=0;
  counter++;
  if (running) {
    return;
  }
  running=1;
  if (counter>=15) {
    counter-=15;
    clock_inc_irq(1, 22);
  }

  motpid_cnt++;
  if (motpid_cnt>=MOTPID_CALL_CNT) {
    //pid_left_timer_int();
    //schedule_irq();
    //pid_right_timer_int();
    //schedule_irq();
    //comdata_signal();
    motpid_cnt=0;
  }

}


#ifdef __cplusplus
} // extern "C"
#endif

