// spi_bus.c //

#include <msp430.h>
#include "drivers/spi/spi_bus.h"
#include "core/io.h"


void spi_cs2_low(void);
void spi_cs2_high(void);


// Tablica profili dla urządzeń
static spi_profile_t s_profile[DEV_COUNT] = {
    [DEV_PCAP04] = { .mode = SPI_MODE1, .div = 4 }, // PCAP04: Mode 1, 2 MHz
    [DEV_DAC161] = { .mode = SPI_MODE0, .div = 4 }  // DAC161: Mode 0, 2 MHz
};

static inline void cs_all_high(void) {
    P2OUT |= (SPI_CS | SPI_CS2);
}


void spi_bus_init(void) {
    spi_ucb0_init();
    cs_all_high();

    spi_ucb0_set_mode(s_profile[DEV_PCAP04].mode);
    spi_ucb0_set_div(s_profile[DEV_PCAP04].div);
}

void spi_bus_config(spi_dev_t dev, spi_mode_t mode, uint16_t div) {
    if (dev >= DEV_COUNT) return;
    if (div == 0) div = 1;
    s_profile[dev].mode = mode;
    s_profile[dev].div  = div;
}

void spi_begin(spi_dev_t dev) {
    if (dev >= DEV_COUNT) return;

    cs_all_high();
    spi_ucb0_set_mode(s_profile[dev].mode);
    spi_ucb0_set_div(s_profile[dev].div);
    __no_operation();

    spi_tst_high();
    if (dev == DEV_PCAP04) {
        spi_cs1_low();
    } else if (dev == DEV_DAC161) {
        spi_cs2_low();
    }
}

void spi_end(spi_dev_t dev) {
    if (dev >= DEV_COUNT) return;

    if (dev == DEV_PCAP04) {
        spi_cs1_high();
    } else if (dev == DEV_DAC161) {
        spi_cs2_high();
    }
    spi_tst_low();
}


void spi_cs2_low(void)  { P2OUT &= ~SPI_CS2; }
void spi_cs2_high(void) { P2OUT |=  SPI_CS2; }

