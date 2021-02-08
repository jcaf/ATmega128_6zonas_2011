/*
 * EliminarEscena_1.c
 *
 * Created: 09/04/2012 04:10:06 p.m.
 *  Author: jcaf
 */ 
	#include "Includes/InitializeAllModules.h"

	//----------------------------------------------------
	typedef enum _OPERATINGMODE_THISPS
	{
		DELETE_SCENE=0,		//MODO0
		DO_DIAGBOX=1,		//MODE1,
	}OPERATINGMODE_THISPS;

	static struct _thisps
	{
		OPERATINGMODE_THISPS operating_mode;
		signed char scheduler0;
		signed char scheduler1;
	}thisps;
	//----------------------------------------------------
	//--timmer declarations
	#define THIS_TIMMER_NUMOFTIMMERS (3)
	static volatile struct _this_timmer_nb
	{
		_timmer_nb timmer_nb[THIS_TIMMER_NUMOFTIMMERS];

	}this_timmer_nb ={
		.timmer_nb[0].time = 100/20,//>>    cada 150ms
		.timmer_nb[1].time = 100/20,//<<    cada 150ms
		.timmer_nb[2].time = 350/20,//[ok] cada 350ms
	};
	static void timmer_nb__ps(void);

	volatile void *p2_this_timmer_nb = &this_timmer_nb;//wrapper
	//----------------------------------------------------

	///////////////////////////////////////////////////////
	static struct _ps_search_scene
	{
		byte event_ok__sm0;

	}ps_search_scene;

	///////////////////////////////////////////////////////

	static void key1_1fmode0(void);
	static void key2_1fmode0(void);
	static void key3_1fmode0(void);
	static void key3_1fmode0_aft(void);
	static void key4_1fmode0(void);

	static void key1_1fmode1(void);
	static void key2_1fmode1(void);
	static void key3_1fmode1(void);
	static void key3_1fmode1_aft(void);
	static void key4_1fmode1(void);

	static void key3_2fmode0(void);
	//static void key3_2fmode1(void);//POR AHORA SE PROHIBE LA SALIDA EN MODE1=DIALOG BOX

	static void _return2shell(void);
	
	static void ps_search_scene__handler(void);

	static void _entering_to_preview_scene(void);
	void _delete_scene(void);
	
	static PTRFXrVOID thisps_fxs[4][MAXNUM_MODE_BY_PS][KB_TOTALOFKEYS]={
		{
		{&key1_1fmode0, &key2_1fmode0, &key3_1fmode0, &key4_1fmode0},	//doing delete scenes
		{&key1_1fmode1, &key2_1fmode1, &key3_1fmode1, &key4_1fmode1},	//doing dialog-box
		{&DUMMYFX, &DUMMYFX, &DUMMYFX, &DUMMYFX},	
		{&DUMMYFX, &DUMMYFX, &DUMMYFX, &DUMMYFX},	
		},
		{
		{&DUMMYFX, &DUMMYFX, &key3_1fmode0_aft, &DUMMYFX},
		{&DUMMYFX, &DUMMYFX, &key3_1fmode1_aft, &DUMMYFX},
		{&DUMMYFX, &DUMMYFX, &DUMMYFX, &DUMMYFX},
		{&DUMMYFX, &DUMMYFX, &DUMMYFX, &DUMMYFX},
		},
		{
		{&DUMMYFX, &DUMMYFX, &key3_2fmode0, &DUMMYFX},
		{&DUMMYFX, &DUMMYFX, &DUMMYFX, &DUMMYFX},//key3_2fmode1 se prohibe salida M+3 en dialog box
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

	////////////////////////////////////////////////////////////////////////////////////////
	#define schedule(val) do{thisps.scheduler0 = val; thisps.scheduler1=0x00;}while(0)

	void delete_scene_handler(void)
	{
		if (thisps.scheduler0 == 0)//initialize once
		{
			if (thisps.scheduler1 == 0)
			{
				thisps.scheduler1++;
				
				//p2_this_timmer_nb = &this_timmer_nb;
				
				//
				thisps.operating_mode = (OPERATINGMODE_THISPS)DELETE_SCENE;//MODO0
				change_operating_mode(thisps_fxs, thisps.operating_mode);
				//
				ks0108ClearScreen();
				
				ks0108DrawRect(0,0,63,63,BLACK);//division en 2 paneles: 
				ks0108DrawRect(65,0,191-65,63,BLACK);
				if (currentscene.num_scene != ISNOT_A_SAVED_SCENE)
					{previewscene.num_scene =  currentscene.num_scene;}
				else
					{previewscene.num_scene =  0;}
				//direct_clearallpixel_less1border_CHIP1();
				_entering_to_preview_scene();
				
				//if (ps_scene.totalofscenes > 0)		//es administrado por _entering_to_preview_scene();				
				//{
					//CaptionOfAllZones();
					//DrawBarsVertOfAllZones();
					//_write_display_threshold_allzone();	
				//}
			}
			schedule(-1);	//espera un nuevo evento
		}			
		//////////////////////////////////////////////////////////////////////////////////
		if (thisps.scheduler0 == 1)	//schedule(1)
		{
			if (thisps.scheduler1 == 0)//1.- show any menu
			{
				thisps.scheduler1++;

				softcentric_clearallpixel_less1border_CHIP1();
				ks0108GotoXY(2+15,2+23);	ks0108Puts_P(PSTR("Salir?"));
				dialogbox_sino(2,2,(DIALOGBOX_OPTIONS)_DIALOGBOX_OPTION_SI_);
			}
			if (thisps.scheduler1 == 1)//2.- wait for answer
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
					else if ((dialogbox_nb.cr == (DIALOGBOX_CR)NO)||(dialogbox_nb.cr == (DIALOGBOX_CR)SCAPE))
					{	
						_entering_to_preview_scene();

						thisps.operating_mode = (OPERATINGMODE_THISPS)DELETE_SCENE;//
						change_operating_mode(thisps_fxs, thisps.operating_mode);
						//
						__dialogbox_cr_wasread();
					}
					
				}
			}
		}
	
		//space delay
		timmer_nb__ps();
	
		//space delay
		if (this_timmer_nb.timmer_nb[0].sm_app >0)
		{
			_draw_triangle_rigth_solid_black(54,52);
			this_timmer_nb.timmer_nb[0].sm_app = 0x00;	
		}
		if (this_timmer_nb.timmer_nb[1].sm_app >0)
		{
			_draw_triangle_left_solid_black(9,52);
			this_timmer_nb.timmer_nb[1].sm_app = 0x00;
		}
		ps_search_scene__handler();
	}
	
	///////////////////////////////////////////////////////////////////////////////////
	static void _options_preview_scene(void)
	{
		if (previewscene.num_scene >= ps_scene.totalofscenes )
			{previewscene.num_scene = 0x00;}
		
		if (previewscene.num_scene < 0)
			{previewscene.num_scene = ps_scene.totalofscenes-1;}

		previewscene.preview();
	}
	
	static void _entering_to_preview_scene(void)
	{
		previewscene.preview__bkframewnd();
		
		if (ps_scene.totalofscenes > 0)
		{
			ks0108GotoXY(6,19);ks0108Puts_P(PSTR("Escena:"));
			_options_preview_scene();
		}
		else
		{
			ks0108GotoXY(6,19);ks0108Puts_P(PSTR("No existen"));
			ks0108GotoXY(10,30);ks0108Puts_P(PSTR("escenas"));
			
			ks0108FillRect(66,1,190-66,61,WHITE);//clear bars/titles of zones
		}		
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////////	
	//doing preview
	static void key1_1fmode0(void)
	{	
		playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);

		if (ps_scene.totalofscenes > 0)
		{
			_draw_triangle_rigth_solid_white(54,52);
			//		
			this_timmer_nb.timmer_nb[0].counter = 0x0;
			this_timmer_nb.timmer_nb[0].sm_app = 0x0;
			this_timmer_nb.timmer_nb[0].run = 1;
			//_delay_ms(200);
			//_draw_triangle_rigth_solid_white(54,52);
			previewscene.num_scene++;
			_options_preview_scene();
		}		
	}
	static void key2_1fmode0(void)
	{
		playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
		
		if (ps_scene.totalofscenes > 0)
		{
			_draw_triangle_left_solid_white(9,52);
			//
			this_timmer_nb.timmer_nb[1].counter = 0x0;
			this_timmer_nb.timmer_nb[1].sm_app = 0x0;
			this_timmer_nb.timmer_nb[1].run = 1;
			//_delay_ms(200);
			//_draw_triangle_left_solid_white(9,52);
			previewscene.num_scene--;
			_options_preview_scene();
		}		
	}
	
	static void key3_1fmode0(void)
	{
		playsound(SOUND_BUZZER, _BUZZER_ACCEPT_SOUND0_);
		//
		this_timmer_nb.timmer_nb[2].counter = 0x0;
		this_timmer_nb.timmer_nb[2].sm_app = 0x0;
		this_timmer_nb.timmer_nb[2].run = 1;
		
		ps_search_scene.event_ok__sm0 = 1;
		
		_KB_inhibited();
	}
	static void key3_1fmode0_aft(void){}

	static void key4_1fmode0(void)
	{
		playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
		
		thisps.operating_mode = (OPERATINGMODE_THISPS)DO_DIAGBOX;//cambia a modo 1
		change_operating_mode(thisps_fxs, thisps.operating_mode);
		schedule(1);
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
	static void key4_1fmode1(void)
	{
		playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
		dialogbox_nb.dialogbox_sino_ESC();
	}
	
	static void key3_2fmode0(void)
	{
		_return2shell();//sale con schedule 0
		//_KB_waitfor_kb_free_and_complete_ps();
		
		playsound(SOUND_BUZZER, _BUZZER_ACCEPT_SOUND0_);
	}
	//static void key3_2fmode1(void)//por ahora prohibido salida por combinacion M+3 en dialog box
	
	//...............................................................
	static void ps_search_scene__handler(void)
	{
		if (ps_search_scene.event_ok__sm0 > 0)
		{
			if (ps_search_scene.event_ok__sm0 == 1)
			{
				if (this_timmer_nb.timmer_nb[2].sm_app == 0)
				{
					this_timmer_nb.timmer_nb[2].sm_app++;//incremented in interrupt
					
					ks0108FillRect(25,47,14,10,WHITE);
					ks0108GotoXY(26,47);ks0108Puts_P(PSTR("ok"));//show ok inverted->osea presionado
					ks0108InvertRect(25,47, 14,10);
				}
				else if (this_timmer_nb.timmer_nb[2].sm_app == 2)
				{
					this_timmer_nb.timmer_nb[2].sm_app = 0x00;
					//
					ks0108InvertRect(25,47, 14,10);//restore [ok] NO inverted
				
					if (ps_scene.totalofscenes > 0)
					{
						_delete_scene();
								//
								softcentric_clearallpixel_less1border_CHIP1();
								window_Aviso(2,2);
								ks0108GotoXY(2+10,2+17);	ks0108Puts_P(PSTR("Escena"));
								ks0108GotoXY(2+4,2+17+12);ks0108Puts_P(PSTR("eliminada"));
								_delay_ms(1000);
								//
						_entering_to_preview_scene();
					}
					else
						{_return2shell();}
					
					_KB_waitfor_kb_free_and_complete_ps();

					ps_search_scene.event_ok__sm0++;
				}
			}
			
			if (ps_search_scene.event_ok__sm0 == 2)
			{
				thisps.operating_mode = (OPERATINGMODE_THISPS)DELETE_SCENE;
				change_operating_mode(thisps_fxs, thisps.operating_mode);
				//
				ps_search_scene.event_ok__sm0 = 0x00;
			}
		}
	}
	
	static void _return2shell(void)
	{
		shell.coderet = (CODERETURN_TOSHELL)RESTORE_SHELL;
		schedule(0);
		_KB_waitfor_kb_free_and_complete_ps();
	}	
			
	static void timmer_nb__ps(void)
	{
		timmer_nb__processing( (void *)&this_timmer_nb,THIS_TIMMER_NUMOFTIMMERS);
	}
	
	void _delete_scene(void)
	{
		byte i;
		byte zone;
		byte startpoint_to_delete;
		
		startpoint_to_delete = previewscene.num_scene;
		
		if (ps_scene.totalofscenes > 0)
		{
			if (previewscene.num_scene == currentscene.num_scene)	//si previamente currentscene.num_scene = ISNOT_A_SAVED_SCENE,
			{														//Ya no lo vuelve a poner pues, simplemente no entra a la condicion
				currentscene.num_scene = ISNOT_A_SAVED_SCENE;
			}
			if (previewscene.num_scene == ps_scene.totalofscenes-1)//si se encuentra en la ultima posicion
			{
				if (previewscene.num_scene > 0)//se prohibe bajar a -1, queda truncado a 0
				{
					previewscene.num_scene--;//borrara y disminuye como lo hara "ps_scene.totalofscenes"
				}
			}
			
			//2 corrimiento
			for (i = startpoint_to_delete; i<ps_scene.totalofscenes-1; i++)
			{
				//i-1 = i;
				
				for (zone=0; zone<NUM_ZONAS; zone++)
				{
					if (sizeof(TYPEDC) == sizeof(unsigned int))
					{
						EEPROM_WriteWord( (TYPEDC *)&objstorage_scene_epp[i].objzone[zone].dc,  get_dcofzone_ofscene_EEP(i+1,zone));
					}			
					else if (sizeof(TYPEDC) == sizeof(unsigned char))
					{
						EEPROM_WriteByte( (TYPEDC *)&objstorage_scene_epp[i].objzone[zone].dc,  get_dcofzone_ofscene_EEP(i+1,zone));	
					}
				}
				EEPROM_WriteByte((byte*) &objstorage_scene_epp[i].num_name, EEPROM_ReadByte((byte *) &objstorage_scene_epp[i+1].num_name));
			}

			//3.- descontar
			ps_scene.totalofscenes--;
			EEPROM_WriteByte( (byte *)&objscene_commonprop_epp.totalofscenes, ps_scene.totalofscenes);
		}
	}
