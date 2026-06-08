#include "uart.h"

error_t uart_init(const uart_parity_control_t parity)
{
    check(UART_PARITY_IS_OK(parity), INVALID_ARG);

    UART->BRR1 = (unsigned char)0x41;
    UART->BRR2 = (unsigned char)0x02;

    if (!(UART->CR3 & (1 << 6)))
        UART->CR1 |= parity;

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

error_t uart_send(const unsigned char data, const uart_transmit_t type)
{
    check(!(UART->CR1 & (1 << 5)), FAIL);
    check(UART_TRANSMIT_IS_OK(type), INVALID_ARG);

    if (type == UART_DATA_TRANSMITTER)
    {
        if (UART->SR & (1 << 7))
            return FAIL;

        UART->CR2 |= (1 << 3);
    }

    if (type == UART_DATA_RECEIVER)
    {
        if (UART->SR & (1 << 5))
            return FAIL;

        UART->CR2 |= (1 << 2);
    }

    if (type == UART_DATA_DUPLEX)
    {
        if (!(UART->CR2 & (1 << 3)))
            UART->CR2 |= (1 << 3);

        if (!(UART->CR2 & (1 << 2)))
            UART->CR2 |= (1 << 2);
    }

    UART->DR = data;

    return OK;
}

unsigned char uart_read(void)
{
    check(!(UART->CR1 & (1 << 5)), 0x00);
    return UART->DR;
}

void uart_deinit(void)
{
    UART->SR = (unsigned char)0xC0;
    UART->DR = (unsigned char)0x00; /* in datasheet written 0xXX */
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
