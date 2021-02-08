/*
 * MenuSelectDimmNoDimmLoad_1.c
 *
 * Created: 7/24/2012 5:29:35 PM
 *  Author: jcaf

	By default the config is NO DIMMABLE
 */ 
#include "Includes/InitializeAllModules.h"

	_ClassRadioGroup_SDNDL ObjRadioGroup_SDNDL[NUM_ZONAS];	//Select Dimm No-Dimm Load
	
	static void AtExit_UpdateVars(void);
	
	typedef enum _OPERATINGMODE_THISPS
	{
		DO_RADIO=0,//MODE0=0,//doing scene
		DO_DIAGBOX,//MODE1,	//doing dialogbox
	}OPERATINGMODE_THISPS;


	static struct _thisps
	{
		signed char zone;
		OPERATINGMODE_THISPS operating_mode;
		signed char scheduler0;
		signed char scheduler1;
		
		_STACK_MODE app_kb_layout;
	
	}thisps;
	
	////////////////////////////////////////////////////////////////////////////////////////
	#define schedule(val) do{thisps.scheduler0 = val; thisps.scheduler1=0x00;}while(0)

	//----------------------------------------------------------
	//--timmer declarations
	#define THIS_TIMMER_NUMOFTIMMERS (1)
	static volatile struct _this_timmer_nb
	{
		_timmer_nb timmer_nb[THIS_TIMMER_NUMOFTIMMERS];

	}this_timmer_nb ={
		.timmer_nb[0].time = 1200/20,//entre 20ms
	};
	static void timmer_nb__ps(void);

	volatile void *p0_this_timmer_nb= &this_timmer_nb;//wrapper
	//----------------------------------------------------------
	
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

	static void _return2shell(void);
	
	static PTRFXrVOID thisps_fxs[4][MAXNUM_MODE_BY_PS][KB_TOTALOFKEYS]={
		{
		{&key1_1fmode0, &key2_1fmode0, &key3_1fmode0, &key4_1fmode0},
		{&key1_1fmode1, &key2_1fmode1, &key3_1fmode1, &key4_1fmode1},//doing dialog-box
		{&DUMMYFX, &DUMMYFX, &DUMMYFX, &DUMMYFX},
		{&DUMMYFX, &DUMMYFX, &DUMMYFX, &DUMMYFX},
		},
		{
		{&DUMMYFX, &DUMMYFX, &key3_1fmode0_aft, &DUMMYFX},
		{&DUMMYFX, &DUMMYFX, &key3_1fmode1_aft, &DUMMYFX},//doing dialog-box//
		{&DUMMYFX, &DUMMYFX, &DUMMYFX, &DUMMYFX},
		{&DUMMYFX, &DUMMYFX, &DUMMYFX, &DUMMYFX},
		},
		{
		{&DUMMYFX, &DUMMYFX, &key3_2fmode0, &DUMMYFX},
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
	
	//only if necesary
	/*
	static struct _key_properties key_properties__ps_forall[KB_TOTALOFKEYS]=
	{
		[0].u.bf.OnKeyPressed = 1,
		[0].group_autoexcluding = 1,
		
		[1].u.bf.OnKeyPressed = 1,
		[1].group_autoexcluding = 1,
		
		[2].u.bf.OnKeyPressed = 1,
		[2].group_autoexcluding = 1,
		
		[3].u.bf.AtTimeExpired = 1,
		[3].group_autoexcluding = _NO_AGRUPADO_AUTOEXCLUDING_,
		
		
		//[0].u.bf.OnKeyPressed = 1,
		//[0].u.bf.OnKeyPressedAndKeyRelease = 0,
		//[0].u.bf.AtTimeExpired = 0,
		//[0].u.bf.Reptt = 0,
		//[0].group_autoexcluding = 1,
		//
		//[1].u.bf.OnKeyPressed = 1,
		//[1].u.bf.OnKeyPressedAndKeyRelease = 0,
		//[1].u.bf.AtTimeExpired = 0,
		//[1].u.bf.Reptt = 0,
		//[1].group_autoexcluding = 1,
				//
		//[2].u.bf.OnKeyPressed = 1,
		//[2].u.bf.OnKeyPressedAndKeyRelease = 0,
		//[2].u.bf.AtTimeExpired = 0,
		//[2].u.bf.Reptt = 0,
		//[2].group_autoexcluding = 1,
				//
		//[3].u.bf.OnKeyPressed = 0,
		//[3].u.bf.OnKeyPressedAndKeyRelease = 0,
		//[3].u.bf.AtTimeExpired = 1,
		//[3].u.bf.Reptt = 0,
		//[3].group_autoexcluding = _NO_AGRUPADO_AUTOEXCLUDING_,
		//
	};
	*/
	
	//////////////////////////////////////////////////////////////////////////////////////////////
	//run-time init, then can change theirs positions
	//////////////////////////////////////////////////////////////////////////////////////////////
	void RG_SDNDL_Init_AllRadios(void)	
	{
		byte group, idxOfgroup;
		byte x,y;

		for (group=0; group<NUM_ZONAS; group++)
		{
			for (idxOfgroup=0; idxOfgroup<(KTES_RADIOBUTTON_SDNDL)_NUM_RADIO_THIS_GROUP_SDNDL_; idxOfgroup++)
			{
				x = ( (_BAR_PSC_BASE_X_+(_INTERV_ENTRE_BARR_VERT_*group) )+5 );
				y = ( (KTES_RADIOBUTTON_SDNDL)_XY_YINIT_+ ( (KTES_RADIOBUTTON_SDNDL)_XY_RADIO_DIVISION_VERT_ *idxOfgroup) );

				InitRadio_xy(&ObjRadioGroup_SDNDL[group], idxOfgroup, x, y);
			}
			//
			ObjRadioGroup_SDNDL[group].idxOfgroup = -1;	//unchecked all
			ObjRadioGroup_SDNDL[group].idxOfgroup_old = ObjRadioGroup_SDNDL[group].idxOfgroup;
			ObjRadioGroup_SDNDL[group].NumRadiosThisGroup = (KTES_RADIOBUTTON_SDNDL)_NUM_RADIO_THIS_GROUP_SDNDL_;
		}
	}
	//////////////////////////////////////////////////////////////////////////////////////////////
	void RG_SDNDL_DrawOuter_AllRadios(void)
	{	
		byte group;
			for (group=0; group<NUM_ZONAS; group++)
				{DrawOuterRadioButtonThisGroup(&ObjRadioGroup_SDNDL[group]);}
	}		
	/************************************************************************************************
	EXISTE UNA CORRESPONDENCIA UNIVOCA ENTRE TypeOfLoad<-->y la posicion vertical de los radioButtons
	
	typedef enum _ZONE_TypeOfLoad_
	{
		NoDimmable, -->0
		Dimmable	-->1
		etc			-->3...
	}_ZONE_TypeOfLoad;
	
	*************************************************************************************************/
	void RG_SDNDL_Menu_Texts(void)
	{
		ks0108SelectFont(SC,ks0108ReadFontData,BLACK);
		ks0108GotoXY(8,17);ks0108Puts_P(PSTR("No-Dimm"));//ks0108GotoXY(10,yposicion)->yposicion = ObjRadioGroup_SDNDL[0].Radio_xy[0].y - (SC_HEIGHT/2)+1 
		ks0108GotoXY(8,35);ks0108Puts_P(PSTR("Dimmable"));
		ks0108GotoXY(10,3); ks0108Puts_P(PSTR("SELECT"));
		ks0108InvertRect(2,2,60,12);
	}
	
	void RG_SDNDL_Menu(void)
	{
		if (thisps.scheduler0 == 0)//initialize once
		{
			if (thisps.scheduler1 == 0)
			{
				thisps.scheduler1++;
				
				ks0108ClearScreen();

				DrawOnlyMarcoGlobalGLCD();
				CaptionOfAllZones();
				ks0108DrawHoriLine(64,14,190-64,BLACK);ks0108DrawVertLine(64,1,12,BLACK);//draw |__
				RG_SDNDL_Menu_Texts();
				RG_SDNDL_DrawOuter_AllRadios();
				byte zone;
				for (zone=0; zone<NUM_ZONAS; zone++)
				{
					ObjRadioGroup_SDNDL[zone].idxOfgroup = objzone[zone].TypeOfLoad;	//o usar _translate_AtEnter(v,zone)
					SetCheckedRadio(&ObjRadioGroup_SDNDL[zone]);
				}
				
				//bfCommonProcess0.Timmer_BlinkCaption = ON;
				//thisps.zone = 0x00;//se conservara la ultima entrada a la zona respectiva
				blink_captionof_barzone_RUN(thisps.zone);
				
				ks0108DrawRoundRect(ObjRadioGroup_SDNDL[thisps.zone].Radio_xy[0].x-7, ObjRadioGroup_SDNDL[thisps.zone].Radio_xy[0].y-7, 14,31,3,BLACK);
				
				//registrar las funciones al entrar
				thisps.operating_mode = (OPERATINGMODE_THISPS)DO_RADIO;//MODO0
				change_operating_mode(thisps_fxs, thisps.operating_mode);
			}

			//debe existir una seccion de destruccion de proceso
			//timmer space
			timmer_nb__reset_counter((_timmer_nb *)&this_timmer_nb.timmer_nb[0]);	//counter = 0x00;
			timmer_nb__reset_sm_app((_timmer_nb *)&this_timmer_nb.timmer_nb[0]);	//sm_app=0x0
			//--

			//layout keyboard
			//thisps.app_kb_layout = synch_change_layout_kb( (_STACK_MODE)DIRECT, &key_properties__ps_forall[0]);
//thisps.app_kb_layout = synch_change_layout_kb( (_STACK_MODE)PUSH, &key_properties__ps_forall[0]);
			
			schedule(-1);	//espera un nuevo evento			
		}	
		//////////////////////////////////////////////////////////////////////////////////
		if (thisps.scheduler0 == 1)	//schedule(1)
		{
			if (thisps.scheduler1 == 0)
			{
				thisps.scheduler1++;

				softcentric_clearallpixel_less1border_CHIP1();
				
				ks0108GotoXY(2+8,2+17);		ks0108Puts_P(PSTR("Aceptar"));
				ks0108GotoXY(2+8,2+17+12);	ks0108Puts_P(PSTR("cambios?"));
				dialogbox_sino(2,2,(DIALOGBOX_OPTIONS)_DIALOGBOX_OPTION_NO_);//leave dialogbox_nb.cr=-1
			}
			if (thisps.scheduler1 == 1)
			{
					if (dialogbox_nb.cr > (DIALOGBOX_CR)NONE )
					{
						if (dialogbox_nb.cr ==  (DIALOGBOX_CR)YES)
						{
							if (this_timmer_nb.timmer_nb[0].sm_app == 0)	
							{
																			//_waitforclean_keys();
								AtExit_UpdateVars();
						
								ks0108FillRect(6,19,53,41,WHITE);//clear text
								ks0108GotoXY(12,2+17);		ks0108Puts_P(PSTR("Cambio"));
								ks0108GotoXY(7,2+17+10);	ks0108Puts_P(PSTR("ejecutado"));
								ks0108InvertRect(6,19,50,23);
								//_delay_ms(1500);//execute space x delay
								
								//
								this_timmer_nb.timmer_nb[0].sm_app++;
								this_timmer_nb.timmer_nb[0].run = 1;
								//
								_KB_inhibited();
							}
							else if (this_timmer_nb.timmer_nb[0].sm_app == 2)	//+2
							{
								timmer_nb__reset_sm_app((_timmer_nb *)&this_timmer_nb.timmer_nb[0]);	//sm_app=0x0
								
								playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
								
								_return2shell();	//todas las salidas dejan schedule(), para una entrada en MODO 0
								//
								__dialogbox_cr_wasread();
								//
								//_KB_waitfor_kb_free_and_complete_ps();//ahora toda salida es con limpieza
							}
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
				dialogbox_sino(2,2,(DIALOGBOX_OPTIONS)_DIALOGBOX_OPTION_SI_);//reset dialogbox_nb.cr=-1
			}
			if (thisps.scheduler1 == 1)//wait for answer
			{
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
						softcentric_clearallpixel_less1border_CHIP1();
						//Restore
						RG_SDNDL_Menu_Texts();
						blink_captionof_barzone_RUN(thisps.zone);
						
						thisps.operating_mode = (OPERATINGMODE_THISPS)DO_RADIO;//MODO0
						change_operating_mode(thisps_fxs, thisps.operating_mode);
						//
						__dialogbox_cr_wasread();
					}
					//thisps.scheduler1++;
				}
			}
		}

	timmer_nb__ps();
	
	}	
		
	/////////////////////////////////////////////////////////////////////////////////////////////////
	static void key1_1fmode0(void)
	{
		if (++thisps.zone >= NUM_ZONAS)
		{
			thisps.zone = 0;
			blink_captionof_barzone_STOP(NUM_ZONAS-1);
			ks0108DrawRoundRect(ObjRadioGroup_SDNDL[NUM_ZONAS-1].Radio_xy[0].x-7,ObjRadioGroup_SDNDL[NUM_ZONAS-1].Radio_xy[0].y-7, 14,31,3,WHITE);
		}
		else
		{
			blink_captionof_barzone_STOP(thisps.zone-1);
			ks0108DrawRoundRect(ObjRadioGroup_SDNDL[thisps.zone-1].Radio_xy[0].x-7, ObjRadioGroup_SDNDL[thisps.zone-1].Radio_xy[0].y-7, 14,31,3,WHITE);
		}
		blink_captionof_barzone_RUN(thisps.zone);
		ks0108DrawRoundRect(ObjRadioGroup_SDNDL[thisps.zone].Radio_xy[0].x-7, ObjRadioGroup_SDNDL[thisps.zone].Radio_xy[0].y-7, 14,31,3,BLACK);
		//
		playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
	}
			
	static void key2_1fmode0(void)
	{
		if (--thisps.zone < 0)
		{
			thisps.zone = (NUM_ZONAS-1);
			blink_captionof_barzone_STOP(0);
			ks0108DrawRoundRect(ObjRadioGroup_SDNDL[0].Radio_xy[0].x-7, ObjRadioGroup_SDNDL[0].Radio_xy[0].y-7, 14,31,3,WHITE);
		}
		else
		{
			blink_captionof_barzone_STOP(thisps.zone+1);
			ks0108DrawRoundRect(ObjRadioGroup_SDNDL[thisps.zone+1].Radio_xy[0].x-7, ObjRadioGroup_SDNDL[thisps.zone+1].Radio_xy[0].y-7, 14,31,3,WHITE);
		}
		blink_captionof_barzone_RUN(thisps.zone);
		ks0108DrawRoundRect(ObjRadioGroup_SDNDL[thisps.zone].Radio_xy[0].x-7, ObjRadioGroup_SDNDL[thisps.zone].Radio_xy[0].y-7, 14,31,3,BLACK);
		//				
		playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
	}

	static void key3_1fmode0(void)//Or before
	{
		if (++ObjRadioGroup_SDNDL[thisps.zone].idxOfgroup >= (KTES_RADIOBUTTON_SDNDL)_NUM_RADIO_THIS_GROUP_SDNDL_ )
			{ObjRadioGroup_SDNDL[thisps.zone].idxOfgroup=0;}
				
		SetCheckedRadio(&ObjRadioGroup_SDNDL[thisps.zone]);

		playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
	}

	static void key3_1fmode0_aft(void)
	{	key3_1fmode0();	}

	static void key4_1fmode0(void)
	{
		schedule(1);
		
		thisps.operating_mode = (OPERATINGMODE_THISPS)DO_DIAGBOX;//MODO1
		change_operating_mode(thisps_fxs, thisps.operating_mode);	
		
		playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
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
		{ key3_1fmode1();}
	//
	static void key4_1fmode1(void)
	{
		dialogbox_nb.dialogbox_sino_ESC();
		playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
	}
	
	////////////////////////////////////////////////////////////
	static void key3_2fmode0(void)
	{
		playsound(SOUND_BUZZER, _BUZZER_ACCEPT_SOUND0_);
		_return2shell();
		//_KB_waitfor_kb_free_and_complete_ps();
		
		//Ahora todas las salidas se unifican, y se aplican algunos criterios restrictivos,
		//tal vez no se requieran segun la naturaleza del evento, pero hace que el codigo sea mas depurable
	}
	////////////////////////////////////////////////////////////
	static void _return2shell(void)
	{
		blink_captionof_barzone_STOP(thisps.zone);
		//bfCommonProcess0.Timmer_BlinkCaption = OFF;
	
		shell.coderet = (CODERETURN_TOSHELL)RESTORE_SHELL;
		schedule(0);//todas las salidas dejan para una entrada en MODO 0

		//La salida depende de la manera que se haya configurado en teclado(DIRECT, PUSH, POP)
		//OJO: synch_change_layout_kb cambia eL scheduler del keyboard
		
		if (thisps.app_kb_layout == (_STACK_MODE)UNTOUCH)//POR AHORA ES 0x00
		{
			_KB_waitfor_kb_free_and_complete_ps();
		}
		else if (thisps.app_kb_layout == (_STACK_MODE)DIRECT)
		{
			//-> apunta a una region de memoria para el cambio respectivo
		}
		else if (thisps.app_kb_layout == (_STACK_MODE)PUSH)
		{
			synch_change_layout_kb( (_STACK_MODE)POP, (struct _key_properties *)&synch_kb_exposed_to_app.key_change_layout.__dummy);	
			//
			//OJO: synch_change_layout_kb hace un proceso interno de "_KB_waitfor_kb_free_and_complete_ps"
		}

	}

	/***********************************************************************************
	Por ahora el tipo de efecto sera implicito de acuerdo al tipo de carga.
	***********************************************************************************/
	static void AtExit_UpdateVars(void)
	{
		byte zone;
		byte num_scene;
		
		for (zone=0; zone<NUM_ZONAS; zone++)
		{	//Update only if necessary!
			if (objzone[zone].TypeOfLoad != ObjRadioGroup_SDNDL[zone].idxOfgroup)	//algo ha cambiado?
			{
				objzone[zone].TypeOfLoad = ObjRadioGroup_SDNDL[zone].idxOfgroup;		//udpate TypeOfLoad
				
				if (objzone[zone].TypeOfLoad == NoDimmable)
				{
					if (objzone[zone].sfading.bf.fading_active)			//Stop fading, and direct->update
					{
						objzone[zone].sfading.bf.fading_active = OFF;
					}
					
					if (if_fadingactive_nextdc_else_dc(zone) > objzone[zone].thrshld)		//objzone[zone].dc > 0
					{
						objzone[zone].dc = MAX_VAL_DUTYCYCLE;
					}
					else //reafirma
					{
						objzone[zone].dc = 0x0;	
					}
					updatedc(zone,objzone[zone].dc);	
					
					currentscene.objzone[zone].dc = objzone[zone].dc;	//update dc of currentscene	
					
					//update all scenes()
					if (ps_scene.totalofscenes > 0)
					{
						for (num_scene=0; num_scene< ps_scene.totalofscenes; num_scene++)
						{
							if (get_dcofzone_ofscene_EEP(num_scene,zone) > objzone[zone].thrshld)	
							{
								set_dcofzone_ofscene_EPP(num_scene,zone, MAX_VAL_DUTYCYCLE);
							}
							else
							{
								set_dcofzone_ofscene_EPP(num_scene,zone, 0x0);
							}
						}
					}

					//LIMPIAR EL FLAG DE RESTAURACION!!!! PUES SI SE PRESIONA KEY3 UN TOQUE, LO LLEVA A ESE ESTADO
					objzone[zone].onoffrstr.dcr = 0x0;
					objzone[zone].onoffrstr.bf.pto_rstr = OFF;
					objzone[zone].commingfrom = (COMMINGFROM)LASTEVENT_CLEAR;
					
					//
					objzone[zone].TypeOfEffect = Direct;	//implicito por ahora
					
					
					//udpate current scene 
					//currentscene.num_scene = ps_scene.totalofscenes-1;
					//_all_dcs_taked_as_scene();
				}
				else if (objzone[zone].TypeOfLoad == Dimmable)
				{
					objzone[zone].TypeOfEffect = (_ZONE_TypeOfEffect)Fading;//implicito por ahora
				}
				//
				EEPROM_WriteByte((byte *)&objzone_epp[zone].TypeOfLoad, objzone[zone].TypeOfLoad);		
				EEPROM_WriteByte((byte *)&objzone_epp[zone].TypeOfEffect, objzone[zone].TypeOfEffect);//implicito por ahora
				//
			}
		}
	}	

	//-------------------------------------
	//timmer space
	static void timmer_nb__ps(void)
	{
		timmer_nb__processing((void *)&this_timmer_nb,THIS_TIMMER_NUMOFTIMMERS);
	}
	
	
	//if (ObjRadioGroup_SDNDL[zone].idxOfgroup)
	//---------------------------------------------------------------
	//solo si son manejados en un orden diferente
	//void _translate_AtEnter(v,zone)
	//{	switch (v)
	//{	case 0: ObjRadioGroup_SDNDL[zone].idxOfgroup = ; break;
	//case 1: ObjRadioGroup_SDNDL[zone].idxOfgroup = ; break;
	////case ...:  = ; break;
//}
	//}
	
	//solo si son manejados en un orden diferente
	//void _translate_AtExit(v,zone)
	//{	switch (v)
		//{	case 0: ObjZONEram[zone].TypeOfLoad  = ; break;
			//case 1: ObjZONEram[zone].TypeOfLoad  = ; break;
			////case 0:...  = ; break;
		//}
	//}
	