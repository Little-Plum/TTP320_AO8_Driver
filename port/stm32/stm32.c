#include "TTP320_AO8.h"
#include "stm32h7xx_hal.h"
#include "cmsis_os.h"
#include <stdint.h>

#define TTP_SDA_GPIO_PORT GPIOB
#define TTP_SDA_GPIO_PIN  GPIO_PIN_7
#define TTP_SCL_GPIO_PORT GPIOB
#define TTP_SCL_GPIO_PIN  GPIO_PIN_6

uint8_t read_sda()
{
    if (HAL_GPIO_ReadPin(TTP_SDA_GPIO_PORT, TTP_SDA_GPIO_PIN) == GPIO_PIN_SET)
        return 1;
    else
        return 0;
}

static void sda_high()
{
    HAL_GPIO_WritePin(TTP_SDA_GPIO_PORT, TTP_SDA_GPIO_PIN, GPIO_PIN_SET);
}

static void sda_low()
{
    HAL_GPIO_WritePin(TTP_SDA_GPIO_PORT, TTP_SDA_GPIO_PIN, GPIO_PIN_RESET);
}

static void scl_high()
{
    HAL_GPIO_WritePin(TTP_SCL_GPIO_PORT, TTP_SCL_GPIO_PIN, GPIO_PIN_SET);
}

static void scl_low()
{
    HAL_GPIO_WritePin(TTP_SCL_GPIO_PORT, TTP_SCL_GPIO_PIN, GPIO_PIN_RESET);
}

static void sda_mode_out()
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin              = TTP_SDA_GPIO_PIN;
    GPIO_InitStruct.Mode             = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull             = GPIO_PULLUP;
    GPIO_InitStruct.Speed            = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(TTP_SDA_GPIO_PORT, &GPIO_InitStruct);
}

static void sda_in()
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin              = TTP_SDA_GPIO_PIN;
    GPIO_InitStruct.Mode             = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull             = GPIO_PULLUP;
    HAL_GPIO_Init(TTP_SDA_GPIO_PORT, &GPIO_InitStruct);
}

static void delay_us(size_t us)
{
    osDelay((us));
}

ttp_io_i io = {
    .read_sda     = read_sda,
    .sda_high     = sda_high,
    .sda_low      = sda_low,
    .scl_high     = scl_high,
    .scl_low      = scl_low,
    .sda_mode_out = sda_mode_out,
    .sda_mode_in  = sda_in,
    .delay_us     = delay_us,
};

ttp_io_i *ttp320_hal_init(void)
{
    return &io;
}