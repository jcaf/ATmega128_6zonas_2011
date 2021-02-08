/*
 * NamingZone_1.c
 *
 * Created: 20/04/2012 12:04:42 p.m.
 *  Author: jcaf
 */ 

#include "Includes/InitializeAllModules.h"
	
const char vAmbienteDeCasa_FLASH[][_MAX_LENGTH_AMBIENTE_CASA_] PROGMEM={
"-VACIO-",
"Alero",
"Aseo",
"Balcon",
"Bar",
"Bodega",
"Cerco",
"Cesped",
"Cochera",
"Cocina",
"Comedor",
"CuartoServ",
"Despacho",
"Despensa",
"Desvan",
"Dormitorio",
"Entr.Auto",
"Entrada",
"Escalera",
"Estudio",
"Habitacion",
"Hall",
"Jardin",
"Lavadero",
"Lobby",
"Pared",
"Pasadiso",
"Pasillo",
"Patio",
"Pileta",
"Piscina",
"Piso",
"Planta",
"Portico",
"Puerta",
"Sala",
"Salon",
"Servicios",
"Sotano",
"Techo",
"Terraza",
"Ventana",
"Vestibulo",
};	

const char vTipoDeLuminaria_FLASH[][_MAX_LENGTH_TIPO_LUMINARIA_] PROGMEM ={
"-VACIO-",
"ampolla",
"apantallad",
"balasto",
"braquete",
"bombilla",
"candelabro",
"colgante",
"cristal",
"cubo",
"dicroico",
"difusor",
"esferico",
"estaca",
"faro",
"fluo frio",
"fluoBlanco",
"fluoresc.",
"foco",
"foco Ahorr",
"halogeno",
"halospot",
"hornacina",
"incandesc.",
"induccion",
"l.colgante",
"lamp.mesa",
"lamp.techo",
"lamp.pie",
"lampara",
"LED",
"Luz",
"luzDirect",
"luzIndirec",
"mercurio",
"RGB",
"nicho",
"parabolico",
"plafon",
"poste",
"reflector",
"sodio",
"spotlight",
"telescopic",
"tira",
};
const char vPosicionReferencia_FLASH[][_MAX_LENGTH_POSICION_REF_] PROGMEM ={
"-VACIO-",
"abajo",
"alto(a)",
"anterior",
"arriba",
"bajo(a)",
"centro",
"costado",
"cruzado",
"delantera",
"derecho(a)",
"diagonal",
"este",
"emb.pared",
"emb.piso",
"extremo",
"frente",
"fondo",
"izquierdo",
"int.1",
"int.2",
"int.3",
"int.4",
"int.5",
"int.6",
"int.7",
"int.8",
"int.9",
"lateral",
"mitad",
"noreste",
"noroeste",
"norte",
"oeste",
"posterior",
"piso",
"sector 1",
"sector 2",
"sector 3",
"sur",
"sureste",
"suroeste",
"techo",
"trasero(a)",
};
const char vOtrosEnCasa_FLASH[][_MAX_LENGTH_OTROS_EN_CASA_] PROGMEM ={
"-VACIO-",
"antena",
"bienvenida",
"chimenea",
"cielorraso",
"cobertizo",
"computer",
"doble",
"ingreso",
"pantalla",
"persiana",
"salida",
"seto",
"sol-sombra",
"tector",
"tabiqueria",
"terreno",
"timbre",
"tragaluz",
"1",
"2",
"3",
"4",
"5",
"6",
"7",
"8",
"9",
"10",
};

