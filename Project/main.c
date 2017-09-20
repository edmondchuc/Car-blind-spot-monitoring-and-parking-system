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

int Time1A;
int Time1B;
int Time2A;
int Time2B;

int leftObject = 0;
int rightObject = 0;

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


void Buzz(int numOfBeeps, int delay);

int main(void)
{
	
//	setup_UART();	// no longer used, only used for testing
	
	
	
	setup_GPIO();
	
	setup_interrupt();
	
	setup_timer();
	
	
	
	while(1)	// prevent from ending program.
	{
		//enable_buzzer();
		//GPIO_PORT_A_DATA |= 0x4;	// TEST
		GPIO_PORT_A_DATA |= 0x10;
		util_DelayUs(11);
		
		GPIO_PORT_A_DATA &= ~0x10;
		util_DelayMs(100);
		//GPIO_PORT_A_DATA &= ~0x4; // TEST
		//disable_buzzer();
	}
}

void button_ISR()
{
	
	if((GPIO_PORT_A_RIS & 0x20) == 0x20)	// interrupt on pin 5
	{
		if(leftObject)
		{
			Buzz(3, 100);
		}
		GPIO_PORT_A_ICR |= 0x20;	// clear interrupt flag
	}
	else if((GPIO_PORT_A_RIS & 0x40) == 0x40)	// interrupt on pin 6
	{
		if(rightObject)
		{
			Buzz(3, 100);
		}
		GPIO_PORT_A_ICR |= 0x40;	// clear interrupt flag
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
		rightObject = 1;
	}
	else
	{
		GPIO_PORT_A_DATA &= ~0x8;	// turn off LED0 on pin 3
		rightObject = 0;
	}
}

void Buzz(int numOfBeeps, int delay)
{
	int i;
	for(i=0; i< numOfBeeps; i++)
	{
			enable_buzzer();
			util_DelayMs(delay);
			disable_buzzer();
			util_DelayMs(delay);
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
		leftObject = 1;
		
	}
	else
	{
		GPIO_PORT_A_DATA &= ~0x4;	// turn off LED3 on pin 2
		leftObject = 0;
	}
}

void TM1_Rise()
{
	Time1A = TIMER_1_TAV & 0xFFFF;
	//util_write_char('-');
	TIMER_1_ICR |= 0x4;	// event trigger clear
}

void TM1_Fall()
{
	Time1B = TIMER_1_TBV & 0xFFFF;
	//util_write_char('.');
	TIMER_1_ICR |= 0x400; // event trigger clear
	
	//print_time(TimeA, TimeB);
	int diff = difference(Time1A, Time1B);
	if(diff <= 5000 && diff > 3100)
	{
		//enable_buzzer();
		Buzz(5, 50);
	}
	else if(diff <= 7000 && diff > 5000)
	{
		Buzz(3, 100);
	}
	else if(diff < 9000 && diff > 7000)
	{
		//GPIO_PORT_A_DATA |= 0x4;	// turn on LED3 on pin 2
		//enable_buzzer();
		Buzz(2, 200);
		//util_DelayMs(1000);
	}
	else
	{
		//GPIO_PORT_A_DATA &= ~0x4;	// turn off LED3 on pin 2
		//disable_buzzer();
	}
}

