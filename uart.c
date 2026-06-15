#include "uart.h"

error_t uart_init(const uart_baud_rate_t baudrate,
                  const uart_data_size_t word_length,
                  const uart_parity_t parity,
                  const uart_selection_t selection)
{
    check(UART_BAUD_IS_OK(baudrate), INVALID_ARG);
    check(UART_WORD_IS_OK(word_length), INVALID_ARG);
    check(UART_PARITY_IS_OK(parity), INVALID_ARG);
    check(UART_PARITY_SELECTION_IS_OK(selection), INVALID_ARG);

    UART->BRR1 = baudrate;
    UART->CR1 |= parity;
    UART->CR1 |= word_length;

    if (!(UART->CR3 & (1 << 6)))
    {
        UART->CR1 |= parity;
        UART->CR1 |= selection;
    }

    return OK;
}

error_t uart_enable(void)
{
    check(UART->CR1 & (1 << 5), FAIL);
    UART->CR1 &= (0 << 5);
    return OK;
}

error_t uart_disable(void)
{
    check(!(UART->CR1 & (1 << 5)), FAIL);
    UART->CR1 |= (1 << 5);
    return OK;
}

error_t uart_send(const unsigned char data)
{
    check(!(UART->CR1 & (1 << 5)), FAIL);  /* if uart disabled */
    check(UART->SR & UART_FLAG_TXE, FAIL); /* if framing error */

    UART->DR = data;

    return OK;
}

unsigned char uart_read(void)
{
    check(!(UART->CR1 & (1 << 5)), 0x00);
    check(!(UART->SR & UART_FLAG_NF), 0x00);
    check(!(UART->SR & UART_FLAG_RXNE), 0x00);
    return UART->DR;
}

void uart_deinit(void)
{
    UART->SR = (unsigned char)0xC0;
    UART->DR = (unsigned char)0x00; /* in reference manual written 0xXX */
    UART->BRR1 = (unsigned char)0x00;
    UART->BRR2 = (unsigned char)0x00;
    UART->CR1 = (unsigned char)0x00;
    UART->CR2 = (unsigned char)0x00;
    UART->CR3 = (unsigned char)0x00;
    UART->CR4 = (unsigned char)0x00;
    UART->CR5 = (unsigned char)0x00;
    UART->GTR = (unsigned char)0x00;
    UART->PSCR = (unsigned char)0x00;
}
