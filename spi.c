#include "spi.h"

error_t spi_init(const spi_mode_t mode, const spi_baud_rate_t baud,
                 const spi_frame_format_t frame)
{
    check(!(SPI->CR1 & (1 << 6)), FAIL);
    check(SPI_MODE_IS_OK(mode), INVALID_ARG);
    check(SPI_BAUD_IS_OK(baud), INVALID_ARG);
    check(SPI_FRAME_FORMAT_IS_OK(frame), INVALID_ARG);

    SPI->CR1 |= mode;
    SPI->CR1 |= baud;
    SPI->CR1 |= frame;

    return OK;
}

error_t spi_enable(void)
{
    check(!(SPI->CR1 & (1 << 6)), FAIL);

    SPI->CR1 |= (1 << 6);

    return OK;
}

error_t spi_disable(void)
{
    check(SPI->CR1 & (1 << 6), FAIL);

    SPI->CR1 &= (0 << 6);

    return OK;
}

error_t spi_send(const spi_device_t *device, const spi_transaction_t type,
                 const unsigned char data)
{
    check(device, FAIL);
    check(SPI->CR1 & (1 << 6), FAIL);
    check(SPI_TRANSACTION_TYPE_IS_OK(type), INVALID_ARG);
    check(!(SPI->SR & (1 << 7)), FAIL);

    (void)gpio_level_set(device->gpio_cs, device->cs, LOW);
    if (type == SPI_TRANSACTION_COMMAND)
        (void)gpio_level_set(device->gpio_dc, device->dc, HIGH);
    else
        (void)gpio_level_set(device->gpio_dc, device->dc, LOW);

    SPI->DR = data;

    (void)gpio_level_set(device->gpio_cs, device->cs, HIGH);

    return OK;
}

void spi_deinit(void)
{
    SPI->SR = (unsigned char)0x02;
    SPI->DR = (unsigned char)0x00;
    SPI->CR1 = (unsigned char)0x00;
    SPI->CR2 = (unsigned char)0x00;
    SPI->ICR = (unsigned char)0x00;
    SPI->CRCPR = (unsigned char)0x07;
    SPI->RXCRCR = (unsigned char)0xFF;
    SPI->TXCRCR = (unsigned char)0xFF;
}

unsigned char spi_read(const spi_device_t *device,
                       const unsigned char data)
{
    check(device, FAIL);
    check(SPI->CR1 & (1 << 6), FAIL);

    SPI->DR = data;

    return SPI->DR;
}
