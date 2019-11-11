/**
 * main.c
 * This file communicates with the EEPROM
 * using I2C protocol and performs read and
 * write operations on the memory.
 */

#include "msp.h"
#include "myIncludes.h"

char uiLines[80] = "\n\r-------------------------------------------------\n\r";
char messages[6][80] = {" Enter w to write a byte ", " Enter r to read a byte ", " Enter h to hex dump ", " Enter p to page write "," Enter x for reset "," Enter b to go back to main menu\n\r"};
char wrongInput[80] = "Please enter a valid character";
char wrongStringInput[80] = "Please enter valid data or address";
char newLine [2] = {'\n','\r'};
int i, readValue;

//int getstr()
//{
//    i = 0;
//    while (x != '\r')
//    {
//        if ( i == 4)
//        {
//            putstr(wrongStringInput);
//            putstr(newLine);
//            break;
//        }
//        buffer[i] = x;
//        i++;
//    }
//    readValue = atoi(buffer);
//    snprintf(buffer,10,"%d", readValue); //Print Duty cycle
//    putstr(buffer);
////    printf("%d", readValue);
//    return (readValue);
//}
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

    //Initialise SDA and SCL pins
    pinInit();
    asm(" nop");

    //Initialise UART registers
    uartInit();

    //Enable global interrupts
    __enable_irq();

    //Add UART interrupt to NVIC
    NVIC->ISER[0] |= (1 << (EUSCIA0_IRQn & 31));

    putstr(uiLines);
    putstr(newLine);
    for ( i = 0; i < 6; i++)
    {
        putstr(messages[i]);
        putstr(newLine);
    }
    putstr(uiLines);
    putstr(newLine);
    while(1)
    {
//        for ( i = 0; i < 4; i++)
//        {
//            putstr(&messages[i][80]);
//            putstr(newLine);
//        }
        if ( x == 'w')
        {
            startBit();
            write();
            stopBit();
            x = NULL; //Reset the character used to echo
        }

        else if (x == 'r')
        {
            startBit();
            read();
            stopBit();
            x = NULL; //Reset the character used to echo
        }

        else if (x == 'x')
        {
            eereset();
            x = NULL; //Reset the character used to echo
        }

        else if(x == 'p')
        {
            startBit();
            pageWrite();
            stopBit();
            x = NULL; //Reset the character used to echo
        }
//        else
//        {
//            putstr(wrongInput);
//            x = NULL; //Reset the character used to echo
//        }
    }
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
