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
		//_________________________
		DrawOnlyMarcoGlobalGLCD();
		ks0108DrawHoriLine(0,14,191,BLACK);
		ks0108DrawVertLine(57,14,63-14,BLACK);
		ks0108DrawCircle((192/2)+25, 39,7,BLACK);
		//
		//ks0108DrawRoundRect(57,14,191-57,63-14,10,BLACK);
//ks0108DrawRoundRect(58,15, 191-59,63-16,20,BLACK);
		//_________________________
////////////
		//ks0108DrawLine(64,20,120,45,BLACK);
	/*
	{192/2,17},
	{65,34},
	{192/2+ 10 ,47},
	{192/2 + 50,34},
		*/
		ks0108DrawRect(100	,16	,40,14,BLACK);
		ks0108DrawRect(64	,33	,40,14,BLACK);
		
		ks0108DrawRect(140	,33	,40,14,BLACK);
		ks0108DrawRect(100	,47	,40,14,BLACK);
		
		//ks0108DrawRect(96,16,30,13,BLACK);
		//ks0108DrawRect(96,45,30,13,BLACK);

///////////////
		ks0108SelectFont(Corsiva_12,ks0108ReadFontData,BLACK);
		ks0108GotoXY(3,2);	ks0108Puts_P(PSTR("Jaime De-Souza-Ferreyra"));//Ugarte
		
		//__Time and date
		ks0108SelectFont(Arial_Bold_14,ks0108ReadFontData,BLACK);
		ks0108GotoXY(3,30);	ks0108Puts_P(PSTR("12:12 pm"));
		ks0108SelectFont(SC,ks0108ReadFontData,BLACK);
		ks0108GotoXY(3,47);	ks0108Puts_P(PSTR("Vie 9 Set"));
		//__
	}
	/**************************************************************
	**************************************************************/
	
	#define NUM_OPTION_MAIN_MENU (4)
	typedef struct _xy_Option_menu_texts_
	{
		byte x;
		byte y;
	}_xy_Option_menu_texts;
	_xy_Option_menu_texts xy_Option_menu_texts[NUM_OPTION_MAIN_MENU]={	{192/2,17},
																		{65,34},
																		{192/2+ 10 ,47},
																		{192/2 + 50,34},
																		};
	char Shell_main_Option_menu_texts[NUM_OPTION_MAIN_MENU][10]={"Escenas","Zonas","Config","Ayuda"};
	
	void Shell_main(void)
	{
		Shell_main_GUI0();
		
		byte idx_base =0;
		byte idx_off;
		byte i;
		
		for (i=0; i< NUM_OPTION_MAIN_MENU; i++)		
		{
			ks0108GotoXY(xy_Option_menu_texts[i].x ,xy_Option_menu_texts[i].y); 
			ks0108Puts(&Shell_main_Option_menu_texts[i][0]);
		}
		
		
		while (1)
		{
			//ScheduleWhenShowOnDisplayTimeAndDate();	//time and date	
			if (KB_KEY1_ReadyToRead())
			{
				if (++idx_base >= NUM_OPTION_MAIN_MENU) {idx_base=0;}
				
				idx_off = idx_base;
				
				for (i=0; i< NUM_OPTION_MAIN_MENU; i++)
				{
					ks0108FillRect(xy_Option_menu_texts[i].x ,xy_Option_menu_texts[i].y ,40 ,12 ,WHITE);		
					ks0108GotoXY(xy_Option_menu_texts[i].x , xy_Option_menu_texts[i].y);
			
					ks0108Puts( &Shell_main_Option_menu_texts[idx_off][0]);
				
					if (++idx_off >= NUM_OPTION_MAIN_MENU) {idx_off=0;}
				}
				ks0108InvertRect(xy_Option_menu_texts[0].x ,xy_Option_menu_texts[0].y ,40 ,12 );
				
				PlaySound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
				KB_KEY1_HasBeenRead();
			}				
			
			if (KB_KEY2_ReadyToRead())
			{
				PlaySound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
				KB_KEY2_HasBeenRead();
			}
			if (KB_KEY3_ReadyToRead())
			{
				PlaySound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
				KB_KEY3_HasBeenRead();
			}
			if (KB_KEY4_ReadyToRead())
			{
				PlaySound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
				KB_KEY4_HasBeenRead();
			}

		}
		
	}
	//	byte count_main_scheduler = 0