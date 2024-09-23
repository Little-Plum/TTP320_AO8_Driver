#include "TTP320_AO8.h"
#include "TTP320_AO8_hal.h"
#include <stdint.h>
#include <stdio.h>

uint8_t gRdTestBuf = (0x3C & ~(0xC0));
uint8_t sda_state = 0;

#define SDA_IN_STATE 0
#define SDA_OUT_STATE 1

static uint8_t read_sda() {
  if (sda_state == SDA_OUT_STATE) {
    printf("SDA NOT IN READ STATE\n");
    return 0;
  }
  // get gRdTestBuf 6th bit,and shift left 1 bit
  uint8_t ret = (gRdTestBuf & (1 << 5)) >> 5;
  gRdTestBuf <<= 1;
  printf("sda read: %d\n", ret);
  if (ret)
    return 1;
  else
    return 0;
}
static void sda_high() {
  if (sda_state != SDA_OUT_STATE) {
    printf("SDA NOT IN OUT MODE\n");
    return;
  }
  printf("sda: 1\n");
}
static void sda_low() {
  if (sda_state != SDA_OUT_STATE) {
    printf("SDA NOT IN OUT MODE\n");
    return;
  }
  printf("sda: 0\n");
}
static void scl_high() { /*printf("scl: 1\n");*/
}
static void scl_low() { /*printf("scl: 0\n"); */
}
static void sda_mode_out() {
  sda_state = SDA_OUT_STATE;
  printf("sda: out\n");
}
static void sda_mode_in() {
  sda_state = SDA_IN_STATE;
  printf("sda: in\n");
}
static void delay_us(size_t us) { /*printf("delay: %d\n", us); */
}

ttp_io_i ttp = {
    .read_sda = read_sda,
    .sda_high = sda_high,
    .sda_low = sda_low,
    .scl_high = scl_high,
    .scl_low = scl_low,
    .sda_mode_out = sda_mode_out,
    .sda_mode_in = sda_mode_in,
    .delay_us = delay_us,
};

ttp_io_i *ttp320_pc_hal_init(void) { return &ttp; }