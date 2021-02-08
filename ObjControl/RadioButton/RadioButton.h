/*
 * RadioButton.h
 *
 * Created: 7/26/2012 8:44:09 PM
 *  Author: jcaf
	esta es una clase plantilla, no se usa directamente, se copia y se dan los parametros necesarios
 */ 
#ifndef RADIOBUTTON_H_
#define RADIOBUTTON_H_
	
	//Existiran tantas copias de esta clase como cuantos radios de diferentes numero de radios x grupo se necesita
	
		typedef enum
		{
			//_XY_YINIT_						= (23),
			//_XY_RADIO_DIVISION_VERT_		= (17),
			//_XY_Y_RADIOBUTTON_NODIMMABLE_	= (_XY_YINIT_),
			//_XY_Y_RADIOBUTTON_DIMMABLE_		= (_XY_YINIT_+_XY_RADIO_DIVISION_VERT_),
			//
			__NUM_RADIOS_THIS_GROUP0__ = 2,	//minimo 2 items
			
		}__KTES_RADIOBUTTON0__;
	
	typedef struct _ClassRadioGroup0_
	{
		struct _Radio_xy
		{	byte x;
			byte y;
			//byte NameOfRadio;//puntero -> FLASH
			//byte Align; //alineacion del texto respecto al radio
		}Radio_xy[(__KTES_RADIOBUTTON0__)__NUM_RADIOS_THIS_GROUP0__];
		
		signed char idxOfgroup;
		signed char idxOfgroup_old;
		byte NumRadiosThisGroup;	//_NUM_RADIO_THIS_GROUP_SDNDL_

	}_ClassRadioGroup0;
	
	//void DrawOuterRadioButtonThisGroup(_ClassRadioGroup_ *pObjRadioGroup)/*Reemplazar _ClassRadioGroup_ por corresp. clase a usar */;
	//void InitRadio_xy(_ClassRadioGroup_ *pObjRadioGroup, byte idxOfgroup, byte x, byte y)/*Reemplazar _ClassRadioGroup_ por corresp. clase a usar */;
	//void SetCheckedRadio(_ClassRadioGroup_ *pObjRadioGroup)/*Reemplazar _ClassRadioGroup_ por corresp. clase a usar */;

#endif /* RADIOBUTTON_H_ */