/*
 * printMenu.c
 *
 *  Created on: 11-Nov-2019
 *      Author: Rahul
 */

#include "myIncludes.h"

char uiLines[80] = "\n\r-------------------------------------------------\n\r";
char messages[6][80] = {" Enter w to write a byte ", " Enter r to read a byte ", " Enter h to hex dump ", " Enter p to page write "," Enter x for reset "," Enter b to go back to main menu\n\r"};
//char newLine [2] = {'\n','\r'};

void printMenu()
{
    int i;
    putstr(uiLines);
    putstr(newLine);
    for ( i = 0; i < 6; i++)
    {
        putstr(messages[i]);
        putstr(newLine);
    }
    putstr(uiLines);
    putstr(newLine);
}


