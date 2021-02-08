/*
 * CommonToProcess.h
 *
 * Created: 19/10/2012 07:27:16 p.m.
 *  Author: JCaf
 */ 


#ifndef COMMONTOPROCESS_H_
#define COMMONTOPROCESS_H_

	struct _crossover_scene_zone
	{
		unsigned from_zone:1;
		unsigned from_scene:1;
		unsigned __none:6;
	};
	extern struct _crossover_scene_zone crossover_scene_zone;


#endif /* COMMONTOPROCESS_H_ */