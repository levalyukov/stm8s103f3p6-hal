#include "clock.h"

void clock_reset(void)
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
