/*
 * MenuDimming6Zonas_1.c
 *
 * Created: 24/02/2012 04:44:37 p.m.
 *  Author: jcaf
 */ 
#include "Includes/InitializeAllModules.h"

	typedef enum _KEYMIXSTATES
	{
		SCHEDULER=0,
		KEYS1FX,
		KEYS2FX,
		KEYSEXIT,
	}KEYMIXSTATES;

	static struct _keyhardmixps
	{
		KEYMIXSTATES sm0;
		byte ikey;			//key pressed?
		//byte mode;		
	}keyhardmixps;

	typedef enum _OPERATINGMODE_THISPS
	{
		MODE0=0,
	}OPERATINGMODE_THISPS;

	static struct _thisps
	{
		signed char zone;
		CODERETURN_TOSHELL codereturn;
		OPERATINGMODE_THISPS operating_mode;
	}thisps;
	
	//Existe una distincion entre el this.operating_mode  y el de keymixapplvl.mode
	//mientras que el primero puede varia de acuredo al punto de vista del programa(proceso actual),
	//keymixapplvl.mode podria cambiar a la par o tal vez, a otros modos de diferente connotacion.
	//Por el momento ambos van a la par.
	typedef OPERATINGMODE_THISPS MODE_KEYINAPPLVL;
	
	static struct _keyinapplvl				//independent-key in application-level
	{
		MODE_KEYINAPPLVL mode;
		byte sm0;
		byte sm1;
		//byte counter0;
	}keyinapplvl[KB_TOTALOFKEYS];
	
	//////////////////////////////////////////////////////////////////////////
	static void key1_mode0(void);
	//static void key1_mode1(void);
	static void key2_mode0(void);
	//static void key2_mode1(void);
	static void key3_mode0_bef(void);
	//static void key3_mode1_bef(void);
	static void key3_mode0_aft(void);
	//static void key3_mode1_aft(void);
	
	//----------
	void RestoreOnOff_mode1(byte zone);
	void directOnOff_mode1(byte zone);
	void RestoreOnOff_mode2(byte zone);
	void directOnOff_mode2(byte zone);
	//----------

	#define TORIGHT (+1)
	#define TOLEFT 	(-1)
	static void selectzone_menus(signed char dir);
	static void menus(void);
	static void waitfor(void);
	
	static void schedulerkey(void);
	static void keys1f(void);
	static void keys2f(void);
	static void keysexit(void);

	static void PeriodicCall_Thread_FadingProcess_AllZone(void);
	
	//////////////////////////////////////////////////////////////////////////////////
	static void SettKb_Dimming6Zones(void) 
	{
		ObjKey[KB_iKEY1].bfCTRLKey.OnKeyPressed  =1;
		ObjKey[KB_iKEY1].bfCTRLKey.AtTimeExpired =0;//add
		ObjKey[KB_iKEY1].bfCTRLKey.Reptt = 1;
		ObjKey[KB_iKEY1].bfCTRLKey.Group_AutoExcluding = 1;
		//.................................		
		ObjKey[KB_iKEY2].bfCTRLKey.OnKeyPressed  =1;
		ObjKey[KB_iKEY2].bfCTRLKey.AtTimeExpired =0;//add
		ObjKey[KB_iKEY2].bfCTRLKey.Reptt = 1;
		ObjKey[KB_iKEY2].bfCTRLKey.Group_AutoExcluding = 1;
		//.................................
		ObjKey[KB_iKEY3].bfCTRLKey.OnKeyPressed  =0;
		ObjKey[KB_iKEY3].bfCTRLKey.AtTimeExpired =1;
		
		ObjKey[KB_iKEY3].bfCTRLKey.Reptt = 0;
		ObjKey[KB_iKEY3].bfCTRLKey.Group_AutoExcluding = 1;
		//.................................		
		ObjKey[KB_iKEY4].bfCTRLKey.OnKeyPressed  =0;
		ObjKey[KB_iKEY4].bfCTRLKey.AtTimeExpired =1;
		
		ObjKey[KB_iKEY4].bfCTRLKey.Reptt = 0;
		ObjKey[KB_iKEY4].bfCTRLKey.Group_AutoExcluding = 0;
	}
	//////////////////////////////////////////////////////////////////////////////////
	static void selectzone(byte zone)	//NO SYNCH
	{
		ClearAllPixel_Less1Border_CHIP1();

		//namez(zone);
		ks0108SelectFont(SC, ks0108ReadFontData, BLACK);
		//ClearOnlyRegionForFindAndPrintNameOfZone();
		FindAndPrintNameOfZone(zone, xiCHIP1);			//name();				//mostrar nombre de Zona
		ks0108FillRect(1,63-17,61,0,BLACK);						//recta horizontal separadora
		
		//dcporcentz(thisps.zone);		
		PrintPorcentOfDCLevel(__If_FadingActive_ReturnNEXTDC_else_ReturnDC(zone));	//maybe in progressive your duty-cycle	
		
		//blinkrunz(thisps.zone);		
		ObjBlink_CaptionOfBarZone_BLINK_RUN_(zone);		//Blink current
	}

	////////////////////////////////////////////////////////////////////////////////////////
	//Se ingresa con todo fading finalizado.			
	////////////////////////////////////////////////////////////////////////////////////////
	signed char zone_handler(void)
	{
		thisps.codereturn = (CODERETURN_TOSHELL)NOEXIT;

		selectzone(thisps.zone);		
		
		keyhardmixps.sm0 = 0;		

		keyinapplvl[KB_iKEY4].sm0 = 0;		
		keyinapplvl[KB_iKEY4].sm1 = 0;
		
		bfCommonProcess0.Timmer_BlinkCaption = ON;	
		
		SettKb_Dimming6Zones();
		
		while (1)
		{
			//if ()
			//{		
				//_________________________________	
				if (keyhardmixps.sm0 == SCHEDULER)	
					{schedulerkey();}
				if (keyhardmixps.sm0 == KEYS1FX)	
					{keys1f();}			
				if (keyhardmixps.sm0 == KEYS2FX)		
					{keys2f();}							
				if (keyhardmixps.sm0 == KEYSEXIT)
					{keysexit();}
				//_________________________________
			//}	
			//if ()
			//{
				//dialogbox_sino_keyboardhandler();
			//}	
				//_________________________________

			if (thisps.codereturn > (CODERETURN_TOSHELL)NOEXIT)
			{	
				//Convergiendo salidas. AUN TODAVIA NO
				//if (keyinapplvl[KB_iKEY4].sm0 == 0) {ObjBlink_CaptionOfBarZone_BLINK_STOP_(thisps.zone);}
				//bfCommonProcess0.Timmer_BlinkCaption = OFF;
				break;	
			}

			//__
			if (bfCommonProcess0.Timmer_BlinkCaption)
			{
				if (bfCommonProcess0.SignOneTick_BlinkCaption)
				{
					bfCommonProcess0.SignOneTick_BlinkCaption = OFF;
					ObjBlink_Timming_CaptionOfBarZone();
				}
			}			
			//__
			PeriodicCall_Thread_FadingProcess_AllZone();
			//__
		}
		
		return thisps.codereturn;
	}	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	static void schedulerkey(void)
	{
		if ( ObjKey[KB_iKEY4].bfSTATE.StableState == KB_KEY_RELEASED )
		{
			if (ObjKey[KB_iKEY1].bfSTATE.InProcessing) {keyhardmixps.ikey=KB_iKEY1;keyhardmixps.sm0 = KEYS1FX;return;}
			if (ObjKey[KB_iKEY2].bfSTATE.InProcessing) {keyhardmixps.ikey=KB_iKEY2;keyhardmixps.sm0 = KEYS1FX;return;}
			if (ObjKey[KB_iKEY3].bfSTATE.InProcessing) {keyhardmixps.ikey=KB_iKEY3;keyhardmixps.sm0 = KEYS1FX;return;}
		}
		if (KB_KEY4_ReadyToRead())	
		{
			if (ObjKey[KB_iKEY4].bfSTATE.AtTimeExpired_BeforeOrAfter == KB_BEFORE_THR)	{}
			else {	if (!ObjKey[KB_iKEY4].bfCTRLKey.Reptt){}	else {}	}				
															
			KB_KEY4_HasBeenRead();
			playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
			
			if 	(keyinapplvl[KB_iKEY4].mode == MODE0)
			{
				selectzone_menus(TORIGHT);
			}
		}
		if (ObjKey[KB_iKEY4].bfSTATE.StableState == KB_KEY_PRESSED) 
		{
			if ((ObjKey[KB_iKEY1].bfSTATE.InProcessing)||(ObjKey[KB_iKEY2].bfSTATE.InProcessing)||(ObjKey[KB_iKEY3].bfSTATE.InProcessing))
			{
				keyhardmixps.sm0 = KEYS2FX;
				
				//if (ObjKey[KB_iKEY4].bfCTRLKey.Reptt)		//stop Reptt si estuviera activo -> guardar/restaurar	
				//	{ObjKey[KB_iKEY4].bfSTATE.temp = ObjKey[KB_iKEY4].bfCTRLKey.Reptt;}
			}
		}
	}				
	//////////////////////////////////////////////////////
	//NO-2DA_Fn		
	//definitivamente entrarA hasta q se estabilice las "variables"
	//////////////////////////////////////////////////////
	static void keys1f(void)
	{
		if (KB_KEY1_ReadyToRead())
		{
			//if (keyinapplvl[keyhardmixps.ikey].mode ==(MODE_KEYINAPPLVL)MODE0)	
				{key1_mode0();} 
			//else if (keyinapplvl[keyhardmixps.ikey].mode == (MODE_KEYINAPPLVL))		{key1_mode1();} 
		
			KB_KEY1_HasBeenRead();
			ResetCounterTimmerForNewKeepingTimmingBLGLCD();	
		}
		else if (KB_KEY2_ReadyToRead())
		{	
			//if (keyinapplvl[keyhardmixps.ikey].mode == (MODE_KEYINAPPLVL)MODE0)	
				{key2_mode0();} 
			//else if (keyinapplvl[keyhardmixps.ikey].mode == (MODE_KEYINAPPLVL) )		{key2_mode1();} 
		
			KB_KEY2_HasBeenRead();
			ResetCounterTimmerForNewKeepingTimmingBLGLCD();	
		}
		else if (KB_KEY3_ReadyToRead())
		{
			if (ObjKey[KB_iKEY3].bfSTATE.AtTimeExpired_BeforeOrAfter == KB_BEFORE_THR)
			{	
				//if (keyinapplvl[keyhardmixps.ikey].mode == (MODE_KEYINAPPLVL)MODE0)	
					{key3_mode0_bef();} 
				//else if (keyinapplvl[keyhardmixps.ikey].mode == (MODE_KEYINAPPLVL))		{key3_mode1_bef();} 
			}	
			else 
			{	
				if (!ObjKey[KB_iKEY3].bfCTRLKey.Reptt) {}	else {}
				
				//if (keyinapplvl[keyhardmixps.ikey].mode == (MODE_KEYINAPPLVL)MODE0)	
					{key3_mode0_aft();} 
				//else if (keyinapplvl[keyhardmixps.ikey].mode == MODE1_SYNCHALL)		{key3_mode1_aft();} 
			}
			playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
			KB_KEY3_HasBeenRead();
			ResetCounterTimmerForNewKeepingTimmingBLGLCD();	//BackLightGLCD reset-timming
		}
		//espera hasta que se procese ObjKey[keymixps.ikey].bfSTATE.InProcessing = 0
		if (!ObjKey[keyhardmixps.ikey].bfSTATE.InProcessing)	
			{keyhardmixps.sm0 = KEYSEXIT;}	
	}	
	//////////////////////////////////////////////////////
	//2DA_Fn activa
	//////////////////////////////////////////////////////
	static void keys2f(void)
	{	
		if (ObjKey[KB_iKEY4].bfSTATE.StableState == KB_KEY_PRESSED)	
		{
			ResetCounterTimmerForNewKeepingTimmingBLGLCD();			//while pressing kb4 resetting
		
			if (KB_KEY1_ReadyToRead())
			{
				//if (keyinapplvl[KB_iKEY1].mode == MODE0)
				//{
						KB_KEY1_HasBeenRead();
						playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
					selectzone_menus(TOLEFT);
				//}
			}
			
			if (KB_KEY2_ReadyToRead())
			{
				thisps.codereturn = (CODERETURN_TOSHELL)CR_SCENE_HANDLER;//switch to scene
				//
				KB_KEY2_HasBeenRead();	
				playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);	
			}

			//if ( KB_KEY3_ReadyToRead() )
			if (ObjKey[KB_iKEY3].bfSTATE.InProcessing)
			{
				if (ObjKey[KB_iKEY3].bfSTATE.AtTimeExpired_BeforeOrAfter == KB_BEFORE_THR)	
				{}
				else
				{	if (!ObjKey[KB_iKEY3].bfCTRLKey.Reptt)	{} else {}	}
				
				//
				ObjBlink_CaptionOfBarZone_BLINK_STOP_(thisps.zone);	//Stop zone actual
				bfCommonProcess0.Timmer_BlinkCaption = OFF;		
				//
				
				thisps.codereturn = (CODERETURN_TOSHELL) CR_ZONE_HANDLER;	//back to shell
				
				KB_KEY3_HasBeenRead();
				playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
				
			}		
		}
		else
			{keyhardmixps.sm0 = KEYSEXIT;} 
	}			
	//////////////////////////////////////////////////////
	//Primero, todos las teclas han sido soltadas-> segundo, limpia la condicion "ReadyToRead" para que sus
	//maquinas de estados se reseteen
	//////////////////////////////////////////////////////
	static void keysexit(void)
	{
		byte i;
		if ( ObjSharedFeatKeys.bfSHARED.AreAllKeysReleased )
		{
			for (i=0; i<KB_TOTALOFKEYS; i++)		//All-Clear states
			{
				ObjKey[i].bfSTATE.ReadyToRead = KB_CLEAR_READYTOREAD_INAPP;
				ObjKey[i].bfSTATE.AtTimeExpired_BeforeOrAfter = 0;
			}
			keyhardmixps.sm0 = SCHEDULER;
		}
		else
		{
			ResetCounterTimmerForNewKeepingTimmingBLGLCD();	
		}
	}	
	/////////////////////////////////////////////////////////////////////////////////////////////
	static void key1_mode0(void)
	{
		objzone[thisps.zone].uCommonProcess.bfCommonProcess._PRINT_PORCENT_OF_DC_LEVEL_ = ON;
		_PreEx_DimmingUp(thisps.zone);
	}
	
	//static void key1_mode1(void)	{}
	
	static void key2_mode0(void)
	{
		objzone[thisps.zone].uCommonProcess.bfCommonProcess._PRINT_PORCENT_OF_DC_LEVEL_ = ON;
		_PreEx_DimmingDown(thisps.zone);
	}
	
	//static void key2_mode1(void)	{}
	
	static void key3_mode0_bef(void)
	{
		objzone[thisps.zone].uCommonProcess.bfCommonProcess._PRINT_PORCENT_OF_DC_LEVEL_ = ON;

		if (objzone[thisps.zone].cfgmodeof_restoreonoff == (CFGMODEOF_RESTOREONOFF)RESTORE_AND_ON_OFF)
			{RestoreOnOff_mode1(thisps.zone);}
		else //ONLY_ON_OFF
			{RestoreOnOff_mode2(thisps.zone);}
	}
	
	//static void key3_mode1_bef(void)	{}
	
	static void key3_mode0_aft(void)
	{
		objzone[thisps.zone].uCommonProcess.bfCommonProcess._PRINT_PORCENT_OF_DC_LEVEL_ = ON;
		
		if (objzone[thisps.zone].cfgmodeof_restoreonoff == (CFGMODEOF_RESTOREONOFF)RESTORE_AND_ON_OFF)
			{directOnOff_mode1(thisps.zone);}
		else //ONLY_ON_OFF
			{directOnOff_mode2(thisps.zone);}
	}
	
	//static void key3_mode1_aft(void)	{}
	
	void key3_updateDC(byte zone)
	{
		__Parsing_UpdateBarZone_AccodingToTheFeatures(zone);

		if (objzone[zone].uCommonProcess.bfCommonProcess._PRINT_PORCENT_OF_DC_LEVEL_)	
		{__Parsing_PrintPorcentOfDCLevelZone_AccodingToTheFeatures(zone);}
		
		updatedc_acctypeofload(zone);			//Ejecuta
	}

	/////////////////////////////////////////////////////////////////////////
	static void selectzone_menus(signed char dir)
	{
		if (keyinapplvl[KB_iKEY4].sm0 == 0)
		{
			thisps.zone += dir;

			if (thisps.zone < 0)
			{
				ObjBlink_CaptionOfBarZone_BLINK_STOP_(0);
				thisps.zone = NUM_ZONAS-1;
				keyinapplvl[KB_iKEY4].sm0++;
			}
			else if (thisps.zone >= NUM_ZONAS)
			{
				ObjBlink_CaptionOfBarZone_BLINK_STOP_(NUM_ZONAS-1);
				thisps.zone = 0;
				keyinapplvl[KB_iKEY4].sm0++;
			}
			else
			{
				ObjBlink_CaptionOfBarZone_BLINK_STOP_(thisps.zone + (dir*-1) );
				selectzone(thisps.zone);
			}
		}

		if (keyinapplvl[KB_iKEY4].sm0 > 0 )
		{
			if (keyinapplvl[KB_iKEY4].sm0 == 1)
			{
				menus();
				
				if (thisps.codereturn == (CODERETURN_TOSHELL)NOEXIT)		
				{
					//restore
					selectzone(thisps.zone);	//Re-blink through this function
					SettKb_Dimming6Zones();
					keyinapplvl[KB_iKEY4].sm0 = 0;
				}		
			}
		}
	}
	/////////////////////////////////////////////////////////////////////////
	static void menus(void)
	{
		if (keyinapplvl[KB_iKEY4].sm1 == 0)
		{
			waitfor();
			keyinapplvl[KB_iKEY4].sm1++;
		}
		
		if (keyinapplvl[KB_iKEY4].sm1 > 0)
		{
			if (keyinapplvl[KB_iKEY4].sm1 == 1)
			{
				ClearAllPixel_Less1Border_CHIP1();
				if	( _dialogbox_sino_B__salir(2,2, (DIALOGBOX_OPTIONS)_DIALOGBOX_OPTION_SI_ ) )
				{
					bfCommonProcess0.Timmer_BlinkCaption = OFF;
					thisps.codereturn = (CODERETURN_TOSHELL)CR_ZONE_HANDLER;
				}
				ClearAllPixel_Less1Border_CHIP1();
				
				keyinapplvl[KB_iKEY4].sm1 = 0;
			}
		}
	}
	
	
	/////////////////////////////////////////////////////////////////////////
	static void waitfor(void)
	{
		ObjBlink_CaptionOfBarZone_Blink_Stop_All();
		
		if (DIMMING_FLAGS.TIMER0_IsActiveFading)
		{
			MessageBox_FadingInProgressing(128,32);

			while (DIMMING_FLAGS.TIMER0_IsActiveFading)
			{PeriodicCall_Thread_FadingProcess_AllZone();}
		}
		//_____
		while ( !ObjSharedFeatKeys.bfSHARED.AreAllKeysReleased )
			{ResetCounterTimmerForNewKeepingTimmingBLGLCD();}
		for (byte i=0; i<KB_TOTALOFKEYS; i++)		//All-Clear states
		{
			ObjKey[i].bfSTATE.ReadyToRead = KB_CLEAR_READYTOREAD_INAPP;
			ObjKey[i].bfSTATE.AtTimeExpired_BeforeOrAfter = 0;
		}
		//_____
	}
	/******************************************************************************
	//fx is local	
	******************************************************************************/
	static void PeriodicCall_Thread_FadingProcess_AllZone(void)	
	{
		if (DIMMING_FLAGS.TIMER0_IsActiveFading)
		{
			if (DIMMING_FLAGS.PeriodicCallTo_FadingProcess)	
			{	
				DIMMING_FLAGS.PeriodicCallTo_FadingProcess=0;
				
				ThisThreadCallTo_FadingProcess_AllZone();				//vStatus_FadingProcess_Zone[] is updated! 
				
				if ( FADING_IsFadingInAllZoneFinished() )			//esta decision lo deja local	 	
				{
					DIMMING_FLAGS.TIMER0_IsActiveFading = 0;
				}	
			}			
		}
	}
	
	////////////////////////////////////////////////////////////////
	TYPEDC gettingdc(byte zone)
	{
		if (objzone[zone].sfading.bf.fading_active)
			{return objzone[zone].sfading.nextdcfading;}
		else
			{return objzone[zone].dc;}
	}
	////////////////////////////////////////////////////////////////
	//setting_preupdate_dc
	void settingdc(byte zone, word val)
	{
		if (objzone[zone].TypeOfLoad == Dimmable)
		{
			if (objzone[zone].TypeOfEffect == Fading)
				{objzone[zone].sfading.nextdcfading = val;	}
		}
		else if	(objzone[zone].TypeOfLoad == NoDimmable)
		{
			if (objzone[zone].TypeOfEffect == Direct)
				{objzone[zone].dc = val;}
		}
	}
	
	////////////////////////////////////////////////////////////////
	void RestoreOnOff_mode1(byte zone)
	{
		if (gettingdc(zone) > objzone[zone].thrshld_sect)//if (objzone[zone].dc > objzone[zone].thrshld_sect)
		{
			if (gettingdc(zone) == MAX_VAL_DUTYCYCLE)//if (objzone[zone].dc == MAX_VAL_DUTYCYCLE)
			{
				if (objzone[zone].commingfrom == (COMMINGFROM)LASTEVENT_DIRECTONOFF)//viene desde fromdirectonoff
				{
					if (objzone[zone].oorstr.dcr < MAX_VAL_DUTYCYCLE)
					{
						settingdc(zone, objzone[zone].oorstr.dcr);//objzone[zone].dc = objzone[zone].oorstr.dcr;
						goto __exit_thisfx;
					}
				}
			}	
			//para el resto de situaciones
			objzone[zone].oorstr.dcr = objzone[zone].dc;
			objzone[zone].oorstr.bf.pto_rstr = ON;
			settingdc(zone,0);//objzone[zone].dc = 0;
		}
		else
		{
			if (objzone[zone].oorstr.bf.pto_rstr == OFF) //if (objzone[zone].laidsw == SECTION_LESSEQUALTHAN_THRSHLD )
			{
										//direct, perdio su dcr al bajar a este punto
				if ( objzone[zone].cfgtorestore_atlevel== (CFGTORESTORE_ATLEVEL)MAXVAL)	//x default
				{
					settingdc(zone, MAX_VAL_DUTYCYCLE);				//objzone[zone].dc = MAX_VAL_DUTYCYCLE;
				}				
				else if ( objzone[zone].cfgtorestore_atlevel == (CFGTORESTORE_ATLEVEL)THRESHOLD_MAS_1)
				{
					settingdc(zone, objzone[zone].thrshld_sect+1);	//objzone[zone].dc = objzone[zone].thrshld_sect+1;
				}	
			}
			else //else if (objzone[zone].laidsw == SECTION_GREATERTHAN_THRSHLD )
			{
				settingdc(zone, objzone[zone].oorstr.dcr);//objzone[zone].dc = objzone[zone].oorstr.dcr;
				objzone[zone].oorstr.bf.pto_rstr = OFF;
			}
		}
		__exit_thisfx:
		
		//		
		__Parsing_UpdateBarZone_AccodingToTheFeatures(zone);
		if (objzone[zone].uCommonProcess.bfCommonProcess._PRINT_PORCENT_OF_DC_LEVEL_)
			{__Parsing_PrintPorcentOfDCLevelZone_AccodingToTheFeatures(zone);}
		//
		
		updatedc_acctypeofload(zone);
	
		objzone[zone].commingfrom = (COMMINGFROM)LASTEVENT_CLEAR;
	}
	
	///////////////////////////////////////////////////////////////////////////
	void directOnOff_mode1(byte zone)
	{
		if (gettingdc(zone) < MAX_VAL_DUTYCYCLE)//if (objzone[zone].dc < MAX_VAL_DUTYCYCLE)
		{
			if (gettingdc(zone) > objzone[zone].thrshld_sect)//if (objzone[zone].dc > objzone[zone].thrshld_sect)
				{objzone[zone].oorstr.dcr = objzone[zone].dc;}	
			
			settingdc(zone, MAX_VAL_DUTYCYCLE);	//objzone[zone].dc = MAX_VAL_DUTYCYCLE;	
		}
		else
			{settingdc(zone,0 );}//objzone[zone].dc = 0;
		//
__Parsing_UpdateBarZone_AccodingToTheFeatures(zone);
		if (objzone[zone].uCommonProcess.bfCommonProcess._PRINT_PORCENT_OF_DC_LEVEL_)
			{__Parsing_PrintPorcentOfDCLevelZone_AccodingToTheFeatures(zone);}
		//
		
		objzone[zone].commingfrom = (COMMINGFROM)LASTEVENT_DIRECTONOFF;
	
		updatedc_acctypeofload(zone);
	}
	
	///////////////////////////////////////////////////////////////////////////
	void RestoreOnOff_mode2(byte zone)
	{
		if (gettingdc(zone) > objzone[zone].thrshld_sect)	//if (objzone[zone].dc > objzone[zone].thrshld_sect)
			{settingdc(zone, 0);}							//{objzone[zone].dc = 0;}
		else
			{settingdc(zone, MAX_VAL_DUTYCYCLE);}			//{objzone[zone].dc = MAX_VAL_DUTYCYCLE;}
		
		//_______
		__Parsing_UpdateBarZone_AccodingToTheFeatures(zone);
		if (objzone[zone].uCommonProcess.bfCommonProcess._PRINT_PORCENT_OF_DC_LEVEL_)
			{__Parsing_PrintPorcentOfDCLevelZone_AccodingToTheFeatures(zone);}
		//_______
		
		updatedc_acctypeofload(zone);
	}
	
	///////////////////////////////////////////////////////////////////////////
	void directOnOff_mode2(byte zone)
	{
		if (gettingdc(zone) < MAX_VAL_DUTYCYCLE)	//if (objzone[zone].dc < MAX_VAL_DUTYCYCLE)
			{settingdc(zone, MAX_VAL_DUTYCYCLE);}	//{objzone[zone].dc = MAX_VAL_DUTYCYCLE;}
		else
			{settingdc(zone, 0);}					//{objzone[zone].dc = 0;}
		
		//_______
		__Parsing_UpdateBarZone_AccodingToTheFeatures(zone);
		
		if (objzone[zone].uCommonProcess.bfCommonProcess._PRINT_PORCENT_OF_DC_LEVEL_)
			{__Parsing_PrintPorcentOfDCLevelZone_AccodingToTheFeatures(zone);}
		//_______
		
		updatedc_acctypeofload(zone);
	}
                    