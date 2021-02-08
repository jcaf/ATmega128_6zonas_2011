/*
 * key.h
 *
 * Created: 10/7/2012 1:04:58 PM
 *  Author: JCaf
 */ 

#ifndef KEY_H_
#define KEY_H_

	#define MAXNUM_MODE_BY_PS (4)
	
	void change_operating_mode(
							PTRFXrVOID (*pvfx)[MAXNUM_MODE_BY_PS][KB_TOTALOFKEYS],
							byte operating_mode
	);

	struct _key
	{
		PTRFXrVOID _1fmode;
		PTRFXrVOID _1fmode_aft;
		PTRFXrVOID _2fmode;
		PTRFXrVOID _2fmode_aft;
	};
	//////////////////////////////////
	struct _stackfx
	{
		struct _level
		{
			struct _key key[KB_TOTALOFKEYS];
		}level[10];  //maximo numero de niveles que puede guardar

		byte sp;	//Stack Pointer
	};
	//////////////////////////////////
	//Lo he tenido que hacer visible para que pueda usarse _waitforclean_keys()
	typedef enum _KEYMIXSTATES
	{
		INHIBITED__CHANGE_LAYOUT_KB=-2,
		INHIBITED=-1,
		SCHEDULING_KEYS=0,
		PROCESSING_KEYS1FX,
		PROCESSING_KEYS2FX,
		WAITFOR_KB_FREE_AND_COMPLETE_PS,
	}KEYMIXSTATES;

	struct _kbhandler_app
	{
		KEYMIXSTATES scheduler;
		byte ikey;			//key pressed?
	};
	
	extern struct _key key[KB_TOTALOFKEYS];
	extern struct _kbhandler_app kbhandler_app;
	
	extern struct _stackfx stackfx;
	void push_address_fx(void);
	void pop_address_fx(void);
	void DUMMYFX(void);
	
	void kb_handler0(void);

#define _KB_waitfor_kb_free_and_complete_ps() do{kbhandler_app.scheduler = (KEYMIXSTATES)WAITFOR_KB_FREE_AND_COMPLETE_PS;}while(0)
#define _KB_inhibited() do{kbhandler_app.scheduler = (KEYMIXSTATES)INHIBITED;}while(0)
	
#endif /* KEY_H_ */
