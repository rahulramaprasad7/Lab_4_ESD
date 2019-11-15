/*
 * putstr.c
 *
 *  Sends the serial
 *  message on UI.
 */

#include "myIncludes.h"

void putstr(char *buff)
{
    int i = 0;
    while(buff[i] != '\0') //Transmit until the NULL character is reached
    {
        while(!(EUSCI_A0->IFG & EUSCI_A_IFG_TXIFG)); //Wait till other interrupts are cleared
        EUSCI_A0->TXBUF = buff[i];  //Transmit by loading into TxBUF
        i++;
    }
}


