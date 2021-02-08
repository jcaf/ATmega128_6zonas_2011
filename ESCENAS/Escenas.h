/*
 * Escenas.h
 *
 * Created: 05/03/2012 12:18:55 p.m.
 *  Author: jcaf
 */ 
#ifndef ESCENAS_H_
#define ESCENAS_H_

	#define _NUM_ESCENAS_MAXIMA_		(20)
	

	#define ISNOT_A_SAVED_SCENE (0xFF)
	
	//EEPROM
	typedef struct _objscene_commonprop_epp_
	{
		byte num_scene;						//ultima escena en uso
		byte totalofscenes;
	}_objscene_commonprop_epp;

	//EEPROM
	typedef struct _objstorage_scene_
	{
		byte num_name;					//graba el indice dentro del vector
		
		//TYPEDC dcs_ofscene[NUM_ZONAS];
		struct _objzone_objstorage_scene_
		{
			TYPEDC dc;
		}objzone[NUM_ZONAS];
		
	}_objstorage_scene;

	struct _ps_scene
	{
		byte totalofscenes;		//inicia desde 0
	};
	
	struct _currentscene
	{
		//signed char 
		byte num_scene;	
		byte num_name;				

		struct _objzone_currentscene
		{
			TYPEDC dc;
			}objzone[NUM_ZONAS];
	};
	
	struct _previewscene
	{
		signed char num_scene;	
		byte num_name;			
		TYPEDC dc_from_epp[NUM_ZONAS];
		
		PTRFXrVOID preview;
		PTRFXrVOID execute;
		PTRFXrVOID preview__bkframewnd;
	};
	
	extern volatile struct _currentscene currentscene;
	extern volatile struct _previewscene previewscene;
	extern volatile struct _ps_scene ps_scene;
	
	void init_scene(void);
	void _print_texts_scene(byte num_scene);
	void directclearall_barlevel_ofscene(void);
	
	TYPEDC get_dcofzone_ofscene_EEP(byte num_scene, byte zone);
	void set_dcofzone_ofscene_EPP(byte num_scene, byte zone, TYPEDC dc);
	
	void save_scene_epp(byte num_scene, byte num_name);
	void _all_dcs_taked_as_currentscene(void);
	
	//extern EEMEM _objstorage_scene objstorage_scene_epp[_NUM_ESCENAS_MAXIMA_];
	extern _objstorage_scene objstorage_scene_epp[_NUM_ESCENAS_MAXIMA_];
	
	//extern EEMEM _objscene_commonprop_epp objscene_commonprop_epp;
	extern _objscene_commonprop_epp objscene_commonprop_epp;

BOOL _all_dcs_of_currentscene__lessequalthan_threshold(void);// o <= 0x0	

BOOL _all_dcs_of_currentscene__areequalthan_current_dcs(void);// o <= 0x0

BOOL _all_dcs_of_objzone__equalthan_100porcent(void);//100%





#endif /* ESCENAS_H_ */
