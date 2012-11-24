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
 *  @date    2007-07-13
 */

#ifndef _IODEFS_H_
#define _IODEFS_H_

#include "iodefs_nibo2.h"

#include <avr/io.h>

#define DISTCO_I2C_ID 42
#define MOTCO_I2C_ID 44

/******************************************************************************/

/* helper macro */
#define _PPCAT(a,b) a##b

/* Macro-functions for IO-bits */
#define set_output_bit(NAME) _PPCAT(NAME,_PORT)|=_BV(_PPCAT(NAME,_BIT))
#define clear_output_bit(NAME) _PPCAT(NAME,_PORT)&=~(unsigned char)_BV(_PPCAT(NAME,_BIT))
#define set_output_bitval(NAME, VAL) _PPCAT(NAME,_PORT)=(_PPCAT(NAME,_PORT)&~(unsigned char)_BV(_PPCAT(NAME,_BIT)))|((VAL)?_BV(_PPCAT(NAME,_BIT)):0)

#define activate_output_bit(NAME) _PPCAT(NAME,_DDR)|=_BV(_PPCAT(NAME,_BIT))
#define deactivate_output_bit(NAME) _PPCAT(NAME,_DDR)&=~(unsigned char)_BV(_PPCAT(NAME,_BIT))

#define get_input_bit(NAME) (_PPCAT(NAME,_PIN)&_BV(_PPCAT(NAME,_BIT)))
#define get_output_bit(NAME) (_PPCAT(NAME,_PORT)&_BV(_PPCAT(NAME,_BIT)))


#endif
