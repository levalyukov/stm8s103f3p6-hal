#ifndef MCU_ERROR_H
#define MCU_ERROR_H

#include "mcu_pins_layout.h"

#define _assert(x)                                              \
    do                                                          \
    {                                                           \
        if (!(x))                                               \
            error_signal_start();                               \
    } while (0)

#define _check(y, z)                                            \
    do                                                          \
    {                                                           \
        if (!(y))                                               \
            return z;                                           \
    } while (0)

typedef enum mcu_error_codes
{
    OK,
    FAIL,
    TIMEOUT,
    INVALID_ARG,
    CRITICAL_ERROR
} mcu_error_t;

void error_signal_start(void);
static void error_pin_reset(void);

#endif /* MCU_ERROR_H */
