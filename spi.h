#ifndef SPI_H
#define SPI_H

#include "gpio.h"
#include "mcu_error.h"

#define SPI ((spi *)0x005200)

#define SPI_MODE_IS_OK(mode)                                    \
    (((mode) == SPI_MODE_SLAVE) || ((mode) == SPI_MODE_MASTER))
#define SPI_BAUD_IS_OK(baud)                                    \
    (((baud) == SPI_BAUD_RATE_2) ||                             \
     ((baud) == SPI_BAUD_RATE_4) ||                             \
     ((baud) == SPI_BAUD_RATE_8) ||                             \
     ((baud) == SPI_BAUD_RATE_16) ||                            \
     ((baud) == SPI_BAUD_RATE_32) ||                            \
     ((baud) == SPI_BAUD_RATE_64) ||                            \
     ((baud) == SPI_BAUD_RATE_128) ||                           \
     ((baud) == SPI_BAUD_RATE_256))
#define SPI_FRAME_FORMAT_IS_OK(frame)                           \
    (((frame) == SPI_FRAME_FORMAT_MSB) ||                       \
     ((frame) == SPI_FRAME_FORMAT_LSB))
#define SPI_TRANSACTION_TYPE_IS_OK(type)                        \
    (((type) == SPI_TRANSACTION_DATA) ||                        \
     ((type) == SPI_TRANSACTION_COMMAND))

typedef struct spi
{
    volatile unsigned char CR1; /* Control Register 1 */
    volatile unsigned char CR2; /* Control Register 2 */
    volatile unsigned char ICR; /* Interrupt Control Register */
    volatile unsigned char SR;  /* Status Register */
    volatile unsigned char DR;  /* Data Register */
    volatile unsigned char CRCPR;  /* CRC Polynomial Register */
    volatile unsigned char RXCRCR; /* Rx CRC Register */
    volatile unsigned char TXCRCR; /* Tx CRC Register */
} spi;

typedef enum spi_mode_t
{
    SPI_MODE_SLAVE = (unsigned char)0x00,
    SPI_MODE_MASTER = (unsigned char)0x04
} spi_mode_t;

typedef enum spi_baud_rate_t
{
    SPI_BAUD_RATE_2 = (unsigned char)0x00,
    SPI_BAUD_RATE_4 = (unsigned char)0x08,
    SPI_BAUD_RATE_8 = (unsigned char)0x10,
    SPI_BAUD_RATE_16 = (unsigned char)0x18,
    SPI_BAUD_RATE_32 = (unsigned char)0x20,
    SPI_BAUD_RATE_64 = (unsigned char)0x28,
    SPI_BAUD_RATE_128 = (unsigned char)0x30,
    SPI_BAUD_RATE_256 = (unsigned char)0x38
} spi_baud_rate_t;

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

typedef struct spi_device
{
    gpio_t *gpio_cs;
    gpio_t *gpio_dc;
    unsigned char cs;
    unsigned char dc;
} spi_device_t;

mcu_error_t spi_init(spi_mode_t mode, spi_baud_rate_t baud,
                     spi_frame_format_t frame);
mcu_error_t spi_enable(void);
mcu_error_t spi_send(spi_device_t *device,
                     spi_transaction_t type, unsigned char data);
unsigned char spi_read(spi_device_t* device, unsigned char data);
mcu_error_t spi_disable(void);
void spi_deinit(void);

#endif /* SPI_H */
