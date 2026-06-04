#include "error.h"

void error_signal_start(void)
{
    error_pin_reset();

    GPIO_B->IDR = 0x00;
    GPIO_B->CR1 = 0x00;
    GPIO_B->CR2 = 0x00;
    GPIO_B->DDR |= (1 << 5);

    while (1)
    {
        GPIO_B->ODR |= (1 << 5);
        {
            unsigned long i;
            for (i = 0; i < 200000; i++)
                ;
        }
        GPIO_B->ODR &= ~(1 << 5);
        {
            unsigned long i;
            for (i = 0; i < 200000; i++)
                ;
        }
    }
}

static void error_pin_reset(void)
{
    gpio_t *GPIOS[6] = {GPIO_A, GPIO_B, GPIO_C, GPIO_D, GPIO_E, GPIO_F};

    {
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
}
