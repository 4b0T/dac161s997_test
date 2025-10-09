// core/sysclk.c //

#include <msp430.h>
#include "core/sysclk.h"

#ifndef MCLK_MHZ_FREQ
#define MCLK_MHZ_FREQ 8u
#endif

static void software_trim(void) {
    unsigned int oldDcoTap = 0xffff;
    unsigned int newDcoTap = 0xffff;
    unsigned int newDcoDelta = 0xffff;
    unsigned int bestDcoDelta = 0xffff;
    unsigned int csCtl0Copy = 0;
    unsigned int csCtl1Copy = 0;
    unsigned int csCtl0Read = 0;
    unsigned int csCtl1Read = 0;
    unsigned int dcoFreqTrim = 3;
    unsigned char endLoop = 0;

    do {
        CSCTL0 = 0x0100;
        do { CSCTL7 &= ~DCOFFG; } while (CSCTL7 & DCOFFG);
        __delay_cycles((uint16_t)3000 * MCLK_MHZ_FREQ);
        while ((CSCTL7 & (FLLUNLOCK0 | FLLUNLOCK1)) && ((CSCTL7 & DCOFFG) == 0));

        csCtl0Read = CSCTL0;
        csCtl1Read = CSCTL1;

        oldDcoTap = newDcoTap;
        newDcoTap = csCtl0Read & 0x01FF;
        dcoFreqTrim = (csCtl1Read & 0x0070) >> 4;

        if (newDcoTap < 256) {
            newDcoDelta = 256 - newDcoTap;
            if ((oldDcoTap != 0xffff) && (oldDcoTap >= 256)) endLoop = 1;
            else {
                if (dcoFreqTrim) dcoFreqTrim--;
                CSCTL1 = (csCtl1Read & ~(DCOFTRIM0 | DCOFTRIM1 | DCOFTRIM2)) | (dcoFreqTrim << 4);
            }
        } else {
            newDcoDelta = newDcoTap - 256;
            if (oldDcoTap < 256) endLoop = 1;
            else {
                dcoFreqTrim++;
                CSCTL1 = (csCtl1Read & ~(DCOFTRIM0 | DCOFTRIM1 | DCOFTRIM2)) | (dcoFreqTrim << 4);
            }
        }

        if (newDcoDelta < bestDcoDelta) {
            csCtl0Copy = csCtl0Read;
            csCtl1Copy = csCtl1Read;
            bestDcoDelta = newDcoDelta;
        }
    } while (!endLoop);

    CSCTL0 = csCtl0Copy;
    CSCTL1 = csCtl1Copy;
    while (CSCTL7 & (FLLUNLOCK0 | FLLUNLOCK1));
}

void sysclk_cfg(void) {
	/*
    CSCTL4 &= ~XT1OFF;
    do {
        CSCTL5 &= ~XT1OFFG;
        SFRIFG1 &= ~OFIFG;
        __delay_cycles(10000);
    } while (SFRIFG1 & OFIFG);
	*/

    __bis_SR_register(SCG0);
    CSCTL3 |= SELREF__XT1CLK;
    CSCTL1 = DCOFTRIMEN | DCOFTRIM0 | DCOFTRIM1 | DCORSEL_3;
    CSCTL2 = FLLD_0 + 243;
    __delay_cycles(3);
    __bic_SR_register(SCG0);

    software_trim();

    CSCTL4 = SELMS__DCOCLKDIV | SELA__XT1CLK;
    CSCTL5 |= DIVM_0 | DIVS_0;

    SFRIE1 |= WDTIE;
}

#pragma vector = WDT_VECTOR
__interrupt void WDT_ISR(void) {
    while (1) {}
}
