// Author: 				Edmond Chuc
// Date created:	12/09/2017
// File: 					setup.c
// Description:		Setup functions for UART, GPIO, Interrupts, etc.

#include "registers.h"
#include "utilities.h"

// Setup GPIO on port B, pins 2, 3, 4
void setup_GPIO(void)
{
	// enable/wait for clock to stabilise
	SYSCTL_RCGCGPIO |= 0x2;	// enable clock for port B
	while((SYSCTL_PRGPIO & 0x2) != 0x2) {}; // wait for clock to stabilise
	util_DelayMs(50);	// delay for 50 milliseconds in case clock is not stable
		
	// set data direction
	GPIO_PORT_B_DIR &= ~0xC;	// input on pins 2, 3
	GPIO_PORT_B_DIR |= 0x10;	// output on pin 4
	
	// set regular port/alternate function
	GPIO_PORT_B_AFSEL |= 0xC;	// alternate function on pins 2, 3
	
	// configure port control
	GPIO_PORT_B_PCTL &= ~0xFFF00;	// regular GPIO for pins 2, 3, 4
		
	// enable digital I/O
	GPIO_PORT_B_DEN |= 0x1C;	// set digital I/O on pins 2, ,3 4
}

void setup_UART(void)
{
	
}
