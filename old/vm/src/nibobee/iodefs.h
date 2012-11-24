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

/*! @file    iodefs.h
 *  @brief   Zuordnung der physikalischen Pins zu symbolischen Namen
 *  @author  Nils Springob (nils@nicai-systems.de)
 *  @date    2009-08-19
 */

#ifndef _IODEFS_H_
#define _IODEFS_H_


#ifdef _NIBOBEE_
# include "iodefs_nibobee.h"
#else
# error "no robot platform defined"
#endif

#ifdef __AVR_ATmega644__
#define _NIBOBEE_MEGAxx4_
#endif

#ifdef __AVR_ATmega324__
#define _NIBOBEE_MEGAxx4_
#endif

#ifdef __AVR_ATmega164__
#define _NIBOBEE_MEGAxx4_
#endif


#include <avr/io.h>
#include <avr/interrupt.h>


/******************************************************************************/

#define LOBYTE(x)        (uint8_t)((uint16_t)x)
#define HIBYTE(x)        (uint8_t)(((uint16_t)x)>>8)
#define MAKE_WORD(hi,lo) ((hi*0x100)+lo)

#define enable_interrupts() sei()
#define disable_interrupts() cli()

/* helper macro */
#define _PPCAT(a,b) a##b
#define _PPCAT3(a,b,c) a##b##c

/* Macro-functions for IO-bits */
#define activate_output_bit(NAME) _PPCAT(NAME,_DDR)|=_BV(_PPCAT(NAME,_BIT))
#define deactivate_output_bit(NAME) _PPCAT(NAME,_DDR)&=~(unsigned char)_BV(_PPCAT(NAME,_BIT))
#define set_output_bit(NAME) _PPCAT(NAME,_PORT)|=_BV(_PPCAT(NAME,_BIT))
#define clear_output_bit(NAME) _PPCAT(NAME,_PORT)&=~(unsigned char)_BV(_PPCAT(NAME,_BIT))
#define set_output_bitval(NAME, VAL) _PPCAT(NAME,_PORT)=(_PPCAT(NAME,_PORT)&~(unsigned char)_BV(_PPCAT(NAME,_BIT)))|((VAL)?_BV(_PPCAT(NAME,_BIT)):0)

#define get_input_bit(NAME) (_PPCAT(NAME,_PIN)&_BV(_PPCAT(NAME,_BIT)))
#define get_output_bit(NAME) (_PPCAT(NAME,_PORT)&_BV(_PPCAT(NAME,_BIT)))

/* Macro-functions for IO-groups */
#define activate_output_groupbit(NAME,BIT) _PPCAT(NAME,_DDR)|=_BV(_PPCAT3(NAME,_BIT_,BIT))
#define deactivate_output_groupbit(NAME,BIT) _PPCAT(NAME,_DDR)&=~(unsigned char)_BV(_PPCAT3(NAME,_BIT_,BIT))
#define set_output_groupbit(NAME,BIT) _PPCAT(NAME,_PORT)|=_BV(_PPCAT3(NAME,_BIT_,BIT))
#define clear_output_groupbit(NAME,BIT) _PPCAT(NAME,_PORT)&=~(unsigned char)_BV(_PPCAT3(NAME,_BIT_,BIT))
#define set_output_groupbitval(NAME,BIT,VAL) _PPCAT(NAME,_PORT)=(_PPCAT(NAME,_PORT)&~(unsigned char)_BV(_PPCAT3(NAME,_BIT_,BIT)))|((VAL)?_BV(_PPCAT3(NAME,_BIT_,BIT)):0)

#define get_input_groupbit(NAME,BIT) (_PPCAT(NAME,_PIN)&_BV(_PPCAT3(NAME,_BIT_,BIT)))
#define get_output_groupbit(NAME,BIT) (_PPCAT(NAME,_PORT)&_BV(_PPCAT3(NAME,_BIT_,BIT)))

#define activate_output_group(NAME) _PPCAT(NAME,_DDR)|=_PPCAT(NAME,_MASK)
#define deactivate_output_group(NAME) _PPCAT(NAME,_DDR)&=~(unsigned char)_PPCAT(NAME,_MASK)
#define set_output_group(NAME) _PPCAT(NAME,_PORT)|=_PPCAT(NAME,_MASK)
#define clear_output_group(NAME) _PPCAT(NAME,_PORT)&=~(unsigned char)_PPCAT(NAME,_MASK)



#endif
