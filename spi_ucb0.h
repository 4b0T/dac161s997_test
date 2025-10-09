// spi_ucb0.h //

#pragma once


#include <stdint.h>

typedef enum {
    SPI_MODE0 = 0, // CPOL=0, CPHA=0 -> UCCKPL=0, UCCKPH=1
    SPI_MODE1,     // CPOL=0, CPHA=1 -> UCCKPL=0, UCCKPH=0
    SPI_MODE2,     // CPOL=1, CPHA=0 -> UCCKPL=1, UCCKPH=1
    SPI_MODE3      // CPOL=1, CPHA=1 -> UCCKPL=1, UCCKPH=0
} spi_mode_t;

void spi_ucb0_init(void);
uint8_t spi_ucb0_xfer(uint8_t byte);
void spi_ucb0_set_div(uint16_t div);
void spi_ucb0_set_mode(spi_mode_t mode);

void spi_cs1_low(void);
void spi_cs1_high(void);
void spi_tst_low(void);
void spi_tst_high(void);
