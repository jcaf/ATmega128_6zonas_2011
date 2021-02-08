/*
 * Dimming_1.c
 *
 * Created: 23/02/2012 10:58:21 p.m.
 *  Author: jcaf
 
 Uninitialized global variable are allocated from the BSS section and initialized to 0 by default. 
	
 */ 
#include "Includes/InitializeAllModules.h"

	//OCRnx= [OCRnxH:OCRnxL]
	volatile word *	vOCRnx_Zn[NUM_ZONAS]={&OCRnx_Z1,&OCRnx_Z2,&OCRnx_Z3,&OCRnx_Z4,&OCRnx_Z5,&OCRnx_Z6};

	volatile _DIMMING_FLAGS DIMMING_FLAGS;

	volatile byte NUM_ELEM_DENTRO_BAR = 44;
	volatile byte FACTOR_ESCALA_DIMMING = 3;		//Todas las barras comparten la misma escala para el menu actual en que se encuentre
	
	#define MAX_VAL_DUTYCYCLE (NUM_ELEM_DENTRO_BAR*FACTOR_ESCALA_DIMMING)

	/************************************************************************************************
	_NUM_ELEM_DENTRO_REC_ACTUAL_ y _FACTOR_ESCALA_DIMMING_ACTUAL_ Pueden ser cambiantes de acuerdo al 
	tipo de barras que se crean en el menu actual en que se crea.
	void UpdateDutyCycle_Zn(byte Zona, word CountDutycycle_Zn,byte _NUM_ELEM_DENTRO_REC_ACTUAL_ , byte _FACTOR_ESCALA_DIMMING_ACTUAL_)
	*(vOCRnx_Zn[Zona])= ((word)( ((-1023.0/(_NUM_ELEM_DENTRO_REC_ACTUAL_*_FACTOR_ESCALA_DIMMING_ACTUAL_))*CountDutycycle_Zn )+1023 ));	
	************************************************************************************************/
	void UpdateDutyCycle_Zn(byte Zona, word CountDutycycle_Zn)
	{
		*(vOCRnx_Zn[Zona])= ((word)( ((-1023.0/(MAX_VAL_DUTYCYCLE))*CountDutycycle_Zn )+1023 ));	
	}
	
	/******************************************************************************************
	******************************************************************************************/	
	word __If_FadingActive_ReturnNEXTDC_else_ReturnDC(byte zone)
	{
		if (objzone[zone].uFADINGPROC.bf.FadingActive)				
			{return objzone[zone].nextdcfading;}	//aun no llega al objetivo
		else
			{return objzone[zone].dc;}				//ya es estable
	}
	
	/******************************************************************************************
	sugerencia: renombrar funcion
	1.- Get dc
	2.- Mark level
	******************************************************************************************/
	void _MarkLevelTo_KeySetMode_TOGGLINGVAL(byte zone)
	{
		volatile word dc;
		
		if (objzone[zone].TypeOfLoad == Dimmable)
		{
			if (objzone[zone].TypeOfEffect == Fading)
			{
				dc = __If_FadingActive_ReturnNEXTDC_else_ReturnDC(zone);
			}
		}		
		else if (objzone[zone].TypeOfLoad == NoDimmable)
		{
			if (objzone[zone].TypeOfEffect == Direct)
			{
				dc = objzone[zone].dc;			
			}		
		}			
	
		if (dc <= 0)	//THRESHOLD
			{objzone[zone].SetLevel = Off100p;}
		else 
			{objzone[zone].SetLevel = Restore;}
	}
	
	/********************************************************************************************	
	********************************************************************************************/
	//void ConvertDC_InASCIIPorcent(_PARAMIn word DutyCycle, _PARAMOut char * PorcentDimmingOfZoneASCII)
	//{
		//double PorcentDimmingOfZone = (DutyCycle*100.0) /(double)(MAX_VAL_DUTYCYCLE) ;
		//sprintf(PorcentDimmingOfZoneASCII, "%.1f", PorcentDimmingOfZone);
	//}
	/********************************************************************************************	
	La velocidad de retorno esta ligada al tiempo de respuesta de GLCD, mientras mas rapida, mejor
	********************************************************************************************/
	void PrintPorcentOfDCLevel(word dutycycle)//@X,Y
	{
		char PorcentDimmingOfZoneASCII[7];
		
		//ConvertDC_InASCIIPorcent(_PARAMIn dutycycle, _PARAMOut PorcentDimmingOfZoneASCII);
		double PorcentDimmingOfZone = ((double)(dutycycle*100.0)) /((double)(MAX_VAL_DUTYCYCLE));
		sprintf(PorcentDimmingOfZoneASCII, "%.1f", PorcentDimmingOfZone);
	
		ks0108SelectFont(SC, ks0108ReadFontData, BLACK);
		
		ks0108FillRect(10,63-16,(SC_WIDTH*6) ,12,WHITE);	//limpiar
		ks0108GotoXY(10,63-16);	ks0108Puts(PorcentDimmingOfZoneASCII);ks0108Puts("%");//ks0108GotoXY(10+SC_WIDTH*5 +1,63-16);ks0108Puts("%");
	}
	/******************************************************************************************
	******************************************************************************************/
