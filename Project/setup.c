// Author: 				Edmond Chuc
// Date created:	12/09/2017
// File: 					setup.c
// Description:		Setup functions for UART, GPIO, Interrupts, etc.

#include "registers.h"
#include "utilities.h"

// enable/disable interrupts
extern void DisableInterrupts(void);
extern void EnableInterrupts(void);

// --------------------------------------------------------------------------
//																--- GPIO SETUP ---
// --------------------------------------------------------------------------
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
	
	// configure port control/column number for alternate function
	GPIO_PORT_B_PCTL &= ~0xFFF00;	// clear bits in pins 2, 3, 4
	GPIO_PORT_B_PCTL |= 0x7700;		// set port control column 7 for timers. 
		
	// enable digital I/O
	GPIO_PORT_B_DEN |= 0x1C;	// set digital I/O on pins 2, ,3 4
}

// --------------------------------------------------------------------------
//															--- TIMER SETUP ---
// --------------------------------------------------------------------------
// Setup Timer0 A with input capture: edge-time mode
// detect rising & falling with TimerA edge
void setup_timer(void)
{
	// enable/wait for clock to stabilise
	SYSCTL_RCGCTIMER |= 0x1;	// enable Timer0 clock
	while((SYSCTL_PRTIMER & 0x1) != 0x1) {};	// wait for clock to stabilise
	util_DelayMs(50);	// delay for 50 milliseconds in case clock is not stable
	
	// disable interrupts to safely change settings
	DisableInterrupts();
		
	// configures further the timer operation and enabling other features
	TIMER_0_CTL &= ~0x1;	// disable Timer A
	
	// configures global operation of timer
	TIMER_0_CFG |= 0x4;	// select 16-bit configuration
		
	// configures Timer A operating modes
	TIMER_0_TAMR &= ~0x8;	// TAAMS - alternate mode, select capture mode enabled
	TIMER_0_TAMR |= 0x7;	// TACMR - edge-time mode enabled
												// TAMR - capture mode enabled
	
	// set TAEVENT definition of active edges
	TIMER_0_CTL &= ~0xC; // set event mode in rising edge
		
	// set starting preload values
	TIMER_0_TAILR |= 0xFFFF; // load max preload value for start timer
	
	// set interrupt settings
	// note: priority left as default
	TIMER_0_IMR |= 0x1;	// enable interrupts for capture mode event
	
	// enable correct interrupt in NVIC_ENn register
	// IRQ no. = 19
	// 19/32 = 0 rem. 19
	// EN0 with bits 19 shifted
	NVIC_EN0 |= (1<<19);	// set-enable interrupt register
	
	// clear trigger flags
	TIMER_0_ICR |= 0x4;	// clearing CAEINT, which clears CAERIS in RIS/MIS reg.
	
	// start timer & begin count-down from preload value
	TIMER_0_CTL |= 0x1;	// enable and start counting on Timer 0A
	
	// enable interrupts after setup
	EnableInterrupts();
}

void setup_UART(void)
{
	
}
