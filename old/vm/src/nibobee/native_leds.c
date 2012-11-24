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
//  native_leds.c
//

#include "types.h"
#include "debug.h"
#include "config.h"
#include "error.h"

#ifdef NIBOBEE

#include "nibobee/delay.h"
#include "stack.h"
#include "vm.h"
#include "nibobee/native.h"
#include "nibobee/native_leds.h"
#include "nibobee/delay.h"
#include "nibobee/iodefs.h"


#define NATIVE_METHOD_setStatus 1
#define NATIVE_METHOD_getStatus 2

#define LOBYTE(x)        (uint8_t)((uint16_t)x)
#define HIBYTE(x)        (uint8_t)(((uint16_t)x)>>8)
#define MAKE_WORD(hi,lo) ((hi*0x100)+lo)

int16_t tspeed_l = 0;
int16_t tspeed_r = 0;

void native_nibobee_leds_init(void) {
  activate_output_group(IO_LEDS);
}

// the ctbot class
void native_nibobee_leds_invoke(u08_t mref) {

  // JAVA: void setStatus(int led, boolean status)
  if(mref == NATIVE_METHOD_setStatus) {
    nvm_int_t status = stack_pop_int();
    nvm_int_t led = stack_pop_int();

    if (status) {
      IO_LEDS_PORT |= 0x01<<led;
    } else {
      IO_LEDS_PORT &= ~(0x01<<led);
    }
  }
  
  // JAVA: boolean getStatus(int led)
  else if (mref == NATIVE_METHOD_getStatus) {
    nvm_int_t val = stack_pop_int();
    val = IO_LEDS_PORT & (0x01<<val);
    val = val?1:0;
    stack_push(val);

  } else {
    error(ERROR_NATIVE_UNKNOWN_METHOD);
  }
}

#endif
