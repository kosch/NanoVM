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

/*! @file    copro_prot.h
 *  @brief   Definitionen zur Kommunikation zwischen ATmega128 und ATmega88
 *  @author  Nils Springob (nils@nicai-systems.de)
 *  @date    2009-04-14
 */

#ifndef NIBO_COPRO_PROT_H_
#define NIBO_COPRO_PROT_H_

#include <util/delay.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

enum {
  COPRO_CMD_INVALID,        // () - 0 byte
  COPRO_CMD_STOP,           // () - 0 byte
  COPRO_CMD_SETSPEED,       // (int16_t left, int16_t right) - 4 byte
  COPRO_CMD_SETTARGET_ABS,  // (int16_t left, int16_t right, uint16_t speed) - 6 byte
  COPRO_CMD_SETTARGET_REL,  // (int16_t left, int16_t right, uint16_t speed) - 6 byte
  COPRO_CMD_SETPWM,         // (int16_t left, int16_t right) - 4 byte
  COPRO_CMD_SETPARAMETERS,  // (int8_t p, int8_t i, int8_t d) - 3 byte
  
  COPRO_CMD_START_IR, // () - 0 byte
  COPRO_CMD_STOP_IR,  // () - 0 byte
  COPRO_CMD_SEND_RC5, // (uint16_t rc5, uint8_t dummy) - 3 byte
  
  COPRO_CMD_NONE = 0xff
};


#ifdef __cplusplus
} // extern "C"
#endif

#endif // NIBO_COPRO_PROT_H_

