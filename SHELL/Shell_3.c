/*
 * Shell_1.c
 *
 * Created: 8/9/2012 3:26:49 PM
 *  Author: jcaf
 */ 
#include "Includes/InitializeAllModules.h"

	static void key1_1fmode0(void);
	static void key2_1fmode0(void);
	static void key3_1fmode0(void);
	static void key4_1fmode0(void);
	
	static PTRFXrVOID thisps_fxs[4][MAXNUM_MODE_BY_PS][KB_TOTALOFKEYS]={
		{
		{&key1_1fmode0, &key2_1fmode0, &key3_1fmode0, &key4_1fmode0},
		{&DUMMYFX,&DUMMYFX,&DUMMYFX,&DUMMYFX},
		{&DUMMYFX,&DUMMYFX,&DUMMYFX,&DUMMYFX},
		{&DUMMYFX,&DUMMYFX,&DUMMYFX,&DUMMYFX},
		},
		{
		{&DUMMYFX,&DUMMYFX,&DUMMYFX,&DUMMYFX},
		{&DUMMYFX,&DUMMYFX,&DUMMYFX,&DUMMYFX},
		{&DUMMYFX,&DUMMYFX,&DUMMYFX,&DUMMYFX},
		{&DUMMYFX,&DUMMYFX,&DUMMYFX,&DUMMYFX},
		},
		{
		{&DUMMYFX,&DUMMYFX,&DUMMYFX,&DUMMYFX},
		{&DUMMYFX,&DUMMYFX,&DUMMYFX,&DUMMYFX},
		{&DUMMYFX,&DUMMYFX,&DUMMYFX,&DUMMYFX},
		{&DUMMYFX,&DUMMYFX,&DUMMYFX,&DUMMYFX},
		},
		{
		{&DUMMYFX,&DUMMYFX,&DUMMYFX,&DUMMYFX},
		{&DUMMYFX,&DUMMYFX,&DUMMYFX,&DUMMYFX},
		{&DUMMYFX,&DUMMYFX,&DUMMYFX,&DUMMYFX},
		{&DUMMYFX,&DUMMYFX,&DUMMYFX,&DUMMYFX},
		}
	};
	
	void MainMenu_Panel0(void)
	{
		DrawOnlyMarcoGlobalGLCD();
		ks0108DrawHoriLine(0,13,191,BLACK);
		
		ks0108SelectFont(Corsiva_12,ks0108ReadFontData,BLACK);
		ks0108GotoXY(3,1);	
		ks0108Puts_P(PSTR("Jaime De-Souza-Ferreyra"));//Ugarte
		
		//__Time and date
		ks0108SelectFont(Arial_Bold_14,ks0108ReadFontData,BLACK);
		ks0108GotoXY(4,30);	ks0108Puts_P(PSTR("12:00 pm"));
		ks0108SelectFont(SC,ks0108ReadFontData,BLACK);
		ks0108GotoXY(4,47);	ks0108Puts_P(PSTR("Dom"));
		ks0108GotoXY(30,47);	ks0108Puts_P(PSTR("21"));
		ks0108GotoXY(42,47);	ks0108Puts_P(PSTR("Oct"));
		//__
	}
	
	signed char fx1(void);
	signed char fx2(void);
	signed char fx3(void);
	signed char fx4(void);
	signed char fx5(void);
	signed char Mas(void);			//seria lo mismo para cualquier skin
	signed char Volver(void);
	
	void bkPanelSkin0(void);
	void bkPanelSkin1(void);

	typedef struct _xyCaptions_
	{	byte x;
		byte y;
	}_xyCaptions;
	
	typedef struct _paramInvertRect_
	{
		byte x;
		byte y;
		byte w;
		byte h;
	}_paramInvertRect;
	
	typedef struct _limit_
	{	//byte inf;//->directo es 0
		byte sup;
	}_limit;
	
	#define NUM_SKINS_MAINMENU (2)
	#define MAX_NUM_PAGES	(2)
	#define MAX_NUM_OPTION_PER_PAGE (4)
	
	typedef struct _page_
	{
		_xyCaptions xyCaptions[MAX_NUM_OPTION_PER_PAGE];
		char Captions[MAX_NUM_OPTION_PER_PAGE][10];
		_paramInvertRect paramInvertRect[MAX_NUM_OPTION_PER_PAGE];
		PTRFXrSCHAR fx[MAX_NUM_OPTION_PER_PAGE];
		_limit limit;
		signed char option;
	
	}_page;
	
	typedef struct _mainmenu_
	{
		const uint8_t * fontForCaptions;	//SC/ Arial_Bold_14 / Corsiva_12
		_page page[MAX_NUM_PAGES];
		PTRFXrVOID bkpanel;	//podria pertenecer a la estructura page
	}_mainmenu;
	
	volatile _mainmenu mainmenu[NUM_SKINS_MAINMENU]=
	{
		//---------------------------------
		//1st MENU
			//Font in this MENU
			SC,
			//1st page
			//xy
			107,17,
			149,31,
			107,46,
			64,31,
			//captions
			"Escenas",
			"Zonas",
			"Config",
			"Otros",
			//param for InvertRect
			106,16, 41,SC_HEIGHT,
			148,30, 41,SC_HEIGHT,
			106,45, 41,SC_HEIGHT,
			63,30, 41,SC_HEIGHT,
			//fxs
			&scene_handler,
			&zone_handler,
			&RG_SDNDL_Menu,
			&Mas,
			//limites for this page
			//0,//inferior
			3,//superior
		
			//option variable
			0,
			//2st page
			//xy
			107,17,
			149,31,
			107,46,
			0x00,0x00,
			//captions
			"Enlace",
			"Ayuda",
			"Volver",
			"",
			//param for InvertRect
			106,16, 41,SC_HEIGHT,
			148,30, 41,SC_HEIGHT,
			106,45, 41,SC_HEIGHT,
			0x00,0x00,0x00,0x00,
			//fxs
			&fx4,
			&fx5,
			&Volver,
			(void*)0,
			//limites for this page
			//0,//inferior
			2,//superior
		
			//option variable
			0,
			
			//background panel for this menu
			&bkPanelSkin0,
		//---------------------------------
		//2st MENU
			//Font in this MENU
			Arial_Bold_14,
			//1st page
			//xy
			69,20,
			140,20,
			75,44,
			140,44,
			//captions
			"Escenas",
			"Zonas",
			"Config",
			"Otros",
			//param for InvertRect
			68,18,55,16,
			131,18,55,16,
			68,42,55,16,
			131,42,55,16,
			//fxs
			&scene_handler,
			&zone_handler,
			&scene_add_handler,//&SettingNameToZone,//&RG_SDNDL_Menu,
			&Mas,
			//limites for this page
			//0,//inferior
			3,//superior
		
			//option variable
			0,

			//2st page
			//xy
			69,20,
			140,20,
			77,44,
			0x00,0x00,
			//captions
			"Enlace",
			"Ayuda",
			"Volver",
			"",
			//param for InvertRect
			68,18,55,16,
			131,18,55,16,
			68,42,55,16,
			0x00,0x00,0x00,0x00,
			//fxs
			&fx4,
			&fx5,
			&Volver,
			(void*)0,
			//limites for this page
			//0,//inferior
			2,//superior
		
			//option variable
			0,
			//background panel for this menu
			&bkPanelSkin1,
	};
	
	byte skin = 1;		//EEPROM_ReadByte()	//global
	static byte pg = 0;	//page
	
	/**************************************************************
	**************************************************************/
	void bkPanelSkin0(void)
	{
		//ks0108DrawRect(66,16,59,20, BLACK);
		
	}
	/**************************************************************
	**************************************************************/
	void bkPanelSkin1(void)
	{
		ks0108DrawRect(66,16,59,20, BLACK);
		ks0108DrawRect(129,16,59,20, BLACK);
		ks0108DrawRect(66,40,59,20, BLACK);
		ks0108DrawRect(129,40,59,20, BLACK);
	}
	/**************************************************************
	**************************************************************/
	#define _ks0108InvertRect() do{ ks0108InvertRect(	mainmenu[skin].page[pg].paramInvertRect[mainmenu[skin].page[pg].option].x, \
														mainmenu[skin].page[pg].paramInvertRect[mainmenu[skin].page[pg].option].y, \
														mainmenu[skin].page[pg].paramInvertRect[mainmenu[skin].page[pg].option].w, \
														mainmenu[skin].page[pg].paramInvertRect[mainmenu[skin].page[pg].option].h);}while(0)

	
	/**************************************************************
	**************************************************************/
	void MainMenu_MenuThisSkin(void)
	{
		byte i;
		
		mainmenu[skin].bkpanel();
		ks0108SelectFont(mainmenu[skin].fontForCaptions, ks0108ReadFontData,BLACK);
		for (i=0; i<=mainmenu[skin].page[pg].limit.sup; i++)
		{
			ks0108GotoXY(mainmenu[skin].page[pg].xyCaptions[i].x, mainmenu[skin].page[pg].xyCaptions[i].y);
			ks0108Puts(mainmenu[skin].page[pg].Captions[i]);
		}
		_ks0108InvertRect();
	}	
	/**************************************************************
	**************************************************************/
	void MainMenu_All(void)
	{
		MainMenu_Panel0();//top/left/bottom
		MainMenu_MenuThisSkin();
	}
	
	static struct _thisps
	{
		signed char zone;
		char operating_mode;
		signed char  commonfeat_kb;
	}thisps;
		 
	struct _shell shell;
	static void PeriodicCall_Thread_FadingProcess_AllZone(void);
	
	///////////////////////////////////////////////////////////////
	//ScheduleWhenShowOnDisplayTimeAndDate();	//time and date	
	///////////////////////////////////////////////////////////////
	void Shell_main(void)
	{
		byte i;
		
		thisps.operating_mode = 0;
		change_operating_mode(thisps_fxs, thisps.operating_mode);

	bfCommonProcess0.Timmer_BlinkCaption = ON;
		
		MainMenu_All();
		
		while (1)
		{
			//-----------------------------------------			
			kb_handler0();
			
			//-----------------------------------------			
			if (shell.coderet_shell.bf.retfromps)	//ha ocurrido salida por parte de una funcion
			{
				shell.coderet_shell.bf.retfromps = 0;
				
				ps_fading_inbk.bf.printdisplay = DISABLE;
				
				//pop_functions
				pop_address_fx();//vuelve a registar al padre

				if ( mainmenu[skin].page[pg].option == shell.coderet_shell.coderet )
				{	
					//Restaura menu actual
					ks0108ClearScreen();
					MainMenu_All();
					shell.bf.callfx = 0;
				}
				else //seleccion interna
				{
					mainmenu[skin].page[pg].option = shell.coderet_shell.coderet;//re ingresa al otro menu
					//
					push_address_fx();
					shell.bf.callfx = 1;
				}
			}
			//-----------------------------------------
			//constantemente estara llamando a la funcion,cada funcion sera responsable de organizar sus cambios de vista
			if (shell.bf.callfx)//do function
			{
				//push_address_fx();
				mainmenu[skin].page[pg].fx[ mainmenu[skin].page[pg].option ]();
			}
			//-----------------------------------------		
			daemons();
			//-----------------------------------------					
		}
	}

	///////////////////////////////////////////////////////////////
	void daemons(void)
	{
		if (bfCommonProcess0.Timmer_BlinkCaption)
		{
			if (bfCommonProcess0.SignOneTick_BlinkCaption)
			{
				bfCommonProcess0.SignOneTick_BlinkCaption = OFF;
				ObjBlink_Timming_CaptionOfBarZone();
			}
		}
		PeriodicCall_Thread_FadingProcess_AllZone();
	}	
	//=====================================================================================================
	static void PeriodicCall_Thread_FadingProcess_AllZone(void)
	{
		//if (ps_fading_inbk.bf.timmer_active)	{
			if (ps_fading_inbk.bf.sign_new_tick)
			{	ps_fading_inbk.bf.sign_new_tick = 0;
					
				do_fadingprocess_allzone();
			//if ( is_fadingprocess_allzone_finish() ){ps_fading_inbk.bf.timmer_active = 0;}
		}
	//}
	}
		
	///////////////////////////////////////////////////////////////
	static void key1_1fmode0(void)
	{
		_ks0108InvertRect();

		if (++mainmenu[skin].page[pg].option > mainmenu[skin].page[pg].limit.sup)
			{mainmenu[skin].page[pg].option = 0;}
		
		_ks0108InvertRect();
		
		playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
	}
	///////////////////////////////////////////////////////////////
	static void key2_1fmode0(void)
	{
		_ks0108InvertRect();
		
		if (--mainmenu[skin].page[pg].option < 0)
			{mainmenu[skin].page[pg].option = mainmenu[skin].page[pg].limit.sup;}

		_ks0108InvertRect();

		playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
	}
	///////////////////////////////////////////////////////////////
	static void key3_1fmode0(void)
	{
		playsound(SOUND_BUZZER, _BUZZER_ACCEPT_SOUND0_);
		KB_KEY3_HasBeenRead();
		//
		ks0108ClearScreen();

		//
if ( (pg==0) && (mainmenu[skin].page[pg].option == 3))
{
	Mas();
}
else if ( (pg==1) && (mainmenu[skin].page[pg].option == 2))
{
	Volver();
}	
else
{
		push_address_fx(); //--> PASADO A HORA AL WHILE
		shell.bf.callfx = 1;
}
		
		/*
		else if (mainmenu[skin].page[pg].option == 2)	//CONFIG TYPE OF LOAD
		{
					DrawOnlyMarcoGlobalGLCD();
					CaptionOfAllZones();

			ks0108DrawHoriLine(64,14,190-64,BLACK);ks0108DrawVertLine(64,1,12,BLACK);//draw |__
		}
		*/
	}

	static void key4_1fmode0(void)
	{
		playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
	}

	/**************************************************************
	cada ingreso a nueva pagina inicia en la opcion 0
	**************************************************************/
	signed char Mas(void)
	{
		pg++;
		mainmenu[skin].page[pg].option = 0;
		ks0108ClearScreen();
		MainMenu_All();
		return 0;
	}
	signed char Volver(void)
	{
		pg--;
		ks0108ClearScreen();
		MainMenu_All();
		return 0;
	}
	
	signed char fx1(void)
	{
		//ks0108ClearScreen();
		//ks0108SelectFont(Arial_Bold_14,ks0108ReadFontData,BLACK);
		//ks0108GotoXY(192/2, 64/2);	ks0108Puts_P(PSTR("FX1"));
		//_delay_ms(2000);
		return 0;
	}
	signed char fx2(void)
	{
		//ks0108ClearScreen();
		//ks0108SelectFont(Arial_Bold_14,ks0108ReadFontData,BLACK);
		//ks0108GotoXY(192/2, 64/2);	ks0108Puts_P(PSTR("FX2"));
		//_delay_ms(2000);
		return 0;
	}
	signed char fx3(void)
	{
		//ks0108ClearScreen();
		//ks0108SelectFont(Arial_Bold_14,ks0108ReadFontData,BLACK);
		//ks0108GotoXY(192/2, 64/2);	ks0108Puts_P(PSTR("FX3"));
		//_delay_ms(2000);
		return 0;
	}

	signed char fx4(void)
	{
		//ks0108ClearScreen();
		//ks0108SelectFont(Arial_Bold_14,ks0108ReadFontData,BLACK);
		//ks0108GotoXY(192/2, 64/2);	ks0108Puts_P(PSTR("FX4"));
		//_delay_ms(2000);
		return 0;
	}
	signed char fx5(void)
	{
		//ks0108ClearScreen();
		//ks0108SelectFont(Arial_Bold_14,ks0108ReadFontData,BLACK);
		//ks0108GotoXY(192/2, 64/2);	ks0108Puts_P(PSTR("FX5"));
		//_delay_ms(2000);
		return 0;
	}


	
	
		