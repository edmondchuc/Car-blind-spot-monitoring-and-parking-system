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
// Setup GPIO on port B, pins 2, 3, 4, 6, 7
void setup_GPIO(void)
{
	// enable/wait for clock to stabilise
	SYSCTL_RCGCGPIO |= 0x2;	// enable clock for port B
	while((SYSCTL_PRGPIO & 0x2) != 0x2) {}; // wait for clock to stabilise
	util_DelayMs(50);	// delay for 50 milliseconds in case clock is not stable
		
	// set data direction
	GPIO_PORT_B_DIR &= ~0xCC;	// input on pins 2, 3, 6, 7
	GPIO_PORT_B_DIR |= 0x10;	// output on pin 4
	
	// set regular port/alternate function
	GPIO_PORT_B_AFSEL |= 0xCC;	// alternate function on pins 2, 3, 6, 7
	
	// configure port control/column number for alternate function
	GPIO_PORT_B_PCTL &= ~0xFF0FFF00;	// clear bits in pins 2, 3, 4, 6, 7
	GPIO_PORT_B_PCTL |= 0x77007700;		// set port control column 7 for timers. 
		
	// enable digital I/O
	GPIO_PORT_B_DEN |= 0xDC;	// set digital I/O on pins 2, ,3, 4, 6, 7
}

// --------------------------------------------------------------------------
//															--- TIMER SETUP ---
// --------------------------------------------------------------------------
// Setup Timer3 A, B with input capture: edge-time mode
// detect rising & falling with TimerA edge, TimerB respectively
void setup_timer(void)
{
	// enable/wait for clock to stabilise
	SYSCTL_RCGCTIMER |= 0x9;	// enable Timer0, 3 clock
	while((SYSCTL_PRTIMER & 0x9) != 0x9) {};	// wait for clock to stabilise
	util_DelayMs(50);	// delay for 50 milliseconds in case clock is not stable
	
	// disable interrupts to safely change settings
	DisableInterrupts();
		
	// configures further the timer operation and enabling other features
	TIMER_0_CTL &= ~0x101;
	TIMER_3_CTL &= ~0x101;	// disable Timer A, B
	
	// configures global operation of timer
	TIMER_0_CFG |= 0x4;
	TIMER_3_CFG |= 0x4;	// select 16-bit configuration
		
	// configures Timer A operating modes
	TIMER_0_TAMR &= ~0x8;
	TIMER_0_TAMR |= 0x7;
	TIMER_0_TBMR &= ~0x8;
	TIMER_0_TBMR |= 0x7;
	TIMER_3_TAMR &= ~0x8;	// TAAMS - alternate mode, select capture mode enabled
	TIMER_3_TAMR |= 0x7;	// TACMR - edge-time mode enabled
												// TAMR - capture mode enabled
	TIMER_3_TBMR &= ~0x8; // TBAMS - " "
	TIMER_3_TBMR |= 0x7;	// TBCMR - " "
												// TBMR - " "
	
	// set TAEVENT definition of active edges
	TIMER_0_CTL &= ~0xC0C;
	TIMER_0_CTL |= 0x400;
	TIMER_3_CTL &= ~0xC0C;	// clear bits in TAEVENT for Timer A and B
													// this also sets Timer A to positive edge (rise)
	TIMER_3_CTL |= 0x400;		// set negative edge for Timer B (fall)
		
	// set starting preload values for Timer A, B
	TIMER_0_TAILR |= 0xFFFF;
	TIMER_0_TBILR |= 0xFFFF;
	TIMER_3_TAILR |= 0xFFFF; // load max preload value for start timer
	TIMER_3_TBILR |= 0xFFFF; // " "
	
	// set interrupt settings for Timer A, B
	// note: priority left as default
	TIMER_0_IMR |= 0x404;
	TIMER_3_IMR |= 0x404;	// enable interrupts for capture mode event
	
	// enable correct interrupt in NVIC_ENn register
	// IRQ no. = 19
	// 19/32 = 0 rem. 19
	// EN0 with bits 19 shifted
	NVIC_EN0 |= (1<<19);
	NVIC_EN0 |= (1<<20);
	NVIC_EN1 |= (1<<3);	// set-enable interrupt register
	NVIC_EN1 |= (1<<4);
	
	// clear trigger flags for both Timer A, B
	TIMER_0_ICR |= 0x404;
	TIMER_3_ICR |= 0x404;	// clearing CAEINT, which clears CAERIS in RIS/MIS reg.
	
	// start Timer A, B & begin count-down from preload value
	TIMER_0_CTL |= 0x101;
	TIMER_3_CTL |= 0x101;	// enable and start counting on Timer 0A, B
	
	// enable interrupts after setup
	EnableInterrupts();
}

void setup_UART(void)
{
	
}
