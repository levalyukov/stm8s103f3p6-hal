#ifndef UART_H
#define UART_H

#include "error.h"

#define UART ((uart_t *)0x005230)
#define UART_TRANSMIT_IS_OK(type)                                         \
    (((type) == UART_DATA_TRANSMITTER) ||                                 \
     ((type) == UART_DATA_RECEIVER) || ((type) == UART_DATA_DUPLEX))
#define UART_PARITY_IS_OK(parity)                                         \
    (((parity) == UART_PARITY_DISABLE) || ((parity) == UART_PARITY_ENABLE))

typedef struct uart
{
    volatile unsigned char SR;   /* Status Register */
    volatile unsigned char DR;   /* Data Register */
    volatile unsigned char BRR1; /* Baud Rate Register 1 */
    volatile unsigned char BRR2; /* Baud Rate Register 2 */
    volatile unsigned char CR1;  /* Control Register 1 */
    volatile unsigned char CR2;  /* Control Register 2 */
    volatile unsigned char CR3;  /* Control Register 3 */
    volatile unsigned char CR4;  /* Control Register 4 */
    volatile unsigned char CR5;  /* Control Register 5 */
    volatile unsigned char GTR;  /* Guard Time Register */
    volatile unsigned char PSCR; /* Prescaler Register */
} uart_t;

typedef enum uart_transmit
{
    UART_DATA_TRANSMITTER,
    UART_DATA_RECEIVER,
    UART_DATA_DUPLEX
} uart_transmit_t;

typedef enum uart_parity_control
{
    UART_PARITY_DISABLE = (unsigned char)0x00,
    UART_PARITY_ENABLE = (unsigned char)0x02
} uart_parity_control_t;

error_t uart_init(const uart_parity_control_t parity);
error_t uart_enable(void);
error_t uart_send(unsigned char data, uart_transmit_t type);
unsigned char uart_read(void);
error_t uart_disable(void);
void uart_deinit(void);

#endif /* UART_H */
