#include "Includes/InitializeAllModules.h"

#ifdef _BUZZER_

	volatile _Buzzer Buzzer;

	void Buzzer_SimpleSound0(void);
	void Buzzer_AcceptSound0(void);

	/*************************************************************************	
	*************************************************************************/
	void InitBuzzer(void)
	{
		Buzzer.bfBuzzer.SoundEnable = ON;//ON;	//ON;		//Configurable x software
		ConfigOutputPin(DDRxBUZZER, BUZZER_pinCTRL);	
	}

	/*************************************************************************	
	main-line
	*************************************************************************/
	//#define BuzzerDisable()	do{BUZZER_OFF();Buzzer.bfBuzzer.SoundEnable=OFF;}while(0) //main-line

	/*************************************************************************	
	*************************************************************************/
	void BuzzerScheduler(void)
	{
		if (Buzzer.bfBuzzer.Play)	
		{
			if (Buzzer.ubfBuzzerAutoex.bfBuzzerSoundsAutoex.SimpleSound0)
				{Buzzer_SimpleSound0();}
			else if (Buzzer.ubfBuzzerAutoex.bfBuzzerSoundsAutoex.AcceptSound0)
				{Buzzer_AcceptSound0();}
		}
	}
	/*************************************************************************	
	Scheduler 0 reset all set-variables
	*************************************************************************/
	void Buzzer_SimpleSound0(void)	
	{
		//if (Buzzer.bfBuzzer.Play)
		//{
			if (Buzzer.scheduler == 0)
			{
				Buzzer.Counter0 = 0x00;//Reset all set-variables

				BUZZER_ON();
				Buzzer.scheduler++;
			}
			if (Buzzer.scheduler == 1)					
			{
				if (++Buzzer.Counter0 >= 8)//@5ms
				{
					BUZZER_OFF();
					Buzzer.Counter0 = 0x00;
					Buzzer.scheduler = 0;
					Buzzer.ubfBuzzerAutoex.bfBuzzerSoundsAutoex.SimpleSound0 =0;
					Buzzer.bfBuzzer.Play = 0;
				}	
			}
		//}
	}
	/*************************************************************************	
	*************************************************************************/
	void Buzzer_AcceptSound0(void)
	{
		//if (Buzzer.bfBuzzer.Play)
		//{
			if (Buzzer.scheduler == 0)
			{
				Buzzer.Counter0 = 0x00;	//Reset all set-variables
				Buzzer.Counter1 = 0x00;
				Buzzer.scheduler++;		
			}			

			if (Buzzer.scheduler == 1)
			{
				BUZZER_ON();
				
				Buzzer.Counter1++;				//numero de pasadas
				
				if (Buzzer.Counter1 == 1)
				{	Buzzer.Counter2 = 3;		//tiempo en ON
					Buzzer.Counter3 = 13;		//tiempo en OFF
				}
				else if (Buzzer.Counter1 == 2)
				{	Buzzer.Counter2 = 6;		//tiempo en ON
					Buzzer.Counter3 = 12;		//tiempo en OFF
				}
				else if (Buzzer.Counter1 == 3)
				{	Buzzer.Counter2 = 30;		//tiempo en ON
					Buzzer.Counter3 = 0;		//tiempo en OFF
				}
				Buzzer.scheduler++;
			}
			
			if (Buzzer.scheduler == 2)
			{
				if (++Buzzer.Counter0 == Buzzer.Counter2)//@5ms
				{	
					Buzzer.Counter0 = 0x00;
					BUZZER_OFF();
					Buzzer.scheduler++;
				}
			}
			
			if (Buzzer.scheduler == 3)
			{
				if (Buzzer.Counter1 < 3)
				{
					if (++Buzzer.Counter0 == Buzzer.Counter3)
					{	
						Buzzer.Counter0 = 0;
						Buzzer.scheduler = 1;	//loop cycle
					}
				}
				else
				{
					Buzzer.bfBuzzer.Play = 0;
					Buzzer.Counter1 = 0;
					Buzzer.scheduler = 0;
				}
			}
		//}
	}

#endif
