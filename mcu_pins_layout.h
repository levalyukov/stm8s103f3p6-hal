#ifndef MCU_PINS_H
#define MCU_PINS_H

/* cppcheck-suppress-begin misra-c2012-11.4 */
#define GPIO_A (volatile gpio_t *)0x005000U
#define GPIO_B (volatile gpio_t *)0x005005U
#define GPIO_C (volatile gpio_t *)0x00500AU
#define GPIO_D (volatile gpio_t *)0x00500FU
#define GPIO_E (volatile gpio_t *)0x005014U
#define GPIO_F (volatile gpio_t *)0x005019U
/* cppcheck-suppress-end misra-c2012-11.4 */

typedef struct
{
    volatile unsigned char ODR; /* Output Data Register */
    volatile unsigned char IDR; /* Input Data Register */
    volatile unsigned char DDR; /* Direction Data Register */
    volatile unsigned char CR1; /* Control Register 1 */
    volatile unsigned char CR2; /* Control Register 2 */
} gpio_t;

#endif /* MCU_PINS_LAYOUT_H */
