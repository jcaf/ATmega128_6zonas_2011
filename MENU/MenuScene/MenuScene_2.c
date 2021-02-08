/*
 * MenuScene_1.c
 *
 * Created: 9/19/2012 5:37:33 PM
 *  Author: JCaf
 */ 
#include "Includes/InitializeAllModules.h"
//----------------------------------------------------
	
	typedef enum _OPERATINGMODE_THISPS
	{
		DOING_SCENE = 0,	//MODO0
		DO_DIAGBOX=1,			//MODE1,	//doing dialogbox
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
//----------------------------------------------------
//--timmer declarations
#define THIS_TIMMER_NUMOFTIMMERS (3)
static volatile struct _this_timmer_nb
{
	_timmer_nb timmer_nb[THIS_TIMMER_NUMOFTIMMERS];

}this_timmer_nb ={
	.timmer_nb[0].time = 200/20,//cada 200ms
	.timmer_nb[1].time = 200/20,//cada 200ms
	.timmer_nb[2].time = 200/20,//cada 200ms
};
static void timmer_nb__ps(void);

volatile void *p1_this_timmer_nb= &this_timmer_nb;//wrapper
//----------------------------------------------------
//----------------------------------------------------
	
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
	
	static void key1_2fmode0(void);
	static void key2_2fmode0(void);
	static void key3_2fmode0(void);
	
	//static void key3_2fmode1(void);//POR AHORA SE PROHIBE LA SALIDA EN MODE1=DIALOG BOX
	static void key3_2fmode2(void);//POR AHORA SE PROHIBE LA SALIDA EN MODE1=DIALOG BOX
	
	//
	static void switch_to_zone(void);
	static void _return2shell(void);
	static void _synch_all(void);
	
	static void _directshow_the_scene(void);
	static void _entering_to_preview_scene(void);
	
	static PTRFXrVOID thisps_fxs[4][MAXNUM_MODE_BY_PS][KB_TOTALOFKEYS]={
		{
		{&key1_1fmode0, &key2_1fmode0, &key3_1fmode0, &key4_1fmode0},	//doing dimming
		{&key1_1fmode1, &key2_1fmode1, &key3_1fmode1, &key4_1fmode1},	//doing dialog-box
		{&key1_1fmode2, &key2_1fmode2, &key3_1fmode2, &key4_1fmode2},	//doing preview
		{&key1_1fmode3, &key2_1fmode3, &key3_1fmode3, &DUMMYFX},		//doing synchronizing	
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

	//////////////////////////////////////////////////////////////////////////
	static void messagesynch(void)	
	{
		ks0108SelectFont(SC, ks0108ReadFontData, BLACK);
			
		ks0108GotoXY(4,3);					ks0108Puts_P(PSTR("Sincroniz."));
		ks0108GotoXY(7,3+SC_HEIGHT);		ks0108Puts_P(PSTR("todas las"));
		ks0108GotoXY(12,3+(SC_HEIGHT<<1));	ks0108Puts_P(PSTR("Zonas"));
		
		ks0108FillRect(1,63-17,61,0,BLACK);							//Dibujar recta horizontal separadora
		
		ks0108FillRect(10,63-16,(SC_WIDTH*6) ,12,WHITE);			//limpiar
		_DrawUpTriangleState(12,53);								//ks0108Puts_P(PSTR("U/D/OnOff"));
		_DrawDownTriangleState(27,53);
		_DrawOnOffState(50, 50);
	}

	static BOOL isnt_a_scene_storaged(void)
	{
		byte zone;
		for (zone=0;zone<NUM_ZONAS;zone++)
		{
			if (if_fadingactive_nextdc_else_dc(zone) != currentscene.objzone[zone].dc)//objzone[zone].dc != currentscene.objzone[zone].dc
				{return 1;}	
		}
		return 0;
	}
	
	//restore state
	//scene
	//else synchronizing
	////////////////////////////////////////////////////////////////////////////////////////
	void scene_handler(void)
	{
		if (thisps.scheduler0 == 0)//initialize once
		{
			if (thisps.scheduler1 == 0)
			{
				thisps.scheduler1++;
				
				//__
				//if existe algun zona activa... entonces.. re-habilitar! 
				if (!is_fadingprocess_allzone_finish())
				{ps_fading_inbk.bf.printdisplay = ENABLE;}
				//__
				
				if (!crossover_scene_zone.from_zone )
				{
					ks0108ClearScreen();

					ks0108DrawRect(0,0,63,63,BLACK);
					ks0108DrawRect(65,0,191-65,63,BLACK);
					//ks0108DrawRoundRect(65,0,191-65,63,3, BLACK);
					
					//DrawOnlyMarcoGlobalGLCD();
					//DrawOnlyDivisionAt63();
					CaptionOfAllZones();
					DrawBarsVertOfAllZones();
					
					byte zone;
					//previamente ocurrio un ks0108ClearScreen();
					for (zone=0;zone<NUM_ZONAS;zone++)
						{directfill_barlevel(zone, objzone[zone].dc);}
				}	
				else 
				{
					crossover_scene_zone.from_zone =0;//apaga
				}			
				
				direct_clearallpixel_less1border_CHIP1();
			
				//ADD++
				if (currentscene.num_scene != _UNKNOW_)
				{
					if (isnt_a_scene_storaged())
					{
						currentscene.num_scene = _UNKNOW_;
						currentscene.name = _UNKNOW_;
					}
				}					
				
				_all_dcs_taked_as_scene();

				_print_texts_scene(currentscene.num_scene, currentscene.name);
				
				//
				if (currentscene.num_scene != _UNKNOW_)
					{previewscene.num_scene =  currentscene.num_scene;}
				//
				
				//
				thisps.operating_mode = (OPERATINGMODE_THISPS)DOING_SCENE;//MODO0
				change_operating_mode(thisps_fxs, thisps.operating_mode);
				//
			
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
					}
					else if ((dialogbox_nb.cr == (DIALOGBOX_CR)NO)||(dialogbox_nb.cr == (DIALOGBOX_CR)SCAPE))
					{	
						schedule(2); //sgte. menu
					}
					//
					__dialogbox_cr_wasread();
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
					}
					else if ((dialogbox_nb.cr ==  (DIALOGBOX_CR)NO)||(dialogbox_nb.cr ==  (DIALOGBOX_CR)SCAPE))
					{
						schedule(3);//sgte. menu
					}
					//
					__dialogbox_cr_wasread();
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
					}
					else if ((dialogbox_nb.cr ==  (DIALOGBOX_CR)NO)||(dialogbox_nb.cr ==  (DIALOGBOX_CR)SCAPE))
					{
						schedule(4);//sgte
					}
					
					__dialogbox_cr_wasread();
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
					}
					else if ((dialogbox_nb.cr ==  (DIALOGBOX_CR)NO)||(dialogbox_nb.cr ==  (DIALOGBOX_CR)SCAPE))
					{
						//posible inclusion dentro de un funcion 
						//static void return_to_mode0(void) {}
						direct_clearallpixel_less1border_CHIP1();
						_directshow_the_scene();
						//previewscene.scene = currentscene.scene;//supuestamente en este modo no se toca preview scene
						thisps.operating_mode = (OPERATINGMODE_THISPS)DOING_SCENE;
						change_operating_mode(thisps_fxs, thisps.operating_mode);
						//
						schedule(-1);
						
						//tal vez se va prohibir la salida M+3 en dialog box MODE1
					}
					//
					__dialogbox_cr_wasread();
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
						softcentric_clearallpixel_less1border_CHIP1();
						
						_directshow_the_scene();
						
						//vuelve a su estado original
						if (currentscene.num_scene != _UNKNOW_)
							{previewscene.num_scene =  currentscene.num_scene;}
						//
						
						thisps.operating_mode = (OPERATINGMODE_THISPS)DOING_SCENE;
						change_operating_mode(thisps_fxs, thisps.operating_mode);
						schedule(-1);
					}
					else if ((dialogbox_nb.cr ==  (DIALOGBOX_CR)NO)||(dialogbox_nb.cr ==  (DIALOGBOX_CR)SCAPE))
					{
						//retornar a preview...!!!!!!!!!!!!!!!
						//sigue en la busqueda.
					}
					//
					__dialogbox_cr_wasread();
				}
			}
		}
	//space delay
	timmer_nb__ps();
	if (this_timmer_nb.timmer_nb[0].sm_app >0)
	{
		_draw_triangle_rigth_solid_white(54,52);
		this_timmer_nb.timmer_nb[0].sm_app = 0x00;	
	}
	if (this_timmer_nb.timmer_nb[1].sm_app >0)
	{
		_draw_triangle_left_solid_white(9,52);
		this_timmer_nb.timmer_nb[1].sm_app = 0x00;
	}
	if (this_timmer_nb.timmer_nb[2].sm_app >0)
	{
		ks0108InvertRect(25,47, 14,10);//[ok]
		this_timmer_nb.timmer_nb[2].sm_app = 0x00;
	}
	
	
	
	//space delay
	}
	
	///////////////////////////////////////////////////////////////////////////////////
	static void _options_preview_scene(signed char forw_back)
	{
		if (previewscene.num_scene > ps_scene.totalofscenes+1 )
		{	previewscene.num_scene = 0x00;	
			ks0108FillRect(1,19,61,24,WHITE);
			ks0108GotoXY(6,19);ks0108Puts_P(PSTR("Escena:"));
		}

		if (previewscene.num_scene < 0)
			{previewscene.num_scene = ps_scene.totalofscenes+1;}

		if (forw_back == -1)//coming for backward
		{
			if (previewscene.num_scene == ps_scene.totalofscenes)
			{
				ks0108FillRect(1,19,61,24,WHITE);
				ks0108GotoXY(6,19);ks0108Puts_P(PSTR("Escena:"));
			}	
		}
		
		if (previewscene.num_scene == ps_scene.totalofscenes+1)
		{			//window_Aviso(2,2);
			ks0108FillRect(1,19,61,24,WHITE);
			ks0108GotoXY(9,19);	ks0108Puts_P(PSTR("Cancelar"));
			ks0108GotoXY(5,30);	ks0108Puts_P(PSTR("busqueda?"));
		}
		else
			{previewscene.preview();}
	}
	static void _entering_to_preview_scene(void)
	{
		//if ( !isnt_a_storage_scene() || !is_fadingprocess_allzone_finish() )
		if ( (currentscene.num_scene != _UNKNOW_))// || (!is_fadingprocess_allzone_finish()) )
			{previewscene.num_scene++;}
		
		if (ps_fading_inbk.bf.printdisplay == ENABLE)
			{ps_fading_inbk.bf.printdisplay = DISABLE;}

		previewscene.preview__bkframewnd();

		_options_preview_scene(+1);
		
		//
		//if (thisps.operating_mode == (OPERATINGMODE_THISPS)DOING_SCENE)//esta demas esta comprobacion?
		//{
			thisps.operating_mode = (OPERATINGMODE_THISPS)PREVIEW_SCENE;//
			change_operating_mode(thisps_fxs, thisps.operating_mode);
		//}
		//
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
		_entering_to_preview_scene();
	}
	static void key2_1fmode0(void)	//on/off/restore on scene
	{
		byte zone;
		
		if (_anyzone_isnt_zero())
		{
			//apaga todas las zonas
			for (zone=0;zone<NUM_ZONAS;zone++) 
			{
				if (currentscene.objzone[zone].dc> objzone[zone].thrshld )//or >0
				{
					objzone[zone].bf.print_dcporcentz=OFF;
					RestoreOnOff_mode1(zone);
				}
			}			
		}
		else
		{
			//Restaura solo las q son >0
			for (zone=0;zone<NUM_ZONAS;zone++) 
			{
				if (currentscene.objzone[zone].dc> objzone[zone].thrshld )//or >0
				{
					objzone[zone].bf.print_dcporcentz=OFF;
					RestoreOnOff_mode1(zone);
				}
			}
		}		
	}
	
	static void key3_1fmode0(void){}
	static void key3_1fmode0_aft(void)
	{
		_synch_all();
	}
	
	static void key4_1fmode0(void)
	{
		playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
		//cambia a modo 1
		thisps.operating_mode = (OPERATINGMODE_THISPS)DO_DIAGBOX;
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
		if (ps_fading_inbk.bf.printdisplay == ENABLE)
			{ps_fading_inbk.bf.printdisplay = DISABLE;}
		
		previewscene.num_scene++;
		
		playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
		
		_draw_triangle_rigth_solid_black(54,52);
		//		
		this_timmer_nb.timmer_nb[0].counter = 0x0;
		this_timmer_nb.timmer_nb[0].sm_app = 0x0;
		this_timmer_nb.timmer_nb[0].run = 1;
		//_delay_ms(200);
		//_draw_triangle_rigth_solid_white(54,52);

		_options_preview_scene(+1);

	}
	static void key2_1fmode2(void)
	{
		if (ps_fading_inbk.bf.printdisplay == ENABLE)
			{ps_fading_inbk.bf.printdisplay = DISABLE;}
		
		previewscene.num_scene--;
		playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
		
		_draw_triangle_left_solid_black(9,52);
		//
		this_timmer_nb.timmer_nb[1].counter = 0x0;
		this_timmer_nb.timmer_nb[1].sm_app = 0x0;
		this_timmer_nb.timmer_nb[1].run = 1;
		//_delay_ms(200);
		//_draw_triangle_left_solid_white(9,52);

		_options_preview_scene(-1);
	}
	
	static void key3_1fmode2(void)
	{
		byte zone;
		//
		playsound(SOUND_BUZZER, _BUZZER_ACCEPT_SOUND0_);
		//
ks0108InvertRect(25,47, 14,10);//[ok]
		//this_timmer_nb.timmer_nb[2].counter = 0x0;
		//this_timmer_nb.timmer_nb[2].sm_app = 0x0;
		//this_timmer_nb.timmer_nb[2].run = 1;
		////
_delay_ms(200);
ks0108InvertRect(25,47, 14,10);//[ok]
		if (previewscene.num_scene == ps_scene.totalofscenes+1)//cancelar busqueda
		{

			//
			direct_clearallpixel_less1border_CHIP1();
			_directshow_the_scene();
			//
			if (currentscene.num_scene != _UNKNOW_)
				{previewscene.num_scene =  currentscene.num_scene;}
			//
		}
		else
		{
			//if (currentscene.num_scene == previewscene.num_scene)
			//{
				////warning: escena ya existe.	
				////direct scene			
			//}
			//else
			//{
				ps_fading_inbk.bf.printdisplay = ENABLE;
				for (zone=0;zone<NUM_ZONAS;zone++)
				{
					graphbarlevel.g[zone].Qsaved = graphbarlevel.g[zone].Q;
					graphbarlevel.g[zone].bf.check_bar = 1;
				}
				previewscene.execute();
				
				//udpate current scene
				currentscene.num_scene = previewscene.num_scene;
				currentscene.name = previewscene.name;
				
				for (zone=0; zone<NUM_ZONAS; zone++)
					{currentscene.objzone[zone].dc = previewscene.dc_from_epp[zone];}
				//
				//Si se esta ejecutando el cambio y el usuario presiona el boton de preview
				//
			//}
		}
		
		thisps.operating_mode = (OPERATINGMODE_THISPS)DOING_SCENE;
		change_operating_mode(thisps_fxs, thisps.operating_mode);
	}
	
	static void key4_1fmode2(void)
	{
		thisps.operating_mode = (OPERATINGMODE_THISPS)DO_DIAGBOX;
		change_operating_mode(thisps_fxs, thisps.operating_mode);
		schedule(5);

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
		blink_captionof_barzone_STOPALL();

		//se deja empaquetado para incluir en funcion static void return_to_mode0(void)
		softcentric_clearallpixel_less1border_CHIP1();
		
		//_directshow_the_scene();
		//No hay necesidad de pintar, pues se acaba de escribir en display
		//por eso no se llama a _directshow_the_scene()
		if (currentscene.num_scene != _UNKNOW_)
		{
			if (isnt_a_scene_storaged())
			{
				currentscene.num_scene = _UNKNOW_;
				currentscene.name = _UNKNOW_;
			}
		}
		_all_dcs_taked_as_scene();
		
		_print_texts_scene(currentscene.num_scene, currentscene.name);
		//++
		
		thisps.operating_mode = (OPERATINGMODE_THISPS)DOING_SCENE;//desynch
		change_operating_mode(thisps_fxs, thisps.operating_mode);
		//
		schedule(-1);
		//
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	static void key1_2fmode0(void)
	{
		_waitforclean_keys();
	}
	static void key2_2fmode0(void)//switch to zone
	{
		switch_to_zone();
		_waitforclean_keys();
		
		playsound(SOUND_BUZZER, _BUZZER_ACCEPT_SOUND0_);
	}

	static void key3_2fmode0(void)
	{
		_return2shell();//sale con schedule 0
		_waitforclean_keys();
		
		playsound(SOUND_BUZZER, _BUZZER_ACCEPT_SOUND0_);
	}
	
	static void key3_2fmode2(void)// salida intempestiva en preview
	{
		direct_clearallpixel_less1border_CHIP1();
		//...
		//COMO SE ENCUENTRA EN PREVIEW, quiere decir q si 
		//previamente que si isnt_a_storage_scene==1 -> ya fue tomado por _all_dcs_taked_as_scene();
		//pues solo hay 2 maneras de detectar el cambio, al entrar a la funcion
		//o despues de hacer una sincronizacion
		//if (isnt_a_storage_scene())
		//{
			//_print_texts_scene(_UNKNOW_ , _UNKNOW_);
			//_all_dcs_taked_as_scene();//solo x seguridad redundando
		//}
		//else
			//{_print_texts_scene(currentscene.scene, currentscene.name);}
		//
		//byte zone;
		//for (zone=0;zone<NUM_ZONAS;zone++)
		//{
			//directclearall_barlevel(zone);
			//directfill_barlevel(zone, currentscene.objzone[zone].dc);
		//}
		//
		////...
		_directshow_the_scene();
		//
		if (currentscene.num_scene != _UNKNOW_)
			{previewscene.num_scene =  currentscene.num_scene;}
		//

		thisps.operating_mode = (OPERATINGMODE_THISPS)DOING_SCENE;//mode0
		change_operating_mode(thisps_fxs, thisps.operating_mode);

		//esta salida SI esperara a que KEY4 sea soltada, y todo el buffer del teclado
		//este liberado
		_waitforclean_keys();//Add. por seguridad, pues si presiona 1 vez mas, como ya se encuentra
							//en doing_scene, automaticamente saldra,,, por ahora lo restringo
							//a esperar a q suelte para admitir prox. combinacion
		
		playsound(SOUND_BUZZER, _BUZZER_ACCEPT_SOUND0_);
	}	

	//previamente si isnt_a_storage_scene()==1 -> ya fue tomado por _all_dcs_taked_as_scene();
	//pues solo hay 2 maneras de detectar el cambio, al entrar a la funcion
	//o despues de hacer una sincronizacion
	static void _directshow_the_scene(void)
	{
		//Se da por hecho que ya ha sido analizado si no pertenece a una escena guardada
		_print_texts_scene(currentscene.num_scene, currentscene.name);

		byte zone;
		for (zone=0;zone<NUM_ZONAS;zone++)
		{
			directclearall_barlevel(zone);
			directfill_barlevel(zone, currentscene.objzone[zone].dc);
		}
	}
	
	static void _menu_synch_allzones(void)
	{
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
	}	
	static void _synch_all(void)
	{
		thisps.operating_mode = (OPERATINGMODE_THISPS)SYNCH_ALLZONES;//synch
		change_operating_mode(thisps_fxs, thisps.operating_mode);
		
		blink_captionof_barzone_RUNALL();
		softcentric_clearallpixel_less1border_CHIP1();
		messagesynch();
		
		ps_fading_inbk.bf.printdisplay = ENABLE;	//habilita escritura en display
		schedule(-1);
	}
			
	//-------------------------------------
	//timmer space
	static void timmer_nb__ps(void)
	{
		timmer_nb__processing(&this_timmer_nb,THIS_TIMMER_NUMOFTIMMERS);
	}
	