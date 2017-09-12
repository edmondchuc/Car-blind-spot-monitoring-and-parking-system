#include "registers.h"
extern void DelayMs(unsigned int);
extern void Delayy(unsigned int);
extern void DisableInterrupts(void);
extern void EnableInterrupts(void);
extern void Initialize_UART0(void);
extern void Test_UART(void);  
extern void Write_Char(unsigned char);
extern unsigned char Read_Char(void);
extern void ASetupGPIOF(void);
extern void ASetupPWM(void);

#define GPIO_PORTX_IM	(*((volatile unsigned long *)0x40025410))
#define GPIO_PORTX_IS	(*((volatile unsigned long *)0x40025404))
#define GPIO_PORTX_IEV	(*((volatile unsigned long *)0x4002540C))
#define GPIO_PORTX_IBE	(*((volatile unsigned long *)0x40025408))
#define NVIC_PRI7	(*((volatile unsigned long *)0xE000E428))
#define GPIO_PORTX_RIS	(*((volatile unsigned long *)0x40025414))
#define GPIO_PORTX_ICR	(*((volatile unsigned long *)0x4002541C))

#define SYSCTL_RCGCTIMER 	(*((volatile unsigned long *)0x400FE604))
#define SYSCTL_PRTIMER (*((volatile unsigned long *)0x400FEA04))
#define TIMER1_CFG 	(*((volatile unsigned long *)0x40031000))
#define TIMER1_TAMR	(*((volatile unsigned long *)0x40031004))
#define TIMER1_TAILR	(*((volatile unsigned long *)0x40031028))

void setupGPIO_F(void);
void setup_PWM(void);
void setup_INTERRUPT(void);

int main(void)
{	  
    //unsigned int a=0;
    //unsigned int b=0;
    unsigned int c=2000;
	  //unsigned char ch;
    
		Initialize_UART0();
//		Test_UART();
//	  DelayMs(500);
//		ch = Read_Char();
//		Write_Char(ch);
	
		//ASetupGPIOF();
		setupGPIO_F();
		
		setup_INTERRUPT();
	
	  //ASetupPWM();
		setup_PWM();
		
		TIMER1_TAMATCH = 0x6000;
	  Delayy(c);
		
		TIMER1_TAMATCH = 0xFFFE;
	  Delayy(c);
		//TIMER1_CTL &=~1;       //disable timer
    while(1);
}

void GPIOF_Handler(void)
{
		if((GPIO_PORTX_RIS & 1) == 1)	// PIN 0
		{
				if(TIMER1_TAMATCH < 58000)
				{
						TIMER1_TAMATCH += 5000;
						//Write_Char('1');
						DelayMs(10);
						GPIO_PORTX_ICR |= 1;
				}
				else
				{
						Write_Char('T');
						Write_Char('o');
						Write_Char('o');
						Write_Char(' ');
						Write_Char('S');
						Write_Char('m');
						Write_Char('a');
						Write_Char('l');
						Write_Char('l');
						Write_Char('!');
						DelayMs(10);
						GPIO_PORTX_ICR |= 1;
				}
		}
		else if((GPIO_PORTX_RIS & 16) == 16)	// PIN 4
		{
				//Write_Char('4');
				if(TIMER1_TAMATCH > 5100)
				{
						TIMER1_TAMATCH -= 5000;
						DelayMs(10);
						GPIO_PORTX_ICR |= 16;
				}
				else
				{
						Write_Char('T');
						Write_Char('o');
						Write_Char('o');
						Write_Char(' ');
						Write_Char('L');
						Write_Char('a');
						Write_Char('r');
						Write_Char('g');
						Write_Char('e');
						Write_Char('!');
						DelayMs(10);
						GPIO_PORTX_ICR |= 16;
				}
		}
}

void setupGPIO_F(void)
{
		SYSCTL_RCGCGPIO |= 32;
		while((SYSCTL_PRGPIO & 32) != 32){};
		GPIOF_LOCK = 0x4C4F434B;
		GPIOF_CR |= 0x1;
		GPIOF_DIR &= ~0x11;
		GPIOF_DIR |= 0xE;
		GPIOF_AFSEL &= ~0x1B;
		GPIOF_AFSEL |= 0x4;
		GPIOF_PUR |= 0x11;
		GPIOF_PCTL &= ~0xFFFFF;
		GPIOF_PCTL |= 0x700;
		GPIOF_DEN |= 0x1F;
}

void setup_INTERRUPT(void)
{
		DisableInterrupts();
	  GPIO_PORTX_IM &= ~0x11;
	  GPIO_PORTX_IS &= ~0x11;
		GPIO_PORTX_IEV |= 0x11;
		GPIO_PORTX_IBE &= ~0x11;
		NVIC_EN0 |= (1<<30);
//		NVIC_PRI7 &= ~(7<<21);
//		NVIC_PRI7 |= (3<<21);
		GPIO_PORTX_IM |= 0x11;
		EnableInterrupts();
}

void setup_PWM(void)
{
		SYSCTL_RCGCTIMER |= 0x2;
		while((SYSCTL_PRTIMER & 0x2) != 0x2){};
		TIMER1_CTL &= ~0x1;
		TIMER1_CFG |= 0x4;
		TIMER1_TAMR |= 0xA;
		TIMER1_TAMR &= ~4;
		TIMER1_TAILR |= 0xFFFF;
		TIMER1_CTL |= 0x1;
}
