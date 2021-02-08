/*
 * MenuSelectDimmNoDimmLoad.h
 *
 * Created: 7/24/2012 5:29:44 PM
 *  Author: jcaf
 */ 
#ifndef MENUSELECTDIMMNODIMMLOAD_H_
#define MENUSELECTDIMMNODIMMLOAD_H_
	
	typedef enum
	{
		_XY_YINIT_						= (24),
		_XY_RADIO_DIVISION_VERT_		= (17),
		
		_XY_Y_RADIOBUTTON_NODIMMABLE_	= (_XY_YINIT_),
		_XY_Y_RADIOBUTTON_DIMMABLE_		= (_XY_YINIT_+_XY_RADIO_DIVISION_VERT_),
		
		_NUM_RADIO_THIS_GROUP_SDNDL_ = (2),

	}KTES_RADIOBUTTON_SDNDL;


	typedef struct _ClassRadioGroup_SDNDL_
	{
		struct _Radio_xy_SDNDL
		{	byte x;
			byte y;
			//byte NameOfRadio;//puntero -> FLASH
			//byte Align; //alineacion del texto respecto al radio
		}Radio_xy[(KTES_RADIOBUTTON_SDNDL)_NUM_RADIO_THIS_GROUP_SDNDL_];
	
		signed char idxOfgroup;
		signed char idxOfgroup_old;
		//_ZONE_TypeOfLoad idxOfgroup;
		//_ZONE_TypeOfLoad idxOfgroup_old;
		
		
		byte NumRadiosThisGroup;

	}_ClassRadioGroup_SDNDL;
	
	extern _ClassRadioGroup_SDNDL ObjRadioGroup_SDNDL[NUM_ZONAS];
	
	//fx propias de la clase: metodos
	void DrawOuterRadioButtonThisGroup(_ClassRadioGroup_SDNDL *pObjRadioGroup);
	void InitRadio_xy(_ClassRadioGroup_SDNDL *pObjRadioGroup, byte idxOfgroup, byte x, byte y);
	void SetCheckedRadio(_ClassRadioGroup_SDNDL *pObjRadioGroup);
	
	//fx propias del proceso 
	void RG_SDNDL_Init_AllRadios(void);
	void RG_SDNDL_DrawOuter_AllRadios(void);

	void RG_SDNDL_Menu(void);

//por ahora
extern volatile void *p0_this_timmer_nb;

#endif /* MENUSELECTDIMMNODIMMLOAD_H_ */