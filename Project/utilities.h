// Author: 				Edmond Chuc
// Date created:	12/09/2017
// File: 					utilities.h
// Description:		Utilities/helper functions

// Blocks for numLoops in milliseconds.
void util_DelayMs(unsigned int numLoops);

// Blocks for numLoops in microseconds
void util_DelayUs(unsigned int numLoops);

// Writes a char to the terminal
void util_write_char(unsigned char c);

// Converts an int to char and writes to terminal
void util_write_char_dec(unsigned int number);

// Prints the time difference between A and B
// Takes into account wrapping of reload values
void print_time(int A, int B);

// Finds the difference of a and b
// Returns the absolute value of the difference
// Takes into account wrapping of reload values
int difference(int a, int b);

// Turn on buzzer
void enable_buzzer(void);

// Turn off buzzer
void disable_buzzer(void);

// Turns on the buzzer. First parameter takes an int for the number of desired beeps.
// Second parameter takes an int for the delay between each beeps.
void Buzz(int numOfBeeps, int delay);
