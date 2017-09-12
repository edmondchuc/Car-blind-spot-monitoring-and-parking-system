; main.s

       THUMB
       AREA    DATA, ALIGN=2
TimeA  SPACE  4
TimeB  SPACE  4
	
       ALIGN          
       AREA    |.text|, CODE, READONLY, ALIGN=2
	   INCLUDE Registers.s	  
       EXPORT  Start
	   EXPORT TimeA
	   EXPORT TimeB
           
	   IMPORT  Initialize_UART0
       IMPORT  OUT2DEC
	   IMPORT  Read_Char   ; char returned in R3
       IMPORT  Write_Char  ; char must be in R3 before calling
       IMPORT  DelayMs	   ; number of ms must be stored in R4 before calling
	   IMPORT  DelayUs	   
	   IMPORT  Test_UART 
	   IMPORT  Setup_TIMER
       IMPORT  SetupGPIO
		   
Start  
       BL  Initialize_UART0    ; setup UART0 (38400, 8, 2 stop, odd parity, noflow)
	   BL  Test_UART         ; prints GO then echos chars in terminal until q pressed.
      
	   BL  SetupGPIO    
       BL  Setup_TIMER  

Spin
       MOV  R4, #11

	   ;LDR R0, =GPIO_B_DATA
       ;LDR R1, [R0]
       ;EOR R1, #0x10
       ;STR R1, [R0]
       ;BL DelayUs	   
	   
	   LDR R0, =GPIO_B_DATA
	   LDR R1, [R0]
	   ORR R1, #0x10
	   STR R1, [R0]
	   BL DelayUs
	   
	   BIC R1, #0x10
	   STR R1, [R0]
	   MOV R4, #1000
	   BL DelayMs

	   B  Spin



       ALIGN      
       END  
           
           