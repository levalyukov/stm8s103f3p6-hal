#include "gpio.h"

error_t gpio_level_set(gpio_t *gpio, const unsigned char pin,
                       const gpio_level_t level)
{
    check(GPIO_PIN_IS_OK(pin), INVALID_ARG);
    check(GPIO_LEVEL_IS_OK(level), INVALID_ARG);

    if (gpio->DDR & (1 << pin))
    {
        if (level)
            gpio->ODR |= (1 << pin);
        else
            gpio->ODR &= ~(1 << pin);
    }

    else
    {
        if (level)
            gpio->IDR |= (1 << pin);
        else
            gpio->IDR &= ~(1 << pin);
    }

    return OK;
}

error_t gpio_direction_set(gpio_t *gpio, const unsigned char pin,
                           const gpio_direction_t direction)
{
    check(GPIO_PIN_IS_OK(pin), INVALID_ARG);
    check(GPIO_DIRECTION_IS_OK(direction), INVALID_ARG);

    if (direction && !(gpio->DDR & (1 << pin)))
        gpio->DDR |= (1 << pin);
    else
        gpio->DDR &= ~(1 << pin);

    return OK;
}

error_t gpio_input_config_set(gpio_t *gpio, const unsigned char pin,
                              const gpio_input_config_t value_1,
                              const gpio_input_config_t value_2)
{
    check(GPIO_PIN_IS_OK(pin), INVALID_ARG);
    check(!(gpio->ODR & (1 << pin)), FAIL);
    check(GPIO_INPUT_CONFIG_IS_OK(value_1, value_2), FAIL);

    if (value_1)
        gpio->CR1 |= (1 << pin);
    else
        gpio->CR1 &= ~(1 << pin);

    if (value_2)
        gpio->CR2 |= (1 << pin);
    else
        gpio->CR2 &= ~(1 << pin);

    return OK;
}

error_t gpio_output_config_set(gpio_t *gpio, const unsigned char pin,
                               const gpio_output_config_t value_1,
                               const gpio_output_config_t value_2)
{
    check(GPIO_PIN_IS_OK(pin), INVALID_ARG);
    check(!(gpio->IDR & (1 << pin)), FAIL);
    check(GPIO_OUTPUT_CONFIG_IS_OK(value_1, value_2), FAIL);

    if (value_1)
        gpio->CR1 |= (1 << pin);
    else
        gpio->CR1 &= ~(1 << pin);

    if (value_2)
        gpio->CR2 |= (1 << pin);
    else
        gpio->CR2 &= ~(1 << pin);

    return OK;
}

void gpio_reset(void)
{
    gpio_t *GPIOS[6] = {GPIO_A, GPIO_B, GPIO_C, GPIO_D, GPIO_E, GPIO_F};

    char i;
    for (i = 0; i < (sizeof(GPIOS) / sizeof(GPIOS[0])); i++)
    {
        GPIOS[i]->ODR = 0x00;
        GPIOS[i]->IDR = 0x00;
        GPIOS[i]->DDR = 0x00;
        GPIOS[i]->CR1 = 0x00;
        GPIOS[i]->CR2 = 0x00;
    }
}
