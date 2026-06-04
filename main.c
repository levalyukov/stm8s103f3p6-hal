#include "gpio.h"
#include "error.h"
#include "mcu_pins_layout.h"
#include "spi.h"
#include "st7735s.h"

error_t main(void)
{
    spi_device_t device = {
        .gpio_cs = GPIO_D,
	.gpio_dc = GPIO_D,
	.cs = 5,
	.dc = 6
    };

    (void)gpio_direction_set(GPIO_D, 6, OUTPUT);
    (void)gpio_direction_set(GPIO_D, 5, OUTPUT);
    (void)gpio_level_set(GPIO_D, 5, HIGH);
    (void)spi_init(SPI_MODE_MASTER, SPI_BAUD_RATE_8, SPI_FRAME_FORMAT_MSB);
    (void)spi_enable();

    assert(spi_send(&device, SPI_TRANSACTION_COMMAND, SWRESET) == OK);
    assert(spi_send(&device, SPI_TRANSACTION_COMMAND, GAMSET) == OK);
    assert(spi_send(&device, SPI_TRANSACTION_COMMAND, SLPOUT) == OK);
    assert(spi_send(&device, SPI_TRANSACTION_COMMAND, DISPON) == OK);

    return OK;
}
