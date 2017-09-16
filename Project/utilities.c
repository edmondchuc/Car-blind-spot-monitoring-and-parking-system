// Author: 				Edmond Chuc
// Date created:	12/09/2017
// File: 					utilities.c
// Description:		Utilities/helper functions

#include "registers.h"

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

// Writes a char to terminal
void util_write_char(unsigned char c)
{
	// accessing UART# FR
	while((UART_0_FR & 0x20) != 0) {};
	UART_0_DR |= c;
}
