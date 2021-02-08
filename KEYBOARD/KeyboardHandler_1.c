/*
 * KeyboardHandler_1.c
 *
 * Created: 16/02/2012 09:11:55 p.m.
 *  Author: jcaf
 */ 
#include "Includes/InitializeAllModules.h"	

#ifdef _KEYBOARD_HANDLER_	

	volatile struct _ObjKey objkey[KB_TOTALOFKEYS];//=
	//{
		//[0].key_properties.u.bf.OnKeyPressed = 1,
		//[0].key_properties.u.bf.OnKeyPressedAndKeyRelease = 0,
		//[0].key_properties.u.bf.AtTimeExpired = 0,
		//[0].key_properties.u.bf.Reptt = 0,
		//[0].key_properties.group_autoexcluding = 1,
		//
		//[1].key_properties.u.bf.OnKeyPressed = 1,
		//[1].key_properties.u.bf.OnKeyPressedAndKeyRelease = 0,
		//[1].key_properties.u.bf.AtTimeExpired = 0,
		//[1].key_properties.u.bf.Reptt = 0,
		//[1].key_properties.group_autoexcluding = 1,
		//
		//[2].key_properties.u.bf.OnKeyPressed = 0,
		//[2].key_properties.u.bf.OnKeyPressedAndKeyRelease = 0,
		//[2].key_properties.u.bf.AtTimeExpired = 1,
		//[2].key_properties.u.bf.Reptt = 0,
		//[2].key_properties.group_autoexcluding = 1,
		//
		//[3].key_properties.u.bf.OnKeyPressed = 0,
		//[3].key_properties.u.bf.OnKeyPressedAndKeyRelease = 0,
		//[3].key_properties.u.bf.AtTimeExpired = 1,
		//[3].key_properties.u.bf.Reptt = 0,
		//[3].key_properties.group_autoexcluding = _NO_AGRUPADO_AUTOEXCLUDING_,
	//};
	
	volatile struct _objsharedfeatkeys objsharedfeatkeys=
	{
		.TriggerRepttGlobal = _KTE_TRIGGER_REPPT_500ms_,
		.HoldingRepttGlobal = 50/5	//expresados en *ms ->cada 5ms*10 = 50ms
		
	};	//x shared features 
	
	static volatile struct _key_change_layout
	{
		//stack
		byte stack_index;

		struct _stack_key_change_layout
		{
			struct _key_properties key_properties[KB_TOTALOFKEYS];
			
		}stack[KEY_CHANGE_LAYOUT__STACK_DEEP];//profundidad stack software
		
		byte sm0;

	}key_change_layout;

	static volatile struct _synch_kb
	{
		byte kb_free_and_complete_ps_sm0;
	}synch_kb;
	
	volatile struct _synch_kb_exposed_to_app synch_kb_exposed_to_app;
	
	///////////////////////////////////////////////////////////////////////////
	void InitKeyboard(void)
	{	
		KB_PULLUP_ON_KEY_1_();
		ConfigInputPin(DDRxKB_KEY_1,KB_pinKEY_1);
		
		KB_PULLUP_ON_KEY_2_();
		ConfigInputPin(DDRxKB_KEY_2,KB_pinKEY_2);
		
		KB_PULLUP_ON_KEY_3_();
		ConfigInputPin(DDRxKB_KEY_3,KB_pinKEY_3);
		
		KB_PULLUP_ON_KEY_4_();
		ConfigInputPin(DDRxKB_KEY_4,KB_pinKEY_4);
	}
	
	///////////////////////////////////////////////////////////////////////////
	static void ReadCurrentValueFromKEYS_SortPredefined(void)
	{
		objkey[0].bfSTATE.Pin = _INTRO_BIT_FROM_PINREAD_AT_POSC_KEY_1_;
		objkey[1].bfSTATE.Pin = _INTRO_BIT_FROM_PINREAD_AT_POSC_KEY_2_;
		objkey[2].bfSTATE.Pin = _INTRO_BIT_FROM_PINREAD_AT_POSC_KEY_3_;
		objkey[3].bfSTATE.Pin = _INTRO_BIT_FROM_PINREAD_AT_POSC_KEY_4_;
	}
	
	///////////////////////////////////////////////////////////////////////////
	#define _KB_KEY_HANDLED_AS_PRESSED_ 	(0)	//hardware conexion
	#define _KB_KEY_HANDLED_AS_RELEASED_ 	(1)	//hardware conexion
	
	#define _KTE_TIME_DEBOUNCE_EXPIRED_		(5)//(4)	//5x4=20mS

	static void ScanKeys_DebounceFilter(void)
	{
		byte ikey;
		
		for (ikey=0; ikey<KB_TOTALOFKEYS; ikey++)
		{
			if (objkey[ikey].smPinState ==0)
			{
				if (objkey[ikey].bfSTATE.Pin == _KB_KEY_HANDLED_AS_PRESSED_)
					objkey[ikey].smPinState++;	
			}
			else if (objkey[ikey].smPinState ==1)
			{
				if (++objkey[ikey].CountDebounce >= _KTE_TIME_DEBOUNCE_EXPIRED_ )
				{
					objkey[ikey].CountDebounce =0;
					
					if (objkey[ikey].bfSTATE.Pin == _KB_KEY_HANDLED_AS_RELEASED_)
						objkey[ikey].smPinState--;	//was noise
					else
					{
						objkey[ikey].bfSTATE.StableState = KB_KEY_PRESSED;
						objkey[ikey].smPinState++;
					}
				}
			}
			else if (objkey[ikey].smPinState ==2)
			{
				if (objkey[ikey].bfSTATE.Pin == _KB_KEY_HANDLED_AS_RELEASED_)
					objkey[ikey].smPinState++;									
			}
			else if (objkey[ikey].smPinState ==3)
			{
				if (++objkey[ikey].CountDebounce >= _KTE_TIME_DEBOUNCE_EXPIRED_ )
				{
					objkey[ikey].CountDebounce =0;
					
					if (objkey[ikey].bfSTATE.Pin == _KB_KEY_HANDLED_AS_PRESSED_)
						objkey[ikey].smPinState--;
					else
					{
						objkey[ikey].bfSTATE.StableState = KB_KEY_RELEASED;
						objkey[ikey].smPinState = 0;
					}
				}
			}				
		}		
	}

	#define _GROUP_LOCKED_		(1)
	#define _GROUP_UNLOCKED_	(0)
	//#define _NO_AGRUPADO_AUTOEXCLUDING_ (0)
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	static BOOL IsKeyAccesible(byte ikey)
	{
		if (objkey[ikey].key_properties.group_autoexcluding > _NO_AGRUPADO_AUTOEXCLUDING_)	//esta agrupado ?
		{	
			if (objsharedfeatkeys.vgroup_autoexcluding[objkey[ikey].key_properties.group_autoexcluding] == _GROUP_LOCKED_)
			{	
				if ( !objkey[ikey].bfSTATE.OwnerOfGroup)	//Si no es quien gano la propiedad...
					{return FALSE;}		
			}
		}		
		return TRUE;
	}		
	///////////////////////////////////////////////////////////////////////////
	#define _STAGE_START_PARSING_			(0)
	#define _STAGE_ISKEY_RELEASED_			(1)
	#define _STAGE_ISKEY_READFROMAPP_		(2)
	#define _STAGE_FIREATIMEEXPIRED_		(3)
	#define _STAGE_PRESSEDANDKEYRELEASE_	(4)
	
	//Reptt deben ser contiguos!
	#define _STAGE_REPTT_					(5)
    #define _STAGE_REPTT_1_					(6)
    #define _STAGE_REPTT_2_					(7)
	//	
	#define _STAGE_END_PARSING_				(8)
	
	static void ParsingPropKey(void)
	{
		byte ikey;
		
		for (ikey=0; ikey<KB_TOTALOFKEYS; ikey++)
		{       
            if ( objkey[ikey].smParsingProp == _STAGE_START_PARSING_ )
			{        
				if ( IsKeyAccesible(ikey) )
				{
					if (objkey[ikey].bfSTATE.StableState == 1)
					{
						//........................................................
						if (objkey[ikey].key_properties.u.bf.OnKeyPressed)
						{
							objkey[ikey].bfSTATE.ReadyToRead = KB_SET_READYTOREAD_INAPP;	//Populate Key to app.
			
							if (objkey[ikey].key_properties.u.bf.Reptt)
								{objkey[ikey].smParsingProp = _STAGE_REPTT_;}
							else
								{objkey[ikey].smParsingProp = _STAGE_ISKEY_RELEASED_;}
						}
						else if ( objkey[ikey].key_properties.u.bf.OnKeyPressedAndKeyRelease)
                            {objkey[ikey].smParsingProp = _STAGE_PRESSEDANDKEYRELEASE_;}
						
						else if (objkey[ikey].key_properties.u.bf.AtTimeExpired)
							{objkey[ikey].smParsingProp = _STAGE_FIREATIMEEXPIRED_;}
						
						//Add++
						objkey[ikey].bfSTATE.InProcessing = 1;
						//++
						
						//........................................................
						
						if (objkey[ikey].key_properties.group_autoexcluding > _NO_AGRUPADO_AUTOEXCLUDING_)
						{
							objsharedfeatkeys.vgroup_autoexcluding[ objkey[ikey].key_properties.group_autoexcluding ] = _GROUP_LOCKED_;
							objkey[ikey].bfSTATE.OwnerOfGroup = 1;
						}
						//........................................................
					}
				}
			}
			
            //_________________________________________________________________________________________
				//comprueba entre las pasadas de repeticion/no repeticion si se ha soltado la tecla
				if ( (objkey[ikey].smParsingProp >= _STAGE_REPTT_ ) && (objkey[ikey].smParsingProp <= _STAGE_REPTT_2_))
				{
					if (!objkey[ikey].bfSTATE.StableState)			//ya solto?
					{
						objkey[ikey].CounterKeeper = 0;				//stop timmer
						
						objkey[ikey].smParsingProp = _STAGE_ISKEY_READFROMAPP_;
					}
				}
            //.............................................................................
			if (objkey[ikey].smParsingProp == _STAGE_REPTT_ )	
			{
                if ( ++objkey[ikey].CounterKeeper >= objsharedfeatkeys.TriggerRepttGlobal)
                {       objkey[ikey].CounterKeeper =0;

                        objkey[ikey].smParsingProp = _STAGE_REPTT_1_;
                }
			}
            if (objkey[ikey].smParsingProp == _STAGE_REPTT_1_)	//ping-pong between 1<->2
            {
                if (objkey[ikey].bfSTATE.ReadyToRead == KB_CLEAR_READYTOREAD_INAPP)				//ya leyo?
                {    objkey[ikey].bfSTATE.ReadyToRead = KB_SET_READYTOREAD_INAPP;				//Repopulate again
                    objkey[ikey].smParsingProp = _STAGE_REPTT_2_;
                }
            }
            if (objkey[ikey].smParsingProp == _STAGE_REPTT_2_)	//ping-pong 2<->1
            {
                if ( ++objkey[ikey].CounterKeeper >= objsharedfeatkeys.HoldingRepttGlobal)
                {      objkey[ikey].CounterKeeper = 0;
                    objkey[ikey].smParsingProp = _STAGE_REPTT_1_;
                }
            }
            //_________________________________________________________________________________________
			if (objkey[ikey].smParsingProp == _STAGE_PRESSEDANDKEYRELEASE_ )
			{
				if (!objkey[ikey].bfSTATE.StableState)	//ya solto?
				{
					objkey[ikey].bfSTATE.ReadyToRead = KB_SET_READYTOREAD_INAPP;							//Populate Key to app.
					objkey[ikey].smParsingProp = _STAGE_ISKEY_READFROMAPP_;		//esperar x leer
				}						
			}			
			//_________________________________________________________________________________________
			if (objkey[ikey].smParsingProp == _STAGE_FIREATIMEEXPIRED_ )        
			{
				//objkey[ikey].CountAtTimeExpired++;
				objkey[ikey].CounterKeeper++;
				
				if (!objkey[ikey].bfSTATE.StableState)	//ya solto?
				{
					//if (objkey[ikey].CountAtTimeExpired <= (_FIRE_AT_TIME_THRESHOLD_) )
					//{	objkey[ikey].CountAtTimeExpired	= 0;            
					if (objkey[ikey].CounterKeeper <= (_FIRE_AT_TIME_THRESHOLD_) )	//USANDO UN SOLO CONTADOR, 
					{	objkey[ikey].CounterKeeper	= 0;							//PUES SE USA EN TIEMPOS DIFERENTES            

						objkey[ikey].bfSTATE.ReadyToRead = KB_SET_READYTOREAD_INAPP;					
						objkey[ikey].bfSTATE.AtTimeExpired_BeforeOrAfter = KB_BEFORE_THR;	
						
						objkey[ikey].smParsingProp = _STAGE_ISKEY_READFROMAPP_;		//Go directly to wait for read key from high-level application
					}
				}
				//
				//if (objkey[ikey].CountAtTimeExpired > (_FIRE_AT_TIME_THRESHOLD_) )
				//{	objkey[ikey].CountAtTimeExpired = 0;          
				if (objkey[ikey].CounterKeeper > (_FIRE_AT_TIME_THRESHOLD_) )
				{	objkey[ikey].CounterKeeper = 0x0000;       					      

					objkey[ikey].bfSTATE.ReadyToRead = KB_SET_READYTOREAD_INAPP;						
					objkey[ikey].bfSTATE.AtTimeExpired_BeforeOrAfter = KB_AFTER_THR;	//queda senializado

					if (!objkey[ikey].key_properties.u.bf.Reptt)							//x No Reptt
						{objkey[ikey].smParsingProp = _STAGE_ISKEY_RELEASED_;}	//wait for key is release
					else
						{objkey[ikey].smParsingProp = _STAGE_REPTT_2_;}
				}
			}				
			//_________________________________________________________________________________________
			if (objkey[ikey].smParsingProp == _STAGE_ISKEY_RELEASED_)		//MODO->FireOnKeyPressed + no Repetitibilidad 	//MODO->solo esperar que suelte
			{																//smOnKeyPressed_NOT_Repett
				if (objkey[ikey].bfSTATE.StableState == KB_KEY_RELEASED)						//ya solto?
					{objkey[ikey].smParsingProp = _STAGE_ISKEY_READFROMAPP_;}	//esperar x leer
			}			
			//_________________________________________________________________________________________
			if (objkey[ikey].smParsingProp == _STAGE_ISKEY_READFROMAPP_)
			{
				if (objkey[ikey].bfSTATE.ReadyToRead == KB_CLEAR_READYTOREAD_INAPP)	//ya leyo?
					{objkey[ikey].smParsingProp = _STAGE_END_PARSING_;}
			}
			//_________________________________________________________________________________________
			if (objkey[ikey].smParsingProp == _STAGE_END_PARSING_)
			{
				if (objkey[ikey].key_properties.group_autoexcluding > _NO_AGRUPADO_AUTOEXCLUDING_)	//forma grupo?
				{
					objsharedfeatkeys.vgroup_autoexcluding[objkey[ikey].key_properties.group_autoexcluding] = _GROUP_UNLOCKED_;
					objkey[ikey].bfSTATE.OwnerOfGroup = 0;
				}

				objkey[ikey].smParsingProp = _STAGE_START_PARSING_;
				
				//Add++
					objkey[ikey].bfSTATE.InProcessing = 0;
				//++
			}
		}				
	}

	///////////////////////////////////////////////////////////////////////////
	//ninguna tecla presionada 
	///////////////////////////////////////////////////////////////////////////
	static BOOL AllKeysReleased(void)
	{
		byte i;			
		for (i=0; i<KB_TOTALOFKEYS; i++)
		{
			if (objkey[i].bfSTATE.StableState == KB_KEY_PRESSED)
				{return FALSE;}
		}
		return TRUE;		
	}
	///////////////////////////////////////////////////////////////////////////
	//todos los eventos de tecla leidas -> all keys completed their current processes
	///////////////////////////////////////////////////////////////////////////

	static BOOL AllKeysCompletedProcessing(void)
	{
		byte i;		
		for (i=0; i<KB_TOTALOFKEYS; i++)
		{
			if (objkey[i].bfSTATE.InProcessing == 1)
				{return FALSE;}
		}
		return TRUE;
	}	
	
	///////////////////////////////////////////////////////////////////////////
	static BOOL KB_if_allreleased_clearReadyToRead(void)//no reentrant - interrupt thread
	{
		byte i;
		//if ( objsharedfeatkeys.bfSHARED.AllKeysReleased )
		if ( AllKeysReleased() )
		{
			for (i=0; i<KB_TOTALOFKEYS; i++)		//All-Clear states
			{
				//si hace falta limpiar flag
				if (objkey[i].bfSTATE.ReadyToRead == KB_SET_READYTOREAD_INAPP)//consistenciado
				{
					objkey[i].bfSTATE.ReadyToRead = KB_CLEAR_READYTOREAD_INAPP;
					objkey[i].bfSTATE.AtTimeExpired_BeforeOrAfter = 0;	
				}
				
			}
			return TRUE;
		}
		else
			{return FALSE;}
	}
	
	////////////////////////////////////////////////////////////////
	static BOOL kb_free_and_complete_ps(void)
	{
		if (synch_kb.kb_free_and_complete_ps_sm0 == 0)
		{
			if ( KB_if_allreleased_clearReadyToRead() )
				{synch_kb.kb_free_and_complete_ps_sm0++;}
		}

		if (synch_kb.kb_free_and_complete_ps_sm0 == 1)
		{
			//if ( objsharedfeatkeys.bfSHARED.AllKeysReleased )//double check //only for security
			if ( AllKeysReleased() )//double check //only for security
			{
				if (AllKeysCompletedProcessing() )//if (objsharedfeatkeys.bfSHARED.AllKeysCompleteProcesses )
				{
					synch_kb.kb_free_and_complete_ps_sm0 = 0x00;
					
					return TRUE;	//evoluciona statemachine de la funcion que llama
				}
			}
			else
				{synch_kb.kb_free_and_complete_ps_sm0 = 0x0;}
		}
		return FALSE;
	}

	////////////////////////////////////////////////////////////////
	static void KB_synch_kb_free_and_complete_ps(void)
	{
		if (synch_kb_exposed_to_app.synch_kb_free_and_complete_ps.synch_freecomplete_sm0 == 1)
		{
			if ( kb_free_and_complete_ps() )
			{
				synch_kb_exposed_to_app.synch_kb_free_and_complete_ps.synch_freecomplete_sm0++;
			}
		}
	}

	////////////////////////////////////////////////////////////////
	static void KB_change_layout_keyboard__push_stack(void)
	{
		byte i;
		for (i=0; i< KB_TOTALOFKEYS; i++)
		{
			key_change_layout.stack[key_change_layout.stack_index].key_properties[i].u._8b_key_properties = objkey[i].key_properties.u._8b_key_properties;
			key_change_layout.stack[key_change_layout.stack_index].key_properties[i].group_autoexcluding = objkey[i].key_properties.group_autoexcluding;
		}
		key_change_layout.stack_index++;
	}
	
	static void KB_change_layout_keyboard__pop_stack(void)
	{
		byte i;
		key_change_layout.stack_index--;
		for (i=0; i< KB_TOTALOFKEYS; i++)
		{
			objkey[i].key_properties.u._8b_key_properties = key_change_layout.stack[key_change_layout.stack_index].key_properties[i].u._8b_key_properties;
			objkey[i].key_properties.group_autoexcluding = key_change_layout.stack[key_change_layout.stack_index].key_properties[i].group_autoexcluding;
		}
	}

	static void KB_synch_change_layout_keyboard(void)
	{
		byte i;
	
		if (synch_kb_exposed_to_app.key_change_layout.change_sm0 == 1)
		{
			if (key_change_layout.sm0 == 0)
			{
				if ( kb_free_and_complete_ps() )
					{ key_change_layout.sm0++; }
			}	

			if (key_change_layout.sm0 == 1)
			{
				key_change_layout.sm0 = 0x00;
				//===================================
				
				if (synch_kb_exposed_to_app.key_change_layout.stack_mode == (_STACK_MODE)POP)	//(_STACK_MODE)PUSH
				{
					KB_change_layout_keyboard__pop_stack();
				}
				else
				{
					if (synch_kb_exposed_to_app.key_change_layout.stack_mode == (_STACK_MODE)PUSH)	//(_STACK_MODE)PUSH
					{	KB_change_layout_keyboard__push_stack();}	
					
					for (i=0; i< KB_TOTALOFKEYS; i++)
					{
						objkey[i].key_properties.u._8b_key_properties = synch_kb_exposed_to_app.key_change_layout.p_key_properties[i].u._8b_key_properties;
						objkey[i].key_properties.group_autoexcluding = synch_kb_exposed_to_app.key_change_layout.p_key_properties[i].group_autoexcluding;
					}	
				}

				//===================================
				synch_kb_exposed_to_app.key_change_layout.change_sm0++;//populate to application
			}
		}
	}

	///////////////////////////////////////////////////////////////////////////
	void KB_KeyboardProcess(void)
	{
		ReadCurrentValueFromKEYS_SortPredefined();
		ScanKeys_DebounceFilter();
		ParsingPropKey();
			
		//Synchronized-Processes:
		//objsharedfeatkeys.bfSHARED.AllKeysReleased = AllKeysReleased();
		//objsharedfeatkeys.bfSHARED.AllKeysCompleteProcesses = AllKeysCompletedProcessing();
			
		KB_synch_change_layout_keyboard();
		KB_synch_kb_free_and_complete_ps();
	}
		

	

#endif

