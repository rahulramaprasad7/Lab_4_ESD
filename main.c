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
uint16_t i, readValue, writeAddress, readAddress, data, controlByte, blockNumber, endAddress, temp;
volatile bool readCheck = false;
volatile bool inputReady1 = false;
volatile bool inputReady2 = false;
volatile bool interruptCheck = false;
char readConvert[8];
char addressConvert[8];
char expanderInput[8];

uint16_t getstr()
{
    memset(buffer, '\0', 10*sizeof(char)); //Reset the Buffer
    i = 0;
    while (x != '\n')
    {
        if ( i == 5)
        {
            buffer[i] = '\0';
            memset(buffer, '\0', 10*sizeof(char)); //Reset the Buffer
            putstr(wrongStringInput);
            printMenu();
            return 10000;
        }
        else if ( readCheck == true)
        {
            if( (x >= '0' && x <= '9') || (x >= 'A' && x <= 'F') || (x >= 'a' && x <= 'f') || x == '\n' || x == '\r')
            {
                buffer[i] = x;
                i++;
//                readCheck = false;
            }
            else if (x != NULL)
            {
                putstr("\n\rInavlid Input\n\r");
                printMenu();
                readCheck = false;
                x = NULL;
                return 10000;
            }
            readCheck = false;
        }
    }
//    buffer[i] = '\0';
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
            inputReady1 = true;
            blockNumber = getstr();
            if(blockNumber == 10000)
                continue;
            if (blockNumber > 0x7FF)
            {
                x = NULL; //Reset the character used to echo
                putstr("\n\rEntered word address is not in range of the EEPROM address\n\r");
                printMenu();
                inputReady1 = false;
                continue;
            }
            inputReady1 = false;

            putstr("\n\rEnter the data\n\r");
            inputReady2 = true;
            data = getstr();
            if(data == 10000)
                continue;
            if (data > 0xFF)
            {
                x = NULL; //Reset the character used to echo
                putstr("\n\rEntered data is not between 0 and FF");
                printMenu();
                inputReady2 = false;
                continue;
            }
            x = NULL; //Reset the character used to echo
            inputReady2 = false;

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
            putstr("\n\r");
//            eereset();
        }

        else if (x == 'r')
        {
            x = NULL; //Reset the character used to echo
            putstr("\n\rEnter the address\n\r");
            inputReady1 = true;
            blockNumber = getstr();
            if(blockNumber == 10000)
                continue;
            readAddress = blockNumber;
            if ((blockNumber > 0x7FF))
            {
                x = NULL; //Reset the character used to echo
                putstr("\n\rEntered word address is not in range of the EEPROM address\n\r");
                printMenu();
                inputReady1 = false;
                continue;
            }
            inputReady1 = false;

            controlByte = EEPROM_WRITE | (( blockNumber >> 8) << 1);
            blockNumber &= 0x00FF;
            startBit();
            uint8_t byteRead = read(controlByte, blockNumber);
            snprintf(readConvert, 8, "%X",byteRead);
            snprintf(addressConvert, 8, "%X",readAddress);
            putstr("\n\r");
            putstr(addressConvert);
            putstr(":");
            putstr(readConvert);
            memset(readConvert, '\0', 8*sizeof(char)); //Reset the Buffer
            memset(addressConvert, '\0', 8*sizeof(char)); //Reset the Buffer
            stopBit();
//            x = NULL; //Reset the character used to echo
//            eereset();
        }

        else if (x == 'x')
        {
            x = NULL; //Reset the character used to echo
            eereset();
            putstr("\n\r");
        }

        else if(x == 'p')
        {
            x = NULL; //Reset the character used to echo
            putstr("\n\rEnter the address\n\r");
            inputReady1 = true;
            blockNumber = getstr();
            if(blockNumber == 10000)
                continue;
            if ((blockNumber > 0x7EF))
            {
                x = NULL; //Reset the character used to echo
                putstr("\n\rEntered word address is not in range of the EEPROM address");
                printMenu();
                inputReady1 = false;
                continue;
            }
            x = NULL; //Reset the character used to echo
            inputReady1 = false;

            putstr("\n\rEnter the data\n\r");
            inputReady2 = true;
            data = getstr();
            if(data == 10000)
                continue;
            if ((data > 0xFF))
            {
                x = NULL; //Reset the character used to echo
                putstr("\n\rEntered data is not between 0 and FF");
                printMenu();
                inputReady2 = false;
                continue;
            }
            x = NULL; //Reset the character used to echo
            inputReady2 = false;

            controlByte = EEPROM_WRITE | (( blockNumber >> 8) << 1);
            blockNumber &= 0x00FF;
            startBit();
            pageWrite(controlByte, blockNumber, data);
            stopBit();
            x = NULL; //Reset the character used to echo
//            eereset();
        }

        else if(x == 'h')
        {
            x = NULL;
            putstr("\n\rEnter the starting address\n\r");
            inputReady1 = true;
            blockNumber = getstr();
            if(blockNumber == 10000)
                continue;
            readAddress = blockNumber;
            if ((readAddress > 0x7FF))
            {
                x = NULL; //Reset the character used to echo
                putstr("\n\rEntered address is not in range of the EEPROM address\n\r");
                printMenu();
                inputReady1 = false;
                continue;
            }
            x = NULL; //Reset the character used to echo
            inputReady1 = false;

            putstr("\n\rEnter the ending address\n\r");
            inputReady2 = true;
            temp = getstr();
            if(temp == 10000)
                continue;
            endAddress = temp;
            if (endAddress > 0x7FF)
            {
                putstr("\n\rEntered address is invalid\n\r");
                printMenu();
                x = NULL; //Reset the character used to echo
                inputReady2 = false;
                continue;
            }

            if (endAddress < readAddress)
            {
                putstr("\n\rEntered address is invalid\n\r");
                printMenu();
                x = NULL; //Reset the character used to echo
                inputReady2 = false;
                continue;
            }
            x = NULL; //Reset the character used to echo
            inputReady2 = false;

            putstr("\n\r");
            controlByte = EEPROM_WRITE | (( blockNumber >> 8) << 1);
            blockNumber &= 0x00FF;
            startBit();
            asm(" nop");
            //Write address to read  from EEPROM
            sendByte(controlByte);
            asm(" nop");

            sendByte(blockNumber);
            asm(" nop");

            startBit();
            asm(" nop");
            //Read data from EEPROM
            sendByte((controlByte + 1));
            asm(" nop");
//            P6->DIR &= ~BIT7;
//            asm(" nop");
            int j = 0, k = 0;
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
                    if( k != (endAddress - readAddress))
                    {
                        ack();
                        asm(" nop");
                    }
                    else
                        nack();
                }
                putstr("\n\r");
                memset(addressConvert, '\0', 8*sizeof(char)); //Reset the Buffer
            }
            asm(" nop");
            stopBit();
            asm(" nop");
            eereset();
        }
        else if (x == 'm')
        {
            x = NULL;  //Resetting echo character
            printMenu();
        }

        else if (x == 'i')
        {
            x = NULL;  //Resetting echo character
            startBit();
            sendByte(0x41);
            uint8_t portRead = receiveByte();
            ack();
            stopBit();
            snprintf(expanderInput, 8, "%X",portRead);
            putstr("\n\r");
            putstr("Input : ");
            putstr(expanderInput);
            memset(expanderInput, '\0', 8*sizeof(char)); //Reset the Buffer
            startBit();
            sendByte(0x40);
            portRead = (portRead <<1) + 1;
            sendByte(portRead);
            stopBit();
            x = NULL;
        }
        if ( interruptCheck == true)
        {
            putstr("\n\rInterrupt detected\n\r");
            interruptCheck = false;
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
    if(inputReady1 || inputReady2)
        readCheck = true;
}

void PORT1_IRQHandler(void)
{
    // Toggling the output on the LED
    if(P1->IFG & BIT5)
    {
        interruptCheck = true;
    }
    P1->IFG &= ~BIT5;
}
