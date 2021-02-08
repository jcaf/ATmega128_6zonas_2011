/*
 * MenuScene_1.c
 *
 * Created: 9/19/2012 5:37:33 PM
 *  Author: JCaf
 */ 
#include "Includes/InitializeAllModules.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
////////////////////////////////////////////////////////////////////////////
//USADO PARA SALIR DEL PASO, entrega a Bruno Sabado 8 Dic.2012
////////////////////////////////////////////////////////////////////////////
static volatile byte borrame;// 200 //c/5x200 1000ms
volatile byte borrame_flag;
volatile byte borrame_start;
volatile byte borrame_counter;
void _borrame_timming(void);
#define _borrame_timming_run()		do{borrame_start=1; borrame=0x00; borrame_counter=0x00; borrame_flag =0;}while(0)
#define _borrame_timming_restart()	do{borrame_counter=0x00;}while(0)
#define _borrame_timming_stop()		do{borrame_start = 0;}while(0)

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


	//----------------------------------------------------
	typedef enum _OPERATINGMODE_THISPS
	{
		DOING_SCENE = 0,	//MODO0
		DO_DIAGBOX=1,		
		PREVIEW_SCENE=2,
		SYNCH_ALLZONES=3,
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

	volatile void *p1_this_timmer_nb = &this_timmer_nb;//wrapper
	
	//----------------------------------------------------

	static struct _ps_search_scene
	{
		byte event_ok__sm0;

	}ps_search_scene;


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
	
	static void key1_1fmode2(void);
	static void key2_1fmode2(void);
	static void key3_1fmode2(void);
	static void key4_1fmode2(void);
	
	static void key1_1fmode3(void);
	static void key2_1fmode3(void);
	static void key3_1fmode3(void);
	static void key3_1fmode3_aft(void);
	static void key4_1fmode3(void);
	
	static void key1_2fmode0(void);
	static void key2_2fmode0(void);
	static void key3_2fmode0(void);
	
	//static void key3_2fmode1(void);//POR AHORA SE PROHIBE LA SALIDA EN MODE1=DIALOG BOX
	static void key3_2fmode2(void);//POR AHORA SE PROHIBE LA SALIDA EN MODE1=DIALOG BOX
	
	//
	static void switch_to_zone(void);
	static void _return2shell(void);
	
	static void _synch_all(void);
	static void _desynch_all(void);
	static void _entering_to_preview_scene(void);
	static void _show_the_scene(void);
	static void ps_search_scene__handler(void);
	static void this_rule(void);
	
	static PTRFXrVOID thisps_fxs[4][MAXNUM_MODE_BY_PS][KB_TOTALOFKEYS]={
		{
		{&key1_1fmode0, &key2_1fmode0, &key3_1fmode0, &key4_1fmode0},	//doing dimming
		{&key1_1fmode1, &key2_1fmode1, &key3_1fmode1, &key4_1fmode1},	//doing dialog-box
		{&key1_1fmode2, &key2_1fmode2, &key3_1fmode2, &key4_1fmode2},	//doing preview
		{&key1_1fmode3, &key2_1fmode3, &key3_1fmode3, &key4_1fmode3},	//doing synchronizing	
		},
		{
		{&DUMMYFX, &DUMMYFX, &key3_1fmode0_aft, &DUMMYFX},
		{&DUMMYFX, &DUMMYFX, &key3_1fmode1_aft, &DUMMYFX},
		{&DUMMYFX, &DUMMYFX, &DUMMYFX, &DUMMYFX},
		{&DUMMYFX, &DUMMYFX, &key3_1fmode3_aft, &DUMMYFX},
		},
		{
		{&key1_2fmode0, &key2_2fmode0, &key3_2fmode0, &DUMMYFX},
		{&DUMMYFX, &DUMMYFX, &DUMMYFX, &DUMMYFX},//key3_2fmode1 se prohibe salida M+3 en dialog box
		{&DUMMYFX, &DUMMYFX, &key3_2fmode2, &DUMMYFX},
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

	static BOOL isnot_a_saved_scene(void)
	{
		byte zone;
		for (zone=0;zone<NUM_ZONAS;zone++)
		{
			if (if_fadingactive_nextdc_else_dc(zone) != currentscene.objzone[zone].dc)//objzone[zone].dc != currentscene.objzone[zone].dc
				{return 1;}	
		}
		return 0;
	}

	void scene_handler(void)
	{
		byte zone;
		
		if (thisps.scheduler0 == 0)//initialize once
		{
			if (thisps.scheduler1 == 0)
			{
				thisps.scheduler1++;

				ps_fading_inbk.bf.printdisplay = ENABLE;	//Ahora Habilita incondicionalmente para todo este proceso
				
				//Add for compatibility On/Off/Restore 
				for (zone=0; zone<NUM_ZONAS; zone++)
				{
						if (objzone[zone].commingfrom == (COMMINGFROM)LASTEVENT_DIRECTONOFF)
						{
							objzone[zone].commingfrom = (COMMINGFROM)LASTEVENT_CLEAR;
							//apagando el flag hace q al hacer 1 toque(on/off/restore), lo deje en OFF completamente
							//y no baje a un restore "dcr" previo.
							/*
							ESTO VA A HACER Q SI REGRESO SIN HACER NADA EN SCENE(), PIERDA EL PUNTO DE RESTAURACION
							TENDRA
							*/
						}
				}
				//

				if (!crossover_scene_zone.from_zone )//si no vino directo desde zona con M+2
				{
					ks0108ClearScreen();
					ks0108DrawRect(0,0,63,63,BLACK);//division en 2 paneles
					ks0108DrawRect(65,0,191-65,63,BLACK);
					CaptionOfAllZones();
					DrawBarsVertOfAllZones();
					_write_display_threshold_allzone();

					for (zone=0;zone<NUM_ZONAS;zone++)
					{
						//directclearall_barlevel(zone);	//previamente ocurrio un ks0108ClearScreen();
						directfill_barlevel(zone, objzone[zone].dc);
					}
				}	
				else 
					{crossover_scene_zone.from_zone =0;}			
				
			
				//if (currentscene.num_scene != ISNOT_A_SAVED_SCENE)//tal vez vino modificado desde zona
				//{	
				//	if (isnot_a_saved_scene())	{currentscene.num_scene = ISNOT_A_SAVED_SCENE;}
				//}					
				//_all_dcs_taked_as_currentscene();
				
				//initialize previewscene.num_scene
				this_rule();
				
				if (currentscene.num_scene != ISNOT_A_SAVED_SCENE)
					{previewscene.num_scene = currentscene.num_scene;}
				else
					{previewscene.num_scene = 0x00;}
				
				direct_clearallpixel_less1border_CHIP1();
				_print_texts_scene(currentscene.num_scene);

				//p1_this_timmer_nb = &this_timmer_nb;
				//
				thisps.operating_mode = (OPERATINGMODE_THISPS)DOING_SCENE;//MODO0
				change_operating_mode(thisps_fxs, thisps.operating_mode);
				//
			
				////
				//time_printdisp__run();
				//date_printdisp__run();
				////
						
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
					else if ((dialogbox_nb.cr == (DIALOGBOX_CR)NO)||(dialogbox_nb.cr == (DIALOGBOX_CR)SCAPE))
					{	
						schedule(2); //sgte. menu
						//
						__dialogbox_cr_wasread();
					}
					
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
				
				ks0108GotoXY(2+10,2+17);	ks0108Puts_P(PSTR("Buscar"));
				ks0108GotoXY(2+11,2+17+12);	ks0108Puts_P(PSTR("escena ?"));
				dialogbox_sino(2,2,(DIALOGBOX_OPTIONS)_DIALOGBOX_OPTION_SI_);
			}
			if (thisps.scheduler1 == 1)//wait for answer
			{
				//thisps.scheduler1++;
				
				if (dialogbox_nb.cr > (DIALOGBOX_CR)NONE )
				{
					if (dialogbox_nb.cr ==  (DIALOGBOX_CR)YES)
					{
						softcentric_clearallpixel_less1border_CHIP1();
						_entering_to_preview_scene();//buscar scene cambia a (OPERATINGMODE_THISPS)PREVIEW_SCENE
						schedule(-1);
						//
						__dialogbox_cr_wasread();
					}
					else if ((dialogbox_nb.cr ==  (DIALOGBOX_CR)NO)||(dialogbox_nb.cr ==  (DIALOGBOX_CR)SCAPE))
					{
						schedule(3);//sgte. menu
						//
						__dialogbox_cr_wasread();
					}
					
				}
			}
		}
		
		//////////////////////////////////////////////////////////////////////////////////
		if (thisps.scheduler0 == 3)	//schedule(3)
		{
			if (thisps.scheduler1 == 0)
			{
				thisps.scheduler1++;
				softcentric_clearallpixel_less1border_CHIP1();
				ks0108GotoXY(2+4,2+17);		ks0108Puts_P(PSTR("Cambiar a "));
				ks0108GotoXY(2+13,2+17+12);	ks0108Puts_P(PSTR("zonas ?"));
				dialogbox_sino(2,2,(DIALOGBOX_OPTIONS)_DIALOGBOX_OPTION_SI_);
			}
			if (thisps.scheduler1 == 1)
			{
				//thisps.scheduler1++;
				if (dialogbox_nb.cr > (DIALOGBOX_CR)NONE )
				{
					if (dialogbox_nb.cr ==  (DIALOGBOX_CR)YES)
					{
						switch_to_zone();
						//_waitforclean_keys();
						//
						__dialogbox_cr_wasread();
					}
					else if ((dialogbox_nb.cr ==  (DIALOGBOX_CR)NO)||(dialogbox_nb.cr ==  (DIALOGBOX_CR)SCAPE))
					{
						schedule(4);//sgte
						//
						__dialogbox_cr_wasread();
					}
				
				}
			}
		}
		//////////////////////////////////////////////////////////////////////////////////
		if (thisps.scheduler0 == 4)	//schedule(4)
		{
			if (thisps.scheduler1 == 0)
			{
				thisps.scheduler1++;
				softcentric_clearallpixel_less1border_CHIP1();
				ks0108GotoXY(2+3,2+17);		ks0108Puts_P(PSTR("Sincroniza"));
				ks0108GotoXY(2+5,2+17+12);	ks0108Puts_P(PSTR("Dimming"));
				dialogbox_sino(2,2,(DIALOGBOX_OPTIONS)_DIALOGBOX_OPTION_SI_);
			}
			
			if (thisps.scheduler1 == 1)
			{
				//thisps.scheduler1++;
				if (dialogbox_nb.cr > (DIALOGBOX_CR)NONE )
				{
					if (dialogbox_nb.cr ==  (DIALOGBOX_CR)YES)
					{
						_synch_all();//deja schedule(-1);
						//
						__dialogbox_cr_wasread();
					}
					else if ((dialogbox_nb.cr ==  (DIALOGBOX_CR)NO)||(dialogbox_nb.cr ==  (DIALOGBOX_CR)SCAPE))
					{
						direct_clearallpixel_less1border_CHIP1();
						_show_the_scene();//_directshow_the_scene();
						
						//previewscene.scene = currentscene.scene;//supuestamente en este modo no se toca preview scene
						thisps.operating_mode = (OPERATINGMODE_THISPS)DOING_SCENE;
						change_operating_mode(thisps_fxs, thisps.operating_mode);
						//
						
						schedule(-1);
						//
						__dialogbox_cr_wasread();
						//tal vez se va prohibir la salida M+3 en dialog box MODE1
					}
				}
			}
		}
		//////////////////////////////////////////////////////////////////////////////////
		// estando en _menu_preview_scene
		if (thisps.scheduler0 == 5)	//schedule(5)
		{
			if (thisps.scheduler1 == 0)
			{
				thisps.scheduler1++;
				softcentric_clearallpixel_less1border_CHIP1();
				ks0108GotoXY(2+7,2+17);		ks0108Puts_P(PSTR("Cancelar"));
				ks0108GotoXY(2+3,2+17+12);	ks0108Puts_P(PSTR("busqueda?"));
				dialogbox_sino(2,2,(DIALOGBOX_OPTIONS)_DIALOGBOX_OPTION_SI_);
			}
			
			if (thisps.scheduler1 == 1)
			{
				//thisps.scheduler1++;
				if (dialogbox_nb.cr > (DIALOGBOX_CR)NONE )
				{
					if (dialogbox_nb.cr ==  (DIALOGBOX_CR)YES)
					{
						///////////esto es cancelar busqueda//////////
						softcentric_clearallpixel_less1border_CHIP1();
						_show_the_scene();	//_directshow_the_scene();
						
						//vuelve a su estado original
						if (currentscene.num_scene != ISNOT_A_SAVED_SCENE)
							{previewscene.num_scene =  currentscene.num_scene;}
						else
						{
							previewscene.num_scene =  0x00;
						}
						//
						
						thisps.operating_mode = (OPERATINGMODE_THISPS)DOING_SCENE;
						change_operating_mode(thisps_fxs, thisps.operating_mode);
						schedule(-1);
						
						//
						__dialogbox_cr_wasread();
					}
					else if ((dialogbox_nb.cr ==  (DIALOGBOX_CR)NO)||(dialogbox_nb.cr ==  (DIALOGBOX_CR)SCAPE))
					{
						_entering_to_preview_scene();


						//
						_borrame_timming_run();
						//

						//
						__dialogbox_cr_wasread();
					}
				}
			}
		}
		
		//////////////////////////////////////////////////////////////////////////////////
		//desynchronizing
		if (thisps.scheduler0 == 6)	//schedule(6)
		{
			if (thisps.scheduler1 == 0)
			{
				thisps.scheduler1++;
				softcentric_clearallpixel_less1border_CHIP1();
				ks0108GotoXY(2+6,2+17);		ks0108Puts_P(PSTR("Cancelar"));
				ks0108GotoXY(2+3,2+17+12);	ks0108Puts_P(PSTR("sincroniz?"));
				dialogbox_sino(2,2,(DIALOGBOX_OPTIONS)_DIALOGBOX_OPTION_SI_);
			}
			
			if (thisps.scheduler1 == 1)
			{
				//thisps.scheduler1++;
				if (dialogbox_nb.cr > (DIALOGBOX_CR)NONE )
				{
					if (dialogbox_nb.cr ==  (DIALOGBOX_CR)YES)
					{
						_desynch_all();	//leave schedule(-1);	
						//
						__dialogbox_cr_wasread();	
					}
					else if ((dialogbox_nb.cr ==  (DIALOGBOX_CR)NO)||(dialogbox_nb.cr ==  (DIALOGBOX_CR)SCAPE))
					{
						_synch_all();	//leave schedule(-1);
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
	
	//USADO PARA SALIR DEL PASO, entrega a Bruno Sabado 8 Dic.2012
	_borrame_timming();
	
	}
	
	///////////////////////////////////////////////////////////////////////////////////
	static void _options_preview_scene(void)
	{
		if (previewscene.num_scene >= ps_scene.totalofscenes )
			{previewscene.num_scene = 0x00;}
		
		if (previewscene.num_scene < 0)
			{previewscene.num_scene = ps_scene.totalofscenes-1;}

		ps_fading_inbk.bf.printdisplay = DISABLE;
		
		previewscene.preview();
	}

	static void _entering_to_preview_scene(void)//solo por el frame
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
		}		
		
		thisps.operating_mode = (OPERATINGMODE_THISPS)PREVIEW_SCENE;//
		change_operating_mode(thisps_fxs, thisps.operating_mode);
	}
	
	BOOL _anyzone_isnt_zero(void)
	{
		byte zone;
		for (zone=0;zone<NUM_ZONAS;zone++)
		{
			if (if_fadingactive_nextdc_else_dc(zone)>0 )
				return 1;			
		}			
		return 0;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////	
	//doing scene
	static void key1_1fmode0(void)
	{
		playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
		
		if ( (currentscene.num_scene != ISNOT_A_SAVED_SCENE))//previamente ya se comprobo si no corresponde a una escena guardada
			{previewscene.num_scene++;}
		
		_entering_to_preview_scene();
		
		//
		_borrame_timming_run();
		//
	}
	static void key2_1fmode0(void)	//on/off/restore on scene
	{
		byte zone;

		if (is_fadingprocess_allzone_finish())
		{
				if (_anyzone_isnt_zero())
				{
					//TODOS OFF!
					playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
					
					if (_all_dcs_of_currentscene__lessequalthan_threshold() ) //== TODOS 0x00 o MENOR Q THRESHOLD
					{
						//Siguiendo Regla 1. se supone q para este tipo de escene == TODOS 0%(por preguardado o puesto al "vuelo")
						//APAGADO CON RestoreOnOff para conservar el dcr!
						for (zone=0; zone<NUM_ZONAS; zone++)
						{
							objzone[zone].bf.print_dcporcentz=OFF;
							
							//	
							if (objzone[zone].cfgmodeof_restoreonoff == (CFGMODEOF_RESTOREONOFF)RESTORE_AND_ON_OFF)
								{RestoreOnOff_mode1(zone);}
							else //ONLY_ON_OFF
								{RestoreOnOff_mode2(zone);}
							//					
						}
					}													
					else
					{
						//apaga todas las zonas
						for (zone=0;zone<NUM_ZONAS;zone++)
						{
							if (currentscene.objzone[zone].dc> objzone[zone].thrshld )//or >0
							{
								//Patch! analizar cuando entra en 0 y el restore.
								//	directclearall_barlevel(zone);
								//	directfill_barlevel(zone, objzone[zone].dc);
								// ahora espero a que haya finalizado la accion
								//
								objzone[zone].bf.print_dcporcentz=OFF;
								
								if (objzone[zone].cfgmodeof_restoreonoff == (CFGMODEOF_RESTOREONOFF)RESTORE_AND_ON_OFF)
							{	RestoreOnOff_mode1(zone);}
								else //ONLY_ON_OFF
							{	RestoreOnOff_mode2(zone);}
							}
						}
							
					}										
				
				}
				else //TODOS ON
				{
					//caso especial
					if (_all_dcs_of_currentscene__lessequalthan_threshold() ) //== TODOS 0x00 o MENOR Q THRESHOLD
					{
						//FUERZA TODO A 100%
						for (zone=0; zone<NUM_ZONAS; zone++)
						{
							objzone[zone].bf.print_dcporcentz=OFF;
							
							setting_preupdate_dc(zone, MAX_VAL_DUTYCYCLE);
							updatedc_acctypeofload(zone);
							//
							if (objzone[zone].TypeOfLoad == NoDimmable)	
								{clear_and_directfill_barlevel(zone, objzone[zone].dc);}
						}
						//
					}
					else
					{
					
						//
						for (zone=0; zone<NUM_ZONAS; zone++)
						{
							objzone[zone].bf.print_dcporcentz=OFF;
							
							setting_preupdate_dc(zone, currentscene.objzone[zone].dc);
							updatedc_acctypeofload(zone);
							//
							if (objzone[zone].TypeOfLoad == NoDimmable)	
								{clear_and_directfill_barlevel(zone, objzone[zone].dc);}
			
							////Add..
							//if ( previewscene.dc_from_epp[zone] >= objzone[zone].dc )
							//{
								//directfill_barlevel(zone, objzone[zone].dc);
							//}
							//else
							//{
								//clear_and_directfill_barlevel(zone,objzone[zone].dc);
								//preview_dc_barlevel(zone, previewscene.dc_from_epp[zone]);
							//}
							//Add..
						}
					}
					//Restaura solo las q son >0
					//DEBERIA RECARGAR A LA ESCENA DONDE ES!!!!
					//for (zone=0;zone<NUM_ZONAS;zone++) 
					//{
						//if (currentscene.objzone[zone].dc> objzone[zone].thrshld )//or >0
						//{
							//objzone[zone].bf.print_dcporcentz=OFF;
							//
							//if (objzone[zone].cfgmodeof_restoreonoff == (CFGMODEOF_RESTOREONOFF)RESTORE_AND_ON_OFF)
								//{RestoreOnOff_mode1(zone);}
							//else //ONLY_ON_OFF
								//{RestoreOnOff_mode2(zone);}
						//}
					//}
				}		
		}
	
	}
	
	static void key3_1fmode0(void){}
	
	static void key3_1fmode0_aft(void)
	{
		playsound(SOUND_BUZZER, _BUZZER_ACCEPT_SOUND0_);
		_synch_all();
	}
	
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
	//static void key3_2fmode1(void)//por ahora prohibido salida por combinacion M+3 en dialog box
	
	////////////////////////////////////////////////////////////////////////////////////////////////	
	//doing preview
	static void key1_1fmode2(void)
	{	
		playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);

		if (ps_scene.totalofscenes > 0)
		{
			//
			_borrame_timming_restart();
			//
			
			
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
	static void key2_1fmode2(void)
	{
		playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
		
		if (ps_scene.totalofscenes > 0)
		{
			//
			_borrame_timming_restart();
			//
			
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
	
	static void key3_1fmode2(void)
	{	
		//
		_borrame_timming_stop();
		//

	
		playsound(SOUND_BUZZER, _BUZZER_ACCEPT_SOUND0_);
		//
		this_timmer_nb.timmer_nb[2].counter = 0x0;
		this_timmer_nb.timmer_nb[2].sm_app = 0x0;
		this_timmer_nb.timmer_nb[2].run = 1;
		
		ps_search_scene.event_ok__sm0 = 1;
		
		_KB_inhibited();
	}
	
	static void key4_1fmode2(void)
	{
		//
		_borrame_timming_stop();
		//
		
		playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
		
		thisps.operating_mode = (OPERATINGMODE_THISPS)DO_DIAGBOX;
		change_operating_mode(thisps_fxs, thisps.operating_mode);
		schedule(5);
	}	
	//...............................................................
	static void ps_search_scene__handler(void)
	{
		byte zone;

		if (ps_search_scene.event_ok__sm0 > 0)
		{
			if (ps_search_scene.event_ok__sm0 == 1)
			{
				//if (currentscene.num_scene == previewscene.num_scene)
				//{	////warning: escena ya existe.	//}	//else{
				
				if (this_timmer_nb.timmer_nb[2].sm_app == 0)
				{
					this_timmer_nb.timmer_nb[2].sm_app++;//incremented in interrupt
					
					//show ok inverted -> osea presionado
					ks0108FillRect(25,47,14,10,WHITE);
					ks0108GotoXY(26,47);ks0108Puts_P(PSTR("ok"));
					ks0108InvertRect(25,47, 14,10);
					//
					if (ps_scene.totalofscenes > 0)
					{
						for (zone=0;zone<NUM_ZONAS;zone++)
						{
							graphbarlevel.g[zone].Qsaved = graphbarlevel.g[zone].Q;
							graphbarlevel.g[zone].bf.check_bar = 1;
						}
					
						//1-2-3 ejecturse en ese orden	
						//1- Formalizar todos las zonas van a ejecutar su respectivo cambio sin importar su naturaleza
						for (zone=0;zone<NUM_ZONAS;zone++)	//add
							{objzone[zone].bf.changing_of_escene = 1;}//podria ahorrar la senializacion de acuerdo a la naturaleza de la carga
						//2-
						//Ya debe ir ejecutandose el cambio de escena, no esperar a q se cumpla el tiempo para el [OK] invertido.
						
						ps_fading_inbk.bf.printdisplay = ENABLE;
						
						previewscene.execute();
						//Add. patching
						for (zone=0; zone<NUM_ZONAS; zone++)
							{objzone[zone].onoffrstr.bf.pto_rstr = OFF;	}
						//
						
						//3-							
						//si despues de previewscene.execute() no se ha senializado un proceso de fading
						//entonces apagar el flag
						for (zone=0;zone<NUM_ZONAS;zone++)
						{
							if (objzone[zone].TypeOfLoad == Dimmable)
							{	if (objzone[zone].TypeOfEffect == Fading)
								{
									if (objzone[zone].sfading.bf.fading_active == OFF)//si no fue puesto a 1, quiere decir q el diff == 0, no hay cambio(fading) que hacer
										{objzone[zone].bf.changing_of_escene = 0x0;}
								}
							}
							else if (objzone[zone].TypeOfLoad == NoDimmable)
							{	if (objzone[zone].TypeOfEffect == Direct)
									{objzone[zone].bf.changing_of_escene = 0x0;}
							}
						}					
							
						//update current scene
						currentscene.num_scene = previewscene.num_scene;
							
						for (zone=0; zone<NUM_ZONAS; zone++)
							{currentscene.objzone[zone].dc = previewscene.dc_from_epp[zone];}
					}					
				}
				else if (this_timmer_nb.timmer_nb[2].sm_app == 2)
				{
					this_timmer_nb.timmer_nb[2].sm_app = 0x00;
					//
					ks0108InvertRect(25,47, 14,10);//[ok] //restore to [ok] -> solo por formalidad
				
					direct_clearallpixel_less1border_CHIP1();
					_print_texts_scene(currentscene.num_scene);			
							
					ps_search_scene.event_ok__sm0++;
						
					_KB_waitfor_kb_free_and_complete_ps();
				}
			}
			
			if (ps_search_scene.event_ok__sm0 == 2)
			{
				thisps.operating_mode = (OPERATINGMODE_THISPS)DOING_SCENE;
				change_operating_mode(thisps_fxs, thisps.operating_mode);
				//
				ps_search_scene.event_ok__sm0 = 0x00;
			}
		}
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////////	
	//doing synchronizing
	static void key1_1fmode3(void)
	{
		byte i;
		for (i=0; i<NUM_ZONAS; i++)
		{
			objzone[i].bf.print_dcporcentz = OFF;
			_PreEx_DimmingUp(i);
		}
	}
	static void key2_1fmode3(void)
	{
		byte i;
		for (i=0; i<NUM_ZONAS; i++)
		{
			objzone[i].bf.print_dcporcentz = OFF;
			_PreEx_DimmingDown(i);
		}
	}
	
	static void key3_1fmode3(void)
	{}//no se usa on/off, tendria q bajar a doing scene, por ahora
		
	static void key3_1fmode3_aft(void)//desynchronize
	{
		playsound(SOUND_BUZZER, _BUZZER_ACCEPT_SOUND0_);
		_desynch_all();
	}
	static void key4_1fmode3(void)
	{
		playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
		
		thisps.operating_mode = (OPERATINGMODE_THISPS)DO_DIAGBOX;
		change_operating_mode(thisps_fxs, thisps.operating_mode);

		schedule(6);
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	static void key1_2fmode0(void)
	{
		_KB_waitfor_kb_free_and_complete_ps();
	}
	static void key2_2fmode0(void)//switch to zone
	{
		switch_to_zone();
		_KB_waitfor_kb_free_and_complete_ps();
		
		playsound(SOUND_BUZZER, _BUZZER_ACCEPT_SOUND0_);
	}

	static void key3_2fmode0(void)
	{
		_return2shell();//sale con schedule 0
		//_KB_waitfor_kb_free_and_complete_ps();
		
		playsound(SOUND_BUZZER, _BUZZER_ACCEPT_SOUND0_);
	}
	
	static void key3_2fmode2(void)// salida intempestiva en preview
	{
		playsound(SOUND_BUZZER, _BUZZER_ACCEPT_SOUND0_);
		
		direct_clearallpixel_less1border_CHIP1();
		_show_the_scene();	//_directshow_the_scene();
		//
		if (currentscene.num_scene != ISNOT_A_SAVED_SCENE)
			{previewscene.num_scene =  currentscene.num_scene;}
		else
			{previewscene.num_scene =  0x00;}
		//
		thisps.operating_mode = (OPERATINGMODE_THISPS)DOING_SCENE;//mode0
		change_operating_mode(thisps_fxs, thisps.operating_mode);
												//esta salida SI esperara a que KEY4 sea soltada, y todo el buffer del teclado este liberado
		_KB_waitfor_kb_free_and_complete_ps();	//Add. por seguridad, pues si presiona 1 vez mas, como ya se encuentra
												//en doing_scene, automaticamente saldra,,, por ahora lo restringo
												//a esperar a q suelte para admitir prox. combinacion
	}	

	
	////////////////////////////////////////////////////////////////////////////////////////
	//mostrara de acuerdo a si se encuentra en plena actividad de fading o no
	////////////////////////////////////////////////////////////////////////////////////////
	static void _show_the_scene(void)
	{
		//previamente si isnt_a_storage_scene()==1 -> ya fue tomado por _all_dcs_taked_as_scene();
		//pues solo hay 2 maneras de detectar el cambio, al entrar a la funcion
		//o despues de hacer una sincronizacion
		//Se da por hecho que ya ha sido analizado si no pertenece a una escena guardada
		_print_texts_scene(currentscene.num_scene);
		
		ps_fading_inbk.bf.printdisplay = ENABLE;
		
		byte zone;
		for (zone=0;zone<NUM_ZONAS;zone++)
		{
			directclearall_barlevel(zone);
			
			if (objzone[zone].sfading.bf.fading_active)
			{
				if (objzone[zone].bf.changing_of_escene)
				{
					if (objzone[zone].sfading.kte_addsub == +1)//making dimming-up
					{
						preview_dc_barlevel(zone, currentscene.objzone[zone].dc);
						directfill_barlevel(zone, objzone[zone].dc);
					}
					else // -1 making dimming-down
					{
						directfill_barlevel(zone, objzone[zone].dc);
						preview_dc_barlevel(zone, currentscene.objzone[zone].dc);
					}
				}
				else
				{	directfill_barlevel(zone, objzone[zone].dc); }
			}
			else
			{	directfill_barlevel(zone, objzone[zone].dc); }
		}			
	}
	
	static void switch_to_zone(void)
	{
		//bfCommonProcess0.Timmer_BlinkCaption = OFF;
		crossover_scene_zone.from_scene = 1;
		menu_operational.goto_address = address_menu_main__zone;
		shell.coderet = (CODERETURN_TOSHELL)INTERNAL_SELECTION;
		schedule(0);	//todas las salidas dejan para una entrada en MODO 0
		//_waitforclean_keys();
	}
	static void _return2shell(void)
	{
		shell.coderet = (CODERETURN_TOSHELL)RESTORE_SHELL;
		schedule(0);
		_KB_waitfor_kb_free_and_complete_ps();
	}	
	//////////////////////////////////////////////////////////////////////////
	static void messagesynch(void)
	{
		ks0108SelectFont(SC, ks0108ReadFontData, BLACK);

		ks0108GotoXY(3,3);ks0108Puts_P(PSTR("Sincroniza"));
		ks0108InvertRect(2,2,59,12);
		
		ks0108GotoXY(7,3+SC_HEIGHT);		ks0108Puts_P(PSTR("Todas las"));
		ks0108GotoXY(15,3+(SC_HEIGHT<<1));	ks0108Puts_P(PSTR("zonas"));
		
		ks0108FillRect(1,63-17,61,0,BLACK);							//Dibujar recta horizontal separadora
		
		ks0108FillRect(10,63-16,(SC_WIDTH*6) ,12,WHITE);			//limpiar
		_DrawUpTriangleState(12,53);								//ks0108Puts_P(PSTR("U/D/OnOff"));
		_DrawDownTriangleState(27,53);
		_DrawOnOffState(50, 50);
	}
	//hay 2 posibilidades, q pare la ejecucion actual o q no este disponible sino hasta q se haya terminado de ejecutar el proceso
	//Tendria q crear una fx q pare el proceso de dimming fading si se encuentra en ejectucion
	
	//VOY A LIMITARLO A SINCRONIZAR CUANDO ESTE DETENIDO TODO PROCESO!!!	
	static void _synch_all(void)
	{
		byte zone;
		
		//++para cualquier proceso q se encuentre en ejecucion
		//para todo proceso!
		for (zone=0; zone<NUM_ZONAS; zone++)
		{
			if (objzone[zone].sfading.bf.fading_active == ON)	//FINALIZO TODO PROCESO
			   {objzone[zone].sfading.bf.fading_active = OFF;}
			
			if (objzone[zone].bf.changing_of_escene == ON)	//stop algun cambio de scene
			   {objzone[zone].bf.changing_of_escene = OFF;}
			
			//ESTO VA A HACER Q SI REGRESO SIN HACER NADA EN SCENE(), PIERDA EL PUNTO DE RESTAURACION
			if (objzone[zone].commingfrom == (COMMINGFROM)LASTEVENT_DIRECTONOFF)
			    {objzone[zone].commingfrom = (COMMINGFROM)LASTEVENT_CLEAR;}
		
			directclearall_barlevel(zone);
			directfill_barlevel(zone, objzone[zone].dc);
		}					
		
		//++
		thisps.operating_mode = (OPERATINGMODE_THISPS)SYNCH_ALLZONES;//synch
		change_operating_mode(thisps_fxs, thisps.operating_mode);
		
		blink_captionof_barzone_RUNALL();
		softcentric_clearallpixel_less1border_CHIP1();
		messagesynch();
		
		schedule(-1);
	}
	
	static void _desynch_all(void)
	{
		blink_captionof_barzone_STOPALL();
		
		softcentric_clearallpixel_less1border_CHIP1();
				
		//_directshow_the_scene();
		//No hay necesidad de pintar,pues se acaba de escribir en display por eso no se llama a _directshow_the_scene()
		if (currentscene.num_scene != ISNOT_A_SAVED_SCENE)//NO COINCIDIO!!! CON LOS NIVELES DE LA ESCENA ORIGI.ANTES DE HACER SINCRONIZACION
		{
			if (isnot_a_saved_scene())
			{currentscene.num_scene = ISNOT_A_SAVED_SCENE;	}
		}
		_all_dcs_taked_as_currentscene();
				
		_print_texts_scene(currentscene.num_scene);
				
		thisps.operating_mode = (OPERATINGMODE_THISPS)DOING_SCENE;//desynch
		change_operating_mode(thisps_fxs, thisps.operating_mode);

		schedule(-1);
	}
			
	//-------------------------------------
	//timmer space
	static void timmer_nb__ps(void)
	{
		timmer_nb__processing((void *)&this_timmer_nb,THIS_TIMMER_NUMOFTIMMERS);
	}
	
	///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////
	/*
	RULES:
	
	1.*Si un currentscene == TODOS 0x00 o MENOR Q THRESHOLD
		solo puede conmutar entre 100% y su nivel (<= threshold -> 0%)
	2. TODOS FUERON BLANKeados por dimming o NUNCA fueron restaurados desde q el uC arranco		se decide por seguir usando la escena que se encuentra activa
	*/
	//ENTERING
	static void this_rule(void)
	{
		byte zone;
		
		if ( !_all_current_dcs_are_lessequalthan_threshold() )	//Al menos there is a dc > THRESHOLD (or ZERO)
		{
			if (_all_dcs_of_currentscene__lessequalthan_threshold() ) //== TODOS 0x00 o MENOR Q THRESHOLD
			{
				//APPLY Rule 1
				if (!_all_dcs_of_objzone__equalthan_100porcent())//!= 100%)	
				{
					_all_dcs_taked_as_currentscene();
					currentscene.num_scene = ISNOT_A_SAVED_SCENE;//Una current_scene con todos sus niveles 0% ha sido modificado
				}
			}
			else //caso-contrario cualquier escena pregrabada/o en el "aire" y que todos sus niveles NO son CEROS
			{
				if (!_all_dcs_of_currentscene__areequalthan_current_dcs() )
				{
					_all_dcs_taked_as_currentscene();
					currentscene.num_scene = ISNOT_A_SAVED_SCENE;
					
					//Add. patching
					for (zone=0; zone<NUM_ZONAS; zone++)
						{objzone[zone].onoffrstr.bf.pto_rstr = OFF;	}
					//
				}	
			}
		
		}
		else //Absolutely All dcs less-equal than THRESHOLD( or ZERO)
		{
			//+aniado para el caso especial de escena 0x00
			if (_all_dcs_of_currentscene__lessequalthan_threshold() ) //== TODOS 0x00 o MENOR Q THRESHOLD
			{
				if (_all_zones_have_pto_rstr_OFF() ) //==pto_rstr OFF!
				{
					//no pasa nada, sigue de largo -> RETOMA LA ULTIMA ESCENA COMO SIEMPRE
				}
				else
				{
					//AL MENOS HAY UN DCR
					for (zone=0; zone<NUM_ZONAS; zone++)
					{
						if (objzone[zone].onoffrstr.bf.pto_rstr == ON)
						{
							//
							if (objzone[zone].onoffrstr.dcr < MAX_VAL_DUTYCYCLE) //basta q sea diferente
							{
								currentscene.num_scene = ISNOT_A_SAVED_SCENE;
								currentscene.objzone[zone].dc = objzone[zone].onoffrstr.dcr;	
							}
							//
						}
						else
						{
							//SE REFUERZA A 0, a pesar de que la condicion DE ENTRADA SENALA Q TODOS ESTAN A 0X00
							currentscene.objzone[zone].dc = 0x0;	//ESTA DEMAS
						}
					}	
				}
			}
			else
			{
			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
				if (_all_zones_have_pto_rstr_OFF() ) //==pto_rstr OFF!
				{
					//APPLY Rule 2
					/*
					LA ESCENA NO ES MODIFICADA!
					
					Todos fueron blankeados x dimming o NUNCA fueron restaurados desde q el uC arranco
					y se han mantenido asi.
					
					Se aplica la segunda regla.
					
					Si fueron blankeados, estonces se perdio el punto de restauracion
					esta es la razon de recargar directamente con los valores de escena actual y no usar
					RestoreOnOff_mode1()
									
					*/
				}
				else //al menos 1 dcr se puede recuperar
				{
					//AL MENOS 1 dcr se puede recuperar					//Al menos quiere decir que es posible que desee ver algun punto de restauracion.					//Repondra o tomara como escena a las que tienen su punto de restauracion "ON"					for (zone=0; zone<NUM_ZONAS; zone++)					{						if (objzone[zone].onoffrstr.bf.pto_rstr == ON)						{							//							if (currentscene.objzone[zone].dc != objzone[zone].onoffrstr.dcr) //basta q sea diferente								{currentscene.num_scene = ISNOT_A_SAVED_SCENE;}							//							currentscene.objzone[zone].dc = objzone[zone].onoffrstr.dcr;//a. el q quedo en scene																						//   o'																						//b. el q ha sido modificado en zonas						}						else						{							currentscene.objzone[zone].dc = 0x0;							//los puntos de restauracion han sido tocados O SIMPLEMENTE SIEMPRE ESTUVO A OFF
							#ifdef USE_SCENE_MIRROR								currentscene.objzone[zone].dc = SCENE_MIRROR.dc//del ultimo mirror guardado								//El uso de mirror podria hacer q en *LEEME, se decida								//posteriormente si ha cambiado la escenea, al salir del for/if del q								//se encuentra. Tal vez las decisiones que se adopten puedan ser								//no tan rigida si alguien cambia tal vez en un cierto porcentaje hacia arriba/abajo							#endif						}					}				}
			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			}
		}
	}
	
	
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	////////////////////////////////////////////////////////////////////////////
	//USADO PARA SALIR DEL PASO, entrega a Bruno Sabado 8 Dic.2012
	////////////////////////////////////////////////////////////////////////////
	void Timmer_TimmingToBackScene(void)//llamado desde ISR
	{
		//static volatile byte borrame;// 200 //c/5x200 1000ms
		
		if (borrame_start == 1)
		{
			if (++borrame >= 200)	
			{
				borrame = 0x00;
				borrame_flag = 1;
			}
		}
		
	}

void _borrame_timming(void)
{
	if (borrame_start == 1)
	{
		if (borrame_flag == 1) //cada 1s
		{
			borrame_flag = 0;
			
			if (++borrame_counter >= 5)//cada 8ms
			{
				borrame_start = 0;	//stop timming
				borrame_counter =0;
				//
				///////////esto es cancelar busqueda//////////
				softcentric_clearallpixel_less1border_CHIP1();
				_show_the_scene();	//_directshow_the_scene();
				
				//vuelve a su estado original
				if (currentscene.num_scene != ISNOT_A_SAVED_SCENE)
					{previewscene.num_scene =  currentscene.num_scene;}
				else
				{
					previewscene.num_scene =  0x00;
				}
				//
				
				thisps.operating_mode = (OPERATINGMODE_THISPS)DOING_SCENE;
				change_operating_mode(thisps_fxs, thisps.operating_mode);
				schedule(-1);
				
			}
		}
		
	}
}
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

