
       AREA    MYCODE, CODE, READONLY, ALIGN=2
       
       INCLUDE Registers.s	  
		   
	   IMPORT TimeA
	   IMPORT TimeB
       IMPORT  OUT2DEC
	   IMPORT  Read_Char   ; char returned in R3
       IMPORT  Write_Char  ; char must be in R3 before calling
       IMPORT  DelayMs	   ; number of ms must be stored in R4 before calling
	   IMPORT  DelayUs	   
	   IMPORT  Init_Timers
       IMPORT  GpioSetupClk
       IMPORT  GpioSetupPort 
	   IMPORT  OUT2DEC
	   IMPORT  MyISRup
       IMPORT  MyISRdown
		   
	   EXPORT  Setup_TIMER
       EXPORT  SetupGPIO
	   EXPORT  Rise_ISR
	   EXPORT  Fall_ISR

SetupGPIO
      ; Setup gpio port on pins B4-B6 for trigger and echo lines
      PUSH  {LR}
	  BL GpioSetupClk  
	  BL GpioSetupPort
	  
      POP  {LR}
      BX LR

Setup_TIMER
      ; Setup required timer to detect rising (timer A) / falling (timer B)edge
      PUSH  {LR}
	  BL Init_Timers  
	  
      POP  {LR}
      BX LR



Rise_ISR
      PUSH  {LR}
	  BL MyISRup
      POP  {LR}
      BX LR

Fall_ISR
      PUSH  {LR}
       BL MyISRdown
      POP  {LR}
      BX LR

     
       ALIGN      
       END  
