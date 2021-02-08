/*************************************************************************************
ATmega16 TIMER/COUNTER 0

Autor: Juan Carlos Agüero Flores

Las definiciones y las macros pueden tomar en cualquier momento nuevos valores
validos para cualquier punto del programa siempre y cuando se corresponda
i.e:	CS02_00_CLCK_64 = PRESCALER_TCNT0_64
en cuanto a una nueva configuración en TCCR0 (Timer Counter Control Register0)

Macros del PRE-Procesador

int()	Truncates a floating point expression to integer (ie discards fractional part)
frac() Extracts fractional part of a floating point expression (ie discards integer part).
q7() Converts a fractional floating point expression to a form suitable for the FMUL/FMULS/FMULSU instructions. (sign + 7-bit fraction)
q15() Converts a fractional floating point to the form returned by the FMUL/FMULS/FMULSY instructions (sign + 15-bit fraction).
abs()

				TCNT0 Registers:

1-	TimerCounter Control Register TCCR
2-	TCNT0
3-	TimerInterrupt Flag Register TIFR
4-	Timer Interrupt Mask Register TIMSK
5-	Output Compare Register OCR0
6-	Special Function IO Register SFIOR	-> Bit 0 PSR10:Prescaler Reset Timer/Counter1 & Timer/Counter0

El maximo valor de temporización Tov para:
#define TCNT0_VALUE(Tov,PRESCALER_TCNT0_DECIMAL) (int( ((MAX_TCNT0+1) - ( (Tov)*FREQ_SYSTEM)/PRESCALER_TCNT0_DECIMAL) ) )

con MAX_TCNT0=255, FREQ_SYSTEM = 16MHz y PRESCALER_TCNT0_DECIMAL=1024 es de 16*mS

PARA 8MHZ es 32*ms


*************************************************************************************/
#ifndef _TCNT0_H_
#define _TCNT0_H_

	#define CLKi_o (FREQ_SYSTEM)	//ATmega datasheet usa CLKi/o para referirse a la frecuencia CPU / externa para mi

	#define BOTTOM_TCNT0 = 0x00
	//#define TOP_TCNT0 	= 0xFF
	#define MAX_TCNT0   = 0xFF

	//TCCR0	Timer/Counter Control Register 0 - ORing Setup
	//----------------------------------------------------
	//FOC0 WGM00 COM01 COM00 - WGM01   CS02 CS01 CS00
	//   0    0    0		0	-	0		0	0    0	 =0x00
	//   0    1    0     0   -   0   	0	0	 0	 =0x40
	//   0  	 0	  0		0	-	1   	0   0    0   =0x08
	//   0  	 1	  0		0	-	1   	0   0    0   =0x48


	#define WGM01_0_MODE_0_NORMAL 				(0x00)
	#define WGM01_0_MODE_1_PWM_PHASE_CORRECT 	(0x40)
	#define WGM01_0_MODE_2_CTC 				    (0x08)
	#define WGM01_0_MODE_3_FAST_PWM 			(0x48)

	//.EQU WGM01_0 = MODE_0_NORMAL -> si hago esto, estaria limitando todas los posibles cambios que
	//que podria efectuar en run-time....

	//Definiciones cuando WGM01:0 es igual a NORMAL o CTC MODE (Non-PWM)
	#define COM01_COM00_NORMAL_OC0_DISCONNECTED (0x00)
	#define COM01_COM00_TOGGLE_OC0 			    (0x10)
	#define COM01_COM00_CLEAR_OC0 				(0x20)
	#define COM01_COM00_SET_OC0 				(0x30)

	//Compare Output Mode, Fast PWM Mode
	//#define COM01_COM00_NORMAL_OC0_DISCONNECTED=  (0x00)	//Se repite
	#define COM01_COM00_RESERVED_FAST_PWM		(0x10)
	#define COM01_COM00_CLEAR_OC0_SET_OC0_TOP	(0x20)
	#define COM01_COM00_SET_OC0_CLEAR_OC0_TOP	(0x30)


	//Compare Output Mode, Phase Correct PWM Mode
	//#define COM01_COM00_NORMAL_OC0_DISCONNECTED=  (0x00)	//Se repite
	#define COM01_COM00_RESERVED_PHASE_C_PWM	(0x10)
	#define COM01_COM00_CLEAR_UP_SET_DOWN		(0x20)
	#define COM01_COM00_SET_UP_CLEAR_DOWN		(0x30)

	//Clock Select bits
	//------------------------------------------------------------------
	//If external pin modes are used for the Timer/Counter0, transitions on the T0 pin will
	//clock the counter even if the pin is configured as an output. This feature allows software
	//control of the counting.
	//
	#if defined __AVR_ATmega128__ || defined __AVR_ATmega64__
		//OJO: mega64/128 no disponen de pin T0 = entrada de clock, en cambio, tienen entrada de cristal 32.768KHz
		#define CS02_00_NO_CLOCK_SOURCE 			(0x00)
		#define CS02_00_CLK_NO_PRESCALING 			(0x01)
		#define CS02_00_CLCK_8 						(0x02)
		#define CS02_00_CLCK_32 					(0x03)
		#define CS02_00_CLCK_64 					(0x04)
		#define CS02_00_CLCK_128 					(0x05)
		#define CS02_00_CLCK_256  					(0x06)
		#define CS02_00_CLCK_1024 					(0x07)
	
		//ALIAS:
		#define TCNT0_STOPPED (CS02_00_NO_CLOCK_SOURCE)

		//Obviamente esto estas declaraciones son validas para TCNT0 modo Temporizador
		#define PRESCALER_TCNT0_1 		(1)
		#define PRESCALER_TCNT0_8 		(8)
		#define PRESCALER_TCNT0_32 		(32)
		#define PRESCALER_TCNT0_64 		(64)
		#define PRESCALER_TCNT0_128 	(128)
		#define PRESCALER_TCNT0_256 	(256)
		#define PRESCALER_TCNT0_1024	(1024)

	#else	
	//#elif defined __AVR_ATmega8__ || defined __AVR_ATmega16__  || defined __AVR_ATmega32__ 
	//Por confirmarrrr
		#define CS02_00_NO_CLOCK_SOURCE 			(0x00)
		#define CS02_00_CLK_NO_PRESCALING 			(0x01)
		#define CS02_00_CLCK_8 						(0x02)
		#define CS02_00_CLCK_64 					(0x03)
		#define CS02_00_CLCK_256 					(0x04)
		#define CS02_00_CLCK_1024 					(0x05)
		#define CS02_00_EXTERN_CLK_T0_FALLING_EDGE 	(0x06)
		#define CS02_00_EXTERN_CLK_T0_RISING_EDGE 	(0x07)
		//ALIAS:
		#define TCNT0_STOPPED (CS02_00_NO_CLOCK_SOURCE)

		//Obviamente esto estas declaraciones son validas para TCNT0 modo Temporizador
		#define PRESCALER_TCNT0_1 		(1)
		#define PRESCALER_TCNT0_8 		(8)
		#define PRESCALER_TCNT0_64 		(64)
		#define PRESCALER_TCNT0_256		(256)
		#define PRESCALER_TCNT0_1024	(1024)

	#endif

	//**************************************************************
	//	#define TCNT0_VALUE(Tov,PRESCALER_TCNT0_DECIMAL) (int( ((MAX_TCNT0+1) - ( (Tov)*FREQ_SYSTEM)/PRESCALER_TCNT0_DECIMAL) ) )
	//
	//	Ejmp: de ésta manera se efectúa una llamada a la macro TCNT0_VALUE
	//
	//	ldi		temp0,TCNT0_VALUE(5*mS, PRESCALER_TCNT0_1024)
	//	out		TCNT0,temp0
	//
	//	NOTA:
	//	Esta macro es re-usable para cualquier punto del programa, solo debe cumplirse
	//	i.e:	CS02_00_CLCK_64 = PRESCALER_TCNT0_64
	//
	//**************************************************************
