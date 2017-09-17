// Author: 				Edmond Chuc
// Date created:	12/09/2017
// File: 					utilities.h
// Description:		Utilities/helper functions

// Blocks for numLoops in milliseconds.
void util_DelayMs(unsigned int numLoops);

void util_DelayUs(unsigned int numLoops);

// Writes a char to terminal
void util_write_char(unsigned char c);

void util_write_char_dec(unsigned int number);

void print_time(int A, int B);

int difference(int a, int b);

