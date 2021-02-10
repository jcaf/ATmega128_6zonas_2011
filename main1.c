/* ESTE ES EL FIRMWARE PARA EL DISENO DEL 2011. PRIMER DISENO VENDIDO A VARIOS CLIENTES
 * 2021: Arch Linux, MPLAB X IDE v5.45, AvrDragon JTAG

 * Sacado del proyecto original en Avr Studio 2011
 * 
[jcaf@firwar production]$ avrdude -c dragon_jtag -P usb -p m128 -U flash:w:ATmega128_6Zonas_2011.X.production.elf

 * Para generar el .hex correctamente (recd star las secciones que no son codigo ejec.)
[jcaf@firwar production]$ avr-objcopy -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "ATmega128_6Zonas_2011.X.production.elf" "ATmega128_6Zonas_2011.X.production.hex" -R .sobjscene_commonprop_epp  -R .sobjstorage_scene_epp  -R .sobjzone_epp

 *  * 
 * PARA GENERAR el .eep correctamente
 * avr-objcopy -j .eeprom -j .sobjscene_commonprop_epp -j .sobjstorage_scene_epp -j .sobjzone_epp --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0 --change-section-lma .sobjscene_commonprop_epp=0x100 --change-section-lma .sobjstorage_scene_epp=0x200 --change-section-lma .sobjzone_epp=0x400 --no-change-warnings -O ihex ATmega128_6Zonas_2011.X.production.elf ATmega128_6Zonas_2011.X.production.eep
 * main1.c
 *
 * Por fin perfectamente configurado con esos comandos... todo OK

 * -Wl,-u,vfprintf -lprintf_flt -lm //2021 deprecado... solo con dtostrf
 * 
 * 
 * 
.sobjscene_commonprop_epp	@ 0x100
.sobjstorage_scene_epp		@ 0x200 (+0x200 of free-space)
.sobjzone_epp				@ 0x400 (+0x200 of free-space)

AVRStudio v6.0.1843
AVR/GNU Linker -> Memory setting -> EEPROM segment (adicionar)

.sobjscene_commonprop_epp=0x100
.sobjstorage_scene_epp=0x200               
.sobjzone_epp=0x400                    


 * Created: 13/02/2012 10:05:28 a.m.
 *  Author: jcaf
DEPURACION OK con ATmelStudio 6.0.1843
en este proyecto esta el archivo adc1.c para probar la pulsacion tactil

Se cierra toda modificacion al 1 junio de 2013 12:32 pm
 
objzone[zone].thrshld = 26;//26=20.5%     
objzone[zone].time_of_fading = 3200;//ms

Apto x entregar a Bruno

 */ 
