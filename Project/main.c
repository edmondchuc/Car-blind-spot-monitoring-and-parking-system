// Author: 				Edmond Chuc
// Date created:	12/09/2017
// File: 					main.c
// Description:		The main loop of the program. 

#include "setup.h"
#include "registers.h"
#include "utilities.h"

// --------------------------------------------------------------------------
//															--- Global Variables ---
// --------------------------------------------------------------------------

// Timer values for each interrupt
// gets stored and calculated to 
// determine distance for each
// ultrasonic sensor
int Time0A;
int Time0B;
int Time3A;	
int Time3B;	
int Time1A;
int Time1B;
int Time2A;
int Time2B;

// Booleans used by the blind-spot sensors
// if there is an object, value is 1,
// else, value is 0
int leftObject = 0;
int rightObject = 0;

// --------------------------------------------------------------------------
//															--- Function Prototypes ---
// --------------------------------------------------------------------------

// nothing

// --------------------------------------------------------------------------
//															     --- Main  ---
// --------------------------------------------------------------------------
int main(void)
{
//	setup_UART();	// no longer used, only used for initial testing
	
	// call the setup functions
	setup_GPIO();
	setup_interrupt();
	setup_timer();
	
	// Block
	while(1)	// prevent from ending program.
	{
		GPIO_PORT_A_DATA |= 0x10;	// Send data to the sensors (high)
		util_DelayUs(11);					// required minimum delay for the ultrasonic sensors to work
		
		GPIO_PORT_A_DATA &= ~0x10;	// Stop sending data (low)
		util_DelayMs(100);					// The frequency of updating the sensor data
	}
}

// The interrupt service routine (ISR) for buttons (momentary clickers)
void button_ISR()
{
	if((GPIO_PORT_A_RIS & 0x20) == 0x20)	// interrupt on pin 5
	{
		if(leftObject)	// if there is an object on the left blind-spot sensor
		{
			Buzz(3, 100);
		}
		GPIO_PORT_A_ICR |= 0x20;	// clear interrupt flag
	}
	else if((GPIO_PORT_A_RIS & 0x40) == 0x40)	// interrupt on pin 6
	{
		if(rightObject)	// if there is an object on the right blind-spot sensor
		{
			Buzz(3, 100);
		}
		GPIO_PORT_A_ICR |= 0x40;	// clear interrupt flag
	}
	
}


// ISR for Timer0A
void TM0_Rise()
{
	Time0A = TIMER_0_TAV & 0xFFFF;	// Store the current value
	TIMER_0_ICR |= 0x4;	// event trigger clear
}

// ISR for Timer0B
void TM0_Fall()
{
	Time0B = TIMER_0_TBV & 0xFFFF;	// Store the current value
	TIMER_0_ICR |= 0x400; // event trigger clear
	int diff = difference(Time0A, Time0B);	// difference between Timer0A interrupt & Timer0B
	if(diff < 12000 && diff > 3200)	// if distance is within these bounds
	{
		GPIO_PORT_A_DATA |= 0x8;	// turn on LED0 on pin 3
		rightObject = 1;					// notify other ISR an object has been detected
		if(diff < 4800 && diff > 3200)
		{
			Buzz(5, 50);	// produce sound
		}
	}
	else
	{
		GPIO_PORT_A_DATA &= ~0x8;	// turn off LED0 on pin 3
		rightObject = 0;					// notify other ISR no object detected
	}
}

// ISR for Timer3A
void TM3_Rise()
{
	Time3A = TIMER_3_TAV & 0xFFFF;	// Store the current value
	TIMER_3_ICR |= 0x4;	// event trigger clear
}

// ISR for Timer3B
void TM3_Fall()
{
	Time3B = TIMER_3_TBV & 0xFFFF;	// Store the current value
	TIMER_3_ICR |= 0x400; // event trigger clear
	int diff = difference(Time3A, Time3B);	// difference between Timer3A interrupt & Timer3B
	if(diff < 12000 && diff > 3200)	// if distance is within these bounds
	{
		GPIO_PORT_A_DATA |= 0x4;	// turn on LED3 on pin 2
		leftObject = 1;						// notify other ISR an object has been detected
		if(diff < 4800 && diff > 3200)
		{
			Buzz(5, 50);	// produce sound
		}
	}
	else
	{
		GPIO_PORT_A_DATA &= ~0x4;	// turn off LED3 on pin 2
		leftObject = 0;						// notify other ISR no object detected
	}
}

// ISR for Timer1A
void TM1_Rise()
{
	Time1A = TIMER_1_TAV & 0xFFFF;	// Store the current value
	TIMER_1_ICR |= 0x4;	// event trigger clear
}

// ISR for Timer1B
void TM1_Fall()
{
	Time1B = TIMER_1_TBV & 0xFFFF;	// Store the current value
	TIMER_1_ICR |= 0x400; // event trigger clear
	int diff = difference(Time1A, Time1B);	// difference between Timer1A interrupt & Timer1B
	if(diff <= 5000 && diff > 3100)	// if distance is within these bounds
	{
		Buzz(5, 50);	// produce sound
	}
	else if(diff <= 7000 && diff > 5000)	// if distance is within these bounds
	{
		Buzz(3, 100);	// produce sound
	}
	else if(diff < 9000 && diff > 7000)	// if distance is within these bounds
	{
		Buzz(2, 200);		// produce sound
	}
	else
	{
		// nothing
	}
}

