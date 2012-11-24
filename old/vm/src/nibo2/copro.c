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

#include "nibo2/iodefs.h"
#include "nibo2/copro.h"
#include "nibo2/spi.h"
#include "nibo2/copro_prot.h"
#include <string.h>
#include <avr/interrupt.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LOBYTE(x)        (uint8_t)((uint16_t)x)
#define HIBYTE(x)        (uint8_t)(((uint16_t)x)>>8)
#define MAKE_WORD(hi,lo) (((uint8_t)hi*(uint16_t)0x100)+(uint8_t)lo)


int16_t copro_speed_l;
int16_t copro_speed_r;

int16_t copro_ticks_l;
int16_t copro_ticks_r;

int16_t copro_current_l;
int16_t copro_current_r;

float copro_pos_x;
float copro_pos_y;
float copro_pos_ori;

uint8_t copro_ir_mode;
uint16_t copro_distance[5];
uint8_t copro_rc5_count;
uint16_t copro_rc5_cmd;

uint8_t copro_buffer[25];
uint8_t copro_commands[3][7];

uint8_t copro_seq;

// CALLBACK

uint8_t spi_finished_callback(uint8_t rx_size) {
  uint8_t pos=0;
  copro_seq++;
  if (rx_size==25) {
    memcpy(copro_buffer, spi_rx_buf, 25);
  }
  spi_tx_buf[0]=spi_tx_buf[7]=spi_tx_buf[14]=0xff;
  if (copro_commands[0][0]!=0xff) {
     memcpy(spi_tx_buf+pos, copro_commands[0], 7);
     copro_commands[0][0]=0xff;
     pos+=7;
  }
  if (copro_commands[1][0]!=0xff) {
     memcpy(spi_tx_buf+pos, copro_commands[1], 7);
     copro_commands[0][0]=0xff;
     pos+=7;
  }
  if (copro_commands[2][0]!=0xff) {
     memcpy(spi_tx_buf+pos, copro_commands[2], 7);
     copro_commands[0][0]=0xff;
     pos+=7;
  }
  return pos?21:7;
}

extern uint8_t spi_debug;

uint8_t copro_update_dist() {
  cli();
  copro_distance[0] = MAKE_WORD(copro_buffer[1], copro_buffer[0]);
  copro_distance[1] = MAKE_WORD(copro_buffer[3], copro_buffer[2]);
  copro_distance[2] = MAKE_WORD(copro_buffer[5], copro_buffer[4]);
  copro_distance[3] = MAKE_WORD(copro_buffer[7], copro_buffer[6]);
  copro_distance[4] = MAKE_WORD(copro_buffer[9], copro_buffer[8]);
  sei();
  return 1;
}

uint8_t copro_update_motor() {
  cli();
  copro_ticks_l = MAKE_WORD(copro_buffer[11], copro_buffer[10]);
  copro_ticks_r = MAKE_WORD(copro_buffer[13], copro_buffer[12]);
  copro_speed_l = MAKE_WORD(copro_buffer[15], copro_buffer[14]);
  copro_speed_r = MAKE_WORD(copro_buffer[17], copro_buffer[16]);
  copro_current_l = MAKE_WORD(copro_buffer[19], copro_buffer[18]);
  copro_current_r = MAKE_WORD(copro_buffer[21], copro_buffer[20]);
  sei();
  return 1;
}

uint8_t copro_update() {
  copro_update_dist();
  copro_update_motor();
  return 1;
}

uint8_t copro_stop() {
  cli();
  copro_commands[0][0] = COPRO_CMD_STOP;
  sei();
  return 1;
}


uint8_t copro_setPWM(int16_t left, int16_t right) {
  cli();
  copro_commands[0][0] = COPRO_CMD_SETPWM;
  copro_commands[0][1] = LOBYTE(left);
  copro_commands[0][2] = HIBYTE(left);
  copro_commands[0][3] = LOBYTE(right);
  copro_commands[0][4] = HIBYTE(right);
  sei();
  return 1;
}

uint8_t copro_setSpeed(int16_t left, int16_t right) {
  cli();
  copro_commands[0][0] = COPRO_CMD_SETSPEED;
  copro_commands[0][1] = LOBYTE(left);
  copro_commands[0][2] = HIBYTE(left);
  copro_commands[0][3] = LOBYTE(right);
  copro_commands[0][4] = HIBYTE(right);
  sei();
  return 1;
}

uint8_t copro_setTargetAbs(int16_t left, int16_t right, uint16_t speed) {
  cli();
  copro_commands[0][0] = COPRO_CMD_SETTARGET_ABS;
  copro_commands[0][1] = LOBYTE(left);
  copro_commands[0][2] = HIBYTE(left);
  copro_commands[0][3] = LOBYTE(right);
  copro_commands[0][4] = HIBYTE(right);
  copro_commands[0][5] = LOBYTE(speed);
  copro_commands[0][6] = HIBYTE(speed);
  sei();
  return 1;
}

uint8_t copro_setTargetRel(int16_t left, int16_t right, uint16_t speed) {
  cli();
  copro_commands[0][0] = COPRO_CMD_SETTARGET_REL;
  copro_commands[0][1] = LOBYTE(left);
  copro_commands[0][2] = HIBYTE(left);
  copro_commands[0][3] = LOBYTE(right);
  copro_commands[0][4] = HIBYTE(right);
  copro_commands[0][5] = LOBYTE(speed);
  copro_commands[0][6] = HIBYTE(speed);
  sei();
  return 1;
}

uint8_t copro_setSpeedParameters(int8_t ki, int8_t kp, int8_t kd) {
  cli();
  copro_commands[2][0] = COPRO_CMD_SETPARAMETERS;
  copro_commands[2][1] = ki;
  copro_commands[2][2] = kp;
  copro_commands[2][3] = kd;
  sei();
  return 1;
}

uint8_t copro_setPositionParameters(int8_t ki, int8_t kp, int8_t kd) {
  return 1;
}

uint8_t copro_resetOdometry(int16_t left, int16_t right) {
  return 1;
}

uint8_t copro_ir_stop() {
  cli();
  copro_commands[1][0] = COPRO_CMD_STOP_IR;
  sei();
  return 1;
}

uint8_t copro_ir_startMeasure() {
  cli();
  copro_commands[1][0] = COPRO_CMD_START_IR;
  sei();
  return 1;
}

uint8_t copro_transmitRC5(uint16_t rc5) {
  cli();
  copro_commands[1][0] = COPRO_CMD_START_IR;
  copro_commands[1][1] = LOBYTE(rc5);
  copro_commands[1][2] = HIBYTE(rc5);
  sei();
  return 1;
}


#ifdef __cplusplus
} // extern "C"
#endif
