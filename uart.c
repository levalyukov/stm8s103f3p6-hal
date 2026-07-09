#include "uart.h"

static void uart_baudrate_set(uart_baudrate_t baudrate);

error_t uart_init(const uart_baudrate_t baudrate,
                  const uart_data_size_t word_length,
                  const uart_parity_t parity,
                  const uart_selection_t selection,
                  const uart_stopbit_t stopbit)
{
    error_t status = OK;

    if (!UART_BAUDRATE_IS_OK(baudrate) || !UART_WORD_IS_OK(word_length) ||
        !UART_PARITY_IS_OK(parity) ||
        !UART_PARITY_SELECTION_IS_OK(selection) ||
        !UART_STOPBIT_IS_OK(stopbit))
    {
        status = INVALID_ARG;
    }

    if (status == OK)
    {
        CLOCK->PCKENR1 |= CLK_GATING_UART1;
        UART->CR1 |= parity;
        UART->CR1 |= word_length;
        uart_baudrate_set(baudrate);

        if (stopbit != UART_STOPBIT_1)
        {
            UART->CR3 |= stopbit;
        }
        else
        {
            UART->CR3 &= ~stopbit;
        }

        if (UART->CR3 & (1U << 6U) || !stopbit)
        {
            UART->CR3 &= ~((1U << 5U) | (1U << 4U));
        }

        if (!(UART->CR3 & (1U << 6U)))
        {
            UART->CR1 |= parity;
            UART->CR1 |= selection;
        }
    }

    return status;
}

error_t uart_enable(void)
{
    error_t status = OK;

    if ((UART->CR1 & (1U << 5U)) == 1U)
    {
        UART->CR1 &= ~(1U << 5U);
    }
    else
    {
        status = FAIL;
    }

    return status;
}

error_t uart_disable(void)
{
    error_t status = OK;

    if ((UART->CR1 & ~(1U << 5U)) == 1U)
    {
        UART->CR1 |= (1U << 5U);
    }
    else
    {
        status = FAIL;
    }

    return status;
}

error_t uart_send(const unsigned char data)
{
    error_t status = OK;
    if ((UART->CR1 & ~(1U << 5U)) == 1U)
    {
        UART->DR = data;
    }
    else
    {
        status = INVALID_ARG;
    }

    return status;
}

unsigned char uart_read(void)
{
    unsigned char data = 0x00U;
    if ((UART->CR1 & ~(1U << 5U)) == 1U)
    {
        data = UART->DR;
    }

    return data;
}

error_t uart_mode_set(const uart_mode_t mode)
{
    error_t status = OK;
    if (!UART_MODE_IS_OK(mode))
    {
        status = INVALID_ARG;
    }

    if (status == OK)
    {
        if (mode == UART_MODE_RECEIVER)
        {
            UART->CR2 |= (1U << 2U);
        }

        if (mode == UART_MODE_TRANSMITTER)
        {
            UART->CR2 |= (1U << 3U);
        }

        if (mode == UART_MODE_FULLDUPLEX)
        {
            UART->CR2 |= ((1U << 3U) | (1U << 2U));
        }

        if (mode == UART_MODE_NONE)
        {
            UART->CR2 &= ~((1U << 3U) | (1U << 2U));
        }
    }

    return status;
}

static void uart_baudrate_set(const uart_baudrate_t baudrate)
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
        break;
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
