/*
 * PlaySound_1.c
 *
 * Created: 7/19/2012 12:52:32 PM
 *  Author: jcaf
 */ 
#include "Includes/InitializeAllModules.h"

	/*********************************************************
	*********************************************************/
	void playsound(byte soundsystem, byte sound)
	{
		if (soundsystem == SOUND_BUZZER)
		{
			#ifdef _BUZZER_
			
			if (Buzzer.bfBuzzer.SoundEnable)
			{
				Buzzer.bfBuzzer.Play = 1;								//Time to sound Buzzer!
				Buzzer.ubfBuzzerAutoex.BuzzerSoundsAutoex = 1<<sound;	//Sound is autoexcluyente
				Buzzer.scheduler = 0;									//Resetting scheduler all reset in the state machine.See code
			}			
			
			#endif
		}
		if (soundsystem == SOUND_ISD4004)
		{
			
		}
	}
	