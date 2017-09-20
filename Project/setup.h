// Author: 				Edmond Chuc
// Date created:	12/09/2017
// File: 					setup.h
// Description:		Setup functions for UART, GPIO, Interrupts, etc.


// --------------------------------------------------------------------------
//																--- GPIO SETUP ---
// --------------------------------------------------------------------------
// Setup GPIO on port B, pins 2, 3, 6, 7
// Setup GPIO on port A, pins 0, 1 for UART0
// Setup GPIO on port A, pin 2 for LED3, pin 3 for LED0
// Setup GPIO on port B, pins 4, 5
// Setup GPIO on port B, pins 0 for PWM
// Setup GPIO on port A, pins 5, 6 for clicker input
void setup_GPIO(void);

// --------------------------------------------------------------------------
//															--- TIMER SETUP ---
// --------------------------------------------------------------------------
// Setup Timer3 A, B with input capture: edge-time mode
// detect rising & falling with TimerA edge, TimerB respectively
void setup_timer(void);

// --------------------------------------------------------------------------
//															--- UART SETUP ---
// --------------------------------------------------------------------------
// setup UART0 on port A, pin 0 (Rx), 1 (Tx)
void setup_UART(void);

// --------------------------------------------------------------------------
//															--- Interrupt SETUP ---
// --------------------------------------------------------------------------
// setup GPIO inputs on port A, pins 5, 6
void setup_interrupt(void);
