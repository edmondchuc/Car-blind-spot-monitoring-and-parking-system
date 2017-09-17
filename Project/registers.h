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
	
// GPIO port A 0x40004000
#define GPIO_PORT_A_DIR (*((volatile unsigned long *) 0x40004400))
#define GPIO_PORT_A_AFSEL (*((volatile unsigned long *) 0x40004420))
#define GPIO_PORT_A_PCTL (*((volatile unsigned long *) 0x4000452C))
#define GPIO_PORT_A_DEN (*((volatile unsigned long *) 0x4000451C))
#define GPIO_PORT_A_DATA (*((volatile unsigned long *) 0x400043FC))

// Timer clock
#define SYSCTL_RCGCTIMER (*((volatile unsigned long *) 0x400FE604))
#define SYSCTL_PRTIMER (* ((volatile unsigned long *) 0x400FEA04))
	
// Timer3 0x40033000
#define TIMER_3_CTL (* ((volatile unsigned long *) 0x4003300C))
#define TIMER_3_CFG (* ((volatile unsigned long *) 0x40033000))
#define TIMER_3_TAMR (* ((volatile unsigned long *) 0x40033004))
#define TIMER_3_TBMR (* ((volatile unsigned long *) 0x40033008))
#define TIMER_3_TAILR (* ((volatile unsigned long *) 0x40033028))
#define TIMER_3_TBILR (* ((volatile unsigned long *) 0x4003302C))
#define TIMER_3_IMR (* ((volatile unsigned long *) 0x40033018))
#define TIMER_3_ICR (* ((volatile unsigned long *) 0x40033024))
#define TIMER_3_TAV (* ((volatile unsigned long *) 0x40033050))
#define TIMER_3_TBV (* ((volatile unsigned long *) 0x40033054))

// NVIC
#define NVIC_EN1 (* ((volatile unsigned long *) 0xE000E104))


// Timer0 0x40036000
#define TIMER_0_CTL (* ((volatile unsigned long *) 0x4003000C))
#define TIMER_0_CFG (* ((volatile unsigned long *) 0x40030000))
#define TIMER_0_TAMR (* ((volatile unsigned long *) 0x40030004))
#define TIMER_0_TBMR (* ((volatile unsigned long *) 0x40030008))
#define TIMER_0_TAILR (* ((volatile unsigned long *) 0x40030028))
#define TIMER_0_TBILR (* ((volatile unsigned long *) 0x4003002C))
#define TIMER_0_IMR (* ((volatile unsigned long *) 0x40030018))
#define TIMER_0_ICR (* ((volatile unsigned long *) 0x40030024))

// NVIC
#define NVIC_EN0 (* ((volatile unsigned long *) 0xE000E100))

// UART SYSCTL
#define SYSCTL_RCGUART (* ((volatile unsigned long *) 0x400FE618))
#define SYSCTL_PRUART (* ((volatile unsigned long *) 0x400FEA18))
	
// UART0
#define UART_0_CTL (*((volatile unsigned long*) 0x4000C030))
#define UART_0_IBRD (*((volatile unsigned long*) 0x4000C024))
#define UART_0_FBRD (*((volatile unsigned long*) 0x4000C028))
#define UART_0_LCRH (*((volatile unsigned long*) 0x4000C02C))
#define UART_0_FR (*((volatile unsigned long *)0x4000C018)) 
#define UART_0_DR (*((volatile unsigned long *) 0x4000C000))
