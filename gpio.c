#include "gpio.h"

error_t gpio_level_set(gpio_t *gpio, const unsigned char pin,
                       const gpio_level_t level)
{
    error_t status = OK;

    if (!GPIO_PIN_IS_OK(pin) || !GPIO_LEVEL_IS_OK(level))
    {
        status = INVALID_ARG;
    }

    if ((gpio->DDR & (1U << pin)) != 0U)
    {
        if (level == HIGH)
        {
            gpio->ODR |= (1U << pin);
        }
        else
        {
            gpio->ODR &= ~(1U << pin);
        }
    }

    else
    {
        if (level == HIGH)
        {
            gpio->IDR |= (1U << pin);
        }
        else
        {
            gpio->IDR &= ~(1U << pin);
        }
    }

    return status;
}

error_t gpio_direction_set(gpio_t *gpio, const unsigned char pin,
                           const gpio_direction_t direction)
{
    error_t status = OK;

    if (!GPIO_PIN_IS_OK(pin) || !GPIO_DIRECTION_IS_OK(direction))
    {
        status = INVALID_ARG;
    }

    if (direction && !(gpio->DDR & (1U << pin)))
    {
        gpio->DDR |= (1U << pin);
    }
    else
    {
        gpio->DDR &= ~(1U << pin);
    }

    return status;
}

error_t gpio_input_config_set(gpio_t *gpio, const unsigned char pin,
                              const gpio_input_config_t value_1,
                              const gpio_input_config_t value_2)
{
    error_t status = OK;

    if (!GPIO_PIN_IS_OK(pin) ||
        !GPIO_INPUT_CONFIG_IS_OK(value_1, value_2) ||
        (gpio->ODR & (1U << pin)) != 0U)
    {
        status = INVALID_ARG;
    }

    if (value_1 == PULLUP_ON)
    {
        gpio->CR1 |= (1U << pin);
    }
    else
    {
        gpio->CR1 &= ~(1U << pin);
    }

    if (value_2 == EXTERNAL_INTERRPUT_ON)
    {
        gpio->CR2 |= (1U << pin);
    }
    else
    {
        gpio->CR2 &= ~(1U << pin);
    }

    return status;
}

error_t gpio_output_config_set(gpio_t *gpio, const unsigned char pin,
                               const gpio_output_config_t value_1,
                               const gpio_output_config_t value_2)
{
    error_t status = OK;

    if (!GPIO_PIN_IS_OK(pin) ||
        GPIO_OUTPUT_CONFIG_IS_OK(value_1, value_2) ||
        (gpio->IDR & (1U << pin)) != 0U)
    {
        status = INVALID_ARG;
    }

    if (value_1 == PUSH_PULL)
    {
        gpio->CR1 |= (1U << pin);
    }
    else
    {
        gpio->CR1 &= ~(1U << pin);
    }

    if (value_2 == HIGH_SPEED)
    {
        gpio->CR2 |= (1U << pin);
    }
    else
    {
        gpio->CR2 &= ~(1U << pin);
    }

    return status;
}

void gpio_reset(void)
{
    gpio_t *GPIOS[6] = {GPIO_A, GPIO_B, GPIO_C, GPIO_D, GPIO_E, GPIO_F};

    unsigned char i;
    for (i = 0; i < (unsigned char)(sizeof(GPIOS) / sizeof(GPIOS[0])); i++)
    {
        GPIOS[i]->ODR = 0x00;
        GPIOS[i]->IDR = 0x00;
        GPIOS[i]->DDR = 0x00;
        GPIOS[i]->CR1 = 0x00;
        GPIOS[i]->CR2 = 0x00;
    }
}
