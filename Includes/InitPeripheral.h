/*****************************************************************************************************
	InitSystems esta relacionado a la inicialización y configuración
	de los periféricos de uC

								Habilitación de Periféricos a Usar..
	Descomentar SOLO los periféricos que se necesiten, asi el InitPeripheral.c crecerá de acuerdo a esto.

*****************************************************************************************************/
#ifndef InitPeripheral_H_
#define InitPeripheral_H_

    /*--------------------------------------------------------------------------------------
					internals
	--------------------------------------------------------------------------------------*/
    //#define _TMR0_
    //#define _TMR1_
    //#define _TMR2_
	//#define _TMR3_
	//
    #define _TCNT0_
    //#define _TCNT1_
    //#define _TCNT2_
    //#define _TCNT3_
    //#define _CCP1_
    //#define _CCP2_
    #define _PWM_
    #define _USART_
    //#define _INT0_
    //#define _INT1_
    //#define _INT2_
    #define _EEPROM_
    #define _ADC_
    #define _I2C_
    //#define _SPI_
    //#define _USB_

    /*--------------------------------------------------------------------------------------
			externals
	--------------------------------------------------------------------------------------*/
	//#define _HC595_
	//#define _KEYBOARD_
    //#define _KEYBOARD_AT_PS2_
    //#define _LCD_ALPHANUMERIC_
	//#define  _ISD4003_04M_
	//#define _DS1307_
	#define _GLCD192X64_	
	#define _DS3231_
	#define _BUZZER_
	#define _RS485_
#define _KS108_	//esto es solo hasta que contruya mi propio driver al 100%
	#define _KEYBOARD_HANDLER_
    /*--------------------------------------------------------------------------------------
		common
	--------------------------------------------------------------------------------------*/
    //#define _ERRORS_
    #define _DELAYS_
	

      /***************************************************************************************************

      ***************************************************************************************************/

		#if defined _DELAYS_
			#if defined __ICCAVR__
				#include "Delays/Delays.h"
			#elif defined __GNUC__
				#define F_CPU (FREQ_SYSTEM)		//IMPORTANTE!!! Para <delay.h>
				#include <util/delay.h>
			#elif defined __PIC18__ || defined __PICC__
				//#include "Delays/pic/delay/delay.h"
				#include "Delays/DelayC/delay.h"
			#endif
		#endif

		#if defined _KEYBOARD_
				#include "Keyboard/Keyboard.h"		//uC directamente controla el teclado
				//#include "Keyboard/KeyBoardExt.h"		//uC direcciona a traves de I2C <-> ATmega16
		#endif

		#if defined _LCD_ALPHANUMERIC_
				#include "LCD/LCD_Alphanumeric.h"
				#include "LCDfx/LCDfx.h"
		#endif

		#if defined _USART_
				#include "USART/USART.h"
		#endif

		#if defined _PWM_
				#include "PWM/PWM.h"
		#endif

		#if defined _I2C_
				#include "I2C/I2C.h"
				#include "I2C/I2CCommonFx.h"	//add
		#endif

		#if defined _SPI_
				#include "SPI/SPI.h"
		#endif

		#if defined _ADC_
				#include "ADC/ADC.h"
		#endif

		#if defined _EEPROM_
				#include "EEPROM/EEPROM.h"
				#include <avr/eeprom.h> 
		#endif

		#if defined _USB_
				#include "USB/USB_Prototipos.h"
		#endif

		#if defined _TCNT0_
			#include "TCNT0/TCNT0.h"
		#endif

		#if defined _INT0_
			#include "INT0/INT0.h"
		#endif

		#if defined _INT1_
			#include "INT1/INT1.h"
		#endif

		#if defined _KEYBOARD_AT_PS2_
			#include "KeyboardAT_PS2/KeyboardAT_PS2.h"
		#endif

		#if defined _TMR1_
			#include "TMR1/TMR1.h"
		#endif
		
		#if defined _HC595_
			#include "74HC595/74HC595.H"
		#endif
		
		#if defined _ISD4003_04M_
			#include "ISD400X/ISD400X.h"
		#endif

		#if defined _DS1307_
			#include "DS1307/DS1307.h"
		#endif
		
		#if defined _GLCD192X64_					
			#include "GLCD192X64/GLCD192x64.h"
			#include "GLCD192X64/GLCD_fxs.h"	//soporte de funciones utiles adicionales
		#endif
		
		#if defined _DS3231_
			#include "DS3231/DS3231.h"
		#endif
		
		#if defined _BUZZER_
			#include "BUZZER/Buzzer.h"
		#endif
		
		#if defined _RS485_
			#include "RS485/RS485.h"
		#endif

		#if defined _KS108_
			#include "KS108v1/ks0108.h"
			//#include "KS108v1/arial_bold_14.h"
			//#include "KS108v1/SC.h"
			//#include "KS108v1/Bitmap.h"
			//
			//#include "KS108v1/corsiva_12.h"
			//#include "KS108v1/font12x16.h"
		#endif
		
		#if defined _KEYBOARD_HANDLER_
			#include "KEYBOARD/KeyboardHandler.h"
			#include "KEYBOARD/KEYBOARD_API/KeyboardAPI_1.h"
		#endif
#endif
