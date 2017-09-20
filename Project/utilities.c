// Author: 				Edmond Chuc
// Date created:	12/09/2017
// File: 					utilities.c
// Description:		Utilities/helper functions

#include "registers.h"
#include "utilities.h"

// Blocks for numLoops in milliseconds
void util_DelayMs(unsigned int numLoops)
{
	unsigned int lp=0;
	unsigned int i=0;
	
	for(lp=0; lp<numLoops; lp++)
	{
		for(i=0; i<4000; i++) {};
	}
}

// Blocks for numLoops in microseconds
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
	while((UART_0_FR & 0x20) != 0) {};	// while data not ready, block
	UART_0_DR |= c;											// write to terminal
}

// Converts an int to char and writes to terminal
void util_write_char_dec(unsigned int number)
{
		int i = 1;
	
		// if number is zero
		if(number == 0)
		{
			util_write_char('0');
			return;
		}
    
		// determine how large the number is
    while(i < number)
    {
        i = i * 10;
    }
    
    i = i / 10;
    
		// find current position and print until done
    while(i > 0)
    {
				util_write_char(number / i + '0');
        
        number = number % i;
        
        i = i / 10;
    }
}

// Prints the time difference between A and B
// Takes into account wrapping of reload values
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

// Finds the difference of a and b
// Returns the absolute value of the difference
// Takes into account wrapping of reload values
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

// Turn on buzzer
void enable_buzzer()
{
	TIMER_2_TAILR = 0x6000;
	TIMER_2_TAMATCH = 0x600;
}

// Turn off buzzer
void disable_buzzer()
{
	TIMER_2_TAILR = 0x6000;
	TIMER_2_TAMATCH = 0x6000 ;
}


// Turns on the buzzer. First parameter takes an int for the number of desired beeps.
// Second parameter takes an int for the delay between each beeps.
void Buzz(int numOfBeeps, int delay)
{
	int i;
	for(i=0; i< numOfBeeps; i++)
	{
			enable_buzzer();
			util_DelayMs(delay);
			disable_buzzer();
			util_DelayMs(delay);
	}
}
