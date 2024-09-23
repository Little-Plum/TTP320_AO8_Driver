#ifndef __PC_H__
#define __PC_H__

#ifdef __cplusplus
extern "C" {
#endif
#include "TTP320_AO8.h"
#include "TTP320_AO8_hal.h"
#include <stdint.h>

ttp_io_i *ttp320_pc_hal_init(void);

#ifdef __cplusplus
}
#endif
#endif