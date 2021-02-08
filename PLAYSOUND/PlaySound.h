/*
 * PlaySound.h
 *
 * Created: 7/19/2012 12:52:42 PM
 *  Author: jcaf
 */ 


#ifndef PLAYSOUND_H_
#define PLAYSOUND_H_
	
	typedef enum{
		_BUZZER_SIMPLE_SOUND0_=0,
		_BUZZER_ACCEPT_SOUND0_
	}BUZZER_SOUNDS;
	
	#define SOUND_BUZZER	(0)
	#define SOUND_ISD4004	(1)
	
	void playsound(byte soundsystem, byte sound);

#endif /* PLAYSOUND_H_ */