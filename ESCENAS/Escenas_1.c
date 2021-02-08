/*
 * Escenas_1.c
 *
 * Created: 05/03/2012 12:18:38 p.m.
 *  Author: jcaf
 */ 
/*********************************************
.sObjSCENE_COMMONPROPepp	@ 0x100
.sObjStorSCENEeep			@ 0x200 (+0x200 of free-space)
.sObjZONEeep				@ 0x400 (+0x200 of free-space)

AVRStudio v6.0.1843
AVR/GNU Linker -> Memory setting -> EEPROM segment (adicionar)

.sObjSCENE_COMMONPROPepp=0x100
.sObjStorSCENEeep=0x200               
.sObjZONEeep=0x400                    
**********************************************/
#include "Includes/InitializeAllModules.h"
	
	//EEMEM _ObjSCENE_COMMONPROPepp ObjSCENE_COMMONPROPepp; //@ offset 256
	//EEMEM _ObjStorageSCENE ObjStorSCENEeep[_NUM_ESCENAS_MAXIMA_]; //@ offset 512 + (512 of space)
	
	_ObjSCENE_COMMONPROPepp ObjSCENE_COMMONPROPepp __attribute__((section(".sObjSCENE_COMMONPROPepp"))); //@ offset 256
	_ObjStorageSCENE ObjStorSCENEeep[_NUM_ESCENAS_MAXIMA_] __attribute__((section(".sObjStorSCENEeep"))); //@ offset 512 + (512 of space)

	volatile _ObjSCENEram ObjSCENEram;

//#define _IDX_TODOS_0_PORCENT_		(0)
//#define _IDX_TODOS_100_PORCENT_	(4)
//No mover los primeros 5 nombres
		   //PROGMEM
const char vNombreDeEscena_FLASH[][_MAX_LENGTH_NOM_ESCENAS_] ={\
"Todos 0%",
"Todos 25%",
"Todos 50%",
"Todos 75%",
"Todo 100%",
"LuzCamino",
"LuzDiario",
"LuzNoche",
"LuzTarde",
"LuzVisita",
"Luz Cena",
"Mix 1",
"Mix 2",
"Mix 3",
"Mix 4",
"Mix 5",
"Mix 6",
"Mix 7",
"Mix 8",
"Mix 9",
"Reunion",
"Recepcion",
"Juego",
"Lectura",
"Calido",
"Confort",
"Fiesta",
"Frio",
"Intermedio",
"Natural",
"Neutro",
"Sutil",
"Decorativo",
"Agradable",
"Velada",
"L.Entrada",
"Emergencia"};

const byte _NUMERO_ELEM_vNombreDeEscena_FLASH =(sizeof(vNombreDeEscena_FLASH)/sizeof(vNombreDeEscena_FLASH[0]));