//const char vColours_FLASH[][] PROGMEM ={};//color cromo, mate, pavonado
//const char vShape_FLASH[][] PROGMEM ={};//forma	//plano,angosto, cuadrado..etc,etc
//const char vPower_FLASH[][] PROGMEM ={};//forma	//36W, 50W, baja tension..etc,etc
//const char vAdjetives_FLASH[][] PROGMEM ={}; //simple, doble, impermeable
//const char vMaterial_FLASH[][] PROGMEM ={}; //vidrio, hierro, bronce, metal, aluminio,acero,acero inx.etc..
	
	//EEMEM _stZONA stZona[NUM_ZONAS];//={2,2};	//Estructura en EEPROM
  ///////////////////////////////////////////////////////// Lista - derecha ////////////////////////
	#define _INTERLINEADO_ (SC_HEIGHT+2)	//13-1 = 12
	//#define _INITIAL_X_CHIP3_	(128-1)	//correguir
	
	#define _INITIAL_X_CHIP3_	(128)	//correguir
	
	#define _NUM_FIELDS_TO_SHOW_ (4)
	
	//
	#define _NUM_DBASE_TO_NAME_ZONE_ (4)
	//
	_pCADS_LENGTH_COMMON pCADS_LENGTH_COMMON[_NUM_DBASE_TO_NAME_ZONE_]={	
												vAmbienteDeCasa_FLASH,
												vTipoDeLuminaria_FLASH,
												vPosicionReferencia_FLASH,
												vOtrosEnCasa_FLASH,
											};
	
	
	const char vNombreASCII_DBase_To_Name_Zone[][_MAX_LENGTH_CADS_COMMON_] PROGMEM ={
												"Ambiente",
												"Luminaria",
												"Posicion",
												"Otros",
												};									
	

	byte vNUMERO_CADENAS_THIS_VECTOR[_NUM_DBASE_TO_NAME_ZONE_] ={
												sizeof(vAmbienteDeCasa_FLASH)/sizeof(vAmbienteDeCasa_FLASH[0]),
												sizeof(vTipoDeLuminaria_FLASH)/sizeof(vTipoDeLuminaria_FLASH[0]),
												sizeof(vPosicionReferencia_FLASH)/sizeof(vPosicionReferencia_FLASH[0]),
												sizeof(vOtrosEnCasa_FLASH)/sizeof(vOtrosEnCasa_FLASH[0]),
												};
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

	//_class_listbox listbox;//objeto re-usable para todo este menu
	
	byte ReturnToEscenas(void);
	
	byte ChooseIfEnter_SettingNameToZones(void);
	byte ChooseFromList(byte NumZona, byte NumField);
	
	byte GuardarCambios_ChooseFromList(byte NumZona, byte NumField,byte VectorApuntadoX, byte elemDeVectorApuntadoX);
	byte SeleccionarNuevoZonaCampo_ChooseFromList(void);
	
	//static byte smachine_SettingNameToZones;

	void SettKb_PutNameToZone(void)	
	{
		objkey[KB_iKEY1].key_properties.u.bf.OnKeyPressed  =1;
		objkey[KB_iKEY1].key_properties.u.bf.Reptt = 1;
		
		objkey[KB_iKEY2].key_properties.u.bf.OnKeyPressed  =1;
		objkey[KB_iKEY2].key_properties.u.bf.Reptt = 1;
		
		objkey[KB_iKEY3].key_properties.u.bf.OnKeyPressed  =1;
		objkey[KB_iKEY3].key_properties.u.bf.Reptt = 0;
		
		objkey[KB_iKEY4].key_properties.u.bf.OnKeyPressed  =1;
		objkey[KB_iKEY4].key_properties.u.bf.Reptt = 1;
	}
