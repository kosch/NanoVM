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
//  native_bot.c
//

#include "types.h"
#include "debug.h"
#include "config.h"
#include "error.h"

#include "delay.h"
#include "stack.h"
#include "vm.h"
#include "nibo2/native.h"
#include "nibo2/native_bot.h"
#include "nibo2/iodefs.h"

#include "nibo2/adc.h"
#include "spi.h"

#define NATIVE_METHOD_update 1
#define NATIVE_METHOD_getSupplyVoltage 2

uint16_t supply;

void native_nibo_bot_init(void) {
  adc_init(AN_VBAT);
  
  // Reset controllers
  activate_output_bit(IO_RESET_CO);
  clear_output_bit(IO_RESET_CO);
  delay(10);
  set_output_bit(IO_RESET_CO);

  // Initialize communication
  spi_init();
  delay(10);
}

void native_nibo_bot_invoke(u08_t mref) {

  // JAVA: void update()
  if (mref == NATIVE_METHOD_update) {
    supply = adc_read(AN_VBAT);
  }
  
  // JAVA: int getSupplyVoltage()
  else if(mref == NATIVE_METHOD_getSupplyVoltage) {
    nvm_int_t val = supply;
    stack_push(val);
  }


}

