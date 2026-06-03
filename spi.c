#include "spi.h"

mcu_error_t spi_init(const spi_mode_t mode,
                     const spi_baud_rate_t baud,
                     const spi_frame_format_t frame)
{
    _check(!(SPI->CR1 & (1 << 6)), FAIL);
    _check(SPI_MODE_IS_OK(mode), INVALID_ARG);
    _check(SPI_BAUD_IS_OK(baud), INVALID_ARG);
    _check(SPI_FRAME_FORMAT_IS_OK(frame), INVALID_ARG);

    SPI->CR1 |= mode;
    SPI->CR1 |= baud;
    SPI->CR1 |= frame;

    return OK;
}

mcu_error_t spi_enable(void)
{
    _check(!(SPI->CR1 & (1 << 6)), FAIL);

    SPI->CR1 |= (1 << 6);

    return OK;
}

mcu_error_t spi_disable(void)
{
    _check(SPI->CR1 & (1 << 6), FAIL);

    SPI->CR1 &= (0 << 6);

    return OK;
}

mcu_error_t spi_send(const spi_device_t *device,
                     const spi_transaction_t type,
                     const unsigned char data)
{
    _check(device, FAIL);
    _check(SPI->CR1 & (1 << 6), FAIL);
    _check(SPI_TRANSACTION_TYPE_IS_OK(type), INVALID_ARG);

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
    SPI->SR = 0x02;
    SPI->DR = 0x00;
    SPI->CR1 = 0x00;
    SPI->CR2 = 0x00;
    SPI->ICR = 0x00;
    SPI->CRCPR = 0x07;
    SPI->RXCRCR = 0xFF;
    SPI->TXCRCR = 0xFF;
}

unsigned char spi_read(const spi_device_t* device, const unsigned char data) {
  _check(device, FAIL);
  _check(SPI->CR1 & (1 << 6), FAIL);
  
  SPI->DR = data;
  
  return SPI->DR;
}
