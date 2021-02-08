/*
 * MenuScene.h
 *
 * Created: 9/20/2012 3:36:28 PM
 *  Author: JCaf
 */ 


#ifndef MENUSCENE_H_
#define MENUSCENE_H_
	
	#define SOFTCENTRICCLEAR	(0)
	#define DIRECTCLEAR			(1)
	#define CLEAR_BETWEEN_PREVIEWSCENE (DIRECTCLEAR)
	//#define CLEAR_BETWEEN_PREVIEWSCENE (SOFTCENTRICCLEAR)
	
	void scene_handler(void);

extern volatile void *p1_this_timmer_nb;


void Timmer_TimmingToBackScene(void);	//usado solo por ahora, mejorar sistematicamente el delay

#endif /* MENUSCENE_H_ */