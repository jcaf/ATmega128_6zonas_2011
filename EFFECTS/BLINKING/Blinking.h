/*
 * Blinking.h
 *
 * Created: 5/31/2012 7:10:27 PM
 *  Author: jcaf
 */ 
#ifndef BLINKING_H_
#define BLINKING_H_

	typedef struct _ObjBlink_
	{
		word CounterTimmer;

		byte TogglingBlink;
		
		struct _bfBlink
		{	
			unsigned RunStop:1;
			unsigned Block_EnterToStop:1;
			//unsigned TogglingBlink:1;	//x reducir codigo uso complemento de byte
			unsigned _xxx:6;
		}bfBlink;
		
	
		//byte Posicion;	//DON'T USE por ahora se usa un vector global para acceder
	
	}_ObjBlink;

	
	extern volatile _ObjBlink ObjBlink_CaptionOfBarZone[NUM_ZONAS];
	
	/*************************************************************************************
	*************************************************************************************/
	#define _BLINK_RUN_		(1)
	#define _BLINK_STOP_	(0)
	
	void ObjBlink_CaptionOfBarZone_InitAllCounterTimer(void);
	
	#define blink_captionof_barzone_RUN(zone) do{ObjBlink_CaptionOfBarZone[zone].bfBlink.RunStop = _BLINK_RUN_;}while(0)
	void blink_captionof_barzone_STOP(byte idx);
	void blink_captionof_barzone_RUNALL(void);
	void blink_captionof_barzone_STOPALL(void);
	
	void ObjBlink_Timming_CaptionOfBarZone(void);

#endif /* BLINKING_H_ */