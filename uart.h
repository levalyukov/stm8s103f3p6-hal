#ifndef UART_H
#define UART_H

#define UART ((uart_t *)0x005230)

typedef struct uart
{
    volatile unsigned char SR;   /* Status Register */
    volatile unsigned char DR;   /* Data Register */
    volatile unsigned char BRR1; /* Baud Rate Register 1 */
    volatile unsigned char BBR2; /* Baud Rate Register 2 */
    volatile unsigned char CR1;  /* Control Register 1 */
    volatile unsigned char CR2;  /* Control Register 2 */
    volatile unsigned char CR3;  /* Control Register 3 */
    volatile unsigned char CR4;  /* Control Register 4 */
    volatile unsigned char CR5;  /* Control Register 5 */
    volatile unsigned char GTR;  /* Guard Time Register */
    volatile unsigned char PSCR; /* Prescaler Register */
} uart_t

#endif /* UART_H */
