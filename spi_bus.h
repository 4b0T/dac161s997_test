// spi_bus.h //

#pragma once

#include <stdint.h>
#include "drivers/spi/spi_ucb0.h"

// Identyfikatory urządzeń na magistrali
typedef enum {
    DEV_PCAP04 = 0,
    DEV_DAC161 = 1,
    DEV_COUNT
} spi_dev_t;

// Konfiguracja profilu urządzenia
typedef struct {
    spi_mode_t mode;   // SPI mode (0..3)
    uint16_t   div;    // dzielnik UCB0BRW: SCLK = SMCLK / div
} spi_profile_t;

// Inicjalizacja magistrali (UCB0 + domyślne profile + CS/TST w stan spoczynku)
void spi_bus_init(void);

// Zmiana profilu konkretnego urządzenia (np. DAC: Mode 3, 500 kHz -> mode=SPI_MODE3, div=16)
void spi_bus_config(spi_dev_t dev, spi_mode_t mode, uint16_t div);

// Rozpoczęcie transakcji z danym urządzeniem (ustawia mode/div, podnosi TST, opuszcza właściwy CS)
void spi_begin(spi_dev_t dev);

// Zakończenie transakcji (podnosi CS danego urządzenia, opuszcza TST)
void spi_end(spi_dev_t dev);

