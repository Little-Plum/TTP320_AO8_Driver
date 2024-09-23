#ifndef __TTP320_AO8_HAL_H__
#define __TTP320_AO8_HAL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

typedef struct ttp_io_s ttp_io_i;

struct ttp_io_s {
  uint8_t (*read_sda)();
  void (*sda_high)();
  void (*sda_low)();
  void (*scl_high)();
  void (*scl_low)();
  void (*sda_mode_out)();
  void (*sda_mode_in)();
  void (*delay_us)(size_t us);
};



#ifdef __cplusplus
}
#endif

#endif //__TTP320_AO8_HAL_H__