//DirectForce_And_Hold_MAX_PWM_BLGLCD();	//para esta configuracion->> se va a mantener 100% a ON BLGLCD
//exitfx = ChooseIfEnter_SettingNameToZones();
//}while (exitfx == 0);

	void Draw2RectsMarkActiveField(byte Pos, byte Colour)
	{
		ks0108DrawRect(xiCHIP2+2,Pos-1	,	59, 0,Colour);	//rectas q marcan el campo
		ks0108DrawRect(xiCHIP2+2,Pos+13	,	59, 0,Colour);	//rectas q marcan el campo
	}
	#define PrinNewDigitInASCIIAt_CampoAndZona() do{\
		PrintNewDigitInASCIIAt(CenterText_HPix_CHIP1(GLCD192X64_SIZEX_CHIP1,"Zona: 0",SC_WIDTH,2,0)  +LongitudText_Hpix("Zona:",SC_WIDTH) +2, 60-(SC_HEIGHT*2), SC_WIDTH, SC_HEIGHT, NumZona+1);	\
		PrintNewDigitInASCIIAt(CenterText_HPix_CHIP1(GLCD192X64_SIZEX_CHIP1,"Campo: 0",SC_WIDTH,2,0) +LongitudText_Hpix("Campo:",SC_WIDTH) +6, 60-(SC_HEIGHT), SC_WIDTH, SC_HEIGHT, NumField+1);	\
	}while(0)
	
	void InitializeEnter_SettingNameToZone(byte NumZona, byte NumField)
	{
		SettKb_PutNameToZone();
		
		ks0108SelectFont(SC, ks0108ReadFontData, BLACK);
		
		softcentric_clearallpixel_less1border_CHIP1();
		
		ks0108_PrintTextP_CenterH_CHIP1(1,"Nombrar",SC_WIDTH,2,-3); 
		ks0108InvertRect(1,1,61,SC_HEIGHT-1);
		
		ks0108_PrintTextP_CenterH_CHIP1( 1+(SC_HEIGHT)+2, "seleccione",SC_WIDTH, 2, 5);
		
		//
		ks0108DrawRect(1,60-(SC_HEIGHT*2 )-2,62,0,BLACK);				//Dibujar separador
		ks0108DrawRect(1,60-(SC_HEIGHT*2 )-1,61,(SC_HEIGHT*2)+3,BLACK);	//Dibujar recuadro /visto como doble linea
		//
		ks0108GotoXY( CenterText_HPix_CHIP1(GLCD192X64_SIZEX_CHIP1,"Zona: 0",SC_WIDTH,2,0) ,60-(SC_HEIGHT*2) );	
		ks0108Puts_P(PSTR("Zona:"));
		
		ks0108GotoXY( CenterText_HPix_CHIP1(GLCD192X64_SIZEX_CHIP1,"Campo: 0",SC_WIDTH,2,0) ,60-SC_HEIGHT );		
		ks0108Puts_P(PSTR("Campo:"));
		
		PrinNewDigitInASCIIAt_CampoAndZona();
		//
		//softcentric_clearallpixel_less1border_CHIP2();
		direct_clearallpixel_less1border_CHIP2();
		FindAndPrintNameOfZone(NumZona, xiCHIP2);
		Draw2RectsMarkActiveField(vGogoXY_VerticalFieldNameZone[NumField],BLACK);//Dibuja
	}
	
	signed char SettingNameToZone(void)
	{
		byte NumZona;
		byte NumField;
									//Dividir en 3 GLCD	//Presentar al centro de GLCD
		ks0108ClearScreen();
		DrawOnlyMarcoGlobalGLCD();
		DrawOnlyDivisionAt63();		//dentro de CHIP 1
		DrawOnlyDivisionAt128();	//dentro de CHIP 3

		NumZona=0;
		NumField=0;
		
		InitializeEnter_SettingNameToZone(NumZona, NumField);
		
		ListBox_init_dimension(&listbox, 128,0,63,63, SC, SC_HEIGHT);//todos comparten la misma caja(x,y,font) para listbox
		ListBox_create_box(&listbox);//todos comparten la misma caja(x,y,font) para listbox
		
		while (1)
		{
			if (KB_KEY1_ReadyToRead())
			{
				if (++NumZona == NUM_ZONAS)	{NumZona =0;}						
															
				//softcentric_clearallpixel_less1border_CHIP2();
				direct_clearallpixel_less1border_CHIP2();

				FindAndPrintNameOfZone(NumZona, xiCHIP2);	
				
				//Draw2RectsMarkActiveField(vGogoXY_VerticalFieldNameZone[NumField],WHITE);//borra
				NumField=0;
				Draw2RectsMarkActiveField(vGogoXY_VerticalFieldNameZone[NumField],BLACK);//dibuja

				PrinNewDigitInASCIIAt_CampoAndZona();
				
				playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
				KB_KEY1_HasBeenRead();
			}
	
			if (KB_KEY2_ReadyToRead())
			{
				Draw2RectsMarkActiveField(vGogoXY_VerticalFieldNameZone[NumField],WHITE);//borra
				
				if (++NumField == NUM_FIELDS_Q_COMPONEN_NOMBRE_DE_ZONA )	{NumField=0;}
					
				Draw2RectsMarkActiveField(vGogoXY_VerticalFieldNameZone[NumField],BLACK);//dibuja
				
				PrintNewDigitInASCIIAt( CenterText_HPix_CHIP1(GLCD192X64_SIZEX_CHIP1,"Campo: 0",SC_WIDTH,2,0) +((sizeof("Campo:")-1)*SC_WIDTH) +6,\
										60-(SC_HEIGHT), \
										SC_WIDTH, SC_HEIGHT, NumField+1);
				
				playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
				KB_KEY2_HasBeenRead();
			}
	
			if (KB_KEY3_ReadyToRead())
			{
				playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
				KB_KEY3_HasBeenRead();
				
				if ( ChooseFromList(NumZona, NumField) == 2)
				{
					return 1;
				}					
				InitializeEnter_SettingNameToZone(NumZona, NumField);	//Restaurando el contexto de menu actual
			}
			
			if (KB_KEY4_ReadyToRead())
			{	
				//if (Schedule_SettingNameToZone == 0)
				//{
					playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);	
					KB_KEY4_HasBeenRead();
					
					ScroolingZ_CHIP1();
					softcentric_clearallpixel_less1border_CHIP1();

					if (ReturnToEscenas())	//if (ReturnToMenuPadre_SettingNameToZone())
					{
						return 1;							
					}
					ScroolingZ_CHIP1();
					softcentric_clearallpixel_less1border_CHIP1();
					
					//Schedule_SettingNameToZone=0;

					InitializeEnter_SettingNameToZone(NumZona,NumField);

				//}
				//
			}		
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void FindAndPrintNameOfZone(byte NumZona, byte xiCHIPX)
	{
		byte i,y;
		byte VectorApuntadoX, elemDeVectorApuntadoX;
		
		ks0108SelectFont(SC, ks0108ReadFontData, BLACK);	//Set tipografia - obtener altura de tipografia SC_HEIGHT
		
		y=0;
		for (i=0;i<NUM_FIELDS_Q_COMPONEN_NOMBRE_DE_ZONA;i++)
		{
			//Carga desde EEPROM
			
			
			VectorApuntadoX = EEPROM_ReadByte( (const byte *) &objzone_epp[NumZona].NameZone.FIELD_LINK[i].VectorApuntadoX);
			elemDeVectorApuntadoX = EEPROM_ReadByte( (const byte *) &objzone_epp[NumZona].NameZone.FIELD_LINK[i].elemDeVectorApuntadoX);

			
			//VectorApuntadoX = EEPROM_ReadByte( (const byte *) &stZona[NumZona].FIELD_LINK[i].VectorApuntadoX);
			//elemDeVectorApuntadoX = EEPROM_ReadByte( (const byte *) &stZona[NumZona].FIELD_LINK[i].elemDeVectorApuntadoX);
			//
			//ks0108FillRect(xiCHIPX+1,vGogoXY_VerticalFieldNameZone[i]+1,(61),SC_HEIGHT-1,WHITE);
			//	
			if (elemDeVectorApuntadoX!= 0)
			{
				ks0108GotoXY(xiCHIPX+2,vGogoXY_VerticalFieldNameZone[y++]);					//Imprime en posicion...
				ks0108Puts_P(&pCADS_LENGTH_COMMON[VectorApuntadoX][elemDeVectorApuntadoX]);
			}
		}
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void SaveNameOfZoneToEEPROM(byte NumZona, byte NumField, byte VectorApuntadoX, byte elemDeVectorApuntadoX)
	{
		
		EEPROM_WriteByte((byte *)&objzone_epp[NumZona].NameZone.FIELD_LINK[NumField].VectorApuntadoX, VectorApuntadoX);
		EEPROM_WriteByte((byte *)&objzone_epp[NumZona].NameZone.FIELD_LINK[NumField].elemDeVectorApuntadoX, elemDeVectorApuntadoX);
		
		//EEPROM_WriteByte((byte *)&stZona[NumZona].FIELD_LINK[NumField].VectorApuntadoX, VectorApuntadoX);
		//EEPROM_WriteByte((byte *)&stZona[NumZona].FIELD_LINK[NumField].elemDeVectorApuntadoX, elemDeVectorApuntadoX);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//ListBox_InitParams siempre retorna 0
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	byte LoadNewListFromThisDB(byte DBpointed)
	{
		byte temp;
		ks0108FillRect(xiCHIP1+1, yiCHIP1+1 +SC_HEIGHT, (xfCHIP1-1)-(xiCHIP1+1), SC_HEIGHT, WHITE);	
		ks0108GotoXY( CenterText_HPix_CHIPn_fx(xiCHIP1,GLCD192X64_SIZEX_CHIP1,strlen_P(&vNombreASCII_DBase_To_Name_Zone[DBpointed]),SC_WIDTH, 2,2),
						yiCHIP1+1 +SC_HEIGHT );
		ks0108Puts_P(&vNombreASCII_DBase_To_Name_Zone[DBpointed]);
		
		temp = ListBox_LoadnewDB(&listbox,
								pCADS_LENGTH_COMMON[DBpointed],
								_MAX_LENGTH_CADS_COMMON_, 
								vNUMERO_CADENAS_THIS_VECTOR[DBpointed]);
		
		ClearInnerRegionListBox(&listbox);
		
		ks0108SelectFont(SC, ks0108ReadFontData, BLACK);	
		fill_listbox(&listbox);
		
		return	temp;//siempre sera 0
				
				//ListBox_InitParams siempre retorna 0
		
		
		
		//return	ListBox_InitParams(	&listbox,
		//128,0,63,63,
		//SC_HEIGHT,
		//pCADS_LENGTH_COMMON[DBpointed],_MAX_LENGTH_CADS_COMMON_, vNUMERO_CADENAS_THIS_VECTOR[DBpointed]);
		////ListBox_InitParams siempre retorna 0
//
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
	
	//Limpia 2 posiciones a la vertical, desde arriba
	#define ClearRegionWorkForAllEvent_ChooseFromList() do{ks0108FillRect(xiCHIP1+1, yiCHIP1+1 , (xfCHIP1-1)-(xiCHIP1+1), SC_HEIGHT*2, WHITE);}while(0)
	
	//////////////////////////////////////////////////////////////////////////////////////////////
	byte InitializeEnter_ChooseFromList(byte DBpointed)
	{
		ks0108SelectFont(SC, ks0108ReadFontData, BLACK);
		
		ClearRegionWorkForAllEvent_ChooseFromList();
		
		ks0108_PrintTextP_CenterH_CHIP1(1,"Diccionario",SC_WIDTH,2,1);
		ks0108InvertRect(xiCHIP1+1,yiCHIP1+1, (xfCHIP1-1)-(xiCHIP1+1),SC_HEIGHT-1);
		
		return LoadNewListFromThisDB(DBpointed);//siempre retornara 0
	}
	/********************************************************************************************
	********************************************************************************************/
	byte ChooseFromList(byte NumZona, byte NumField)
	{
		volatile byte DB_LastPointed;
		byte DB_LastElemPointed;

		byte CountDBpointed=0;
		byte Schedule_ChooseFromList=0;
		
		DB_LastElemPointed = InitializeEnter_ChooseFromList(CountDBpointed);	//inicia con 0
		
		while (1)
		{
			if (KB_KEY1_ReadyToRead())
			{
				DB_LastElemPointed= ListBox_Ex(&listbox, LISTBOX_FORD);
				//
				playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
				KB_KEY1_HasBeenRead();
			}
			//-----------------------------------------------------------------------------------------
			if (KB_KEY2_ReadyToRead())
			{
				DB_LastElemPointed= ListBox_Ex(&listbox,LISTBOX_BACK);
				//
				playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
				KB_KEY2_HasBeenRead();
			}
			//-----------------------------------------------------------------------------------------
			if (KB_KEY3_ReadyToRead())
			{
				DB_LastPointed = CountDBpointed;	//Guardar estos valores para opcion grabar
				
				ks0108FillRect(xiCHIP2+1,vGogoXY_VerticalFieldNameZone[NumField],(xfCHIP2-1)-(xiCHIP2+1), SC_HEIGHT-1,WHITE);	//Clear position
				ks0108GotoXY(xiCHIP2+2,vGogoXY_VerticalFieldNameZone[NumField]);	//print new text

				ks0108Puts_P(&pCADS_LENGTH_COMMON[CountDBpointed][DB_LastElemPointed]);					
				
				//
				playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
				KB_KEY3_HasBeenRead();
			}
			//-----------------------------------------------------------------------------------------
			if (KB_KEY4_ReadyToRead())
			{	
				if (Schedule_ChooseFromList == 0)	
				{
					if (++CountDBpointed < _NUM_DBASE_TO_NAME_ZONE_)
					{
						LoadNewListFromThisDB(CountDBpointed);	//Carga nueva lista
					}
					else
					{
						CountDBpointed =0;		
						Schedule_ChooseFromList++;
					}
					//
					playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);	
					KB_KEY4_HasBeenRead();
				}
				
				if (Schedule_ChooseFromList == 1)
				{	
					if ( GuardarCambios_ChooseFromList(NumZona, NumField, DB_LastPointed, DB_LastElemPointed) )
					{
						softcentric_clearallpixel_less1border_CHIP3();	//borra seccion visualizacion de la lista
						return 1;
					}
					Schedule_ChooseFromList++;
				}
				if (Schedule_ChooseFromList == 2)
				{
					if (SeleccionarNuevoZonaCampo_ChooseFromList())	
					{	
						softcentric_clearallpixel_less1border_CHIP3();		
						return 1;							
					}
					Schedule_ChooseFromList++;
				}
				
				if (Schedule_ChooseFromList == 3)
				{
					ClearRegionWorkForAllEvent_ChooseFromList();
					//if (ReturnToMenuPadre_ChooseFromList())	
					if (ReturnToEscenas())	
					{	
						softcentric_clearallpixel_less1border_CHIP3();		
						return 2;							
					}
					Schedule_ChooseFromList =0;
					
					InitializeEnter_ChooseFromList(CountDBpointed);	//Carga nueva lista
				}
			}		
		}
	}
	/***************************************************************************************
	***************************************************************************************/
	byte GuardarCambios_ChooseFromList(byte NumZona, byte NumField,byte VectorApuntadoX, byte elemDeVectorApuntadoX)
	{
		ks0108SelectFont(SC, ks0108ReadFontData, BLACK);
	
		ClearRegionWorkForAllEvent_ChooseFromList();
		
		ks0108_PrintTextP_CenterH_CHIP1(yiCHIP1+1,"Guardar",SC_WIDTH,2,-3);
		ks0108_PrintTextP_CenterH_CHIP1((yiCHIP1+1)+SC_HEIGHT,"cambio ?",SC_WIDTH,2,3);
		
		while (1)
		{
			if (KB_KEY1_ReadyToRead())	{KB_KEY1_HasBeenRead();}
			if (KB_KEY2_ReadyToRead())	{KB_KEY2_HasBeenRead();}
			
			if (KB_KEY3_ReadyToRead())
			{
				SaveNameOfZoneToEEPROM(NumZona, NumField, VectorApuntadoX, elemDeVectorApuntadoX);
				
				ClearRegionWorkForAllEvent_ChooseFromList();
				 
				ks0108_PrintTextP_CenterH_CHIP1(( ((yiCHIP1+1) +(SC_HEIGHT*2)) - (yiCHIP1-1) )/2,"Guardado!",SC_WIDTH,2,0);
				
				playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
				_delay_ms(500);	

				//ks0108FillRect(,WHITE);	//limpiar mensaje

				KB_KEY3_HasBeenRead();
				return 1;
			}
			if (KB_KEY4_ReadyToRead())
			{	
				playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
				KB_KEY4_HasBeenRead();
				return 0;
			}
		}			
	}
	/***************************************************************************************
	***************************************************************************************/
	byte SeleccionarNuevoZonaCampo_ChooseFromList(void)
    {
		ks0108SelectFont(SC, ks0108ReadFontData, BLACK);
	
		ClearRegionWorkForAllEvent_ChooseFromList();
		
		ks0108_PrintTextP_CenterH_CHIP1(yiCHIP1+1,"Nuevo",SC_WIDTH,2,-2);
		
		ks0108_PrintTextP_CenterH_CHIP1((yiCHIP1+1)+SC_HEIGHT,"nombre ?",SC_WIDTH,2,0);//2
		
        while (1)
        {
            if (KB_KEY1_ReadyToRead()){KB_KEY1_HasBeenRead();}
            if (KB_KEY2_ReadyToRead()){KB_KEY2_HasBeenRead();}
            
			if (KB_KEY3_ReadyToRead())
            {
				playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
                KB_KEY3_HasBeenRead();
				return 1; 
            }
            if (KB_KEY4_ReadyToRead())
            {
				playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
				KB_KEY4_HasBeenRead();
				return 0;
            }
        }
    }	
	/***************************************************************************************
	***************************************************************************************/
	byte ReturnToEscenas(void)
    {
		ks0108SelectFont(SC, ks0108ReadFontData, BLACK);
	
		//ClearRegionWorkForAllEvent_ChooseFromList();
		
		ks0108_PrintTextP_CenterH_CHIP1(yiCHIP1+1,"Retornar a",SC_WIDTH,2,2);
		
		ks0108_PrintTextP_CenterH_CHIP1((yiCHIP1+1)+SC_HEIGHT,"escenas ?",SC_WIDTH,2,2);
		
		while (1)
        {
            if (KB_KEY1_ReadyToRead()){KB_KEY1_HasBeenRead();}
            if (KB_KEY2_ReadyToRead()){KB_KEY2_HasBeenRead();}
            
			if (KB_KEY3_ReadyToRead())
            {
				playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
                KB_KEY3_HasBeenRead();
				return 1; 
            }
            if (KB_KEY4_ReadyToRead())
            {
				playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
				KB_KEY4_HasBeenRead();
				return 0;
            }
        }
    }
	
