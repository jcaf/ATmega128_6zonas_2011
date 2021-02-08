/*
 * NuevaEscena_1.c
 *
 * Created: 09/04/2012 04:09:47 p.m.
 *  Author: jcaf 
 */ 
#include "Includes/InitializeAllModules.h"

	typedef enum _OPERATINGMODE_THISPS
	{
		DO_SCENE=0,//MODE0=0,//doing scene
		DO_DIAGBOX,//MODE1,	//doing dialogbox
		DO_LISTBOX//MODE2,	//doing listbox
	}OPERATINGMODE_THISPS;

	static struct _thisps
	{
		signed char zone;
		OPERATINGMODE_THISPS operating_mode;
		byte scheduler;

		//CODERETURN_TOSHELL codereturn;
		
	}thisps = {.scheduler = 1};
	
	struct _thismenups{
		byte currentmenu;
		struct _thismenups_bf
		{
			unsigned shownewmenu:1;
			unsigned __none:7;
		}bf;
	}thismenups;	
	
	static void key1_1fmode0(void);
	static void key1_1fmode1(void);//doing dialogbox [si][no]
	static void key1_1fmode2(void);
	static void key1_2fmode0(void);

	static void key2_1fmode0(void);
	static void key2_1fmode1(void);//doing dialogbox [si][no]
	static void key2_1fmode2(void);

	static void key3_1fmode0(void);
	static void key3_1fmode1(void);//bef//doing dialogbox [si][no]
	static void key3_1fmode2(void);//before

	static void key3_1fmode0_aft(void);
	static void key3_1fmode1_aft(void);
	static void key3_1fmode2_aft(void);

	static void key4_1fmode0(void);
	static void key4_1fmode1(void);

	static PTRFXrVOID thisps_fxs[4][MAXNUM_MODE_BY_PS][KB_TOTALOFKEYS]={
		{
		{&key1_1fmode0, &key2_1fmode0, &key3_1fmode0, &key4_1fmode0},
		{&key1_1fmode1, &key2_1fmode1, &key3_1fmode1, &key4_1fmode1},
		{&key1_1fmode2, &key2_1fmode2, &key3_1fmode2, &DUMMYFX},
		},
		{
		{&DUMMYFX, &DUMMYFX, &key3_1fmode0_aft, &DUMMYFX},
		{&DUMMYFX, &DUMMYFX, &key3_1fmode1_aft, &DUMMYFX},
		{&DUMMYFX, &DUMMYFX, &key3_1fmode2_aft, &DUMMYFX},
		},
		{
		{&key1_2fmode0, &DUMMYFX, &DUMMYFX, &DUMMYFX},
		{&DUMMYFX, &DUMMYFX, &DUMMYFX, &DUMMYFX},
		{&DUMMYFX, &DUMMYFX, &DUMMYFX, &DUMMYFX},
		},
		{
		{&DUMMYFX, &DUMMYFX, &DUMMYFX, &DUMMYFX},
		{&DUMMYFX, &DUMMYFX, &DUMMYFX, &DUMMYFX},
		{&DUMMYFX, &DUMMYFX, &DUMMYFX, &DUMMYFX},
		}
	};
	
	#define TORIGHT (+1)
	#define TOLEFT 	(-1)
	
	static void selectzone(signed char dir);
	static void menu_handler(void);
	
	static void dialogbox_sino_handler(void);
	static void return_to_doing_scene(void);	

	//////////////////////////////////////////////////////////////////////////////////
	static void listbox_name_scene(void)
	{
		ListBox_create_box(&listbox);
		ClearInnerRegionListBox(&listbox);
		fill_listbox(&listbox);
								//change layout-no, se mantiene el layout del teclado
	}	
	//////////////////////////////////////////////////////////////////////////////////
	static void showpropzone(byte zone)	
	{
		blink_captionof_barzone_RUN(zone);		
		ks0108SelectFont(SC, ks0108ReadFontData, BLACK);
		FindAndPrintNameOfZone(zone, xiCHIP1);			//namez(zone);
		ks0108FillRect(1,63-17,61,0,BLACK);				//recta horizontal separadora
		dcporcentz(if_fadingactive_nextdc_else_dc(zone));	//maybe in progressive your duty-cycle	
	}

	////////////////////////////////////////////////////////////////////////////////////////
	
	signed char scene_add_handler(void)
	{
		if (thisps.scheduler == 1)//initialize once
		{
			thisps.scheduler = 0x00;
			
			DrawOnlyMarcoGlobalGLCD();
			CaptionOfAllZones();
			DrawOnlyDivisionAt63();
			DrawBarsVertOfAllZones();
			//ingresa con dc actual
			for (byte i=0;i<NUM_ZONAS;i++){directfill_barlevel(i, objzone[i].dc);}
			//
			//direct_clearallpixel_less1border_CHIP1();
			showpropzone(thisps.zone);

			//Inicializa listbox /reusando objeto
			ListBox_init_dimension(&listbox, 0,0,63,63, SC, SC_HEIGHT);
			ListBox_LoadnewDB(&listbox,	vNombreDeEscena_FLASH,_MAX_LENGTH_NOM_ESCENAS_, _NUMERO_ELEM_vNombreDeEscena_FLASH);

			//registrar las funciones al entrar
			thisps.operating_mode = (OPERATINGMODE_THISPS)DO_SCENE;//MODO0
			change_operating_mode(thisps_fxs, thisps.operating_mode);

			//thisps.codereturn = (CODERETURN_TOSHELL)NOEXIT;
			thismenups.currentmenu = 0x00;
		}
		else if (thisps.scheduler == 2)		
		{
			if (thisps.operating_mode > (OPERATINGMODE_THISPS)MODE0)
			{
				menu_handler();//enter when is necessary
				dialogbox_sino_handler(); //
				//menu_handler tiene su propio flag q solo da ingreso 1 vez...
				//por eso que flujo 2, no puede ser reseteado, ahora apunta a este lado
			}
		}
		
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	static void key1_1fmode0(void)
	{
		objzone[thisps.zone].bf.print_dcporcentz = ON;
		ps_fading_inbk.bf.printdisplay = ENABLE;
		_PreEx_DimmingUp(thisps.zone);
	}
	
	static void key2_1fmode0(void)
	{
		objzone[thisps.zone].bf.print_dcporcentz = ON;
		ps_fading_inbk.bf.printdisplay = ENABLE;
		_PreEx_DimmingDown(thisps.zone);
	}
	
	static void key3_1fmode0(void)//Or before
	{
		ps_fading_inbk.bf.printdisplay = ENABLE;
		objzone[thisps.zone].bf.print_dcporcentz = ON;

		if (objzone[thisps.zone].cfgmodeof_restoreonoff == (CFGMODEOF_RESTOREONOFF)RESTORE_AND_ON_OFF)
			{RestoreOnOff_mode1(thisps.zone);}
		else //ONLY_ON_OFF
			{RestoreOnOff_mode2(thisps.zone);}
		
		//playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);				
	}
	
	static void key3_1fmode0_aft(void)
	{
		ps_fading_inbk.bf.printdisplay = ENABLE;
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
	{	key3_1fmode1();}

	static void key4_1fmode1(void)//ya estando en modo1
	{
		switch (thismenups.currentmenu)
		{
			case 1://nombrar escena?
			dialogbox_nb.dialogbox_sino_ESC();
			break;
			case 2://Salir? a shell
			dialogbox_nb.dialogbox_sino_ESC();
			break;
			
			//__3 y 4 son complementarios
			case 3:
			//estando en listbox, pregunta: Cancelar seleccion?
			thismenups.bf.shownewmenu =1;
			thismenups.currentmenu =4;
			//
			thisps.operating_mode = (OPERATINGMODE_THISPS)MODE1;
			change_operating_mode(thisps_fxs, thisps.operating_mode);
			
			flujo = 2;
			//
			//presenta, y cancela a la vez
			break;
			
			case 4:
			thismenups.currentmenu =3;//escapa de pregunta y vuelve
			
			thisps.operating_mode = (OPERATINGMODE_THISPS)MODE2;
			change_operating_mode(thisps_fxs, thisps.operating_mode);
			
			flujo = 2;
			
			//direct_clearallpixel_less1border_CHIP1();
			listbox_name_scene();
			dialogbox_nb.cr = -1;
			break;
			//__
			
			case 5:
			//retorna a current listbox
			
			thisps.operating_mode = (OPERATINGMODE_THISPS)MODE1;
			change_operating_mode(thisps_fxs, thisps.operating_mode);
			
			flujo = 2;
			break;
			
			case 6:
			//retorna a current listbox
			break;
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////

	static void key1_1fmode2(void)
	{
		ListBox_Ex(&listbox, LISTBOX_FORD);
		playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
	}
	static void key2_1fmode2(void)
	{
		ListBox_Ex(&listbox,LISTBOX_BACK);
		playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
	}
	static void key3_1fmode2(void)//before
	{
		//show menu
		thismenups.bf.shownewmenu =1;
		thismenups.currentmenu = 5;
		
		thisps.operating_mode = (OPERATINGMODE_THISPS)MODE1;
		change_operating_mode(thisps_fxs, thisps.operating_mode);
	flujo = 2;		
		
		playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
	}
	static void key3_1fmode2_aft(void)
	{	key3_1fmode2();	}
	
	static void key1_2fmode0(void)
	{
		playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
		selectzone(TOLEFT);
	}
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	static void selectzone(signed char dir)
	{
		thisps.zone += dir;
		
		if (thisps.zone < 0) 
		{
			blink_captionof_barzone_STOP(0);
			thisps.zone = NUM_ZONAS-1;

			//
			thisps.operating_mode = (OPERATINGMODE_THISPS)DO_LISTBOX;//MODE1;
			change_operating_mode(thisps_fxs, thisps.operating_mode);
			//		
			
			thisps.scheduler = 2;	
		
			//
			thismenups.bf.shownewmenu =1;
			thismenups.currentmenu = 1;
			//
waitfor_kbclean.bf.wait = 1;//add
			//
		}
		else if (thisps.zone >= NUM_ZONAS) 
		{
			blink_captionof_barzone_STOP(NUM_ZONAS-1);
			thisps.zone = 0;
			//
			thisps.operating_mode = (OPERATINGMODE_THISPS)DO_LISTBOX;//MODE1;
			change_operating_mode(thisps_fxs, thisps.operating_mode);
			
			thisps.scheduler= 2;	
			
			//
			thismenups.bf.shownewmenu =1;
			thismenups.currentmenu = 1;
			//

waitfor_kbclean.bf.wait = 1;//add
			//
		}
		else 
		{
			blink_captionof_barzone_STOP(thisps.zone + (dir*-1) );
			direct_clearallpixel_less1border_CHIP1();
			showpropzone(thisps.zone);
		}
	}

	static void menu_handler(void)
	{
		//if ( thismenups.currentmenu == 0)//initializer once again	//{}
		
		if (thismenups.bf.shownewmenu)
		{
			thismenups.bf.shownewmenu = 0;//1 vez ejecuta
			
			softcentric_clearallpixel_less1border_CHIP1();
			
			switch (thismenups.currentmenu)
			{
				case 1://Nombrar escenas?
						ks0108GotoXY(2+4,2+17);		ks0108Puts_P(PSTR("Nombrar"));
						ks0108GotoXY(2+8,2+17+12);	ks0108Puts_P(PSTR("Escena ?"));
						dialogbox_sino(2,2,(DIALOGBOX_OPTIONS)_DIALOGBOX_OPTION_SI_);//reinicializa dialogbox_nb.cr = -1
				break;
				
				case 2://Salir de este menu
						ks0108GotoXY(2+4,2+23);	ks0108Puts_P(PSTR("Salir"));
						dialogbox_sino(2,2,(DIALOGBOX_OPTIONS)_DIALOGBOX_OPTION_SI_);
				break;
				
				case 3:
				break;
				
				case 4:
						//_menu_in_listbox
						ks0108GotoXY(2+4,2+17);		ks0108Puts_P(PSTR("Cancelar"));
						ks0108GotoXY(2+8,2+17+12);	ks0108Puts_P(PSTR("seleccion?"));
						dialogbox_sino(2,2,(DIALOGBOX_OPTIONS)_DIALOGBOX_OPTION_SI_);
				break;
				
				case 5:
						//_menu_in_post_select_name(void)
						//si presiona M, simplemente retrocede, al igual que si presiona No
						ks0108GotoXY(2+4,2+17);		ks0108Puts_P(PSTR("Confirma"));
						ks0108GotoXY(2+4,2+17+12);	ks0108Puts_P(PSTR("seleccion?"));
						dialogbox_sino(2,2,(DIALOGBOX_OPTIONS)_DIALOGBOX_OPTION_SI_);
						
						//ks0108GotoXY(2+4,40);		
						//ks0108Puts_P(&vNombreDeEscena_FLASH[_get_last_elementpointed(&listbox)]);
				break;
				
				case 6:
						ks0108GotoXY(2+4,2+17);		ks0108Puts_P(PSTR("Guardar"));
						ks0108GotoXY(2+8,2+17+12);	ks0108Puts_P(PSTR("cambios?"));
						dialogbox_sino(2,2,(DIALOGBOX_OPTIONS)_DIALOGBOX_OPTION_SI_);
				break;
			}				
		}
	}

	static void dialogbox_sino_handler(void)
	{
		if (dialogbox_nb.cr > -1)//exist any answer by user
		{
			if (dialogbox_nb.cr == 1)//[Si]
			{
				switch (thismenups.currentmenu)
				{
					case 1:
					thisps.operating_mode = (OPERATINGMODE_THISPS)MODE2;
					change_operating_mode(thisps_fxs, thisps.operating_mode);
					
					flujo = 2;
					
					listbox_name_scene();
					
					thismenups.currentmenu = 3;//lo deja preparado
					dialogbox_nb.cr = -1;
					break;
					
					case 2:
					
					//thisps.codereturn = (CODERETURN_TOSHELL)CR_CREATE_SCENE_HANDLER;//sale a sub-menu principal
					//
					shell.coderet_shell.coderet = 2;//thisps.codereturn;
					shell.coderet_shell.bf.retfromps =1;
					flujo = 1;
					//
					break;
					
					//
					case 3:
					break;
					case 4:
					//cancela seleccion de nombre en listbox
					return_to_doing_scene();//change to (OPERATINGMODE_THISPS)MODE0;
					break;
					//
					
					case 5:
					//confirma seleccion
					thismenups.bf.shownewmenu =1;
					thismenups.currentmenu = 6;
					break;
					
					case 6:
					//guarda
					break;
				}
				
				
				bfCommonProcess0.Timmer_BlinkCaption = OFF;
			}
			
			if (dialogbox_nb.cr == 0)//[No]
			{
				switch (thismenups.currentmenu)
				{
					case 1:
					thismenups.bf.shownewmenu = 1;
					thismenups.currentmenu++;
					break;
					
					case 2:
					return_to_doing_scene();
					break;
					
					//__
					case 3:
					
					break;
					case 4:
					thismenups.currentmenu=3;//escapa de pregunta y vuelve
					
					thisps.operating_mode = (OPERATINGMODE_THISPS)MODE2;
					change_operating_mode(thisps_fxs, thisps.operating_mode);
					
					flujo = 2;
					
					//direct_clearallpixel_less1border_CHIP1();
					listbox_name_scene();
					dialogbox_nb.cr = -1;
					break;
					//__
					
					case 5:
					thismenups.currentmenu=3;//escapa de pregunta y vuelve
					
					thisps.operating_mode = (OPERATINGMODE_THISPS)MODE2;
					change_operating_mode(thisps_fxs, thisps.operating_mode);
					
					flujo = 2;
					//direct_clearallpixel_less1border_CHIP1();
					listbox_name_scene();
					
					dialogbox_nb.cr = -1;
					break;
					
					case 6:
					break;
				}
			}
		}
		
	}

	static void return_to_doing_scene(void)
	{
		//restore
		softcentric_clearallpixel_less1border_CHIP1();
		showpropzone(thisps.zone);	//Re-blink through this function
		
		thismenups.currentmenu = 0x00;
		
		thisps.operating_mode = (OPERATINGMODE_THISPS)MODE0;
		change_operating_mode(thisps_fxs, thisps.operating_mode);
		
		flujo = 1;
	}
	
	
	

//EEPROM_WriteByte( (byte *)&objscene_commonprop_epp.totalofscenes, objscene.totalofscenes);
//save_scene_epp( scene.totalofscene,	_get_last_elementpointed(&listbox) );	


