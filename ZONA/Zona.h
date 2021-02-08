/*
 * Zona.h
 *
 * Created: 15/03/2012 04:27:55 p.m.
 *  Author: jcaf
	
	Por defecto todas las cargas estan configuradas como NO dimerizables y EFECTO directo.
 */ 
#ifndef ZONA_H_
#define ZONA_H_

	#define NUM_ZONAS (6)

	typedef word TYPEDC;
	//typedef byte TYPEDC;

	#define NUM_FIELDS_Q_COMPONEN_NOMBRE_DE_ZONA (3)
	struct _FIELD_LINK
	{
		byte VectorApuntadoX;		//inicio del vector al q se apunta
		byte elemDeVectorApuntadoX;	//indice dentro del vector
	};

	struct _NAME_ZONE
	{
		struct _FIELD_LINK FIELD_LINK[NUM_FIELDS_Q_COMPONEN_NOMBRE_DE_ZONA];
	};

	typedef enum _ZONE_InMode_
	{
		KeySetMode_TOGGLINGVAL = 0,
		KeySetMode_MAXVAL,
	}_ZONE_InMode;	

	typedef enum _ZONE_SetLevel_
	{
		Off100p = 0,
		Restore,
		ON100p
	}_ZONE_SetLevel;

	typedef enum _ZONE_TypeOfEffect_
	{
		Direct = 0,
		Fading		
	}_ZONE_TypeOfEffect;		

	typedef enum _ZONE_TypeOfLoad_
	{
		//UNDEFINED=-1,
		NoDimmable = 0,
		Dimmable
	}_ZONE_TypeOfLoad;

	typedef enum _COMMINGFROM
	{
		LASTEVENT_CLEAR=0,
		LASTEVENT_DIRECTONOFF,
		LASTEVENT_RESTOREONOFF
	}COMMINGFROM;
	
	//#define SECTION_LESSEQUALTHAN_THRSHLD (0)
	//#define SECTION_GREATERTHAN_THRSHLD 	(1)
	typedef enum _CFGSECTIONOF_DIMMRANGE
	{
		SECTION_LESSEQUALTHAN_THRSHLD =0,
		SECTION_GREATERTHAN_THRSHLD
	}SECTIONOF_DIMMRANGE;
	
	typedef enum _CFGTORESTORE_ATLEVEL
	{
		MAXVAL=0,
		THRESHOLD_MAS_1,
	}CFGTORESTORE_ATLEVEL;
	
	typedef enum _CFGMODEOF_RESTOREONOFF
	{
		RESTORE_AND_ON_OFF=0,
		ONLY_ON_OFF
	}CFGMODEOF_RESTOREONOFF;
	
	typedef enum _CFGMODEOF_DIMM_IN_LESSEQUALTHAN_THRSHLD
	{
		AUTOMATIC_BYPASS=0,
		DIMMABLE_WITH_SENSE
	}CFGMODEOF_DIMM_IN_LESSEQUALTHAN_THRSHLD;

	//proceso de fading
	struct _sfading
	{	
		TYPEDC nextdcfading;	
		signed char kte_addsub;
		//
		signed int diff;
		word counterof_diff;
		
		//timing
		word ticktime_of_fading;
		word counterof_ticktime_of_fading;
		
		struct _bf
		{
			unsigned fading_active:1;
			unsigned _none:7;
			//unsigned UpdateDCInFadingProcess;
		}bf;

	};	

	struct _onoffrstr
	{
		TYPEDC dcr;				
		struct _onoffrstr_bf
		{
			unsigned pto_rstr:1;
			unsigned :7;
		}bf;
	};
	
	struct _objzone_ram
	{
		struct _NAME_ZONE NameZone;
		_ZONE_TypeOfLoad TypeOfLoad;
		_ZONE_TypeOfEffect TypeOfEffect;
		TYPEDC dc;						//work var
	
		struct _onoffrstr onoffrstr;					//on/off/restore 
		struct _sfading sfading;
	
		struct _bf_objzone_ram
		{
			unsigned print_dcporcentz:1;
			unsigned changing_of_escene:1;
			unsigned __none:6;
		}bf;
		
		COMMINGFROM commingfrom;		
		word time_of_fading;

		word thrshld;
		CFGMODEOF_DIMM_IN_LESSEQUALTHAN_THRSHLD cfgmodeof_diLET_THRSHLD;//modeof dimming in LessEqualthan threshold
		
		CFGMODEOF_RESTOREONOFF cfgmodeof_restoreonoff;
		CFGTORESTORE_ATLEVEL cfgtorestore_atlevel;
		
		word timmer;

		//_ZONE_InMode InMode;			//deprecated
		//_ZONE_SetLevel SetLevel;		//deprecated
		//SECTIONOF_DIMMRANGE laidsw;	//por ahora no usado
	};

	extern volatile struct _objzone_ram objzone[NUM_ZONAS];	

	struct _objzone_epp
	{
		struct _NAME_ZONE NameZone;
		   
		_ZONE_TypeOfLoad TypeOfLoad;		//8-bit size
		_ZONE_TypeOfEffect TypeOfEffect;	//8-bit size
		
		TYPEDC DutyCycle;						//no usado, lo dejo por si mas adelante lo necesito
	};	

	//extern EEMEM struct _ObjZONEeep ObjZONEeep[NUM_ZONAS];
	extern struct _objzone_epp objzone_epp[NUM_ZONAS];
	
	void InitZones(void);

#endif /* ZONA_H_ */