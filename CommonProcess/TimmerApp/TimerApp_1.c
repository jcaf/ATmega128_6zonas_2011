/*
 * TimerApp_1.c
 
	Contiene timers de uso comun para todas las aplicaciones q lo necesiten.
 	
	 OJO: no es fx reentrante
 *
 * Created: 10/04/2012 03:50:26 p.m.
 *  Author: jcaf
 */ 
#include "Includes/InitializeAllModules.h"
	
	volatile _bfCommonProcess0 bfCommonProcess0;
	
	/***************************************************************************************
	cada 5 ms es ejecutado.
	***************************************************************************************/
	void TIMER0_IsActiveFading(void)
	{
		if (ps_fading_inbk.bf.timmer_active)
		{
			ps_fading_inbk.bf.sign_new_tick=1;	
		}			
	}
	
	/***************************************************************************************
	Llamado desde ISR() - cada 5 ms es ejecutado.
	***************************************************************************************/
	void TimmingHandler_BlinkCaption(void)
	{
		//if (++CountTicks_BlinkCaptionZone == 60)	//5ms*60= 300ms
		//{	  CountTicks_BlinkCaptionZone = 0;
		//
			//cada 5ms es comprado en main-line
			bfCommonProcess0.SignOneTick_BlinkCaption = ON;
			//MD6Z_FLAGS.InitBlinkCaptionZone = 1;
		//}
	}	