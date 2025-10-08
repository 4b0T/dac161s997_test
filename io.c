// io.c //

#include "io.h"

void io_ctl(void) {
    // Port 1
    P1DIR  = P1_DIR_CFG;
    P1OUT  = P1_OUT_CFG;
    P1SEL0 = P1_SEL0_CFG;
    P1SEL1 = P1_SEL1_CFG;
    P1REN  = P1_REN_CFG;

    // Port 2
    P2SEL0 = P2_SEL0_CFG;
    P2SEL1 = P2_SEL1_CFG;
    P2DIR  = P2_DIR_CFG;
    P2OUT  = P2_OUT_CFG;
    P2REN  = P2_REN_CFG;
    if (P2_REN_CFG) {
        P2OUT = (P2OUT & ~P2_REN_CFG) | (P2_OUT_PULLS & P2_REN_CFG);
    }

    // Port 3
    P3DIR  = P3_DIR_CFG;
    P3OUT  = P3_OUT_CFG;
    P3SEL0 = P3_SEL0_CFG;
    P3SEL1 = P3_SEL1_CFG;
    P3REN  = P3_REN_CFG;

    PM5CTL0 &= ~LOCKLPM5;
}
