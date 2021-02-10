/*
 * Escenas_1.c
 *
 * Created: 05/03/2012 12:18:38 p.m.
 *  Author: jcaf
 */ 
/*********************************************
.sobjscene_commonprop_epp	@ 0x100
.sobjstorage_scene_epp		@ 0x200 (+0x200 of free-space)
.sobjzone_epp				@ 0x400 (+0x200 of free-space)

AVRStudio v6.0.1843
AVR/GNU Linker -> Memory setting -> EEPROM segment (adicionar)

.sobjscene_commonprop_epp=0x100
.sobjstorage_scene_epp=0x200               
.sobjzone_epp=0x400                    
**********************************************/
#include "Includes/InitializeAllModules.h"
#include <stdlib.h>
	//EEMEM _objscene_commonprop_epp objscene_commonprop_epp; //@ offset 256
	//EEMEM _objstorage_scene objstorage_scene_epp[_NUM_ESCENAS_MAXIMA_]; //@ offset 512 + (512 of space)
	_objscene_commonprop_epp objscene_commonprop_epp __attribute__((section(".sobjscene_commonprop_epp"))) = {0}; //@ offset 256
	_objstorage_scene objstorage_scene_epp[_NUM_ESCENAS_MAXIMA_] __attribute__((section(".sobjstorage_scene_epp")))= {0}; //@ offset 512 + (512 of space)
	
	//_objstorage_scene objstorage_scene_borrame[_NUM_ESCENAS_MAXIMA_];

	volatile struct _currentscene currentscene;
	volatile struct _ps_scene ps_scene;
	
	static void _preview(void);
	static void _execute(void);
	static void _preview__bkframewnd(void);
	
	volatile struct _previewscene previewscene = 
	{
		.preview = &_preview,
		.execute = &_execute,
		.preview__bkframewnd = &_preview__bkframewnd,
	};
	
	void print_numberofscene(byte scene);

	void init_scene(void)
	{
		byte zone;
		TYPEDC dc;
		
		ps_scene.totalofscenes = EEPROM_ReadByte((byte *)&objscene_commonprop_epp.totalofscenes);
		
		if (ps_scene.totalofscenes == 0x00)
		{
			currentscene.num_scene = ISNOT_A_SAVED_SCENE;	//0xFF
		}
		else
		{
			//carga la ultima scene 
			//currentscene.num_scene = EEPROM_ReadByte((byte *) &objscene_commonprop_epp.num_scene);
			currentscene.num_scene = 0x00;	//arranca con la scene #0
			
			
			/*
			17 ener 2012:
			Segun el analisis de hoy, el inicio cae en la condicion como si estuvieramos cambiando a una nueva escena.
			Tener en cuenta que en los cambios de escenas, se aplican restricciones(en el ON/OFF/RESTORES) y reglas.
			Si se obviaran estas restricciones/reglas, el sistema entraria en una catastrofe.
			
			Otra opcion de incorporar este parche, es hacerlo de forma serializada, y liberar la CPU al finalizar el cambio.
			
			Existe otro bug. y es que debe de verse los puntitos y la barras subiendo/bajando cuando se sale y se reingresa al modo de escena!
			tal vez lo dejo pasar este bug. para finalizar maniana viernes y conversar con Bruno.
			*/
			
			for (zone=0; zone<NUM_ZONAS; zone++)//inicializa escena #0
			{
				dc = get_dcofzone_ofscene_EEP(currentscene.num_scene, zone);
				
				//siguiendo un orden programatico
				//1.-
				ps_fading_inbk.bf.printdisplay = DISABLE;
				setting_preupdate_dc(zone, dc);
				updatedc_acctypeofload(zone);
				//2.-
				currentscene.objzone[zone].dc = dc;					
			}
			
			/*
			for (zone=0;zone<NUM_ZONAS;zone++)//inicializa escena #0
			{
				currentscene.objzone[zone].dc = get_dcofzone_ofscene_EEP(currentscene.num_scene, zone);
				objzone[zone].dc = currentscene.objzone[zone].dc;
			}
			*/
			
			//currentscene.num_name = EEPROM_ReadByte((byte *) &objstorage_scene_epp[currentscene.num_scene].num_name);	
		}
		
	}

	void _print_texts_scene(byte num_scene)	
	{
		ks0108SelectFont(SC, ks0108ReadFontData, BLACK);
		
		ks0108GotoXY(3,3);ks0108Puts_P(PSTR("Escena:"));
		
		if (num_scene == ISNOT_A_SAVED_SCENE)
		{	
			ks0108GotoXY(43,2);	ks0108Puts_P(PSTR("*"));
		}
		else
		{	
			ks0108SelectFont(Arial_Bold_14, ks0108ReadFontData, BLACK);
				ks0108GotoXY(43,2);	print_numberofscene(num_scene+1);
			ks0108SelectFont(SC, ks0108ReadFontData, BLACK);
		}
		ks0108InvertRect(2,2,59,12);
		
		ks0108GotoXY(2,19);	
		
		if (num_scene == ISNOT_A_SAVED_SCENE)
			{ks0108Puts_P(PSTR("****"));}
		else
		{	//currentscene.num_name = EEPROM_ReadByte((byte *) &objstorage_scene_epp[currentscene.num_scene].num_name		
			//por ahora no se usa currentscene.num_name para mantener un orden y limpieza en el codigo,
			//espero q esto no sobrecargue el "CPU halted", pues solo es 1 lectura mas al fin y al cabo
			
			//ks0108Puts_P(&vNombreDeEscena_FLASH[ EEPROM_ReadByte((byte *) &objstorage_scene_epp[currentscene.num_scene].num_name) ]);
			ks0108Puts_P( (const char *) &v_names_for_scenes[ EEPROM_ReadByte((byte *) &objstorage_scene_epp[num_scene].num_name) ]);
		}
	}
	
	static void _preview(void)//load,print txt and preview bar
	{
		byte zone;
		
		//load from eeprom
		previewscene.num_name =	EEPROM_ReadByte((byte *) &objstorage_scene_epp[previewscene.num_scene].num_name);
		
		for (zone=0; zone < NUM_ZONAS; zone++)
			{previewscene.dc_from_epp[zone]= get_dcofzone_ofscene_EEP(previewscene.num_scene,zone);	}
		//		
		ks0108SelectFont(SC, ks0108ReadFontData, BLACK);
		ks0108FillRect(45,19,61-45,31-19-1,WHITE);
		ks0108GotoXY(45,19); 
		print_numberofscene(previewscene.num_scene +1);

		ks0108FillRect(1,30,61,12,WHITE);
		ks0108GotoXY(2,30); 
		ks0108Puts_P((const char *)&v_names_for_scenes[previewscene.num_name]);
//++
CaptionOfAllZones();
DrawBarsVertOfAllZones();
_write_display_threshold_allzone();	
//++
		for (zone=0; zone < NUM_ZONAS; zone++)
		{
			directclearall_barlevel(zone);
			preview_dc_barlevel(zone, previewscene.dc_from_epp[zone]);
		}
	}
	static void _preview__bkframewnd(void)
	{
		//ks0108DrawRect(0,0,63,63,BLACK);
		//ks0108DrawRect(65,0,191-65,63,BLACK);
		direct_clearallpixel_less1border_CHIP1();
		ks0108SelectFont(SC, ks0108ReadFontData, BLACK);
		ks0108GotoXY(6,2);ks0108Puts_P(PSTR("Busqueda"));
		ks0108InvertRect(2,2,59,13);
		ks0108DrawHoriLine(0,17,63,BLACK);
		//
		//ks0108GotoXY(6,19);ks0108Puts_P(PSTR("Escena:"));
		//ks0108GotoXY(3,30);ks0108Puts_P(PSTR("Todos0%"));
		ks0108DrawHoriLine(0,44,63,BLACK);
		//
		ks0108GotoXY(21,46);ks0108Puts_P(PSTR("["));
		ks0108GotoXY(26,47);ks0108Puts_P(PSTR("ok"));
		ks0108GotoXY(41,46);ks0108Puts_P(PSTR("]"));
		//ks0108InvertRect(25,47, 14,10);//[ok]

		_draw_triangle_left(9,52);
		//_draw_triangle_left_contour(9,52);
		//_draw_triangle_left_solid_black(9,52);
		//_draw_triangle_left_solid_white(9,52);
		//
		_draw_triangle_rigth(54,52);
		//_draw_triangle_rigth_contour(54,52);
		//_draw_triangle_rigth_solid_black(54,52);
		//_draw_triangle_rigth_solid_white(54,52);
	}
	
	static void _execute(void)
	{
		byte zone;
		for (zone=0; zone<NUM_ZONAS; zone++)
		{
			setting_preupdate_dc(zone, previewscene.dc_from_epp[zone]);
			updatedc_acctypeofload(zone);
		
			//Add..
			if ( previewscene.dc_from_epp[zone] >= objzone[zone].dc )
			{
				directfill_barlevel(zone, objzone[zone].dc);
			}
			else
			{
				clear_and_directfill_barlevel(zone,objzone[zone].dc);
				preview_dc_barlevel(zone, previewscene.dc_from_epp[zone]);
			}
			//Add..
		}		
	}
	
	TYPEDC get_dcofzone_ofscene_EEP(byte num_scene, byte zone)
	{
																//return objstorage_scene_borrame[scene].objzone[zone].dc;
		if (sizeof(TYPEDC) == sizeof(unsigned int))
		{
			return EEPROM_ReadWord( (const TYPEDC *)&objstorage_scene_epp[num_scene].objzone[zone].dc);
		}
		else if (sizeof(TYPEDC) == sizeof(unsigned char))
		{
			return EEPROM_ReadByte( (const TYPEDC *)&objstorage_scene_epp[num_scene].objzone[zone].dc);
		}			
	}
	
	void set_dcofzone_ofscene_EPP(byte num_scene, byte zone, TYPEDC dc)
	{
		if (sizeof(TYPEDC) == sizeof(unsigned int))
		{
			EEPROM_WriteWord( (TYPEDC *)&objstorage_scene_epp[num_scene].objzone[zone].dc,  dc);//if_fadingactive_nextdc_else_dc(zone)
		}
		else if (sizeof(TYPEDC) == sizeof(unsigned char))
		{
			EEPROM_WriteByte( (TYPEDC *)&objstorage_scene_epp[num_scene].objzone[zone].dc,  dc);//if_fadingactive_nextdc_else_dc(zone)
		}
	}
	
	void print_numberofscene(byte scene)
	{
		char ascii[10];
		//sprintf(ascii,"%i",(scene));//2011
        itoa(scene, ascii, 10 );
		ks0108Puts(ascii);
	}

	void directclearall_barlevel_ofscene(void)
	{
		byte zone;
		for (zone=0; zone<NUM_ZONAS; zone++)
			{directclearall_barlevel(zone);}
	}
	
	
	//CONSISTENCIAR AL GRABAR Q TODOS LOS NIVELES ESTEN ESTABLES!!
	//otra podria ser <if_fadingactive_nextdc_else_dc(zone)	>
	void save_scene_epp(byte num_scene, byte num_name)
	{
		byte zone;
		
		for (zone=0; zone<NUM_ZONAS; zone++)
			{set_dcofzone_ofscene_EPP(num_scene, zone, objzone[zone].dc);}//o usar if_fadingactive_nextdc_else_dc(zone)		

		EEPROM_WriteByte((byte*) &objstorage_scene_epp[num_scene].num_name, num_name);
	}
	
	void _all_dcs_taked_as_currentscene(void)
	{
		byte zone;
		for (zone=0; zone<NUM_ZONAS; zone++)
			{currentscene.objzone[zone].dc = if_fadingactive_nextdc_else_dc(zone);}
	}
	///////////////////////////////////////////////////////////////////
	BOOL _all_dcs_of_currentscene__lessequalthan_threshold(void)// o <= 0x0
	{
		byte zone;
		for (zone=0; zone<NUM_ZONAS; zone++)
		{
			if (currentscene.objzone[zone].dc > objzone[zone].thrshld)
			{return FALSE;}
		}
		return TRUE;
	}
	
	BOOL _all_dcs_of_currentscene__areequalthan_current_dcs(void)// o <= 0x0
	{
		byte zone;
		for (zone=0; zone<NUM_ZONAS; zone++)
		{
			//if (currentscene.objzone[zone].dc != objzone[zone].dc)
			if (currentscene.objzone[zone].dc != if_fadingactive_nextdc_else_dc(zone))
				{return FALSE;}
		}
		return TRUE;
	}
	
	BOOL _all_dcs_of_objzone__equalthan_100porcent(void)//100%
	{
		byte zone;
		for (zone=0; zone<NUM_ZONAS; zone++)
		{
			//if ( objzone[zone].dc < MAX_VAL_DUTYCYCLE)
			if ( if_fadingactive_nextdc_else_dc(zone) < MAX_VAL_DUTYCYCLE)
			
				{return FALSE;}
		}
		return TRUE;
	}