#include "Includes/InitializeAllModules.h"
#include "main.h"


	volatile byte _sreg_temp_main_;	//extern en DefinicionesGrl.h
	
	//only if necesary
	static struct _key_properties key_properties__ps_forall[KB_TOTALOFKEYS]=
	{
		//[0].u.bf.OnKeyPressed = 1,
		//[0].group_autoexcluding = 1,
		//[1].u.bf.OnKeyPressed = 1,
		//[1].group_autoexcluding = 1,
		//[2].u.bf.OnKeyPressed = 1,
		//[2].group_autoexcluding = 1,
		//[3].u.bf.AtTimeExpired = 1,
		//[3].group_autoexcluding = _NO_AGRUPADO_AUTOEXCLUDING_,

		[0].u.bf.OnKeyPressed = 1,
		[0].u.bf.OnKeyPressedAndKeyRelease = 0,
		[0].u.bf.AtTimeExpired = 0,
		[0].u.bf.Reptt = 1,
		[0].group_autoexcluding = 1,
		
		[1].u.bf.OnKeyPressed = 1,
		[1].u.bf.OnKeyPressedAndKeyRelease = 0,
		[1].u.bf.AtTimeExpired = 0,
		[1].u.bf.Reptt = 1,
		[1].group_autoexcluding = 1,
				
		[2].u.bf.OnKeyPressed = 0,
		[2].u.bf.OnKeyPressedAndKeyRelease = 0,
		[2].u.bf.AtTimeExpired = 1,
		[2].u.bf.Reptt = 0,
		[2].group_autoexcluding = 1,
				
		[3].u.bf.OnKeyPressed = 0,
		[3].u.bf.OnKeyPressedAndKeyRelease = 0,
		[3].u.bf.AtTimeExpired = 1,
		[3].u.bf.Reptt = 0,
		[3].group_autoexcluding = _NO_AGRUPADO_AUTOEXCLUDING_,

	};

	
	//#define _TEST_ASSEMBLY_1_	//-> tambien habilitar #define _DEBUG_KEYBOARD_HANDLER_ (KeyboardHandler.h)
	#ifdef _TEST_ASSEMBLY_1_
		void __testAssembly_BeforeSoldingGLCD__(void);
	#endif

	static void InitSystem(void);
    
    
     //+--Added 2021
    volatile struct _isr_flag isr_flag = { 0 };
    struct _main_flag main_flag = { 0 };
    //--+
    

	int main(void) 
	{
		
		volatile uint16_t i;
		//-------------------------
		//#ifdef _TEST_ASSEMBLY_1_
		//	__testAssembly_BeforeSoldingGLCD__();
		//#endif
		//-------------------------

//singleconv1();	//test OK capacitive touch

		InitSystem();
		
		//GLCD
		for(i=0; i<15000; i++)
			{;}
		GLCD192X64_RSTB_RELEASE();							//LCD_CMD_PORT_RSTB |= (1<<_RSTB_);	//Release from Reset 
		
		ks0108Init(0);										// Initialize the LCD
		ks0108ClearScreen();
		ks0108SelectFont(SC, ks0108ReadFontData, BLACK);	
		
		//ZONES
		InitZones();
		
		//SCENE INITIALIZE
		init_scene();
		
		//BLINK CAPTION
		ObjBlink_CaptionOfBarZone_InitAllCounterTimer();
		
		//MENUs
		//Select Dimm NO-Dimm Load
		RG_SDNDL_Init_AllRadios(); //initialization for RADIOBUTTON
		
		//KEYBOARD
		//Es necesario darle un valor inicial al teclado, antes de ponerlo en estado de inhibido a traves de synch_change_layout_kb();
		for (i=0; i< KB_TOTALOFKEYS; i++)//setkb_mix0();
		{
			objkey[i].key_properties.u._8b_key_properties = key_properties__ps_forall[i].u._8b_key_properties;
			objkey[i].key_properties.group_autoexcluding = key_properties__ps_forall[i].group_autoexcluding;
		}
		synch_change_layout_kb( (_STACK_MODE)DIRECT, &key_properties__ps_forall[0]);//start with all keys released

		
		//time_printdisp.bf.print_second = 1;
		time_printdisp__set_xy();
		//
		date_printdisp.format_date = (DATE_FORMAT)sDAY_DD_sMONTH;
		date_printdisp__set_xy();

		sei();

		Shell_main();
		
		/*while (1)	
			{TxByteNoWaitTXC_USART0('b');}
		*/
		return 0;
	}
	/***************************************************************************
	***************************************************************************/
	static void InitSystem(void)
	{
		InitPWM();
		
		Init_I2C_unimaster();
		
		//.......................................
		InitDS3231();
		//DS3231_UpdateClock();				
		
		//.......................................

		InitBuzzer();
		
		Init_USART0();
		InitRS845_0();

		InitGLCD192x64();
	
		InitKeyboard();
		
		InitTCNT0();		//xCTC
		TIMSK = 1<<OCIE0;	//Hab. interr. x TCNT0
	}
	
	
	#ifdef _TEST_ASSEMBLY_1_
	void __testAssembly_BeforeSoldingGLCD__(void)
	{
		//--test PWM
		InitPWM();
		OCR1A = OCR1B = OCR1C = OCR3A = OCR3B = OCR3C = 512;
		//--
		//--test GLCD
		DDRC=0xFF;
		PORTC=0xAA;
		//--
		//--Test DS3231
		Init_I2C_unimaster();
		InitDS3231();
		//DS3231_UpdateClock();
		//--
		InitBuzzer();
		//BUZZER_ON();

		//--test keyboard
		InitKeyboard();
		
		InitTCNT0();		//xCTC
		TIMSK = 1<<OCIE0;	//Hab. interr. x TCNT0

		sei();
		//TestKeyboard_highlevel();
		//TestKeyboard_highlevel_noks();
		TestKeyboardHandler01_ONLY_BUZZER();
		//TestKeyboardHandler02();
		while(1);
	}
	
	void capacitive1(void)
	{
		
	
	}		
	
	
	#endif
	
