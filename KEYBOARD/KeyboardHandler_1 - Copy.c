/*
 * KeyboardHandler_1.c
 *
 * Created: 16/02/2012 09:11:55 p.m.
 *  Author: jcaf
 */ 
#include "Includes/InitializeAllModules.h"	

#ifdef _KEYBOARD_HANDLER_	
	
	
	static void ReadCurrentValueFromKEYS_SortPredefined(void);
	static void ScanKeys_DebounceFilter(void);
	static void KB_Parsing_GroupedKeys(void);
	static void KB_Parsing_IndependentKeys(void);
	static BOOL Parsing_IfexistIndptBitsInGroup(volatile byte CountNumIndependentBits);

	//void ClearOtherBitsInGroup(volatile byte NumElementoActual, volatile byte CountGroup);
	static void ModeFirePopulateKey(volatile byte * pv_smachine_x_group ,byte _iNumElemInVect_, byte _bit_shift_);
	
	static void TestTimmingAndRepetitibilidad(	volatile byte * pv_smachine_KeyX ,
												volatile byte * pv_smachine_Reptt,
												volatile byte * pv_CountKeepTimming,
												volatile byte _iNumElemInVect_,
												volatile byte _bit_shift_);

	static void FireAtTimeExpired(	volatile byte * pv_smachine_KeyX ,	 
									byte * pv_smachine_ModeShoot_FireAtTimeExpired,
									word * pv_Count_FireAtTimeExpired,
									byte _iNumElemInVect_, 				  
									byte _bit_shift_	);
	
	static volatile byte vReadCurrentValueKeys[_NUM_VECTS_X_READKEYS_];
	static volatile byte vOutDebounced[_NUM_VECTS_X_READKEYS_];
	//
	//volatile byte vScratch[_NUM_VECTS_X_READKEYS_];	//ANALIZAR SI NECESARIO?
	volatile byte vExposedToApp[_NUM_VECTS_X_READKEYS_];	
	
	volatile byte BitsQconfGrupo[_MAX_NUMERO_DE_GRUPOS_][_MAX_NUMERO_ELEM_EN_GRUPO_];
	volatile byte NumeroDeGruposFormados;
	
	//------------------------------------------------------------------------------
	//SECTION: ModeFirePopulateKey
	volatile byte vModeShoot_FireOnKeyPressed[_NUM_VECTS_X_READKEYS_];
	volatile byte vModeShoot_FireOnKeyPressedAndKeyRelease[_NUM_VECTS_X_READKEYS_];
	
	//
	volatile byte vModeShoot_FireAtTimeExpired[_NUM_VECTS_X_READKEYS_];
	volatile byte vModeShoot_FireAtTimeExpired_AssertedBefOrAfter[_NUM_VECTS_X_READKEYS_];
	//volatile word vModeShoot_FireAtTimeExpired_TimingThreshold[_NUM_VECTS_X_READKEYS_];//-> define x constant.

	//------------------------------------------------------------------------------
	//SECTION: Repetitibilidad
	volatile byte vModeTimmingReptt[_NUM_VECTS_X_READKEYS_];
	//usando variables globales que afectan a todas las teclas x reptt.
	volatile byte TriggerRepttGlobal = _KTE_TRIGGER_REPPT_500ms_;
	volatile byte HoldingRepttGlobal = _KTE_HOLDING_REPPT_100ms_;
	
	/******************************************************************
	
	******************************************************************/
	void InitKeyboard(void)
	{	
		byte i;
		
		KB_PULLUP_ON_KEY_1_();
		ConfigInputPin(DDRxKB_KEY_1,KB_pinKEY_1);
		
		KB_PULLUP_ON_KEY_2_();
		ConfigInputPin(DDRxKB_KEY_2,KB_pinKEY_2);
		
		KB_PULLUP_ON_KEY_3_();
		ConfigInputPin(DDRxKB_KEY_3,KB_pinKEY_3);
		
		KB_PULLUP_ON_KEY_4_();
		ConfigInputPin(DDRxKB_KEY_4,KB_pinKEY_4);
		
		for (i=0;i<_NUM_VECTS_X_READKEYS_;i++ ) 
		{
			vExposedToApp[i] = 0;	
		}		
	}
	/******************************************************************
	Podria agilizar usando macros x concatenar...
	******************************************************************/
	static void ReadCurrentValueFromKEYS_SortPredefined(void)
	{
		volatile byte i;
		
		for (i=0;i<_NUM_VECTS_X_READKEYS_;i++) vReadCurrentValueKeys[i]=0;	//Clear position in Vectors
	
		vReadCurrentValueKeys[0] = _INTRO_BIT_FROM_PINREAD_AT_POSC_KEY_1_<<0;	
		vReadCurrentValueKeys[0]|= _INTRO_BIT_FROM_PINREAD_AT_POSC_KEY_2_<<1;	
		vReadCurrentValueKeys[0]|= _INTRO_BIT_FROM_PINREAD_AT_POSC_KEY_3_<<2;	
		vReadCurrentValueKeys[0]|= _INTRO_BIT_FROM_PINREAD_AT_POSC_KEY_4_<<3;	
		//vReadCurrentValueKeys[0]|= _INTRO_BIT_FROM_PINREAD_AT_POSC_KEY_5_<<4;	
		//vReadCurrentValueKeys[0]|= _INTRO_BIT_FROM_PINREAD_AT_POSC_KEY_6_<<5;	
		//vReadCurrentValueKeys[0]|= _INTRO_BIT_FROM_PINREAD_AT_POSC_KEY_7_<<6;	
		//vReadCurrentValueKeys[0]|= _INTRO_BIT_FROM_PINREAD_AT_POSC_KEY_8_<<7;	
	}
	
	/******************************************************************
	Previamente a sido inicializado a 0 todos los elementos de v_smachine_ScanKeys[]
	
	******************************************************************/
	static void ScanKeys_DebounceFilter(void)
	{
		static volatile byte v_smachine_ScanKeys[NUM_KEYS_CONFORM_THE_KEYBORD];//={0};//todos los elemento inicializados a 0
		static volatile byte vCountDebounce[NUM_KEYS_CONFORM_THE_KEYBORD];//={0};
		volatile byte CountOfKeys;//=0;				//x cada bit dentro de un array, se avanza en su correspondiente state_machine

		volatile byte _iNumElemInVect_,_bit_shift_;	//x,y
		
		static volatile byte * pv_smachine_ScanKeys;
		
		for (CountOfKeys=0;CountOfKeys<NUM_KEYS_CONFORM_THE_KEYBORD;CountOfKeys++)
		{
			_iNumElemInVect_	= CountOfKeys >>3;			// div 8
			_bit_shift_ = CountOfKeys - (_BYTE_WIDTH_*_iNumElemInVect_);
			
			pv_smachine_ScanKeys = &v_smachine_ScanKeys[CountOfKeys];
			
			if (*pv_smachine_ScanKeys == 0)
			{
				if (!( vReadCurrentValueKeys[_iNumElemInVect_] & (1<<_bit_shift_))	)//tecla presionada?
				{
					(*pv_smachine_ScanKeys)++;	//avanza maquina
				}	
			}
			else if (*pv_smachine_ScanKeys  == 1)
			{
				if (++vCountDebounce[CountOfKeys] == _KTE_TIME_DEBOUNCE_EXPIRED_ )
				{
					vCountDebounce[CountOfKeys]=0;	//reset Count Debounce
						
					//volver a evaluar tecla en cuestión
					if ( vReadCurrentValueKeys[_iNumElemInVect_] & (1<<_bit_shift_))	//tecla no presionada?
					{
						*pv_smachine_ScanKeys  =0;	//reset state machine
					}
					else //Assert firmemente bit on Output-Vector 
					{
						BitTo1(vOutDebounced[_iNumElemInVect_],_bit_shift_);
						(*pv_smachine_ScanKeys)++;	//avanza vector
					}
				}
			}
			else if (*pv_smachine_ScanKeys  == 2)	//si solto?
			{
				if ( vReadCurrentValueKeys[_iNumElemInVect_] & (1<<_bit_shift_))
				{
					(*pv_smachine_ScanKeys)++;	//avanza maquina
				}	
			}				
			else if (*pv_smachine_ScanKeys  == 3)
			{
				if (++vCountDebounce[CountOfKeys] == _KTE_TIME_DEBOUNCE_EXPIRED_ )
				{
					vCountDebounce[CountOfKeys]=0;	//reset Count Debounce
						
					//volver a evaluar tecla en cuestión
					if (!( vReadCurrentValueKeys[_iNumElemInVect_] & (1<<_bit_shift_))	)	//aun presionada?
					{
						*pv_smachine_ScanKeys  =2;//fue ruido
					}
					else //Assert firmemente bit on Output-Vector 
					{
						BitTo0(vOutDebounced[_iNumElemInVect_],_bit_shift_);
						*pv_smachine_ScanKeys =0;	//Reset maquina
					}
				}
			}//end if..else..if				
		}//End for
	}//End fx


	//Variables for MODO-> FireOnKeyPressed + Repetitibilidad 
	static volatile byte v_smachine_Reptt[NUM_KEYS_CONFORM_THE_KEYBORD], *pv_smachine_Reptt;
	static volatile byte v_CountKeepTimming[NUM_KEYS_CONFORM_THE_KEYBORD], *pv_CountKeepTimming;

	//Variables for MODO-> FireOnKeyPressed + NOT Repetitibilidad 		
	static volatile byte v_smachine_FireOnKeyPressed_NOT_Repett[NUM_KEYS_CONFORM_THE_KEYBORD], *pv_smachine_FireOnKeyPressed_NOT_Repett;

	//Variables for MODO-> FireOnKeyPressedAndKeyRelease
	static volatile byte v_smachine_FireOnKeyPressedAndKeyRelease[NUM_KEYS_CONFORM_THE_KEYBORD], *pv_smachine_FireOnKeyPressedAndKeyRelease;

	//Variables for MODO-> FireAtTimeExpired
	static volatile word v_Count_FireAtTimeExpired[NUM_KEYS_CONFORM_THE_KEYBORD], *pv_Count_FireAtTimeExpired;
	static volatile byte v_smachine_ModeShoot_FireAtTimeExpired[NUM_KEYS_CONFORM_THE_KEYBORD], *pv_smachine_ModeShoot_FireAtTimeExpired;

	/*****************************************************************************************************************
	Para cuando se encuentra una tecla presionada dentro del grupo, solo esa <posicion-de-bit> dentro del numero de
	elemento-de-vector correspondiente, debe ponerse a '1', el resto de [num_elemnto_vector][elemntos] deben ser '0's
	
	Como vExposedToApp[elements] es inicializado a '0', solo se pone el bit correspiendte en ese momento, el resto siguen a '0'.
	Este bit es luego puesto a '0', al ser leido desde el nivel-aplicación
	
	static volatile byte v_xy[_MAX_NUMERO_DE_GRUPOS_][2];	//Si es necesario este vector Guarda x,y
	es necesario en el sentido que, basta q se encuentre un elemento dentro del grupo con tecla presionada. se aborta 
	el scan-secuencial y se concentra en ese bit específico.

	_iNumElemInVect_	= BitsQconfGrupo[CountGroup][idx] / _BYTE_WIDTH_;//el cociente.
	
	x = _iNumElemInVect_	
	y = _bit_shift_ 
				
	El _iNumElemInVect_(cociente) me da, de acuerdo a la posicion del bit, el numero de vector[x] a analizar, 
	me informa si debo saltar al siguiente

	*****************************************************************************************************************/
	static void KB_Parsing_GroupedKeys(void)
	{
		static volatile byte v_xy[_MAX_NUMERO_DE_GRUPOS_][2];	//Si es necesario, este vector Guarda x,y
		static volatile byte v_smachine_x_group[_MAX_NUMERO_DE_GRUPOS_], * pv_smachine_x_group;			

		volatile byte CountGroup, iElemIntoGroup;
		volatile byte _iNumElemInVect_, _bit_shift_;	//x,y

		volatile byte _Bit_PoscNumb;
		
		for (CountGroup=0;CountGroup < NumeroDeGruposFormados; CountGroup++)
		{	
			pv_smachine_x_group = &v_smachine_x_group[CountGroup];
			
			if (*pv_smachine_x_group == 0)	
			{
				//for (iElemIntoGroup=0; (BitsQconfGrupo[CountGroup][iElemIntoGroup] != END_OF_GROUPn) ; iElemIntoGroup++)
				iElemIntoGroup=0;
				while (1)
				{
					_Bit_PoscNumb =	 BitsQconfGrupo[CountGroup][iElemIntoGroup];
					
					if ( _Bit_PoscNumb == END_OF_GROUPn ) {break;}

					//Variables for MODO-> FireOnKeyPressed + Repetitibilidad 
					//___________________________________________________________________________________________
					pv_smachine_Reptt = &v_smachine_Reptt[_Bit_PoscNumb];
					pv_CountKeepTimming = &v_CountKeepTimming[_Bit_PoscNumb];
				
					//Variables for MODO-> FireOnKeyPressed + NOT Repetitibilidad 
					//___________________________________________________________________________________________
					pv_smachine_FireOnKeyPressed_NOT_Repett = &v_smachine_FireOnKeyPressed_NOT_Repett[_Bit_PoscNumb];
				
					//Variables for MODO-> FireOnKeyPressedAndKeyRelease
					//___________________________________________________________________________________________
					pv_smachine_FireOnKeyPressedAndKeyRelease = &v_smachine_FireOnKeyPressedAndKeyRelease[_Bit_PoscNumb];				
				
					//MODO-> FireAtTimeExpired
					//___________________________________________________________________________________________
					pv_Count_FireAtTimeExpired = &v_Count_FireAtTimeExpired[_Bit_PoscNumb];
					pv_smachine_ModeShoot_FireAtTimeExpired = &v_smachine_ModeShoot_FireAtTimeExpired[_Bit_PoscNumb];
				
					//
					_iNumElemInVect_	= _Bit_PoscNumb >>3;						//div x 8//el cociente.
					_bit_shift_ = _Bit_PoscNumb - (_BYTE_WIDTH_*_iNumElemInVect_);				
					
					if (  (vOutDebounced[_iNumElemInVect_] & ( 1<<_bit_shift_ ) ))  	
					{
						ModeFirePopulateKey(pv_smachine_x_group , _iNumElemInVect_, _bit_shift_ );//ModeFirePopulateKey organiza de aqui en adelante el estado de v_smachine_x_group
						
						//save positions for next use.
						v_xy[CountGroup][0]= _iNumElemInVect_;
						v_xy[CountGroup][1]= _bit_shift_ ;
						
									//ClearOtherBitsInGroup(BitsQconfGrupo[CountGroup][iElemIntoGroup] , CountGroup);
						break;		//Como se ha encontrado al menos la primera condición de tecla presionada dentro del grupo,
									//se rompera con la busqueda de mas bits del grupo actual.Prosigue sgte. grupo si lo hubiera.
					}	
				
				iElemIntoGroup++;
				}							
			}
			//....................................................................................................................
			else if (*pv_smachine_x_group == 1)	//MODO->FireOnKeyPressed
			{	
				TestTimmingAndRepetitibilidad(	pv_smachine_x_group,
													pv_smachine_Reptt,
													pv_CountKeepTimming,
													v_xy[CountGroup][0],
													v_xy[CountGroup][1]);				
			}
			//....................................................................................................................
			else if (*pv_smachine_x_group  == 2)	//MODO->FireOnKeyPressed + no Repetitibilidad 	//MODO->solo esperar que suelte
			{	
				if (*pv_smachine_FireOnKeyPressed_NOT_Repett ==0)
				{
					if (! (vOutDebounced[v_xy[CountGroup][0]] & (1<<v_xy[CountGroup][1]) )) //Preguntar si ya solto la tecla
					{
						(*pv_smachine_FireOnKeyPressed_NOT_Repett)++;
					}	
				}
				else if (*pv_smachine_FireOnKeyPressed_NOT_Repett ==1)				
				{
					if (! (vExposedToApp[v_xy[CountGroup][0]] & (1<<v_xy[CountGroup][1]) )) //Preguntar si ya leyo!
					{
						*pv_smachine_x_group = 0;	
						*pv_smachine_FireOnKeyPressed_NOT_Repett = 0;	//End state machines
					}		
				}
			}				
			//....................................................................................................................
			else if ( *pv_smachine_x_group == 3)		 //MODO-> FireOnKeyPressed-And-KeyRelease
			{
				//FireOnKeyPressedAndKeyRelease();

				if (*pv_smachine_FireOnKeyPressedAndKeyRelease == 0)
				{
					if (! (vOutDebounced[v_xy[CountGroup][0]] & (1<<v_xy[CountGroup][1]) )) //Preguntar si ya solto la tecla
					{
						vExposedToApp[v_xy[CountGroup][0]] |= (1<<v_xy[CountGroup][1]);	//POPULATE TECLA x APPLICATION LEVELS!!!
						
						(*pv_smachine_FireOnKeyPressedAndKeyRelease)++;
					}	
				}
				else if (*pv_smachine_FireOnKeyPressedAndKeyRelease == 1)
				{
					if (! (vExposedToApp[v_xy[CountGroup][0]] & (1<<v_xy[CountGroup][1]) )) //Preguntar si ya leyo!
					{
						*pv_smachine_x_group = 0;	
						*pv_smachine_FireOnKeyPressedAndKeyRelease = 0;
					}		
				}
			}
			//....................................................................................................................
			else if ( *pv_smachine_x_group == 4)		 //MODO-> FireAtTimeExpired
			{
				FireAtTimeExpired(	pv_smachine_x_group,
									pv_smachine_ModeShoot_FireAtTimeExpired,
									pv_Count_FireAtTimeExpired,	
									v_xy[CountGroup][0],
									v_xy[CountGroup][1]);				
			}				
		}
			
	}

	/*****************************************************************************************************************
	Todas las posiciones de las variables nacen desde aqui, pues se controla con -CountNumIndependentBits-
	*****************************************************************************************************************/
	static void KB_Parsing_IndependentKeys(void)
	{
		static volatile byte v_smachine_indep_keys[NUM_KEYS_CONFORM_THE_KEYBORD], *pv_smachine_indep_keys;			

		volatile byte CountNumIndependentBits;
		volatile byte _iNumElemInVect_, _bit_shift_;
		

		for (CountNumIndependentBits=0; CountNumIndependentBits<NUM_KEYS_CONFORM_THE_KEYBORD; CountNumIndependentBits++)
		{
			if (!Parsing_IfexistIndptBitsInGroup(CountNumIndependentBits))					//Filtra que posicion es la que se trabaja
			{	
				pv_smachine_indep_keys = &v_smachine_indep_keys[CountNumIndependentBits];	//...usando puntero...AVR GNUC reduce el codigo
				
				//Variables for MODO-> FireOnKeyPressed + Repetitibilidad 
				//___________________________________________________________________________________________
				pv_smachine_Reptt = &v_smachine_Reptt[CountNumIndependentBits];
				pv_CountKeepTimming = &v_CountKeepTimming[CountNumIndependentBits];
				
				//Variables for MODO-> FireOnKeyPressed + NOT Repetitibilidad 
				//___________________________________________________________________________________________
				pv_smachine_FireOnKeyPressed_NOT_Repett = &v_smachine_FireOnKeyPressed_NOT_Repett[CountNumIndependentBits];
				
				//Variables for MODO-> FireOnKeyPressedAndKeyRelease
				//___________________________________________________________________________________________
				pv_smachine_FireOnKeyPressedAndKeyRelease = &v_smachine_FireOnKeyPressedAndKeyRelease[CountNumIndependentBits];				
				
				//MODO-> FireAtTimeExpired
				//___________________________________________________________________________________________
				pv_Count_FireAtTimeExpired = &v_Count_FireAtTimeExpired[CountNumIndependentBits];
				pv_smachine_ModeShoot_FireAtTimeExpired = &v_smachine_ModeShoot_FireAtTimeExpired[CountNumIndependentBits];
				
				//___________________________________________________________________________________________
				_iNumElemInVect_ = CountNumIndependentBits >>3;	// div x 8					//x
				_bit_shift_ = CountNumIndependentBits - (_iNumElemInVect_ *_BYTE_WIDTH_);	//y

				//....................................................................................................................
				if ( *pv_smachine_indep_keys == 0)
				{
					if ( (vOutDebounced[_iNumElemInVect_] & ( 1<<_bit_shift_ ) ))  	
					{
						ModeFirePopulateKey(pv_smachine_indep_keys, _iNumElemInVect_, _bit_shift_ );//Redirige el flujo de la maquina de estados.
					}	
				}
				//....................................................................................................................
				else if ( *pv_smachine_indep_keys == 1)		 //MODO-> FireOnKeyPressed + Repetitibilidad - tratado en la misma funcion	
				{
					TestTimmingAndRepetitibilidad(	pv_smachine_indep_keys,
													pv_smachine_Reptt,
													pv_CountKeepTimming,
													_iNumElemInVect_,
													_bit_shift_);
				}
				//....................................................................................................................
				else if ( *pv_smachine_indep_keys == 2)		//MODO-> FireOnKeyPressed + no Repetitibilidad 	
				{
					if (*pv_smachine_FireOnKeyPressed_NOT_Repett == 0)
					{
						if (! (vOutDebounced[_iNumElemInVect_] & (1<<_bit_shift_) ))	//Preguntar si ya solto la tecla
						{
							(*pv_smachine_FireOnKeyPressed_NOT_Repett)++;
						}
					}					
					else if (*pv_smachine_FireOnKeyPressed_NOT_Repett ==1 )
					{
						if (! (vExposedToApp[_iNumElemInVect_] & (1<<_bit_shift_) ))	//Preguntar si ya leyo!
						{
							*pv_smachine_indep_keys = 0;
							*pv_smachine_FireOnKeyPressed_NOT_Repett = 0;
						}		
					}
				}
				//....................................................................................................................
				else if ( *pv_smachine_indep_keys == 3)		 //MODO-> FireOnKeyPressedAndKeyRelease. 
				{
					//FireOnKeyPressedAndKeyRelease();
										 
					if (*pv_smachine_FireOnKeyPressedAndKeyRelease == 0)
					{
						if (! (vOutDebounced[_iNumElemInVect_] & (1<<_bit_shift_) ))	//Preguntar si ya solto la tecla
						{
							vExposedToApp[_iNumElemInVect_] |= (1<<_bit_shift_);		//POPULATE TECLA x APPLICATION LEVELS!!!
							(*pv_smachine_FireOnKeyPressedAndKeyRelease)++;
						}	
					}
					else if (*pv_smachine_FireOnKeyPressedAndKeyRelease == 1)
					{
						if (! (vExposedToApp[_iNumElemInVect_] & (1<<_bit_shift_) ))	//Preguntar si ya leyo!
						{
							*pv_smachine_indep_keys = 0;
							*pv_smachine_FireOnKeyPressedAndKeyRelease = 0;
						}		
					}
				}
				//....................................................................................................................
				else if ( *pv_smachine_indep_keys == 4)		 //MODO-> FireAtTimeExpired
				{
					FireAtTimeExpired(	pv_smachine_indep_keys,
										pv_smachine_ModeShoot_FireAtTimeExpired,
										pv_Count_FireAtTimeExpired,	
										_iNumElemInVect_,
										_bit_shift_		);
				}				

			}//end if (!Parsing_IfexistIndptBitsInGroup(CountNumIndependentBits))

		}//end for
	}//end fx

	/*****************************************************************************************************************
	Si se encuentra, retorna TRUE	
	*****************************************************************************************************************/
	static BOOL Parsing_IfexistIndptBitsInGroup(volatile byte CountNumIndependentBits)
    {
		volatile byte CountGroup,iElemIntoGroup;

		for ( CountGroup=0; CountGroup < NumeroDeGruposFormados; CountGroup++)
		{
			for (iElemIntoGroup=0; (BitsQconfGrupo[CountGroup][iElemIntoGroup] != END_OF_GROUPn) ; iElemIntoGroup++)
			{
				if (CountNumIndependentBits == BitsQconfGrupo[CountGroup][iElemIntoGroup])
				{
					return TRUE;			
				}
			}				
		}			
		return FALSE;
    }

	/******************************************************************
	ModeFirePopulateKey:	1.- Redirige el flujo del programa.
	numerElemento: es el indice para el particular elemento de 8bits a 	analizar, 
	_bit_shift_: es el actual bit dentro del vectorX[numElemento]
	******************************************************************/
	static void ModeFirePopulateKey(volatile byte * pv_smachine_KeyX ,byte _iNumElemInVect_, byte _bit_shift_)
	{
		if ( vModeShoot_FireOnKeyPressed[_iNumElemInVect_] & (1<<_bit_shift_) )
		{
			//Ya puede iniciar en este momento el disparo, o bien puedo crear un stage mas,y alli recien poner a '1'...veremos cual es la mejor opción 
			if (vModeTimmingReptt[_iNumElemInVect_] & (1<<_bit_shift_) )
			{
				*pv_smachine_KeyX  = 1;	//Redirige el flujo-> it'will be handled bt TestTimmingAndRepetitibilidad()

				vExposedToApp[_iNumElemInVect_] |= (1<<_bit_shift_);			//POPULATE TECLA x APPLICATION LEVELS!!!
			}
			else
			{
				*pv_smachine_KeyX  = 2;	//Redirige el flujo
				
				vExposedToApp[_iNumElemInVect_] |= (1<<_bit_shift_);			//POPULATE TECLA x APPLICATION LEVELS!!!
			}
		}		
		//--------------------------------------------------------------------------------------------------------------------------
		if ( vModeShoot_FireOnKeyPressedAndKeyRelease[_iNumElemInVect_] & (1<<_bit_shift_) )
		{
			*pv_smachine_KeyX  = 3;	//Redirige el flujo
		}
		//--------------------------------------------------------------------------------------------------------------------------
		if ( vModeShoot_FireAtTimeExpired[_iNumElemInVect_] & (1<<_bit_shift_) )//Temporizar hasta cierto tiempo, si pasa, efectua otra operación
		{
			*pv_smachine_KeyX  = 4;	//Redirige el flujo
		}
	
	}

	/******************************************************************
	
	******************************************************************/	
	static void FireAtTimeExpired(	volatile byte * pv_smachine_KeyX ,	 
									byte * pv_smachine_ModeShoot_FireAtTimeExpired,
									word * pv_Count_FireAtTimeExpired,
									byte _iNumElemInVect_, 				  
									byte _bit_shift_	)	
	{
		if (*pv_smachine_ModeShoot_FireAtTimeExpired == 0)	
		{
			(*pv_Count_FireAtTimeExpired)++;
		
			if (! (vOutDebounced[_iNumElemInVect_] & (1<<_bit_shift_) )) //Preguntar si ya solto la tecla
			{
				if (*pv_Count_FireAtTimeExpired <= (_FIRE_AT_TIME_THRESHOLD_) )//if (*pv_Count_FireAtTimeExpired < (vModeShoot_FireAtTimeExpired_TimingThreshold[_iNumElemInVect_]&(1<<_bit_shift_)) )
				{
					//_IsKeyX_Pressed + BEFORE
					vExposedToApp[_iNumElemInVect_] |= (1<<_bit_shift_);	//POPULATE TECLA x APPLICATION LEVELS!!!//Populate key once
					vModeShoot_FireAtTimeExpired_AssertedBefOrAfter[_iNumElemInVect_] &= ~(1<<_bit_shift_);	//->0
				
					*pv_smachine_ModeShoot_FireAtTimeExpired =2;	//Go directly to wait for read key from high-level application
				}
			}
			//
			if (*pv_Count_FireAtTimeExpired > (_FIRE_AT_TIME_THRESHOLD_) )//if (*pv_Count_FireAtTimeExpired > (vModeShoot_FireAtTimeExpired_TimingThreshold[_iNumElemInVect_]&(1<<_bit_shift_)) )
			{
				//_IsKeyX_Pressed + AFTER
				vExposedToApp[_iNumElemInVect_] |= (1<<_bit_shift_);	//POPULATE TECLA x APPLICATION LEVELS!!!//Populate key once
				vModeShoot_FireAtTimeExpired_AssertedBefOrAfter[_iNumElemInVect_] |= (1<<_bit_shift_);	//->1
				//
				(*pv_smachine_ModeShoot_FireAtTimeExpired)++;		//wait for key is release
			}
		}				
		else if (*pv_smachine_ModeShoot_FireAtTimeExpired == 1)				
		{
			if (! (vOutDebounced[_iNumElemInVect_] & (1<<_bit_shift_) )) //Preguntar si ya solto la tecla
			{
				(*pv_smachine_ModeShoot_FireAtTimeExpired)++;		//This stage is only if (*pv_Count_FireAtTimeExpired > (1000/5) )
			}				
		}			
		else if (*pv_smachine_ModeShoot_FireAtTimeExpired == 2)				
		{
			if (!(vExposedToApp[_iNumElemInVect_]&(1<<_bit_shift_)))		//Preguntar si ya leyo!	//Reset if only if High-level Application read the key
			{
				*pv_smachine_ModeShoot_FireAtTimeExpired = 0;	
				*pv_Count_FireAtTimeExpired  = 0;	
				*pv_smachine_KeyX = 0;
			}
		}
	}
	/***************************************************************************************************
		Si se desea ser mas independiente en cuanto a las ktes de tiempo para disparar/mantener la repett.,
		se tendria que usar un Vector por cada tecla que compone el sistema de teclado...
		vKtesTimeReptt[NUM_KEYS_CONFORM_THE_KEYBORD][2] donde:
		vKtesTimeReptt[NUM_KEYS_CONFORM_THE_KEYBORD][0] = variable_TRIGGER_REPTT
		vKtesTimeReptt[NUM_KEYS_CONFORM_THE_KEYBORD][1] = variable_HOLDING_REPTT
		
		ver layout: _3propuestasXTestReppt.c
		
		+------------------------------------------------------------------------------+		
		+------------------------------------------------------------------------------+
		NOTA:		vModeShoot_FireOnKeyPressed <->	vModeTimmingReptt
				
				Solo el modo FireOnKeyPressed puede soportar repetitibilidad
		+------------------------------------------------------------------------------+		
		+------------------------------------------------------------------------------+
	***************************************************************************************************/
	static void TestTimmingAndRepetitibilidad(	volatile byte * pv_smachine_KeyX ,
												volatile byte * pv_smachine_Reptt,
												volatile byte * pv_CountKeepTimming,
												volatile byte _iNumElemInVect_,
												volatile byte _bit_shift_)
	{

		if (! (vOutDebounced[_iNumElemInVect_] & (1<<_bit_shift_) )) //Preguntar si ya solto la tecla
		{
			*pv_smachine_Reptt = 3;
		}
		////////////////////////////////////////////////////////////////////////
		
		if (*pv_smachine_Reptt == 0)
		{
			if ( ++(*pv_CountKeepTimming) == TriggerRepttGlobal)
			{
				*pv_CountKeepTimming =0;	//se reutilizara este contador en sgte. stage
				
				(*pv_smachine_Reptt)++;
			}	
		}
		else if (*pv_smachine_Reptt == 1)
		{
//____________________
byte vWaitForReadFromApp[1];
//if (vSynchToReadFromApp[_iNumElemInVect_] & (1<<_bit_shift_))
//{
//}
//else
//{
//}		
			//
			if (! (vExposedToApp[_iNumElemInVect_] & (1<<_bit_shift_) ))	//Preguntar si ya leyo!
			{
				vExposedToApp[_iNumElemInVect_] |= (1<<_bit_shift_);		//Repopulate again

				(*pv_smachine_Reptt)++;
			}
		}
		else if (*pv_smachine_Reptt == 2)									//ping-pong 2<->1
		{
			if (++(*pv_CountKeepTimming) == HoldingRepttGlobal)
			{
				*pv_CountKeepTimming =0;

				(*pv_smachine_Reptt)--;
			}
		}
		
		////////////////////////////////////////////
		if (*pv_smachine_Reptt == 3)
		{
			if (! (vExposedToApp[_iNumElemInVect_] & (1<<_bit_shift_) ))//Preguntar si ya leyo!
			{
				//Abort any timming in course
				*pv_smachine_Reptt = 0;
				*pv_smachine_KeyX  = 0;
				//
				*pv_CountKeepTimming =0;
			}												
		}
		//////////////////////////////////////////
	}//End fx
	
	/******************************************************************
	ninguna tecla presionada && todos los eventos de tecla leidas.	
	******************************************************************/
	byte AllkeyReleasedAndBufferAlreadyRead(void)
	{
		byte i;
		
		for (i=0;i<_NUM_VECTS_X_READKEYS_;i++)
		{
			if ( (vOutDebounced[i]!=0x00))// && (vExposedToApp[i]!=0x00) )	
				return 0;	
		}
		
		return 1;		
	}
	
	/******************************************************************
	
	******************************************************************/
	volatile byte KBAndBuffApp_Released;
	void KB_KeyboardProcess(void)
	{
		ReadCurrentValueFromKEYS_SortPredefined();
		ScanKeys_DebounceFilter();
		//
		KB_Parsing_GroupedKeys();
		KB_Parsing_IndependentKeys();
	
		//comentar si se llama directamente desde hi-level app a "AllkeyReleasedAndBufferAlreadyRead()"
		KBAndBuffApp_Released = AllkeyReleasedAndBufferAlreadyRead();	//sincronizado
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	/******************************************************************
	Por seguridad todas las teclas serian auto-excluyentes. Forman 1 grupo	
	******************************************************************/
	void SettKb_GrlConfig1(void)	
	{
		BitsQconfGrupo[0][0] = 0;			//tecla 1
		BitsQconfGrupo[0][1] = 1;			//tecla 2
		BitsQconfGrupo[0][2] = 2;			//tecla 3
		BitsQconfGrupo[0][3] = 3;			//tecla 4
		BitsQconfGrupo[0][4]= END_OF_GROUPn;
		
		NumeroDeGruposFormados = 1;
		//
		SettingBitsInRegister(vModeShoot_FireOnKeyPressed[0],0,0,0,0,1,1,1,1);		//key8-key1
		SettingBitsInRegister(vModeShoot_FireOnKeyPressedAndKeyRelease[0],0,0,0,0,0,0,0,0);		//key8-key1
		SettingBitsInRegister(vModeShoot_FireAtTimeExpired[0],0,0,0,0,0,0,0,0);		//key8-key1
		//
		SettingBitsInRegister(vModeTimmingReptt[0],0,0,0,0,1,1,1,1);		//key8-key1
		//Acepting overriding
		TriggerRepttGlobal = _KTE_TRIGGER_REPPT_500ms_;
		HoldingRepttGlobal = 50/5;	//expresados en *ms ->cada 5ms*10 = 50ms
	}	
	
	/******************************************************************
	SettingBitsInRegister( )
		De acuerdo a la posicion de los bits, pondre o no a '1' la 
		correspondiente tecla que deseo modificar su comportamiento
	
	******************************************************************/
	void HighLevel(void)
	{
		////////////////////////////////////// Setting Keyboard //////////////////////////////
		//....................................................................................
		BitsQconfGrupo[0][0] = 0;	//tecla 1
		BitsQconfGrupo[0][1] = 1;	//tecla 2
		BitsQconfGrupo[0][2] = 2;
												//BitsQconfGrupo[0][3] = 3;
		BitsQconfGrupo[0][3]= END_OF_GROUPn;
												//BitsQconfGrupo[0][2]= END_OF_GROUPn;		
		NumeroDeGruposFormados = 1;//1;//x grupos

		//BitsQconfGrupo[0][0] = 0;	//tecla 1
		//BitsQconfGrupo[0][1] = 1;	//tecla 2
		//BitsQconfGrupo[0][2]= END_OF_GROUPn;
		////
		//BitsQconfGrupo[1][0] = 2;
		//BitsQconfGrupo[1][1] = 3;
		//BitsQconfGrupo[1][2]= END_OF_GROUPn;
		////BitsQconfGrupo[0][2]= END_OF_GROUPn;		
		//NumeroDeGruposFormados = 2;//1;//x grupos
//
		//....................................................................................
		SettingBitsInRegister(vModeShoot_FireOnKeyPressed[0],0,0,0,0,0,1,1,1);		//key8-key1
		//SettingBitsInRegister(vModeShoot_FireOnKeyPressed[1],0,0,0,0,0,0,0,0);	//key16-key9
		//etc...																	//key24-key17..
		
		SettingBitsInRegister(vModeShoot_FireOnKeyPressedAndKeyRelease[0],0,0,0,0,0,0,0,0);		//key8-key1
		//SettingBitsInRegister(vModeShoot_FireOnKeyPressedAndKeyRelease[1],0,0,0,0,0,0,0,0);	//key16-key9
		//etc...																				//key24-key17..
		SettingBitsInRegister(vModeShoot_FireAtTimeExpired[0],0,0,0,0,1,0,0,0);		//key8-key1
		//SettingBitsInRegister(vModeShoot_FireAtTimeExpired[1],0,0,0,0,0,0,0,0);	//key16-key9
		//etc...																	//key24-key17..
		//vModeShoot_FireAtTimeExpired_TimingThreshold[0] = (1000*ms) / (5*ms) ;
		//....................................................................................
		//Setting x repett
		SettingBitsInRegister(vModeTimmingReptt[0],0,0,0,0,0,1,1,1);		//key8-key1
		//SettingBitsInRegister(vModeTimmingReptt[1],0,0,0,0,1,1,1,1);		//key16-key9

		//Acepting overriding
		//TriggerRepttGlobal = _KTE_TRIGGER_REPPT_500ms_;
		//HoldingRepttGlobal = 10;
		
		///////////////////////////////////////////////////////////////////////////////////////
	}
	
	/******************************************************************
	
	
	******************************************************************/
	void TestKeyboard_highlevel(void)
	{
		HighLevel();	//Config keyboard 
		
		ks0108SelectFont(SC, ks0108ReadFontData, BLACK);
		ks0108GotoXY(1,10);
		//_____________________________________________________________________-
		byte scheduler=0;
		byte scheduler2=0;
		//byte scheduler3=0;
		
		while (1)
		{
			if (scheduler==0)	
			{
				//..............................................................................................
				if ( !(vOutDebounced[0] & (1<<3) ) )//key4 ==RELEASED
				{
					if ( (vOutDebounced[0]&(1<<0)) || (vOutDebounced[0]&(1<<1)) || (vOutDebounced[0]&(1<<2)) )
					{
						scheduler=1;	
					}
				}
				
				//..............................................................................................
				if (_IsKey4_Pressed)
				{
					if (_Key4_WasPressed_BefAfterThrTime == _BEFORE_THRTIME_)
					{
						ks0108Puts_P(PSTR("B"));	
						_Key4_Set_Already_Read();	//aqui mismo murio!
					}
					else
					{
						if (! (vModeTimmingReptt[0]&(1<<3)) )	//No Reptt
						{
							ks0108Puts_P(PSTR("A"));	
							_Key4_Set_Already_Read();	
						}
						else	//Si Reptt
						{
							ks0108Puts_P(PSTR("rA"));	//synchronize puede ser activado
							_Key4_Set_Already_Read();	
						}
						
					}
				}										
				
				//..............................................................................................
				if (vOutDebounced[0]&(1<<3))	//kEY4 Pressed
				{
					if ( (vOutDebounced[0]&(1<<0)) || (vOutDebounced[0]&(1<<1)) || (vOutDebounced[0]&(1<<2)) )
					{
						scheduler=2;	
					}
				}
				//..............................................................................................
			}
			//==========================================================================================================
			//==========================================================================================================
			if (scheduler==1)			
			{
				if (scheduler2 == 0)
				{
					//si se suelta y nuevamente se presiona key1, la tecla seguiria ejecutando su correspondiente tarea...
					if ( (vOutDebounced[0] & (1<<0)) ) //se respeta la intencion del usuario, si suelta, 
					{
						//..............................................
						if (_IsKey1_Pressed)
						{
							ks0108Puts_P(PSTR("1"));			
							_Key1_Set_Already_Read();
							//
							BUZZER_FLAGS.BUZZER_Triggered = 1;	
						}
						//..............................................
					}	
					else
					{
						scheduler2++;
						//la misma tecla se "mata", en el sentido que ya no es valido nuevamente
					}
				}
				if (scheduler2==1)
				{
					//esperar a que todos sueltenbyte i;
					if (AllkeyReleasedAndBufferAlreadyRead())
					{
						scheduler=0;
						scheduler2=0;
						//clear buffers
						vExposedToApp[0] = 0;
						vModeShoot_FireAtTimeExpired_AssertedBefOrAfter[0] = 0;
						//
					}
				}
			}			
			//==========================================================================================================
			//==========================================================================================================
			if (scheduler==2)			
			{
				if (scheduler2 == 0)
				{
					if ( (vOutDebounced[0] & (1<<3)) ) //key4 pressed se mantiene presionado
					{
						if (_IsKey1_Pressed)
						{
							ks0108Puts_P(PSTR("c1")); _Key1_Set_Already_Read(); BUZZER_FLAGS.BUZZER_Triggered = 1;	
						}
						if (_IsKey2_Pressed)
						{
							ks0108Puts_P(PSTR("c2")); _Key2_Set_Already_Read();	BUZZER_FLAGS.BUZZER_Triggered = 1;	
						}
						if (_IsKey3_Pressed)
						{
							ks0108Puts_P(PSTR("c3")); _Key3_Set_Already_Read();	BUZZER_FLAGS.BUZZER_Triggered = 1;	
						}		
					}
					else
					{
						scheduler2++;
					}
				
				}					
				if (scheduler2 == 1) //else //solto
				{
					if (AllkeyReleasedAndBufferAlreadyRead())
					{
						scheduler=0;
						scheduler2=0;

						//clear buffers
						vExposedToApp[0] = 0;
						vModeShoot_FireAtTimeExpired_AssertedBefOrAfter[0] = 0;
						//
					}
				}
			}							
			//==========================================================================================================
			//==========================================================================================================
		
		}//end while
	
	}
/*

		while (1)
		{
			if (_IsKey1_Pressed)
			{
				ks0108Puts_P(PSTR("1"));			
				_Key1_Set_Already_Read();
				//
				BUZZER_FLAGS.BUZZER_Triggered = 1;	
			}
			
			if (_IsKey2_Pressed)
			{
				ks0108Puts_P(PSTR("2"));
				_Key2_Set_Already_Read();
				//
				BUZZER_FLAGS.BUZZER_Triggered = 1;	
			}
			
			if (_IsKey3_Pressed)
			{
				ks0108Puts_P(PSTR("3"));
				_Key3_Set_Already_Read();
				//
				BUZZER_FLAGS.BUZZER_Triggered = 1;	
			}
//===========================================================================
byte smachine_ctrl1=0;
			
			if (_IsKey4_Pressed)
			{
				if (_Key4_WasPressed_BefAfterThrTime == _BEFORE_THRTIME_)
				{
					ks0108Puts_P(PSTR("B"));	
					
					_Key4_Set_Already_Read();
				}
				else
				{
					
					if (smachine_ctrl1 == 0)
					{
						if ( (_IsKey1_Pressed)||(_IsKey2_Pressed)||(_IsKey3_Pressed))//mismo grupo exc
						{
							//Abortar,, encausar el flujo--------------->>>>
							smachine_ctrl1++;
						
						}
						else
						{
							
							ks0108Puts_P(PSTR("A"));	//de manera repetitiva...		
							//_Key4_Set_Already_Read();
							
						}
					}
					if (smachine_ctrl1 == 1)
					{
						while ( vOutDebounced[0]& (1<<3) )
						{
							if (_IsKey1_Pressed)
							{
								ks0108Puts_P(PSTR(">"));
								_Key1_Set_Already_Read();	
							}
							if (_IsKey2_Pressed)
							{
								ks0108Puts_P(PSTR("<"));	
								_Key2_Set_Already_Read();	
							}
							if (_IsKey3_Pressed)
							{
								if (_Key3_WasPressed_BefAfterThrTime == _BEFORE_THRTIME_)
								{
									ks0108Puts_P(PSTR("tgALL"));	
								}
								else
								{
									ks0108Puts_P(PSTR("ONALL"));	
								}	
								_Key3_Set_Already_Read();									
							}
						
						}						
					}
				
				}

				//
				BUZZER_FLAGS.BUZZER_Triggered = 1;	
			}	
			
		}
	}
*/

#endif


