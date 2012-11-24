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
//  native_linedetector.c
//
#include "nibo2/iodefs.h"

#include "types.h"
#include "debug.h"
#include "config.h"
#include "error.h"

#include "delay.h"
#include "stack.h"
#include "vm.h"
#include "nibobee/native.h"
#include "nibobee/native_linedetector.h"
#include "nibobee/line.h"

#define NATIVE_METHOD_getValue 1
#define NATIVE_METHOD_calibrateWhite 2
#define NATIVE_METHOD_calibrateBlack 3
#define NATIVE_METHOD_setEnableIR 4
#define NATIVE_METHOD_getEnableIR 5

uint16_t value_off_l;
uint16_t value_off_r;
uint16_t value_on_l;
uint16_t value_on_r;

void native_nibobee_linedetector_init(void) {
  line_init();
}

// the ctbot class
void native_nibobee_linedetector_invoke(u08_t mref) {

  // JAVA: int getValue(int idx)
  if (mref == NATIVE_METHOD_getValue) {
    nvm_int_t val = stack_pop_int();
    val = line_get(val);
    stack_push(val);
  }

  // JAVA: void calibrateWhite()
  else if (mref == NATIVE_METHOD_calibrateWhite) {
    line_calibrateWhite();
    line_writePersistent();
  }

  // JAVA: void calibrateBlack()
  else if (mref == NATIVE_METHOD_calibrateBlack) {
    line_calibrateBlack();
    line_writePersistent();
  }

  // JAVA: void setEnableIR(boolean val)
  else if (mref == NATIVE_METHOD_setEnableIR) {
    /* nvm_int_t val = */ stack_pop_int();
  }

  // JAVA: boolean getEnableIR()
  else if (mref == NATIVE_METHOD_getEnableIR) {
    nvm_int_t val = 1;
    stack_push(val);
  }

  // ERROR
  else
    error(ERROR_NATIVE_UNKNOWN_METHOD);
  
}

