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
//  native_wheelencoder.c
//

#include "types.h"
#include "debug.h"
#include "config.h"
#include "error.h"

#include "delay.h"
#include "stack.h"
#include "vm.h"
#include "nibobee/native.h"
#include "nibobee/native_wheelencoder.h"
#include "nibobee/iodefs.h"
#include "nibobee/odometry.h"

#define NATIVE_METHOD_getLeftInc 1
#define NATIVE_METHOD_getRightInc 2
#define NATIVE_METHOD_getLeftSpeed 3
#define NATIVE_METHOD_getRightSpeed 4

void native_nibobee_wheelencoder_init(void) {
  odometry_init();
}

void native_nibobee_wheelencoder_invoke(u08_t mref) {

  // JAVA: int getLeftInc()
  if(mref == NATIVE_METHOD_getLeftInc) {
    nvm_int_t val = odometry_getLeft(1);
    stack_push(val);
  }

  // JAVA: int getRightInc()
  else if(mref == NATIVE_METHOD_getRightInc) {
    nvm_int_t val = odometry_getRight(1);
    stack_push(val);
  }

  // JAVA: int getLeftSpeed()
  else if(mref == NATIVE_METHOD_getLeftSpeed) {
    nvm_int_t val = 0;
    stack_push(val);
  }

  // JAVA: int getRightSpeed()
  else if(mref == NATIVE_METHOD_getRightSpeed) {
    nvm_int_t val = 0;
    stack_push(val);
  
  } else
    error(ERROR_NATIVE_UNKNOWN_METHOD);
  
}

