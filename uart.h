#ifndef UART_H
#define UART_H

#include "error.h"

#define UART ((uart_t *)0x005230)

#define UART_TRANSMIT_IS_OK(type)                                         \
    (((type) == UART_DATA_TRANSMITTER) ||                                 \
     ((type) == UART_DATA_RECEIVER) || ((type) == UART_DATA_DUPLEX))

#define UART_BAUD_IS_OK(baud)                                             \
    (((baud) == UART_BAUDRATE_2400) || ((baud) == UART_BAUDRATE_9600) ||  \
     ((baud) == UART_BAUDRATE_19200) ||                                   \
     ((baud) == UART_BAUDRATE_57600) ||                                   \
     ((baud) == UART_BAUDRATE_115200) ||                                  \
     ((baud) == UART_BAUDRATE_230400) ||                                  \
     ((baud) == UART_BAUDRATE_460800))

#define UART_WORD_IS_OK(word)                                             \
    (((word) == UART_DATA_SIZE_8_BITS) ||                                 \
     ((word) == UART_DATA_SIZE_9_BITS))

#define UART_PARITY_IS_OK(parity)                                         \
    (((parity) == UART_PARITY_DISABLE) || ((parity) == UART_PARITY_ENABLE))

#define UART_PARITY_SELECTION_IS_OK(selection)                            \
    (((selection) == UART_PARITY_SELECTION_ODD) ||                        \
     ((selection) == UART_PARITY_SELECTION_EVEN))

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

typedef enum uart_flags
{
    UART_FLAG_TXE = (unsigned char)0x80,  /* Data is transferred  */
    UART_FLAG_TC = (unsigned char)0x40,   /* Transmission is complete */
    UART_FLAG_RXNE = (unsigned char)0x20, /* Received ready to read */
    UART_FLAG_IDLE = (unsigned char)0x10, /* Idle line is detected */
    UART_FLAG_OR = (unsigned char)0x08,   /* Overrune / LIN slave error */
    UART_FLAG_NF = (unsigned char)0x04,   /* Noise is detected */
    UART_FLAG_FE = (unsigned char)0x02,   /* Framing error */
    UART_FLAG_PE = (unsigned char)0x01    /* Parity error  */
} uart_flags_t;

typedef enum uart_transmit
{
    UART_DATA_TRANSMITTER,
    UART_DATA_RECEIVER,
    UART_DATA_DUPLEX
} uart_transmit_t;

typedef enum uart_baud_rate
{
    UART_BAUDRATE_2400 = (unsigned char)0x1047,
    UART_BAUDRATE_9600 = (unsigned char)0x0412,
    UART_BAUDRATE_19200 = (unsigned char)0x0209,
    UART_BAUDRATE_57600 = (unsigned char)0x00AE,
    UART_BAUDRATE_115200 = (unsigned char)0x0057,
    UART_BAUDRATE_230400 = (unsigned char)0x002B,
    UART_BAUDRATE_460800 = (unsigned char)0x0016
} uart_baud_rate_t;

typedef enum uart_data_size
{
    UART_DATA_SIZE_8_BITS = (unsigned char)0x00,
    UART_DATA_SIZE_9_BITS = (unsigned char)0x10
} uart_data_size_t;

typedef enum uart_parity
{
    UART_PARITY_DISABLE = (unsigned char)0x00,
    UART_PARITY_ENABLE = (unsigned char)0x02
} uart_parity_t;

typedef enum uart_selection
{
    UART_PARITY_SELECTION_ODD = (unsigned char)0x01,
    UART_PARITY_SELECTION_EVEN = (unsigned char)0x00
} uart_selection_t;

error_t uart_init(uart_baud_rate_t baud_rate, uart_data_size_t word_length,
                  uart_parity_t parity, uart_selection_t selection);
error_t uart_enable(void);
error_t uart_send(unsigned char data);
unsigned char uart_read(void);
error_t uart_disable(void);
void uart_deinit(void);

#endif /* UART_H */
