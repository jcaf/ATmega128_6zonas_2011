/*
 * MenuDimming6Zonas_1.c
 *
 * Created: 24/02/2012 04:44:37 p.m.
 *  Author: jcaf
 */ 
#include "Includes/InitializeAllModules.h"

	typedef enum _OPERATINGMODE_THISPS
	{
		DO_ZONE=0,//MODE0=0,//doing scene
		DO_DIAGBOX,//MODE1,	//doing dialogbox
	}OPERATINGMODE_THISPS;

	static struct _thisps
	{
		signed char zone;
		OPERATINGMODE_THISPS operating_mode;
		signed char scheduler0;
		signed char scheduler1;
	}thisps;
	
	static void key1_1fmode0(void);//
	static void key2_1fmode0(void);//
	static void key3_1fmode0(void);//
	static void key3_1fmode0_aft(void);
	static void key4_1fmode0(void);
	
	static void key1_1fmode1(void);//doing dialogbox [si][no]
	static void key2_1fmode1(void);//doing dialogbox [si][no]
	static void key3_1fmode1(void);//bef//doing dialogbox [si][no]
	static void key3_1fmode1_aft(void);
	static void key4_1fmode1(void);
	
	static void key1_2fmode0(void);
	static void key2_2fmode0(void);
	static void key3_2fmode0(void);
	
	static PTRFXrVOID thisps_fxs[4][MAXNUM_MODE_BY_PS][KB_TOTALOFKEYS]={
		{
		{&key1_1fmode0, &key2_1fmode0, &key3_1fmode0, &key4_1fmode0},//doing dimming
		{&key1_1fmode1, &key2_1fmode1, &key3_1fmode1, &key4_1fmode1},//doing dialog-box
		{&DUMMYFX, &DUMMYFX, &DUMMYFX, &DUMMYFX},
		{&DUMMYFX, &DUMMYFX, &DUMMYFX, &DUMMYFX},
		},
		{
		{&DUMMYFX, &DUMMYFX, &key3_1fmode0_aft, &DUMMYFX},//doing dimming
		{&DUMMYFX, &DUMMYFX, &key3_1fmode1_aft, &DUMMYFX},//doing dialog-box
		{&DUMMYFX, &DUMMYFX, &DUMMYFX, &DUMMYFX},
		{&DUMMYFX, &DUMMYFX, &DUMMYFX, &DUMMYFX},
		},
		{
		{&key1_2fmode0, &key2_2fmode0, &key3_2fmode0, &DUMMYFX},
		{&DUMMYFX, &DUMMYFX, &DUMMYFX, &DUMMYFX},
		{&DUMMYFX, &DUMMYFX, &DUMMYFX, &DUMMYFX},
		{&DUMMYFX, &DUMMYFX, &DUMMYFX, &DUMMYFX},
		},
		{
		{&DUMMYFX, &DUMMYFX, &DUMMYFX, &DUMMYFX},
		{&DUMMYFX, &DUMMYFX, &DUMMYFX, &DUMMYFX},
		{&DUMMYFX, &DUMMYFX, &DUMMYFX, &DUMMYFX},
		{&DUMMYFX, &DUMMYFX, &DUMMYFX, &DUMMYFX},
		}
	};
	
	//
	#define TORIGHT (+1)
	#define TOLEFT 	(-1)	
	static void selectzone(signed char dir);
	//
	static void switch_to_scene(void);
	static void return_to_mode0(void);
	static void _return2shell(void);
	
	////////////////////////////////////////////////////////////////////////////////////////
	#define schedule(val) do{thisps.scheduler0 = val; thisps.scheduler1=0x00;}while(0)
	
	////////////////////////////////////////////////////////////////////////////////////////
	static void showpropzone(byte zone)
	{
		blink_captionof_barzone_RUN(zone);
		ks0108SelectFont(SC, ks0108ReadFontData, BLACK);
		FindAndPrintNameOfZone(zone, xiCHIP1);				//namez(zone);
		ks0108FillRect(1,63-17,61,0,BLACK);					//recta horizontal separadora
		dcporcentz(if_fadingactive_nextdc_else_dc(zone));	//maybe in progressive your duty-cycle
	}

	////////////////////////////////////////////////////////////////////////////////////////
	void zone_handler(void)
	{
		if (thisps.scheduler0 == 0)//initialize once
		{
			if (thisps.scheduler1 == 0)
			{
				thisps.scheduler1++;
															
				ps_fading_inbk.bf.printdisplay = ENABLE;	//Ahora Habilita incondicionalmente
				
				if (!crossover_scene_zone.from_scene)
				{
					ks0108ClearScreen();
					
					//division en 2 paneles:
					ks0108DrawRect(0,0,63,63,BLACK);
					ks0108DrawRect(65,0,191-65,63,BLACK);
					//
					_write_display_threshold_allzone();
					//
					CaptionOfAllZones();
					DrawBarsVertOfAllZones();

					//ingresa con dc actual
					byte i;
					for (i=0;i<NUM_ZONAS;i++)
						{directfill_barlevel(i, objzone[i].dc);}	
				}
				else 
				{
					crossover_scene_zone.from_scene =0;
				}	

				direct_clearallpixel_less1border_CHIP1();		
				showpropzone(thisps.zone);

				//registrar las funciones al entrar
 				thisps.operating_mode = (OPERATINGMODE_THISPS)DO_ZONE;//MODO0
 				change_operating_mode(thisps_fxs, thisps.operating_mode);
			}	
			schedule(-1);	//espera un nuevo evento			
		}

		//////////////////////////////////////////////////////////////////////////////////
		if (thisps.scheduler0 == 1)	//schedule(1)
		{
			if (thisps.scheduler1 == 0)//show menu
			{
				thisps.scheduler1++;

				softcentric_clearallpixel_less1border_CHIP1();
				ks0108GotoXY(2+4,2+17);		ks0108Puts_P(PSTR("Cambiar a"));
				ks0108GotoXY(2+8,2+17+12);	ks0108Puts_P(PSTR("Escenas ?"));
				dialogbox_sino(2,2,(DIALOGBOX_OPTIONS)_DIALOGBOX_OPTION_SI_);
			}
			if (thisps.scheduler1 == 1)//wait for answer
			{
				//thisps.scheduler1++;
				
				if (dialogbox_nb.cr > (DIALOGBOX_CR)NONE )
				{
					if (dialogbox_nb.cr ==  (DIALOGBOX_CR)YES)
					{
						//blink_captionof_barzone_STOP(thisps.zone);	
						//bfCommonProcess0.Timmer_BlinkCaption = OFF;
						switch_to_scene();
						//_waitforclean_keys();
						//
						__dialogbox_cr_wasread();
					}
					else if ((dialogbox_nb.cr ==  (DIALOGBOX_CR)NO)||(dialogbox_nb.cr ==  (DIALOGBOX_CR)SCAPE))
					{
						schedule(2);//sgte menu
						//
						__dialogbox_cr_wasread();
					}
					
					//thisps.scheduler1++;
				}					
			}
		}
		//////////////////////////////////////////////////////////////////////////////////
		if (thisps.scheduler0 == 2)	//schedule(2)
		{
			if (thisps.scheduler1 == 0)//show menu
			{
				thisps.scheduler1++;

				softcentric_clearallpixel_less1border_CHIP1();
				//Salir de este menu
				ks0108GotoXY(2+15,2+23);	ks0108Puts_P(PSTR("Salir?"));
				dialogbox_sino(2,2,(DIALOGBOX_OPTIONS)_DIALOGBOX_OPTION_SI_);
			}
			if (thisps.scheduler1 == 1)//wait for answer
			{
				//thisps.scheduler1++;
				
				if (dialogbox_nb.cr > (DIALOGBOX_CR)NONE )
				{
					if (dialogbox_nb.cr ==  (DIALOGBOX_CR)YES)
					{
						_return2shell();//deja schedule(0);
						//
						__dialogbox_cr_wasread();
					}
					else if ((dialogbox_nb.cr ==  (DIALOGBOX_CR)NO)||(dialogbox_nb.cr ==  (DIALOGBOX_CR)SCAPE))
					{
						return_to_mode0();//deja schedule(-1);
						//
						__dialogbox_cr_wasread();
					}
					
					//thisps.scheduler1++;
				}
			}
		}

	}//end fx
	
	static void key1_1fmode0(void)
	{
		objzone[thisps.zone].bf.print_dcporcentz = ON;
		_PreEx_DimmingUp(thisps.zone);
	}
	
	static void key2_1fmode0(void)
	{
		objzone[thisps.zone].bf.print_dcporcentz = ON;
		_PreEx_DimmingDown(thisps.zone);
	}

	static void key3_1fmode0(void)//Or before
	{
		objzone[thisps.zone].bf.print_dcporcentz = ON;

		if (objzone[thisps.zone].cfgmodeof_restoreonoff == (CFGMODEOF_RESTOREONOFF)RESTORE_AND_ON_OFF)
			{RestoreOnOff_mode1(thisps.zone);}
		else //ONLY_ON_OFF
			{RestoreOnOff_mode2(thisps.zone);}
		
		//if (>threshold)
		//playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);//solo si es mayor de threshold
	}

	static void key3_1fmode0_aft(void)
	{
		objzone[thisps.zone].bf.print_dcporcentz = ON;
		
		if (objzone[thisps.zone].cfgmodeof_restoreonoff == (CFGMODEOF_RESTOREONOFF)RESTORE_AND_ON_OFF)
			{directOnOff_mode1(thisps.zone);}
		else //ONLY_ON_OFF
			{directOnOff_mode2(thisps.zone);}
		
		//playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
	}

	static void key4_1fmode0(void)
	{
		playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
		selectzone(TORIGHT);
	}
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//doing dialogbox
	static void key1_1fmode1(void)//doing dialogbox [si][no]
	{
		dialogbox_nb.dialogbox_sino_UP();
		playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
	}
	static void key2_1fmode1(void)//doing dialogbox [si][no]
	{
		dialogbox_nb.dialogbox_sino_DN();
		playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
	}
	static void key3_1fmode1(void)//bef//doing dialogbox [si][no]
	{
		dialogbox_nb.dialogbox_sino_SEL();
		//
		if	(dialogbox_nb.option == 0)//yes
			{playsound(SOUND_BUZZER, _BUZZER_ACCEPT_SOUND0_);}
		else if (dialogbox_nb.option == 1)//no
			{playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);}
	}
	
	static void key3_1fmode1_aft(void)
	{	
		//no es necesario waitforclean_keys(), es limpiado de manera correcta
		//siempre necesario para que satisfaga el modo before/after para tecla 3
		key3_1fmode1();
	}
		
	static void key4_1fmode1(void)//ya estando en modo1
	{
		playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
		dialogbox_nb.dialogbox_sino_ESC();
	}

	///////////////////////////////////////////////////////////////////////////////////////
	static void key1_2fmode0(void)
	{
		playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
		selectzone(TOLEFT);
	}
	static void key2_2fmode0(void)//switch to scene
	{
		blink_captionof_barzone_STOP(thisps.zone);
		//bfCommonProcess0.Timmer_BlinkCaption = OFF;
		switch_to_scene();
		_KB_waitfor_kb_free_and_complete_ps();

		playsound(SOUND_BUZZER, _BUZZER_ACCEPT_SOUND0_);
	}

	static void key3_2fmode0(void)
	{
		playsound(SOUND_BUZZER, _BUZZER_ACCEPT_SOUND0_);
		
		blink_captionof_barzone_STOP(thisps.zone);
		//bfCommonProcess0.Timmer_BlinkCaption = OFF;
		
		_return2shell();
		//_KB_waitfor_kb_free_and_complete_ps();//ahora es general la salida con limpieza
	}
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	static void selectzone(signed char dir)
	{
		thisps.zone += dir;
			
		signed char temp = thisps.zone;
			
		if (thisps.zone < 0)
		{
			blink_captionof_barzone_STOP(0);
			thisps.zone = NUM_ZONAS-1;
		}
		else if (thisps.zone >= NUM_ZONAS)
		{
			blink_captionof_barzone_STOP(NUM_ZONAS-1);
			thisps.zone = 0;
		}
		else
		{
			blink_captionof_barzone_STOP( (byte) (thisps.zone + (byte)(dir*-1) ) );
			direct_clearallpixel_less1border_CHIP1();
			showpropzone(thisps.zone);
		}
		//...........................................................................
		if ( (temp < 0) || (temp >= NUM_ZONAS))
		{
			thisps.operating_mode = (OPERATINGMODE_THISPS)DO_DIAGBOX;//MODE1;
			change_operating_mode(thisps_fxs, thisps.operating_mode);
			//
			schedule(1);
			_KB_waitfor_kb_free_and_complete_ps();//si provino de combinacion M+1
		}
		//...........................................................................
	
	}
	
	static void switch_to_scene(void)
	{
		//blink_captionof_barzone_STOP(thisps.zone);
		//bfCommonProcess0.Timmer_BlinkCaption = OFF;
		crossover_scene_zone.from_zone = 1;
		menu_operational.goto_address = address_menu_main__scene;
		shell.coderet = (CODERETURN_TOSHELL)INTERNAL_SELECTION;
		schedule(0);//todas las salidas dejan para una entrada en MODO 0
		//_waitforclean_keys();
	}

	static void return_to_mode0(void)
	{
		//restore
		softcentric_clearallpixel_less1border_CHIP1();
		showpropzone(thisps.zone);	//Re-blink through this function
			
		thisps.operating_mode = (OPERATINGMODE_THISPS)DO_ZONE;//mode0
		change_operating_mode(thisps_fxs, thisps.operating_mode);
		schedule(-1);	//espero un nuevo evento
	}
	
	static void _return2shell(void)	//sale con schedule 0
	{
		//bfCommonProcess0.Timmer_BlinkCaption = OFF;
		shell.coderet = (CODERETURN_TOSHELL)RESTORE_SHELL;
		schedule(0);
		_KB_waitfor_kb_free_and_complete_ps();
	}
	
