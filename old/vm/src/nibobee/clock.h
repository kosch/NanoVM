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

/*! @file    clock.h
 *  @brief   Zeitzählung
 *  @author  Nils Springob (nils@nicai-systems.de)
 *  @date    2009-08-19
 */

#ifndef _NIBOBEE_CLOCK_H_
#define _NIBOBEE_CLOCK_H_

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * Funktion zum Aufruf durch den IRQ. Wird bei verwendung des PID Reglers
 * automatisch aufgerufen.
 */
void clock_inc_irq(uint8_t ms, uint16_t us);


/*!
 * zählt bis 1000 (1s) in 1ms Schritten
 */
extern uint16_t clock_ms;


/*!
 * zählt die Sekunden seit dem Systemstart
 */
extern uint32_t clock_sec;



#ifdef __cplusplus
} // extern "C"
#endif

#endif // _NIBOBEE_CLOCK_H_
