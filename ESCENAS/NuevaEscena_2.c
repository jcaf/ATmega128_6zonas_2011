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
			
		signed char scheduler0;
		signed char scheduler1;
		
	}thisps;
	
	static void key1_1fmode0(void);//doing dialogbox [si][no]
	static void key2_1fmode0(void);//doing dialogbox [si][no]
	static void key3_1fmode0(void);//bef//doing dialogbox [si][no]
	static void key3_1fmode0_aft(void);
	static void key4_1fmode0(void);
	
	static void key1_1fmode1(void);//doing dialogbox [si][no]
	static void key2_1fmode1(void);//doing dialogbox [si][no]
	static void key3_1fmode1(void);//bef//doing dialogbox [si][no]
	static void key3_1fmode1_aft(void);
	static void key4_1fmode1(void);
	
	static void key1_1fmode2(void);
	static void key2_1fmode2(void);
	static void key3_1fmode2(void);//before
	static void key3_1fmode2_aft(void);
	static void key4_1fmode2(void);
	
	static void key1_2fmode0(void);
	static void key3_2fmode0(void);
	
	
	static PTRFXrVOID thisps_fxs[4][MAXNUM_MODE_BY_PS][KB_TOTALOFKEYS]={
		{
		{&key1_1fmode0, &key2_1fmode0, &key3_1fmode0, &key4_1fmode0},
		{&key1_1fmode1, &key2_1fmode1, &key3_1fmode1, &key4_1fmode1},
		{&key1_1fmode2, &key2_1fmode2, &key3_1fmode2, &key4_1fmode2},
		{&DUMMYFX, &DUMMYFX, &DUMMYFX, &DUMMYFX},
		},
		{
		{&DUMMYFX, &DUMMYFX, &key3_1fmode0_aft, &DUMMYFX},
		{&DUMMYFX, &DUMMYFX, &key3_1fmode1_aft, &DUMMYFX},
		{&DUMMYFX, &DUMMYFX, &key3_1fmode2_aft, &DUMMYFX},
		{&DUMMYFX, &DUMMYFX, &DUMMYFX, &DUMMYFX},
		},
		{
		{&key1_2fmode0, &DUMMYFX, &key3_2fmode0, &DUMMYFX},
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
	static void return_to_mode0(void);
	static void _return2shell(void);
	static void _save_new_scene(void);

	static void showpropzone(byte zone)
	{
		blink_captionof_barzone_RUN(zone);
		ks0108SelectFont(SC, ks0108ReadFontData, BLACK);
		FindAndPrintNameOfZone(zone, xiCHIP1);			//namez(zone);
		ks0108FillRect(1,63-17,61,0,BLACK);				//recta horizontal separadora
		dcporcentz(if_fadingactive_nextdc_else_dc(zone));	//maybe in progressive your duty-cycle
	}
	//////////////////////////////////////////////////////////////////////////////////
	static void listbox_name_scene(void)
	{
		direct_clearallpixel_less1border_CHIP1();//patch for clear.
		
		ListBox_create_box(&listbox);
		ClearInnerRegionListBox(&listbox);
		fill_listbox(&listbox);
		//change layout-no, se mantiene el layout del teclado
	}	
	////////////////////////////////////////////////////////////////////////////////////////
	#define schedule(val) do{thisps.scheduler0 = val; thisps.scheduler1=0x00;}while(0)	
	
	void scene_add_handler(void)
	{
		if (thisps.scheduler0 == 0)//initialize once
		{
			if (thisps.scheduler1 == 0)
			{
				thisps.scheduler1++;

				ps_fading_inbk.bf.printdisplay = ENABLE;

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
				
				//este menu debe empezar con zona 0
				thisps.zone = 0x00;
				
				showpropzone(thisps.zone);//direct_clearallpixel_less1border_CHIP1();

				//Inicializa listbox /reusando objeto
				ListBox_init_dimension(&listbox, 0,0,63,63, SC, SC_HEIGHT);
				
				ListBox_LoadnewDB(&listbox, (void *)v_names_for_scenes,_MAX_LENGTH_NOM_ESCENAS_, LENGTH__V_NAMES_FOR_SCENES);

				//registrar las funciones al entrar
				thisps.operating_mode = (OPERATINGMODE_THISPS)DO_SCENE;//MODO0
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
				ks0108GotoXY(2+4,2+17);		ks0108Puts_P(PSTR("Nombrar"));
				ks0108GotoXY(2+8,2+17+12);	ks0108Puts_P(PSTR("Escena ?"));
				dialogbox_sino(2,2,(DIALOGBOX_OPTIONS)_DIALOGBOX_OPTION_SI_);//reinicializa dialogbox_nb.cr = -1
			}
			if (thisps.scheduler1 == 1)//wait for answer
			{
				//thisps.scheduler1++;
				
				if (dialogbox_nb.cr > (DIALOGBOX_CR)NONE )
				{
					if (dialogbox_nb.cr ==  (DIALOGBOX_CR)YES)
					{
						thisps.operating_mode = (OPERATINGMODE_THISPS)DO_LISTBOX;
						change_operating_mode(thisps_fxs, thisps.operating_mode);
						
						listbox_name_scene();
						
						schedule(-1);//espera por eventos de menu haciendo list-box
						//
						__dialogbox_cr_wasread();
					}
					else if ((dialogbox_nb.cr ==  (DIALOGBOX_CR)NO)||(dialogbox_nb.cr ==  (DIALOGBOX_CR)SCAPE))
					{
						schedule(2);
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
						_return2shell();
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
		
		//////////////////////////////////////////////////////////////////////////////////
		if (thisps.scheduler0 == 3)	//schedule(3)
		{
			if (thisps.scheduler1 == 0)//muestra la opcion cancelar en pleno list-box
			{
				thisps.scheduler1++;
				//_menu_in_listbox
				softcentric_clearallpixel_less1border_CHIP1();
				ks0108GotoXY(2+4,2+17);		ks0108Puts_P(PSTR("Cancelar"));
				ks0108GotoXY(2+8,2+17+12);	ks0108Puts_P(PSTR("seleccion?"));
				dialogbox_sino(2,2,(DIALOGBOX_OPTIONS)_DIALOGBOX_OPTION_SI_);
			}
			if (thisps.scheduler1 == 1)
			{
				//thisps.scheduler1++;
				if (dialogbox_nb.cr > (DIALOGBOX_CR)NONE )
				{
					if (dialogbox_nb.cr ==  (DIALOGBOX_CR)YES)
					{
						//retorna a doing scenes
						return_to_mode0();//deja schedule(-1);
						//
						__dialogbox_cr_wasread();
					}
					else if ((dialogbox_nb.cr ==  (DIALOGBOX_CR)NO)||(dialogbox_nb.cr ==  (DIALOGBOX_CR)SCAPE))
					{
						//prosigue con listbox
						thisps.operating_mode = (OPERATINGMODE_THISPS)DO_LISTBOX;//bajar a modo dialog-box
						change_operating_mode(thisps_fxs, thisps.operating_mode);
						listbox_name_scene();
						schedule(-1);
						//
						__dialogbox_cr_wasread();
					}
					
					//thisps.scheduler1++;
				}
			}
		}								
		
		//////////////////////////////////////////////////////////////////////////////////
		if (thisps.scheduler0 == 4)	//schedule(4)
		{
			if (thisps.scheduler1 == 0)
			{
				thisps.scheduler1++;
				//si presiona M, simplemente retrocede, al igual que si presiona No
				softcentric_clearallpixel_less1border_CHIP1();
				ks0108GotoXY(2+4,2+17);		ks0108Puts_P(PSTR("Confirma"));
				ks0108GotoXY(2+4,2+17+12);	ks0108Puts_P(PSTR("seleccion?"));
				dialogbox_sino(2,2,(DIALOGBOX_OPTIONS)_DIALOGBOX_OPTION_SI_);
				
				//ks0108GotoXY(2+4,40);
				//ks0108Puts_P(&vNombreDeEscena_FLASH[ListBox_get_last_elementpointed(&listbox)]);
			}
			if (thisps.scheduler1 == 1)
			{
				//thisps.scheduler1++;
				if (dialogbox_nb.cr > (DIALOGBOX_CR)NONE )
				{
					if (dialogbox_nb.cr ==  (DIALOGBOX_CR)YES)
					{
						schedule(5);
						//
						__dialogbox_cr_wasread();
					}
					else if ((dialogbox_nb.cr ==  (DIALOGBOX_CR)NO)||(dialogbox_nb.cr ==  (DIALOGBOX_CR)SCAPE))
					{
						//prosigue con listbox
						thisps.operating_mode = (OPERATINGMODE_THISPS)DO_LISTBOX;//bajar a modo dialog-box
						change_operating_mode(thisps_fxs, thisps.operating_mode);
						listbox_name_scene();
						schedule(-1);
						//
						__dialogbox_cr_wasread();
					}
					
					//thisps.scheduler1++;
				}
			}
		}
		
		//////////////////////////////////////////////////////////////////////////////////
		if (thisps.scheduler0 == 5)	//schedule(5)
		{
			if (thisps.scheduler1 == 0)
			{
				thisps.scheduler1++;
				softcentric_clearallpixel_less1border_CHIP1();
				ks0108GotoXY(2+4,2+17);		ks0108Puts_P(PSTR("Guardar"));
				ks0108GotoXY(2+8,2+17+12);	ks0108Puts_P(PSTR("cambios?"));
				dialogbox_sino(2,2,(DIALOGBOX_OPTIONS)_DIALOGBOX_OPTION_SI_);
			}
			if (thisps.scheduler1 == 1)
			{
				//thisps.scheduler1++;
				if (dialogbox_nb.cr > (DIALOGBOX_CR)NONE )
				{
					if (dialogbox_nb.cr ==  (DIALOGBOX_CR)YES)
					{
						_save_new_scene();
						//
						return_to_mode0();
						//
						__dialogbox_cr_wasread();
					}
					else if (dialogbox_nb.cr ==  (DIALOGBOX_CR)NO)//no existe escape, tiene q decidir!
					{
						return_to_mode0();
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
			
		//playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
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
	{	key3_1fmode1();}
	static void key4_1fmode1(void)//ya estando en modo1
	{
		playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
		dialogbox_nb.dialogbox_sino_ESC();
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//doing list-box
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
		thisps.operating_mode = (OPERATINGMODE_THISPS)DO_DIAGBOX;
		change_operating_mode(thisps_fxs, thisps.operating_mode);
	
		playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
		schedule(4);
	}
	static void key3_1fmode2_aft(void)
	{	key3_1fmode2();	}

	static void key4_1fmode2(void)
	{
		playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
		
		schedule(3); //muestra la opcion cancelar en pleno list-box
		thisps.operating_mode = (OPERATINGMODE_THISPS)DO_DIAGBOX;//bajar a modo dialog-box
		change_operating_mode(thisps_fxs, thisps.operating_mode);
	}
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	static void key1_2fmode0(void)
	{
		playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
		selectzone(TOLEFT);
	}
	static void key3_2fmode0(void)
	{
		blink_captionof_barzone_STOP(thisps.zone);
		_return2shell();//sale con schedule 0
		//_KB_waitfor_kb_free_and_complete_ps();
		
		playsound(SOUND_BUZZER, _BUZZER_ACCEPT_SOUND0_);
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
			blink_captionof_barzone_STOP(thisps.zone + (dir*-1) );
			direct_clearallpixel_less1border_CHIP1();
			showpropzone(thisps.zone);
		}
		//...........................................................................
		if ( (temp < 0) ||(temp>= NUM_ZONAS))
		{
			thisps.operating_mode = (OPERATINGMODE_THISPS)DO_DIAGBOX;//MODE1;
			change_operating_mode(thisps_fxs, thisps.operating_mode);
			//
			schedule(1);
			_KB_waitfor_kb_free_and_complete_ps();
		}
		//...........................................................................
	}
	
	static void return_to_mode0(void)
	{
		//restore
		softcentric_clearallpixel_less1border_CHIP1();
		showpropzone(thisps.zone);	//Re-blink through this function
		
		thisps.operating_mode = (OPERATINGMODE_THISPS)DO_SCENE;
		change_operating_mode(thisps_fxs, thisps.operating_mode);
		schedule(-1);	//espero un nuevo evento
	}
	static void _return2shell(void)
	{
		shell.coderet = (CODERETURN_TOSHELL)RESTORE_SHELL;
		schedule(0);
		//blink_captionof_barzone_STOPALL();
		_KB_waitfor_kb_free_and_complete_ps();
	}
	
	static void _save_new_scene(void)
	{
		if (1)//(SceneDontRepeat())
		{
			if (ps_scene.totalofscenes	< _NUM_ESCENAS_MAXIMA_)
			{
				save_scene_epp( ps_scene.totalofscenes,	ListBox_get_last_elementpointed(&listbox) );//la lista en uso actual//listbox_opened
				
				ps_scene.totalofscenes++;	//add+
				EEPROM_WriteByte( (byte *)&objscene_commonprop_epp.totalofscenes, ps_scene.totalofscenes);

				//udpate current scene
				currentscene.num_scene = ps_scene.totalofscenes-1;
				//currentscene.num_name = ListBox_get_last_elementpointed(&listbox); ya no es necesario
				
				_all_dcs_taked_as_currentscene();
				//si ya rebasa los 20 registros de EEPROM, no grabara, entonces los cambios
				//de  duty cycle quedan a ser tratados como UNKNOW
				//++
			}
		}
		
	}

