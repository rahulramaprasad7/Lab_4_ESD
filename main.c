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
    memset(buffer, '\0', 10*sizeof(char));                              //Reset the Buffer
    i = 0;
    while (x != '\n')                                                   //Take input until the user enters 'enter'
    {
        if ( i == 5)                                                    //Take only 3 digits
        {
            buffer[i] = '\0';
            memset(buffer, '\0', 10*sizeof(char));                      //Reset the Buffer
            putstr(wrongStringInput);                                   //Print wrong input message
            printMenu();                                                //Print the main menu
        return 10000;                                                   //Return the error code
        }
        else if ( readCheck == true)                                    //Check if the boolean is true to take input
        {
            if( (x >= '0' && x <= '9') || (x >= 'A' && x <= 'F') || (x >= 'a' && x <= 'f') || x == '\n' || x == '\r')  //Take only valid inputs
            {
                buffer[i] = x;                                          //Add the entered character to buffer
                i++;                                                    //Increment the buffer
//                readCheck = false;
            }
            else if (x != NULL)                                         //Check for invalid characters apart from the NULLwhen user is entering information
            {
                putstr("\n\rInavlid Input\n\r");
                printMenu();
                readCheck = false;
                x = NULL;
                return 10000;
            }
            readCheck = false;                                          //Change the input read boolean to false
        }
    }
    sscanf(buffer, "%X", &readValue);                                   //Convert the input into hex value
    x = NULL;                                                           //Reset the input character
    return (readValue);                                                 //Return the input value
}
void main(void)
{
    P1->DIR = ~(uint8_t) BIT5;                                          //Set the INT pin for IO Expander as input
    P1->OUT = BIT5;                                                     //Enable the alternate function for pull up
    P1->REN = BIT5;                                                     // Enable pull-up resistor (P1.5 output high)
    P1->SEL0 = 0;
    P1->SEL1 = 0;
    P1->IES = BIT5;                                                     // Interrupt on high-to-low transition
    P1->IFG = 0;                                                        // Clear all P1 interrupt flags
    P1->IE = BIT5;                                                      // Enable interrupt for P1.5

    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		                    // stop watchdog timer

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

    //Print the main menu
    printMenu();

    while(1)
    {
        //Write mode
        if ( x == 'w')
        {
            x = NULL;                                                   //Reset the character used to echo
            putstr("\n\rEnter the address\n\r");
            inputReady1 = true;                                         //Set the boolean for input to true to take user input
            blockNumber = getstr();                                     //Get the user input in AAA format
            if(blockNumber == 10000)                                    //Check if the input function returned an error
                continue;
            if (blockNumber > 0x7FF)                                    //Check if the input is out of range
            {
                x = NULL;                                               //Reset the character used to echo
                putstr("\n\rEntered word address is not in range of the EEPROM address\n\r");
                printMenu();                                            //Print the menu again
                inputReady1 = false;                                    //Change the input ready boolean to false to stop taking input
                continue;
            }
            inputReady1 = false;                                        //Change the input ready boolean to false to stop taking input

            putstr("\n\rEnter the data\n\r");
            inputReady2 = true;                                         //Set the boolean for input to true to take user input for data
            data = getstr();                                            //Get data input from user
            if(data == 10000)                                           //Check if teh input function returns error code
                continue;
            if (data > 0xFF)                                            //Check if data is out of range
            {
                x = NULL;                                               //Reset the character used to echo
                putstr("\n\rEntered data is not between 0 and FF");
                printMenu();                                            //Print the main menu
                inputReady2 = false;                                    //Change the input ready boolean to false to stop taking input
                continue;
            }
            x = NULL;                                                   //Reset the character used to echo
            inputReady2 = false;                                        //Change the input ready boolean to false to stop taking input

            controlByte = EEPROM_WRITE | (( blockNumber >> 8) << 1);    //Mask the user input format to get block number with device address
            blockNumber &= 0x00FF;                                      //Mask the user input to get word address
            startBit();                                                 //Send start bit to write
            write(controlByte, blockNumber, data);                      //Call the byte read function
            //Acknowledgement polling
//            while (ackCheck != true)
//            {
//                startBit();
//                sendByte(controlByte);
//            }
            stopBit();                                                  //Call the stop bit function
            putstr("\n\r");
//            eereset();
            printMenu();                                                //Call the main menu function
        }

        //Random read
        else if (x == 'r')
        {
            x = NULL;                                                   //Reset the character used to echo
            putstr("\n\rEnter the address\n\r");
            inputReady1 = true;
            blockNumber = getstr();                                     //Get the user input
            if(blockNumber == 10000)                                    //Check if input function returns error code
                continue;
            readAddress = blockNumber;
            if ((blockNumber > 0x7FF))                                  //Check if input is out of bounds
            {
                x = NULL;                                               //Reset the character used to echo
                putstr("\n\rEntered word address is not in range of the EEPROM address\n\r");
                printMenu();
                inputReady1 = false;
                continue;
            }
            inputReady1 = false;

            controlByte = EEPROM_WRITE | (( blockNumber >> 8) << 1);    //Mask the input to find block number
            blockNumber &= 0x00FF;                                      //Mask the input to find word address
            startBit();                                                 //Send start bit
            uint8_t byteRead = read(controlByte, blockNumber);          //Store received byte
            snprintf(readConvert, 8, "%X",byteRead);                    //Convert the read byte to string to display
            snprintf(addressConvert, 8, "%X",readAddress);              //Convert the read address to string to display
            putstr("\n\r");
            putstr(addressConvert);                                     //Print the address
            putstr(":");
            putstr(readConvert);                                        //Print the data
            memset(readConvert, '\0', 8*sizeof(char));                  //Reset the Buffer
            memset(addressConvert, '\0', 8*sizeof(char));               //Reset the Buffer
            stopBit();                                                  //Send stop bit
//            x = NULL; //Reset the character used to echo
//            eereset();
            printMenu();                                                //Print main menu
        }

        //EERESET from AN709
        else if (x == 'x')
        {
            x = NULL; //Reset the character used to echo
            eereset();                                                  //Call the eereset function
            putstr("\n\r");
            putstr("Reset successful\n\r");
            printMenu();                                                //Print main menu
        }

        //Page write
        else if(x == 'p')
        {
            x = NULL; //Reset the character used to echo
            putstr("\n\rEnter the address\n\r");                        //Take starting address
            inputReady1 = true;
            blockNumber = getstr();
            if(blockNumber == 10000)
                continue;
            if ((blockNumber > 0x7EF))
            {
                x = NULL; //Reset the character used to echo
                putstr("\n\rEntered word address is not in range of the EEPROM address\n\r");
                printMenu();
                inputReady1 = false;
                continue;
            }

            if (blockNumber % 16 != 0)
            {
                x = NULL; //Reset the character used to echo
                putstr("\n\rEntered word address is not divisible by 16\n\r");
                printMenu();
                inputReady1 = false;
                continue;
            }
            x = NULL; //Reset the character used to echo
            inputReady1 = false;

            putstr("\n\rEnter the data\n\r");                           //Take input data
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

            controlByte = EEPROM_WRITE | (( blockNumber >> 8) << 1);    //Mask input to get block number
            blockNumber &= 0x00FF;                                      //Mask input to get word address
            startBit();                                                 //Send start bit
            pageWrite(controlByte, blockNumber, data);                  //Call page write
            stopBit();                                                  //Send stop bit
            x = NULL; //Reset the character used to echo
//            eereset();
            printMenu();                                                //Print main menu
        }

        //Hex dump
        else if(x == 'h')
        {
            x = NULL;                                                   //Reset echo character
            putstr("\n\rEnter the starting address\n\r");
            inputReady1 = true;
            blockNumber = getstr();                                     //Take user input for starting address
            if(blockNumber == 10000)                                    //Check for error code
                continue;
            readAddress = blockNumber;
            if ((readAddress > 0x7FF))                                  //Check if input is out of bounds
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
            temp = getstr();                                            //Take user input for Ending address
            if(temp == 10000)
                continue;
            endAddress = temp;
            if (endAddress > 0x7FF)
            {
                putstr("\n\rEntered address is out of range\n\r");
                printMenu();
                x = NULL; //Reset the character used to echo
                inputReady2 = false;
                continue;
            }

            if (endAddress < readAddress)                               //Check if end address is lesser than start address
            {
                putstr("\n\rEntered address is lesser than start address\n\r");
                printMenu();
                x = NULL; //Reset the character used to echo
                inputReady2 = false;
                continue;
            }
            x = NULL; //Reset the character used to echo
            inputReady2 = false;

            putstr("\n\r");
            controlByte = EEPROM_WRITE | (( blockNumber >> 8) << 1);    //Mask input to get block number
            blockNumber &= 0x00FF;                                      //Mask input to get word address
            startBit();                                                 //Send start bit
            asm(" nop");
            //Write address to read  from EEPROM
            sendByte(controlByte);                                      //Send the controlByte
            asm(" nop");

            sendByte(blockNumber);                                      //Send word address
            asm(" nop");

            startBit();                                                 //Send start bit again
            asm(" nop");
            //Read data from EEPROM
            sendByte((controlByte + 1));                                //Send control byte with Read bit
            asm(" nop");

            //Print the read characters 16 bytes per line according to the format given in the question
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
                    memset(readConvert, '\0', 8*sizeof(char));          //Reset the Buffer
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
                memset(addressConvert, '\0', 8*sizeof(char));            //Reset the Buffer
            }
            asm(" nop");
            stopBit();                                                   //Send stop bit
            asm(" nop");
            eereset();
            printMenu();                                                 //Print main menu
        }

        //Print main menu
        else if (x == 'm')
        {
            x = NULL;                                                   //Resetting echo character
            printMenu();
        }

        //IO expander
        else if (x == 'i')
        {
            x = NULL;                                                   //Resetting echo character
            startBit();
            sendByte(0x41);                                             //Send IO expander address to read
            uint8_t portRead = receiveByte();                           //Read the pins
            ack();                                                      //Send Ack
            stopBit();                                                  //Send stop
            snprintf(expanderInput, 8, "%X",portRead);                  //Print the read value
            putstr("\n\r");
            putstr("Input : ");
            putstr(expanderInput);                                      //Print on serial terminal
            memset(expanderInput, '\0', 8*sizeof(char));                //Reset the Buffer
            startBit();                                                 //Send start bit
            sendByte(0x40);                                             //Send IO Expander address to write
            portRead = (portRead <<1) + 1;                              //Left shift input by 1 and add 1 and send it
            sendByte(portRead);
            stopBit();                                                  //Stop bit
//            x = NULL;
            printMenu();                                                //Print main menu
        }
        if ( interruptCheck == true)                                    //Check if IO expander interrupts
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
        x = EUSCI_A0->RXBUF;                                            //Receive a character
    }
    EUSCI_A0->TXBUF = x;                                                //Transmit the character
    if(inputReady1 || inputReady2)                                      //Set input read flags
        readCheck = true;
}

void PORT1_IRQHandler(void)
{
    //Interrupt handler for IO Expander interrupt
    if(P1->IFG & BIT5)
    {
        interruptCheck = true;
    }
    P1->IFG &= ~BIT5;
}
