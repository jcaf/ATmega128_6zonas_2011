/*
 * KeyboardAPI_1.c
 *
 * Created: 12/11/2012 01:26:35 p.m.
 *  Author: JCaf
 */ 
#include "Includes/InitializeAllModules.h"	

	///////////////////////////////////////////////////////////////////////////
	//Procesos comunes a nivel de aplicacion
	//add. 3 oct 2012:
	//After clean, todavia falta asegurar q los procesos de todas las teclas
	//has been finished, esto sera en el siguiente +5ms de interrupcion
	///////////////////////////////////////////////////////////////////////////
/*
	BOOL KB_API_if_allreleased_clearReadyToRead(void)//no reentrant - application thread
	{
		byte i;
		if ( objsharedfeatkeys.bfSHARED.AllKeysReleased )
		{
			for (i=0; i<KB_TOTALOFKEYS; i++)		//All-Clear states
			{
				objkey[i].bfSTATE.ReadyToRead = KB_CLEAR_READYTOREAD_INAPP;
				objkey[i].bfSTATE.AtTimeExpired_BeforeOrAfter = 0;
			}
			return 1;
		}
		else
			{return 0;}
	}
*/
	///////////////////////////////////////////////////////////////////////////////////////////////////
	//DIRECT & PUSH usan realmente la direccion senialada
	//POP-> __dummy, pues there is not required by the operation
	///////////////////////////////////////////////////////////////////////////////////////////////////
	_STACK_MODE synch_change_layout_kb(_STACK_MODE stack_mode, struct _key_properties * p_key_properties)
	{
		synch_kb_exposed_to_app.key_change_layout.stack_mode = stack_mode;
		synch_kb_exposed_to_app.key_change_layout.p_key_properties = p_key_properties;
		kbhandler_app.scheduler = (KEYMIXSTATES)INHIBITED__CHANGE_LAYOUT_KB;
		
		return stack_mode;
	}
	

