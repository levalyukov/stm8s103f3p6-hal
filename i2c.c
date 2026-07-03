#include "i2c.h"

void i2c_deinit(void)
{
    I2C->CR1 = (unsigned char)0x00;
    I2C->CR2 = (unsigned char)0x00;
    I2C->FREQR = (unsigned char)0x00;
    I2C->OARL = (unsigned char)0x00;
    I2C->OARH = (unsigned char)0x00;
    I2C->DR = (unsigned char)0x00;
    I2C->SR1 = (unsigned char)0x00;
    I2C->SR2 = (unsigned char)0x00;
    I2C->SR3 = (unsigned char)0x00;
    I2C->ITR = (unsigned char)0x00;
    I2C->CCRL = (unsigned char)0x00;
    I2C->CCRH = (unsigned char)0x00;
    I2C->TRISER = (unsigned char)0x02;
    I2C->PECR = (unsigned char)0x00;
}
