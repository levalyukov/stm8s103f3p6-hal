#include "spi.h"

error_t spi_init(const spi_mode_t mode, const spi_baudrate_t baud,
                 const spi_frame_format_t frame)
{
    check(!(SPI->CR1 & (1 << 6)), FAIL);
    check(SPI_MODE_IS_OK(mode), INVALID_ARG);
    check(SPI_BAUD_IS_OK(baud), INVALID_ARG);
    check(SPI_FRAME_FORMAT_IS_OK(frame), INVALID_ARG);

    CLOCK->PCKENR1 |= CLK_GATING_SPI;
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
    SPI->CR1 &= ~(1 << 6);
    return OK;
}

error_t spi_send(const spi_device_t *device,
		 const spi_transaction_t type,
                 const unsigned char data)
{
    check(device, FAIL);
    check(SPI->CR1 & (1 << 6), FAIL); /* if disabled */
    check(SPI_TRANSACTION_TYPE_IS_OK(type), INVALID_ARG);
    check(!(SPI->SR & (1 << 7)), FAIL); /* if busy */
    
    (device->gpio_cs)->ODR &= ~(1 << device->cs);
    if (type)
      (device->gpio_dc)->ODR |= (1 << device->dc);
    else
      (device->gpio_dc)->ODR &= ~(1 << device->dc);

    SPI->DR = data;
    (device->gpio_cs)->ODR |= (1 << device->cs);

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

unsigned char spi_read(void)
{
  check(SPI->CR1 & (1 << 6), 0x00); /* if disabled */
  return SPI->DR;
}
