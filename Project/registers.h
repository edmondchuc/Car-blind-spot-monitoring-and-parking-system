// Author: 				Edmond Chuc
// Date created:	12/09/2017
// File: 					registers.h
// Description:		All #defines of register addresses.

// GPIO
#define SYSCTL_RCGCGPIO (*((volatile unsigned long *)0x400FE608))
#define SYSCTL_PRGPIO (*((volatile unsigned long *)0x400FEA08))
	
// GPIO PORT B
#define GPIO_PORT_B_DIR (*((volatile unsigned long *) 0x400053FC))
#define GPIO_PORT_B_AFSEL (*((volatile unsigned long *) 0x4000420))
#define GPIO_PORT_B_PCTL (*((volatile unsigned long *) 0x4000552C))
#define GPIO_PORT_B_DEN (*((volatile unsigned long *) 0x4000551C))

#define GPIO_PORT_B_DATA (*((volatile unsigned long *) 0x400053FC))
