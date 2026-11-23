#include <gpio.h>

void _delay(volatile unsigned int t)
{
    while (--t)
    {
        __asm__("nop");
    }
}


void main(void)
{
    
    gpio_direction_set(GPIO_B,5, 1);
    gpio_config_set(GPIO_B,5,1,0);
    
    while (1)
    {
        gpio_level_high(GPIO_B, 5);
        _delay(1000000000);
        gpio_level_low(GPIO_B, 5);
        _delay(1000000000);
    }
}
