/*
 * RadioButton_1.c
 *
 * Created: 7/26/2012 8:44:00 PM
 *  Author: jcaf
 */ 
#include "Includes/InitializeAllModules.h"

	#define _WRITE_RADIO_ (BLACK)
	#define _CLEAR_RADIO_ (WHITE)
	/******************************************************************************************************************
	******************************************************************************************************************/
	void CheckUncheckRadio(byte x, byte y, byte _WRITEorCLEAR_RADIO_)
	{
		ks0108DrawCircle(x, y, 1, _WRITEorCLEAR_RADIO_);
		ks0108SetDot(x, y, _WRITEorCLEAR_RADIO_);
	}
	/******************************************************************************************************************
	******************************************************************************************************************/
	#define WriteRadio(x,y) do{CheckUncheckRadio(x,y,_WRITE_RADIO_);}while(0)
	#define ClearRadio(x,y) do{CheckUncheckRadio(x,y,_CLEAR_RADIO_);}while(0)
	/******************************************************************************************************************
	******************************************************************************************************************/
	#define DrawOuterRadioButton(x,y) do{ks0108DrawCircle(x, y, 3, BLACK);}while(0)
	/******************************************************************************************************************
	******************************************************************************************************************/
	void SetCheckedRadio(_ClassRadioGroup_SDNDL *pObjRadioGroup)//Reemplazar _ClassRadioGroup_ por corresp. clase a usar
	{
		signed char idxOfgroup		= pObjRadioGroup->idxOfgroup;
		signed char idxOfgroup_old	= pObjRadioGroup->idxOfgroup_old;
		byte i;
		
		if (idxOfgroup >=0)
		{
			if (idxOfgroup_old >=0)
				{ClearRadio(pObjRadioGroup->Radio_xy[idxOfgroup_old].x, pObjRadioGroup->Radio_xy[idxOfgroup_old].y);}
			WriteRadio(	pObjRadioGroup->Radio_xy[idxOfgroup].x, pObjRadioGroup->Radio_xy[idxOfgroup].y);
		}
		else 
		{
			for (i=0; i<(pObjRadioGroup->NumRadiosThisGroup); i++)	//uncheck all items
				{ClearRadio(pObjRadioGroup->Radio_xy[i].x, pObjRadioGroup->Radio_xy[i].y);}
		}
		pObjRadioGroup->idxOfgroup_old = idxOfgroup;
	}
	/******************************************************************************************************************
	******************************************************************************************************************/
	void InitRadio_xy(_ClassRadioGroup_SDNDL *pObjRadioGroup, byte idxOfgroup, byte x, byte y)//Reemplazar _ClassRadioGroup_ por corresp. clase a usar
	{
		pObjRadioGroup->Radio_xy[idxOfgroup].x = x;
		pObjRadioGroup->Radio_xy[idxOfgroup].y = y;
	}
	/******************************************************************************************************************
	******************************************************************************************************************/		
	void DrawOuterRadioButtonThisGroup(_ClassRadioGroup_SDNDL *pObjRadioGroup)//Reemplazar _ClassRadioGroup_ por corresp. clase a usar
	{
		byte idxOfgroup;
			for (idxOfgroup=0; idxOfgroup< (pObjRadioGroup->NumRadiosThisGroup); idxOfgroup++)
				{DrawOuterRadioButton(pObjRadioGroup->Radio_xy[idxOfgroup].x, pObjRadioGroup->Radio_xy[idxOfgroup].y);}
	}
