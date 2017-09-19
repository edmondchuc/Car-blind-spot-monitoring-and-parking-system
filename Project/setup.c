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
// Setup GPIO on port B, pins 2, 3, 6, 7 for Timer0, Timer3 (left/right side sensors)
// Setup GPIO on port A, pins 0, 1 for UART0
// Setup GPIO on port A, pin 2 for LED3, pin 3 for LED0
// Setup GPIO on port A, pin 4 for output - trigger ultrasonic sensors
// Setup GPIO on port B, pins 4, 5 for Timer1
void setup_GPIO(void)
{
	// enable/wait for clock to stabilise
	SYSCTL_RCGCGPIO |= 0x3;	// enable clock for port B, A
	while((SYSCTL_PRGPIO & 0x3) != 0x3) {}; // wait for clock to stabilise
	util_DelayMs(50);	// delay for 50 milliseconds in case clock is not stable
		
	// set data direction
	GPIO_PORT_B_DIR &= ~0xCC;	// input on pins 2, 3, 6, 7 for Timer0, Timer3
	GPIO_PORT_A_DIR |= 0x10;		// output on pin 4 for sensor trigger
	GPIO_PORT_A_DIR	|= 0x1; 	// input on pin 0 for UART0
	GPIO_PORT_A_DIR &= ~0x2;	// output on pin 1 for UART0
	GPIO_PORT_A_DIR |= 0x4;		// input on pin 2 LED3
	GPIO_PORT_A_DIR |= 0x8;		// input on pin 3 LED0
	GPIO_PORT_B_DIR &= ~0x30;	// input on pins 4, 5, for Timer1
	
	// set regular port/alternate function
	GPIO_PORT_B_AFSEL |= 0xCC;	// alternate function on pins 2, 3, 6, 7
	GPIO_PORT_A_AFSEL	|= 0x3;		// alternate function on pins 0, 1
	GPIO_PORT_A_AFSEL &= ~0xC;	// set as regular port for pins 2, 3
	GPIO_PORT_A_AFSEL &= ~0x10;	// set as regular port for pin 4
	GPIO_PORT_B_AFSEL |= 0x30;	// alternate function on pins 4, 5 for Timer1
	
	// configure port control/column number for alternate function
	GPIO_PORT_B_PCTL &= ~0xFFFFFF00;	// clear bits in pins 2, 3, 4, 5 6, 7 for Timer0, Timer1, Timer2, Timer3
	GPIO_PORT_B_PCTL |= 0x77777700;		// set port control column 7 for timers.
	GPIO_PORT_A_PCTL &= ~0xFF; 	// clear bits in pins 0, 1
	GPIO_PORT_A_PCTL |= 0x11;		// set port control column 1 for UART0
	GPIO_PORT_A_PCTL &= ~0x4;		// set pin 2 as regular GPIO for LED3
	GPIO_PORT_A_PCTL &= ~0x8;		// set pin 3 as regular GPIO for LED0
	GPIO_PORT_A_PCTL &= ~0x10;	// set pin 4 as regular GPIO for ultrasonic trigger
	
		
	// enable digital I/O
	GPIO_PORT_B_DEN |= 0xCC;	// set digital I/O on pins 2, 3, 6, 7
	GPIO_PORT_A_DEN |= 0x3;		// set digital I/O on pins 0, 1
	GPIO_PORT_A_DEN |= 0xC;		// set digital I/O on pin 2, 3
	GPIO_PORT_A_DEN |= 0x10;	// set digital I/O on pin 4
	GPIO_PORT_B_DEN |= 0x30;	// set digital I/O on pin 4, 5
}

