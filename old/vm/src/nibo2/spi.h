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

/*! @file    spi.h
 *  @brief   Routinen zur Kommunikation ueber SPI
 *  @author  Nils Springob (nils@nicai-systems.de)
 *  @date    2009-04-14
 *
 * Dieses Modul erlaubt die Kommunikation über die SPI Schnittstelle. Der
 * ATmega128 läuft dabei im Slave Modus, der ATmega88 als Master. Das Modul wird
 * in der Regel zusammen mit dem Copro Modul verwendet.
 * Die Kommunikation wird vom ATmega88 automatisch alle 10 ms (100 Hz) initiiert.
 */

#ifndef NIBO_SPISLAVE_H_
#define NIBO_SPISLAVE_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SPI_BUF_SIZE 25

/*!
 * Frame counter, Anzahl der empfangenen Frames (zählt alle 256 Frames
 * wieder ab 0). Der Wert verändert sich alle 10 ms.
 */
extern uint8_t spi_frame_cnt;


/*!
 * Sende-Puffer zur Datenübertragung
 */
extern uint8_t spi_tx_buf[SPI_BUF_SIZE];

/*!
 * Empfangs-Puffer zur Datenübertragung
 */
extern uint8_t spi_rx_buf[SPI_BUF_SIZE];

/*!
 * Initialisierung der SPI Schnittstelle
 */
void spi_init(void);

/*!
 * Callback - muss im auswertendem Modul definiert werden, nur innerhalb
 * dieser Funktion ist der Zugriff auf @ref spi_rx_buf[] und @ref spi_tx_buf[]
 * erlaubt. Wird alle 10 ms aufgerufen.
 * @return tx_size
 */
uint8_t spi_finished_callback(uint8_t rx_size);


#ifdef __cplusplus
} // extern "C"
#endif

#endif // NIBO_SPISLAVE_H_
