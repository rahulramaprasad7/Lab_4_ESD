/*
 * uartInit.c
 *
 *  Created on: 10-Nov-2019
 *      Author: Rahul
 */

#include "myIncludes.h"

void uartInit()
{

    P1->SEL0 |= BIT2 | BIT3;  //Selecting the alternate functions of P1.2 and P1.3 for Rx and Tx

    EUSCI_A0->CTLW0 |= EUSCI_A_CTLW0_SWRST;  //Enabling software reset
    EUSCI_A0->CTLW0 = EUSCI_A_CTLW0_SWRST | EUSCI_B_CTLW0_SSEL__SMCLK;  //Enabling clock
    /* Baudrate calculation
     * Fclk = 3Mhz, Baudrate = 230400
    */
    EUSCI_A0->BRW = 13;
    EUSCI_A0->MCTLW = 0;

    EUSCI_A0->CTLW0 &= ~EUSCI_A_CTLW0_SWRST;  //Disabling reset
    EUSCI_A0->IFG &= ~EUSCI_A_IFG_RXIFG;      //Clearing Rx flag
    EUSCI_A0->IE |= EUSCI_A_IE_RXIE;          //Enabling Rx interrupt
}


