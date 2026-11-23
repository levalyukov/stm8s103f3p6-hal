#if defined(STM8S103F3P6_HAL)
#if !defined(HAL_CLOCK_H)
#define HAL_CLOCK_H

/* cppcheck-suppress misra-c2012-11.4 */
#define CLK ((volatile clock_t *)0x0050C0)

typedef struct
{
    volatile unsigned char ICKR;     /* Internal Clock Control */
    volatile unsigned char ECKR;     /* External Clock Control */
    const volatile unsigned char RESERVED; /* Reserved 1 byte */
    volatile unsigned char CMSR      /* Clock Master Status */;
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

#define CLK_GATING_TIM1   (1U << 7U)
#define CLK_GATING_TIM2   (1U << 5U)
#define CLK_GATING_TIM4   (1U << 4U)
#define CLK_GATING_UART1  (1U << 3U)
#define CLK_GATING_SPI    (1U << 1U)
#define CLK_GATING_I2C    (1U << 0U)
/* PCKENR2 */
#define CLK_GATING_ADC    (1U << 3U)
#define CLK_GATING_AWU    (1U << 2U)

#define CLK_GATING_ALL    0xFFU
#define CLK_GATING_NONE  ~CLK_GATING_ALL



#endif /* HAL_CLOCK_H */
#endif /* STM8S103F3P6_HAL */
