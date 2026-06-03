#ifndef MCU_PINS_LAYOUT_H
#define MCU_PINS_LAYOUT_H

#define GPIO_A ((gpio_t *)0x005000)
#define GPIO_B ((gpio_t *)0x005005)
#define GPIO_C ((gpio_t *)0x00500A)
#define GPIO_D ((gpio_t *)0x00500F)
#define GPIO_E ((gpio_t *)0x005014)
#define GPIO_F ((gpio_t *)0x005019)

typedef struct gpio
{
    volatile unsigned char ODR; /* Output Data Register */
    volatile unsigned char IDR; /* Input Data Register */
    volatile unsigned char DDR; /* Direction Data Register */
    volatile unsigned char CR1; /* Control Register 1 */
    volatile unsigned char CR2; /* Control Register 2 */
} gpio_t;

#endif /* MCU_PINS_LAYOUT_H */
