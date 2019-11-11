/**
 * main.c
 * This file communicates with the EEPROM
 * using I2C protocol and performs read and
 * write operations on the memory.
 */

#include "msp.h"
#include "myIncludes.h"

char messages[5][80] = {"Enter w to write a byte ", "Enter r to read a byte ", "Enter h to hex dump ", "Enter x for reset ","Enter b to go back to main menu "};
char newLine [2] = {'\n','\r'};
int i;

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

    uartInit();

    __enable_irq();   //Enable global interrupts

    NVIC->ISER[0] |= (1 << (EUSCIA0_IRQn & 31));

    for ( i = 0; i < 4; i++)
    {
        putstr(&messages[i][80]);
        putstr(newLine);
    }

    //Initialise SDA and SCL pins
    pinInit();
    asm(" nop");

/****************** EEPROM WRITE ***************/
    //Send Start Bit
    startBit();

    //Write to EEPROM
    sendByte(EEPROM_WRITE);
    asm(" nop");

    sendByte(0x00);
    asm(" nop");

    sendByte(0x03);
    asm(" nop");

/****************** EEPROM READ ***************/
    //Send Start to read
    startBit();

    //Write address to read  from EEPROM
    sendByte(EEPROM_WRITE);
    asm(" nop");

    sendByte(0x00);
    asm(" nop");

    startBit();
    //Read data from EEPROM
    sendByte(EEPROM_READ);
    asm(" nop");

    char a = receiveByte();
    asm(" nop");

    //stopBit();
    stopBit();

    while(1);
}

void EUSCIA0_IRQHandler(void)
{
    if(EUSCI_A_IFG_RXIFG & EUSCI_A0->IFG )
    {
        while(!(EUSCI_A0->IFG & EUSCI_A_IFG_TXIFG));
        x = EUSCI_A0->RXBUF;  //Receive a character
    }
    EUSCI_A0->TXBUF = x;  //Transmit the character
}
