#if defined(STM8S103F3P6_HAL)
#include <tim4.h>

void tim4_init(const tim4_config_t* config)
{
    CLK->PCKENR1 |= CLK_GATING_TIM4;
    TIM4->CR1 |= config->onepulse_flag&0x08U;
    TIM4->CR1 |= config->autoreload_flag&0x80U;
    TIM4->CR1 |= config->update_source&0x04U;
    TIM4->CR1 |= config->update_flag&0x02U;
    TIM4->CR1 &= ~112;
    TIM4->EGR = 0x01U; /* force update the shadow registers */
}

void tim4_enable(void)
{
    TIM4->CR1 |= TIM4_COUNTER_ENABLE;
}

void tim4_disable(void)
{
    TIM4->CR1 &= TIM4_COUNTER_DISABLE;
}

void tim4_deinit(void)
{
    TIM4->CR1 = 0x00U;
    TIM4->IER = 0x00U;
    TIM4->SR = 0x00U;
    TIM4->EGR = 0x00U;
    TIM4->CNTR = 0x00U;
    TIM4->PSCR = 0x00U;
    TIM4->ARR = 0xFFU;
    CLK->PCKENR1 &= ~CLK_GATING_TIM4;
}


void tim4_autoreload_set(const unsigned char value)
{
    TIM4->ARR = (value > 0U) ? (value) : 0x1U;
}

void tim4_counter_set(const unsigned char value)
{
    TIM4->CNTR = value;
}

void tim4_prescaler_set(const unsigned char value)
{
    TIM4->PSCR = value&0x07U;
}

void tim4_interrupt(const unsigned char value)
{
    TIM4->IER = value;
    
}

#endif /* STM8S103F3P6_HAL */
