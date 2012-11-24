/*  BSD-License:

Copyright (c) 2008 by Nils Springob, nicai-systems, Germany

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

/*! @file    copro.h
 *  @brief   Routinen zum Ansprechen des Coprozessors.
 *
 *  Dieses Modul erlaubt den Zugriff auf die Daten des ATmega88 Co-Prozessors.
 *  Vor Benutzung der Funktionen muss @ref spi_init() aufgerufen werden.
 *  @author  Nils Springob (nils@nicai-systems.de)
 *  @date    2008-11-16
 */

#ifndef NIBO_COPRO_H_
#define NIBO_COPRO_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * Aktuelle Geschwindigkeit des linken Rades
 */
extern int16_t copro_speed_l;

/*!
 * Aktuelle Geschwindigkeit des rechten Rades
 */
extern int16_t copro_speed_r;

/*!
 * Aktuelle Inkrements des linken Rades
 */
extern int16_t copro_ticks_l;

/*!
 * Aktuelle Inkrements des rechten Rades
 */
extern int16_t copro_ticks_r;

/*!
 * Aktueller Strom im linken Motor
 */
extern int16_t copro_current_l;

/*!
 * Aktuelle Strom im rechten Motor
 */
extern int16_t copro_current_r;


uint8_t copro_update_dist();

uint8_t copro_update_motor();

/*!
 * Aktualisiert alle Daten
 */
uint8_t copro_update();

/*!
 * Motoren anhalten
 */
uint8_t copro_stop();

/*!
 * PWM Werte für die beiden Motoren setzen. Die PWM Werte sind bei idealisierter
 * Mechanik und Elektonik proportional zum Drehmoment.
 * @param left Wert für linkes Rad (-1024 ... +1024)
 * @param right Wert für rechets Rad (-1024 ... +1024)
 */
uint8_t copro_setPWM(int16_t left, int16_t right);

/*!
 * Geschwindigkeit für die beiden Motoren setzen. Die Werte werden in Ticks/Sekunde
 * angegeben. 40 Ticks entsprechen einer Radumdrehung.
 * @param left Sollwert für linkes Rad
 * @param right Sollwert für rechets Rad
 */
uint8_t copro_setSpeed(int16_t left, int16_t right);

/*!
 * Zielposition für Räder setzen. Die Werte werden in Ticks
 * angegeben. 40 Ticks entsprechen einer Radumdrehung.
 * @param left absoluter Sollwert für linkes Rad
 * @param right absoluter Sollwert für rechets Rad
 * @param speed Wert für maximale Geschwindigkeit
 */
uint8_t copro_setTargetAbs(int16_t left, int16_t right, uint16_t speed);

/*!
 * Zielposition für Räder setzen. Die Werte werden in Ticks relativ zur
 * aktuellen Position angegeben. 40 Ticks entsprechen einer Radumdrehung.
 * @param left relativer Sollwert für linkes Rad
 * @param right relativer Sollwert für rechets Rad
 * @param speed Wert für maximale Geschwindigkeit
 */
uint8_t copro_setTargetRel(int16_t left, int16_t right, uint16_t speed);

/*!
 * Regelungsparameter setzen. Weitere Infos im Wiki unter
 * http://www.nibo-roboter.de/wiki/Motorcontroller-Firmware
 * @param ki Integralanteil
 * @param kp Proportionalanteil
 * @param kd Differentialanteil
 */
uint8_t copro_setSpeedParameters(int8_t ki, int8_t kp, int8_t kd);

/*!
 * Regelungsparameter setzen. Weitere Infos im Wiki unter
 * http://www.nibo-roboter.de/wiki/Motorcontroller-Firmware
 * @param ki Integralanteil
 * @param kp Proportionalanteil
 * @param kd Differentialanteil
 */
uint8_t copro_setPositionParameters(int8_t ki, int8_t kp, int8_t kd);

/*!
 * Odometriewerte auf angegebene Werte zurücksetzen
 * @param left Wert für linkes Rad
 * @param right Wert für rechets Rad
 */
uint8_t copro_resetOdometry(int16_t left, int16_t right);



enum {
  COPRO_IR_PASSIVE = 0,
  COPRO_IR_RC5TX   = 1,
  COPRO_IR_MEASURE = 2,
};

/*!
 * Aktueller Modus des IR-Controllers
 */
extern uint8_t copro_ir_mode;

/*!
 * Aktuelle Reflexionswerte der Distanzsensoren
 */
extern uint16_t copro_distance[5];

/*!
 * Zuletzt empfangenes RC5 Kommando
 */
extern uint16_t copro_rc5_cmd;

/*!
 * Aussenden von IR-Licht stoppen, nur Empfang
 */
uint8_t copro_ir_stop();

/*!
 * Reflexionsmessung starten
 */
uint8_t copro_ir_startMeasure();

/*!
 * RC5 Code übertragen
 * @param rc5 RC5 Code
 */
uint8_t copro_transmitRC5(uint16_t rc5);






#ifdef __cplusplus
} // extern "C"
#endif

#endif // NIBO_COPRO_H_
