#ifndef SPI_H
#define SPI_H

#include "error.h"
#include "gpio.h"

#define SPI ((spi *)0x005200)

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

typedef struct spi
{
    volatile unsigned char CR1;    /* Control Register 1 */
    volatile unsigned char CR2;    /* Control Register 2 */
    volatile unsigned char ICR;    /* Interrupt Control Register */
    volatile unsigned char SR;     /* Status Register */
    volatile unsigned char DR;     /* Data Register */
    volatile unsigned char CRCPR;  /* CRC Polynomial Register */
    volatile unsigned char RXCRCR; /* Rx CRC Register */
    volatile unsigned char TXCRCR; /* Tx CRC Register */
} spi;

typedef enum spi_mode_t
{
    SPI_MODE_SLAVE = (unsigned char)0x00,
    SPI_MODE_MASTER = (unsigned char)0x04
} spi_mode_t;

typedef enum spi_baudrate_t
{
    SPI_BAUDRATE_2 = (unsigned char)0x00,
    SPI_BAUDRATE_4 = (unsigned char)0x08,
    SPI_BAUDRATE_8 = (unsigned char)0x10,
    SPI_BAUDRATE_16 = (unsigned char)0x18,
    SPI_BAUDRATE_32 = (unsigned char)0x20,
    SPI_BAUDRATE_64 = (unsigned char)0x28,
    SPI_BAUDRATE_128 = (unsigned char)0x30,
    SPI_BAUDRATE_256 = (unsigned char)0x38
} spi_baudrate_t;

typedef enum spi_frame_format
{
    SPI_FRAME_FORMAT_MSB = (unsigned char)0x00,
    SPI_FRAME_FORMAT_LSB = (unsigned char)0x80
} spi_frame_format_t;

typedef enum spi_transaction
{
    SPI_TRANSACTION_DATA,
    SPI_TRANSACTION_COMMAND
} spi_transaction_t;

typedef enum spi_flags
{
    SPI_FLAG_BSY = (unsigned char)0x80,    /* Busy flag */
    SPI_FLAG_OVR = (unsigned char)0x40,    /* Overrun flag */
    SPI_FLAG_MODF = (unsigned char)0x20,   /* Mode fault */
    SPI_FLAG_CRCERR = (unsigned char)0x10, /* CRC error flag */
    SPI_FLAG_WKUP = (unsigned char)0x04,   /* Wakeup flag */
    SPI_FLAG_TXE = (unsigned char)0x02,    /* Transmit buffer not empty */
    SPI_FLAG_RXNE = (unsigned char)0x01    /* Receive buffer not empty */
} spi_flags_t;

typedef struct spi_device
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
unsigned char spi_read(spi_device_t *device, unsigned char data);
error_t spi_disable(void);
void spi_deinit(void);

#endif /* SPI_H */
