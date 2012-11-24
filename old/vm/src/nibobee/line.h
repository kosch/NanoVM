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

/*! @file    line.h
 *  @brief   Zuordnung der physikalischen Pins zu symbolischen Namen
 *  @author  Nils Springob (nils@nicai-systems.de)
 *  @date    2009-08-19
 */

#ifndef _NIBOBEE_LINE_H_
#define _NIBOBEE_LINE_H_

#include "nibobee/analog.h"

#ifdef __cplusplus
extern "C" {
#endif


enum {
  LINE_L = ANALOG_L0-ANALOG_L0,
  LINE_C = ANALOG_C0-ANALOG_L0,
  LINE_R = ANALOG_R0-ANALOG_L0,
};


/*!
 * Initialisierung des Liniensensors.
 * Ruft bei Bedarf analog_init() und line_readPersistent() auf.
 * Die Interrupts müssen aktiviert sein, damit die Sensorwerte gemessen werden!
 */
void line_init();


/*!
 * Speichert die Kaibrierungsdaten im EEPROM des ATmega16
 */
void line_writePersistent();


/*!
 * Laden der Kaibrierungsdaten aus dem EEPROM des ATmega16
 */
void line_readPersistent();


/*!
 * Liefert den normalisierten Wert des Liniensensors mit dem index @param idx .
 * Die Interrupts müssen aktiviert sein, damit die Sensorwerte gemessen werden!
 * Der Parameter @param idx kann die Werte LINE_L, LINE_C oder LINE_R annehmen.
 */
uint16_t line_get(uint8_t idx);


/*!
 * Kalibrierung auf weisse Oberfläche für normalisiserten Wert 1024.
 * Die Interrupts müssen aktiviert sein, damit die Sensorwerte gemessen werden!
 */
void line_calibrateWhite();


/*!
 * Kalibrierung auf schwarze Oberfläche für normalisiserten Wert 0.
 * Die Interrupts müssen aktiviert sein, damit die Sensorwerte gemessen werden!
 * Die Funktion darf erst nach line_calibrateWhite() aufgerufen werden.
 */
void line_calibrateBlack();

#ifdef __cplusplus
} // extern "C"
#endif



#endif // _NIBOBEE_LINE_H_
