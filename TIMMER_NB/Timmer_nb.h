/*
 * Timmer_nb.h
 *
 * Created: 11/6/2012 10:05:06 AM
 *  Author: jcaf
 */ 


#ifndef TIMMER_NB_H_
#define TIMMER_NB_H_
	
	#define _TIMMER_NB_8BITS_  (0)
	#define _TIMMER_NB_16BITS_ (1)
	
	#define _TIMMER_NB_XBITS_ (_TIMMER_NB_8BITS_)
	//#define _TIMMER_NB_XBITS_ (_TIMMER_NB_16BITS_)
	
	#if _TIMMER_NB_XBITS_ == _TIMMER_NB_8BITS_
		typedef byte TimmerXb;
	#elif _TIMMER_NB_XBITS_ == _TIMMER_NB_16BITS_
		typedef word TimmerXb;
	#endif
	
	typedef struct _timmer_nb_
	{
		
		//con 20ms de acceso, se cubre (max 8-bits)255*20ms = 5100ms = 5,1s q cubre las necesidades para el tiempo
		//de fading y para delays x procesos como delays
		
		//volatile
		TimmerXb counter;//individual volatile
		
		TimmerXb time;

		//volatile 
		byte sm_app;
		
		//volatile 
		byte run;
		//struct _bf_init{
			//unsigned init:1;
			//unsigned __none:7;
		//}bf;
		
	}_timmer_nb;
	//la declaracion de la structura sera volatile
	

	void timmer_nb__processing(void *this_timmer_nb, word MAX);
	void timmer_nb__reset_counter(_timmer_nb * timmer_nb);
	void timmer_nb__reset_sm_app(_timmer_nb * timmer_nb);
	void timmer_nb__set_time(_timmer_nb *timmer_nb, word time);

#endif /* TIMMER_NB_H_ */