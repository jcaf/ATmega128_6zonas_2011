/*
 * Fading_1.c
 *
 * Created: 16/04/2012 07:41:17 p.m.
 *  Author: jcaf
 */ 
#include "Includes/InitializeAllModules.h"

	#define MenorTiempoBaseDeTemporizacion_Fading	(5*ms)
	
	volatile struct _ps_fading_inbk ps_fading_inbk;
	
	void FindKtesOfTimeToExcFading_And_SignNewInitOfFadingZone(byte zone)
	{
		objzone[zone].sfading.diff = (int)objzone[zone].sfading.nextdcfading - (int)objzone[zone].dc;

		if (objzone[zone].sfading.diff != 0)
		{
			if ( objzone[zone].sfading.diff < 0)
			{	//
				objzone[zone].sfading.kte_addsub= -1;//dimming-down
				objzone[zone].sfading.diff *= -1;
				//
				if (objzone[zone].cfgmodeof_diLET_THRSHLD == (CFGMODEOF_DIMM_IN_LESSEQUALTHAN_THRSHLD)AUTOMATIC_BYPASS )
				{
					if (objzone[zone].sfading.nextdcfading <= objzone[zone].thrshld)
						{objzone[zone].sfading.diff -= objzone[zone].thrshld;}
				}
			}
			else
			{	//
				objzone[zone].sfading.kte_addsub = +1;//dimming-up
				//
				if (objzone[zone].cfgmodeof_diLET_THRSHLD == (CFGMODEOF_DIMM_IN_LESSEQUALTHAN_THRSHLD)AUTOMATIC_BYPASS )
				{
					if (objzone[zone].dc <= objzone[zone].thrshld)
					{
						objzone[zone].sfading.diff -= objzone[zone].thrshld;
						//
						if (objzone[zone].dc == 0) //va a ir de 0->mas OJO: se esta redundado al comprobar por if (objzone[zone].dc == 0)
						{
							if (ps_fading_inbk.bf.printdisplay == ENABLE)	//BUG FIXED 18 ENER 2013
							{							
							directfill_barlevel(zone, objzone[zone].thrshld);	//show/draw threshold	
							}													
						}	
					}
					
				}
			}
			word __temp = (word) round( (float)(objzone[zone].time_of_fading*1.0) /(float)(objzone[zone].sfading.diff) );
			objzone[zone].sfading.ticktime_of_fading =(word) round( (float)(__temp*1.0) / (MenorTiempoBaseDeTemporizacion_Fading*1E3));		//dividir por Tiempo INTERR= 5ms
			
			objzone[zone].sfading.counterof_ticktime_of_fading = 0x0000;			
			objzone[zone].sfading.counterof_diff = 0x0000;
			
			objzone[zone].sfading.bf.fading_active = ON;		//fading process sera quien apague el bit
			ps_fading_inbk.bf.timmer_active = ON;			//reusando flag	-> Timmer x app ON
		}
	}
	//////////////////////////////////////////////////////////////////////////
	//objzone[zone].sfading.counterof_diff++;//el minimo avance es 1
	//////////////////////////////////////////////////////////////////////////
	void fadingprocess_inzone(byte zone)
	{
		if (++objzone[zone].sfading.counterof_ticktime_of_fading >= objzone[zone].sfading.ticktime_of_fading)
		{	  objzone[zone].sfading.counterof_ticktime_of_fading = 0x0000;
			
			objzone[zone].sfading.counterof_diff++;
			objzone[zone].dc += objzone[zone].sfading.kte_addsub;	//dc ++ o -- 
			dimming(zone, objzone[zone].sfading.kte_addsub);		//updatedc(zone, objzone[zone].dc);
		}
		if ( objzone[zone].sfading.counterof_diff >= objzone[zone].sfading.diff)
			{objzone[zone].sfading.bf.fading_active = OFF;}
	}

	BOOL is_fadingprocess_allzone_finish(void)
	{
		byte zone;
		for (zone=0; zone<NUM_ZONAS; zone++)		
		{
			if (objzone[zone].sfading.bf.fading_active)
				{return 0;}
		}
		return 1;
	}