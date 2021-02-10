/*
 * Dimming_1.c
 *
 * Created: 23/02/2012 10:58:21 p.m.
 *  Author: jcaf
 
 Uninitialized global variable are allocated from the BSS section and initialized to 0 by default. 
	
 */ 
#include "Includes/InitializeAllModules.h"

//#include <math.h>
#include <stdlib.h>
	
	//OCRnx= [OCRnxH:OCRnxL]
	volatile word *	vOCRnx_Zn[NUM_ZONAS]={&OCRnx_Z1,&OCRnx_Z2,&OCRnx_Z3,&OCRnx_Z4,&OCRnx_Z5,&OCRnx_Z6};

	volatile byte NUM_ELEM_DENTRO_BAR = 44;
	volatile byte FACTOR_ESCALA_DIMMING = 3;		//Todas las barras comparten la misma escala para el menu actual en que se encuentre
	
	#define MAX_VAL_DUTYCYCLE (NUM_ELEM_DENTRO_BAR*FACTOR_ESCALA_DIMMING)

	/************************************************************************************************
	_NUM_ELEM_DENTRO_REC_ACTUAL_ y _FACTOR_ESCALA_DIMMING_ACTUAL_ Pueden ser cambiantes de acuerdo al 
	tipo de barras que se crean en el menu actual en que se crea.
	void UpdateDutyCycle_Zn(byte Zona, word CountDutycycle_Zn,byte _NUM_ELEM_DENTRO_REC_ACTUAL_ , byte _FACTOR_ESCALA_DIMMING_ACTUAL_)
	*(vOCRnx_Zn[Zona])= ((word)( ((-1023.0/(_NUM_ELEM_DENTRO_REC_ACTUAL_*_FACTOR_ESCALA_DIMMING_ACTUAL_))*CountDutycycle_Zn )+1023 ));	
	************************************************************************************************/
	void updatedc(byte zone, TYPEDC dc)
	{
		*(vOCRnx_Zn[zone]) = ((word)( ((-1023.0/(MAX_VAL_DUTYCYCLE))*dc )+1023 ));	
	}

	///////////////////////////////////////////////////////////////////////////////////////////////
	void _PreEx_DimmingUp(byte zone)
	{
		if (objzone[zone].TypeOfLoad == Dimmable)	
		{
			if (objzone[zone].sfading.bf.fading_active == OFF)
			{
				if (objzone[zone].dc < (MAX_VAL_DUTYCYCLE) )	//44*3 = 132
				{
					objzone[zone].dc++;
					dimming(zone, DIMMING_UP);
					
					//
					if (objzone[zone].bf.print_dcporcentz)
					{
						dcporcentz(objzone[zone].dc);
					}
					//
				}	
			}
		}
	}
	///////////////////////////////////////////////////////////////////////////////////////////////
	void _PreEx_DimmingDown(byte zone)
	{
		if (objzone[zone].TypeOfLoad == Dimmable)	
		{
			if (objzone[zone].sfading.bf.fading_active == OFF)
			{
				if (objzone[zone].dc > 0)
				{
					objzone[zone].dc--;
					//
					if ( objzone[zone].dc <= objzone[zone].thrshld) 
					{
						objzone[zone].onoffrstr.bf.pto_rstr = OFF;
					}
					//
					dimming(zone, DIMMING_DOWN);
					
					//add
					if (objzone[zone].bf.print_dcporcentz)
					{
						dcporcentz(objzone[zone].dc);
					}
					//
				}
			}			
		}
	}
	///////////////////////////////////////////////////////////////////////////////////////////////
	void dimming(byte zone, signed char dir)
	{
		if (dir == DIMMING_UP)
			{dimming_up(zone);}
		else 
			{dimming_down(zone);}
	}
	///////////////////////////////////////////////////////////////////////////////////////////////
	void dimming_up(byte zone)
	{	
		if (objzone[zone].cfgmodeof_diLET_THRSHLD == (CFGMODEOF_DIMM_IN_LESSEQUALTHAN_THRSHLD)AUTOMATIC_BYPASS )
		{
			if (objzone[zone].dc == 1)
			{
				objzone[zone].dc += objzone[zone].thrshld;
				playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);

				if (ps_fading_inbk.bf.printdisplay == ENABLE)	
				{
					directfill_barlevel(zone, objzone[zone].dc);	//draw threshold+dc
				}				
				goto _dimming_up_exit;
			}
		}

		graphbarlevel.write_barlevel(zone);
		
		_dimming_up_exit:
		//
		//if (objzone[zone].dc > objzone[zone].thrshld_sect)
			//{objzone[zone].laidsw = SECTION_GREATERTHAN_THRSHLD;}

		updatedc(zone , objzone[zone].dc);
	}
	///////////////////////////////////////////////////////////////////////////////////////////////
	void dimming_down(byte zone)
	{
		if (objzone[zone].dc <= objzone[zone].thrshld)
		{
			//objzone[zone].laidsw = SECTION_LESSEQUALTHAN_THRSHLD ;	
			//
			if (objzone[zone].cfgmodeof_diLET_THRSHLD == (CFGMODEOF_DIMM_IN_LESSEQUALTHAN_THRSHLD)AUTOMATIC_BYPASS )
			{
				if (objzone[zone].dc == objzone[zone].thrshld)
				{
					playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);

					if (ps_fading_inbk.bf.printdisplay == ENABLE)			
					{
						directclear_barlevel(zone, objzone[zone].thrshld + FACTOR_ESCALA_DIMMING);	//formalmente seria((byte)(thrshld_sect/FACTOR_ESCALA_DIMMING))+FACTOR_ESCALA_DIMMING 
					}
					objzone[zone].dc = 0;															//sumando +FACTOR_ESCALA_DIMMING asegura que agarra el sgte en la escala superior
					goto _dimming_down_exit;
				}
			}
		}		
		
		graphbarlevel.erase_barlevel(zone);
		
		_dimming_down_exit:
		
		updatedc(zone , objzone[zone].dc);
	}
	
	////////////////////////////////////////////////////////////////
	TYPEDC if_fadingactive_nextdc_else_dc(byte zone)//getting a stable dc
	{
		if (objzone[zone].sfading.bf.fading_active)
			{return objzone[zone].sfading.nextdcfading;}
		else
			{return objzone[zone].dc;}
	}
	////////////////////////////////////////////////////////////////
	void setting_preupdate_dc(byte zone, TYPEDC val_to_dc)//BUG FIXED word-> TYPEDC
	{
		if (objzone[zone].TypeOfLoad == Dimmable)
		{
			if (objzone[zone].TypeOfEffect == Fading)
				{objzone[zone].sfading.nextdcfading = val_to_dc;}
		}
		else if	(objzone[zone].TypeOfLoad == NoDimmable)
		{
			if (objzone[zone].TypeOfEffect == Direct)
				{objzone[zone].dc = val_to_dc;}
		}
	}

	void updatedc_acctypeofload(byte zone)	//Updating DC ofZone AccodingToTheFeatures
	{
		if (objzone[zone].TypeOfLoad == Dimmable)	
		{
			if (objzone[zone].TypeOfEffect == Fading)
				{FindKtesOfTimeToExcFading_And_SignNewInitOfFadingZone(zone);}
		}							
		else if (objzone[zone].TypeOfLoad == NoDimmable)	
		{
			if (objzone[zone].TypeOfEffect == Direct)
				{updatedc(zone,objzone[zone].dc);}			
		}		
	}
				
	///////////////////////////////////////////////////////////////////////////////////////////////
	//La velocidad de retorno esta ligada al tiempo de respuesta de GLCD, mientras mas rapida, mejor
	///////////////////////////////////////////////////////////////////////////////////////////////
	void dcporcentz(TYPEDC dc)
	{
		char porcent_ascii[10];
		
		//double porcent = ((double)(dc*100.0)) /((double)(MAX_VAL_DUTYCYCLE));
        float porcent = (dc*100.0) /MAX_VAL_DUTYCYCLE;
		
        //+-2011
        //sprintf(porcent_ascii, "%.1f", porcent);
		//itoa( (int)porcent, porcent_ascii, 10);
        //-+
        
        //2021
        dtostrf(porcent, 0,1, porcent_ascii);
		
		
		ks0108SelectFont(SC, ks0108ReadFontData, BLACK);
		
		ks0108FillRect(10,63-16,(SC_WIDTH*6) ,12,WHITE);	//limpiar
		ks0108GotoXY(10,63-16);	
		ks0108Puts(porcent_ascii);
		ks0108Puts("%");
	}
	
	//////////////////////////////////////////////////////////////////
	void _dcporcentz_acctypeofload(byte zone)	
	{
		if (objzone[zone].TypeOfLoad == Dimmable)	
		{
			if (objzone[zone].TypeOfEffect == Fading)
			{
				dcporcentz(objzone[zone].sfading.nextdcfading);
			}
		}							
		else if (objzone[zone].TypeOfLoad == NoDimmable)	
		{
			if (objzone[zone].TypeOfEffect == Direct)
			{
				dcporcentz(objzone[zone].dc);	
			}			
		}		
	}
	
	//////////////////////////////////////////////////////////////////
	//void for_nodimmable_directupdate_barlevel(byte zone)
	//{
		//if (objzone[zone].TypeOfLoad == NoDimmable)
		//{	if (objzone[zone].TypeOfEffect == Direct)
			//{	clear_and_directfill_barlevel(zone, objzone[zone].dc);}
		//}
	//}
	
	////////////////////////////////////////////////////////////////
	void RestoreOnOff_mode1(byte zone)
	{
		if (if_fadingactive_nextdc_else_dc(zone) > objzone[zone].thrshld)//if (objzone[zone].dc > objzone[zone].thrshld_sect)
		{
			if (if_fadingactive_nextdc_else_dc(zone) == MAX_VAL_DUTYCYCLE)//if (objzone[zone].dc == MAX_VAL_DUTYCYCLE)
			{
				if (objzone[zone].commingfrom == (COMMINGFROM)LASTEVENT_DIRECTONOFF)//viene desde fromdirectonoff
				{
					if (objzone[zone].onoffrstr.dcr < MAX_VAL_DUTYCYCLE)
					{
						setting_preupdate_dc(zone, objzone[zone].onoffrstr.dcr);//objzone[zone].dc = objzone[zone].onoffrstr.dcr;
						
						//ADD
						graphbarlevel.g[zone].bf.check_bar =1;
						//
						
						goto __exit_thisfx;
					}
				}
			}
			//para el resto de situaciones
			objzone[zone].onoffrstr.dcr = objzone[zone].dc;//if_fadingactive_nextdc_else_dc(zone); HUBIERA PODIDO SER,
															/*PERO YA NO CAPTURARIA EN ESE INSTANTE EL dutycycle EN JUEGO, SINO EL QUE
															EL USUARIO LO PUSO EN CAMINO DE SU DESEO PREVIO.
															En modo escena, al entrar captura el "if_fadingactive_nextdc_else_dc(zone);",
															esto hace q al apagar/restaurar, se guarde el dc en movimiento, y no con el q se capturo la escena,
															podria seguir asi, solo lo digo para tener en cuenta del porque no restauraria a la captura hecha al 
															entrar a escenas.
															*/
			
			//objzone[zone].onoffrstr.dcr = if_fadingactive_nextdc_else_dc(zone);
			
			objzone[zone].onoffrstr.bf.pto_rstr = ON;
			setting_preupdate_dc(zone, 0x00);//objzone[zone].dc = 0;
			
			//++add.
			graphbarlevel.g[zone].Qsaved = graphbarlevel.g[zone].Q;
			//++
		}
		else //<=
		{
			if (objzone[zone].onoffrstr.bf.pto_rstr == OFF) //if (objzone[zone].laidsw == SECTION_LESSEQUALTHAN_THRSHLD )
			{
				//direct, perdio su dcr al bajar a este punto
				if ( objzone[zone].cfgtorestore_atlevel== (CFGTORESTORE_ATLEVEL)MAXVAL)	//x default
				{
					setting_preupdate_dc(zone, MAX_VAL_DUTYCYCLE);				//objzone[zone].dc = MAX_VAL_DUTYCYCLE;
				}
				else if ( objzone[zone].cfgtorestore_atlevel == (CFGTORESTORE_ATLEVEL)THRESHOLD_MAS_1)
				{
					setting_preupdate_dc(zone, objzone[zone].thrshld+1);	//objzone[zone].dc = objzone[zone].thrshld_sect+1;
				}
			}
			else //else if (objzone[zone].laidsw == SECTION_GREATERTHAN_THRSHLD )
			{
				//ADD
				graphbarlevel.g[zone].bf.check_bar = 1;
				//
				setting_preupdate_dc(zone, objzone[zone].onoffrstr.dcr);//objzone[zone].dc = objzone[zone].onoffrstr.dcr;
				objzone[zone].onoffrstr.bf.pto_rstr = OFF;
			}
		}
		__exit_thisfx:
		
		//
		if (objzone[zone].TypeOfLoad == NoDimmable)	
			{clear_and_directfill_barlevel(zone, objzone[zone].dc);}
	
		if (objzone[zone].bf.print_dcporcentz)
			{_dcporcentz_acctypeofload(zone);}
		//

		updatedc_acctypeofload(zone);

		objzone[zone].commingfrom = (COMMINGFROM)LASTEVENT_CLEAR;
	}
	
	///////////////////////////////////////////////////////////////////////////
	void directOnOff_mode1(byte zone)
	{
		if (if_fadingactive_nextdc_else_dc(zone) < MAX_VAL_DUTYCYCLE)//if (objzone[zone].dc < MAX_VAL_DUTYCYCLE)
		{
			if (if_fadingactive_nextdc_else_dc(zone) > objzone[zone].thrshld)//if (objzone[zone].dc > objzone[zone].thrshld_sect)
				{objzone[zone].onoffrstr.dcr = objzone[zone].dc;}	
			
			setting_preupdate_dc(zone, MAX_VAL_DUTYCYCLE);	//objzone[zone].dc = MAX_VAL_DUTYCYCLE;	
			
			//++add.
			graphbarlevel.g[zone].Qsaved = graphbarlevel.g[zone].Q;
			//++

		}
		else
			{setting_preupdate_dc(zone,0 );}//objzone[zone].dc = 0;
		//
		if (objzone[zone].TypeOfLoad == NoDimmable)	
		{
			clear_and_directfill_barlevel(zone, objzone[zone].dc);
		}
				
		if (objzone[zone].bf.print_dcporcentz)
			{_dcporcentz_acctypeofload(zone);}
		//
		
		objzone[zone].commingfrom = (COMMINGFROM)LASTEVENT_DIRECTONOFF;
	
		updatedc_acctypeofload(zone);
	}
	
	///////////////////////////////////////////////////////////////////////////
	void RestoreOnOff_mode2(byte zone)
	{
		if (if_fadingactive_nextdc_else_dc(zone) > objzone[zone].thrshld)	//if (objzone[zone].dc > objzone[zone].thrshld_sect)
			{setting_preupdate_dc(zone, 0);}							//{objzone[zone].dc = 0;}
		else
			{setting_preupdate_dc(zone, MAX_VAL_DUTYCYCLE);}			//{objzone[zone].dc = MAX_VAL_DUTYCYCLE;}
		
		//_______
		if (objzone[zone].TypeOfLoad == NoDimmable)	
		{
			clear_and_directfill_barlevel(zone, objzone[zone].dc);
		}
		
		if (objzone[zone].bf.print_dcporcentz)
		{
			_dcporcentz_acctypeofload(zone);
		}
		//_______
		
		updatedc_acctypeofload(zone);
	}
	
	///////////////////////////////////////////////////////////////////////////
	void directOnOff_mode2(byte zone)
	{
		if (if_fadingactive_nextdc_else_dc(zone) < MAX_VAL_DUTYCYCLE)	//if (objzone[zone].dc < MAX_VAL_DUTYCYCLE)
			{setting_preupdate_dc(zone, MAX_VAL_DUTYCYCLE);}	//{objzone[zone].dc = MAX_VAL_DUTYCYCLE;}
		else
			{setting_preupdate_dc(zone, 0);}					//{objzone[zone].dc = 0;}

		//_______
		if (objzone[zone].TypeOfLoad == NoDimmable)
			{clear_and_directfill_barlevel(zone, objzone[zone].dc);}
		
		if (objzone[zone].bf.print_dcporcentz)
			{_dcporcentz_acctypeofload(zone);}
		//_______
		updatedc_acctypeofload(zone);
	}
                    
	//////////////////////////////////////////////////////////////////////////////////////////////////
	BOOL _all_current_dcs_are_lessequalthan_threshold(void)// o <= 0x0
	{
		byte zone;
		for (zone=0; zone<NUM_ZONAS; zone++)
		{
			//if (objzone[zone].dc > objzone[zone].thrshld)
			if (if_fadingactive_nextdc_else_dc(zone) > objzone[zone].thrshld)
	
				{return FALSE;}
		}
		return TRUE;
	}
	
	BOOL _all_zones_have_pto_rstr_OFF(void)
	{
		byte zone;
		for (zone=0; zone<NUM_ZONAS; zone++)
		{
			if (objzone[zone].onoffrstr.bf.pto_rstr == ON)
				{return FALSE;}
		}
		return TRUE;	
	}
	
	