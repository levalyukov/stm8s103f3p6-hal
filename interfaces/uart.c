#include "uart.h"

void uart_init(const unsigned short baudrate, const uart_data_size_t word_length,
               const uart_parity_t parity, const uart_selection_t selection,
               const uart_stopbit_t stopbit)
{
    CLOCK->PCKENR1 |= CLK_GATING_UART1;
    UART->CR1 |= (unsigned char)parity & 0x04U;
    UART->CR1 |= (unsigned char)word_length & 0x10U;

    /* the datasheet requires BRR1 to be written after BRR2 */
    UART->BRR2 = (((baudrate & 0xF000U) >> 8U) | (baudrate & 0x000FU)) & 0xFFU;
    UART->BRR1 = (((baudrate + 8U) & 0x0FF0U) >> 4U) & 0xFFU;

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

void uart_enable(void)
{
    /* The datasheet says 0 bit - enable periphery */
    UART->CR1 &= ~(1U << 5U);
}

void uart_disable(void)
{
    UART->CR1 |= (1U << 5U);
}

void uart_send(const unsigned char data)
{
    if ((UART->CR1 & ~(1U << 5U)) == 1U)
    {
        UART->DR = data;
    }
}

unsigned char uart_read(void)
{
    unsigned char data = 0x00;

    if ((UART->CR1 & ~(1U << 5U)) == 1U)
    {
        data = UART->DR;
    }

    return data;
}

void uart_mode_set(const uart_mode_t mode)
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

void uart_deinit(void)
{
    CLOCK->PCKENR1 &= ~CLK_GATING_UART1;
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
