/*
 * DimmBLGLCD_1.c
 *
 * Created: 7/16/2012 11:49:11 AM
 *  Author: jcaf
 */ 
#include "Includes/InitializeAllModules.h"

#ifdef _USING_GLCD_BACKLIGHT_PIN_
 	
	volatile _DimmHandler DimmHandler;

	void PWM_Handler_BackLight_GLCD(void);
	
	/**********************************************************
	#define _RESET_AND_WAITFOR_NEW_EVENT_KEEPING_TIMMING_BLGLCD_	(0)
	#define _RESET_COUNTERTIMMER_FOR_NEW_KEEPING_TIMMING_BLGLCD_	(1)
	#define _KEEPING_TIMMING_BLGLCD_								(2)
	//
	#define _LIFESPAN_KEEPING_TIMMING_BLGLCD_ (10000)//ms
	
	#define _KTE_LIFESPAN_KEEPING_TIMMING_BLGLCD_	((word)( (_LIFESPAN_KEEPING_TIMMING_BLGLCD_*1.0) / 5))	//in milliseconds

	#define ResetCounterTimmerForNewKeepingTimmingBLGLCD() do{DimmHandler.SchedulerTimmerKeepAlive_BLGLCD = _RESET_COUNTERTIMMER_FOR_NEW_KEEPING_TIMMING_BLGLCD_;}while(0)
	**********************************************************/
	void ScheduleTimmerKeepAlive_BLGLCD(void)	//executed each 5 ms
	{
		//DimmHandler.SchedulerTimmerKeepAlive_BLGLCD "trabaja" solo para valaores 1 y 2, 0 es el valor en el que espera una nueva orden para ser ejecutada una sola vez
		if (DimmHandler.SchedulerTimmerKeepAlive_BLGLCD == _RESET_COUNTERTIMMER_FOR_NEW_KEEPING_TIMMING_BLGLCD_)
		{
			DimmHandler.CounterTimmerKeepAlive_BLGLCD = 0x0000;
			DimmHandler.SchedulerEvent = _HOLDMAX_PWM_BLGLCD_;	//ON 100% Backlight GLCD
			DimmHandler.SchedulerTimmerKeepAlive_BLGLCD++;
		}
		if (DimmHandler.SchedulerTimmerKeepAlive_BLGLCD == _KEEPING_TIMMING_BLGLCD_)
		{
			if (++DimmHandler.CounterTimmerKeepAlive_BLGLCD == _KTE_LIFESPAN_KEEPING_TIMMING_BLGLCD_)
			{
				//DimmHandler.CounterTimmerKeepAlive_BLGLCD = 0x0000;		//it's no longer necessary
				DimmHandler.SchedulerEvent = _DIMMING_DOWN_TO_MIN_BLGLCD_;	//
				
				DimmHandler.SchedulerTimmerKeepAlive_BLGLCD = _RESET_AND_WAITFOR_NEW_EVENT_KEEPING_TIMMING_BLGLCD_;
			}
		}
	}
	
	/**********************************************************
	#define TIME_DIMMING_BLGLCD		(3000)//ms
	#define NUM_PASOS_PWM_BLGLCD	(12)	//pasos de resolucion 1/(0.125ms*12) = FrecPWM_BL_GLCD = 666Hz
	#define BASE_TIME_BLGLCD		(0.125)//ms
	#define TIME_LIMIT_COUNTER ( (unsigned int) ( (TIME_DIMMING_BLGLCD*1.0) / (NUM_PASOS_PWM_BLGLCD *BASE_TIME_BLGLCD)) )
	//
	#define _RESET_AND_WAITFOR_NEW_EVENT_BLGLCD_	(0)
	#define _DIMMING_DOWN_TO_MIN_BLGLCD_			(1)
	#define _HOLDMAX_PWM_BLGLCD_					(2)
	
	//Save current state
	#define _ON_100P_DC_BLGLCD_						(NUM_PASOS_PWM_BLGLCD)
	#define _OFF_100P_DC_BLGLCD_					(0)
	#define _MIN_DC_BLGLCD_							(_OFF_100P_DC_BLGLCD_+1)
	
	**********************************************************/
	/*
	#define xxx() do{\
					DimmHandler.CounterTicks = 0x0000;\
					DimmHandler.SchedulerEvent = _DIMMING_DOWN_TO_MIN_BLGLCD_;\
					}while(0)
	*/
	
	//ejecutado c/0.125ms
extern int8_t glcd_isWakeup; //Added 2021
	void SchedulerEvent_PWM_BLGLCD(void)
	{
		if (DimmHandler.SchedulerEvent == _DIMMING_DOWN_TO_MIN_BLGLCD_)
		{
				if (++DimmHandler.CounterTicks == TIME_LIMIT_COUNTER)	//(3000ms/12)/0.125ms
				{
					DimmHandler.CounterTicks = 0x0000;
					
					if (DimmHandler.DutyCycle_BLGLCD > 1)				//decrementa desde el punto en donde se encuentre
						DimmHandler.DutyCycle_BLGLCD--;				
					else						
						DimmHandler.DutyCycle_BLGLCD = _MIN_DC_BLGLCD_;	//Trunca hacia el minimo
					
					if (DimmHandler.DutyCycle_BLGLCD == _MIN_DC_BLGLCD_)//en ambos casos, termina 
					{
						DimmHandler.SchedulerEvent = _RESET_AND_WAITFOR_NEW_EVENT_BLGLCD_;
						//DimmHandler.CurrentState = _MIN_DC_BLGLCD_;	//Reserved 
                        
                        //Added 2021
                        glcd_isWakeup = 1;
					}
				}
		}
		else if (DimmHandler.SchedulerEvent == _HOLDMAX_PWM_BLGLCD_)
		{
				DimmHandler.DutyCycle_BLGLCD = _ON_100P_DC_BLGLCD_;
				
				DimmHandler.CounterTicks = 0x0000;	//Leave prepared for new _DIMMING_DOWN_TO_MIN_BLGLCD
				DimmHandler.SchedulerEvent = _RESET_AND_WAITFOR_NEW_EVENT_BLGLCD_;
				//DimmHandler.CurrentState = _ON_100P_DC_BLGLCD_;	//Reserved 
		}
		
		PWM_Handler_BackLight_GLCD();
	}
	/**********************************************************
	**********************************************************/
	void PWM_Handler_BackLight_GLCD(void)
	{
		DimmHandler.Counter_StepsOfPWM++;
		 
		if ( DimmHandler.Counter_StepsOfPWM == NUM_PASOS_PWM_BLGLCD)
		{
			DimmHandler.Counter_StepsOfPWM = 0;
			
			if (DimmHandler.DutyCycle_BLGLCD > 0)			
				{GLCD192X64_BKLIGHT_ON();}
			else
				{GLCD192X64_BKLIGHT_OFF();}
		}
		
		if (DimmHandler.Counter_StepsOfPWM == DimmHandler.DutyCycle_BLGLCD)	//0<= DimmHandler.Counter_StepsOfPWM <= 11
			{GLCD192X64_BKLIGHT_OFF();}
	}
	
#endif