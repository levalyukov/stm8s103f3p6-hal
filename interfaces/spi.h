#ifndef SPI_H
#define SPI_H

#include <power/clock.h>
/* cppcheck-suppress misra-c2012-11.4 */
#define SPI ((volatile spi_t *)0x005200)

typedef struct
{
    volatile unsigned char CR1;    /* Control Register 1 */
    volatile unsigned char CR2;    /* Control Register 2 */
    volatile unsigned char ICR;    /* Interrupt Control Register */
    const volatile unsigned char SR;     /* Status Register */
    volatile unsigned char DR;     /* Data Register */
    volatile unsigned char CRCPR;  /* CRC Polynomial Register */
    volatile unsigned char RXCRCR; /* Rx CRC Register */
    volatile unsigned char TXCRCR; /* Tx CRC Register */
} spi_t;

typedef enum spi_mode
{
    SPI_MODE_SLAVE = 0x00,
    SPI_MODE_MASTER = 0x04
} spi_mode_t;

typedef enum
{
    SPI_BAUDRATE_2 = 0x00U,
    SPI_BAUDRATE_4 = 0x08U,
    SPI_BAUDRATE_8 = 0x10U,
    SPI_BAUDRATE_16 = 0x18U,
    SPI_BAUDRATE_32 = 0x20U,
    SPI_BAUDRATE_64 = 0x28U,
    SPI_BAUDRATE_128 = 0x30U,
    SPI_BAUDRATE_256 = 0x38U
} spi_baudrate_t;

typedef enum
{
    SPI_FRAME_FORMAT_MSB = 0x00U,
    SPI_FRAME_FORMAT_LSB = 0x80U
} spi_frame_format_t;

typedef enum
{
    SPI_TRANSACTION_DATA,
    SPI_TRANSACTION_COMMAND
} spi_transaction_t;

static enum spi_flags_t {
    SPI_FLAGS_BSY = 0x80,    /* Busy flag */
    SPI_FLAGS_OVR = 0x40,    /* Overrun flag */
    SPI_FLAGS_MODF = 0x20,   /* Mode fault */
    SPI_FLAGS_CRCERR = 0x10, /* CRC error flag */
    SPI_FLAGS_WKUP = 0x04,   /* Wakeup flag */
    SPI_FLAGS_TXE = 0x02,    /* Transmit buffer not empty */
    SPI_FLAGS_RXNE = 0x01    /* Receive buffer not empty */
};

typedef struct
{
    gpio_t *gpio_cs;
    gpio_t *gpio_dc;
    unsigned char cs;
    unsigned char dc;
} spi_device_t;

void spi_init(spi_mode_t mode, spi_baudrate_t baud, spi_frame_format_t frame);
void spi_send(spi_device_t *device, spi_transaction_t type, unsigned char data);
unsigned char spi_read(void);
void spi_enable(void);
void spi_disable(void);
void spi_deinit(void);

#endif /* SPI_H */
