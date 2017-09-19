// Author: 				Edmond Chuc
// Date created:	12/09/2017
// File: 					main.c
// Description:		The main loop of the program. 

#include "setup.h"
#include "registers.h"
#include "utilities.h"

// not used but to get rid of error from Belinda's mycode.o file
int TimeA;
int TimeB;

int Time0A;
int Time0B;
int Time3A;	// save the time for TimerA?
int Time3B;	// save the time for TimerB?

// Belinda's functions
extern void Initialize_UART0(void);
extern void OUT2DEC(void);
extern void Read_Char(void);	// char returned in R3
extern void Write_Char(void);	// char must be in R3 before calling
extern void DelayMs(void);		// number of ms must be stored in R4 before calling
extern void DelayUs(void);
extern void Test_UART(void);
extern void Setup_TIMER(void);
extern void SetupGPIO(void);




int main(void)
{
	//Initialize_UART0();	// TODO: replace
	//Test_UART();	// TODO: replace
	
	setup_UART();
	setup_GPIO();
	
	//Setup_TIMER();	// TODO: replace
	setup_timer();
	
	
	
	//__asm("MOV R3, #'M'");
	//int x = 15;
	//util_write_char_dec((x));
	util_write_char('G');
//	util_DelayMs(1000);
	util_write_char('O');
	util_write_char(' ');
////	util_DelayMs(1000);
//	util_write_char(' ');
//	util_write_char('t');
//	util_DelayMs(1000);
//	util_write_char('e');
//	util_DelayMs(1000);
//	util_write_char('s');
//	util_write_char('t');
	
	while(1)	// prevent from ending program.
	{
//		GPIO_PORT_B_DATA ^= 0x10;
//		util_DelayMs(1000);
		//util_write_char('F');
		
		GPIO_PORT_B_DATA |= 0x10;
		util_DelayUs(11);
		
		GPIO_PORT_B_DATA&= ~0x10;
		util_DelayMs(600);
	}
}

void TM0_Rise()
{
	Time0A = TIMER_0_TAV & 0xFFFF;
	//util_write_char('-');
	TIMER_0_ICR |= 0x4;	// event trigger clear
}

void TM0_Fall()
{
	Time0B = TIMER_0_TBV & 0xFFFF;
	//util_write_char('.');
	TIMER_0_ICR |= 0x400; // event trigger clear
	
	//print_time(TimeA, TimeB);
	int diff = difference(Time0A, Time0B);
	if(diff < 9000 && diff > 3200)
	{
		GPIO_PORT_A_DATA |= 0x8;	// turn on LED0 on pin 3
	}
	else
	{
		GPIO_PORT_A_DATA &= ~0x8;	// turn off LED0 on pin 3
	}
}

void TM3_Rise()
{
	Time3A = TIMER_3_TAV & 0xFFFF;
	//util_write_char('-');
	TIMER_3_ICR |= 0x4;	// event trigger clear
}

void TM3_Fall()
{
	Time3B = TIMER_3_TBV & 0xFFFF;
	//util_write_char('.');
	TIMER_3_ICR |= 0x400; // event trigger clear
	
	//print_time(TimeA, TimeB);
	int diff = difference(Time3A, Time3B);
	if(diff < 9000 && diff > 3200)
	{
		GPIO_PORT_A_DATA |= 0x4;	// turn on LED3 on pin 2
	}
	else
	{
		GPIO_PORT_A_DATA &= ~0x4;	// turn off LED3 on pin 2
	}
}


