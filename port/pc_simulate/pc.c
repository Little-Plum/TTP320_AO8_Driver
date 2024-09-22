#include "TTP320_AO8.h"
#include <stdint.h>
#include <stdio.h>

static uint8_t read_sda() {
  printf("sda= ");
  char ch;
  // ch = getchar();
  scanf("%c", &ch);
  if (ch == '1') {
    return 1;
  } else {
    return 0;
  }
}
static void sda_high() { printf("sda: 1\n"); }
static void sda_low() { printf("sda: 0\n"); }
static void scl_high() { /*printf("scl: 1\n");*/
}
static void scl_low() { /*printf("scl: 0\n"); */
}
static void sda_mode_out() { printf("sda: out\n"); }
static void sda_mode_in() { printf("sda: in\n"); }
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