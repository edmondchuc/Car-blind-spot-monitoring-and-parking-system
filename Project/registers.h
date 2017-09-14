// Author: 				Edmond Chuc
// Date created:	12/09/2017
// File: 					registers.h
// Description:		All #defines of register addresses.

// GPIO clock
#define SYSCTL_RCGCGPIO (*((volatile unsigned long *)0x400FE608))
#define SYSCTL_PRGPIO (*((volatile unsigned long *)0x400FEA08))
	
// GPIO port B 0x40005000
#define GPIO_PORT_B_DIR (*((volatile unsigned long *) 0x40005400))
#define GPIO_PORT_B_AFSEL (*((volatile unsigned long *) 0x40005420))
#define GPIO_PORT_B_PCTL (*((volatile unsigned long *) 0x4000552C))
#define GPIO_PORT_B_DEN (*((volatile unsigned long *) 0x4000551C))

#define GPIO_PORT_B_DATA (*((volatile unsigned long *) 0x400053FC))

// Timer clock
#define SYSCTL_RCGCTIMER (*((volatile unsigned long *) 0x400FE604))
#define SYSCTL_PRTIMER (* ((volatile unsigned long *) 0x400FEA04))
	
// Timer0 0x40036000
#define TIMER_0_CTL (* ((volatile unsigned long *) 0x4003000C))
#define TIMER_0_CFG (* ((volatile unsigned long *) 0x40030000))
#define TIMER_0_TAMR (* ((volatile unsigned long *) 0x40030004))
#define TIMER_0_TAILR (* ((volatile unsigned long *) 0x40030028))
#define TIMER_0_IMR (* ((volatile unsigned long *) 0x40030018))
#define TIMER_0_ICR (* ((volatile unsigned long *) 0x40030024))

// NVIC
#define NVIC_EN0 (* ((volatile unsigned long *) 0xE000E100))
