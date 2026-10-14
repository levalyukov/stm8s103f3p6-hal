#ifndef UART_H
#define UART_H

#include <power/clock.h>
/* cppcheck-suppress misra-c2012-11.4 */
#define UART ((volatile uart_t *)0x005230)

typedef struct
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

typedef enum
{
    UART_FLAG_TXE = (unsigned char)0x80,  /* Data is transferred  */
    UART_FLAG_TC = (unsigned char)0x40,   /* Transmission is complete */
    UART_FLAG_RXNE = (unsigned char)0x20, /* Received ready to read */
    UART_FLAG_IDLE = (unsigned char)0x10, /* Idle line is detected */
    UART_FLAG_OR = (unsigned char)0x08,   /* Overrune / LIN
                                             slave error */
    UART_FLAG_NF = (unsigned char)0x04,   /* Noise is detected */
    UART_FLAG_FE = (unsigned char)0x02,   /* Framing error */
    UART_FLAG_PE = (unsigned char)0x01    /* Parity error  */
} uart_flags_t;

typedef enum
{
    UART_DATA_TRANSMITTER,
    UART_DATA_RECEIVER,
    UART_DATA_DUPLEX
} uart_transmit_t;

typedef enum
{
    UART_BAUDRATE_2400 = 0x1A0B,
    UART_BAUDRATE_9600 = 0x0693,
    UART_BAUDRATE_19200 = 0x0341,
    UART_BAUDRATE_57600 = 0x0116,
    UART_BAUDRATE_115200 = 0x008B,
    UART_BAUDRATE_230400 = 0x0045,
    UART_BAUDRATE_460800 = 0x0023,
    UART_BAUDRATE_921600 = 0x0011
} uart_baudrate_t;

typedef enum
{
    UART_DATA_SIZE_8_BITS = 0x00U,
    UART_DATA_SIZE_9_BITS = 0x10U
} uart_data_size_t;

typedef enum
{
    UART_PARITY_DISABLE = 0x00U,
    UART_PARITY_ENABLE = 0x02U
} uart_parity_t;

typedef enum
{
    UART_PARITY_SELECTION_ODD = 0x01U,
    UART_PARITY_SELECTION_EVEN = 0x00U
} uart_selection_t;

typedef enum
{
    UART_MODE_RECEIVER,
    UART_MODE_TRANSMITTER,
    UART_MODE_FULLDUPLEX,
    UART_MODE_NONE
} uart_mode_t;

typedef enum
{
    UART_STOPBIT_1,
    UART_STOPBIT_2,
    UART_STOPBIT_1_5,
    UART_STOPBIT_RESERVED
} uart_stopbit_t;

void uart_init(unsigned short baudrate, uart_data_size_t word_length,
               uart_parity_t parity, uart_selection_t selection,
               uart_stopbit_t stopbit);
void uart_send(unsigned char data);
unsigned char uart_read(void);
void uart_enable(void);
void uart_disable(void);
void uart_deinit(void);
void uart_mode_set(uart_mode_t mode);

#endif /* UART_H */
