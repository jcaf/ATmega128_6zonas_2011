/*
 * DEBUG_TestKeyboard.c
 *
 * Created: 07/05/2012 06:02:22 p.m.
 *  Author: jcaf
 */ 
#include "Includes/InitializeAllModules.h"	

#ifdef _KEYBOARD_HANDLER_	
	#ifdef _DEBUG_KEYBOARD_HANDLER_
	/******************************************************************
	******************************************************************/
	void TestKeyboardHandler01_ONLY_BUZZER(void)	
	{
		//setting keyboard
		objkey[0].bfCTRLKey.OnKeyPressed  =1;
		objkey[0].bfCTRLKey.Reptt = 1;
		objkey[0].group_autoexcluding = 1;
		//.................................		
		objkey[1].bfCTRLKey.OnKeyPressed  =1;
		objkey[1].bfCTRLKey.Reptt = 1;
		objkey[1].group_autoexcluding = 1;
		//.................................
		objkey[2].bfCTRLKey.OnKeyPressed  =1;
		objkey[2].bfCTRLKey.Reptt = 1;
		objkey[2].group_autoexcluding = 1;
		//.................................		
		//objkey[3].CTRLKey.OnKeyPressed  =1;
		objkey[3].bfCTRLKey.AtTimeExpired=1;
		objkey[3].bfCTRLKey.Reptt = 1;
		
		//Acepting overriding
		objsharedfeatkeys.TriggerRepttGlobal = _KTE_TRIGGER_REPPT_500ms_;
		objsharedfeatkeys.HoldingRepttGlobal = 50/5;	//expresados en *ms ->cada 5ms*10 = 50ms
		
		while (1)		
		{
			if (objkey[0].bfSTATE.ReadyToRead)
			{
				//ks0108Puts_P(PSTR("1"));			
				
				objkey[0].bfSTATE.ReadyToRead=0;
				playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);					
			}
			
			if (objkey[1].bfSTATE.ReadyToRead)
			{
				//ks0108Puts_P(PSTR("2"));			
				
				objkey[1].bfSTATE.ReadyToRead=0;
				playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);					
			}
			
			if (objkey[2].bfSTATE.ReadyToRead)
			{
				//ks0108Puts_P(PSTR("3"));			
				
				objkey[2].bfSTATE.ReadyToRead=0;
				playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);					
			}

			
			if (objkey[3].bfSTATE.ReadyToRead)
			{
				//ks0108Puts_P(PSTR("4"));			
				if (objkey[3].bfSTATE.AtTimeExpired_BeforeOrAfter == KB_BEFORE_THR)
				{
					//ks0108Puts_P(PSTR("B"));			
				}
				else
				{
					//ks0108Puts_P(PSTR("A"));								
				}

				objkey[3].bfSTATE.ReadyToRead=0;
				playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);					
			}
		}
	}
	/******************************************************************
	******************************************************************/
	void TestKeyboardHandler01(void)	
	{
		//setting keyboard
		objkey[0].bfCTRLKey.OnKeyPressed  =1;
		objkey[0].bfCTRLKey.Reptt = 1;
		objkey[0].group_autoexcluding = 1;
		//.................................		
		objkey[1].bfCTRLKey.OnKeyPressed  =1;
		objkey[1].bfCTRLKey.Reptt = 1;
		objkey[1].group_autoexcluding = 1;
		//.................................
		objkey[2].bfCTRLKey.OnKeyPressed  =1;
		objkey[2].bfCTRLKey.Reptt = 1;
		objkey[2].group_autoexcluding = 2;
		//.................................		
		objkey[3].bfCTRLKey.OnKeyPressed  =1;
				//objkey[3].bfCTRLKey.AtTimeExpired=1;
		objkey[3].bfCTRLKey.Reptt = 1;
		objkey[3].group_autoexcluding = 2;
		
		//Acepting overriding
		objsharedfeatkeys.TriggerRepttGlobal = _KTE_TRIGGER_REPPT_500ms_;
		objsharedfeatkeys.HoldingRepttGlobal = 50/5;	//expresados en *ms ->cada 5ms*10 = 50ms

		ks0108GotoXY(1,1);
		
		while (1)		
		{
			if (objkey[0].bfSTATE.ReadyToRead)
			{
				ks0108Puts_P(PSTR("1"));			
				
				objkey[0].bfSTATE.ReadyToRead=0;
				playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);					
			}
			
			if (objkey[1].bfSTATE.ReadyToRead)
			{
				ks0108Puts_P(PSTR("2"));			
				
				objkey[1].bfSTATE.ReadyToRead=0;
				playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);					
			}
			
			if (objkey[2].bfSTATE.ReadyToRead)
			{
				ks0108Puts_P(PSTR("3"));			
				
				objkey[2].bfSTATE.ReadyToRead=0;
				playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);					
			}

			
			if (objkey[3].bfSTATE.ReadyToRead)
			{
				ks0108Puts_P(PSTR("4"));			
			/*	
				if (objkey[3].bfSTATE.AtTimeExpired_BeforeOrAfter == KB_BEFORE_THR)
				{
					ks0108Puts_P(PSTR("B"));			
				}
				else
				{
					ks0108Puts_P(PSTR("A"));								
				}
			*/
				objkey[3].bfSTATE.ReadyToRead=0;
				playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);					
			}
		}
	}
	
	/******************************************************************
	******************************************************************/
	void TestKeyboardHandler02(void)
	{
		ks0108SelectFont(SC, ks0108ReadFontData, BLACK);
		ks0108GotoXY(1,10);
		
		//__________________________________________________
		//setting keyboard
		objkey[KB_iKEY1].bfCTRLKey.OnKeyPressed  =1;
		objkey[KB_iKEY1].bfCTRLKey.Reptt = 1;
		objkey[KB_iKEY1].group_autoexcluding = 1;
		
		objkey[KB_iKEY2].bfCTRLKey.OnKeyPressed  =1;
		objkey[KB_iKEY2].bfCTRLKey.Reptt = 1;
		objkey[KB_iKEY2].group_autoexcluding = 1;
		
		objkey[KB_iKEY3].bfCTRLKey.AtTimeExpired  =1;
		objkey[KB_iKEY3].bfCTRLKey.Reptt = 1;
		objkey[KB_iKEY3].group_autoexcluding = 1;		
		
		//objkey[KB_iKEY4].CTRLKey.OnKeyPressed  =1;
		objkey[KB_iKEY4].bfCTRLKey.AtTimeExpired=1;
		objkey[KB_iKEY4].bfCTRLKey.Reptt = 0;//1;
		
		//Acepting overriding
		objsharedfeatkeys.TriggerRepttGlobal = _KTE_TRIGGER_REPPT_500ms_;
		objsharedfeatkeys.HoldingRepttGlobal = 50/5;	//expresados en *ms ->cada 5ms*10 = 50ms
		//__________________________________________________
		
		
		byte scheduler_main=0;
		byte iKey;

		while (1)
		{
			if (scheduler_main == 0)	
			{
				if (objkey[KB_iKEY4].bfSTATE.StableState == KB_KEY_RELEASED)
				{	
					//Captura al primero que aparezca, para inhibir a tecla de 2da-funcion
					
					if (objkey[KB_iKEY1].bfSTATE.InProcessing) {iKey = KB_iKEY1;scheduler_main = 1;}
					if (objkey[KB_iKEY2].bfSTATE.InProcessing) {iKey = KB_iKEY2;scheduler_main = 1;}
					if (objkey[KB_iKEY3].bfSTATE.InProcessing) {iKey = KB_iKEY3;scheduler_main = 1;}
				}
				//_____________________________________________________________________________________________
				if ( KB_KEY4_ReadyToRead() )	
				{
					if (objkey[KB_iKEY4].bfSTATE.AtTimeExpired_BeforeOrAfter == KB_BEFORE_THR)
						ks0108Puts_P(PSTR("B"));		//KB_KEY4_HasBeenRead();	//aqui mismo murio!
					else	
					{
						if (!objkey[KB_iKEY4].bfCTRLKey.Reptt)	//No Reptt
							ks0108Puts_P(PSTR("A"));	//KB_KEY4_HasBeenRead();	
						else //Reptt
							ks0108Puts_P(PSTR("Ar"));	//synchronize puede ser activado //KB_KEY4_HasBeenRead();	
					}
					KB_KEY4_HasBeenRead();	
				}										
				//_____________________________________________________________________________________________
				if (objkey[KB_iKEY4].bfSTATE.StableState == KB_KEY_PRESSED) //kEY4 Pressed
				{
					if ((objkey[KB_iKEY1].bfSTATE.InProcessing)||(objkey[KB_iKEY2].bfSTATE.InProcessing)||(objkey[KB_iKEY3].bfSTATE.InProcessing))
					{
						scheduler_main = 2;
						//objkey[KB_iKEY4].bfSTATE.temp = objkey[KB_iKEY4].bfCTRLKey.Reptt;//stop Reptt si estuviera activo -> guardar/restaurar
					}
				}
				
			}
			
			/*........................................................................................................
			si se suelta y nuevamente se presiona key1, la tecla seguiria ejecutando su correspondiente tarea...
			if (objkey[iKey].bfSTATE.StableState == KB_KEY_PRESSED)//se respeta la intencion del usuario, si suelta, 
			
			NOTA:	No es necesario el bloque if..else if..else if,,, KeyboardHandler.c ya es conciente de la restriccion
					al pertenecer dichas teclas a un GRUPO DE AUTO-EXCLUSION
					La presencia de dicho bloque if..else if ..else if es solo para que el codigo no pregunte en vano
					por los demas teclas que han sido excluidas.
			........................................................................................................*/	
			if (scheduler_main == 1)	//NO-2DA_Fn
			{
				if ( KB_KEY1_ReadyToRead() )
				{
					ks0108Puts_P(PSTR("1"));			
					KB_KEY1_HasBeenRead();
					//
					playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);	
				}
				else if ( KB_KEY2_ReadyToRead() )
				{
					ks0108Puts_P(PSTR("2"));			
					KB_KEY2_HasBeenRead();
					//
					playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);	
				}
				else if ( KB_KEY3_ReadyToRead() )
				{
					if (objkey[KB_iKEY3].bfSTATE.AtTimeExpired_BeforeOrAfter == KB_BEFORE_THR)
						ks0108Puts_P(PSTR("3a")); 
					else{
						if (!objkey[KB_iKEY3].bfCTRLKey.Reptt)	//No Reptt
							ks0108Puts_P(PSTR("3b")); 
						else //Reptt
							ks0108Puts_P(PSTR("3br")); 
					}						
					KB_KEY3_HasBeenRead();	
					playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);		
				}
				
				//_____________________________________
				if (!objkey[iKey].bfSTATE.InProcessing)
					{scheduler_main =3;}	
			}			
			
			/*........................................................................................................
			Aqui interesa que la tecla 2DAFn sea pulsada, no su procesamiento y caracteristicas			
			........................................................................................................*/	
			if (scheduler_main == 2)		//2DA_Fn activa
			{
				if (objkey[KB_iKEY4].bfSTATE.StableState == KB_KEY_PRESSED)	
				{
					if ( KB_KEY1_ReadyToRead() )
					{
						ks0108Puts_P(PSTR("c1")); 
						KB_KEY1_HasBeenRead(); 
						playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);	
					}
					if ( KB_KEY2_ReadyToRead() )
					{
						ks0108Puts_P(PSTR("c2")); 
						KB_KEY2_HasBeenRead();	
						playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);	
					}
					if ( KB_KEY3_ReadyToRead() )
					{
						if (objkey[KB_iKEY3].bfSTATE.AtTimeExpired_BeforeOrAfter == KB_BEFORE_THR)
							ks0108Puts_P(PSTR("c3a")); 
						else
							
							if (!objkey[KB_iKEY3].bfCTRLKey.Reptt)	//No Reptt
								ks0108Puts_P(PSTR("c3b")); 
							else //Reptt
								ks0108Puts_P(PSTR("c3br")); 

						KB_KEY3_HasBeenRead();	
						playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);		
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
				if ( objsharedfeatkeys.bfSHARED.AllKeysReleased )
				{
					for (iKey=0; iKey<KB_TOTALOFKEYS; iKey++)		//All-Clear states
					{
						objkey[iKey].bfSTATE.ReadyToRead = KB_CLEAR_READYTOREAD_INAPP;
						objkey[iKey].bfSTATE.AtTimeExpired_BeforeOrAfter = 0;
					}
					scheduler_main=0;
				}
			}
		}
	}
	
	
	#endif
#endif	