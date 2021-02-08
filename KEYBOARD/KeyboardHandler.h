/*
 * KeyboardHandler.h
 *
 * Created: 16/02/2012 09:12:13 p.m.
 *  Author: jcaf
 */ 

#ifndef KEYBOARDHANDLER_H_
#define KEYBOARDHANDLER_H_
	
	/**************************************************************************************************
	**************************************************************************************************/
	#define KB_TOTALOFKEYS		(4)
	/**************************************************************************************************
	posicion dentro de vector
	**************************************************************************************************/
	#define KB_iKEY1 (0)
	#define KB_iKEY2 (1)
	#define KB_iKEY3 (2)
	#define KB_iKEY4 (3)
	/**************************************************************************************************
				STABLE SIGNAL (INTERNAMENTE X SOFTWARE)

	NO confundir con los valores de hardware: 
					#define _KB_KEY_HANDLED_AS_PRESSED_ 	(0)	//hardware conexion
					#define _KB_KEY_HANDLED_AS_RELEASED_ 	(1)	//hardware conexion
	**************************************************************************************************/
	#define KB_KEY_PRESSED	(1)	//STABLE SIGNAL (INTERNAMENTE X SOFTWARE)
	#define KB_KEY_RELEASED	(0)	//STABLE SIGNAL (INTERNAMENTE X SOFTWARE)
	/**************************************************************************************************
	to populate
	**************************************************************************************************/
	#define KB_SET_READYTOREAD_INAPP	(1)
	#define KB_CLEAR_READYTOREAD_INAPP	(0)
	/**************************************************************************************************
	**************************************************************************************************/
	#define _MASKING_PIN_INTO_READ_REGISTER_(PINxKB_KEY_X,KB_pinKEY_X) (PINxKB_KEY_X & (1<<KB_pinKEY_X))
	
	/**********************************
	Asignación:
	**********************************/
	#define DDRxKB_KEY_1	(DDRA)
	#define PORTxKB_KEY_1	(PORTA)
	#define PINxKB_KEY_1	(PINA)
	#define KB_pinKEY_1		(1)	//
	#define _READONLYPIN_KEY_1_		_MASKING_PIN_INTO_READ_REGISTER_(PINxKB_KEY_1, KB_pinKEY_1)
	
	#define _INTRO_BIT_FROM_PINREAD_AT_POSC_KEY_1_ (_READONLYPIN_KEY_1_>>KB_pinKEY_1)
	//opcionales x uso
	#define KB_PULLUP_ON_KEY_1_()		PinTo1(PORTxKB_KEY_1,KB_pinKEY_1)
	#define KB_PULLUP_OFF_KEY_1_()		PinTo0(PORTxKB_KEY_1,KB_pinKEY_1)
	
	/**********************************
	Asignación:
	**********************************/
	#define DDRxKB_KEY_2	(DDRA)
	#define PORTxKB_KEY_2	(PORTA)
	#define PINxKB_KEY_2	(PINA)
	#define KB_pinKEY_2		(2)	//
	#define _READONLYPIN_KEY_2_		_MASKING_PIN_INTO_READ_REGISTER_(PINxKB_KEY_2, KB_pinKEY_2)
	
	#define _INTRO_BIT_FROM_PINREAD_AT_POSC_KEY_2_ (_READONLYPIN_KEY_2_>>KB_pinKEY_2)
	//opcionales x uso
	#define KB_PULLUP_ON_KEY_2_()		PinTo1(PORTxKB_KEY_2,KB_pinKEY_2)
	#define KB_PULLUP_OFF_KEY_2_()		PinTo0(PORTxKB_KEY_2,KB_pinKEY_2)
	
	/**********************************
	Asignación:
	**********************************/
	#define DDRxKB_KEY_3	(DDRA)
	#define PORTxKB_KEY_3	(PORTA)
	#define PINxKB_KEY_3	(PINA)
	#define KB_pinKEY_3		(3)	//
	#define _READONLYPIN_KEY_3_		_MASKING_PIN_INTO_READ_REGISTER_(PINxKB_KEY_3, KB_pinKEY_3)
	
	#define _INTRO_BIT_FROM_PINREAD_AT_POSC_KEY_3_ (_READONLYPIN_KEY_3_>>KB_pinKEY_3)
	//opcionales x uso
	#define KB_PULLUP_ON_KEY_3_()		PinTo1(PORTxKB_KEY_3,KB_pinKEY_3)
	#define KB_PULLUP_OFF_KEY_3_()		PinTo0(PORTxKB_KEY_3,KB_pinKEY_3)
	
	/**********************************
	Asignación:
	**********************************/
	#define DDRxKB_KEY_4	(DDRA)
	#define PORTxKB_KEY_4	(PORTA)
	#define PINxKB_KEY_4	(PINA)
	#define KB_pinKEY_4		(0)	//
	#define _READONLYPIN_KEY_4_		_MASKING_PIN_INTO_READ_REGISTER_(PINxKB_KEY_4, KB_pinKEY_4)
	
	#define _INTRO_BIT_FROM_PINREAD_AT_POSC_KEY_4_ (_READONLYPIN_KEY_4_>>KB_pinKEY_4)
	//opcionales x uso
	#define KB_PULLUP_ON_KEY_4_()		PinTo1(PORTxKB_KEY_4,KB_pinKEY_4)
	#define KB_PULLUP_OFF_KEY_4_()		PinTo0(PORTxKB_KEY_4,KB_pinKEY_4)
	

	/*****************************************************************
	Siempre debe existir en el sistema un timmer fijo para programar
	todas las tareas del sistema. Este timmer normalmente es un 
	contador del hardware, y su rango de temporización es en miliseg.
	
		_SYS_TIMMER_X_KEYBOARD_
	
	Para contadores de 8-bits(unsig), el maximo tiempo a _SYS_TIMMER_X_KEYBOARD_(ms)
	seria de	1275*ms = 1.275s
	
	Para contadores de 16-bits(unsig), el maximo tiempo a _SYS_TIMMER_X_KEYBOARD_(ms)
	seria de	327675*ms
	
	WINAVR pierde exactitud al dividir con *ms.. al ser una operacion con residudo 0..???
	Si le entrego directamente en enteros,,, si computa exactamente.
	*****************************************************************/
	
	#define _SYS_TIMMER_X_KEYBOARD_		(_SYS_TIMMER_GRL1_)
	//#define _TIEMPO_DESEADO_(T_DESEADO) (T_DESEADO /_SYS_TIMMER_X_KEYBOARD_)
	
	//#define _KTE_TRIGGER_REPPT_500ms_	((byte)_TIEMPO_DESEADO_(500*ms))	//100*5ms -> 500mS
	//#define _KTE_HOLDING_REPPT_100ms_	((byte)_TIEMPO_DESEADO_(100*ms))	//20*5ms  -> 100mS

	#define _SYS_TIMMER_X_KEYBOARD_IN_MILISEG_		(5)//ms
	#define _KTE_TRIGGER_REPPT_500ms_	(500/_SYS_TIMMER_X_KEYBOARD_IN_MILISEG_)	//Expresado en miliseg. 100*5ms -> 500mS
	#define _KTE_HOLDING_REPPT_100ms_	(100/_SYS_TIMMER_X_KEYBOARD_IN_MILISEG_)	//Expresado en miliseg. 20*5ms  -> 100mS
	//
	/******************************************************************
	Fix the threshold for Trigger before/after 	
	******************************************************************/
	#define _FIRE_AT_TIME_THRESHOLD_ ((1000*ms)/(_SYS_TIMMER_X_KEYBOARD_))

	#define KB_BEFORE_THR	(0)
	#define KB_AFTER_THR	(1)

	/******************************************************************
	******************************************************************/
	#define KB_KEY1_ReadyToRead() (objkey[KB_iKEY1].bfSTATE.ReadyToRead == KB_SET_READYTOREAD_INAPP )
	#define KB_KEY2_ReadyToRead() (objkey[KB_iKEY2].bfSTATE.ReadyToRead == KB_SET_READYTOREAD_INAPP )
	#define KB_KEY3_ReadyToRead() (objkey[KB_iKEY3].bfSTATE.ReadyToRead == KB_SET_READYTOREAD_INAPP )
	#define KB_KEY4_ReadyToRead() (objkey[KB_iKEY4].bfSTATE.ReadyToRead == KB_SET_READYTOREAD_INAPP )
	
	#define KB_KEY1_HasBeenRead() do{objkey[KB_iKEY1].bfSTATE.ReadyToRead = KB_CLEAR_READYTOREAD_INAPP;}while(0)
	#define KB_KEY2_HasBeenRead() do{objkey[KB_iKEY2].bfSTATE.ReadyToRead = KB_CLEAR_READYTOREAD_INAPP;}while(0)
	#define KB_KEY3_HasBeenRead() do{objkey[KB_iKEY3].bfSTATE.ReadyToRead = KB_CLEAR_READYTOREAD_INAPP;}while(0)
	#define KB_KEY4_HasBeenRead() do{objkey[KB_iKEY4].bfSTATE.ReadyToRead = KB_CLEAR_READYTOREAD_INAPP;}while(0)
	
	/******************************************************************
	******************************************************************/
	
	#define _NO_AGRUPADO_AUTOEXCLUDING_ (0)
	
	struct _key_properties
	{
		union _u_key_properties
		{
			struct _bf_key_properties
			{
				unsigned OnKeyPressed:1;
				unsigned OnKeyPressedAndKeyRelease:1;
				unsigned AtTimeExpired:1;
				unsigned Reptt:1;
				unsigned __none:4;
			}bf;	
			
			byte _8b_key_properties;			
		}u;
		
		byte group_autoexcluding;
	};

	struct _ObjKey
	{
		byte smPinState;
		byte CountDebounce;
		
		byte smParsingProp;
        word CounterKeeper;
		//byte smAtTimeExpired;
		//byte CountAtTimeExpired;

		struct _bfSTATE
		{
			unsigned Pin:1;				//direct hardware
			unsigned StableState:1;		//debounce apply
			unsigned ReadyToRead:1;		//soft-populate
			unsigned AtTimeExpired_BeforeOrAfter:1;
			unsigned OwnerOfGroup:1;
			unsigned InProcessing:1;
			unsigned __a:1;
			unsigned __b:1;
			//unsigned temp:1;
		}bfSTATE;
		
		struct _key_properties key_properties;
		//byte TriggerRepttGlobal;	//x si tal se necesita control independiente
		//byte HoldingRepttGlobal;
	};

	struct _objsharedfeatkeys
	{
		byte vgroup_autoexcluding[KB_TOTALOFKEYS/2];//maximo numero de grupo auto-exluyente q se puede formar
		
		byte TriggerRepttGlobal;
		byte HoldingRepttGlobal;

		//struct _bfSHARED
		//{
			//unsigned AllKeysReleased:1;
			//unsigned AllKeysCompleteProcesses:1;
			//unsigned _nada:6;		
		//}bfSHARED;		
	};
	
	////////////////////////////////////////////////////////
	#define KEY_CHANGE_LAYOUT__STACK_DEEP (10)	
	
	typedef enum _STACK_MODE_
	{
		UNTOUCH=0,	//valor util para variable-de-aplicacion "app_kb_layout", NO USADO por synch_change_layout_kb()
		
					//synch_change_layout_kb() devolvera:
		DIRECT=1,	//valor util para variable-de-aplicacion "app_kb_layout"
		PUSH=2,		//valor util para variable-de-aplicacion "app_kb_layout"
		//				
		POP=3
	}_STACK_MODE;		
	
 		
	struct _synch_kb_exposed_to_app
	{
		//x wait for free-key and complete all processes on keyboard
		struct _synch_kb_exposed_to_app__synch_kb_free_and_complete_ps
		{
			byte synch_freecomplete_sm0;
			
		}synch_kb_free_and_complete_ps;
		
		//x change layout
		struct _synch_kb_exposed_to_app__key_change_layout
		{
			byte change_sm0;	
			_STACK_MODE stack_mode;
			struct _key_properties * p_key_properties;
			
			struct _key_properties __dummy;	//only for pop
		}key_change_layout;
	};
	
	extern volatile struct _synch_kb_exposed_to_app synch_kb_exposed_to_app;
	
	extern volatile struct _ObjKey objkey[KB_TOTALOFKEYS];
	extern volatile struct _objsharedfeatkeys objsharedfeatkeys;	//x shared features 

	/******************************************************************
	******************************************************************/
	void InitKeyboard(void);
	void KB_KeyboardProcess(void);
	
	//...................................		
	//#define _DEBUG_KEYBOARD_HANDLER_
	#ifdef 	_DEBUG_KEYBOARD_HANDLER_
		void TestKeyboardHandler01(void);
		void TestKeyboardHandler01_ONLY_BUZZER(void);
		void TestKeyboardHandler02(void);
	#endif
	//...................................

#endif /* KEYBOARDHANDLER_H_ */
