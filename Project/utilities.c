// Author: 				Edmond Chuc
// Date created:	12/09/2017
// File: 					utilities.c
// Description:		Utilities/helper functions

#include "registers.h"
#include "utilities.h"

// Blocks for numLoops in milliseconds.
void util_DelayMs(unsigned int numLoops)
{
	unsigned int lp=0;
	unsigned int i=0;
	
	for(lp=0; lp<numLoops; lp++)
	{
		for(i=0; i<4000; i++) {};
	}
}

void util_DelayUs(unsigned int numLoops)
{	
	unsigned int lp=0;
	unsigned int i=0;
	
	for(lp=0; lp<numLoops; lp++)
	{
		for(i=0; i<4; i++) {};
	}
}

// Writes a char to terminal
void util_write_char(unsigned char c)
{
	// accessing UART# FR
	while((UART_0_FR & 0x20) != 0) {};
	UART_0_DR |= c;
}

void util_write_char_dec(unsigned int number)
{
		int i = 1;
	
		if(number == 0)
		{
			util_write_char('0');
			return;
		}
    
    while(i < number)
    {
        i = i * 10;
    }
    
    i = i / 10;
    
    while(i > 0)
    {
        //printf("%c", number / i + '0');
				util_write_char(number / i + '0');
        
        number = number % i;
        
        i = i / 10;
    }
}

void print_time(int A, int B)
{
	util_write_char('T');
	util_write_char('i');
	util_write_char('m');
	util_write_char('e');
	util_write_char(':');
	util_write_char(' ');
	
	util_write_char_dec(difference(A, B));
}

// calculate the difference of Timer values with wrapping
int difference(int a, int b)
{
    int max = 0xFFFF;
    if(a > b)
    {
        return a - b;
    }
    else
    {
        return max - b + a;
    }
}
