/*
 * DimmBLGLCD.h
 *
 * Created: 7/16/2012 11:49:42 AM
 *  Author: jcaf
 */ 


#ifndef DIMMBLGLCD_H_
#define DIMMBLGLCD_H_

	typedef struct _DimmHandler_
	{
		byte SchedulerEvent;
		//byte CurrentState;	////add:Save the current state. Dont use
		word CounterTicks;
		//
		byte Counter_StepsOfPWM;
		byte DutyCycle_BLGLCD;
		//
		word CounterTimmerKeepAlive_BLGLCD;
		byte SchedulerTimmerKeepAlive_BLGLCD;	//One touch "wake" from last dimming-down(_MIN_DC_BLGLCD_)
	
	}_DimmHandler;
	
	/**********************************************************
	**********************************************************/
	#define TIME_DIMMING_BLGLCD		(650)//ms
	#define NUM_PASOS_PWM_BLGLCD	(12)	//pasos de resolucion 1/(0.125ms*12) = FrecPWM_BL_GLCD = 666Hz
	#define BASE_TIME_BLGLCD		(0.125)//ms
	#define TIME_LIMIT_COUNTER ( (unsigned int) ( (TIME_DIMMING_BLGLCD*1.0) / (NUM_PASOS_PWM_BLGLCD *BASE_TIME_BLGLCD)) )
	//	
	#define _RESET_AND_WAITFOR_NEW_EVENT_BLGLCD_	(0)
	#define _DIMMING_DOWN_TO_MIN_BLGLCD_			(1)
	#define _HOLDMAX_PWM_BLGLCD_					(2)
	
	//For save the current state
	#define _OFF_100P_DC_BLGLCD_					(0)
	#define _MIN_DC_BLGLCD_							(_OFF_100P_DC_BLGLCD_+1)
	//#define _DC_2_	(2)
	//#define _DC_3_	(3)
	//#define _DC_4_	(4)
	//#define _DC_5_	(5)
	//#define _DC_6_	(6)
	//#define _DC_7_	(7)
	//#define _DC_8_	(8)
	//#define _DC_9_	(9)
	//#define _DC_10_	(10)
	//#define _DC_11_	(11)
	#define _ON_100P_DC_BLGLCD_						(NUM_PASOS_PWM_BLGLCD)

	/**********************************************************
#define _RESET_AND_WAITFOR_NEW_EVENT_BLGLCD_	(0)
#define _DIMMING_DOWN_TO_MIN_BLGLCD_			(1)
#define _HOLDMAX_PWM_BLGLCD_					(2)	
**********************************************************/
	#define _RESET_AND_WAITFOR_NEW_EVENT_KEEPING_TIMMING_BLGLCD_	(0)
	#define _RESET_COUNTERTIMMER_FOR_NEW_KEEPING_TIMMING_BLGLCD_	(1)
	#define _KEEPING_TIMMING_BLGLCD_								(2)
	//
	#define _LIFESPAN_KEEPING_TIMMING_BLGLCD_ (20000)//(3000)//ms
		
	#define _KTE_LIFESPAN_KEEPING_TIMMING_BLGLCD_	((word)( (_LIFESPAN_KEEPING_TIMMING_BLGLCD_*1.0) / 5))	//in milliseconds

	/**********************************************************
	**********************************************************/
	
	#define ResetCounterTimmerForNewKeepingTimmingBLGLCD() do{DimmHandler.SchedulerTimmerKeepAlive_BLGLCD = _RESET_COUNTERTIMMER_FOR_NEW_KEEPING_TIMMING_BLGLCD_;}while(0)

	#define DirectForce_And_Hold_MAX_PWM_BLGLCD() do{\
														DimmHandler.SchedulerEvent = _HOLDMAX_PWM_BLGLCD_;	\
														DimmHandler.SchedulerTimmerKeepAlive_BLGLCD = _RESET_AND_WAITFOR_NEW_EVENT_KEEPING_TIMMING_BLGLCD_;\
													} while (0);

	extern volatile _DimmHandler DimmHandler;
	void ScheduleTimmerKeepAlive_BLGLCD(void);
	void SchedulerEvent_PWM_BLGLCD(void);
	
	//in macros...
	//DimmHandler.SchedulerEvent = _DIMMING_DOWN_TO_MIN_BLGLCD_;
	//DimmHandler.SchedulerEvent = _HOLDMAX_PWM_BLGLCD_;
	//DimmHandler.SchedulerEvent = _RESET_AND_WAITFOR_NEW_EVENT_BLGLCD_;

#endif /* DIMMBLGLCD_H_ */