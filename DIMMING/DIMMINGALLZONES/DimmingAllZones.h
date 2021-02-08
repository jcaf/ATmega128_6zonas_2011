/*
 * DimmingAllZones.h
 *
 * Created: 19/10/2012 08:56:44 a.m.
 *  Author: JCaf
 */ 


#ifndef DIMMINGALLZONES_H_
#define DIMMINGALLZONES_H_

	void DAZ_key1_1fmode0(void);
	void DAZ_key2_1fmode0(void);
	void DAZ_key3_1fmode0(void);
	void DAZ_key3_1fmode0_aft(void);
	void DAZ_key4_1fmode0(void);

	#define TORIGHT (+1)
	#define TOLEFT 	(-1)
	
	//void DAZ_selectzone(signed char dir);
	
	
	extern struct _DAZ_thisps DAZ_thisps;

#endif /* DIMMINGALLZONES_H_ */