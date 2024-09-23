#include <assert.h>
#include <stdint.h>

#include "TTP320_AO8.h"
#define TTP_DATA_ESTABLISH_DELAY_US (2)

#define HIGH                        1
#define LOW                         0

#define TTP_COMMAND_BITS            (5)
#define TTP_DATA_BITS               (6)
#include "stdio.h"

void ttp_init(ttp_handle_t *this, size_t clk_freq, ttp_io_i *io)
{
    printf("clk_freq: %zu\n", clk_freq);
    if (this == NULL)
        return;
    if (io == NULL)
        return;
    if (clk_freq > 25000)
        return;
    float clk_pd             = (1e6 / (float)clk_freq);
    this->clk_period_us      = (uint32_t)clk_pd;
    this->clk_half_period_us = this->clk_period_us / 2.0f;
    this->io                 = io;

    printf("clk_period_us: %d\n", this->clk_period_us);
    printf("clk_half_period_us: %d\n", this->clk_half_period_us);
}

/*    _____           _____
 *SCL      \_________/      主机发起
 *    __________
 *SDA           \________   从机回应
 */
static uint8_t ttp_comm_start(ttp_handle_t *this, size_t timeout_us)
{
    assert(this != NULL);
    assert(this->io != NULL);
    this->io->scl_low();
    this->io->sda_mode_in();
    while (this->io->read_sda() == HIGH)
    {
        timeout_us--;
        this->io->delay_us(1);
        if (timeout_us == 0)
        {
            this->io->scl_high();
            return -1;
        }
    }

    this->io->scl_high();
    return 0;
}

static void ttp_comm_stop(ttp_handle_t *this, size_t timeout_us)
{
    /*               _______
     *SCL __________/        主机低电平时，SDA由低变高
     *          ____________
     *SDA ____/              总线闲置
     */
    this->io->scl_low();
    this->io->sda_mode_in();
    while (this->io->read_sda() == HIGH)
    {
        timeout_us--;
        this->io->delay_us(1);
        if (timeout_us == 0)
        {
            break;
        }
    }
    this->io->scl_high();
}

static void send_bits_MSB_first(ttp_handle_t *this, uint8_t data,
                                size_t len_bits)
{
    uint8_t tgt_bit = 1 << (len_bits - 1);
    for (uint8_t i = 0; i < len_bits; i++)
    {
        if ((data << i) & tgt_bit)
        {
            this->io->sda_high();
        }
        else
        {
            this->io->sda_low();
        }
        this->io->delay_us(TTP_DATA_ESTABLISH_DELAY_US);

        this->io->scl_low();
        this->io->delay_us(this->clk_half_period_us);
        this->io->scl_high();
        this->io->delay_us(this->clk_half_period_us);
    }
    printf("data: 0x%x sent\n", data);
}

void ttp_comm_send_CMD(ttp_handle_t *this, uint8_t cmd, uint8_t data)
{
    ttp_comm_start(this, 1000);
    this->io->sda_mode_out();
    send_bits_MSB_first(this, cmd, TTP_COMMAND_BITS);
    send_bits_MSB_first(this, data, TTP_DATA_BITS);
    ttp_comm_stop(this, 1000);
}

uint8_t ttp_comm_read_reg(ttp_handle_t *this, uint8_t cmd)
{
    uint8_t data     = 0;
    uint8_t data_bit = 0;
    this->io->sda_mode_out();
    send_bits_MSB_first(this, cmd, TTP_COMMAND_BITS);
    this->io->sda_mode_in();
    for (uint8_t i = 0; i < TTP_DATA_BITS; i++)
    {
        this->io->scl_low();
        this->io->delay_us(this->clk_half_period_us);

        // ensure only read LSB
        data_bit = (1) & this->io->read_sda();
        printf("bit: %#o read\n", data_bit);
        data = (data << 1) | data_bit;

        this->io->scl_high();
        this->io->delay_us(this->clk_half_period_us);
    }
    printf("data: %#x read\n", data);
    return data;
}