//#define TCNT0_VALUE(Tov,PRESCALER_TCNT0_DECIMAL) (int( ((MAX_TCNT0+1) - ( (Tov)*FREQ_SYSTEM)/PRESCALER_TCNT0_DECIMAL) ) )

#define TCNT0_VALUE(Tov,PRESCALER_TCNT0_DECIMAL) ( (byte)( ((MAX_TCNT0+1) - ( (Tov)*FREQ_SYSTEM)/PRESCALER_TCNT0_DECIMAL) ) )
	//Implicit float->int conversion cause a warning and the fractional part is discarded.
	//Both integers and floating point numbers have 64-bit internal representation.

	/*********************************************************************
	TIME_FOR_CTC
	------------
	No olvidar configurar previamente CS02_00_CLCK_XXXX para TCCR0
		#define CS02_00_CLCK_8 						(0x02)
		#define CS02_00_CLCK_64 					(0x03)
		#define CS02_00_CLCK_256 					(0x04)
		#define CS02_00_CLCK_1024 					(0x05)
	**********************************************************************/
	//#define	TIME_FOR_CTC	(5.0*ms)
	//
	//#define KTE_TIME_FOR_CTC(TimeForCTC, PRESCALER_TCNT0_XXXX ) (int( ((TimeForCTC)*FREQ_SYSTEM)/ PRESCALER_TCNT0_XXXX ) )
	
	
	/***************************************************************************************
	
	***************************************************************************************/
	#define TKTE_CTC_TCNT0 (5*ms)
	
	/***************************************************************************************
	
	***************************************************************************************/
	#define _SYS_TIMMER_GRL1_			(5*ms)	//Asignado a TCNT0
    /***************************************************************************************
	
	***************************************************************************************/
	#define KTE_TIME_FOR_CTC(TimeForCTC, PRESCALER_TCNT0_XXXX ) ((byte)( ((TimeForCTC)*FREQ_SYSTEM)/ PRESCALER_TCNT0_XXXX ) )


	//**************************************************************
	//StopTCNT0 Macro
	//
	//
	//**************************************************************
/*
	.MACRO StopTCNT0

		push	temp0

		in		temp0,TCCR0
		andi	temp0,0xF8	//TCNT0_STOPPED=CS02:00 =000
		out		TCCR0,temp0

		pop	temp0

	.ENDMACRO
*/
    void InitTCNT0(void);
#endif

