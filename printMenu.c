/*
 * printMenu.c
 *
 *  Created on: 11-Nov-2019
 *      Author: Rahul
 */

#include "myIncludes.h"

char uiLines[80] = "\n\r-------------------------------------------------\n\r";
char messages[7][80] = {" Enter w to write a byte ", " Enter r to read a byte ", " Enter h to hex dump ", " Enter p to page write ", " Enter i for port expander ", " Enter x for reset ", " Enter m for main menu "};

void printMenu()
{
    int i;
    putstr(uiLines);
    putstr("\n\r");
    for ( i = 0; i < 7; i++)
    {
        putstr(messages[i]);
        putstr("\n\r");
    }
    putstr(uiLines);
    putstr("\n\r");
}


