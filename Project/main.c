// Author: 				Edmond Chuc
// Date created:	12/09/2017
// File: 					main.c
// Description:		The main loop of the program. 

#include "setup.h"
#include "registers.h"
#include "utilities.h"

int TimeA;	// save the time for TimerA?
int TimeB;	// save the time for TimerB?

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
		util_DelayMs(1000);
	}
}

void TM3_Rise()
{
	TimeA = TIMER_3_TAV & 0xFFFF;
	//util_write_char('-');
	TIMER_3_ICR |= 0x4;	// event trigger clear
}

void TM3_Fall()
{
	TimeB = TIMER_3_TBV & 0xFFFF;
	//util_write_char('.');
	TIMER_3_ICR |= 0x400; // event trigger clear
	
	//print_time(TimeA, TimeB);
	int diff = difference(TimeA, TimeB);
	if(diff < 7100 && diff > 3900)
	{
		util_write_char('O');
		util_write_char('b');
		util_write_char('j');
		util_write_char('e');
		util_write_char('c');
		util_write_char('t');
		util_write_char(' ');
		util_write_char('d');
		util_write_char('e');
		util_write_char('t');
		util_write_char('e');
		util_write_char('c');
		util_write_char('t');
		util_write_char('e');
		util_write_char('d');
		util_write_char('!');
		util_write_char(' ');
	}
}


