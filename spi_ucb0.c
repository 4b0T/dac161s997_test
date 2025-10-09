// spi_ucb0.c //

#include <msp430.h>
#include "drivers/spi/spi_ucb0.h"
#include "core/io.h"


// spi_ucb0.c
void spi_ucb0_init(void) {
    UCB0CTLW0 = UCSWRST | UCSSEL__SMCLK | UCSYNC | UCMST | UCMSB; // baza
    UCB0CTLW0 &= ~(UCCKPL | UCCKPH); // CPOL=0, CPHA=1 (na MSP430: UCCKPH=0 => CPHA=1)
    UCB0BRW = 4; // 8 MHz / 16 = 2MHz
    UCB0CTLW0 &= ~UCSWRST;
}



uint8_t spi_ucb0_xfer(uint8_t byte) {
    while (!(UCB0IFG & UCTXIFG));
    UCB0TXBUF = byte;
    while (!(UCB0IFG & UCRXIFG));
    return UCB0RXBUF;
}


void spi_ucb0_set_div(uint16_t div) {
    if (div == 0) div = 1;
    UCB0CTLW0 |= UCSWRST;
    UCB0BRW = div;
    UCB0CTLW0 &= ~UCSWRST;
}


void spi_ucb0_set_mode(spi_mode_t mode) {
    UCB0CTLW0 |= UCSWRST;
    UCB0CTLW0 &= ~(UCCKPL | UCCKPH);
    switch (mode) {
        case SPI_MODE0: UCB0CTLW0 |= UCCKPH; break;                 // CPOL=0, CPHA=0
        case SPI_MODE1: break;                                      // CPOL=0, CPHA=1
        case SPI_MODE2: UCB0CTLW0 |= (UCCKPL | UCCKPH); break;      // CPOL=1, CPHA=0
        case SPI_MODE3: UCB0CTLW0 |= UCCKPL; break;                 // CPOL=1, CPHA=1
        default: UCB0CTLW0 |= UCCKPL; break;
    }
    UCB0CTLW0 &= ~UCSWRST;
}


void spi_cs1_low(void)  { P2OUT &= ~SPI_CS; }
void spi_cs1_high(void) { P2OUT |=  SPI_CS; }
void spi_tst_low(void)  { P2OUT &= ~TST; }
void spi_tst_high(void) { P2OUT |=  TST; }
