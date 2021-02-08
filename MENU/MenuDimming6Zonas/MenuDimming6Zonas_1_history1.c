/*
 * MenuDimming6Zonas_1.c
 *
 * Created: 24/02/2012 04:44:37 p.m.
 *  Author: jcaf
 */ 
#include "Includes/InitializeAllModules.h"

	volatile _MD6Z_FLAGS MD6Z_FLAGS;

volatile byte CountTicks_BlinkCaptionZone=0;	
void ObjBlink_Timming_CaptionOfBarZone(void);

		
	byte ChooseIfEnter_MD6Z(void);
	byte MenuDimming6Zonas(void);	
	byte ReturnToMenuPadre_Dimming6Zonas(void);

	static void PeriodicCall_Thread_FadingProcess_AllZone(void);

	byte FADING_IsFadingInAllZoneFinished(void);

//:::::::::::::::::::
#define _KTE_BLINK_GO2RIGHT_	(+1)
#define _KTE_BLINK_GO2LEFT_		(-1)
void HandlerEvents_(signed char BLINK_RIGHT_LEFT, byte _KB_iKEYx_);
//:::::::::::::::::::

	/***************************************************************************************
	//Setting Keyboard for this stage(void)
	***************************************************************************************/
	void SettKb_Dimming6Zones(void) 
	{
		ObjKey[KB_iKEY1].bfCTRLKey.OnKeyPressed  =1;
		ObjKey[KB_iKEY1].bfCTRLKey.Reptt = 1;
		ObjKey[KB_iKEY1].bfCTRLKey.Group_AutoExcluding = 1;
		//.................................		
		ObjKey[KB_iKEY2].bfCTRLKey.OnKeyPressed  =1;
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
	
	/***************************************************************************************
	***************************************************************************************/
	byte SchedulingPreEnter_MD6Z(void)
	{
		byte exitfx = ChooseIfEnter_MD6Z();	//It can return only 0 or 1

		if (exitfx)	
			{return MenuDimming6Zonas();}	//It can return only 0 or 1
		return	exitfx;
	}

	/***************************************************************************************
	***************************************************************************************/
    byte ChooseIfEnter_MD6Z(void)
    {
		ClearAllPixel_Less1Border_CHIP1();

        ks0108SelectFont(SC, ks0108ReadFontData, BLACK);
		ks0108GotoXY(5,10);ks0108Puts_P(PSTR("Dimming"));
		ks0108GotoXY(5,22);ks0108Puts_P(PSTR("por Zonas?"));
		//
		ks0108GotoXY(3,47);ks0108Puts_P(PSTR("Seleccionar"));
		ks0108InvertRect(1,47,61,0x0D+2);
	
		while (1)
        {
            if (KB_KEY1_ReadyToRead()) {KB_KEY1_HasBeenRead();}
            if (KB_KEY2_ReadyToRead()) {KB_KEY2_HasBeenRead();}
            
			if (KB_KEY3_ReadyToRead())	
            {
					ScroolingZ_CHIP1();
					BUZZER_FLAGS.BUZZER_Triggered = 1;
					KB_KEY3_HasBeenRead();
				return 1;								
            }
            
            if (KB_KEY4_ReadyToRead())	//Deja pasar, retorna a menu padre
            {
					ScroolingZ_CHIP1();
					BUZZER_FLAGS.BUZZER_Triggered = 1;
					KB_KEY4_HasBeenRead();
				return 0;
            }
        }
    }
	
	/***************************************************************************************
	
	//ClearAllPixel_LessTheBorder_CHIP1();//DrawMainFrameAndBarsToD6Z();
	***************************************************************************************/
	void InitializeEnter_MD6Z(byte CurrentZone)
	{
		SettKb_Dimming6Zones();
		
		ks0108SelectFont(SC, ks0108ReadFontData, BLACK);
		
		ks0108GotoXY(10,3);ks0108Puts_P(PSTR("Zona:"));
		ks0108InvertRect(1,1,61,15);
		
		//
		ObjBlink_CaptionOfBarZone_InitAllCounterTimer();
		ObjBlink_CaptionOfBarZone[CurrentZone].bfBlink.RunStop = _BLINK_RUN_;	
		//
		ClearOnlyRegion_FindAndPrintNameOfZone();
		FindAndPrintNameOfZone(CurrentZone, xiCHIP1);			//mostrar nombre de Zona

		ks0108FillRect(1,63-17,61,0,BLACK);						//Dibujar recta horizontal separadora

		_MarkLevelTo_KeySetMode_TOGGLINGVAL(CurrentZone); 

		PrintPorcentOfDCLevel(__If_FadingActive_ReturnNEXTDC_else_ReturnDC(CurrentZone));	//maybe in progressive your duty-cycle	
	}

	byte Schedule_MenuDimming6Zonas=0;	
	static signed char CurrentZone;	

	/***************************************************************************************
	Se ingresa con todo fading finalizado.			
	***************************************************************************************/
	byte MenuDimming6Zonas(void)
	{
		//byte CurrentZone;	
		byte i;
		
		for (CurrentZone=0; CurrentZone<NUM_ZONAS; CurrentZone++)
		{
			ObjZONEram[CurrentZone].DutyCycleToRestore=
									EEPROM_ReadWord( (const word *)&ObjStorSCENEeep[ObjSCENEram.CurrentScene].vDutyCycleAllZone[CurrentZone]);	
		}
		//_______________________________________________________________________________________________________
		//Si la zona fue grabado con <= 0% (Or threshold), dejar x sgte.touch, 
		for (CurrentZone=0; CurrentZone<NUM_ZONAS; CurrentZone++)
		{
			if (ObjZONEram[CurrentZone].DutyCycleToRestore <= 0)	//maybe it can be a THRESHOLD!!!!
				 {ObjZONEram[CurrentZone].DutyCycleToRestore = NUM_ELEM_DENTRO_BAR*FACTOR_ESCALA_DIMMING;}
		}		
		//_______________________________________________________________________________________________________
		
		ClearAllPixel_Less1Border_CHIP1();	
		//		
		CurrentZone=0;
		InitializeEnter_MD6Z(CurrentZone);		
		//
		byte scheduler_main=0;
		byte iKey;

		while (1)
		{
			if (scheduler_main == 0)	
			{
				if ( ObjKey[KB_iKEY4].bfSTATE.StableState == KB_KEY_RELEASED )
				{	
					if (ObjKey[KB_iKEY1].bfSTATE.InProcessing) {iKey = KB_iKEY1;scheduler_main = 1;}
					if (ObjKey[KB_iKEY2].bfSTATE.InProcessing) {iKey = KB_iKEY2;scheduler_main = 1;}
					if (ObjKey[KB_iKEY3].bfSTATE.InProcessing) {iKey = KB_iKEY3;scheduler_main = 1;}
				}
				
				//_____________________________________________________________________________________________
				if ( KB_KEY4_ReadyToRead() )	
				{
					//Key4 es el encargado de mover/activar <--> cada zona, asi como de llegar a los menues
					
					//_____________________________________________________________________________________
					//if (ObjKey[KB_iKEY4].bfSTATE.AtTimeExpired_BeforeOrAfter == KB_BEFORE_THR)
					//else	
					//{	if (!ObjKey[KB_iKEY4].bfCTRLKey.Reptt)	//No Reptt
					//else										//Reptt
					//}
					//KB_KEY4_HasBeenRead();	
					//_____________________________________________________________________________________

					HandlerEvents_( _KTE_BLINK_GO2RIGHT_, KB_iKEY4 );	//avanza hacia la derecha.
					
					//KB_KEY4_HasBeenRead();
					//BUZZER_FLAGS.BUZZER_Triggered = 1;
				}
								
				//_____________________________________________________________________________________________
				if (ObjKey[KB_iKEY4].bfSTATE.StableState == KB_KEY_PRESSED) //kEY4 Pressed
				{
					if ((ObjKey[KB_iKEY1].bfSTATE.InProcessing)||(ObjKey[KB_iKEY2].bfSTATE.InProcessing)||(ObjKey[KB_iKEY3].bfSTATE.InProcessing))
					{
						scheduler_main = 2;
						//ObjKey[KB_iKEY4].bfSTATE.temp = ObjKey[KB_iKEY4].bfCTRLKey.Reptt;//stop Reptt si estuviera activo -> guardar/restaurar
					}
				}
				
			}
			/*........................................................................................................
			........................................................................................................*/	
			if (scheduler_main == 1)	//NO-2DA_Fn
			{
				if ( KB_KEY1_ReadyToRead() )
				{
					if (!MD6Z_FLAGS.EncDesSynch)
					{	
						_PreEx_DimmingUp(CurrentZone, __PRINT_PORCENT_OF_DC_LEVEL__);	
					}					
					else
					{	for (i=0; i< NUM_ZONAS; i++)
							_PreEx_DimmingUp(i, __DONT_PRINT_PORCENT_OF_DC_LEVEL__);	
					}					
					//
					KB_KEY1_HasBeenRead();
				}
				else if ( KB_KEY2_ReadyToRead() )
				{
					if (!MD6Z_FLAGS.EncDesSynch)
					{
						_PreEx_DimmingDown(CurrentZone, __PRINT_PORCENT_OF_DC_LEVEL__);			
					}					
					else
					{	for (i=0; i< NUM_ZONAS; i++)
							_PreEx_DimmingDown(i, __DONT_PRINT_PORCENT_OF_DC_LEVEL__);
					}					
					//
					KB_KEY2_HasBeenRead();
				}
				else if ( KB_KEY3_ReadyToRead() )
				{
					if (ObjKey[KB_iKEY3].bfSTATE.AtTimeExpired_BeforeOrAfter == KB_BEFORE_THR)
					{
						if (ObjZONEram[CurrentZone].InMode == KeySetMode_MAXVAL)
						{
							if (ObjZONEram[CurrentZone].DutyCycleToRestore == (NUM_ELEM_DENTRO_BAR*FACTOR_ESCALA_DIMMING))			
								{ObjZONEram[CurrentZone].SetLevel = Off100p;}
							else 
								{ObjZONEram[CurrentZone].SetLevel = Restore;}

							ObjZONEram[CurrentZone].InMode = KeySetMode_TOGGLINGVAL;				
						}
						else
						{
							if(ObjZONEram[CurrentZone].SetLevel == Restore) 	{ObjZONEram[CurrentZone].SetLevel = Off100p;}
							else if (ObjZONEram[CurrentZone].SetLevel==Off100p)	{ObjZONEram[CurrentZone].SetLevel = Restore;}	
						
							ObjZONEram[CurrentZone].InMode = KeySetMode_TOGGLINGVAL;	
						}
					}
					else	//> threshold
					{
						//SE PUEDE APLICAR REPETITIBILIDAD!!!!
						
							//if (!ObjKey[KB_iKEY3].bfCTRLKey.Reptt)	//No Reptt
							//	ks0108Puts_P(PSTR("3b")); 
							//else //Reptt
							//	ks0108Puts_P(PSTR("3br")); 
						ObjZONEram[CurrentZone].SetLevel = ON100p;
						ObjZONEram[CurrentZone].InMode = KeySetMode_MAXVAL;			
					}
		
					GettingReadyForNewLevelOfDC_Zone(CurrentZone);					//Prepara todos los valores
					//
					__Parsing_UpdateBarZone_AccodingToTheFeatures(CurrentZone);
					__Parsing_PrintPorcentOfDCLevelZone_AccodingToTheFeatures(CurrentZone);			
					//		
					UpdatingDCofZone_AccodingToTheFeatures(CurrentZone);			//Ejecuta 

					BUZZER_FLAGS.BUZZER_Triggered = 1;
					KB_KEY3_HasBeenRead();	
				}
				
				//_____________________________________
				if (!ObjKey[iKey].bfSTATE.InProcessing)
					{scheduler_main =3;}	
			}			

	
			/*........................................................................................................
			........................................................................................................*/	
			if (scheduler_main == 2)		//2DA_Fn activa
			{
				if (ObjKey[KB_iKEY4].bfSTATE.StableState == KB_KEY_PRESSED)	
				{
					if ( KB_KEY1_ReadyToRead() )
					{
						if (!MD6Z_FLAGS.EncDesSynch)
						{
							HandlerEvents_(_KTE_BLINK_GO2LEFT_, KB_iKEY1);

							//KB_KEY1_HasBeenRead(); //es notificado como leido en HandlerEvents_(xxx,KB_iKEY1)
							//BUZZER_FLAGS.BUZZER_Triggered = 1;
						}
					}

					if ( KB_KEY2_ReadyToRead() )
					{
						MD6Z_FLAGS.EncDesSynch = !MD6Z_FLAGS.EncDesSynch;	//Enclavamiento/desenclavamiento
						
						if (MD6Z_FLAGS.EncDesSynch)
						{
							ObjBlink_CaptionOfBarZone_BLINK_STOP_(CurrentZone);	//Stop actual
							for (i=0; i<NUM_ZONAS; i++)	
								{ObjBlink_CaptionOfBarZone[i].bfBlink.RunStop = _BLINK_RUN_;}	
						}
						else
						{
							for (i=0; i<NUM_ZONAS; i++)
								{ObjBlink_CaptionOfBarZone_BLINK_STOP_(i);}
							//							
							ObjBlink_CaptionOfBarZone[CurrentZone].bfBlink.RunStop = _BLINK_RUN_;	
						}
						
						KB_KEY2_HasBeenRead();	
						BUZZER_FLAGS.BUZZER_Triggered = 1;	
					}

					if ( KB_KEY3_ReadyToRead() )
					{
						if (ObjKey[KB_iKEY3].bfSTATE.AtTimeExpired_BeforeOrAfter == KB_BEFORE_THR)
							ks0108Puts_P(PSTR("c3a")); 
						else
							
							if (!ObjKey[KB_iKEY3].bfCTRLKey.Reptt)	//No Reptt
								ks0108Puts_P(PSTR("c3b")); 
							else //Reptt
								ks0108Puts_P(PSTR("c3br")); 

						KB_KEY3_HasBeenRead();	
						BUZZER_FLAGS.BUZZER_Triggered = 1;		
					}		
				}
				else
					scheduler_main = 3;
			}							
			
			/*........................................................................................................
			Primero, todos las teclas han sido soltadas-> segundo, limpia la condicion "ReadyToRead" para que sus
			maquinas de estados se reseteen
			........................................................................................................*/	
			if (scheduler_main == 3)
			{
				if ( ObjSharedFeatKeys.bfSHARED.AreAllKeysReleased )
				{
					for (iKey=0; iKey<KB_TOTALOFKEYS; iKey++)		//All-Clear states
					{
						ObjKey[iKey].bfSTATE.ReadyToRead = KB_CLEAR_READYTOREAD_INAPP;
						ObjKey[iKey].bfSTATE.AtTimeExpired_BeforeOrAfter = 0;
					}
					scheduler_main=0;
				}
			}
			
		//...............................
		if (MD6Z_FLAGS.InitBlinkCaptionZone)
		{	
			MD6Z_FLAGS.InitBlinkCaptionZone=0;
			ObjBlink_Timming_CaptionOfBarZone();
		}
		//...............................
		//
		PeriodicCall_Thread_FadingProcess_AllZone();
		
		}
	}	

	/***********************************************************************
	***********************************************************************/
	inline void ObjBlink_CaptionOfBarZone_BlinkDirection(byte CurrentZone, signed char KTE_RL)
	{
		ObjBlink_CaptionOfBarZone_BLINK_STOP_(CurrentZone + KTE_RL);			//KTE_Right Or Left
		ObjBlink_CaptionOfBarZone[CurrentZone].bfBlink.RunStop = _BLINK_RUN_;
	}
	
	/***********************************************************************
	***********************************************************************/
	void HandlerEvents_(signed char BLINK_RIGHT_LEFT, byte _KB_iKEYx_)
	{
		
if (MD6Z_FLAGS.EncDesSynch)
{
	Schedule_MenuDimming6Zonas = 1;	//>0
	//
	ObjKey[_KB_iKEYx_].bfSTATE.ReadyToRead = KB_CLEAR_READYTOREAD_INAPP;
	BUZZER_FLAGS.BUZZER_Triggered = 1;
}
			


	
		if (Schedule_MenuDimming6Zonas == 0)
		{
			CurrentZone += BLINK_RIGHT_LEFT;

			if ( CurrentZone < 0 )
			{
				ObjBlink_CaptionOfBarZone_BLINK_STOP_(0);			//Stop Blink
				Schedule_MenuDimming6Zonas++;
			}
			else if ( CurrentZone >= NUM_ZONAS )
			{
				ObjBlink_CaptionOfBarZone_BLINK_STOP_(NUM_ZONAS-1); //Stop Blink
				Schedule_MenuDimming6Zonas++;
			}
			else
			{
				ScroolingZ_CHIP1();
				
				ObjBlink_CaptionOfBarZone_BlinkDirection(CurrentZone, (BLINK_RIGHT_LEFT*-1) );

				//
				ClearOnlyRegion_FindAndPrintNameOfZone();
				FindAndPrintNameOfZone(CurrentZone,xiCHIP1);
				//
				_MarkLevelTo_KeySetMode_TOGGLINGVAL(CurrentZone);
				PrintPorcentOfDCLevel(__If_FadingActive_ReturnNEXTDC_else_ReturnDC(CurrentZone));	//maybe in progressive your duty-cycle
				//
			}

			//1- Podria usar esta comparacion, pero mejor directamente lo paso a 2.-
			//if (__KeyPressed__ == 1) {KB_KEY1_HasBeenRead();}
			//else if (__KeyPressed__ == 2) {KB_KEY2_HasBeenRead();}
			//else if (__KeyPressed__ == 4) {KB_KEY4_HasBeenRead();}
			//

			//2.-
			//#define KB_KEY4_HasBeenRead() do{ObjKey[KB_iKEY4].bfSTATE.ReadyToRead = KB_CLEAR_READYTOREAD_INAPP;}while(0)
			//
			ObjKey[_KB_iKEYx_].bfSTATE.ReadyToRead = KB_CLEAR_READYTOREAD_INAPP;
			BUZZER_FLAGS.BUZZER_Triggered = 1;
			//
		}

		//________________________________________________________			
		if (Schedule_MenuDimming6Zonas == 1)
		{
			if (DIMMING_FLAGS.TIMER0_IsActiveFading)
			{
				MessageBox(128,32);				//Splash message!
				Schedule_MenuDimming6Zonas+=1;
			}
			else
			Schedule_MenuDimming6Zonas+=2;
		}
		//________________________________________________________	
		if (Schedule_MenuDimming6Zonas == 2)	//waiting all Fading-processes had finished
		{
				
			while (DIMMING_FLAGS.TIMER0_IsActiveFading)
			{PeriodicCall_Thread_FadingProcess_AllZone();}

			//...........................................................................................
			//Pintar nuevamente recuadro.!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			ks0108FillRect(xiCHIP2+1, yiCHIP2+1, (xfCHIP3-1)-(xiCHIP2+1), (yfCHIP2-1)-(yiCHIP2+1), WHITE);
			CaptionOfAllZones();
			DrawBarsVertOfAllZones();
			UpdateBar_DirectShow_AllZone((void *) &ObjZONEram[0].DutyCycle);	//estable zona
			//...........................................................................................

			Schedule_MenuDimming6Zonas++;
		}
		//________________________________________________________
		if (Schedule_MenuDimming6Zonas == 3)
		{
			ScroolingZ_CHIP1();
			
			//-->> esperar
			
			while ( !ObjSharedFeatKeys.bfSHARED.AreAllKeysReleased ) {;}
			
			//if ( ObjSharedFeatKeys.bfSHARED.AreAllKeysReleased )
			//{
				for (byte iKey=0; iKey<KB_TOTALOFKEYS; iKey++)		//All-Clear states
				{
					ObjKey[iKey].bfSTATE.ReadyToRead = KB_CLEAR_READYTOREAD_INAPP;
					ObjKey[iKey].bfSTATE.AtTimeExpired_BeforeOrAfter = 0;
				}
			//}
			//-->>			
			
			SchedulingPreEnter_GuardarEscena();
			SettKb_Dimming6Zones();
			Schedule_MenuDimming6Zonas++;
		}
		//________________________________________________________	
		if (Schedule_MenuDimming6Zonas == 4)
		{
			if (ReturnToMenuPadre_Dimming6Zonas())
			{
				return 1;
			}
				
			Schedule_MenuDimming6Zonas=0;
			
			CurrentZone = 0;
			InitializeEnter_MD6Z(CurrentZone);
		}
		//________________________________________________________
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
	/***************************************************************************************
	***************************************************************************************/
	byte ReturnToMenuPadre_Dimming6Zonas(void)
    {
		ClearAllPixel_Less1Border_CHIP1();

        ks0108SelectFont(SC, ks0108ReadFontData, BLACK);
		ks0108GotoXY(10,10);ks0108Puts_P(PSTR("Retornar?"));
		
		ks0108GotoXY(3,47);ks0108Puts_P(PSTR("Seleccionar"));
		ks0108InvertRect(1,47,61,0x0D+2);

        while (1)
        {
            if (KB_KEY1_ReadyToRead()){KB_KEY1_HasBeenRead();}
            if (KB_KEY2_ReadyToRead()){KB_KEY2_HasBeenRead();}
            if (KB_KEY3_ReadyToRead())
            {
                KB_KEY3_HasBeenRead();

					BUZZER_FLAGS.BUZZER_Triggered = 1;

					ScroolingCHIP1up_CHIP2down_CHIP3up();
				
					return 1;   
				
            }
            if (KB_KEY4_ReadyToRead())
            {
					ScroolingZ_CHIP1();
					//ClearAllPixel_LessTheBorder_CHIP1();	//limpia chip1
					ks0108FillRect(1,10,61,28,WHITE);				//clear - parte superior
					ks0108FillRect(1,47,61,0x0D+2,WHITE);			//clear - parte inferior

					BUZZER_FLAGS.BUZZER_Triggered = 1;
					KB_KEY4_HasBeenRead();
				return 0;
            }
        }
    }
	
	/***************************************************************************************
	Llamado desde ISR()
	***************************************************************************************/
	void Timmer_MD6Z(void)
	{
			//if (++CountTicks_BlinkCaptionZone == 60)	//5ms*60= 300ms
			//{	  CountTicks_BlinkCaptionZone = 0;
			//
				MD6Z_FLAGS.InitBlinkCaptionZone=1;
			//}
	}
	/**************************************************************************************
	**************************************************************************************/
	//void ShowSetLevelInGLCD(byte CurrentZone)	
	//{
		//__Parsing_UpdateBarZone_AccodingToTheFeatures(CurrentZone);
		//__Parsing_PrintPorcentOfDCLevelZone_AccodingToTheFeatures(CurrentZone);
	//}
	
