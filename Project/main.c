// Author: 				Edmond Chuc
// Date created:	12/09/2017
// File: 					main.c
// Description:		The main loop of the program. 

#include "setup.h"
#include "registers.h"
#include "utilities.h"

double TimeA;	// save the time for TimerA?
double TimeB;	// save the time for TimerB?

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
	Initialize_UART0();	// TODO: replace
	Test_UART();	// TODO: replace
	
	
	setup_GPIO();
	
	//Setup_TIMER();	// TODO: replace
	setup_timer();
	

	
	while(1)	// prevent from ending program.
	{
		GPIO_PORT_B_DATA ^= 0x10;
		util_DelayMs(500);
	}
}
