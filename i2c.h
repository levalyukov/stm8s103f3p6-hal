#ifndef I2C_H
#define I2C_H

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

void i2c_deinit(void);

#endif /* I2C_H */
