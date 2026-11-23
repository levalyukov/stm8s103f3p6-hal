#if defined(STM8S103F3P6_HAL)
#include <gpio.h>

void gpio_reset_pin(gpio_t* port, unsigned char pin)
{
    port->DDR &= ~(1U << pin);
    port->ODR &= ~(1U << pin);
    port->CR1 &= ~(1U << pin);
    port->CR2 &= ~(1U << pin);
}

void gpio_level_high(gpio_t* port, unsigned char pin)
{
    port->ODR |= (1U << pin);
}

void gpio_level_low(gpio_t* port, unsigned char pin)
{
    port->ODR &= ~(1U << pin);
}

void gpio_direction_set(gpio_t* port,
                        unsigned char pin,
                        unsigned char direction)
{
    if (direction == 0x1U)
    {
        port->DDR |= ((direction&0x1U) << pin);
    }
    else
    {
        port->DDR &= ~((direction&0x1U) << pin);
    }
}

void gpio_config_set(gpio_t* port,
                     unsigned char pin,
                     unsigned char cr1,
                     unsigned char cr2)
{
    if (cr1 == 0x1U)
    {
        port->CR1 |= ((cr1&0x1U) << pin);
    }
    else
    {
        port->CR1 &= ~((cr1&0x1U) << pin);
    }

    if (cr2 == 0x1U)
    {
        port->CR2 |= ((cr2&0x1U) << pin);
    }
    else
    {
        port->CR2 &= ~((cr2&0x1U) << pin);
    }
}

unsigned char gpio_level_get(const gpio_t* port, unsigned char pin)
{
    return((unsigned char)((port->IDR>>pin)&0x1U));
}

#endif /* STM8S103F3P6_HAL */
