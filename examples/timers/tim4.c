#include <gpio.h>
#include <tim4.h>

void main(void)
{
    tim4_config_t config = {
        .autoreload_flag = TIM4_AUTORELOAD_ENABLE,
        .onepulse_flag   = TIM4_ONEPULSE_DISABLE,
        .update_flag     = TIM4_UPDATE_ENABLE,
        .update_source   = TIM4_UPDATE_OVERFLOW
    };

    gpio_direction_set(GPIO_B, 5, GPIO_OUTPUT);
    gpio_config_set(GPIO_B, 5, GPIO_PUSH_PULL, GPIO_LOW_SPEED);
    gpio_level_low(GPIO_B, 5);

    __asm__("rim");
    tim4_init(&config);
    tim4_autoreload_set(250);
    tim4_prescaler_set(TIM4_PRESCALER_16);
    tim4_interrupt(TIM4_INTERRUPT_ENABLE);
    tim4_enable();
    while (1) {}
}

void _tim4_interrupt_blink(void) __interrupt(23)
{
    static volatile unsigned int ticks;

    if (++ticks >= 500)
    {
        GPIO_B->ODR ^= (1U << 5U);
        ticks = 0;
    }

    TIM4->SR = 0x00;
}
