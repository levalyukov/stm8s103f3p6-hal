#if defined(STM8S103F3P6_HAL)
#include <spi.h>

void spi_init(const spi_config_t* config, const spi_device_t* device)
{    
    SPI->CR1 |= config->baudrate&0x38U;
    SPI->CR1 |= config->frame&0x80U;
    SPI->CR1 |= config->mode&0x04U;
    SPI->CR1 |= config->polarity&0x02U;
    SPI->CR1 |= config->phase&0x01U;
    
    if ((config->bidirection&SPI_BDM_1_LINE) == 1U)
    {
        SPI->CR2 |= config->bidirection&0x80U;
        SPI->CR2 |= config->direction&0x40U;
    }
}

void spi_enable(void)
{
    CLK->PCKENR1 |= CLK_GATING_SPI;
    SPI->CR1 |= SPI_ENABLE&0x60U;
}

void spi_disable(void)
{
    if ((SPI->SR&SPI_FLAG_BSY) == 0U)
    {
        CLK->PCKENR1 &= ~CLK_GATING_SPI;
        SPI->CR1 &= ~SPI_ENABLE;        
    }

}

void spi_write(spi_device_t* device,
               const unsigned char data,
               const unsigned char dc)
{
    if ((SPI->CR1&SPI_ENABLE) == 1U)
    {
        /* send data */
        if (dc == 0x1U)
        {
            device->port_dc->ODR |= (1U << device->pin_dc);
        }
        /* send command */
        else
        {
            device->port_dc->ODR &= ~(1U << device->pin_dc);
        }
        
        device->port_cs->ODR &= ~(1U << device->pin_cs);
        
        if (((SPI->CR2&SPI_BDM_1_LINE) == 1U) &&
            ((SPI->CR2&SPI_TRANSMIT_ONLY) == 1U))
        {
            while (((SPI->SR&SPI_FLAG_TXE) == 0U) &&
                   ((SPI->SR&SPI_FLAG_RXNE) == 0U)) {}
            SPI->DR = data;
        }
        else
        {
            while ((SPI->SR&SPI_FLAG_TXE) == 0U) {}
            SPI->DR = data;
        }
        
        device->port_cs->ODR |= (1U << device->pin_cs);
    }
}

unsigned char spi_read(void)
{
    unsigned char data = 0x00;
    if ((SPI->CR1&SPI_ENABLE) == 1U)
    {
        while((SPI->SR&SPI_FLAG_RXNE) == 0U) {};
        data = SPI->DR;
    }

    return(data);
}

void spi_deinit(void)
{
    /* When a transfer is terminated */
    if (((SPI->CR1&SPI_ENABLE) == 1U) &&
        ((SPI->SR&SPI_FLAG_BSY) == 0U))
    {
        CLK->PCKENR1 &= ~CLK_GATING_SPI;
        SPI->CR1 &= SPI_DISABLE;
        SPI->SR = 0x02U;
        SPI->DR = 0x00U;
        SPI->CR1 = 0x00U;
        SPI->CR2 = 0x00U;
        SPI->ICR = 0x00U;
        SPI->CRCPR = 0x07U;
        SPI->RXCRCR = 0xFFU;
        SPI->TXCRCR = 0xFFU;
    }
}

#endif /* STM8S103F3P6_HAL */
