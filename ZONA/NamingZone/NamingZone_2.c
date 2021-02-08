//Bug.fixed new function view_fieldname_of_zone
//March 12 2013
//  [4/22/2013 jc]

#include "Includes/InitializeAllModules.h"

	// Lista - derecha ////////////////////////
	#define _INTERLINEADO_ (SC_HEIGHT+2)	//13-1 = 12
	//#define _INITIAL_X_CHIP3_	(128-1)	//correguir
	
	#define _INITIAL_X_CHIP3_	(128)	//correguir

	#define _NUM_FIELDS_TO_SHOW_ (4)
	
	#define _NUM_DBASE_TO_NAME_ZONE_ (4)

	typedef const char (*_pCADS_LENGTH_COMMON)[_MAX_LENGTH_CADS_COMMON_];
	//typedef PROGMEM const char (_pCADS_LENGTH_COMMON)[_MAX_LENGTH_CADS_COMMON_];	//DEBERIA TRABAJAR.NO TRABAJA
	_pCADS_LENGTH_COMMON pCADS_LENGTH_COMMON[_NUM_DBASE_TO_NAME_ZONE_]={	
												v_places_of_house,
												v_types_of_luminary,
												v_position_or_reference,
												v_others_about_of_house,
											};
	
	const char vNombreASCII_DBase_To_Name_Zone[][_MAX_LENGTH_CADS_COMMON_] PROGMEM ={
												"Ambiente",
												"Luminaria",
												"Posicion",
												"Otros",
												};									
	
	byte vNUMERO_CADENAS_THIS_VECTOR[_NUM_DBASE_TO_NAME_ZONE_] ={
																LENGTH__V_PLACES_OF_HOUSE ,
																LENGTH__V_TYPES_OF_LUMINARY,
																LENGTH__V_POSITION_OR_REFERENCE,
																LENGTH__V_OTHERS_ABOUT_OF_HOUSE,
															};
	
	//byte vNUMERO_CADENAS_THIS_VECTOR[_NUM_DBASE_TO_NAME_ZONE_] ={
												//sizeof(v_places_of_house)/sizeof(v_places_of_house[0]),
												//sizeof(v_types_of_luminary)/sizeof(v_types_of_luminary[0]),
												//sizeof(v_position_or_reference)/sizeof(v_position_or_reference[0]),
												//sizeof(v_others_about_of_house)/sizeof(v_others_about_of_house[0]),
												//};
	byte vGOTOXY_VERTICAL_LIST[]={
											2+(_INTERLINEADO_*0),
											2+(_INTERLINEADO_*1),
											2+(_INTERLINEADO_*2),
											2+(_INTERLINEADO_*3),
										};
	
	//////////////////////////Armandose/mostrando nombre de Zona - Izquierda////////////////////////
	byte vGogoXY_VerticalFieldNameZone[NUM_FIELDS_Q_COMPONEN_NOMBRE_DE_ZONA]={
											3+(SC_HEIGHT*0),
											3+(SC_HEIGHT*1 -2 + 4*1),
											3+(SC_HEIGHT*2 -4 + 4*2),
											};

	static void SaveNameOfZoneToEEPROM(byte zone, byte fieldname, byte VectorApuntadoX, byte elemDeVectorApuntadoX);
	static byte LoadNewListFromThisDB(byte DBpointed);
	
	//Limpia 2 posiciones a la vertical, desde arriba
	#define ClearRegionWorkForAllEvent_ChooseFromList() do{ks0108FillRect(xiCHIP1+1, yiCHIP1+1 , (xfCHIP1-1)-(xiCHIP1+1), SC_HEIGHT*2, WHITE);}while(0)	
	
	
	//_class_listbox listbox;//objeto re-usable para todo este menu

	typedef enum _OPERATINGMODE_THISPS
	{
		SET_ZONE_FIELDNAME=0,//MODE0=0,//doing scene
		DO_DIAGBOX,//MODE1,	//doing dialogbox
		DO_LISTBOX//MODE2,	//doing listbox
	
	}OPERATINGMODE_THISPS;

	static struct _thisps
	{
		signed char zone;
		signed char fieldname;
		
		OPERATINGMODE_THISPS operating_mode;
		
		//scheduling.. tal vez ponerlo dentro de una estructura
		signed char scheduler0;
		signed char scheduler1;
		//
		//_STACK_MODE app_kb_layout;
		
	}thisps;
	
	////////////////////////////////////////////////////////////////////////////////////////
	#define schedule(val) do{thisps.scheduler0 = val; thisps.scheduler1 = 0x00;}while(0)

	static void key1_1fmode0(void);
	static void key2_1fmode0(void);
	static void key3_1fmode0(void);
	static void key3_1fmode0_aft(void);
	static void key4_1fmode0(void);

	static void key1_1fmode1(void);
	static void key2_1fmode1(void);
	static void key3_1fmode1(void);
	static void key3_1fmode1_aft(void);
	static void key4_1fmode1(void);
	
	static void key1_1fmode2(void);
	static void key2_1fmode2(void);
	static void key3_1fmode2(void);
	static void key3_1fmode2_aft(void);
	static void key4_1fmode2(void);

	static void key3_2fmode0(void){}

	static void _return2shell(void);
	static void return_to_mode0(void);

	static void view_fieldname_of_zone(byte zone, byte xiCHIPX);
	
	static PTRFXrVOID thisps_fxs[4][MAXNUM_MODE_BY_PS][KB_TOTALOFKEYS]={
		{
		{&key1_1fmode0, &key2_1fmode0, &key3_1fmode0, &key4_1fmode0},
		{&key1_1fmode1, &key2_1fmode1, &key3_1fmode1, &key4_1fmode1},//doing dialog-box
		{&key1_1fmode2, &key2_1fmode2, &key3_1fmode2, &key4_1fmode2},//doing list-box
		{&DUMMYFX, &DUMMYFX, &DUMMYFX, &DUMMYFX},
		},
		{
		{&DUMMYFX, &DUMMYFX, &key3_1fmode0_aft, &DUMMYFX},
		{&DUMMYFX, &DUMMYFX, &key3_1fmode1_aft, &DUMMYFX},//doing dialog-box
		{&DUMMYFX, &DUMMYFX, &key3_1fmode2_aft, &DUMMYFX},//doing list-box
		{&DUMMYFX, &DUMMYFX, &DUMMYFX, &DUMMYFX},
		},
		{
		{&DUMMYFX, &DUMMYFX, &key3_2fmode0, &DUMMYFX},
		{&DUMMYFX, &DUMMYFX, &DUMMYFX, &DUMMYFX},
		{&DUMMYFX, &DUMMYFX, &DUMMYFX, &DUMMYFX},
		{&DUMMYFX, &DUMMYFX, &DUMMYFX, &DUMMYFX},
		},
		{
		{&DUMMYFX, &DUMMYFX, &DUMMYFX, &DUMMYFX},
		{&DUMMYFX, &DUMMYFX, &DUMMYFX, &DUMMYFX},
		{&DUMMYFX, &DUMMYFX, &DUMMYFX, &DUMMYFX},
		{&DUMMYFX, &DUMMYFX, &DUMMYFX, &DUMMYFX},
		}
	};

	//only if necesary
	/*static struct _key_properties key_properties__ps_forall[KB_TOTALOFKEYS]=
	{
		[0].u.bf.OnKeyPressed = 1,
		[0].group_autoexcluding = 1,
	
		[1].u.bf.OnKeyPressed = 1,
		[1].group_autoexcluding = 1,
	
		[2].u.bf.OnKeyPressed = 1,
		[2].group_autoexcluding = 1,
	
		[3].u.bf.AtTimeExpired = 1,
		[3].group_autoexcluding = _NO_AGRUPADO_AUTOEXCLUDING_,
	};
	*/	
	void Draw2RectsMarkActiveField(byte Pos, byte Colour)
	{
		ks0108DrawRect(xiCHIP2+2,Pos-1	,	59, 0,Colour);	//rectas q marcan el campo
		ks0108DrawRect(xiCHIP2+2,Pos+13	,	59, 0,Colour);	//rectas q marcan el campo
	}
	
	static void InitializeEnter_SettingNameToZone(byte zone, byte fieldname)
	{
		ks0108SelectFont(SC, ks0108ReadFontData, BLACK);
		softcentric_clearallpixel_less1border_CHIP1();
		ks0108_PrintTextP_CenterH_CHIP1(1,"Nombrar",SC_WIDTH,2,-3);
		ks0108InvertRect(1,1,61,SC_HEIGHT-1);
		ks0108_PrintTextP_CenterH_CHIP1( 1+(SC_HEIGHT)+2, "seleccione",SC_WIDTH, 2, 5);
		//
		ks0108DrawRect(1,60-(SC_HEIGHT*2 )-2,62,0,BLACK);				//Dibujar separador
		ks0108DrawRect(1,60-(SC_HEIGHT*2 )-1,61,(SC_HEIGHT*2)+3,BLACK);	//Dibujar recuadro /visto como doble linea
		//
		ks0108GotoXY( CenterText_HPix_CHIP1(GLCD192X64_SIZEX_CHIP1,"Zona: 0",SC_WIDTH,2,0) ,60-(SC_HEIGHT*2) );	ks0108Puts_P(PSTR("Zona:"));
		ks0108GotoXY( CenterText_HPix_CHIP1(GLCD192X64_SIZEX_CHIP1,"Campo: 0",SC_WIDTH,2,0) ,60-SC_HEIGHT );	ks0108Puts_P(PSTR("Campo:"));
		
		PrintNewDigitInASCIIAt(CenterText_HPix_CHIP1(GLCD192X64_SIZEX_CHIP1,"Zona: 0",SC_WIDTH,2,0)  +LongitudText_Hpix("Zona:",SC_WIDTH) +2, 60-(SC_HEIGHT*2), SC_WIDTH, SC_HEIGHT, zone+1);
		PrintNewDigitInASCIIAt(CenterText_HPix_CHIP1(GLCD192X64_SIZEX_CHIP1,"Campo: 0",SC_WIDTH,2,0) +LongitudText_Hpix("Campo:",SC_WIDTH) +6, 60-(SC_HEIGHT), SC_WIDTH, SC_HEIGHT, fieldname+1);
		
		direct_clearallpixel_less1border_CHIP2();
		view_fieldname_of_zone(zone, xiCHIP2);	//FindAndPrintNameOfZone(zone, xiCHIP2);
		Draw2RectsMarkActiveField(vGogoXY_VerticalFieldNameZone[fieldname],BLACK);//Dibuja
	}
	
	void SettingNameToZone(void)
	{
		if (thisps.scheduler0 == 0)//initialize once
		{
			if (thisps.scheduler1 == 0)
			{
				thisps.scheduler1++;
				//
				
				//Dividir en 3 GLCD	//Presentar al centro de GLCD
				ks0108ClearScreen();
				DrawOnlyMarcoGlobalGLCD();
				DrawOnlyDivisionAt63();		//dentro de CHIP 1
				DrawOnlyDivisionAt128();	//dentro de CHIP 3

				thisps.zone =0x00;
				thisps.fieldname =0x00;

				InitializeEnter_SettingNameToZone(thisps.zone, thisps.fieldname);

				ListBox_init_dimension(&listbox, 128,0,63,63, SC, SC_HEIGHT);//todos comparten la misma caja(x,y,font) para listbox
				ListBox_create_box(&listbox);//todos comparten la misma caja(x,y,font) para listbox

				//registrar las funciones al entrar
				thisps.operating_mode = (OPERATINGMODE_THISPS)SET_ZONE_FIELDNAME;//MODO0
				change_operating_mode(thisps_fxs, thisps.operating_mode);
			}	
			schedule(-1);	//espera un nuevo evento			
		}			
		
		//////////////////////////////////////////////////////////////////////////////////
		if (thisps.scheduler0 == 1)	//schedule(1)
		{
			if (thisps.scheduler1 == 0)//show menu
			{
				thisps.scheduler1++;

				softcentric_clearallpixel_less1border_CHIP1();
				//Salir de este menu
				ks0108GotoXY(2+15,2+23);	ks0108Puts_P(PSTR("Salir?"));
				dialogbox_sino(2,2,(DIALOGBOX_OPTIONS)_DIALOGBOX_OPTION_SI_);
			}
			if (thisps.scheduler1 == 1)//wait for answer
			{
				//thisps.scheduler1++;
				
				if (dialogbox_nb.cr > (DIALOGBOX_CR)NONE )
				{
					if (dialogbox_nb.cr ==  (DIALOGBOX_CR)YES)
					{
						shell.coderet = (CODERETURN_TOSHELL)RESTORE_SHELL;
						schedule(0);//sale con schedule 0
						//
						__dialogbox_cr_wasread();
					}
					else if ((dialogbox_nb.cr ==  (DIALOGBOX_CR)NO)||(dialogbox_nb.cr ==  (DIALOGBOX_CR)SCAPE))
					{
						return_to_mode0();//deja schedule(-1);
						InitializeEnter_SettingNameToZone(thisps.zone, thisps.fieldname);	//Restaurando el contexto de menu actual
						//
						__dialogbox_cr_wasread();
					}
					//thisps.scheduler1++;
				}
			}
		}
	
	}	

