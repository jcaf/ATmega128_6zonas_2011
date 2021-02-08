/*
 * DEBUG_TestKeyboard.c
 *
 * Created: 07/05/2012 06:02:22 p.m.
 *  Author: jcaf
 */ 
#include "Includes/InitializeAllModules.h"	

//////////////////////////////////////////////////////
#ifdef _KEYBOARD_HANDLER_	
	#ifdef _DEBUG_KEYBOARD_HANDLER_
	
	/******************************************************************
	******************************************************************/
	void TestKeyboardHandler01(void)	
	{
		//setting keyboard
		ObjKey[0].bfCTRLKey.OnKeyPressed  =1;
		ObjKey[0].bfCTRLKey.Reptt = 1;
		ObjKey[0].bfCTRLKey.Group_AutoExcluding = 1;
		//.................................		
		ObjKey[1].bfCTRLKey.OnKeyPressed  =1;
		ObjKey[1].bfCTRLKey.Reptt = 1;
		ObjKey[1].bfCTRLKey.Group_AutoExcluding = 1;
		//.................................
		ObjKey[2].bfCTRLKey.OnKeyPressed  =1;
		ObjKey[2].bfCTRLKey.Reptt = 1;
		
		//.................................		
		//ObjKey[3].CTRLKey.OnKeyPressed  =1;
		ObjKey[3].bfCTRLKey.AtTimeExpired=1;
		ObjKey[3].bfCTRLKey.Reptt = 1;
		
		//Acepting overriding
		ObjSharedFeatKeys.TriggerRepttGlobal = _KTE_TRIGGER_REPPT_500ms_;
		ObjSharedFeatKeys.HoldingRepttGlobal = 50/5;	//expresados en *ms ->cada 5ms*10 = 50ms
		

		while (1)		
		{
			if (ObjKey[0].bfSTATE.ReadyToRead)
			{
				ks0108Puts_P(PSTR("1"));			
				
				ObjKey[0].bfSTATE.ReadyToRead=0;
				BUZZER_FLAGS.BUZZER_Triggered = 1;					
			}
			
			if (ObjKey[1].bfSTATE.ReadyToRead)
			{
				ks0108Puts_P(PSTR("2"));			
				
				ObjKey[1].bfSTATE.ReadyToRead=0;
				BUZZER_FLAGS.BUZZER_Triggered = 1;					
			}
			
			if (ObjKey[2].bfSTATE.ReadyToRead)
			{
				ks0108Puts_P(PSTR("3"));			
				
				ObjKey[2].bfSTATE.ReadyToRead=0;
				BUZZER_FLAGS.BUZZER_Triggered = 1;					
			}

			
			if (ObjKey[3].bfSTATE.ReadyToRead)
			{
				//ks0108Puts_P(PSTR("4"));			
				if (ObjKey[3].bfSTATE.AtTimeExpired_BeforeOrAfter == KB_BEFORE_THR)
				{
					ks0108Puts_P(PSTR("B"));			
				}
				else
				{
					ks0108Puts_P(PSTR("A"));								
				}

				ObjKey[3].bfSTATE.ReadyToRead=0;
				BUZZER_FLAGS.BUZZER_Triggered = 1;					
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
		ObjKey[KB_iKEY1].bfCTRLKey.OnKeyPressed  =1;
		ObjKey[KB_iKEY1].bfCTRLKey.Reptt = 1;
		ObjKey[KB_iKEY1].bfCTRLKey.Group_AutoExcluding = 1;
		
		ObjKey[KB_iKEY2].bfCTRLKey.OnKeyPressed  =1;
		ObjKey[KB_iKEY2].bfCTRLKey.Reptt = 1;
		ObjKey[KB_iKEY2].bfCTRLKey.Group_AutoExcluding = 1;
		
		ObjKey[KB_iKEY3].bfCTRLKey.OnKeyPressed  =1;
		ObjKey[KB_iKEY3].bfCTRLKey.Reptt = 1;
		ObjKey[KB_iKEY3].bfCTRLKey.Group_AutoExcluding = 1;		
		
		//ObjKey[KB_iKEY4].CTRLKey.OnKeyPressed  =1;
		ObjKey[KB_iKEY4].bfCTRLKey.AtTimeExpired=1;
		ObjKey[KB_iKEY4].bfCTRLKey.Reptt = 0;//1;
		
		//Acepting overriding
		ObjSharedFeatKeys.TriggerRepttGlobal = _KTE_TRIGGER_REPPT_500ms_;
		ObjSharedFeatKeys.HoldingRepttGlobal = 50/5;	//expresados en *ms ->cada 5ms*10 = 50ms
		//__________________________________________________
		
		
		byte scheduler_main=0;
		byte iKey;

		while (1)
		{
			if (scheduler_main == 0)	
			{
				//..............................................................................................
				if (ObjKey[KB_iKEY4].bfSTATE.StableState == KB_KEY_RELEASED)
				{	//Captura al primero que aparezca, para inhibir a tecla de 2da-funcion
					if (ObjKey[KB_iKEY1].bfSTATE.StableState==KB_KEY_PRESSED) {iKey = KB_iKEY1;scheduler_main = 1;}
					if (ObjKey[KB_iKEY2].bfSTATE.StableState==KB_KEY_PRESSED) {iKey = KB_iKEY2;scheduler_main = 1;}
					if (ObjKey[KB_iKEY3].bfSTATE.StableState==KB_KEY_PRESSED) {iKey = KB_iKEY3;scheduler_main = 1;}
				}
				//..............................................................................................
				if ( KB_KEY4_ReadyToRead() )	//cuando ya es temporizado evaluado internamente 
				{
					if (ObjKey[KB_iKEY4].bfSTATE.AtTimeExpired_BeforeOrAfter == KB_BEFORE_THR)
					{
						ks0108Puts_P(PSTR("B"));	
						//KB_KEY4_HasBeenRead();	//aqui mismo murio!
					}
					else	
					{
						if (!ObjKey[KB_iKEY4].bfCTRLKey.Reptt)	//No Reptt
						{
							ks0108Puts_P(PSTR("A"));	
							//KB_KEY4_HasBeenRead();	
						}
						else //Reptt
						{
							ks0108Puts_P(PSTR("R"));	//synchronize puede ser activado
							//KB_KEY4_HasBeenRead();	
						}
					}
					KB_KEY4_HasBeenRead();	
				}										
				//..............................................................................................
				if (ObjKey[KB_iKEY4].bfSTATE.StableState == KB_KEY_PRESSED) //kEY4 Pressed
				{
					if ((ObjKey[KB_iKEY1].bfSTATE.StableState == KB_KEY_PRESSED) ||
						(ObjKey[KB_iKEY2].bfSTATE.StableState == KB_KEY_PRESSED) ||
						(ObjKey[KB_iKEY3].bfSTATE.StableState == KB_KEY_PRESSED) )
						{
							scheduler_main = 2;
							
							//stop Reptt si estuviera activo -> guardar/restaurar
							//ObjKey[KB_iKEY4].bfSTATE.temp = ObjKey[KB_iKEY4].bfCTRLKey.Reptt;
						}
				}
				//..............................................................................................
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////
			if (scheduler_main == 1)	//NO-2DA_Fn
			{
					//si se suelta y nuevamente se presiona key1, la tecla seguiria ejecutando su correspondiente tarea...
					if (ObjKey[iKey].bfSTATE.StableState == KB_KEY_PRESSED)//se respeta la intencion del usuario, si suelta, 
					{
						if ( KB_KEY1_ReadyToRead() )
						{
							ks0108Puts_P(PSTR("1"));			
							KB_KEY1_HasBeenRead();
							//
							BUZZER_FLAGS.BUZZER_Triggered = 1;	
						}
						if ( KB_KEY2_ReadyToRead() )
						{
							ks0108Puts_P(PSTR("2"));			
							KB_KEY2_HasBeenRead();
							//
							BUZZER_FLAGS.BUZZER_Triggered = 1;	
						}
						if ( KB_KEY3_ReadyToRead() )
						{
							ks0108Puts_P(PSTR("3"));			
							KB_KEY3_HasBeenRead();
							//
							BUZZER_FLAGS.BUZZER_Triggered = 1;	
						}
					}	
					else
						{scheduler_sub1 = 3}	//la misma tecla se "mata", en el sentido que ya no es valido nuevamente
				}
				
			}			
			/////////////////////////////////////////////////////////////////////////////////////////////////
			if (scheduler_main==2)		//2DA_Fn activa
			{
				if (ObjKey[KB_iKEY4].bfSTATE.StableState == KB_KEY_PRESSED)
				{
					if ( KB_KEY1_ReadyToRead() )
					{
						ks0108Puts_P(PSTR("c1")); 
						KB_KEY1_HasBeenRead(); 
						BUZZER_FLAGS.BUZZER_Triggered = 1;	
					}
					if ( KB_KEY2_ReadyToRead() )
					{
						ks0108Puts_P(PSTR("c2")); 
						KB_KEY2_HasBeenRead();	
						BUZZER_FLAGS.BUZZER_Triggered = 1;	
					}
					if ( KB_KEY3_ReadyToRead() )
					{
						ks0108Puts_P(PSTR("c3")); 
						KB_KEY3_HasBeenRead();	
						BUZZER_FLAGS.BUZZER_Triggered = 1;	
					}		
				}
				else
					scheduler_main = 3;
			}		
			////////////////////////////////////////////////////////////////////////////////////////////
			if (scheduler_main == 3)
			{
				if ( ObjSharedFeatKeys.bfSHARED.AreAllKeysReleased )
				{
					scheduler_main=0;
					scheduler_sub1=0;
						
					for (byte i=0; i<KB_TOTALOFKEYS; i++)		//All-Clear states
					{
						ObjKey[i].bfSTATE.ReadyToRead = KB_CLEAR_READYTOREAD_INAPP;
						ObjKey[i].bfSTATE.AtTimeExpired_BeforeOrAfter = 0;
					//ObjKey[KB_iKEY4].bfCTRLKey.Reptt = ObjKey[KB_iKEY4].bfSTATE.temp;	//restore
					}
				}
			}					
	
		}//end while

	}
	
	
	#endif
#endif	