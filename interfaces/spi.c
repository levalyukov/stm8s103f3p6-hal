#include "spi.h"

void spi_init(const spi_mode_t mode, const spi_baudrate_t baud,
              const spi_frame_format_t frame)
{
    CLOCK->PCKENR1 |= CLK_GATING_SPI;
    SPI->CR1 |= (unsigned char)mode & 0x04U;
    SPI->CR1 |= (unsigned char)baud & 0x38U;
    SPI->CR1 |= (unsigned char)frame & 0x80U;
    SPI->CR1 |= (1U << 6U);
}

void spi_send(const spi_device_t *device, const spi_transaction_t type,
              const unsigned char data)
{
    if (device && (SPI->SR & (unsigned char)SPI_FLAGS_TXE) != 1U &&
        (SPI->CR1 & (1U << 6U)) == 1U)
    {
        device->gpio_cs->ODR &= ~(1U << device->cs);

        if (type == SPI_TRANSACTION_DATA)
        {
            device->gpio_dc->ODR |= (1U << device->dc);
        }
        else
        {
            device->gpio_dc->ODR &= ~(1U << device->dc);
        }

        SPI->DR = data;
        device->gpio_cs->ODR |= (1U << device->cs);
    }
}

unsigned char spi_read(void)
{
    while ((SPI->SR & (unsigned char)SPI_FLAGS_RXNE) == 1U)
    {
    };
    return SPI->DR;
}

void spi_deinit(void)
{
    CLOCK->PCKENR1 &= ~CLK_GATING_SPI;
    SPI->CR1 &= ~(1U << 6U);
    SPI->SR = 0x02U;
    SPI->DR = 0x00U;
    SPI->CR1 = 0x00U;
    SPI->CR2 = 0x00U;
    SPI->ICR = 0x00U;
    SPI->CRCPR = 0x07U;
    SPI->RXCRCR = 0xFFU;
    SPI->TXCRCR = 0xFFU;
}
