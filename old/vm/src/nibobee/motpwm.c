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

/*! @file    motpwm.c
 *  @brief   Zuordnung der physikalischen Pins zu symbolischen Namen
 *  @author  Nils Springob (nils@nicai-systems.de)
 *  @date    2009-08-19
 */

#include <avr/interrupt.h>
#include <util/atomic.h>
#include "nibobee/iodefs.h"
#include "nibobee/base.h"

// Clock = 15 Mhz
// PS = 1
// freq = 15Mhz/1022 = 14.677 kHz



#define PWM_TIMER_MAX 511

#define PWM_TIMER_CNT        TCNT1
#define PWM_TIMER_CCRA       TCCR1A
#define PWM_TIMER_CCRA_INIT  _BV(COM1A1) | _BV(COM1A0) | _BV(COM1B1) | _BV(COM1B0) | _BV(WGM11)
#define PWM_TIMER_CCRB       TCCR1B
#define PWM_TIMER_CCRB_INIT  _BV(CS10)
#define PWM_TIMER_OCRA       OCR1A
#define PWM_TIMER_OCRA_INIT  0
#define PWM_TIMER_OCRB       OCR1B
#define PWM_TIMER_OCRB_INIT  0
#ifdef _NIBOBEE_MEGAxx4_
# define PWM_TIMER_IMSK      TIMSK1
#else
# define PWM_TIMER_IMSK      TIMSK
#endif
#define PWM_TIMER_IMSK_INIT  0
#define PWM_TIMER_IMSK_CMPA  _BV(OCIE1A)
#define PWM_TIMER_IMSK_CMPB  _BV(OCIE1B)

#ifdef __cplusplus
extern "C" {
#endif



//OC1A is IO_MOTOR_BIT_PWM_LEFT
//OC1B is IO_MOTOR_BIT_PWM_RIGHT

int16_t motpwm_motor_l;
int16_t motpwm_motor_r;
uint8_t motpwm_flags;

void motpwm_init() {
  nibobee_initialization |= NIBOBEE_MOTPWM_INITIALIZED;
  set_output_group(IO_MOTOR);
  activate_output_group(IO_MOTOR);
  PWM_TIMER_CCRA = PWM_TIMER_CCRA_INIT;
  PWM_TIMER_CCRB = PWM_TIMER_CCRB_INIT;
  PWM_TIMER_IMSK |= PWM_TIMER_IMSK_INIT;
}


void motpwm_stop() {
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    motpwm_motor_l = 0;
    motpwm_motor_r = 0;
    PWM_TIMER_OCRA = 0;
    PWM_TIMER_OCRB = 0;
  }
}


void motpwm_setLeft(int16_t value) {
  value/=2;
  if (value>PWM_TIMER_MAX) value=PWM_TIMER_MAX;
  if (value<-PWM_TIMER_MAX) value=-PWM_TIMER_MAX;
  
  if (value<0) {
    motpwm_motor_l = - value;
    if (get_output_groupbit(IO_MOTOR, DIR_LEFT)) {
      // direction has changed, stop first
      motpwm_flags&=0x02;
      PWM_TIMER_OCRA = 0;
      PWM_TIMER_IMSK |= PWM_TIMER_IMSK_CMPA;
    } else {
      PWM_TIMER_OCRA = motpwm_motor_l;
    }
  } else {
    motpwm_motor_l = value;
    if (get_output_groupbit(IO_MOTOR, DIR_LEFT)) {
      PWM_TIMER_OCRA = motpwm_motor_l;
    } else {
      // direction has changed, stop first
      motpwm_flags|=0x01;
      PWM_TIMER_OCRA = 0;
      PWM_TIMER_IMSK |= PWM_TIMER_IMSK_CMPA;
    }
  }
}


void motpwm_setRight(int16_t value) {
  value/=2;
  if (value>PWM_TIMER_MAX) value=PWM_TIMER_MAX;
  if (value<-PWM_TIMER_MAX) value=-PWM_TIMER_MAX;
  
  if (value<0) {
    motpwm_motor_r =  - value;
    if (get_output_groupbit(IO_MOTOR, DIR_RIGHT)) {
      PWM_TIMER_OCRB = motpwm_motor_r;
    } else {
      // direction has changed, stop first
      motpwm_flags|=0x02;
      PWM_TIMER_OCRB = 0;
      PWM_TIMER_IMSK |= PWM_TIMER_IMSK_CMPB;
    }
  } else {
    motpwm_motor_r =  value;
    if (get_output_groupbit(IO_MOTOR, DIR_RIGHT)) {
      // direction has changed, stop first
      motpwm_flags&=0x01;
      PWM_TIMER_OCRB = 0;
      PWM_TIMER_IMSK |= PWM_TIMER_IMSK_CMPB;
    } else {
      PWM_TIMER_OCRB = motpwm_motor_r;
    }
  }
}


ISR(TIMER1_COMPA_vect) {
  if (get_input_groupbit(IO_MOTOR, PWM_LEFT)) {
    set_output_groupbitval(IO_MOTOR, DIR_LEFT, motpwm_flags&0x01);
    PWM_TIMER_OCRA = motpwm_motor_l;
    PWM_TIMER_IMSK &= (uint8_t) (~PWM_TIMER_IMSK_CMPA);
  }
}


ISR(TIMER1_COMPB_vect) {
  if (get_input_groupbit(IO_MOTOR, PWM_RIGHT)) {
    set_output_groupbitval(IO_MOTOR, DIR_RIGHT, motpwm_flags&0x02);
    PWM_TIMER_OCRB = motpwm_motor_r;
    PWM_TIMER_IMSK &= (uint8_t) (~PWM_TIMER_IMSK_CMPB);
  }
}


#ifdef __cplusplus
} // extern "C"
#endif


