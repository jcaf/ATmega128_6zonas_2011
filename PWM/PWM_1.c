/*
 * PWM_1.c
 *
 * Created: 22/02/2012 06:58:23 p.m.
 *  Author: jcaf
 */ 
#include "Includes/InitializeAllModules.h"
	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	/*
	BOTTOM The counter reaches the BOTTOM when it becomes 0x0000.

	MAX The counter reaches its MAXimum when it becomes 0xFFFF (decimal 65535).

	TOP The counter reaches the TOP when it becomes equal to the highest value in the 
		count sequence. The TOP value can be assigned to be one of the fixed values: 
		0x00FF, 0x01FF, or 0x03FF, or to the value stored in the OCRnA or ICRn 
		Register. The assignment is dependent of the mode of operation.
	
	
	The fast Pulse Width Modulation or fast PW M mode (W GMn3:0 = 5,6,7,14, or 15) 
	The PW M resolution for fast PW M can be fixed to 8-bit, 9-bit, or 10-bit, or defined by either ICRn
	or OCRnA. The minimum resolution allowed is 2-bit (ICRn or OCRnA set to 0x0003), and the
	maximum resolution is 16-bit (ICRn or OCRnA set to MAX). The PW M resolution in bits can be
	calculated by using the following equation:
	RFPWM
	TOP 1+()log
	2()log
	-----------------------------------=
	
		he PW M frequency for the output can be calculated by the following equation:
	The N variable represents the prescaler divider (1, 8, 64, 256, or 1024).
	*/
	//volatile word DUTY_CYCLE_COUNTER=0;
//extern volatile word DUTY_CYCLE_COUNTER;
	//
	//void Test6PWM(void)
	void InitPWM(void)
	{
		/*
		OCR1A = 512+ (512/2) ;
		OCR1B = 512;
		OCR1C = 512/2;//+(512/2);
		OCR3A = 512;
		OCR3B = 512;
		OCR3C = 512;
		*/
	
		OCR1A = OCR1B = OCR1C = OCR3A = OCR3B = OCR3C = 1023;// DUTY_CYCLE_COUNTER;//; //512;//1023;//0;//512/2;//1023;
		
		TCNT1 = 0;
		TCNT3 = 0;
		
		//  Compare Output Mode, Fast PWM -> non-inverting mode
		//WGMn3:WGMn0 = 7 
		//0 1 1 1 Fast PWM, 10-bit 0x03FF BOTTOM TOP
		
		TCCR1A = (1<<COM1A1) | (0<<COM1A0) | (1<<COM1B1) | (0<<COM1B0)| (1<<COM1C1) | (0<<COM1C0) | (1<<WGM11) | (1<<WGM10);
		TCCR3A = (1<<COM3A1) | (0<<COM3A0) | (1<<COM3B1) | (0<<COM3B0)| (1<<COM3C1) | (0<<COM3C0) | (1<<WGM31) | (1<<WGM30);
		
		//clock select con preescaler = NO PREESCALING! -> Freq PWM @ 16MHz= 15.625KHz
		TCCR1B = (0<<WGM13)  | (1<<WGM12) | (0<<CS12) | (0<<CS11) | (1<<CS10) ;
		TCCR3B = (0<<WGM33)  | (1<<WGM32) | (0<<CS32) | (0<<CS31) | (1<<CS30)  ;
		
		//Estado inicial de pins de salidas, forzar...a 0
		
		TCCR1C = (1<<FOC1A) | (1<<FOC1B) | (1<<FOC1C) ;
		TCCR3C = (1<<FOC3A) | (1<<FOC3B) | (1<<FOC3C) ;
		
		//DDRX:
		ConfigOutputPin(DDRB,PB5);//OC1A
		ConfigOutputPin(DDRB,PB6);//OC1B
		ConfigOutputPin(DDRB,PB7);//OC1C
		//
		ConfigOutputPin(DDRE,PE3);//OC3A
		ConfigOutputPin(DDRE,PE4);//OC3A
		ConfigOutputPin(DDRE,PE5);//OC3A
	}