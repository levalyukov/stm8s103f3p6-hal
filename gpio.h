#ifndef GPIO_H
#define GPIO_H

#include "error.h"
#include "mcu_pins_layout.h"

#define GPIO_PIN_IS_OK(pin) (((pin) < 8) ? 1 : 0)
#define GPIO_LEVEL_IS_OK(level) (((level) == LOW) || ((level) == HIGH))
#define GPIO_DIRECTION_IS_OK(direction)                                   \
    (((direction) == INPUT) || ((direction) == OUTPUT))
#define GPIO_INPUT_CONFIG_IS_OK(z, o)                                     \
    ((((z) == PULLUP_OFF) || ((z) == PULLUP_ON)) &&                       \
     (((o) == EXTERNAL_INTERRPUT_ON) || ((o) == EXTERNAL_INTERRPUT_OFF)))

#define GPIO_OUTPUT_CONFIG_IS_OK(v, x)                                    \
    ((((v) == OPEN_DRAIN) || ((v) == PUSH_PULL)) &&                       \
     (((x) == LOW_SPEED) || ((x) == HIGH_SPEED)))

typedef enum
{
    INPUT,
    OUTPUT
} gpio_direction_t;

typedef enum gpio_level
{
    LOW,
    HIGH
} gpio_level_t;

typedef enum
{
    PULLUP_OFF = 0,
    PULLUP_ON = 1,
    EXTERNAL_INTERRPUT_OFF = 0,
    EXTERNAL_INTERRPUT_ON = 1
} gpio_input_config_t;

typedef enum
{
    OPEN_DRAIN = 0,
    PUSH_PULL = 1,
    LOW_SPEED = 0,
    HIGH_SPEED = 1
} gpio_output_config_t;

error_t gpio_level_set(gpio_t *gpio, unsigned char pin,
                       gpio_level_t level);
error_t gpio_direction_set(gpio_t *gpio, unsigned char pin,
                           gpio_direction_t direction);
error_t gpio_input_config_set(gpio_t *gpio, unsigned char pin,
                              gpio_input_config_t value_1,
                              gpio_input_config_t value_2);
error_t gpio_output_config_set(gpio_t *gpio, unsigned char pin,
                               gpio_output_config_t value_1,
                               gpio_output_config_t value_2);
void gpio_reset(void);

#endif /* GPIO_H */
