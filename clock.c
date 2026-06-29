#include "clock.h"

error_t clock_cpu_frequency_set(const clock_cpu_prescaler_t cpu)
{
  check(CLK_CPU_PRESCALER_IS_OK(cpu), INVALID_ARG);

  if (cpu == CLK_CPU_PRESCALER_NONE)
    CLOCK->CKDIVR |= ~((1 << 2) | (1 << 1) | (1 << 0));
  else
    CLOCK->CKDIVR |= cpu;
  
  return OK;
}

error_t clock_hsi_set(const clock_hsi_t internal)
{
  check(CLK_HSI_IS_OK(internal), INVALID_ARG);

  if (internal == CLK_HSI_NONE)
    CLOCK->CKDIVR |= ~((1 << 4) | (1 << 3));
  else
    CLOCK->CKDIVR |= internal;

  return OK;
}

error_t clock_peripheral_set(const clock_peripheral_t peripheral)
{
    check(CLK_PERIPHERAL_IS_OK(peripheral), INVALID_ARG);

    if (peripheral == CLK_GATING_NONE)
      {
	CLOCK->PCKENR1 = CLK_GATING_NONE;
	CLOCK->PCKENR2 = CLK_GATING_NONE;
	return OK;
      }
    
    if ((peripheral != CLK_GATING_CAN)
	|| (peripheral != CLK_GATING_ADC)
	|| (peripheral != CLK_GATING_AWU))
        CLOCK->PCKENR1 |= peripheral;

    else
        CLOCK->PCKENR2 |= peripheral;

    return OK;
}

void clock_deinit(void)
{
    CLOCK->ICKR = (unsigned char)0x01;
    CLOCK->ECKR = (unsigned char)0x00;
    CLOCK->CMSR = (unsigned char)0xE1;
    CLOCK->SWR = (unsigned char)0xE1;
    CLOCK->SWCR = (unsigned char)0x00; /* in datasheet written 0xXX */
    CLOCK->CKDIVR = (unsigned char)0x18;
    CLOCK->PCKENR1 = (unsigned char)0xFF;
    CLOCK->CSSR = (unsigned char)0x00;
    CLOCK->CCOR = (unsigned char)0x00;
    CLOCK->PCKENR2 = (unsigned char)0xFF;
    CLOCK->CANCCR = (unsigned char)0x00;
    CLOCK->HSITRIMR = (unsigned char)0x00;
    CLOCK->SWIMCCR = (unsigned char)0x00;
}
