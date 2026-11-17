#if defined(STM8S103F3P6_HAL)
#if !defined(HAL_GPIO_H)
#define HAL_GPIO_H

/* cppcheck-suppress-begin misra-c2012-11.4 */
#define GPIO_A ((volatile gpio_t *)0x005000)
#define GPIO_B ((volatile gpio_t *)0x005005)
#define GPIO_C ((volatile gpio_t *)0x00500A)
#define GPIO_D ((volatile gpio_t *)0x00500F)
/* cppcheck-suppress-end misra-c2012-11.4 */

typedef struct
{
    volatile unsigned char ODR;       /* Output Data Register */
    const volatile unsigned char IDR; /* Input Data Register */
    volatile unsigned char DDR;       /* Direction Data Register */
    volatile unsigned char CR1;       /* Control Register 1 */
    volatile unsigned char CR2;       /* Control Register 2 */
} gpio_t;

void gpio_reset_pin(gpio_t* port, unsigned char pin);
void gpio_level_set(gpio_t* port, unsigned char pin, unsigned char level);
void gpio_direction_set(gpio_t* port, unsigned char pin, unsigned char direction);
void gpio_config_set(gpio_t* port, unsigned char pin, unsigned char cr1, unsigned char cr2);
unsigned char gpio_level_get(gpio_t* port, unsigned char pin);

#endif /* HAL_GPIO_H */
#endif /* STM8S103F3P6_HAL */
