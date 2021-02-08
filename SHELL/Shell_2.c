/*
 * Shell_1.c
 *
 * Created: 8/9/2012 3:26:49 PM
 *  Author: jcaf
 */ 
#include "Includes/InitializeAllModules.h"

	/**************************************************************
	**************************************************************/
	void Shell_main_GUI0(void)
	{
		DrawOnlyMarcoGlobalGLCD();
		ks0108DrawHoriLine(0,13,191,BLACK);
		
		ks0108SelectFont(Corsiva_12,ks0108ReadFontData,BLACK);
		ks0108GotoXY(3,1);	ks0108Puts_P(PSTR("Jaime De-Souza-Ferreyra"));//Ugarte
		
		//__Time and date
		ks0108SelectFont(Arial_Bold_14,ks0108ReadFontData,BLACK);
		ks0108GotoXY(3,30);	ks0108Puts_P(PSTR("12:12 pm"));
		ks0108SelectFont(SC,ks0108ReadFontData,BLACK);
		ks0108GotoXY(3,47);	ks0108Puts_P(PSTR("Vie 9 Set"));
		//__
	}
	/***************************************************
	
	***************************************************/
	byte fx1(void);
	byte fx2(void);
	byte fx3(void);
	byte fx4(void);
	byte fx5(void);
	
	void Mas_Skin0(void);	//seria lo mismo para cualquier skin
	void Volver_Skin0(void);
	
	/***************************************************
	Todo se puede resolver en tiempo de compilacion
	***************************************************/
	typedef byte (*PTRFXrBYTE)();
	
	#define NUMOPT_SHELLMENU (7)	
	#define NUM_SKINS_SHELLMENU (1)//
	#define MAX_PAR_LIMITES (2)

	typedef struct _xyCaptions_
	{
		byte x;
		byte y;
	}_xyCaptions;
	
	typedef struct _OptionLimits_
	{
		byte lim_inf;
		byte lim_sup;	
	}_OptionLimits;
	
	typedef struct _paramInvertRect_
	{
		//byte x;//tomados desde xyCaptions .x-1
		//byte y;//tomados desde xyCaptions .y-1	
		byte w;
		byte h;
	}_paramInvertRect;
	
	struct _SHELLMENU{
	
		PTRFXrBYTE fx[NUMOPT_SHELLMENU];
		//
		const uint8_t * fontForCaptions;	//SC/ Arial_Bold_14 / Corsiva_12	
		_xyCaptions xyCaptions[NUMOPT_SHELLMENU];
		char Captions[NUMOPT_SHELLMENU][10];
		_paramInvertRect paramInvertRect[NUMOPT_SHELLMENU];
		//
		_OptionLimits OptionLimits[MAX_PAR_LIMITES];

	}SHELLMENU[NUM_SKINS_SHELLMENU]={ 
									&RG_SDNDL_Menu,
									&fx1,
									&fx2,
									&Mas_Skin0,
									&fx4,
									&fx5,
									&Volver_Skin0,
									//font		
									SC,
									//xy captions
									107,17,
									149,31,
									107,46,
									64,31,
									107,17,
									149,31,
									107,46,		
									//captions
									"Escenas",
									"Zonas",	
									"Config",
									"Mas",
									"Enlace",
									"Ayuda",
									"Volver",
									//params for invert rect width, heigth
									41,SC_HEIGHT,
									41,SC_HEIGHT,
									41,SC_HEIGHT,
									41,SC_HEIGHT,
									41,SC_HEIGHT,
									41,SC_HEIGHT,
									41,SC_HEIGHT,
									//limites 
									0,3,	//pag1 for this menu
									4,6,	//pag2 for this menu
								};
	
	byte nskin = 0;//EEPROM_ReadByte()	//global
	static byte pageinthismenu = 0;	//local a este archivo
	static signed char option = 0;
	/**************************************************************
	**************************************************************/
	void ShowMenu(void)
	{
		Shell_main_GUI0();//CONSIDERADO POR AHORA-AUN NO DEFINIDO

		byte option;
		ks0108SelectFont(SHELLMENU[nskin].fontForCaptions, ks0108ReadFontData,BLACK);
		for (option=SHELLMENU[nskin].OptionLimits[pageinthismenu].lim_inf; option<=SHELLMENU[nskin].OptionLimits[pageinthismenu].lim_sup; option++)
		{	ks0108GotoXY(SHELLMENU[nskin].xyCaptions[option].x, SHELLMENU[nskin].xyCaptions[option].y);
			ks0108Puts(SHELLMENU[nskin].Captions[option]);
		}	
	}
	/**************************************************************
	
	**************************************************************/
	void Shell_main(void)
	{
		
						RG_SDNDL_Init_AllRadios(); //initialization for RADIOBUTTON por ahora aqui
		

		ShowMenu();
		ks0108InvertRect(SHELLMENU[nskin].xyCaptions[option].x-1, SHELLMENU[nskin].xyCaptions[option].y-1, SHELLMENU[nskin].paramInvertRect[option].w, SHELLMENU[nskin].paramInvertRect[option].h);	//default 0
		
		while (1)
		{
			//ScheduleWhenShowOnDisplayTimeAndDate();	//time and date	
			
			if (KB_KEY1_ReadyToRead())
			{
				ks0108InvertRect(SHELLMENU[nskin].xyCaptions[option].x-1,SHELLMENU[nskin].xyCaptions[option].y-1, SHELLMENU[nskin].paramInvertRect[option].w, SHELLMENU[nskin].paramInvertRect[option].h);
				
				if (++option > SHELLMENU[nskin].OptionLimits[pageinthismenu].lim_sup)
					{option = SHELLMENU[nskin].OptionLimits[pageinthismenu].lim_inf;}
				
				ks0108InvertRect(SHELLMENU[nskin].xyCaptions[option].x-1,SHELLMENU[nskin].xyCaptions[option].y-1, SHELLMENU[nskin].paramInvertRect[option].w, SHELLMENU[nskin].paramInvertRect[option].h);		
				
				PlaySound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
				KB_KEY1_HasBeenRead();
			}				
			
			if (KB_KEY2_ReadyToRead())
			{
				ks0108InvertRect(SHELLMENU[nskin].xyCaptions[option].x-1,SHELLMENU[nskin].xyCaptions[option].y-1, SHELLMENU[nskin].paramInvertRect[option].w, SHELLMENU[nskin].paramInvertRect[option].h);
				
				if (--option < SHELLMENU[nskin].OptionLimits[pageinthismenu].lim_inf)
					{option = SHELLMENU[nskin].OptionLimits[pageinthismenu].lim_sup;}

				ks0108InvertRect(SHELLMENU[nskin].xyCaptions[option].x-1,SHELLMENU[nskin].xyCaptions[option].y-1, SHELLMENU[nskin].paramInvertRect[option].w, SHELLMENU[nskin].paramInvertRect[option].h);

				PlaySound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
				KB_KEY2_HasBeenRead();
			}
			
			if (KB_KEY3_ReadyToRead())
			{
				PlaySound(SOUND_BUZZER, _BUZZER_ACCEPT_SOUND0_);
				KB_KEY3_HasBeenRead();
				
				ks0108ClearScreen();
				SHELLMENU[nskin].fx[option]();
				
				//Restaura menu actual
				ks0108ClearScreen();
				ShowMenu();
				ks0108InvertRect(SHELLMENU[nskin].xyCaptions[option].x-1, SHELLMENU[nskin].xyCaptions[option].y-1, SHELLMENU[nskin].paramInvertRect[option].w, SHELLMENU[nskin].paramInvertRect[option].h);	//default 0
			}
			
			if (KB_KEY4_ReadyToRead())
			{
				PlaySound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
				KB_KEY4_HasBeenRead();
			}

		}
		
	}
	
	void Mas_Skin0(void)
	{
		pageinthismenu++;
		option=SHELLMENU[nskin].OptionLimits[pageinthismenu].lim_inf;
	}
	void Volver_Skin0(void)
	{
		pageinthismenu=0;
		option=SHELLMENU[nskin].OptionLimits[pageinthismenu].lim_inf;
	}
	byte fx1(void)
	{
		ks0108ClearScreen();
		ks0108SelectFont(Arial_Bold_14,ks0108ReadFontData,BLACK);
		ks0108GotoXY(192/2, 64/2);	ks0108Puts_P(PSTR("FX1"));
		_delay_ms(2000);
		return 0;
	}
	byte fx2(void)
	{
		ks0108ClearScreen();
		ks0108SelectFont(Arial_Bold_14,ks0108ReadFontData,BLACK);
		ks0108GotoXY(192/2, 64/2);	ks0108Puts_P(PSTR("FX2"));
		_delay_ms(2000);
		return 0;
	}
	byte fx3(void)
	{
		ks0108ClearScreen();
		ks0108SelectFont(Arial_Bold_14,ks0108ReadFontData,BLACK);
		ks0108GotoXY(192/2, 64/2);	ks0108Puts_P(PSTR("FX3"));
		_delay_ms(2000);
		return 0;
	}

	byte fx4(void)
	{
		ks0108ClearScreen();
		ks0108SelectFont(Arial_Bold_14,ks0108ReadFontData,BLACK);
		ks0108GotoXY(192/2, 64/2);	ks0108Puts_P(PSTR("FX4"));
		_delay_ms(2000);
		return 0;
	}
	byte fx5(void)
	{
		ks0108ClearScreen();
		ks0108SelectFont(Arial_Bold_14,ks0108ReadFontData,BLACK);
		ks0108GotoXY(192/2, 64/2);	ks0108Puts_P(PSTR("FX5"));
		_delay_ms(2000);
		return 0;
	}
	