#pragma once
#include "msp430fr2433.h"

// P3
#define P3_DIR_CFG  (BIT0 | BIT1 | BIT2)
#define P3_OUT_CFG  (BIT0 | BIT1 | BIT2)
#define P3_SEL0_CFG (0x00)
#define P3_SEL1_CFG (0x00)
#define P3_REN_CFG  (0x00)

// P2
#define XOUT        BIT0
#define XIN         BIT1
#define NC22        BIT2
#define NC23        BIT3
#define SPI_CS      BIT4
#define SPI_CS2     BIT5
#define TST         BIT6
#define ERRB        BIT7

#define P2_SEL0_CFG  (XIN | XOUT)
#define P2_SEL1_CFG  (0x00)
#define P2_DIR_CFG   (NC22 | NC23 | SPI_CS | SPI_CS2 | TST)
#define P2_OUT_CFG   (NC22 | NC23 | SPI_CS | SPI_CS2)
#define P2_REN_CFG   (ERRB)
#define P2_OUT_PULLS (ERRB)

// P1
#define LED_STT     BIT0
#define SPI_SCK     BIT1
#define SPI_SIMO    BIT2
#define SPI_SOMI    BIT3
#define TXD         BIT4
#define RXD         BIT5
#define TEN         BIT6
#define NC17        BIT7

#define P1_SEL0_CFG  (SPI_SCK | SPI_SIMO | SPI_SOMI | RXD | TXD)
#define P1_SEL1_CFG  (0x00)
#define P1_DIR_CFG   (LED_STT | TEN | NC17)
#define P1_OUT_CFG   (NC17)
#define P1_REN_CFG   (0x00)

void io_ctl(void);
