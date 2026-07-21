#ifndef I2C_H
#define I2C_H

#include "clock.h"
#include "error.h"

/* cppcheck-suppress misra-c2012-11.4 */
#define I2C ((volatile i2c_t *)0x005210)

typedef struct
{
    volatile unsigned char CR1;    /* Control Register 1 */
    volatile unsigned char CR2;    /* Control Register 2 */
    volatile unsigned char FREQR;  /* Frequency Register */
    volatile unsigned char OARL;   /* Own Address Register Low */
    volatile unsigned char OARH;   /* Own Address Register High */
    volatile unsigned char DR;     /* Data Register */
    volatile unsigned char SR1;    /* Status Register 1 */
    volatile unsigned char SR2;    /* Status Register 2 */
    volatile unsigned char SR3;    /* Status Register 3 */
    volatile unsigned char ITR;    /* Interrupt Control Register */
    volatile unsigned char CCRL;   /* Clock Control Register Low */
    volatile unsigned char CCRH;   /* Clock Control Register High */
    volatile unsigned char TRISER; /* TRISE Register */
    volatile unsigned char PECR;   /* Packet Error Checking Register */
} i2c_t;

typedef enum
{
    I2C_FREQ_1MHz = 0x01U,
    I2C_FREQ_2MHz = 0x02U,
    I2C_FREQ_3MHz = 0x03U,
    I2C_FREQ_4MHz = 0x04U
} i2c_freq_t;

typedef enum
{
    I2C_FLAGS_TXE = 0x80U,
    I2C_FLAGS_RXNE = 0x40U,
    I2C_FLAGS_RESERVED = 0x20U,
    I2C_FLAGS_STOPF = 0x10U,
    I2C_FLAGS_ADD10 = 0x08U,
    I2C_FLAGS_BTF = 0x04U,
    I2C_FLAGS_ADDR = 0x02U,
    I2C_FLAGS_SB = 0x01U
} i2c_flags_t;

void i2c_init(i2c_freq_t freq);
void i2c_send(unsigned char data);
unsigned char i2c_read(void);
void i2c_deinit(void);

#endif /* I2C_H */
