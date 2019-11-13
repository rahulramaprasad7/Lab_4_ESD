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
uint16_t i, readValue, writeAddress, readAddress, data, controlByte, blockNumber;
bool readCheck = false;
bool inputReady = false;
char readConvert[8];
uint16_t getstr()
{
    memset(buffer, '\0', 10*sizeof(char)); //Reset the Buffer
    i = 0;
    while (x != '\r')
    {
        if ( i == 5)
        {
            buffer[i] = '\0';
            putstr(wrongStringInput);
            printMenu();
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
    sscanf(buffer, "%X", &readValue);
    x = NULL;
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
            blockNumber = getstr();
            if ((blockNumber > 0x7FF))
            {
                putstr("\n\rEntered word address is not in range of the EEPROM address");
                printMenu();
                x = NULL; //Reset the character used to echo
                inputReady = false;
                continue;
            }
            x = NULL; //Reset the character used to echo
            inputReady = false;

            putstr("\n\rEnter the data\n\r");
            inputReady = true;
            data = getstr();
            if ((data > 0xFF))
            {
                putstr("\n\rEntered data is not between 0 and FF");
                printMenu();
                x = NULL; //Reset the character used to echo
                inputReady = false;
                continue;
            }
            x = NULL; //Reset the character used to echo
            inputReady = false;

            controlByte = EEPROM_WRITE | (( blockNumber >> 8) << 1);
            blockNumber &= 0x00FF;
            startBit();
            write(controlByte, blockNumber, data);
            stopBit();
            putstr(newLine);
        }

        else if (x == 'r')
        {
            putstr("\n\rEnter the address\n\r");
            inputReady = true;
            blockNumber = getstr();
            if ((blockNumber > 0x7FF))
            {
                putstr("\n\rEntered word address is not in range of the EEPROM address");
                printMenu();
                x = NULL; //Reset the character used to echo
                inputReady = false;
                continue;
            }
            x = NULL; //Reset the character used to echo
            inputReady = false;

            controlByte = EEPROM_WRITE | (( blockNumber >> 8) << 1);
            blockNumber &= 0x00FF;
            startBit();
            uint8_t byteRead = read(controlByte, blockNumber);
            snprintf(readConvert, 8, "%X",byteRead);
            putstr(newLine);
            putstr(readConvert);
            putstr(newLine);
            stopBit();
            memset(readConvert, '\0', 8*sizeof(char)); //Reset the Buffer
            x = NULL; //Reset the character used to echo
            putstr(newLine);
        }

        else if (x == 'x')
        {
            eereset();
            x = NULL; //Reset the character used to echo
            putstr(newLine);
        }

        else if(x == 'p')
        {
            startBit();
            pageWrite();
            stopBit();
            x = NULL; //Reset the character used to echo
            putstr(newLine);
        }

        else if(x == 'h')
        {

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