#define YBAS (59)
#define FACT_SCALE (3)

	void _PreEx_DimmingUp(byte zone)
	{
		if (objzone[zone].TypeOfLoad == Dimmable)	
		{
			if (objzone[zone].uFADINGPROC.bf.FadingActive==0)
			{
				if (objzone[zone].dc < (MAX_VAL_DUTYCYCLE) )	//44*3 = 132
				{
					objzone[zone].dc++;//_DimmingUp(zone);
					//
					if (objzone[zone].uCommonProcess.bfCommonProcess._PRINT_PORCENT_OF_DC_LEVEL_)
						{PrintPorcentOfDCLevel(objzone[zone].dc);}
					//
	//_MarkLevelTo_KeySetMode_TOGGLINGVAL(zone);
				}	
			}
		}
	}
	/******************************************************************************************
	******************************************************************************************/
	void _PreEx_DimmingDown(byte zone)
	{
		if (objzone[zone].TypeOfLoad == Dimmable)	
		{
			if (objzone[zone].uFADINGPROC.bf.FadingActive==0)
			{
				if (objzone[zone].dc > 0)
				{
					objzone[zone].dc--;//_DimmingDown(zone);
					
					//add
					if (objzone[zone].uCommonProcess.bfCommonProcess._PRINT_PORCENT_OF_DC_LEVEL_)
						{PrintPorcentOfDCLevel(objzone[zone].dc);}
					//
//_MarkLevelTo_KeySetMode_TOGGLINGVAL(zone);
				}
			}			
		}
	}
	//////////////////////////////////////////////////
	void drawthreshold(byte zone)
	{
		byte _qdiv;

		//ClearBar_Zone(zone);
		_qdiv = (byte)(objzone[zone].thrshld_sect/FACTOR_ESCALA_DIMMING);
		_qdiv = _qdiv*FACTOR_ESCALA_DIMMING;
		ks0108FillRect(vBAR_PSC_BASE_X_MD6Z[zone]+2,_PSC_Y_FINAL_PIXEL_RECT_-_qdiv,_BAR_PSC_BASE_W_-4, _qdiv-1, (_qdiv==0?WHITE:BLACK ));
	}
	/**************************************************************************************
	ON/OFF/RESTORE x ZONA
	**************************************************************************************/
	void GettingReadyForNewLevelOfDC_Zone(byte zone)
	{
		if (objzone[zone].InMode == KeySetMode_TOGGLINGVAL)
		{
			if (objzone[zone].TypeOfLoad == Dimmable)	
			{
				if (objzone[zone].SetLevel == Restore)
				{
					if (objzone[zone].TypeOfEffect == Fading)
					{
						objzone[zone].nextdcfading = objzone[zone].dcr;			   
						//si NextDutyCycleToFading es afectado-->>DUTYCYCLE al final tambien sera afectado
					
					}//else if (ObjZONEram[CurrentZone].TypeOfEffect == Direct)	{}
				}
				else if (objzone[zone].SetLevel == Off100p)
				{
					if (objzone[zone].TypeOfEffect == Fading)
					{
						//es necesario que minimamente, DUTYCYCLE SE HAYA MOVIDO, asi todo encaja correctamente
						//partiendo empezando desde un dimming+/-...es logico guardar el DUTYCYCLE actual en Restore
						objzone[zone].dcr = __If_FadingActive_ReturnNEXTDC_else_ReturnDC(zone);
						//
						objzone[zone].nextdcfading = 0;			   
						
					}//else if (ObjZONEram[CurrentZone].TypeOfEffect == Direct)	{}
				}					
			}
			else if	(objzone[zone].TypeOfLoad == NoDimmable)	
			{	
				if (objzone[zone].SetLevel == Restore)
				{
					if (objzone[zone].TypeOfEffect == Direct)				
					{
						 objzone[zone].dc = objzone[zone].dcr;
					}
				}					
				else if (objzone[zone].SetLevel == Off100p)
				{
					if (objzone[zone].TypeOfEffect == Direct)				
					{
						objzone[zone].dcr = objzone[zone].dc;
						objzone[zone].dc = 0;
					}
				}
			}
		}
		else if (objzone[zone].InMode == KeySetMode_MAXVAL)
		{
			if (objzone[zone].SetLevel == ON100p)
			{
				if (objzone[zone].TypeOfLoad == Dimmable)	
				{
					if (objzone[zone].TypeOfEffect == Fading)
					{
						objzone[zone].nextdcfading = (MAX_VAL_DUTYCYCLE);
					}
				}		
				else if (objzone[zone].TypeOfLoad == NoDimmable)	
				{
					if (objzone[zone].TypeOfEffect == Direct)				
					{
						objzone[zone].dc = (MAX_VAL_DUTYCYCLE);
					}
				}
			}
		}
	}
	
	/**************************************************************************************
	Updating DC ofZone AccodingToTheFeatures
	**************************************************************************************/
	void updatedc(byte zone)
	{
		if (objzone[zone].TypeOfLoad == Dimmable)	
		{
			if (objzone[zone].TypeOfEffect == Fading)
				{FindKtesOfTimeToExcFading_And_SignNewInitOfFadingZone(zone);}
		}							
		else if (objzone[zone].TypeOfLoad == NoDimmable)	
		{
			if (objzone[zone].TypeOfEffect == Direct)
				{UpdateDutyCycle_Zn(zone,objzone[zone].dc);}			
		}		
	}

	/**************************************************************************************
	**************************************************************************************/
	void __Parsing_UpdateBarZone_AccodingToTheFeatures(byte zone)
	{
		if (objzone[zone].TypeOfLoad == Dimmable)	
		{
			if (objzone[zone].TypeOfEffect == Fading)
			{
				//Progressive update for dimmable
				//ClearBar_Zone(CurrentZone);		//incluido dentro de UpdateBar_DirectShow_Zone		//progressive
				UpdateBar_DirectShow_Zone(zone, objzone[zone].nextdcfading);	//progressive
			}
		}							
		else if (objzone[zone].TypeOfLoad == NoDimmable)	
		{
			if (objzone[zone].TypeOfEffect == Direct)
			{
			    //ClearBar_Zone(CurrentZone);		//incluido dentro de UpdateBar_DirectShow_Zone		//direct
				UpdateBar_DirectShow_Zone(zone, objzone[zone].dc);				//direct
			}			
		}		
	}
	/**************************************************************************************
	**************************************************************************************/
	void __Parsing_PrintPorcentOfDCLevelZone_AccodingToTheFeatures(byte zone)	
	{
		if (objzone[zone].TypeOfLoad == Dimmable)	
		{
			if (objzone[zone].TypeOfEffect == Fading)
			{
				PrintPorcentOfDCLevel(objzone[zone].nextdcfading);//progressive
			}
		}							
		else if (objzone[zone].TypeOfLoad == NoDimmable)	
		{
			if (objzone[zone].TypeOfEffect == Direct)
			{
				PrintPorcentOfDCLevel(objzone[zone].dc);			//direct
			}			
		}		
	}
	
