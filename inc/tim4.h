#if defined(STM8S103F3P6_HAL)
#if !defined(HAL_TIM4_H)
#define HAL_TIM4_H

#include <clock.h>
/* cppcheck-suppress misra-c2012-11.4 */
#define TIM4 ((volatile tim4_t*)0x005340)

#define TIM4_AUTORELOAD_ENABLE   (1U << 7U)
#define TIM4_AUTORELOAD_DISABLE ~(1U << 7U)&0xFFU
#define TIM4_ONEPULSE_ENABLE     (1U << 3U)
#define TIM4_ONEPULSE_DISABLE   ~(1U << 3U)&0xFFU
#define TIM4_COUNTER_ENABLE      (1U << 0U)
#define TIM4_COUNTER_DISABLE    ~(1U << 0U)&0xFFU

#define TIM4_UPDATE_DISABLE      (1U << 1U)
#define TIM4_UPDATE_ENABLE      ~(1U << 1U)&0xFFU
#define TIM4_UPDATE_OVERFLOW     (1U << 2U)
#define TIM4_UPDATE_ANYWAY      ~(1U << 2U)&0xFFU
#define TIM4_UPDATE_FLAG         (1U << 0U)

#define TIM4_INTERRUPT_ENABLE    (1U << 0U)
#define TIM4_INTERRUPT_DISABLE  ~(1U << 0U)&0xFFU

#define TIM4_PRESCALER_1         0x00U
#define TIM4_PRESCALER_2         0x01U
#define TIM4_PRESCALER_4         0x02U
#define TIM4_PRESCALER_8         0x03U
#define TIM4_PRESCALER_16        0x04U
#define TIM4_PRESCALER_32        0x05U
#define TIM4_PRESCALER_64        0x06U
#define TIM4_PRESCALER_128       0x07U

typedef struct
{
    volatile unsigned char CR1;  /* Control Register 1 */
    const volatile unsigned char RESERVED_1;
    const volatile unsigned char RESERVED_2;
    volatile unsigned char IER;  /* Interrupt Enable Register */
    volatile unsigned char SR;   /* Status Register */
    volatile unsigned char EGR;  /* Event Generation Register */
    volatile unsigned char CNTR; /* Counter */
    volatile unsigned char PSCR; /* Prescaler */
    volatile unsigned char ARR;  /* Auto-Reload Register */
} tim4_t;

typedef struct
{
    unsigned char autoreload_flag;
    unsigned char onepulse_flag;
    unsigned char update_flag;
    unsigned char update_source;
} tim4_config_t;

void tim4_init(tim4_config_t* config);
void tim4_enable(void);
void tim4_disable(void);
void tim4_deinit(void);

void tim4_autoreload_set(unsigned char value);
void tim4_counter_set(unsigned char value);
void tim4_prescaler_set(unsigned char value);
void tim4_interrupt(unsigned char value);

#endif /* HAL_TIM4_H */
#endif /* STM8S103F3P6_HAL */
