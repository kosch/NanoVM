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

/*! @file    iodefs_nibobee.h
 *  @brief   Zuordnung der physikalischen Pins zu symbolischen Namen
 *  @author  Nils Springob (nils@nicai-systems.de)
 *  @date    2009-08-19
 */


/*! LED group */
#define IO_LEDS_PORT  PORTB
#define IO_LEDS_MASK  0x0f
#define IO_LEDS_DDR   DDRB
#define IO_LEDS_BIT_L_YE 0
#define IO_LEDS_BIT_L_RD 1
#define IO_LEDS_BIT_R_RD 2
#define IO_LEDS_BIT_R_YE 3


/*! Sensor group */
#define IO_SENS_PORT  PORTC
#define IO_SENS_PIN   PINC
#define IO_SENS_MASK  0xf0
#define IO_SENS_DDR   DDRC
#define IO_SENS_BIT_LEFT1  4
#define IO_SENS_BIT_LEFT2  5
#define IO_SENS_BIT_RIGHT1 6
#define IO_SENS_BIT_RIGHT2 7


/*! Motor group */
#define IO_MOTOR_PORT  PORTD
#define IO_MOTOR_PIN   PIND
#define IO_MOTOR_MASK  0xf0
#define IO_MOTOR_DDR   DDRD
#define IO_MOTOR_BIT_DIR_LEFT  6
#define IO_MOTOR_BIT_DIR_RIGHT 7
#define IO_MOTOR_BIT_PWM_LEFT  5
#define IO_MOTOR_BIT_PWM_RIGHT 4


/*! Odometry group */
#define IO_ODO_PORT  PORTD
#define IO_ODO_PIN   PIND
#define IO_ODO_MASK  0x0c
#define IO_ODO_DDR   DDRD
#define IO_ODO_BIT_LEFT  2
#define IO_ODO_BIT_RIGHT 3


/*! Extension Port group */
#define IO_EXT_PORT  PORTC
#define IO_EXT_PIN   PINC
#define IO_EXT_MASK  0x0f
#define IO_EXT_DDR   DDRC
#define IO_EXT_BIT_0  0
#define IO_EXT_BIT_1  1
#define IO_EXT_BIT_2  2
#define IO_EXT_BIT_3  3


/*! Line sensor enable */
#define IO_LINE_EN       IO_LINE_EN
#define IO_LINE_EN_PORT  PORTB
#define IO_LINE_EN_BIT   4
#define IO_LINE_EN_DDR   DDRB


/*! I2C SDA */
#define IO_I2C_SDA_PORT  PORTC
#define IO_I2C_SDA_PIN   PINC
#define IO_I2C_SDA_BIT   1
#define IO_I2C_SDA_DDR   DDRC


/*! I2C SCL */
#define IO_I2C_SCL_PORT  PORTC
#define IO_I2C_SCL_PIN   PINC
#define IO_I2C_SCL_BIT   0
#define IO_I2C_SCL_DDR   DDRC


/*! RXD */
#define IO_UART_RXD_PORT  PORTD
#define IO_UART_RXD_PIN   PIND
#define IO_UART_RXD_BIT   0
#define IO_UART_RXD_DDR   DDRD


/*! TXD */
#define IO_UART_TXD_PORT  PORTD
#define IO_UART_TXD_PIN   PIND
#define IO_UART_TXD_BIT   1
#define IO_UART_TXD_DDR   DDRD



/*! Analog channels */
#define AN_LINE_R    7        /*!< ADC-PIN liniesensor right */
#define AN_LINE_C    6        /*!< ADC-PIN liniesensor center */
#define AN_LINE_L    5        /*!< ADC-PIN liniesensor left */
#define AN_VBAT      4        /*!< ADC-PIN battery voltage */
#define AN_X3        3        /*!< ADC-PIN extension 3 */
#define AN_X2        2        /*!< ADC-PIN extension 2 */
#define AN_X1        1        /*!< ADC-PIN extension 1 */
#define AN_X0        0        /*!< ADC-PIN extension 0 */


