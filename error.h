#ifndef ERROR_H
#define ERROR_H

#include "mcu_pins_layout.h"

#define assert(x)                                                         \
    do                                                                    \
    {                                                                     \
        if (!(x))                                                         \
            error_signal_start();                                         \
    } while (0)

#define check(y, z)                                                       \
    do                                                                    \
    {                                                                     \
        if (!(y))                                                         \
            return z;                                                     \
    } while (0)

typedef enum error_codes
{
    OK,
    FAIL,
    TIMEOUT,
    INVALID_ARG,
    CRITICAL_ERROR
} error_t;

void error_signal_start(void);
static void error_pin_reset(void);

#endif /* ERROR_H */
