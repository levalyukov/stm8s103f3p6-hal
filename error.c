#include "error.h"

static void error_pin_reset(void);

void error_signal_start(void)
{
    unsigned long i;
    error_pin_reset();

    GPIO_B->IDR = 0x00U;
    GPIO_B->CR1 = 0x00U;
    GPIO_B->CR2 = 0x00U;
    GPIO_B->DDR |= (1U << 5U);

    while (1)
    {
        GPIO_B->ODR ^= (1U << 5U);
        for (i = 0; i < 200000UL; i++)
        {
        };
    }
}

static void error_pin_reset(void)
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
