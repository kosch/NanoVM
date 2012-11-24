//
//  Nibo-NanoVM, a tiny java VM for the Nibo robot
//
//  Copyright (C) 2007 by Nils Springob <nils@nicai-systems.de>
//  Based on work by Benjamin Benz(c't-Bot) and Till Harbaum(NanoVM)
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

//
//  native_motor.c
//

#include "types.h"
#include "debug.h"
#include "config.h"
#include "error.h"

#include "delay.h"
#include "stack.h"
#include "vm.h"
#include "nibobee/native.h"
#include "nibobee/native_motor.h"
#include "nibobee/motpwm.h"
#include "nibobee/motpid.h"

#include <avr/interrupt.h>

#define NATIVE_METHOD_setParameters 1
#define NATIVE_METHOD_setPWM 2
#define NATIVE_METHOD_setSpeed 3
#define NATIVE_METHOD_stop 4

void native_nibobee_motor_init(void) {
  motpwm_init();
  motpid_init();
}


void native_nibobee_motor_invoke(u08_t mref) {

  // JAVA: void setParameters(int p, int i, int d)
  if(mref == NATIVE_METHOD_setParameters) {
    /*nvm_int_t d =*/ stack_pop_int();
    /*nvm_int_t i =*/ stack_pop_int();
    /*nvm_int_t p =*/ stack_pop_int();
    //copro_setSpeedParameters(i, p, d);
  }

  // JAVA: void setPWM(int left, int right)
  else if(mref == NATIVE_METHOD_setPWM) {
    nvm_int_t right = stack_pop_int();
    nvm_int_t left = stack_pop_int();
    motpwm_setLeft(left);
    motpwm_setRight(right);
  }

  // JAVA: void setSpeed(int left, int right)
  else if(mref == NATIVE_METHOD_setSpeed) {
    /*nvm_int_t right =*/ stack_pop_int();
    /*nvm_int_t left =*/ stack_pop_int();
    //motpid_setLeft(left);
    //motpid_setRight(right);
  }

  // JAVA: void stop()
  else if(mref == NATIVE_METHOD_stop) {
    motpwm_stop();
  }

  // ERROR
  else {
    error(ERROR_NATIVE_UNKNOWN_METHOD);
  }
}