const char (*pvNombreDeEscena_FLASH)[_MAX_LENGTH_NOM_ESCENAS_] = vNombreDeEscena_FLASH;
	
	/***************************************************************************************
	//Initialize 
					cargar desde EEPROM
	***************************************************************************************/	
	void CopyObjSCENEeepToObjSCENEram(void)	   
	{
		ObjSCENEram.scene = EEPROM_ReadByte((byte *) &ObjSCENE_COMMONPROPepp.CurrentScene);
		ObjSCENEram.totalscenes = EEPROM_ReadByte((byte *) &ObjSCENE_COMMONPROPepp.TotalOfScenes);
		ObjSCENEram.ModeOfSelectNextScene = EEPROM_ReadByte((byte *) &ObjSCENE_COMMONPROPepp.ModeOfSelectNextScene);		
	}	

	/***************************************************************************************************
	***************************************************************************************************/
	void SaveEscena(byte _CurrentScene, byte idx_ToSave)
	{
		byte i;
		
		for (i=0; i<NUM_ZONAS; i++)
		{
			EEPROM_WriteWord((word *) &ObjStorSCENEeep[_CurrentScene].vDutyCycleAllZone[i], objzone[i].dc);	
		}
		
		EEPROM_WriteByte((byte*) &ObjStorSCENEeep[_CurrentScene].idxNameOfScene, idx_ToSave);
		//CopyCadRAM2EEPROM(_CurrentScene, pvNombreDeEscena);//Copia cadena no nula, + '\0'
	}
	
	/***************************************************************************************************
	Si por algun descuido, la cadena en flash en nula '\0', la rutina lo copia, para asegurarse que no
	ocurrira algun desborde de lectura para la variable en RAM
	***************************************************************************************************/
	//void CopyCadFLASH_idxEEPROM_2RAM(byte _CurrentScene, char * pvNombreDeEscenaRAM)
	//{
		//byte idx,i,caracter;		
		//
		//idx= EEPROM_ReadByte((byte *) &ObjStorSCENEeep[_CurrentScene].idxNameOfScene);
		//
		//i=0;
		//for (;;)
		//{	caracter = pgm_read_byte(&vNombreDeEscena_FLASH[idx][i]);
			//*pvNombreDeEscenaRAM = caracter;
			//
			//if (caracter == '\0') {break;}
			//
			//pvNombreDeEscenaRAM++;
			//i++;	
		//}		
		//
	//}
	
	/***************************************************************************************
	***************************************************************************************/
	byte __CheckIfnext_DutyCycleIsLessOrGreatThan(word dutycycle)
	{
		if ( dutycycle <= 0)		//Por ahora el umbral tope es 0x0000
			{return 1;}
		
		return 0;
	}
	/***************************************************************************************
	***************************************************************************************/
	void __LetsNextToggling_OnOff_SCENE(void * PtrBaseToDutyCycle)
	{
		byte zone; 
		byte _count_DC_IsLessOrGreatThanZero =0;
				
		for (zone=0; zone<NUM_ZONAS; zone++)
		{
			_count_DC_IsLessOrGreatThanZero += __CheckIfnext_DutyCycleIsLessOrGreatThan( *((word*)PtrBaseToDutyCycle) );
			PtrBaseToDutyCycle = (_ObjZONEram*)PtrBaseToDutyCycle +1;
		}
					
		//				
		if (_count_DC_IsLessOrGreatThanZero == NUM_ZONAS)						//o _count > NUM_ZONAS/2 -> >50%
			DIMMING_FLAGS.OnRestOFF = _OnRestOFF_NEXT_MUST_BE_RESTORE_OR_ON;
		else
			DIMMING_FLAGS.OnRestOFF = _OnRestOFF_NEXT_MUST_BE_OFF;				
	}
	/**************************************************************************************
	**************************************************************************************/
	void __Parsing_UpdateBarAllZones_AccodingToTheFeatures(void)
	{
		byte zone;
		for (zone=0; zone<NUM_ZONAS; zone++)
			__Parsing_UpdateBarZone_AccodingToTheFeatures(zone);
	}	
	
	/***************************************************************************************
	//incluye ClearBar_zone!
	***************************************************************************************/	
	void UpdateBar_DirectShow_AllZone(void * PtrBaseToDutyCycle)//puntero base hacia primer dutycycle
	{
		byte zone;	
		
		for (zone=0; zone<NUM_ZONAS; zone++)
		{
			//incluye ClearBar_zone!
			directfill_barlevel(zone, *((word*)PtrBaseToDutyCycle));
			PtrBaseToDutyCycle = (_ObjZONEram*)PtrBaseToDutyCycle +1;
		}
	}
	/***************************************************************************************
	***************************************************************************************/
	void UpdatingDCAllZones_AccodingToTheFeatures(void)		
	{	
		byte zone;
		for (zone=0; zone < NUM_ZONAS; zone++)
			{updatedc_acctypeofload(zone);}				
	}
	/*******************************************************************************
	*******************************************************************************/
	void ClearBar_AllZone(void)
	{
		byte zone;	
		for (zone=0; zone<NUM_ZONAS; zone++)	
			directclearall_barlevel(zone);
	}
	
	
	/***************************************************************************************
	llamado cada vez que se cambia de escena
	
							"ObjZONEram[CurrentZone].DutyCycleToRestore"
							
	mantiene los valores de la escena guardada							
	
	***************************************************************************************/	
	void CargarDCdeZonasDeEsceneEEP2RAM(byte _CurrentScene, void * PtrBasePtrBaseToDutyCycle)	//&ObjZONEram[CurrentZone].DutyCycleToRestore 
	{
		byte zone;
		for (zone=0; zone<NUM_ZONAS; zone++)
		{
			*((word*)PtrBasePtrBaseToDutyCycle)= EEPROM_ReadWord( (const word *)&ObjStorSCENEeep[_CurrentScene].vDutyCycleAllZone[zone]);				
			//ObjZONEram[CurrentZone].DutyCycleToRestore = EEPROM_ReadWord( (const word *)&ObjStorSCENEeep[_CurrentScene].vDutyCycleAllZone[CurrentZone]);				
			PtrBasePtrBaseToDutyCycle = ((_ObjZONEram*)PtrBasePtrBaseToDutyCycle) +1;
		}
	}
	/***************************************************************************************
	Alista los valores x todas las zonas, si es o no Dimable
	***************************************************************************************/	
	//void EstablecerValoresParaNuevaEscena(void)
	void EstablecerValoresParaNuevaEscena(void * PtrBasePtrBaseToDutyCycle)
	{
		byte zone;
		
		for (zone=0; zone<NUM_ZONAS; zone++) 
		{	
			if (objzone[zone].TypeOfLoad == Dimmable)
			{
				if (objzone[zone].TypeOfEffect == Fading)	
				{
					objzone[zone].sfading.nextdcfading = *((word*)PtrBasePtrBaseToDutyCycle);//ObjZONEram[CurrentZone].DutyCycleToRestore;
				}
			}							
			else if (objzone[zone].TypeOfLoad == NoDimmable)
			{
				if (objzone[zone].TypeOfEffect == Direct)	
				{
					objzone[zone].dc = *((word*)PtrBasePtrBaseToDutyCycle);//ObjZONEram[CurrentZone].DutyCycleToRestore;
				}
			}
		
		PtrBasePtrBaseToDutyCycle = (_ObjZONEram*)PtrBasePtrBaseToDutyCycle +1;
		}
	}
	/***************************************************************************************
	Utiles: asigna una constante cualquiera , util para Off100% On100%
	***************************************************************************************/	
	void __AsignarKte_ParaNuevaEscena(word val)
	{
		byte zone;
		
		for (zone=0; zone<NUM_ZONAS; zone++) 
		{	
			if (objzone[zone].TypeOfLoad == Dimmable)
			{
				if (objzone[zone].TypeOfEffect == Fading)	
					{objzone[zone].sfading.nextdcfading = val;}
			}							
			else if (objzone[zone].TypeOfLoad == NoDimmable)
			{
				if (objzone[zone].TypeOfEffect == Direct)	
					{objzone[zone].dc = val;}
			}
		}					
	}
