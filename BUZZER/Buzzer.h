#ifndef BUZZER_H_
#define BUZZER_H_
	
	/************************************************************************
	************************************************************************/
	#define PORTxBUZZER	(PORTG)
	#define DDRxBUZZER	(DDRG)
	#define PINxBUZZER	(PING)
	//
	#define BUZZER_pinCTRL (4)	//PG4
	/************************************************************************
	************************************************************************/
	#define BUZZER_ON()		do{PinTo1(PORTxBUZZER, BUZZER_pinCTRL);}while(0)
	#define BUZZER_OFF()	do{PinTo0(PORTxBUZZER, BUZZER_pinCTRL);}while(0)
	/************************************************************************
	************************************************************************/
	#define BuzzerDisable()	do{BUZZER_OFF();Buzzer.bfBuzzer.SoundEnable = OFF;}while(0) 

	/************************************************************************
	************************************************************************/
	typedef struct _Buzzer_{
		
		byte scheduler;
		byte Counter0;
		byte Counter1;
		byte Counter2;
		byte Counter3;
		
		struct _bfBuzzer
		{
			unsigned SoundEnable:1;
			unsigned Play:1;
			unsigned _c:1;
			unsigned _d:1;
			unsigned _e:1;
			unsigned _f:1;
			unsigned _g:1;
			unsigned _h:1;
		}bfBuzzer;
		
		union _ubfBuzzerAutoex
		{
			byte BuzzerSoundsAutoex;
			struct _bfBuzzerSoundsAutoex
			{
				unsigned SimpleSound0:1;
				unsigned AcceptSound0:1;
				unsigned _c:1;
				unsigned _d:1;
				unsigned _e:1;
				unsigned _f:1;
				unsigned _g:1;
				unsigned _h:1;
			}bfBuzzerSoundsAutoex;	

		}ubfBuzzerAutoex;
	
	}_Buzzer;
	/************************************************************************
	************************************************************************/
	void InitBuzzer(void);
	void BuzzerScheduler(void);
	extern volatile _Buzzer Buzzer;

#endif
