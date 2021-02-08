/*
 * TimerApp.h
 *
 * Created: 10/04/2012 03:50:34 p.m.
 *  Author: jcaf
 */ 


#ifndef TIMERAPP_H_
#define TIMERAPP_H_

	typedef struct _bfCommonProcess0_
	{
		unsigned Timmer_BlinkCaption:1;		//Flag puede ser usado en multiples partes del programa
		unsigned SignOneTick_BlinkCaption:1;	//Se pone a 1
		unsigned ___u:6;
	}_bfCommonProcess0;
	
	extern volatile _bfCommonProcess0 bfCommonProcess0;

	void TIMER0_IsActiveFading(void);
	
	void TimmingHandler_BlinkCaption(void);

#endif /* TIMERAPP_H_ */