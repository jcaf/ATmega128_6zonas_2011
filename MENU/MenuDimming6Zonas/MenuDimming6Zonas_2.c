/*
 * MenuDimming6Zonas_1.c
 *
 * Created: 24/02/2012 04:44:37 p.m.
 *  Author: jcaf
 */ 
#include "Includes/InitializeAllModules.h"

	//////////////////////////////////////////////////////////////////////////
	typedef enum _KEYAPPMODE
	{
		MODE0_NOSYNCHALL=0,
		MODE1_SYNCHALL,
	}KEYAPPMODE;
	
	typedef struct _keyapp_				//independent-key in application-level
	{
		KEYAPPMODE mode;
		byte sm0;		
		byte sm1;
		//byte counter0;	
	}_keyapp;	
	
	static _keyapp keyapp[KB_TOTALOFKEYS];
	
	//////////////////////////////////////////////////////////////////////////
	#define NUMMODES_KEYMIXPS		(2)
	
	typedef enum _KEYMIXSTATES
	{
		SCHEDULER=0,
		KEYS1FX,
		KEYS2FX,
		KEYSEXIT,
	}KEYMIXSTATES;

	typedef struct _keymixps_
	{
		KEYMIXSTATES sm0;
		byte mode;			//modo desde el punto de vista al momento de activar segunda funcion
		byte ikey;			//which key was pressed?
	}_keymixps;				//key mixing in this process

	static _keymixps keymixps;
	//////////////////////////////////////////////////////////////////////////
	typedef enum _CODERETURN
	{
		NOEXIT=0,
		EXIT=1,
	}CODERETURN;

	typedef struct _thisps_
	{
		signed char zone;
		CODERETURN codereturn;
	}_thisps;
	
	static _thisps thisps;
	
	//////////////////////////////////////////////////////////////////////////
	static void key1_mode0(void);
	static void key1_mode1(void);
	static void key2_mode0(void);
	static void key2_mode1(void);
	static void key3_mode0_bef(void);
	static void key3_mode1_bef(void);
	static void key3_mode0_aft(void);
	static void key3_mode1_aft(void);

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
	
	/***************************************************************************************
	***************************************************************************************/
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
	
		//blinkrunz(thisps.zone);
		//namez(thisps.zone);
		//setmodexxz(thisps.zone);
		//dcporcentz(thisps.zone);		
		ks0108SelectFont(SC, ks0108ReadFontData, BLACK);
				
		//ClearOnlyRegionForFindAndPrintNameOfZone();
		FindAndPrintNameOfZone(zone, xiCHIP1);			//name();				//mostrar nombre de Zona
		
		ks0108FillRect(1,63-17,61,0,BLACK);						//recta horizontal separadora
		
		_MarkLevelTo_KeySetMode_TOGGLINGVAL(zone); 
		PrintPorcentOfDCLevel(__If_FadingActive_ReturnNEXTDC_else_ReturnDC(zone));	//maybe in progressive your duty-cycle	
				
		ObjBlink_CaptionOfBarZone_BLINK_RUN_(zone);		//Blink current
	}
	//////////////////////////////////////////////////////////////////////////
	static void messagesynch(void)	//SYNCH
	{
		ClearAllPixel_Less1Border_CHIP1();
		
		ks0108SelectFont(SC, ks0108ReadFontData, BLACK);
		
		ks0108GotoXY(4,3);					ks0108Puts_P(PSTR("Sincroniz."));
		ks0108GotoXY(7,3+SC_HEIGHT);		ks0108Puts_P(PSTR("todas las"));
		ks0108GotoXY(12,3+(SC_HEIGHT<<1));	ks0108Puts_P(PSTR("Zonas"));
		//
		ks0108FillRect(1,63-17,61,0,BLACK);							//Dibujar recta horizontal separadora
		//
		ks0108FillRect(10,63-16,(SC_WIDTH*6) ,12,WHITE);			//limpiar
		//ks0108GotoXY(2,63-16);	ks0108Puts_P(PSTR("U/D/OnOff"));
		_DrawUpTriangleState(12,53);
		_DrawDownTriangleState(27,53);
		_DrawOnOffState(50, 50);
	}
	/***************************************************************************************
	Se ingresa con todo fading finalizado.			
	***************************************************************************************/
	byte MenuDimming6Zonas(void)
	{
		byte i;

		ks0108ClearScreen();
		DrawOnlyMarcoGlobalGLCD();
		DrawOnlyDivisionAt63();
		CaptionOfAllZones();
		DrawBarsVertOfAllZones();
		
		for (i=0; i<NUM_ZONAS; i++)			//Toma los valores actuales de la escena actual ObjSCENEram.CurrentScene
		{
			objzone[i].dcr = EEPROM_ReadWord((const word *)&ObjStorSCENEeep[ObjSCENEram.CurrentScene].vDutyCycleAllZone[i]);
			
			if (objzone[i].dcr <= 0)					//maybe it can be a THRESHOLD!!!!
			{
				objzone[i].dcr = (MAX_VAL_DUTYCYCLE);	//Si la zona fue grabado con <= 0% (Or threshold), dejar x sgte.touch,
			}
			_MarkLevelTo_KeySetMode_TOGGLINGVAL(i);
			objzone[i].InMode = KeySetMode_TOGGLINGVAL;
		}
		
		thisps.codereturn = 0;
		thisps.zone = 0;
		selectzone(thisps.zone);		
		
		keymixps.sm0 = 0;		
		keymixps.mode = 0;
		
		for (i=0; i<KB_TOTALOFKEYS; i++) 
		{keyapp[i].mode = keymixps.mode;}

		keyapp[KB_iKEY4].sm0 = 0;		
		keyapp[KB_iKEY4].sm1 = 0;
		
		bfCommonProcess0.Timmer_BlinkCaption = ON;	//Hab. timmer x Blink caption
		
		SettKb_Dimming6Zones();
		
		while (1)
		{
			if (keymixps.sm0 == SCHEDULER)	
				{schedulerkey();}
			if (keymixps.sm0 == KEYS1FX)	
				{keys1f();}			
			if (keymixps.sm0 == KEYS2FX)		
				{keys2f();}							
			if (keymixps.sm0 == KEYSEXIT)
				{keysexit();}
			
			if (thisps.codereturn == EXIT) {return EXIT;}
			
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
	}	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	static void schedulerkey(void)
	{
		if ( ObjKey[KB_iKEY4].bfSTATE.StableState == KB_KEY_RELEASED )
		{
			if (ObjKey[KB_iKEY1].bfSTATE.InProcessing) {keymixps.ikey=KB_iKEY1;keymixps.sm0 = KEYS1FX;return;}
			if (ObjKey[KB_iKEY2].bfSTATE.InProcessing) {keymixps.ikey=KB_iKEY2;keymixps.sm0 = KEYS1FX;return;}
			if (ObjKey[KB_iKEY3].bfSTATE.InProcessing) {keymixps.ikey=KB_iKEY3;keymixps.sm0 = KEYS1FX;return;}
		}
		if (KB_KEY4_ReadyToRead())	
		{
			if (ObjKey[KB_iKEY4].bfSTATE.AtTimeExpired_BeforeOrAfter == KB_BEFORE_THR)	{}
			else {	if (!ObjKey[KB_iKEY4].bfCTRLKey.Reptt){}	else {}	}				
															
			KB_KEY4_HasBeenRead();
			PlaySound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
			
			//_____________________________________________
			if 	(keyapp[KB_iKEY4].mode == MODE0_NOSYNCHALL)
			{
				selectzone_menus(TORIGHT);
			}
			else if (keyapp[KB_iKEY4].mode == MODE1_SYNCHALL)
			{
				menus();
				
				if (thisps.codereturn == NOEXIT)		
				{	//restore
					ObjBlink_CaptionOfBarZone_Blink_Run_All();
					messagesynch();
					SettKb_Dimming6Zones();	
				}
				
			}
			//_____________________________________________
		}
		if (ObjKey[KB_iKEY4].bfSTATE.StableState == KB_KEY_PRESSED) 
		{
			if ((ObjKey[KB_iKEY1].bfSTATE.InProcessing)||(ObjKey[KB_iKEY2].bfSTATE.InProcessing)||(ObjKey[KB_iKEY3].bfSTATE.InProcessing))
			{
				keymixps.sm0 = KEYS2FX;
				
				if (ObjKey[KB_iKEY4].bfCTRLKey.Reptt)		//stop Reptt si estuviera activo -> guardar/restaurar	
					{ObjKey[KB_iKEY4].bfSTATE.temp = ObjKey[KB_iKEY4].bfCTRLKey.Reptt;}
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
			if 		(keyapp[keymixps.ikey].mode == MODE0_NOSYNCHALL)	{key1_mode0();} 
			else if (keyapp[keymixps.ikey].mode == MODE1_SYNCHALL)		{key1_mode1();} 
		
			KB_KEY1_HasBeenRead();
			ResetCounterTimmerForNewKeepingTimmingBLGLCD();	
		}
		else if (KB_KEY2_ReadyToRead())
		{	
			if 		(keyapp[keymixps.ikey].mode == MODE0_NOSYNCHALL)	{key2_mode0();} 
			else if (keyapp[keymixps.ikey].mode == MODE1_SYNCHALL)		{key2_mode1();} 
		
			KB_KEY2_HasBeenRead();
			ResetCounterTimmerForNewKeepingTimmingBLGLCD();	
		}
		else if (KB_KEY3_ReadyToRead())
		{
			if (ObjKey[KB_iKEY3].bfSTATE.AtTimeExpired_BeforeOrAfter == KB_BEFORE_THR)
			{	
				if 		(keyapp[keymixps.ikey].mode == MODE0_NOSYNCHALL)	{key3_mode0_bef();} 
				else if (keyapp[keymixps.ikey].mode == MODE1_SYNCHALL)		{key3_mode1_bef();} 
			}	
			else 
			{	
				if (!ObjKey[KB_iKEY3].bfCTRLKey.Reptt) {}	else {}
				
				if 		(keyapp[keymixps.ikey].mode == MODE0_NOSYNCHALL)	{key3_mode0_aft();} 
				else if (keyapp[keymixps.ikey].mode == MODE1_SYNCHALL)		{key3_mode1_aft();} 
			}
			PlaySound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
			KB_KEY3_HasBeenRead();
			ResetCounterTimmerForNewKeepingTimmingBLGLCD();	//BackLightGLCD reset-timming
		}
		//espera hasta que se procese ObjKey[keymixps.ikey].bfSTATE.InProcessing = 0
		if (!ObjKey[keymixps.ikey].bfSTATE.InProcessing)	
			{keymixps.sm0 = KEYSEXIT;}	
	}	
	//////////////////////////////////////////////////////
	//2DA_Fn activa
	//////////////////////////////////////////////////////
	static void keys2f(void)
	{	
		byte i;
		
		if (ObjKey[KB_iKEY4].bfSTATE.StableState == KB_KEY_PRESSED)	
		{
			ResetCounterTimmerForNewKeepingTimmingBLGLCD();			//while pressing kb4 resetting
		
			if (KB_KEY1_ReadyToRead())
			{
				if (keyapp[KB_iKEY1].mode == MODE0_NOSYNCHALL)
				{
						KB_KEY1_HasBeenRead();
						PlaySound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
					selectzone_menus(TOLEFT);
				}
			}
			
			if (KB_KEY2_ReadyToRead())
			{
															//tanto el proceso como las teclas cambian a sus respectivos modos
				if (++keymixps.mode >= NUMMODES_KEYMIXPS)		//0..x numero de modos en el proceso
					{keymixps.mode = 0;}
			
				for (i=0; i<KB_TOTALOFKEYS; i++)
					{keyapp[i].mode = keymixps.mode;}		
			
				if (keymixps.mode == MODE1_SYNCHALL)
				{
					ObjBlink_CaptionOfBarZone_BLINK_STOP_(thisps.zone);	
					ObjBlink_CaptionOfBarZone_Blink_Run_All();		
					
					messagesynch();
				}
				else if (keymixps.mode == MODE0_NOSYNCHALL)
				{
					ObjBlink_CaptionOfBarZone_Blink_Stop_All();				
					ObjBlink_CaptionOfBarZone_BLINK_RUN_(thisps.zone);		
					
					selectzone(thisps.zone);
				}
				KB_KEY2_HasBeenRead();	
				PlaySound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);	
			}

			if ( KB_KEY3_ReadyToRead() )
			{
				if (ObjKey[KB_iKEY3].bfSTATE.AtTimeExpired_BeforeOrAfter == KB_BEFORE_THR)	{}
				else{	if (!ObjKey[KB_iKEY3].bfCTRLKey.Reptt)	{} else {}	}

		
				KB_KEY3_HasBeenRead();
				PlaySound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
			}		
		}
		else
			{keymixps.sm0 = KEYSEXIT;} 
	}			
	//////////////////////////////////////////////////////
	//Primero, todos las teclas han sido soltadas-> segundo, limpia la condicion "ReadyToRead" para que sus
	//maquinas de estados se reseteen
	//////////////////////////////////////////////////////
	static void keysexit(void)
	{
		if ( ObjSharedFeatKeys.bfSHARED.AreAllKeysReleased )
		{
			for (keymixps.ikey=0; keymixps.ikey<KB_TOTALOFKEYS; keymixps.ikey++)		//All-Clear states
			{
				ObjKey[keymixps.ikey].bfSTATE.ReadyToRead = KB_CLEAR_READYTOREAD_INAPP;
				ObjKey[keymixps.ikey].bfSTATE.AtTimeExpired_BeforeOrAfter = 0;
			}
			keymixps.sm0 = SCHEDULER;
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
	/////////////////////////////////////////////////////////////////////////////////////////////
	static void key1_mode1(void)
	{
		byte i;
		for (i=0; i<NUM_ZONAS; i++)
		{
			objzone[i].uCommonProcess.bfCommonProcess._PRINT_PORCENT_OF_DC_LEVEL_ = OFF;
			_PreEx_DimmingUp(i);
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////
	static void key2_mode0(void)
	{
		objzone[thisps.zone].uCommonProcess.bfCommonProcess._PRINT_PORCENT_OF_DC_LEVEL_ = ON;
		_PreEx_DimmingDown(thisps.zone);
	}
	/////////////////////////////////////////////////////////////////////////////////////////////
	static void key2_mode1(void)
	{	
		byte i;
		for (i=0; i<NUM_ZONAS; i++)
		{
			objzone[i].uCommonProcess.bfCommonProcess._PRINT_PORCENT_OF_DC_LEVEL_ = OFF;
			_PreEx_DimmingDown(i);
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////
	static void key3_mode0_bef(void)
	{
		objzone[thisps.zone].uCommonProcess.bfCommonProcess._PRINT_PORCENT_OF_DC_LEVEL_ = ON;
		//															//LA REGLA DEL JUEGO ES QUE InMode = KeySetMode_TOGGLINGVAL cada vez q se entra a este menu o cualquier otro archivo similar
		if (objzone[thisps.zone].InMode == KeySetMode_MAXVAL)
		{
			//Si se esta aqui es porque se ha movido DUTYCYCLE A ESTE VALOR, OJO! DUTYCYCLE ESTA(O ESTA YENDO A SU MAXIMO VALOR)
			if (objzone[thisps.zone].dcr == (MAX_VAL_DUTYCYCLE))
				{objzone[thisps.zone].SetLevel = Off100p;}
			else
				{objzone[thisps.zone].SetLevel = Restore;}

			objzone[thisps.zone].InMode = KeySetMode_TOGGLINGVAL;
		}
		else if (objzone[thisps.zone].InMode == KeySetMode_TOGGLINGVAL)
		{
			if(objzone[thisps.zone].SetLevel == Restore)
				{objzone[thisps.zone].SetLevel = Off100p;}
			else if (objzone[thisps.zone].SetLevel == Off100p)
				{objzone[thisps.zone].SetLevel = Restore;}

			objzone[thisps.zone].InMode = KeySetMode_TOGGLINGVAL;
		}
		//
		key3_updateDC(thisps.zone);
	}
	/////////////////////////////////////////////////////////////////////////////////////////////
	static void key3_mode1_bef(void)							// else //syncronizado con todos
	{
		byte i;
		//		
		BOOL AnyZone_IsGreaterThan_Off100p = FALSE;
		for (i=0; i<NUM_ZONAS; i++)			
		{
			if (objzone[i].SetLevel != Off100p)	
			{
				AnyZone_IsGreaterThan_Off100p = TRUE;
				break;
			}
		}			
		//
			
		if (AnyZone_IsGreaterThan_Off100p)
		{
			for (i=0; i<NUM_ZONAS; i++)
			{
				objzone[i].uCommonProcess.bfCommonProcess._PRINT_PORCENT_OF_DC_LEVEL_ = OFF;
					
				if (objzone[i].InMode == KeySetMode_MAXVAL)
				{
					if (objzone[i].dcr == (MAX_VAL_DUTYCYCLE))
					objzone[i].SetLevel = Off100p;
					else
					objzone[i].SetLevel = Restore;

					objzone[i].InMode = KeySetMode_TOGGLINGVAL;
						
					key3_updateDC(i);
				}
				else if (objzone[i].InMode == KeySetMode_TOGGLINGVAL)
				{
					//recien en este punto sychronize all//Off all-> Synchronize from Off100p(ZERO)
					if(objzone[i].SetLevel == Restore)
					{
						objzone[i].SetLevel = Off100p;
						objzone[i].InMode = KeySetMode_TOGGLINGVAL;
							
						key3_updateDC(i);		//afecta solo a quien lo necesita
					}
				}
			}
		}
		else
		{
			//entra con todos las Zonas en 0% por AnyZone_IsGreaterThan_Off100p()
			for (i=0; i < NUM_ZONAS; i++)
			{
				objzone[i].uCommonProcess.bfCommonProcess._PRINT_PORCENT_OF_DC_LEVEL_ = OFF;
				//
				//if (ObjZONEram[i].SetLevel == Off100p)	//seria redundar
				{objzone[i].SetLevel = Restore;}		//restore/ON 100%
					
				objzone[i].InMode = KeySetMode_TOGGLINGVAL;
					
				key3_updateDC(i);
			}
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////
	static void key3_mode0_aft(void)
	{
		objzone[thisps.zone].uCommonProcess.bfCommonProcess._PRINT_PORCENT_OF_DC_LEVEL_ = ON;
		//
		objzone[thisps.zone].SetLevel = ON100p;
		objzone[thisps.zone].InMode = KeySetMode_MAXVAL;		//Deja en modo MAXVAL
		//
		key3_updateDC(thisps.zone);
	}
	/////////////////////////////////////////////////////////////////////////////////////////////
	static void key3_mode1_aft(void)
	{
		//syncronizado con todos
		byte i;
		for (i=0; i<NUM_ZONAS; i++)
		{
			objzone[i].uCommonProcess.bfCommonProcess._PRINT_PORCENT_OF_DC_LEVEL_ = OFF;

			objzone[i].SetLevel = ON100p;
			objzone[i].InMode = KeySetMode_MAXVAL;		//Deja en modo MAXVAL

			key3_updateDC(i);
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////
	void key3_updateDC(byte zone)
	{
		GettingReadyForNewLevelOfDC_Zone(zone);					//Prepara todos los valores
		
		__Parsing_UpdateBarZone_AccodingToTheFeatures(zone);

		if (objzone[zone].uCommonProcess.bfCommonProcess._PRINT_PORCENT_OF_DC_LEVEL_)	
		{__Parsing_PrintPorcentOfDCLevelZone_AccodingToTheFeatures(zone);}
		
		UpdatingDCofZone_AccodingToTheFeatures(zone);			//Ejecuta
	}

	/////////////////////////////////////////////////////////////////////////
	static void selectzone_menus(signed char dir)
	{
		if (keyapp[KB_iKEY4].sm0 == 0)
		{
			thisps.zone += dir;

			if (thisps.zone < 0)
			{
				ObjBlink_CaptionOfBarZone_BLINK_STOP_(0);
				thisps.zone = NUM_ZONAS-1;
				keyapp[KB_iKEY4].sm0++;
			}
			else if (thisps.zone >= NUM_ZONAS)
			{
				ObjBlink_CaptionOfBarZone_BLINK_STOP_(NUM_ZONAS-1);
				thisps.zone = 0;
				keyapp[KB_iKEY4].sm0++;
			}
			else
			{
				ObjBlink_CaptionOfBarZone_BLINK_STOP_(thisps.zone + (dir*-1) );
				selectzone(thisps.zone);
			}
		}
		
		if (keyapp[KB_iKEY4].sm0 > 0 )
		{
			if (keyapp[KB_iKEY4].sm0 == 1)
			{
				menus();
				
				if (thisps.codereturn == NOEXIT)
				{
					//restore
					selectzone(thisps.zone);	//Re-blink through this function
					SettKb_Dimming6Zones();
					keyapp[KB_iKEY4].sm0 = 0;
				}		
			}
		}
	}
	/////////////////////////////////////////////////////////////////////////
	static void menus(void)
	{
		if (keyapp[KB_iKEY4].sm1 == 0)
		{
			waitfor();
			keyapp[KB_iKEY4].sm1++;
		}
		
		if (keyapp[KB_iKEY4].sm1 > 0)
		{
			if (keyapp[KB_iKEY4].sm1 == 1)
			{
				ClearAllPixel_Less1Border_CHIP1();
				if	( Handler_DialogBox_SiNo_Salir(2,2) )
				{
					bfCommonProcess0.Timmer_BlinkCaption = OFF;
					thisps.codereturn = 1;
				}
				ClearAllPixel_Less1Border_CHIP1();

				
				keyapp[KB_iKEY4].sm1 = 0;
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

		while ( !ObjSharedFeatKeys.bfSHARED.AreAllKeysReleased )
			{ResetCounterTimmerForNewKeepingTimmingBLGLCD();}

		for (byte i=0; i<KB_TOTALOFKEYS; i++)		//All-Clear states
		{
			ObjKey[i].bfSTATE.ReadyToRead = KB_CLEAR_READYTOREAD_INAPP;
			ObjKey[i].bfSTATE.AtTimeExpired_BeforeOrAfter = 0;
		}
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
	/**************************************************************************************
	**************************************************************************************/
	//void ShowSetLevelInGLCD(byte thisps.zone)	
	//{
		//__Parsing_UpdateBarZone_AccodingToTheFeatures(thisps.zone);
		//__Parsing_PrintPorcentOfDCLevelZone_AccodingToTheFeatures(thisps.zone);
	//}
	
	void RestoreOnOff_mode1(byte zone)
	{
		if (objzone[zone].dc > objzone[zone].thrshld_sect)
		{
			if (objzone[zone] == MAX_VAL_DUTYCYCLE)
			{
				if (objzone[zone].commingfrom == (COMMINGFROM)LASTEVENT_DIRECTONOFF)//viene desde fromdirectonoff
				{
					if (objzone[zone].dcr < MAX_VAL_DUTYCYCLE)
					{
						objzone[zone].dc = objzone[zone].dcr;
						goto __exit_thisfx;
					}
				}
			}	
			//para el resto de situaciones
			objzone[zone].dcr = objzone[zone].dc;
			objzone[zone].dc = 0;
		}
		else
		{
			if (objzone[zone].laidsw == SECTION_LESSEQUALTHAN_THRSHLD )
			{
										//direct, perdio su dcr al bajar a este punto
				if ( objzone[zone].cfgtorestore_atlevel== (CFGTORESTORE_ATLEVEL)MAXVAL)
					{objzone[zone].dc = MAX_VAL_DUTYCYCLE;}	
				else if ( objzone[zone].cfgtorestore_atlevel == (CFGTORESTORE_ATLEVEL)thrshld_sect_MAS_1)
					{objzone[zone].dc = objzone[zone].thrshld_sect+1;}
			}
			else if (objzone[zone].laidsw == SECTION_GREATERTHAN_THRSHLD )
			{
				objzone[zone].dc = objzone[zone].dcr;
			}
		}
		__exit_thisfx:
	
		UpdatingDCofZone_AccodingToTheFeatures(objzone[zone].dc);
	
		objzone[zone].commingfrom = (COMMINGFROM)LASTEVENT_CLEAR;
	}
	///////////////////////////////////////////////////////////////////////////
	void directOnOff_mode1(zone)
	{
		if (objzone[zone].dc < MAX_VAL_DUTYCYCLE)
		{
			if (objzone[zone].dc > objzone[zone].thrshld_sect)
				{objzone[zone].dcr = objzone[zone].dc;}	
		
			objzone[zone].dc = MAX_VAL_DUTYCYCLE;	
		}
		else
			{objzone[zone].dc = 0;}
		//
		objzone[zone].commingfrom = (COMMINGFROM)LASTEVENT_DIRECTONOFF;
	
		UpdatingDCofZone_AccodingToTheFeatures(objzone[zone].dc);
	}
	/////////////--------------------------//////////////
	void RestoreOnOff_mode1(byte zone)
	{
		if (objzone[zone].dc > objzone[zone].thrshld_sect)
			{objzone[zone].dc = 0;}
		else
			{objzone[zone].dc = MAX_VAL_DUTYCYCLE;}
		UpdatingDCofZone_AccodingToTheFeatures(objzone[zone].dc);
	}
	///////////////////////////////////////////////////////////////////////////
	void directOnOff_mode1(byte zone)
	{
		if (objzone[zone].dc < MAX_VAL_DUTYCYCLE)
			{objzone[zone].dc = MAX_VAL_DUTYCYCLE;}
		else
			{objzone[zone].dc = 0;}
		UpdatingDCofZone_AccodingToTheFeatures(objzone[zone].dc);
	}


	//+++++++++++++++++++++++++++++++++++++//+++++++++++++++++++++++++++
	//inital val.. por ahora en RAM!
	for (i=0; i<NUM_ZONAS; i++)
		{objzone[i].thrshld_sect = (byte)(0.1 * MAX_VAL_DUTYCYCLE);}


	void checklevel(byte zone)
	{
		//------------------------------------------------check for inner/outer section
		if (objzone[zone].dc > objzone[zone].thrshld_sect)
			{objzone[zone].laidsw = SECTION_GREATERTHAN_THRSHLD ;}
		else
			{objzone[zone].laidsw = SECTION_LESSEQUALTHAN_THRSHLD ;}
			
		//------------------------------------------------check for			
		//------------------------------------------------check for			
	}

	dimmin+
	{
		dc++;

		//set levels
		if (objzone[zone].dc > objzone[zone].thrshld_sect)
		{
			objzone[zone].laidsw = SECTION_GREATERTHAN_THRSHLD;
		
			if (objzone[zone].dc == (objzone[zone].thrshld_sect+1) )
				{PlaySound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);}
		}
	}
	//-----------------
	dimming-
	{
		dc--;
	
		//set levels
		if (objzone[zone].dc <= objzone[zone].thrshld_sect)
		{
			objzone[zone].laidsw = SECTION_LESSEQUALTHAN_THRSHLD ;

			if (objzone[zone].cfgmodeof_diLET_thrshld == (CFGMODEOF_DIMM_IN_LESSEQUALTHAN_THRSHLD)AUTOMATIC_BYPASS )
			{
				if (objzone[zone].dc == objzone[zone].thrshld_sect)
				{
					PlaySound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
					objzone[zone].dc = 0;	
				}
			}
		}
	
	}