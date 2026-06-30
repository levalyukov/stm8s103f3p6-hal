#include "uart.h"

error_t uart_init(const uart_baudrate_t baudrate,
                  const uart_data_size_t word_length,
                  const uart_parity_t parity,
                  const uart_selection_t selection,
                  const uart_stopbit_t stopbit)
{
    check(UART_BAUDRATE_IS_OK(baudrate), INVALID_ARG);
    check(UART_WORD_IS_OK(word_length), INVALID_ARG);
    check(UART_PARITY_IS_OK(parity), INVALID_ARG);
    check(UART_PARITY_SELECTION_IS_OK(selection), INVALID_ARG);
    check(UART_STOPBIT_IS_OK(stopbit), INVALID_ARG);

    CLOCK->PCKENR1 |= CLK_GATING_UART1;
    UART->CR1 |= parity;
    UART->CR1 |= word_length;
    uart_baudrate_set(baudrate);

    if (stopbit != UART_STOPBIT_1)
        UART->CR3 |= stopbit;

    if (UART->CR3 & (1 << 6) || !stopbit)
        UART->CR3 &= ~((1 << 5) | (1 << 4));

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
    UART->CR1 &= ~(1 << 5);
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
    check(!(UART->CR1 & (1 << 5)), FAIL); /* if uart disabled */
    UART->DR = data;
    return OK;
}

unsigned char uart_read(void)
{
    check(!(UART->CR1 & (1 << 5)), 0x00); /* if disabled */
    return UART->DR;
}

error_t uart_mode_set(const uart_mode_t mode)
{
    check(UART_MODE_IS_OK(mode), INVALID_ARG);

    if (mode == UART_MODE_RECEIVER)
        UART->CR2 |= (1 << 2);

    if (mode == UART_MODE_TRANSMITTER)
        UART->CR2 |= (1 << 3);

    if (mode == UART_MODE_FULLDUPLEX)
        UART->CR2 |= ((1 << 3) | (1 << 2));

    if (mode == UART_MODE_NONE)
        UART->CR2 &= ~((1 << 3) | (1 << 2));

    return OK;
}

void uart_baudrate_set(const uart_baudrate_t baudrate)
{
    switch (baudrate)
    {
    case UART_BAUDRATE_2400:
        UART->BRR2 = 0x17;
        UART->BRR1 = 0x04;
        break;

    case UART_BAUDRATE_9600:
        UART->BRR2 = 0x02;
        UART->BRR1 = 0x41;
        break;

    case UART_BAUDRATE_19200:
        UART->BRR2 = 0x09;
        UART->BRR1 = 0x20;
        break;

    case UART_BAUDRATE_57600:
        UART->BRR2 = 0x0E;
        UART->BRR1 = 0x0A;
        break;

    case UART_BAUDRATE_115200:
        UART->BRR2 = 0x07;
        UART->BRR1 = 0x05;
        break;

    case UART_BAUDRATE_230400:
        UART->BRR2 = 0x0B;
        UART->BRR1 = 0x02;
        break;

    case UART_BAUDRATE_460800:
        UART->BRR2 = 0x06;
        UART->BRR1 = 0x01;
        break;

    default:
        UART->BRR2 = 0x00;
        UART->BRR1 = 0x00;
    }
}

void uart_deinit(void)
{
    UART->SR = 0xC0;
    UART->DR = 0x00; /* in reference manual written 0xXX */
    UART->BRR1 = 0x00;
    UART->BRR2 = 0x00;
    UART->CR1 = 0x00;
    UART->CR2 = 0x00;
    UART->CR3 = 0x00;
    UART->CR4 = 0x00;
    UART->CR5 = 0x00;
    UART->GTR = 0x00;
    UART->PSCR = 0x00;
}
