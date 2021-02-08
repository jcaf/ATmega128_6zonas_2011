/*
 * Blinking_2.c
 * Blinking_1.c ha sido dejado. 
 
 Esta version (2) permite que _BLINK_STOP_ sea directo.
 
 NO DEBE EXISTIR CODIGO QUE ACCEDA A GLCD DESDE INTERRUPCION. Solo de esta manera el recurso se comparte
 correctamente.
 
 *
 * Created: 5/31/2012 7:10:13 PM
 *  Author: jcaf
 */ 

#include "Includes/InitializeAllModules.h"

	volatile _ObjBlink ObjBlink_CaptionOfBarZone[NUM_ZONAS];
	
	/*************************************************************************************
	*************************************************************************************/
	#define _BLINK_RUN_		(1)
	#define _BLINK_STOP_	(0)
	
	#define _ALLOW_ACCESS_	(1)	
	#define _DENY_ACCESS_	(0)	
	
	#define _TOGG_IS_PRINT_TEXT_ (0)
	//#define _TOGG_IS_CLEAR_TEXT_ (1)
	#define _TOGG_IS_CLEAR_TEXT_ (~_TOGG_IS_PRINT_TEXT_)
	
	#define _NEXT_TOGG_WILLBE_PRINT_TEXT_ (_TOGG_IS_CLEAR_TEXT_)
	#define _NEXT_TOGG_WILLBE_CLEAR_TEXT_ (_TOGG_IS_PRINT_TEXT_)
	
	static inline void ObjBlink_CaptionOfBarZone_BlinkingRun(byte idx);
	
	/*************************************************************************************
	*************************************************************************************/
	void ObjBlink_Timming_CaptionOfBarZone(void)
	{
		byte idx;
		
		for (idx=0; idx<NUM_ZONAS; idx++)
		{
			if (ObjBlink_CaptionOfBarZone[idx].bfBlink.RunStop == _BLINK_RUN_)
			{
				ObjBlink_CaptionOfBarZone_BlinkingRun(idx);	//inline
				
				ObjBlink_CaptionOfBarZone[idx].bfBlink.Block_EnterToStop = _ALLOW_ACCESS_;
			}
			//else {} //_BLINK_STOP_
		}
	}
	
	/*************************************************************************************
	probar con 200ms de blinking... si es aceptable. cambiar de word->byte
	*************************************************************************************/
	#define _KTE_TIME_BLINKING_CAPTIONOFBARZONE_ (500/5)	// div by T-int

	/*************************************************************************************
	*************************************************************************************/
	void ObjBlink_CaptionOfBarZone_InitAllCounterTimer(void)
	{
		byte idx;
		for (idx=0;idx<NUM_ZONAS;idx++)
			ObjBlink_CaptionOfBarZone[idx].CounterTimmer = (_KTE_TIME_BLINKING_CAPTIONOFBARZONE_-1);	
	}
	/*************************************************************************************
	*************************************************************************************/
	static inline void ObjBlink_CaptionOfBarZone_BlinkingRun(byte idx)
	{
		if (++ObjBlink_CaptionOfBarZone[idx].CounterTimmer == _KTE_TIME_BLINKING_CAPTIONOFBARZONE_)
		{
			ObjBlink_CaptionOfBarZone[idx].CounterTimmer = 0;

			//ObjBlink_CaptionOfBarZone[idx].bfBlink.TogglingBlink= !ObjBlink_CaptionOfBarZone[idx].bfBlink.TogglingBlink;
			ObjBlink_CaptionOfBarZone[idx].TogglingBlink = ~ObjBlink_CaptionOfBarZone[idx].TogglingBlink;

			//_________________________________________________________________________________________________________
			
			ks0108SelectFont(SC, ks0108ReadFontData, BLACK);
			//ks0108SelectFont(Arial_Bold_14, ks0108ReadFontData, BLACK);
				
			//if (ObjBlink_CaptionOfBarZone[idx].bfBlink.TogglingBlink == _TOGG_IS_PRINT_TEXT_)
			if (ObjBlink_CaptionOfBarZone[idx].TogglingBlink == _TOGG_IS_PRINT_TEXT_)
			{
				ks0108GotoXY(vBAR_PSC_BASE_X_MD6Z[idx], 2);
				ks0108Puts_P(PSTR("Z"));	
				ks0108PutChar( (idx+1) + 0x30 );
			}
			else //_TOGG_IS_CLEAR_TEXT_
			{
				//ks0108FillRect(vBAR_PSC_BASE_X_MD6Z[idx], 2, 15, SC_HEIGHT-1, WHITE);
				ks0108FillRect(vBAR_PSC_BASE_X_MD6Z[idx], 1, 15, SC_HEIGHT-2, WHITE);
			}
			//_________________________________________________________________________________________________________
		}
	
	}
	
	/******************************************************************************
	//Blink Stop all
	******************************************************************************/
	void blink_captionof_barzone_STOPALL(void)
	{	
		byte i;
		for (i=0; i<NUM_ZONAS; i++)	{blink_captionof_barzone_STOP(i);}
	}
	/******************************************************************************
	//Blink Run all
	******************************************************************************/
	void blink_captionof_barzone_RUNALL(void)
	{	
		byte i;
		//for (i=0; i<NUM_ZONAS; i++)	{ObjBlink_CaptionOfBarZone[i].bfBlink.RunStop = _BLINK_RUN_;}
		for (i=0; i<NUM_ZONAS; i++)	{blink_captionof_barzone_RUN(i);}
	}

	/*************************************************************************************
	BLINK_STOP deja a su contador listo para "blankearse" la prox.vez q se re-utilice
			
	*************************************************************************************/
	void blink_captionof_barzone_STOP(byte idx)
	{
		ObjBlink_CaptionOfBarZone[idx].bfBlink.RunStop = _BLINK_STOP_;
		
		if (ObjBlink_CaptionOfBarZone[idx].bfBlink.Block_EnterToStop == _ALLOW_ACCESS_)
		{
			ObjBlink_CaptionOfBarZone[idx].bfBlink.Block_EnterToStop = _DENY_ACCESS_;
			//
			//ks0108SelectFont(SC, ks0108ReadFontData, BLACK);	
		
			ks0108GotoXY(vBAR_PSC_BASE_X_MD6Z[idx],2);
			ks0108Puts_P(PSTR("Z"));
			ks0108PutChar((idx+1) + 0x30);
		
			//
			//ObjBlink_CaptionOfBarZone[idx].bfBlink.TogglingBlink = _NEXT_TOGG_WILLBE_CLEAR_TEXT_;
			ObjBlink_CaptionOfBarZone[idx].TogglingBlink = _NEXT_TOGG_WILLBE_CLEAR_TEXT_;
			
			//Se deja listo para "blankearse" la prox.vez q se re-utilice
			ObjBlink_CaptionOfBarZone[idx].CounterTimmer = (_KTE_TIME_BLINKING_CAPTIONOFBARZONE_-1);//0;
		}		
	
	}
