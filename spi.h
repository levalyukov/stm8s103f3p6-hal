#ifndef SPI_H
#define SPI_H

#include "clock.h"
#include "error.h"

/* cppcheck-suppress misra-c2012-11.4 */
#define SPI ((spi_t *)0x005200)

#define SPI_MODE_IS_OK(mode)                                              \
    (((mode) == SPI_MODE_SLAVE) || ((mode) == SPI_MODE_MASTER))

#define SPI_BAUD_IS_OK(baud)                                              \
    (((baud) == SPI_BAUDRATE_2) || ((baud) == SPI_BAUDRATE_4) ||          \
     ((baud) == SPI_BAUDRATE_8) || ((baud) == SPI_BAUDRATE_16) ||         \
     ((baud) == SPI_BAUDRATE_32) || ((baud) == SPI_BAUDRATE_64) ||        \
     ((baud) == SPI_BAUDRATE_128) || ((baud) == SPI_BAUDRATE_256))

#define SPI_FRAME_FORMAT_IS_OK(frame)                                     \
    (((frame) == SPI_FRAME_FORMAT_MSB) ||                                 \
     ((frame) == SPI_FRAME_FORMAT_LSB))

#define SPI_TRANSACTION_TYPE_IS_OK(type)                                  \
    (((type) == SPI_TRANSACTION_DATA) ||                                  \
     ((type) == SPI_TRANSACTION_COMMAND))

typedef struct
{
    volatile unsigned char CR1;    /* Control Register 1 */
    volatile unsigned char CR2;    /* Control Register 2 */
    volatile unsigned char ICR;    /* Interrupt Control Register */
    volatile unsigned char SR;     /* Status Register */
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
    SPI_BAUDRATE_2 = 0x00,
    SPI_BAUDRATE_4 = 0x08,
    SPI_BAUDRATE_8 = 0x10,
    SPI_BAUDRATE_16 = 0x18,
    SPI_BAUDRATE_32 = 0x20,
    SPI_BAUDRATE_64 = 0x28,
    SPI_BAUDRATE_128 = 0x30,
    SPI_BAUDRATE_256 = 0x38
} spi_baudrate_t;

typedef enum
{
    SPI_FRAME_FORMAT_MSB = 0x00,
    SPI_FRAME_FORMAT_LSB = 0x80
} spi_frame_format_t;

typedef enum
{
    SPI_TRANSACTION_DATA,
    SPI_TRANSACTION_COMMAND
} spi_transaction_t;

typedef enum
{
    SPI_FLAG_BSY = 0x80U,    /* Busy flag */
    SPI_FLAG_OVR = 0x40U,    /* Overrun flag */
    SPI_FLAG_MODF = 0x20U,   /* Mode fault */
    SPI_FLAG_CRCERR = 0x10U, /* CRC error flag */
    SPI_FLAG_WKUP = 0x04U,   /* Wakeup flag */
    SPI_FLAG_TXE = 0x02U,    /* Transmit buffer not empty */
    SPI_FLAG_RXNE = 0x01U    /* Receive buffer not empty */
} spi_flags_t;

typedef struct
{
    gpio_t *gpio_cs;
    gpio_t *gpio_dc;
    unsigned char cs;
    unsigned char dc;
} spi_device_t;

error_t spi_init(spi_mode_t mode, spi_baudrate_t baud,
                 spi_frame_format_t frame);
error_t spi_enable(void);
error_t spi_send(spi_device_t *device, spi_transaction_t type,
                 unsigned char data);
unsigned char spi_read(void);
error_t spi_disable(void);
void spi_deinit(void);

#endif /* SPI_H */