byte CountDBpointed;
byte Schedule_ChooseFromList;

byte DB_LastPointed;
byte DB_LastElemPointed;

	//////////////////////////////////////////////////////////////////////////////////////////
	//selecting zone
	static void key1_1fmode0(void)	
	{
		if (++thisps.zone >= NUM_ZONAS)	
			{thisps.zone = 0x00;}
		
		direct_clearallpixel_less1border_CHIP2();
		view_fieldname_of_zone(thisps.zone, xiCHIP2);	//FindAndPrintNameOfZone(thisps.zone, xiCHIP2);
		
		thisps.fieldname = 0x00;
		Draw2RectsMarkActiveField(vGogoXY_VerticalFieldNameZone[thisps.fieldname],BLACK);//dibuja

		PrintNewDigitInASCIIAt(CenterText_HPix_CHIP1(GLCD192X64_SIZEX_CHIP1,"Zona: 0",SC_WIDTH,2,0)  +LongitudText_Hpix("Zona:",SC_WIDTH) +2, 60-(SC_HEIGHT*2), SC_WIDTH, SC_HEIGHT, thisps.zone+1);
		PrintNewDigitInASCIIAt(CenterText_HPix_CHIP1(GLCD192X64_SIZEX_CHIP1,"Campo: 0",SC_WIDTH,2,0) +LongitudText_Hpix("Campo:",SC_WIDTH) +6, 60-(SC_HEIGHT), SC_WIDTH, SC_HEIGHT, thisps.fieldname+1);

		playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
	}
	
	static void key2_1fmode0(void)
	{
		Draw2RectsMarkActiveField(vGogoXY_VerticalFieldNameZone[thisps.fieldname],WHITE);//borra
				
		if (++thisps.fieldname >= NUM_FIELDS_Q_COMPONEN_NOMBRE_DE_ZONA )	
			{thisps.fieldname = 0x00;}
			
		Draw2RectsMarkActiveField(vGogoXY_VerticalFieldNameZone[thisps.fieldname],BLACK);//dibuja
			
		PrintNewDigitInASCIIAt( CenterText_HPix_CHIP1(GLCD192X64_SIZEX_CHIP1,
								"Campo: 0",
								SC_WIDTH,2,0) +((sizeof("Campo:")-1)*SC_WIDTH) +6,
								60-(SC_HEIGHT),
								SC_WIDTH, SC_HEIGHT, thisps.fieldname+1);
			
		playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
		
	}
	
	static void key3_1fmode0(void)
	{
		playsound(SOUND_BUZZER, _BUZZER_ACCEPT_SOUND0_);

		//prosigue con listbox
		thisps.operating_mode = (OPERATINGMODE_THISPS)DO_LISTBOX;//bajar a modo dialog-box
		change_operating_mode(thisps_fxs, thisps.operating_mode);
		
		CountDBpointed = 0x00;
		Schedule_ChooseFromList = 0x00;
		
		ks0108SelectFont(SC, ks0108ReadFontData, BLACK);
		ClearRegionWorkForAllEvent_ChooseFromList();
		ks0108_PrintTextP_CenterH_CHIP1(1,"Diccionario",SC_WIDTH,2,1);
		ks0108InvertRect(xiCHIP1+1,yiCHIP1+1, (xfCHIP1-1)-(xiCHIP1+1),SC_HEIGHT-1);
		
		//DB_LastElemPointed = 
		LoadNewListFromThisDB(CountDBpointed);//siempre retornara 0
		
		schedule(-1);
	}

	static void key3_1fmode0_aft(void)
		{key3_1fmode0();}
	
	static void key4_1fmode0(void)
	{
		playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
					
		thisps.operating_mode = (OPERATINGMODE_THISPS)DO_DIAGBOX;//MODE1;
		change_operating_mode(thisps_fxs, thisps.operating_mode);
		
		schedule(1);

		_KB_waitfor_kb_free_and_complete_ps();
	}		
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//doing dialogbox
	static void key1_1fmode1(void)
	{
		dialogbox_nb.dialogbox_sino_UP();
		playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
	}
	static void key2_1fmode1(void)
	{
		dialogbox_nb.dialogbox_sino_DN();
		playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
	}
	static void key3_1fmode1(void)
	{
		dialogbox_nb.dialogbox_sino_SEL();
		//
		if	(dialogbox_nb.option == 0)//yes
			{playsound(SOUND_BUZZER, _BUZZER_ACCEPT_SOUND0_);}
		else if (dialogbox_nb.option == 1)//no
			{playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);}
	}
	static void key3_1fmode1_aft(void)
		{	key3_1fmode1();}
	
	static void key4_1fmode1(void)//ya estando en modo1
	{
		playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
		dialogbox_nb.dialogbox_sino_ESC();
	}
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//doing list-box
	static void key1_1fmode2(void)
	{
		if (Schedule_ChooseFromList <= 3)
		{
			ListBox_Ex(&listbox, LISTBOX_FORD);
			playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);	
		}
	}
	static void key2_1fmode2(void)
	{
		if (Schedule_ChooseFromList <= 3)
		{
			ListBox_Ex(&listbox,LISTBOX_BACK);
			playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
		}		
	}
	static void key3_1fmode2(void)//before
	{
		playsound(SOUND_BUZZER, _BUZZER_ACCEPT_SOUND0_);
		
		if (Schedule_ChooseFromList <=3)
		{
			DB_LastPointed = CountDBpointed;	//Guardar estos valores para opcion grabar
			DB_LastElemPointed = ListBox_get_last_elementpointed(&listbox);
			
			ks0108FillRect(xiCHIP2+1,vGogoXY_VerticalFieldNameZone[thisps.fieldname],(xfCHIP2-1)-(xiCHIP2+1), SC_HEIGHT-1,WHITE);	//Clear position
			ks0108GotoXY(xiCHIP2+2,vGogoXY_VerticalFieldNameZone[thisps.fieldname]);	//print new text
			
			ks0108Puts_P((const char *)&pCADS_LENGTH_COMMON[CountDBpointed][DB_LastElemPointed]);
		}	
		
		if (Schedule_ChooseFromList == 4)
		{
			SaveNameOfZoneToEEPROM(thisps.zone, thisps.fieldname, DB_LastPointed, DB_LastElemPointed );
	
			ClearRegionWorkForAllEvent_ChooseFromList();
			ks0108_PrintTextP_CenterH_CHIP1(( ((yiCHIP1+1) +(SC_HEIGHT*2)) - (yiCHIP1-1) )/2,"Guardado!",SC_WIDTH,2,0);
			_delay_ms(500);
			
			return_to_mode0();
	
			softcentric_clearallpixel_less1border_CHIP3();	//borra seccion visualizacion de la lista
			InitializeEnter_SettingNameToZone(thisps.zone, thisps.fieldname);	//Restaurando el contexto de menu actual
		}		
		
		if (Schedule_ChooseFromList == 5)
		{
			return_to_mode0();
	
			softcentric_clearallpixel_less1border_CHIP3();
			InitializeEnter_SettingNameToZone(thisps.zone, thisps.fieldname);	//Restaurando el contexto de menu actual
		}				
		
		if (Schedule_ChooseFromList == 6)
		{
			_return2shell();
		}
	}

	static void key3_1fmode2_aft(void)
		{	key3_1fmode2();	}

	static void key4_1fmode2(void)
	{
		playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
		
		Schedule_ChooseFromList++;
		
		if (Schedule_ChooseFromList == 7)		
		{
			 Schedule_ChooseFromList = 0x00;
			 //
			ks0108SelectFont(SC, ks0108ReadFontData, BLACK);
			ClearRegionWorkForAllEvent_ChooseFromList();
			ks0108_PrintTextP_CenterH_CHIP1(1,"Diccionario",SC_WIDTH,2,1);
			ks0108InvertRect(xiCHIP1+1,yiCHIP1+1, (xfCHIP1-1)-(xiCHIP1+1),SC_HEIGHT-1);
		}
		
		if (Schedule_ChooseFromList <= 3)//0..3
		{
			if (++CountDBpointed >= _NUM_DBASE_TO_NAME_ZONE_)//0..3
				{CountDBpointed = 0x00;}
			
			LoadNewListFromThisDB(CountDBpointed);	//Carga nueva lista
		}
		
		if (Schedule_ChooseFromList == 4)
		{
			ClearRegionWorkForAllEvent_ChooseFromList();
			ks0108_PrintTextP_CenterH_CHIP1(yiCHIP1+1,"Guardar",SC_WIDTH,2,-3);
			ks0108_PrintTextP_CenterH_CHIP1((yiCHIP1+1)+SC_HEIGHT,"cambio ?",SC_WIDTH,2,3);
		}
		
		if (Schedule_ChooseFromList == 5)
		{
			ClearRegionWorkForAllEvent_ChooseFromList();
			ks0108_PrintTextP_CenterH_CHIP1(yiCHIP1+1,"Nuevo",SC_WIDTH,2,-2);
			ks0108_PrintTextP_CenterH_CHIP1((yiCHIP1+1)+SC_HEIGHT,"nombre ?",SC_WIDTH,2,0);//2
		}
			
		if (Schedule_ChooseFromList == 6)
		{
			ClearRegionWorkForAllEvent_ChooseFromList();
			ks0108_PrintTextP_CenterH_CHIP1((yiCHIP1+1)+SC_HEIGHT,"Salir ?",SC_WIDTH,2,2);
		}				
	}
	
	static void SaveNameOfZoneToEEPROM(byte zone, byte fieldname, byte VectorApuntadoX, byte elemDeVectorApuntadoX)
	{
		EEPROM_WriteByte((byte *)&objzone_epp[zone].NameZone.FIELD_LINK[fieldname].VectorApuntadoX, VectorApuntadoX);
		EEPROM_WriteByte((byte *)&objzone_epp[zone].NameZone.FIELD_LINK[fieldname].elemDeVectorApuntadoX, elemDeVectorApuntadoX);
	}
	
	void FindAndPrintNameOfZone(byte zone, byte xiCHIPX)
	{
		byte i,y;
		byte VectorApuntadoX, elemDeVectorApuntadoX;
		
		ks0108SelectFont(SC, ks0108ReadFontData, BLACK);	//Set tipografia - obtener altura de tipografia SC_HEIGHT
		
		y=0;
		for (i=0; i<NUM_FIELDS_Q_COMPONEN_NOMBRE_DE_ZONA; i++)
		{
			//Carga desde EEPROM
			VectorApuntadoX = EEPROM_ReadByte( (const byte *) &objzone_epp[zone].NameZone.FIELD_LINK[i].VectorApuntadoX);
			elemDeVectorApuntadoX = EEPROM_ReadByte( (const byte *) &objzone_epp[zone].NameZone.FIELD_LINK[i].elemDeVectorApuntadoX);
			
			if (elemDeVectorApuntadoX != 0)
			{
				ks0108GotoXY(xiCHIPX+2,vGogoXY_VerticalFieldNameZone[y++]);					//Imprime en posicion...
				ks0108Puts_P((const char *)&pCADS_LENGTH_COMMON[VectorApuntadoX][elemDeVectorApuntadoX]);
			}
		}
	}
	
	static void view_fieldname_of_zone(byte zone, byte xiCHIPX)
	{
		byte i, VectorApuntadoX, elemDeVectorApuntadoX;
		
		ks0108SelectFont(SC, ks0108ReadFontData, BLACK);	
		
		for (i=0; i<NUM_FIELDS_Q_COMPONEN_NOMBRE_DE_ZONA; i++)
		{
			VectorApuntadoX = EEPROM_ReadByte( (const byte *) &objzone_epp[zone].NameZone.FIELD_LINK[i].VectorApuntadoX);
			elemDeVectorApuntadoX = EEPROM_ReadByte( (const byte *) &objzone_epp[zone].NameZone.FIELD_LINK[i].elemDeVectorApuntadoX);
			
			ks0108GotoXY(xiCHIPX+2,vGogoXY_VerticalFieldNameZone[i]);					
			ks0108Puts_P((const char *)&pCADS_LENGTH_COMMON[VectorApuntadoX][elemDeVectorApuntadoX]);
		}
	}

	/////////////////////////////////////////////////////////////	
	static void return_to_mode0(void)
	{
		thisps.operating_mode = (OPERATINGMODE_THISPS)SET_ZONE_FIELDNAME;
		change_operating_mode(thisps_fxs, thisps.operating_mode);
			
		schedule(-1);	//espero un nuevo evento
	}

	static void _return2shell(void)	//sale con schedule 0
	{
		shell.coderet = (CODERETURN_TOSHELL)RESTORE_SHELL;
		schedule(0);
		_KB_waitfor_kb_free_and_complete_ps();
		//NOTA: VER SALIDA DE MenuSelectDimmNoDimmLoad_1.c
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//ListBox_InitParams siempre retorna 0
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	static byte LoadNewListFromThisDB(byte DBpointed)
	{
		byte temp;
		
		ks0108FillRect(xiCHIP1+1, yiCHIP1+1 +SC_HEIGHT, (xfCHIP1-1)-(xiCHIP1+1), SC_HEIGHT, WHITE);
		ks0108GotoXY( CenterText_HPix_CHIPn_fx(xiCHIP1,GLCD192X64_SIZEX_CHIP1,strlen_P((const char *)&vNombreASCII_DBase_To_Name_Zone[DBpointed]),SC_WIDTH, 2,2),	yiCHIP1+1 +SC_HEIGHT );
		ks0108Puts_P((const char *)&vNombreASCII_DBase_To_Name_Zone[DBpointed]);
	
		temp = ListBox_LoadnewDB( &listbox, (void *)pCADS_LENGTH_COMMON[DBpointed], _MAX_LENGTH_CADS_COMMON_, vNUMERO_CADENAS_THIS_VECTOR[DBpointed]);
	
		ClearInnerRegionListBox(&listbox);
	
		ks0108SelectFont(SC, ks0108ReadFontData, BLACK);
		fill_listbox(&listbox);
	
		return	temp;//siempre sera 0
	}

	