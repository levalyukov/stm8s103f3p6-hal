#ifndef CLOCK_H
#define CLOCK_H

#include "error.h"

#define CLOCK ((clock_t *)0x0050C0)

#define CLK_PERIPHERAL_IS_OK(peripheral)                                  \
    (((peripheral) == CLK_GATING_TIM1) ||                                 \
     ((peripheral) == CLK_GATING_TIM3) ||                                 \
     ((peripheral) == CLK_GATING_TIM2_TIM5) ||                            \
     ((peripheral) == CLK_GATING_TIM4_TIM6) ||                            \
     ((peripheral) == CLK_GATING_UART1) ||                                \
     ((peripheral) == CLK_GATING_SPI) ||                                  \
     ((peripheral) == CLK_GATING_I2C) ||                                  \
     ((peripheral) == CLK_GATING_CAN) ||                                  \
     ((peripheral) == CLK_GATING_ADC) ||                                  \
     ((peripheral) == CLK_GATING_AWU) ||                                  \
     ((peripheral) == CLK_GATING_ALL))

#define CLK_CPU_PRESCALER_IS_OK(cpu)                                      \
    (((cpu) == CLK_CPU_PRESCALER_NONE) ||                                 \
     ((cpu) == CLK_CPU_PRESCALER_2) || ((cpu) == CLK_CPU_PRESCALER_4) ||  \
     ((cpu) == CLK_CPU_PRESCALER_8) || ((cpu) == CLK_CPU_PRESCALER_16) || \
     ((cpu) == CLK_CPU_PRESCALER_32) ||                                   \
     ((cpu) == CLK_CPU_PRESCALER_64) || ((cpu) == CLK_CPU_PRESCALER_128))

#define CLK_INTERNAL_PRESCALER_IS_OK(internal)                            \
    (((internal) == CLK_INTERNAL_PRESCALER_NONE) ||                       \
     ((internal) == CLK_INTERNAL_PRESCALER_2) ||                          \
     ((internal) == CLK_INTERNAL_PRESCALER_4) ||                          \
     ((internal) == CLK_INTERNAL_PRESCALER_8))

typedef struct clock
{
    volatile unsigned char ICKR; /* Internal Clock Control */
    volatile unsigned char ECKR; /* External Clock Control */
    unsigned char RESERVED;      /* Reserved 1 byte */
    volatile unsigned char CMSR /* Clock Master Status */;
    volatile unsigned char SWR;      /* Clock Master Switch */
    volatile unsigned char SWCR;     /* Switch Control  */
    volatile unsigned char CKDIVR;   /* Clock Divider */
    volatile unsigned char PCKENR1;  /* Peripheral Clock Gating 1 */
    volatile unsigned char CSSR;     /* Clock Security System */
    volatile unsigned char CCOR;     /* Configurable Clock Control */
    volatile unsigned char PCKENR2;  /* Peripheral Clock Gating 2 */
    volatile unsigned char CANCCR;   /* CAN Clock Control */
    volatile unsigned char HSITRIMR; /* HSI Clock Calibration Trimming */
    volatile unsigned char SWIMCCR;  /* SWIM Clock Control */
} clock_t;

typedef enum clock_peripheral
{
    CLK_GATING_TIM1 = (unsigned char)0x80,
    CLK_GATING_TIM3 = (unsigned char)0x40,
    CLK_GATING_TIM2_TIM5 = (unsigned char)0x20,
    CLK_GATING_TIM4_TIM6 = (unsigned char)0x10,
    CLK_GATING_UART1 = (unsigned char)0x02,
    CLK_GATING_SPI = (unsigned char)0x02,
    CLK_GATING_I2C = (unsigned char)0x01,
    CLK_GATING_CAN = (unsigned char)0x80,
    CLK_GATING_ADC = (unsigned char)0x08,
    CLK_GATING_AWU = (unsigned char)0x04,
    CLK_GATING_ALL = (unsigned char)0xFF
} clock_peripheral_t;

typedef enum clock_cpu_prescaler
{
    CLK_CPU_PRESCALER_NONE = (unsigned char)0x00,
    CLK_CPU_PRESCALER_2 = (unsigned char)0x01,
    CLK_CPU_PRESCALER_4 = (unsigned char)0x02,
    CLK_CPU_PRESCALER_8 = (unsigned char)0x03,
    CLK_CPU_PRESCALER_16 = (unsigned char)0x04,
    CLK_CPU_PRESCALER_32 = (unsigned char)0x05,
    CLK_CPU_PRESCALER_64 = (unsigned char)0x06,
    CLK_CPU_PRESCALER_128 = (unsigned char)0x07
} clock_cpu_prescaler_t;

typedef enum clock_resonator_prescaler
{
    CLK_INTERNAL_PRESCALER_NONE,
    CLK_INTERNAL_PRESCALER_2 = (unsigned char)0x08,
    CLK_INTERNAL_PRESCALER_4 = (unsigned char)0x10,
    CLK_INTERNAL_PRESCALER_8 = (unsigned char)0x18
} clock_internal_prescaler_t;

error_t clock_divider_set(clock_cpu_prescaler_t cpu,
                          clock_internal_prescaler_t internal);
error_t clock_peripheral_set(clock_peripheral_t peripheral);
void clock_deinit(void);

#endif /* CLOCK_H */
