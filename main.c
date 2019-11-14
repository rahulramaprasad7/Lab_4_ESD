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
uint16_t i, readValue, writeAddress, readAddress, data, controlByte, blockNumber, endAddress, temp;
bool readCheck = false;
bool inputReady = false;
char readConvert[8];
char addressConvert[8];
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
    P1->DIR = ~(uint8_t) BIT5;
    P1->OUT = BIT5;
    P1->REN = BIT5;                         // Enable pull-up resistor (P1.5 output high)
    P1->SEL0 = 0;
    P1->SEL1 = 0;
    P1->IES = BIT5;                         // Interrupt on high-to-low transition
    P1->IFG = 0;                            // Clear all P1 interrupt flags
    P1->IE = BIT5;                          // Enable interrupt for P1.5

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
    // Enable Port 1 interrupt on the NVIC
    NVIC->ISER[1] = 1 << ((PORT1_IRQn) & 31);

    printMenu();

    while(1)
    {
        if ( x == 'w')
        {
            x = NULL; //Reset the character used to echo
            putstr("\n\rEnter the address\n\r");
            inputReady = true;
            blockNumber = getstr();
            if ((blockNumber > 0x7FF))
            {
                x = NULL; //Reset the character used to echo
                putstr("\n\rEntered word address is not in range of the EEPROM address");
                printMenu();
                inputReady = false;
                continue;
            }
            inputReady = false;

            putstr("\n\rEnter the data\n\r");
            inputReady = true;
            data = getstr();
            if ((data > 0xFF))
            {
                x = NULL; //Reset the character used to echo
                putstr("\n\rEntered data is not between 0 and FF");
                printMenu();
                inputReady = false;
                continue;
            }
//            x = NULL; //Reset the character used to echo
            inputReady = false;

            controlByte = EEPROM_WRITE | (( blockNumber >> 8) << 1);
            blockNumber &= 0x00FF;
            startBit();
            write(controlByte, blockNumber, data);
            //Acknowledgement polling
//            while (ackCheck != true)
//            {
//                startBit();
//                sendByte(controlByte);
//            }
            stopBit();
            putstr(newLine);
            eereset();
        }

        else if (x == 'r')
        {
            x = NULL; //Reset the character used to echo
            putstr("\n\rEnter the address\n\r");
            inputReady = true;
            blockNumber = getstr();
            readAddress = blockNumber;
            if ((blockNumber > 0x7FF))
            {
                x = NULL; //Reset the character used to echo
                putstr("\n\rEntered word address is not in range of the EEPROM address\n\r");
                printMenu();
                inputReady = false;
                continue;
            }
            inputReady = false;

            controlByte = EEPROM_WRITE | (( blockNumber >> 8) << 1);
            blockNumber &= 0x00FF;
            startBit();
            uint8_t byteRead = read(controlByte, blockNumber);
            snprintf(readConvert, 8, "%X",byteRead);
            snprintf(addressConvert, 8, "%X",readAddress);
            putstr(newLine);
            putstr(addressConvert);
            putstr(":");
            putstr(readConvert);
            memset(readConvert, '\0', 8*sizeof(char)); //Reset the Buffer
            memset(addressConvert, '\0', 8*sizeof(char)); //Reset the Buffer
            stopBit();
//            x = NULL; //Reset the character used to echo
            eereset();
        }

        else if (x == 'x')
        {
            eereset();
            x = NULL; //Reset the character used to echo
            putstr(newLine);
        }

        else if(x == 'p')
        {
            putstr("\n\rEnter the address\n\r");
            inputReady = true;
            blockNumber = getstr();
            if ((blockNumber > 0x7EF))
            {
                x = NULL; //Reset the character used to echo
                putstr("\n\rEntered word address is not in range of the EEPROM address");
                printMenu();
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
                x = NULL; //Reset the character used to echo
                putstr("\n\rEntered data is not between 0 and FF");
                printMenu();
                inputReady = false;
                continue;
            }
            x = NULL; //Reset the character used to echo
            inputReady = false;

            controlByte = EEPROM_WRITE | (( blockNumber >> 8) << 1);
            blockNumber &= 0x00FF;
            startBit();
            pageWrite(controlByte, blockNumber, data);
            stopBit();
            x = NULL; //Reset the character used to echo
            eereset();
        }

        else if(x == 'h')
        {
            putstr("\n\rEnter the starting address\n\r");
            inputReady = true;
            blockNumber = getstr();
            readAddress = blockNumber;
            if ((readAddress > 0x7FF))
            {
                x = NULL; //Reset the character used to echo
                putstr("\n\rEntered address is not in range of the EEPROM address\n\r");
                printMenu();
                inputReady = false;
                continue;
            }
            x = NULL; //Reset the character used to echo
            inputReady = false;

            putstr("\n\rEnter the ending address\n\r");
            inputReady = true;
            temp = getstr();
            endAddress = temp;
            if (((endAddress > 0x7FF) || (endAddress < readAddress)))
            {
                putstr("\n\rEntered address is invalid\n\r");
                printMenu();
                x = NULL; //Reset the character used to echo
                inputReady = false;
                continue;
            }
            x = NULL; //Reset the character used to echo
            inputReady = false;

            putstr("\n\r");
            controlByte = EEPROM_WRITE | (( blockNumber >> 8) << 1);
            blockNumber &= 0x00FF;
            startBit();
            //Write address to read  from EEPROM
            sendByte(controlByte);
            asm(" nop");

            sendByte(writeAddress);
            asm(" nop");

            startBit();
            //Read data from EEPROM
            sendByte((controlByte + 1));
            asm(" nop");
            P6->DIR &= ~BIT7;
            asm(" nop");
            int j, k;
            for ( j = 0; j <= (endAddress - readAddress); j += 16)
            {
                snprintf(addressConvert, 8, "%3X",(readAddress + j));
                putstr(addressConvert);
                putstr(":");
                for (k = j; k < (j+16) && k <= (endAddress - readAddress); k++)
                {
                    putstr(" ");
                    uint8_t a = receiveByte();
                    snprintf(readConvert, 8, "%2X",a);
                    putstr(readConvert);
                    memset(readConvert, '\0', 8*sizeof(char)); //Reset the Buffer
                    asm(" nop");
                    ack();
                }
                putstr("\n\r");
                memset(addressConvert, '\0', 8*sizeof(char)); //Reset the Buffer
            }
            stopBit();
            eereset();
        }
        else if (x == 'm')
        {
            printMenu();
            x = NULL;  //Resetting echo character
        }

        else if (x == 'i')
        {
            startBit();
            sendByte(0x40);
            sendByte(0x01);
            stopBit();
            x = NULL;
        }
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

void PORT1_IRQHandler(void)
{
    // Toggling the output on the LED
    if(P1->IFG & BIT5)
    {

    }
    P1->IFG &= ~BIT5;
}
