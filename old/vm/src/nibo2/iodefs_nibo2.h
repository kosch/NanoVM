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

/*! @file    iodefs_nibo2.h
 *  @brief   Zuordnung der physikalischen Pins zu symbolischen Namen
 *  @author  Nils Springob (nils@nicai-systems.de)
 *  @date    2008-07-19
 */


/*! Red LEDs */
#define IO_LEDS_RED_PORT  PORTE
#define IO_LEDS_RED_MASK  0xff
#define IO_LEDS_RED_DDR   DDRE

/*! Green LEDs */
#define IO_LEDS_GREEN_PORT  PORTC
#define IO_LEDS_GREEN_MASK  0xff
#define IO_LEDS_GREEN_DDR   DDRC


/*! White LED pair */
#define IO_LED_WHITE_PORT  PORTB
#define IO_LED_WHITE_BIT   5
#define IO_LED_WHITE_DDR   DDRB

/*! Display illumination */
#define IO_DISP_LIGHT_PORT  PORTB
#define IO_DISP_LIGHT_BIT   6
#define IO_DISP_LIGHT_DDR   DDRB

/*! Red and Green LEDs brightness */
#define IO_LED_RG_PORT  PORTB
#define IO_LED_RG_BIT   7
#define IO_LED_RG_DDR   DDRB

/*! Audio output */
#define IO_AUDIO_PORT  PORTB
#define IO_AUDIO_BIT   4
#define IO_AUDIO_DDR   DDRB



/*! Line and floor sensor */
#define IO_LINE_FLOOR_EN       IO_LINE_FLOOR_EN
#define IO_LINE_FLOOR_EN_PORT  PORTF
#define IO_LINE_FLOOR_EN_BIT   6
#define IO_LINE_FLOOR_EN_DDR   DDRF



/*! Analog channels */
#define AN_PORT       PORTF
#define AN_DDR        DDRF
#define AN_FLOOR_R    0        /*!< ADC-PIN floorsensor right */
#define AN_FLOOR_L    1        /*!< ADC-PIN floorsensor left  */
#define AN_LINE_L     2        /*!< ADC-PIN liniesensor left  */
#define AN_LINE_R     3        /*!< ADC-PIN liniesensor right */
#define AN_VBAT       7        /*!< ADC-PIN battery voltage   */


/*! Display register select */
#define IO_DISPLAY_RS       IO_DISPLAY_RS
#define IO_DISPLAY_RS_PORT  PORTG
#define IO_DISPLAY_RS_BIT   3
#define IO_DISPLAY_RS_DDR   DDRG

/*! Display read/write */
#define IO_DISPLAY_RW       IO_DISPLAY_RW
#define IO_DISPLAY_RW_PORT  PORTG
#define IO_DISPLAY_RW_BIT   4
#define IO_DISPLAY_RW_DDR   DDRG

/*! Display enable */
#define IO_DISPLAY_EN       IO_DISPLAY_EN
#define IO_DISPLAY_EN_PORT  PORTG
#define IO_DISPLAY_EN_BIT   2
#define IO_DISPLAY_EN_DDR   DDRG

/*! Display chip select 1 */
#define IO_DISPLAY_CS1       IO_DISPLAY_CS1
#define IO_DISPLAY_CS1_PORT  PORTG
#define IO_DISPLAY_CS1_BIT   0
#define IO_DISPLAY_CS1_DDR   DDRG

/*! Display chip select 2 */
#define IO_DISPLAY_CS2       IO_DISPLAY_CS2
#define IO_DISPLAY_CS2_PORT  PORTG
#define IO_DISPLAY_CS2_BIT   1
#define IO_DISPLAY_CS2_DDR   DDRG

/*! Display reset and SS */
#define IO_DISPLAY_RST       IO_DISPLAY_RST
#define IO_DISPLAY_RST_PIN   PINB
#define IO_DISPLAY_RST_PORT  PORTB
#define IO_DISPLAY_RST_BIT   0
#define IO_DISPLAY_RST_DDR   DDRB

/*! Display data port */
#define IO_DISPLAY_PORT  PORTA
#define IO_DISPLAY_PIN   PINA
#define IO_DISPLAY_DDR   DDRA


/*! Ext A */
#define IO_EXT_A_PORT  PORTD
#define IO_EXT_A_PIN   PIND
#define IO_EXT_A_BIT   6
#define IO_EXT_A_DDR   DDRD

/*! Ext B */
#define IO_EXT_B_PORT  PORTD
#define IO_EXT_B_PIN   PIND
#define IO_EXT_B_BIT   5
#define IO_EXT_B_DDR   DDRD

/*! Ext C */
#define IO_EXT_C_PORT  PORTD
#define IO_EXT_C_PIN   PIND
#define IO_EXT_C_BIT   3
#define IO_EXT_C_DDR   DDRD

/*! Ext D */
#define IO_EXT_D_PORT  PORTD
#define IO_EXT_D_PIN   PIND
#define IO_EXT_D_BIT   2
#define IO_EXT_D_DDR   DDRD

/*! Reset Coprocessor */
#define IO_RESET_CO_PORT  PORTD
#define IO_RESET_CO_BIT   7
#define IO_RESET_CO_DDR   DDRD


/*! Input 1 (switch) */
#define IO_INPUT_1       IO_INPUT_1
#define IO_INPUT_1_PORT  PORTD
#define IO_INPUT_1_PIN   PIND
#define IO_INPUT_1_BIT   4
#define IO_INPUT_1_DDR   DDRD

/*! Input 2 (jumper) */
#define IO_INPUT_2       IO_INPUT_2
#define IO_INPUT_2_PORT  PORTF
#define IO_INPUT_2_PIN   PINF
#define IO_INPUT_2_BIT   5
#define IO_INPUT_2_DDR   DDRF

/*! Input 3 (jumper) */
#define IO_INPUT_3       IO_INPUT_3
#define IO_INPUT_3_PORT  PORTF
#define IO_INPUT_3_PIN   PINF
#define IO_INPUT_3_BIT   4
#define IO_INPUT_3_DDR   DDRF


/*! ISP SCK */
#define IO_ISP_SCK_PORT  PORTB
#define IO_ISP_SCK_BIT   1
#define IO_ISP_SCK_DDR   DDRB

/*! ISP MOSI */
#define IO_ISP_MOSI_PORT  PORTB
#define IO_ISP_MOSI_BIT   2
#define IO_ISP_MOSI_DDR   DDRB

/*! ISP MISO */
#define IO_ISP_MISO_PORT  PORTB
#define IO_ISP_MISO_PIN   PINB
#define IO_ISP_MISO_BIT   3
#define IO_ISP_MISO_DDR   DDRB

/*! ISP SS shared with display reset */
#define IO_ISP_SS         IO_DISPLAY_RST

/*! I2C SDA */
#define IO_I2C_SDA_PORT  PORTD
#define IO_I2C_SDA_PIN   PIND
#define IO_I2C_SDA_BIT   1
#define IO_I2C_SDA_DDR   DDRD

/*! I2C SCL */
#define IO_I2C_SCL_PORT  PORTD
#define IO_I2C_SCL_PIN   PIND
#define IO_I2C_SCL_BIT   0
#define IO_I2C_SCL_DDR   DDRD


/*! I2C Interface configuration */
#define I2C_BUF_SIZE 16
//#define I2C_TWBR_INIT 72   /* 100 kHz */
#define I2C_TWBR_INIT 12   /* 400 kHz */


