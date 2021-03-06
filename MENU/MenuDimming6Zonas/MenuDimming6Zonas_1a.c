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
	byte HandlerSections(signed char BLINK_RIGHT_LEFT, byte _KB_iKEYx_);
	//:::::::::::::::::::

	#define _DESENCLAVAR_SYNCHRONIZMO_ALL_ZONE_ (0)
	#define _ENCLAVAR_SYNCHRONIZMO_ALL_ZONE_	(1)
	
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
					PlaySound(0);
					KB_KEY3_HasBeenRead();
					
					//
					ScroolingZ_CHIP1();
				return 1;								
            }
            
            if (KB_KEY4_ReadyToRead())	//Deja pasar, retorna a menu padre
            {
					PlaySound(0);
					KB_KEY4_HasBeenRead();
					//
					ScroolingZ_CHIP1();
				return 0;
            }
        }
    }

	/***************************************************************************************
	***************************************************************************************/
	void StatusMessageInSynchAllMode(void)
	{
		ClearAllPixel_Less1Border_CHIP1();
		
		ks0108SelectFont(SC, ks0108ReadFontData, BLACK);
				
		ks0108GotoXY(3,3);				ks0108Puts_P(PSTR("Sincronizado"));
		ks0108GotoXY(3,3+SC_HEIGHT);	ks0108Puts_P(PSTR("todas las"));
		ks0108GotoXY(3,3+3+SC_HEIGHT);	ks0108Puts_P(PSTR("Zonas"));
		//
		ks0108FillRect(1,63-17,61,0,BLACK);							//Dibujar recta horizontal separadora			
		//
		ks0108FillRect(10,63-16,(SC_WIDTH*6) ,12,WHITE);			//limpiar
		ks0108GotoXY(10,63-16);	ks0108Puts_P(PSTR("UP/DOWN/ONOFF"));
	}

	/***************************************************************************************
	
	***************************************************************************************/
	void ShowCurrentStatusOfZone(byte CurrentZone)
	{
		ClearAllPixel_Less1Border_CHIP1();
			
		ks0108SelectFont(SC, ks0108ReadFontData, BLACK);
		//		
		ClearOnlyRegionForFindAndPrintNameOfZone();				//mostrar nombre de Zona
		FindAndPrintNameOfZone(CurrentZone, xiCHIP1);			
		//
		ks0108FillRect(1,63-17,61,0,BLACK);						//Dibujar recta horizontal separadora
		//
		_MarkLevelTo_KeySetMode_TOGGLINGVAL(CurrentZone); 
		PrintPorcentOfDCLevel(__If_FadingActive_ReturnNEXTDC_else_ReturnDC(CurrentZone));	//maybe in progressive your duty-cycle	
				
		ObjBlink_CaptionOfBarZone_BLINK_RUN_(CurrentZone);		//Blink current
	}
	/******************************************************************************

	******************************************************************************/
	#define _SECTION_SELECT_CURRENT_ZONE_ (0)
	
	#define _disable_section_Select_Current_Zone()	do{Schedule_MenuDimming6Zonas = 1;}while(0)
	#define _enable_section_Select_Current_Zone()	do{Schedule_MenuDimming6Zonas = _SECTION_SELECT_CURRENT_ZONE_;}while(0)
	
	byte Schedule_MenuDimming6Zonas;	
	static signed char CurrentZone;	

	/***************************************************************************
	Ver. MenuDimming6Zonas_2.c como guia de repaso
	***************************************************************************/
	void _parsingA(byte CurrentZone)
	{
		if (ObjZONEram[CurrentZone].InMode == KeySetMode_MAXVAL)
		{
			if (ObjZONEram[CurrentZone].DutyCycleToRestore == (NUM_ELEM_DENTRO_BAR*FACTOR_ESCALA_DIMMING))
				{ObjZONEram[CurrentZone].SetLevel = Off100p;}
			else
				{ObjZONEram[CurrentZone].SetLevel = Restore;}

			ObjZONEram[CurrentZone].InMode = KeySetMode_TOGGLINGVAL;
		}
		else //InMode = KeySetMode_TOGGLINGVAL
		{
			if(ObjZONEram[CurrentZone].SetLevel == Restore) 		
				{ObjZONEram[CurrentZone].SetLevel = Off100p;}
			else if (ObjZONEram[CurrentZone].SetLevel == Off100p)	
				{ObjZONEram[CurrentZone].SetLevel = Restore;}

			ObjZONEram[CurrentZone].InMode = KeySetMode_TOGGLINGVAL;
		}
	}
	void _parsingB(byte CurrentZone)
	{
		ObjZONEram[CurrentZone].SetLevel = ON100p;				
		ObjZONEram[CurrentZone].InMode = KeySetMode_MAXVAL;		//Deja en modo MAXVAL	
	}
	void _parsingC(byte CurrentZone)
	{
		GettingReadyForNewLevelOfDC_Zone(CurrentZone);					//Prepara todos los valores
		//
		__Parsing_UpdateBarZone_AccodingToTheFeatures(CurrentZone);

		if (ObjZONEram[CurrentZone].uCommonProcess.bfCommonProcess._PRINT_PORCENT_OF_DC_LEVEL_)	//add flag
		{__Parsing_PrintPorcentOfDCLevelZone_AccodingToTheFeatures(CurrentZone);}
		//
		UpdatingDCofZone_AccodingToTheFeatures(CurrentZone);			//Ejecuta
	}
	/////////////////////////////////////////////////////////////////////
	byte AnyZone_IsGreaterThan_Off100p(void)
	{
		byte i;
		for (i=0; i<NUM_ZONAS; i++)
				{if (ObjZONEram[i].SetLevel != Off100p)	{return 1;}	}			
		return 0;
	}
	
	/***************************************************************************************
	Se ingresa con todo fading finalizado.			
	***************************************************************************************/
	byte MenuDimming6Zonas(void)
	{
		//byte CurrentZone;	
		byte i;
		
		//==1 Toma los valores actuales de la escena actual ObjSCENEram.CurrentScene
		for (i=0; i<NUM_ZONAS; i++)
		{
			ObjZONEram[i].DutyCycleToRestore = EEPROM_ReadWord( (const word *)&ObjStorSCENEeep[ObjSCENEram.CurrentScene].vDutyCycleAllZone[i] );	
		}
		
		for (i=0; i<NUM_ZONAS; i++)//Si la zona fue grabado con <= 0% (Or threshold), dejar x sgte.touch, 
		{
			if (ObjZONEram[i].DutyCycleToRestore <= 0)	//maybe it can be a THRESHOLD!!!!
				 {ObjZONEram[i].DutyCycleToRestore = (NUM_ELEM_DENTRO_BAR*FACTOR_ESCALA_DIMMING);}
		}		
		for (i=0; i<NUM_ZONAS; i++)
			{_MarkLevelTo_KeySetMode_TOGGLINGVAL(i);}
		//==
		
		//ObjBlink_CaptionOfBarZone_InitAllCounterTimer();	//Esto debe ser parte de la inicialización de todo el sistema
	
		//	
		CurrentZone = 0;
		ShowCurrentStatusOfZone(CurrentZone);		
		//
		byte scheduler_main = 0;
		byte iKey;
		
		SettKb_Dimming6Zones();
		
		Schedule_MenuDimming6Zonas = 0;	
		
		MD6Z_FLAGS.EncDesSynch = _DESENCLAVAR_SYNCHRONIZMO_ALL_ZONE_;	
		
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

					if ( HandlerSections( _KTE_BLINK_GO2RIGHT_, KB_iKEY4 ) )//;	//avanza hacia la derecha.
					{
						return 1;
					}
					
					//KB_KEY4_HasBeenRead();
					//PlaySound(0);
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
						ObjZONEram[CurrentZone].uCommonProcess.bfCommonProcess._PRINT_PORCENT_OF_DC_LEVEL_ = ON;
						_PreEx_DimmingUp(CurrentZone);	
					}					
					else
					{	
						for (i=0; i<NUM_ZONAS; i++)
						{
							ObjZONEram[i].uCommonProcess.bfCommonProcess._PRINT_PORCENT_OF_DC_LEVEL_ = OFF;
							_PreEx_DimmingUp(i);
						}
					}					
					//
					KB_KEY1_HasBeenRead();
				}
				else if ( KB_KEY2_ReadyToRead() )
				{
					if (!MD6Z_FLAGS.EncDesSynch)
					{
						ObjZONEram[CurrentZone].uCommonProcess.bfCommonProcess._PRINT_PORCENT_OF_DC_LEVEL_ = ON;
						//
						_PreEx_DimmingDown(CurrentZone);			
					}					
					else
					{	
						for (i=0; i<NUM_ZONAS; i++)
						{
							ObjZONEram[i].uCommonProcess.bfCommonProcess._PRINT_PORCENT_OF_DC_LEVEL_ = OFF;
							_PreEx_DimmingDown(i);
						}
					}					
					//
					KB_KEY2_HasBeenRead();
				}
				else if ( KB_KEY3_ReadyToRead() )
				{
					if (ObjKey[KB_iKEY3].bfSTATE.AtTimeExpired_BeforeOrAfter == KB_BEFORE_THR)
					{
						if (!MD6Z_FLAGS.EncDesSynch)
						{
							ObjZONEram[CurrentZone].uCommonProcess.bfCommonProcess._PRINT_PORCENT_OF_DC_LEVEL_ = ON;
							//
							_parsingA(CurrentZone);
							_parsingC(CurrentZone);
						}
						else //syncronizado con todos
						{
							if ( AnyZone_IsGreaterThan_Off100p() )
							{
								for (i=0; i<NUM_ZONAS; i++)
								{
									ObjZONEram[i].uCommonProcess.bfCommonProcess._PRINT_PORCENT_OF_DC_LEVEL_ = OFF;
									//
									//
									if (ObjZONEram[i].InMode == KeySetMode_MAXVAL)	
									{
										if (ObjZONEram[i].DutyCycleToRestore == (NUM_ELEM_DENTRO_BAR*FACTOR_ESCALA_DIMMING))
											{ObjZONEram[i].SetLevel = Off100p;}
										else
											{ObjZONEram[i].SetLevel = Restore;}

										ObjZONEram[i].InMode = KeySetMode_TOGGLINGVAL;
										_parsingC(i);
									}
									else //InMode = KeySetMode_TOGGLINGVAL
									{
										//recien en este punto sychronize all//Off all-> Synchronize from Off100p(ZERO)
										if(ObjZONEram[i].SetLevel == Restore) 	
										{										
											ObjZONEram[i].SetLevel = Off100p;
											
											ObjZONEram[i].InMode = KeySetMode_TOGGLINGVAL;
											////
											_parsingC(i);		//afecta solo a quien lo necesita
										}	
									}
								}
							}
							else 
							{
								//entra con todos las Zonas en 0% por AnyZone_IsGreaterThan_Off100p()
								for (i=0; i < NUM_ZONAS; i++)	
								{
									ObjZONEram[i].uCommonProcess.bfCommonProcess._PRINT_PORCENT_OF_DC_LEVEL_ = OFF;
									//
									//if (ObjZONEram[i].SetLevel == Off100p)	//seria redundar
										{ObjZONEram[i].SetLevel = Restore;}		//restore/ON 100%
									
									ObjZONEram[i].InMode = KeySetMode_TOGGLINGVAL;
									
									////
									_parsingC(i);
								}
							}
						}
					}
					else
					{
						//SE PUEDE APLICAR REPETITIBILIDAD!!!!
						//if (!ObjKey[KB_iKEY3].bfCTRLKey.Reptt)	//No Reptt
						//	ks0108Puts_P(PSTR("3b"));
						//else //Reptt
						//	ks0108Puts_P(PSTR("3br"));
						if (!MD6Z_FLAGS.EncDesSynch)
						{
							ObjZONEram[CurrentZone].uCommonProcess.bfCommonProcess._PRINT_PORCENT_OF_DC_LEVEL_ = ON;
							//
							_parsingB(CurrentZone);
							_parsingC(CurrentZone);
						}
						else //syncronizado con todos
						{
							for (i=0; i<NUM_ZONAS; i++)
							{
								ObjZONEram[i].uCommonProcess.bfCommonProcess._PRINT_PORCENT_OF_DC_LEVEL_ = OFF;
								//
								ObjZONEram[i].SetLevel = ON100p;
								ObjZONEram[i].InMode = KeySetMode_MAXVAL;		//Deja en modo MAXVAL
								////
								_parsingC(i);
							}
						}
					}
					
					PlaySound(0);
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
							if ( HandlerSections(_KTE_BLINK_GO2LEFT_, KB_iKEY1) )//es notificado como leido en HandlerSections(xxx,KB_iKEY1)
								{return 1;}
						}
						else	//bug fixed.
						{
							KB_KEY1_HasBeenRead(); 
							//PlaySound(0);
						}
					}

					if ( KB_KEY2_ReadyToRead() )
					{
						MD6Z_FLAGS.EncDesSynch = !MD6Z_FLAGS.EncDesSynch;	//Enclavamiento/desenclavamiento

						if (MD6Z_FLAGS.EncDesSynch == _ENCLAVAR_SYNCHRONIZMO_ALL_ZONE_)
						{
							ObjBlink_CaptionOfBarZone_BLINK_STOP_(CurrentZone);	//Stop current
							ObjBlink_CaptionOfBarZone_Blink_Run_All();			//Blink all
							_disable_section_Select_Current_Zone();	//Schedule_MenuDimming6Zonas > _SECTION_SELECT_CURRENT_ZONE_;//Disable section Select_Current_Zone
						}
						else
						{
							ObjBlink_CaptionOfBarZone_Blink_Stop_All();				//Stop all
							ObjBlink_CaptionOfBarZone_BLINK_RUN_(CurrentZone);		//Blink current
							_enable_section_Select_Current_Zone();	//Schedule_MenuDimming6Zonas == _SECTION_SELECT_CURRENT_ZONE_
							
							//Vuelve a mostrar su nombre
							ShowCurrentStatusOfZone(CurrentZone);
							//
						}
						
						KB_KEY2_HasBeenRead();	
						PlaySound(0);	
					}

					if ( KB_KEY3_ReadyToRead() )
					{
						//Todavia tengo una combinacion de tecla libre
						/*
						if (ObjKey[KB_iKEY3].bfSTATE.AtTimeExpired_BeforeOrAfter == KB_BEFORE_THR)
							ks0108Puts_P(PSTR("c3a")); 
						else
							
							if (!ObjKey[KB_iKEY3].bfCTRLKey.Reptt)	//No Reptt
								ks0108Puts_P(PSTR("c3b")); 
							else //Reptt
								ks0108Puts_P(PSTR("c3br")); 
						
						PlaySound(0);		
						*/
						KB_KEY3_HasBeenRead();	
						
					}		
				}
				else
					{scheduler_main = 3;} 
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
			
			//..........................................
			if (MD6Z_FLAGS.InitBlinkCaptionZone)
			{	
				MD6Z_FLAGS.InitBlinkCaptionZone=0;
				ObjBlink_Timming_CaptionOfBarZone();
			}
			//..........................................
			PeriodicCall_Thread_FadingProcess_AllZone();
			//..........................................
		}
	}	

	/***********************************************************************
	***********************************************************************/
	inline void ObjBlink_CaptionOfBarZone_BlinkDirection(byte CurrentZone, signed char KTE_RL)
	{
		ObjBlink_CaptionOfBarZone_BLINK_STOP_(CurrentZone + KTE_RL);	//KTE_Right Or Left
		ObjBlink_CaptionOfBarZone_BLINK_RUN_(CurrentZone);				//ObjBlink_CaptionOfBarZone[CurrentZone].bfBlink.RunStop=_BLINK_RUN_;
	}
	
	/***********************************************************************
	***********************************************************************/
	byte HandlerSections(signed char BLINK_RIGHT_LEFT, byte _KB_iKEYx_)
	{
		PlaySound(0);	//x q el usuario por cada toque, automaticamente sienta que su orden es procesada al instante
		
		if (Schedule_MenuDimming6Zonas == _SECTION_SELECT_CURRENT_ZONE_)	//ESTE TENDRIA Q ESTAR A 0 PARA Q PARE UN BLINK
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
				ClearOnlyRegionForFindAndPrintNameOfZone();
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
//			ObjKey[_KB_iKEYx_].bfSTATE.ReadyToRead = KB_CLEAR_READYTOREAD_INAPP;
//			PlaySound(0);
			//
		}
		
		//PlaySound(0);	//Es cambiado al inicio para mejorar la experencia de usuario
		ObjKey[_KB_iKEYx_].bfSTATE.ReadyToRead = KB_CLEAR_READYTOREAD_INAPP;
		

		//________________________________________________________			
		if (Schedule_MenuDimming6Zonas == 1)
		{
			if (MD6Z_FLAGS.EncDesSynch)
			{
				ObjBlink_CaptionOfBarZone_Blink_Stop_All();
			}			
			
			if (DIMMING_FLAGS.TIMER0_IsActiveFading)
			{
				MessageBox(128,32);				//Splash message!
				Schedule_MenuDimming6Zonas+=1;
			}
			else
				{Schedule_MenuDimming6Zonas+=2;}
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
			
			
			//ESPERAR QUE TECLADO ESTE LIBRE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			SettKb_Dimming6Zones();
			
			Schedule_MenuDimming6Zonas++;
		}
		//________________________________________________________	
		if (Schedule_MenuDimming6Zonas == 4)
		{
			if ( ReturnToMenuPadre_Dimming6Zonas() )
			{
				return 1;
			}
				
			//Schedule_MenuDimming6Zonas = 0; //BUG. FIXED
			
			//==>
			if (!MD6Z_FLAGS.EncDesSynch)
			{
				CurrentZone = 0;								//iniciar nueva cuenta en CurrentZone
				ShowCurrentStatusOfZone(CurrentZone);			//Re-blink through this function
			
				_enable_section_Select_Current_Zone();			//Schedule_MenuDimming6Zonas = _SECTION_SELECT_CURRENT_ZONE_	
			}
			else
			{
				ObjBlink_CaptionOfBarZone_Blink_Run_All();		//re-Blink all	
				_disable_section_Select_Current_Zone();			//Schedule_MenuDimming6Zonas > _SECTION_SELECT_CURRENT_ZONE_;//Disable section Select_Current_Zone
			}
			//==>
			
		}
		
		SettKb_Dimming6Zones();									//restablece configuracion de teclado
		//________________________________________________________
		return 0;
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
					PlaySound(0);
					ScroolingCHIP1up_CHIP2down_CHIP3up();
				return 1;   
            }

            if ( KB_KEY4_ReadyToRead() )
            {
					KB_KEY4_HasBeenRead();
					PlaySound(0);
					//
					ScroolingZ_CHIP1();
					//ClearAllPixel_LessTheBorder_CHIP1();	//limpia chip1
					ks0108FillRect(1,10,61,28,WHITE);				//clear - parte superior
					ks0108FillRect(1,47,61,0x0D+2,WHITE);			//clear - parte inferior
				
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
				//cada 5ms es comprado en main-line
				MD6Z_FLAGS.InitBlinkCaptionZone = 1;
			//}
	}
	/**************************************************************************************
	**************************************************************************************/
	//void ShowSetLevelInGLCD(byte CurrentZone)	
	//{
		//__Parsing_UpdateBarZone_AccodingToTheFeatures(CurrentZone);
		//__Parsing_PrintPorcentOfDCLevelZone_AccodingToTheFeatures(CurrentZone);
	//}
	
