// #include "TTP320_AO8.h"
// #include <stdint.h>
// #include "stm32h7xx_hal.h"

// #define TTP_SDA_GPIO_PORT GPIOB
// #define TTP_SDA_GPIO_PIN  GPIO_PIN_7
// #define TTP_SCL_GPIO_PORT GPIOB
// #define TTP_SCL_GPIO_PIN  GPIO_PIN_6

// uint8_t read_sda()
// {
//     if (HAL_GPIO_ReadPin(TTP_SDA_GPIO_PORT, TTP_SDA_GPIO_PIN) == GPIO_PIN_SET)
//         return 1;
//     else
//         return 0;
// }

// static void sda_high()
// {
//     HAL_GPIO_WritePin(TTP_SDA_GPIO_PORT, TTP_SDA_GPIO_PIN, GPIO_PIN_SET);
// }

// static void sda_low()
// {
//     HAL_GPIO_WritePin(TTP_SDA_GPIO_PORT, TTP_SDA_GPIO_PIN, GPIO_PIN_RESET);
// }

// static void scl_high()
// {
//     HAL_GPIO_WritePin(TTP_SCL_GPIO_PORT, TTP_SCL_GPIO_PIN, GPIO_PIN_SET);
// }

// static void scl_low()
// {
//     HAL_GPIO_WritePin(TTP_SCL_GPIO_PORT, TTP_SCL_GPIO_PIN, GPIO_PIN_RESET);
// }

// static void sda_mode_out()
// {
//     GPIO_InitTypeDef GPIO_InitStruct = {0};
//     GPIO_InitStruct.Pin              = TTP_SDA_GPIO_PIN;
//     GPIO_InitStruct.Mode             = GPIO_MODE_OUTPUT_OD;
//     GPIO_InitStruct.Pull             = GPIO_NOPULL;
//     GPIO_InitStruct.Speed            = GPIO_SPEED_FREQ_LOW;
//     HAL_GPIO_Init(TTP_SDA_GPIO_PORT, &GPIO_InitStruct);
// }

// static void sda_in()
// {
//     GPIO_InitTypeDef GPIO_InitStruct = {0};
//     GPIO_InitStruct.Pin              = TTP_SDA_GPIO_PIN;
//     GPIO_InitStruct.Mode             = GPIO_MODE_INPUT;
//     GPIO_InitStruct.Pull             = GPIO_NOPULL;
//     HAL_GPIO_Init(TTP_SDA_GPIO_PORT, &GPIO_InitStruct);
// }

// static void delay_us(size_t us)
// {
//     HAL_Delay(us);
// }

// soft_i2c_io_t io = {
//     .read_sda     = read_sda,
//     .sda_high     = sda_high,
//     .sda_low      = sda_low,
//     .scl_high     = scl_high,
//     .scl_low      = scl_low,
//     .sda_mode_out = sda_mode_out,
//     .sda_in       = sda_in,
// };

// void TTP320_init(soft_i2c_handle_t *self, size_t clk_freq, soft_i2c_io_t *io)
// {
//     if (self == NULL)
//         return;
//     if (clk_freq > 25000)
//         return;
//     self->delay_us           = delay_us;
//     self->clk_period_us      = 1 / clk_freq;
//     self->clk_half_period_us = self->clk_period_us / 2;
//     self->io                 = io;
// }
