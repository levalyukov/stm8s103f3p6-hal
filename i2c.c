#include "i2c.h"

void i2c_init(const i2c_freq_t freq)
{
    CLOCK->PCKENR1 |= CLK_GATING_I2C;
    I2C->FREQR = freq;
    I2C->CR1 |= (1U << 0U);
}

void i2c_send(const unsigned char data)
{
    while (!(I2C->SR1 & (unsigned char)I2C_FLAGS_TXE))
    {
    };
    I2C->DR = data;
}

unsigned char i2c_read(void)
{
    while (!(I2C->SR1 & (unsigned char)I2C_FLAGS_RXNE))
    {
    };
    return I2C->DR;
}

void i2c_deinit(void)
{
    CLOCK->PCKENR1 &= ~CLK_GATING_I2C;
    I2C->CR1 = 0x00U;
    I2C->CR2 = 0x00U;
    I2C->FREQR = 0x00U;
    I2C->OARL = 0x00U;
    I2C->OARH = 0x00U;
    I2C->DR = 0x00U;
    I2C->SR1 = 0x00U;
    I2C->SR2 = 0x00U;
    I2C->SR3 = 0x00U;
    I2C->ITR = 0x00U;
    I2C->CCRL = 0x00U;
    I2C->CCRH = 0x00U;
    I2C->TRISER = 0x02U;
    I2C->PECR = 0x00U;
}
