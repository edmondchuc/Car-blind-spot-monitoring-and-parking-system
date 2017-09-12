
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
	  ;BL GpioSetupClk  
	  ;BL GpioSetupPort
	  LDR R0, =SYSCTL_RCGCGPIO
	  LDR R1, [R0]
	  ORR R1, #0x2
	  STR R1, [R0]
	  
	  LDR R0, =SYSCTL_PRGPIO
portClkLoop	  
	  LDR R1, [R0]
	  AND R1, #0x2
	  CMP R1, #0x2
	  BNE portClkLoop
	  
	  MOV R3, #0x10
	  BL DelayMs
	  
	  LDR R0, =GPIO_B_BASE
	  
	  LDR R1, [R0, #GPIO_DIR]
	  BIC R1, #0xC
	  ORR R1, #0x10
	  STR R1, [R0, #GPIO_DIR]
	  
	  LDR R1, [R0, #GPIO_AFSEL]
	  ORR R1, #0xC
	  STR R1, [R0, #GPIO_AFSEL]
	  
	  LDR R1, [R0, #GPIO_PCTL]
	  LDR R2, =0xFFF00
	  BIC R1, R2
	  ORR R1, #0x7700
	  STR R1, [R0, #GPIO_PCTL]
	  
	  LDR R1, [R0, #GPIO_DEN]
	  ORR R1, #0x1C
	  STR R1, [R0, #GPIO_DEN]
	  
	  
      POP  {LR}
      BX LR

Setup_TIMER
      ; Setup required timer to detect rising (timer A) / falling (timer B)edge
      PUSH  {LR}
	  ;BL Init_Timers  
	  
	  LDR R0, =SYSCTL_RCGCTIMER
	  LDR R1, [R0]
	  ORR R1, #0x8
	  STR R1, [R0]
	  
	  LDR R0, =SYSCTL_PRTIMER
timerClkLoop
	  LDR R1, [R0]
	  AND R1, #0x8
	  CMP R1, #0x8
	  BNE timerClkLoop
	  
	  MOV R3, #0x10
	  BL DelayMs
	  
	  CPSID I
	  
	  LDR R0, =TIMER3_BASE
	  
	  LDR R1, [R0, #TIMER_CTL]
	  LDR R2, =0x101
	  BIC R1, R2
	  STR R1, [R0, #TIMER_CTL]
	  
	  LDR R1, [R0, #TIMER_CFG]
	  MOV R1, #0x4
	  STR R1, [R0, #TIMER_CFG]
	  
	  LDR R1, [R0, #TIMER_TAMR]
	  BIC R1, #8
	  ORR R1, #7
	  STR R1, [R0, #TIMER_TAMR]
	  
	  LDR R1, [R0, #TIMER_TBMR]
	  BIC R1, #8
	  ORR R1, #7
	  STR R1, [R0, #TIMER_TBMR]
	  
	  LDR R1, [R0, #TIMER_CTL]
	  LDR R2, =0xC0C
	  BIC R1, R2
	  ORR R1, #0x400
	  STR R1, [R0, #TIMER_CTL]
	  
	  
	  LDR R1, [R0, #TIMER_TAILR]
	  MOV R1, #0xFFFF
	  STR R1, [R0, #TIMER_TAILR]
	  
	  LDR R1, [R0, #TIMER_TBILR]
	  MOV R1, #0XFFFF
	  STR R1, [R0, #TIMER_TBILR]
	  
	  LDR R1, [R0, #TIMER_IMR]
	  LDR R2, =0x404
	  ORR R1, R2
	  STR R1, [R0, #TIMER_IMR]
	  
	  LDR R1, =NVIC_EN1
	  LDR R2, [R1]
	  ORR R2, #(3<<3)
	  STR R2, [R1]
	  
	  LDR R1, [R0, #TIMER_ICR]
	  LDR R2, =0x404
	  ORR R1, R2
	  STR R1, [R0, #TIMER_ICR]
	  
	  LDR R1, [R0, #TIMER_CTL]
	  LDR R2, =0x101
	  ORR R1, R2
	  STR R1, [R0, #TIMER_CTL]
	  
	  CPSIE I
	  
      POP  {LR}
      BX LR



Rise_ISR	; --- TIMER A ---
      PUSH  {LR}
	  ;BL MyISRup
	  
	  MOV R3, #'-'
	  BL Write_Char
	  
	  LDR R0, =TIMER3_BASE
	  LDR R1, [R0, #TIMER_ICR]
	  ORR R1, #4
	  STR R1, [R0, #TIMER_ICR]
	  
      POP  {LR}
      BX LR

Fall_ISR	; --- TIMER B ---
      PUSH  {LR}
       ;BL MyISRdown
	   
	  MOV R3, #'.'
	  BL Write_Char
	  
	  LDR R0, =TIMER3_BASE
	  LDR R1, [R0, #TIMER_ICR]
	  ORR R1, #0x400
	  STR R1, [R0, #TIMER_ICR]
	   
      POP  {LR}
      BX LR

     
       ALIGN      
       END  
