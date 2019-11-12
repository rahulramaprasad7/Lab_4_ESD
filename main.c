/**
 * main.c
 * This file communicates with the EEPROM
 * using I2C protocol and performs read and
 * write operations on the memory.
 */

#include "msp.h"
#include "myIncludes.h"

char wrongInput[80] = "\n\rPlease enter a valid character\n\r";
char wrongStringInput[80] = "\n\rPlease enter valid data or address\n\r";
char newLine [2] = {'\n','\r'};
int i, readValue;
bool readCheck = false;
bool inputReady = false;
int getstr()
{
    memset(buffer, '\0', 10*sizeof(char)); //Reset the Buffer
    i = 0;
    while (x != '\r')
    {
        if ( i == 6)
        {
            buffer[i] = '\0';
            putstr(wrongStringInput);
            return 0;
        }
        else if ( readCheck == true)
        {
            buffer[i] = x;
            i++;
            readCheck = false;
        }
    }
    buffer[i] = '\0';
    sscanf(buffer, "%d", &readValue);
    putstr(newLine);
    return (readValue);
}
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

    printMenu();

    while(1)
    {
        if ( x == 'w')
        {
            putstr("\n\rEnter the address\n\r");
            inputReady = true;
            readInput = getstr();
            memset(buffer, '\0', 10*sizeof(char)); //Reset the Buffer
            snprintf(buffer, 10, "%d", readInput);
            x = NULL; //Reset the character used to echo
            inputReady = false;
            putstr(buffer);
            putstr(newLine);
            startBit();
            write();
            stopBit();
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
    if(inputReady)
        readCheck = true;
}
