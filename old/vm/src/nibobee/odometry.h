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

/*! @file    odometry.h
 *  @brief   Funktionen zur Odometriemessung
 *  @author  Nils Springob (nils@nicai-systems.de)
 *  @date    2009-08-19
 */

#ifndef _NIBOBEE_ODOMETRY_H_
#define _NIBOBEE_ODOMETRY_H_

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * Initialisierung der Odometriemessung.
 * Die Lichtschranken lösen automatisch einen Interrupt aus, in dem die Zähler
 * aktualisisert werden. Die aktuelle Motorrichtung bestimmt ob die Zähler hoch
 * oder runter gezählt werden.
 * Die Interrupts müssen aktiviert sein!
 */
void odometry_init();


/*!
 * Setzt beide Zähler auf 0 zurück
 */
void odometry_reset();


/*!
 * Liefert den Wert des linken Zählers zurück. Je nach Motorrichtung wird der
 * Zähler hoch oder runter gezählt.
 * Wenn @param reset = 0 ist wird der Zählerstand beibehalten, ansonsten auf
 * 0 zurückgesetzt.
 */
int16_t odometry_getLeft(uint8_t reset);


/*!
 * Liefert den Wert des rechten Zählers zurück. Je nach Motorrichtung wird der
 * Zähler hoch oder runter gezählt.
 * Wenn @param reset = 0 ist wird der Zählerstand beibehalten, ansonsten auf
 * 0 zurückgesetzt.
 */
int16_t odometry_getRight(uint8_t reset);



#ifdef __cplusplus
} // extern "C"
#endif

#endif // _NIBOBEE_ODOMETRY_H_