// --------------------------------------------------------------------------
//															--- TIMER SETUP ---
// --------------------------------------------------------------------------
// Setup Timer3 A, B with input capture: edge-time mode
// detect rising & falling with TimerA edge, TimerB respectively
void setup_timer(void)
{
	// enable/wait for clock to stabilise
	SYSCTL_RCGCTIMER |= 0xB;	// enable Timer0, Timer1, Timer3 clock
	while((SYSCTL_PRTIMER & 0xB) != 0xB) {};	// wait for clock to stabilise
	util_DelayMs(50);	// delay for 50 milliseconds in case clock is not stable
	
	// disable interrupts to safely change settings
	DisableInterrupts();
		
	// configures further the timer operation and enabling other features
	TIMER_0_CTL &= ~0x101;
	TIMER_3_CTL &= ~0x101;	// disable Timer A, B
	TIMER_1_CTL &= ~0x101;
	
	// configures global operation of timer
	TIMER_0_CFG |= 0x4;
	TIMER_3_CFG |= 0x4;	// select 16-bit configuration
	TIMER_1_CFG |= 0x4;
		
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
	TIMER_1_TAMR &= ~0x8;
	TIMER_1_TAMR |= 0x7;
	TIMER_1_TBMR &= ~0x8;
	TIMER_1_TBMR |= 0x7;
	
	// set TAEVENT definition of active edges
	TIMER_0_CTL &= ~0xC0C;
	TIMER_0_CTL |= 0x400;
	TIMER_3_CTL &= ~0xC0C;	// clear bits in TAEVENT for Timer A and B
													// this also sets Timer A to positive edge (rise)
	TIMER_3_CTL |= 0x400;		// set negative edge for Timer B (fall)
	TIMER_1_CTL &= ~0xC0C;
	TIMER_1_CTL |= 0x400;
		
	// set starting preload values for Timer A, B
	TIMER_0_TAILR |= 0xFFFF;
	TIMER_0_TBILR |= 0xFFFF;
	TIMER_3_TAILR |= 0xFFFF; // load max preload value for start timer
	TIMER_3_TBILR |= 0xFFFF; // " "
	TIMER_1_TAILR |= 0xFFFF;
	TIMER_1_TBILR |= 0xFFFF;
	
	// set interrupt settings for Timer A, B
	// note: priority left as default
	TIMER_0_IMR |= 0x404;
	TIMER_3_IMR |= 0x404;	// enable interrupts for capture mode event
	TIMER_1_IMR |= 0x404;
	
	// enable correct interrupt in NVIC_ENn register
	// IRQ no. = 19
	// 19/32 = 0 rem. 19
	// EN0 with bits 19 shifted
	NVIC_EN0 |= (1<<19);	// Timer0A
	NVIC_EN0 |= (1<<20); 	// Timer0B
	NVIC_EN1 |= (1<<3);		// Timer3A set-enable interrupt register
	NVIC_EN1 |= (1<<4);		// Timer3B
	NVIC_EN0 |= (1<<21);	// Timer1A
	NVIC_EN0 |= (1<<22);	// Timer1B
	
	// clear trigger flags for both Timer A, B
	TIMER_0_ICR |= 0x404;
	TIMER_3_ICR |= 0x404;	// clearing CAEINT, which clears CAERIS in RIS/MIS reg.
	TIMER_1_ICR |= 0x404;
	
	// start Timer A, B & begin count-down from preload value
	TIMER_0_CTL |= 0x101;
	TIMER_3_CTL |= 0x101;	// enable and start counting on Timer 0A, B
	TIMER_1_CTL |= 0x101;
	
	// enable interrupts after setup
	EnableInterrupts();
}

// setup UART0 on port A, pin 0 (Rx), 1 (Tx)
void setup_UART(void)
{
	// enable UAR01 clock
	SYSCTL_RCGUART |= 0x1;
	
	// wait for UART0 clock to stabilise
	while((SYSCTL_PRUART  & 0x1) != 0x1) {};
	util_DelayMs(50);
		
	// disable UART to change settings
	UART_0_CTL &= ~0x1;
	
	// Baud rate = 57600
	// 8 bit data
	// even parity
	// 1 stop
	// no flow control
	// set UART integer baud rate divisor
	UART_0_IBRD |= 34;
	
	// set UART fractional baud rate divisor
	UART_0_FBRD |= 46;
		
	// set line control register settings
	UART_0_LCRH |= 0x60; // set word length to 8 bits
	UART_0_LCRH &= ~0x8; // select 1 stop bit
	UART_0_LCRH |= 0x6; // select even parity and enable EPS
		
	// enable UART0
	UART_0_CTL |= 0x321; // enable UART, set prescaler as 8 and enable Rx, Tx
}
