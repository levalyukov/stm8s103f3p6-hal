#include "spi.h"

error_t spi_init(const spi_mode_t mode, const spi_baudrate_t baud,
                 const spi_frame_format_t frame)
{
    error_t status = OK;

    if (((SPI->CR1 & (1U << 6U)) == 1U) || !SPI_MODE_IS_OK(mode) ||
        !SPI_BAUD_IS_OK(baud) || !SPI_FRAME_FORMAT_IS_OK(frame))
    {
        status = INVALID_ARG;
    }

    if (status == OK)
    {
        CLOCK->PCKENR1 |= CLK_GATING_SPI;
        SPI->CR1 |= mode;
        SPI->CR1 |= baud;
        SPI->CR1 |= frame;
    }

    return status;
}

error_t spi_enable(void)
{
    error_t status = OK;
    if ((SPI->CR1 & (1U << 6U)) != 1U)
    {
        SPI->CR1 |= (1U << 6U);
    }
    else
    {
        status = INVALID_ARG;
    }

    return status;
}

error_t spi_disable(void)
{
    error_t status = OK;
    if ((SPI->CR1 & (1U << 6U)) == 1U)
    {
        SPI->CR1 &= ~(1U << 6U);
    }
    else
    {
        status = INVALID_ARG;
    }

    return status;
}

error_t spi_send(const spi_device_t *device, const spi_transaction_t type,
                 const unsigned char data)
{
    error_t status = OK;
    if (!device || (SPI->CR1 & (1U << 6U)) != 1U ||
        !SPI_TRANSACTION_TYPE_IS_OK(type) ||
        (SPI->SR & (unsigned char)SPI_FLAG_BSY) != 0U)
    {
        status = INVALID_ARG;
    }

    if (status == OK)
    {
        (device->gpio_cs)->ODR &= ~(1U << device->cs);
        if (type == SPI_TRANSACTION_DATA)
        {
            (device->gpio_dc)->ODR |= (1U << device->dc);
        }
        else
        {
            (device->gpio_dc)->ODR &= ~(1U << device->dc);
        }

        SPI->DR = data;
        (device->gpio_cs)->ODR |= (1U << device->cs);
    }

    return status;
}

void spi_deinit(void)
{
    SPI->SR = 0x02U;
    SPI->DR = 0x00U;
    SPI->CR1 = 0x00U;
    SPI->CR2 = 0x00U;
    SPI->ICR = 0x00U;
    SPI->CRCPR = 0x07U;
    SPI->RXCRCR = 0xFFU;
    SPI->TXCRCR = 0xFFU;
}

unsigned char spi_read(void)
{
    unsigned char data = 0x00U;
    if ((SPI->CR1 & (1U << 6U)) != 0U)
    {
        data = SPI->DR;
    }

    return data;
}
