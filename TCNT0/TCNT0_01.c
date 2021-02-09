/*****************************************************************************************************************
	TCNT0_Init_Config:
		//Configuraci�n para TCNT0 como TEMPORIZADOR
		//ldi		temp0,(0<<FOC0 | WGM01_0_MODE_0_NORMAL | COM01_COM00_NORMAL_OC0_DISCONNECTED | CS02_00_CLCK_8 )
		//out		TCCR0,temp0

		;Configuraci�n para TCNT0 como Clear on Timer On Compare CTC
		;ldi		temp0,77		//77->5ms
		//LDI		temp0,31		//31 ->2ms

		ldi		temp0,KTE_TIME_FOR_CTC( TIME_FOR_CTC, PRESCALER_TCNT0_1024 )
		out		OCR0,temp0

		ldi		temp0,(0<<FOC0 | WGM01_0_MODE_2_CTC | COM01_COM00_NORMAL_OC0_DISCONNECTED | CS02_00_CLCK_1024 )
		;ldi		temp0,(0<<FOC0 | WGM01_0_MODE_2_CTC | COM01_COM00_NORMAL_OC0_DISCONNECTED | CS02_00_CLCK_8 )
		out		TCCR0,temp0

	ret	//End fx()
*****************************************************************************************************************/
    #include "Includes/InitializeAllModules.h"
    #include "main.h"
    /***********************************************************************************************
    Las definiciones y las macros pueden tomar en cualquier momento nuevos valores
    validos para cualquier punto del programa siempre y cuando se corresponda
    i.e:	CS02_00_CLCK_64 = PRESCALER_TCNT0_64
    en cuanto a una nueva configuraci�n en TCCR0 (Timer Counter Control Register0)
	
	TIMER0_COMP_MATCH_INTERRUPT: ms interrupt MAX 32ms@8MHz/16ms@16MHz
    
	//............................................................................
	2012: Ahora es cambiado a 1ms de interrupcion
	
	**********************************************************************************************/
	
	void InitTCNT0(void)
	{
		//Inicializaci�n x CTC
	    //OCR0 =	KTE_TIME_FOR_CTC( TKTE_CTC_TCNT0, PRESCALER_TCNT0_1024 );   //MaxValue:16ms@16MHz /32ms@8MHz
		OCR0 =	KTE_TIME_FOR_CTC( 0.125*ms, PRESCALER_TCNT0_1024 );   //MaxValue:16ms@16MHz /32ms@8MHz
        TCCR0 = (0<<FOC0 | WGM01_0_MODE_2_CTC | COM01_COM00_NORMAL_OC0_DISCONNECTED | CS02_00_CLCK_1024 );
		//
	}
    /**********************************************************************************************
    TIMER0_COMP_MATCH_INTERRUPT: ms interrupt MAX 32ms@8MHz/16ms@16MHz
    **********************************************************************************************/
	ISR(TIMER0_COMP_vect)
    {
		volatile static byte __CounterAccess1__;//x c/5ms
		volatile static byte __CounterAccess2__;//x5x4 = c/20 ms

		//_________________________________________________________________________________________	
		if (++__CounterAccess1__ >= 40)	//__CounterAccess1__ c/5ms
		{	
			__CounterAccess1__ = 0;
			//------------------------------------
			
            isr_flag.f40ms = 1;//added 2021
            
			//KB_KeyboardProcess();//go to Shell_5.c
			
			#ifdef _BUZZER_
			if (Buzzer.bfBuzzer.SoundEnable)
				{BuzzerScheduler();}
			#endif
			
//			if (bfCommonProcess0.Timmer_BlinkCaption)
//				{TimmingHandler_BlinkCaption();}
//			//
//			TIMER0_IsActiveFading();		//PeriodicCallTo_FadingProcess
//            Timmer_TimmingToBackScene();	//Retornar despues de x seg. a escena donde se encontraba.
//			ScheduleTimmerKeepAlive_BLGLCD();

			//++++++++++
			//con 20ms de acceso, se cubre (max 8-bits)255*20ms = 5100ms = 5,1s q cubre las necesidades para el tiempo
			//de fading y para delays x procesos como delays
			
			if (++__CounterAccess2__ >= 4)	//__CounterAccess1__ c/5 * 4 = c/20ms
			{
				__CounterAccess2__ = 0;
				
				//=====================================================
				//x MenuSelectDimmNoDimmLoad.c
				if ( ((_timmer_nb*)p0_this_timmer_nb)[0].run == 1)		
				{
					((_timmer_nb*)p0_this_timmer_nb)[0].counter++;
				}
				
				//=====================================================
				//x MenuEscenas.c
				if ( ((_timmer_nb*)p1_this_timmer_nb)[0].run == 1)// >
				{
					((_timmer_nb*)p1_this_timmer_nb)[0].counter++;
				}
					
				if ( ((_timmer_nb*)p1_this_timmer_nb)[1].run == 1)// <
				{
					((_timmer_nb*)p1_this_timmer_nb)[1].counter++;
				}
					
				if ( ((_timmer_nb*)p1_this_timmer_nb)[2].run == 1)// [ok]
				{
					((_timmer_nb*)p1_this_timmer_nb)[2].counter++;
				}
				
				//=====================================================
				//x delete scenes.c
				if ( ((_timmer_nb*)p2_this_timmer_nb)[0].run == 1)// >
				{
					((_timmer_nb*)p2_this_timmer_nb)[0].counter++;
				}
				
				if ( ((_timmer_nb*)p2_this_timmer_nb)[1].run == 1)// <
				{
					((_timmer_nb*)p2_this_timmer_nb)[1].counter++;
				}
				
				if ( ((_timmer_nb*)p2_this_timmer_nb)[2].run == 1)// [ok]
				{
					((_timmer_nb*)p2_this_timmer_nb)[2].counter++;
				}
				//=====================================================
			}			
			//++++++++++
		}		
		
		SchedulerEvent_PWM_BLGLCD();		//ejecutado c/0.125ms
	}
