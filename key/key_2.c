/*
 * key_1.c
 *
 * Created: 10/7/2012 1:04:47 PM
 *  Author: JCaf
 
	Al desviarse hacia INHIBITED__CHANGE_LAYOUT_KB
 
 */ 
#include "Includes/InitializeAllModules.h"
	
	struct _kbhandler_app kbhandler_app;
	struct _key key[KB_TOTALOFKEYS];

	struct _stackfx stackfx;

	static void scheduling_keys(void);
	static void processing_keys1f(void);
	static void processing_keys2f(void);
	static void waitfor_kb_free_and_complete_ps(void);
	
static void _key4_keys1f(void);
	
	void kb_handler0(void)
	{	
							
		//<0
		if (kbhandler_app.scheduler == (KEYMIXSTATES)INHIBITED__CHANGE_LAYOUT_KB)//-2: State synchronized
		{
			if (synch_kb_exposed_to_app.key_change_layout.change_sm0 == 0)
			{
				synch_kb_exposed_to_app.key_change_layout.change_sm0++;	
			}
			//states 1 evaluated in interrupt//waiting for evolution
			if (synch_kb_exposed_to_app.key_change_layout.change_sm0 == 2)//in this point, key was free, push & change layout
			{
				synch_kb_exposed_to_app.key_change_layout.change_sm0 = 0x00;	
				kbhandler_app.scheduler = (KEYMIXSTATES)WAITFOR_KB_FREE_AND_COMPLETE_PS;
			}
		}

		if (kbhandler_app.scheduler == (KEYMIXSTATES)INHIBITED)//-1 Wait for a delay
		{
			
		}

		//>=0
		if (kbhandler_app.scheduler == (KEYMIXSTATES)SCHEDULING_KEYS)
			{scheduling_keys();}
        
		if (kbhandler_app.scheduler == (KEYMIXSTATES)PROCESSING_KEYS1FX)
			{processing_keys1f();}
        
		if (kbhandler_app.scheduler == (KEYMIXSTATES)PROCESSING_KEYS2FX)
			{processing_keys2f();}
		if (kbhandler_app.scheduler == (KEYMIXSTATES)WAITFOR_KB_FREE_AND_COMPLETE_PS)	//State synchronized
			{waitfor_kb_free_and_complete_ps();}	
	}	
	
	static void scheduling_keys(void)
	{
		if ( objkey[KB_iKEY4].bfSTATE.StableState == KB_KEY_RELEASED )
		{
			//dado la naturaleza de estas tres teclas q pertenecen a grupo-1 exclusivo, solo 1 se garantiza q se ejecuta
			
			if (objkey[KB_iKEY1].bfSTATE.InProcessing) {kbhandler_app.ikey=KB_iKEY1; kbhandler_app.scheduler = (KEYMIXSTATES)PROCESSING_KEYS1FX;return;}
			if (objkey[KB_iKEY2].bfSTATE.InProcessing) {kbhandler_app.ikey=KB_iKEY2; kbhandler_app.scheduler = (KEYMIXSTATES)PROCESSING_KEYS1FX;return;}
			if (objkey[KB_iKEY3].bfSTATE.InProcessing) {kbhandler_app.ikey=KB_iKEY3; kbhandler_app.scheduler = (KEYMIXSTATES)PROCESSING_KEYS1FX;return;}
		}

		//++++++++++++++++++++
		//SI LA LATENCIA ES MUCHA, PODRIA DARSE EL CASO Q KEY1->KEY3 ESTE SENIALIZADO, + KEY4 TAMBIEN SENIALIZADO, Y Q AUN SE MANTENGA PRESIONADO,
		//EN ESE CASOM SE EJECUTARIA KEY4(); Y LUEGO EL CASO PARA 2DA FUNCION, Y ESTO NO HABIA SIDO LO DESEADO, POR ESO Q ESTOY RESTRINGIENDO HACIA UNA SALIDA Q ESPERA
		//Q ASEGURE Q EL TECLADO ESTE APTO(LIMPIA Y SINCRONIZA) PARA OTRO PROCESO
		//++++++++++++++++++++++++
		if (KB_KEY4_ReadyToRead())	
		{
			//YA POPULARIZO! Y DEJO TIEMPO "_FIRE_AT_TIME_THRESHOLD_" PARA CUALQUIER COMBINACION DE TECLA, A pesar q es de la misma naturaleza
			//en este punto ya se senializo, y ahora no hay necesidad y por lo q deseo bloquear la posibilidad de combinacion despues de
			//haberse procesado este punto, se pone el scheduler a "(KEYMIXSTATES)WAITFOR_KB_FREE_AND_COMPLETE_PS" siempre y cuando no haya 
			//sido desviado por "(KEYMIXSTATES)INHIBITED"
			_key4_keys1f();//left KB_KEY4_HasBeenRead(); //YA NO! deja chance a que pueda producirse combinacion de tecla.	
			return;	
		}		
		//PODRIA DEJAR SI CHANCE A Q ANALICE EN SERIE SI EXISTE UNA COMBINACION Q ATENDER. MEJOR ES ESPERAR A Q SUELTE
		//esto es un estado de test mas que tiene tambien tiene q ser posible desviarlo
	
		//HASTA Q SE POPULARICE KEY4, LE DA TIEMPO AL USUARIO A Q PRESIONE LA TECLA PARA ACTIVAR 2DA FUNCION
		if (objkey[KB_iKEY4].bfSTATE.StableState == KB_KEY_PRESSED) 
		{
			if ((objkey[KB_iKEY1].bfSTATE.InProcessing)||(objkey[KB_iKEY2].bfSTATE.InProcessing)||(objkey[KB_iKEY3].bfSTATE.InProcessing))
			{
				kbhandler_app.scheduler = (KEYMIXSTATES)PROCESSING_KEYS2FX;
				
				//if (objkey[KB_iKEY4].bfCTRLKey.Reptt)		//stop Reptt si estuviera activo -> guardar/restaurar	
				//	{objkey[KB_iKEY4].bfSTATE.temp = objkey[KB_iKEY4].bfCTRLKey.Reptt;}
			}
		}
	}				
	//////////////////////////////////////////////////////
	//NO-2DA_Fn		//definitivamente entrarA hasta q se estabilice las "variables"
	//note: for this model, it is processed de this way
	
    int8_t glcd_isWakeup;
    static void processing_keys1f(void)
	{
		if (KB_KEY1_ReadyToRead())
		{
			KB_KEY1_HasBeenRead();
			ResetCounterTimmerForNewKeepingTimmingBLGLCD();	
            
            if (glcd_isWakeup)//Added 2021
            {
                glcd_isWakeup = 0;//Added 2021
            }
            else//Added 2021
            {
                key[KB_iKEY1]._1fmode();//2011
            }
			
		}
		else
		if (KB_KEY2_ReadyToRead())
		{	
			KB_KEY2_HasBeenRead();
			ResetCounterTimmerForNewKeepingTimmingBLGLCD();	
            
            if (glcd_isWakeup)//Added 2021
            {
                glcd_isWakeup = 0;//Added 2021
            }
            else
            {
                key[KB_iKEY2]._1fmode();//2011
            }
		}
		else 
		if (KB_KEY3_ReadyToRead())
		{
			KB_KEY3_HasBeenRead();
			ResetCounterTimmerForNewKeepingTimmingBLGLCD();	//BackLightGLCD reset-timming
            
            if (glcd_isWakeup)//2021
            {
                glcd_isWakeup = 0;//2021
            }
            else
            {
                //++-//2011
                if (objkey[KB_iKEY3].bfSTATE.AtTimeExpired_BeforeOrAfter == KB_BEFORE_THR)
                {	key[KB_iKEY3]._1fmode();	}	
                else 
                {	
                    //if (!objkey[KB_iKEY3].key_properties.u.bf.Reptt) 
                    //{}	
                        //else {}

                    key[KB_iKEY3]._1fmode_aft();
                }
                //--+
            }
		}
		
		//Tal vez fue cambiado por alguna funcion,
		if (kbhandler_app.scheduler > (KEYMIXSTATES)INHIBITED)	//Add.
		{
			//[primero espero a q suelte, luego a q haya leido -> scan nueva pulsacion-> InProcessing = 0]
			//espera hasta que se procese objkey[keymixps.ikey].bfSTATE.InProcessing = 0
			
			if (!objkey[kbhandler_app.ikey].bfSTATE.InProcessing)//esta tecla en particular! SI ES NECESARIO PARA DARLE TIEMPO A KEY3 A QUE SEA POPULATE HACIA LA APLICACION
				{kbhandler_app.scheduler = (KEYMIXSTATES)WAITFOR_KB_FREE_AND_COMPLETE_PS;}
					//YA NO ES NECESARIO EVALUAR si !objkey[kbhandler_app.ikey].bfSTATE.InProcessing PUES EL ESTATE "WAITFOR_KB_FREE_AND_COMPLETE_PS"
					//AHORA ESTA BIEN CONSISTENCIADO
			//ERROR: SI ES NECESARIO EVALUAR Q TERMINE DE PROCESARSE, PUES PARA TECLAS COMO LA "KEY3" Q DEMORAN EN SER POPULARIZADAS POR SU
			//NATURALEZA, SERIAN IGNORADAS YA Q PASARIAN A "WAITFOR_KB_FREE_AND_COMPLETE_PS" DIRECTAMENTE
		}
		
	}	
	
	//es directo, no necesita esperar
	static void _key4_keys1f(void)
	{
			//if (objkey[KB_iKEY4].bfSTATE.AtTimeExpired_BeforeOrAfter == KB_BEFORE_THR)	{}
			//else {	if (!objkey[KB_iKEY4].key_properties.u.bf.Reptt){}	else {}	}

        ResetCounterTimmerForNewKeepingTimmingBLGLCD();
        
        if (glcd_isWakeup)//2021
        {
            glcd_isWakeup = 0;//2021
        }
        else
        {
            //+--2011
            key[KB_iKEY4]._1fmode();

            KB_KEY4_HasBeenRead();

            //PARA LA NATURALEZA DE ESTA TECLA, NO PUEDE
            //ESPERARSE POR if (!objkey[kbhandler_app.ikey].bfSTATE.InProcessing)//esta tecla en particular
            //PUES JUSTAMENTE LE DA CHANCE A EJECUTAR LA COMBINARCION CORRESPONDIENTE, D
            //DEBE SER TRATADA DE MANERA INDEPENDIENTE... SACARLO!!!!!!
            if (kbhandler_app.scheduler > (KEYMIXSTATES)INHIBITED)	//Add.//Tal vez fue cambiado por alguna funcion,
                {kbhandler_app.scheduler = (KEYMIXSTATES)WAITFOR_KB_FREE_AND_COMPLETE_PS;}
            
            //--+
            
        }//2021
	}
	
	//////////////////////////////////////////////////////
	//2DA_Fn activa
	static void processing_keys2f(void)
	{	
		if (objkey[KB_iKEY4].bfSTATE.StableState == KB_KEY_PRESSED)	
		{
			ResetCounterTimmerForNewKeepingTimmingBLGLCD();			//while pressing kb4 resetting
             if (glcd_isWakeup)//2021
            {
                glcd_isWakeup = 0;//2021
            }
            else
            {
		
                //++--2011
                if (KB_KEY1_ReadyToRead())
                {
                    KB_KEY1_HasBeenRead();
                    key[KB_iKEY1]._2fmode();
                }
                //key1=key2=responden a OnKeyPressed //en cambio key3 responde hasta q suelte o //pasao un tiempo, 
                if (KB_KEY2_ReadyToRead())
                {
                    KB_KEY2_HasBeenRead();	
                    key[KB_iKEY2]._2fmode();
                }

                //if ( KB_KEY3_ReadyToRead() )
                if (objkey[KB_iKEY3].bfSTATE.InProcessing)  //salida sin clear-buffer
                {
                    KB_KEY3_HasBeenRead();
                    //no interesa antes o despues
                    //if (objkey[KB_iKEY3].bfSTATE.AtTimeExpired_BeforeOrAfter == KB_BEFORE_THR)	
                    //{}
                    //else
                    //{	if (!objkey[KB_iKEY3].key_properties.u.bf.Reptt)	
                        //{} 
                        //else 
                        //{}	
                    //}

                    key[KB_iKEY3]._2fmode();
                }		
                //--++
            }
		}
		else
			{kbhandler_app.scheduler = (KEYMIXSTATES)WAITFOR_KB_FREE_AND_COMPLETE_PS;}	
	}			
	//////////////////////////////////////////////////////
	//Primero, todos las teclas han sido soltadas-> segundo, limpia la condicion "ReadyToRead" para que sus
	//maquinas de estados se reseteen
	//////////////////////////////////////////////////////
	static void waitfor_kb_free_and_complete_ps(void)
	{
		if (synch_kb_exposed_to_app.synch_kb_free_and_complete_ps.synch_freecomplete_sm0 == 0)
		{
			synch_kb_exposed_to_app.synch_kb_free_and_complete_ps.synch_freecomplete_sm0++;
		}
		//synch_kb_exposed_to_app.synch_kb_free_and_complete_ps.synch_freecomplete_sm0 == 1 -> in interrupt
		
		if (synch_kb_exposed_to_app.synch_kb_free_and_complete_ps.synch_freecomplete_sm0 == 2)
		{
			synch_kb_exposed_to_app.synch_kb_free_and_complete_ps.synch_freecomplete_sm0 = 0x00;
			kbhandler_app.scheduler = (KEYMIXSTATES)SCHEDULING_KEYS;
		}
		
		ResetCounterTimmerForNewKeepingTimmingBLGLCD();
	}			
	
	///////////////////////////////////////////////////////////////////////////////////////////////
 	/////////////////////////////////////////////////////////////////////////////////////
	void change_operating_mode(
								PTRFXrVOID (*pvfx)[MAXNUM_MODE_BY_PS][KB_TOTALOFKEYS],
								byte operating_mode
	)
	{
		byte k;
		for (k=0; k<KB_TOTALOFKEYS; k++)
		{
			key[k]._1fmode		= pvfx[0][operating_mode][k];	//NORMAL OR BEFORE
			key[k]._1fmode_aft	= pvfx[1][operating_mode][k];	//ALWAYS AFTER
			key[k]._2fmode		= pvfx[2][operating_mode][k];	//NORMAL OR BEFORE
			key[k]._2fmode_aft	= pvfx[3][operating_mode][k];	//ALWAYS AFTER
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////
	void _save_address_fxs(byte level)
	{
		byte k;
		for (k=0;k<KB_TOTALOFKEYS;k++)
		{
			stackfx.level[level].key[k]._1fmode		= key[k]._1fmode;
			stackfx.level[level].key[k]._1fmode_aft	= key[k]._1fmode_aft;
			stackfx.level[level].key[k]._2fmode		= key[k]._2fmode;
			stackfx.level[level].key[k]._2fmode_aft	= key[k]._2fmode_aft;
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////
	void _restore_address_fxs(byte level)
	{
		byte k;
		for (k=0;k<KB_TOTALOFKEYS;k++)
		{
			key[k]._1fmode		= stackfx.level[level].key[k]._1fmode;
			key[k]._1fmode_aft	= stackfx.level[level].key[k]._1fmode_aft;
			key[k]._2fmode		= stackfx.level[level].key[k]._2fmode;
			key[k]._2fmode_aft	= stackfx.level[level].key[k]._2fmode_aft;
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////
	void push_address_fx(void)
	{
		_save_address_fxs(stackfx.sp);
		stackfx.sp++;
	}
	/////////////////////////////////////////////////////////////////////////////////////
	void pop_address_fx(void)
	{
		stackfx.sp--;
		_restore_address_fxs(stackfx.sp);
	}

	/////////////////////////////////////////////////////////////////////////////////////
	void DUMMYFX(void){return;}
