/*
 * Zona_1.c
 *
 * Created: 15/03/2012 04:27:44 p.m.
 *  Author: jcaf
 */ 

#include "Includes/InitializeAllModules.h"
	
	//EEMEM _objzone_epp objzone_epp[NUM_ZONAS];
	struct _objzone_epp objzone_epp[NUM_ZONAS] __attribute__((section(".sobjzone_epp"))) = {0};
	
	volatile struct _objzone_ram objzone[NUM_ZONAS];	//mantendra una copia de ObjZONEeep
	
	void InitZone(byte zone);
	void CopyObjZONEeepToObjZONEram(byte zone);
	
	//////////////////////////////////////////////////////////////////
	void InitZones(void)
	{
		byte zone;
		for (zone=0; zone<NUM_ZONAS; zone++)
		{	InitZone(zone);	}		
	}
	
	//////////////////////////////////////////////////////////////////
	//Si se mueve el threshold, quiere decir que el tiempo de desvanecimiento 
	//ha de variar, se "auto-recorta" en el tiempo comprendido entre 0->objzone[zone].thrshld
	//OK! Si se ha considerado en el codigo en Fading_1.c
	//////////////////////////////////////////////////////////////////
	void InitZone(byte zone)
	{
		CopyObjZONEeepToObjZONEram(zone);
		
		//objzone[i].thrshld_sect = (byte)(0.1 * MAX_VAL_DUTYCYCLE);
		objzone[zone].thrshld = 1;//26;//26=20.5%     1;//25;//#define _THRESHOLD_VISUAL_	(33)	//25%
		
		//objzone[zone].cfgmodeof_diLET_THRSHLD = (CFGMODEOF_DIMM_IN_LESSEQUALTHAN_THRSHLD)DIMMABLE_WITH_SENSE;	//ok!
		//objzone[zone].cfgmodeof_restoreonoff = (CFGMODEOF_RESTOREONOFF)ONLY_ON_OFF;	//ok!
	
		objzone[zone].time_of_fading = 3200;//ms
	}
		
	//////////////////////////////////////////////////////////////////
	void CopyObjZONEeepToObjZONEram(byte zone)
	{
		byte numfield;
		for (numfield=0; numfield<NUM_FIELDS_Q_COMPONEN_NOMBRE_DE_ZONA; numfield++)	
		{
			objzone[zone].NameZone.FIELD_LINK[numfield].VectorApuntadoX =  EEPROM_ReadByte( (const byte *) &objzone_epp[zone].NameZone.FIELD_LINK[numfield].VectorApuntadoX);
			objzone[zone].NameZone.FIELD_LINK[numfield].elemDeVectorApuntadoX =  EEPROM_ReadByte( (const byte *) &objzone_epp[zone].NameZone.FIELD_LINK[numfield].elemDeVectorApuntadoX);
		
//objzone[zone].TypeOfLoad = (_ZONE_TypeOfLoad)Dimmable;
//objzone[zone].TypeOfEffect = (_ZONE_TypeOfEffect)Fading ;		

		}
		objzone[zone].TypeOfLoad = EEPROM_ReadByte((const byte *) &objzone_epp[zone].TypeOfLoad );
		objzone[zone].TypeOfEffect = EEPROM_ReadByte((const byte *) &objzone_epp[zone].TypeOfEffect);
	}
/*
objzone[0].TypeOfLoad = (_ZONE_TypeOfLoad)Dimmable;
objzone[0].TypeOfEffect = (_ZONE_TypeOfEffect)Fading ;

objzone[1].TypeOfLoad = (_ZONE_TypeOfLoad)Dimmable;
objzone[1].TypeOfEffect = (_ZONE_TypeOfEffect)Fading ;

objzone[2].TypeOfLoad = (_ZONE_TypeOfLoad)Dimmable;
objzone[2].TypeOfEffect = (_ZONE_TypeOfEffect)Fading ;

objzone[3].TypeOfLoad = (_ZONE_TypeOfLoad)Dimmable;
objzone[3].TypeOfEffect = (_ZONE_TypeOfEffect)Fading ;

objzone[4].TypeOfLoad = (_ZONE_TypeOfLoad)Dimmable;
objzone[4].TypeOfEffect = (_ZONE_TypeOfEffect)Fading ;

objzone[5].TypeOfLoad = (_ZONE_TypeOfLoad)Dimmable;
objzone[5].TypeOfEffect = (_ZONE_TypeOfEffect)Fading ;
*/