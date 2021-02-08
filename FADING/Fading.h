/*
 * Fading.h
 *
 * Created: 16/04/2012 07:41:27 p.m.
 *  Author: jcaf
 */ 


#ifndef FADING_H_
#define FADING_H_

 /*
 * Fading_1.c
 *
 * Created: 16/04/2012 07:41:17 p.m.
 *  Author: jcaf
 */ 
 	 struct _ps_fading_inbk
	 {
		 struct bf_fading_bk
		 {
			 unsigned timmer_active:1;
			 unsigned sign_new_tick:1;
			 unsigned printdisplay:1;
			 unsigned _none:5;
		 }bf;
		 
	 };
	 extern volatile struct _ps_fading_inbk ps_fading_inbk;
 
 	void FindKtesOfTimeToExcFading_And_SignNewInitOfFadingZone(byte zone);
	void fadingprocess_inzone(byte zone);
	void do_fadingprocess_allzone(void);
	BOOL is_fadingprocess_allzone_finish(void);

#endif /* FADING_H_ */