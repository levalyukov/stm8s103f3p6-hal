#if defined(STM8S103F3P6_HAL)
#if !defined(HAL_SPI_H)
#define HAL_SPI_H

#include <gpio.h>
#include <clock.h>
/* cppcheck-suppress misra-c2012-11.4 */
#define SPI ((volatile spi_t *)0x005200)

#define SPI_MODE_SLAVE   ~(1U << 4U)&0xFFU
#define SPI_MODE_MASTER   (1U << 4U)
#define SPI_FRAME_MSB    ~(1U << 7U)&0xFFU
#define SPI_FRAME_LSB     (1U << 7U)
#define SPI_SCK_LOW      ~(1U << 1U)&0xFFU
#define SPI_SCK_HIGH      (1U << 1U)
#define SPI_PHASE_FIRST  ~(1U << 0U)&0xFFU
#define SPI_PHASE_SECOND  (1U << 0U)

#define SPI_BAUDRATE_2    0x00U
#define SPI_BAUDRATE_4    0x08U
#define SPI_BAUDRATE_8    0x10U
#define SPI_BAUDRATE_16   0x18U
#define SPI_BAUDRATE_32   0x20U
#define SPI_BAUDRATE_64   0x28U
#define SPI_BAUDRATE_128  0x30U
#define SPI_BAUDRATE_256  0x38U

#define SPI_FLAG_BSY      (1U << 7U)
#define SPI_FLAG_OVR      (1U << 6U)
#define SPI_FLAG_MODF     (1U << 5U)
#define SPI_FLAG_CRCERR   (1U << 4U)
#define SPI_FLAG_WKUP     (1U << 3U)
#define SPI_FLAG_TXE      (1U << 1U)
#define SPI_FLAG_RXNE     (1U << 0U)

/* bidirectional mode */
#define SPI_BDM_2_LINE   ~(1U << 7U)&0xFFU
#define SPI_BDM_1_LINE    (1U << 7U)
/* only reciver or output if bdm is set to 1 */
#define SPI_RECIVE_ONLY  ~(1U << 6U)&0xFFU
#define SPI_TRANSMIT_ONLY (1U << 6U)

#define SPI_ENABLE        (1U << 6U)
#define SPI_DISABLE      ~(1U << 6U)&0xFFU

typedef struct
{
    volatile unsigned char CR1;    /* Control Register 1 */
    volatile unsigned char CR2;    /* Control Register 2 */
    volatile unsigned char ICR;    /* Interrupt Control Register */
    volatile unsigned char SR;     /* Status Register */
    volatile unsigned char DR;     /* Data Register */
    volatile unsigned char CRCPR;  /* CRC Polynomial Register */
    volatile unsigned char RXCRCR; /* Rx CRC Register */
    volatile unsigned char TXCRCR; /* Tx CRC Register */
} spi_t;

typedef struct
{
    unsigned char baudrate;
    unsigned char mode;
    unsigned char frame;
    unsigned char polarity;
    unsigned char phase;
    unsigned char bidirection;
    unsigned char direction;
} spi_config_t;

typedef struct
{
    volatile gpio_t* port_cs;
    volatile gpio_t* port_dc;
    unsigned char pin_cs;
    unsigned char pin_dc;
} spi_device_t;

void spi_init(spi_config_t* config, spi_device_t* device);
void spi_enable(void);
void spi_disable(void);
void spi_deinit(void);

void spi_write(spi_device_t* device, unsigned char data, unsigned char dc);
unsigned char spi_read(void);

#endif /* HAL_SPI_H */
#endif /* STM8S103F3P6_HAL */
