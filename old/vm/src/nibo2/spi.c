

#include "nibo2/iodefs.h"
#include "nibo2/spi.h"
#include <avr/interrupt.h>

#define nop() __asm volatile("nop")

uint8_t spi_size;
uint8_t spi_pos;
uint8_t spi_tx_chk;
uint8_t spi_rx_chk;

uint8_t spi_rx_size;
uint8_t spi_tx_size;

uint8_t spi_rx_buf[SPI_BUF_SIZE];
uint8_t spi_tx_buf[SPI_BUF_SIZE];

uint8_t spi_debug;
uint8_t spi_frame_cnt;

inline static void spi_tx (uint8_t val) {
  SPDR = val;
  spi_tx_chk ^= val;
}

inline static uint8_t spi_rx() {
  uint8_t val = SPDR;
  spi_rx_chk ^= val;
  return val;
}


uint8_t spi_restart_transmission(uint8_t size) {
  /*
    pre: SPI disabled
    post: SPI enabled, transmission ready
  */
  
  spi_pos = 0;
  spi_tx_size = size;
  spi_size = size+1;
  spi_tx_chk = 0x96;
  spi_rx_chk = 0x96;
  // wait for spi bus idle, finish running frame
  // will take some time if out of sync...
  cli();
  while (get_input_bit(IO_ISP_SS)==0) {
    sei();
    nop();
    cli();
  }
  // spi is ready, prepare registers
  SPCR = _BV(SPIE) | _BV(SPE);
  spi_tx(size);
  SPSR |= _BV(SPIF);
  sei();
  return 0;
}

void spi_init(void) {
  deactivate_output_bit(IO_ISP_SS);
  clear_output_bit(IO_ISP_SS);
  activate_output_bit(IO_ISP_MISO);
  set_output_bit(IO_ISP_MISO);
  spi_restart_transmission(0);
}



ISR(SPI_STC_vect) {
  // receive
  uint8_t rx_data = spi_rx();

  if (spi_pos==0) {
    spi_rx_size = rx_data;
    if (spi_rx_size>sizeof(spi_rx_buf)) {
      spi_tx_size = 0;
      spi_rx_size = 0;
      spi_size = 1;
    } else if (spi_rx_size+1>spi_size) {
      spi_size = spi_rx_size+1;
    }
  } else {
    if (spi_pos-1<spi_rx_size) {
      spi_rx_buf[spi_pos-1]=rx_data;
    } else if (spi_pos-1==spi_rx_size) {
      if (spi_rx_chk!=0) {
        // chk invalid
        spi_rx_size=0;
      }
    }
  }

  if (spi_pos<spi_tx_size) {
    // transmit
    spi_tx(spi_tx_buf[spi_pos]);
    spi_pos++;
  } else if (spi_pos==spi_tx_size) {
    spi_tx(spi_tx_chk);
    spi_pos++;
  } else if (spi_pos<spi_size) {
    spi_tx(0xff);
    spi_pos++;
  } else {
    // disable IRQ
    SPCR = _BV(SPE);
    spi_frame_cnt++;
    sei();
    spi_restart_transmission(spi_finished_callback(spi_rx_size));
  }
}


