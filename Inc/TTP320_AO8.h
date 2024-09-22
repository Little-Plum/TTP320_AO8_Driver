#ifndef __TTP320_AO8_H__
#define __TTP320_AO8_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

typedef enum {
  TTP_OUT_DUTY = 0x01,
  TTP_SCAN_FREQ_START_VAL = 0x04,
  TTP_SCAN_FREQ_END_VAL = 0x05,
  TTP_VC_CHARGE_TIME_AND_SCAN_POWER = 0x06,
  TTP_SCAN_FREQ_MECHAISM_FLAG = 0x07,
  TTP_RE_SCAN = 0x08,
  TTP_LVD_CONT = 0x09,
  TTP_POWERON_MODE = 0x0C
} TTP320_AO8_CMD_t;

typedef enum {
  TTP_READ_SCAN_BUSY = 0x11,
  TTP_READ_LVD_FLAG = 0x12,
  TTP_READ_HIGHEST_VC = 0x13,
  TTP_READ_BEST_FREQ = 0x14,
  TTP_READ_CURRENT_NV = 0x16,
  TTP_READ_CURRENT_SCAN_FREQ = 0x17
} TTP320_AO8_ReadRegs_t;

typedef struct {
  uint8_t (*read_sda)();
  void (*sda_high)();
  void (*sda_low)();
  void (*scl_high)();
  void (*scl_low)();
  void (*sda_mode_out)();
  void (*sda_mode_in)();
  void (*delay_us)(size_t us);
} ttp_io_i;

typedef struct {
  uint32_t clk_period_us;
  uint32_t clk_half_period_us;
  ttp_io_i *io;
} ttp_handle_t;

void ttp_init(ttp_handle_t *self, size_t clk_freq, ttp_io_i *io);
void ttp_comm_send_CMD(ttp_handle_t *self, uint8_t cmd, uint8_t data);
uint8_t ttp_comm_read_reg(ttp_handle_t *self, uint8_t cmd);

#ifdef __cplusplus
}
#endif

#endif