/*
* Timmer_nb_1.c
*
* Created: 11/6/2012 10:04:57 AM
*  Author: jcaf
*/ 
#include "Includes/InitializeAllModules.h"
	
	//Counter is incremeted in interrupt()
	
	//atomic or use byte variable -> byte variable for get more time using 8-bit var
	void timmer_nb__processing(void *this_timmer_nb, word MAX)
	{
		byte i;
		TimmerXb counter;
		byte sreg_temp;
	
		for (i=0;i<	MAX;i++)
		{
			if ( ((_timmer_nb *)this_timmer_nb)[i].run == 1)
			{
				if (sizeof(TimmerXb) > 1)
				{	sreg_temp = SREG;//atomic
					cli();	
				}
				
				counter = ((_timmer_nb *)this_timmer_nb)[i].counter;

				if (sizeof(TimmerXb) > 1)//atomic
				{	SREG = sreg_temp;	}									
				
				//if ( ((_timmer_nb *)this_timmer_nb)[i].counter >= ((_timmer_nb *)this_timmer_nb)[i].time )
				
				//con 20ms de acceso, se cubre (max 8-bits)255*20ms = 5100ms = 5,1s q cubre las necesidades para el tiempo
				//de fading y para delays x procesos como delays
				
				if ( counter >= ((_timmer_nb *)this_timmer_nb)[i].time )
				{
					((_timmer_nb *)this_timmer_nb)[i].run = 0;
					//
					((_timmer_nb *)this_timmer_nb)[i].counter = 0x0;
					((_timmer_nb *)this_timmer_nb)[i].sm_app++;//evolution of variable
				}	
			}
		}				
	}

	void timmer_nb__reset_counter(_timmer_nb * timmer_nb)
	{	timmer_nb->counter = 0x00; }

	///hi
	///<summary>
	///This is a description of my function.
	///</summary>
	void timmer_nb__reset_sm_app(_timmer_nb * timmer_nb)
	{	timmer_nb->sm_app =0x00; }	

	void timmer_nb__set_time(_timmer_nb *timmer_nb, word time)
	{	timmer_nb->time = time; }



