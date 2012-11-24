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

/*! @file    analog.h
 *  @brief   Zugriff auf die analogen Eingänge
 *  @author  Nils Springob (nils@nicai-systems.de)
 *  @date    2009-08-19
 */

#ifndef _NIBOBEE_ANALOG_H_
#define _NIBOBEE_ANALOG_H_


#ifdef __cplusplus
extern "C" {
#endif


enum {
  ANALOG_EXT0,
  ANALOG_EXT1,
  ANALOG_EXT2,
  ANALOG_EXT3,
  ANALOG_VOLT,
  ANALOG_L0,
  ANALOG_C0,
  ANALOG_R0,
  ANALOG_L1,
  ANALOG_C1,
  ANALOG_R1,
};

/*!
 * Initialisierung des Liniensensors.
 * Der AD-Wandler misst im Interruptmodus automatisch alle Werte, und schaltet
 * auch die IR-LEDs der Bodensensoren bei Bedarf ein und aus.
 * Die Interrupts müssen aktiviert sein, damit die Sensorwerte gemessen werden!
 */
void analog_init();

/*!
 * Liefert den Wert des analogen Eingangs mit dem index @param idx zurück.
 * Die Interrupts müssen aktiviert sein, damit die Werte gemessen werden!
 */
uint16_t analog_getValue(uint8_t idx);

#ifdef __cplusplus
} // extern "C"
#endif


#endif // _NIBOBEE_ANALOG_H_

