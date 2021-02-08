/*
 * XObjects_1.c
 *
 * Created: 20/03/2012 12:33:05 p.m.
 *  Author: JCaf.
 */ 
	#include "Includes/InitializeAllModules.h"	
	
	_class_listbox listbox;//objeto re-usable 
	
	void MarkFieldPointed(_class_listbox * pobj_listbox);

	void PrintNewFieldsFromThisDB(_class_listbox * pobj_listbox);

	////////////////////////////////////////////////////////////////////////////////////////
	//1.- Es necesario que antes de hacer la llamada, se establezca la tipografia a usar.
	//Retorna: La posicion del primer elemento, osea 0
	////////////////////////////////////////////////////////////////////////////////////////
	void ListBox_init_dimension(
							_class_listbox * pobj_listbox,
							byte _xipix,
							byte _yipix,
							byte _widthpix,
							byte _heightpix,
							const uint8_t * font,
							byte _font_heightpix)
	{
		pobj_listbox->xipix		= _xipix;
		pobj_listbox->yipix		= _yipix;
		pobj_listbox->widthpix	= _widthpix;
		pobj_listbox->heightpix	= _heightpix;
		
		pobj_listbox->font = font;
		//si array font tuviera una posicion fija de su altura, no habria necesidad de pasar _font_heightpix
		pobj_listbox->font_heightpix = _font_heightpix;
		pobj_listbox->numfields_displayable = (byte) (_heightpix / _font_heightpix);
	}
	void ListBox_create_box(_class_listbox * pobj_listbox)
	{
		ks0108DrawRect(	pobj_listbox->xipix,
						pobj_listbox->yipix,
						pobj_listbox->widthpix,
						pobj_listbox->heightpix,
						BLACK);
	}
	//devuelve elemento el primer elem. apuntado		
	byte ListBox_LoadnewDB(	_class_listbox * pobj_listbox,
							void * _thisDB,
							byte _maxlengthofelemstring_thisDB,
							byte _numelem_ThisDB)
	{
		pobj_listbox->thisDB				= _thisDB;
		pobj_listbox->maxlengthofstring_thisDB	= _maxlengthofelemstring_thisDB;//necesario para el casting del void*
		pobj_listbox->numelem_thisDB		= _numelem_ThisDB;
			
		pobj_listbox->ptrbase_DB = 0;
		pobj_listbox->count_numfields_displayable = 0;	//Cada vez q se crea una nueva lista, se resetean sus variables internas-> Constructor
			
		return (pobj_listbox->ptrbase_DB + pobj_listbox->count_numfields_displayable);	//Posc. elem.apuntado dentro de ThisDB
	}			
	
	void MarkFieldPointed(_class_listbox * pobj_listbox) 
	{	
		ks0108InvertRect(pobj_listbox->xipix+1,
						(pobj_listbox->yipix+3) +(pobj_listbox->count_numfields_displayable*pobj_listbox->font_heightpix),
						(pobj_listbox->widthpix-2),	
						(pobj_listbox->font_heightpix-1));
	}
	void ClearInnerRegionListBox(_class_listbox * pobj_listbox) 
	{	
		ks0108FillRect(	pobj_listbox->xipix+1,
						(pobj_listbox->yipix+3),
						(pobj_listbox->widthpix-2), 
		pobj_listbox->font_heightpix*pobj_listbox->numfields_displayable, WHITE);
	}
	
	void PrintNewFieldsFromThisDB(_class_listbox * pobj_listbox)
	{
		byte i;
		ks0108SelectFont(pobj_listbox->font , ks0108ReadFontData, BLACK);	
		
		for (i=0; i<pobj_listbox->numfields_displayable; i++)
		{
			ks0108GotoXY(pobj_listbox->xipix+2, (pobj_listbox->yipix+3) + (i*pobj_listbox->font_heightpix) );
			ks0108Puts_P((const char *) &(((const char(*)[pobj_listbox->maxlengthofstring_thisDB])pobj_listbox->thisDB)[pobj_listbox->ptrbase_DB+i]) );
			
			//Puntero que salta cada 11 posiciones( (const char(*)[11])thisDB)
			//en este caso le indica q posicion![OFFSET] 
			
			// &( (const char(*)[11])thisDB)[OFFSET] 
			//const char (*pvNombreDeEscena_FLASH)[_MAX_LENGTH_NOM_ESCENAS_] = vNombreDeEscena_FLASH;//referencial
		}
	}
	
	void  fill_listbox(_class_listbox * pobj_listbox)
	{
		PrintNewFieldsFromThisDB(pobj_listbox);	//Imprimir nuevos valores visibles en la lista
		MarkFieldPointed(pobj_listbox);						//Marcar actual
	}
	
	byte ListBox_Ex(_class_listbox * pobj_listbox, byte Back_Ford)
	{
		MarkFieldPointed(pobj_listbox);	//borra vid.inverso actual, antes de pasar al otro.
		
		if (Back_Ford == LISTBOX_FORD)
		{
			if (++pobj_listbox->count_numfields_displayable == pobj_listbox->numfields_displayable)
			{
				pobj_listbox->count_numfields_displayable = pobj_listbox->numfields_displayable-1;	//Trunca
				
				if (++pobj_listbox->ptrbase_DB > (pobj_listbox->numelem_thisDB - pobj_listbox->numfields_displayable) )		//hacer roll-over al DB.
				{
					pobj_listbox->ptrbase_DB = 0;
					pobj_listbox->count_numfields_displayable = 0;
				}
				ClearInnerRegionListBox(pobj_listbox);
			}
		}
		else
		{
			if (--pobj_listbox->count_numfields_displayable < 0)
			{
				pobj_listbox->count_numfields_displayable= 0;		//Trunca
				
				if (--pobj_listbox->ptrbase_DB < 0)					//hacer roll-over al DB.
				{
					pobj_listbox->ptrbase_DB = pobj_listbox->numelem_thisDB - pobj_listbox->numfields_displayable;
					pobj_listbox->count_numfields_displayable = pobj_listbox->numfields_displayable-1;
				}
				ClearInnerRegionListBox(pobj_listbox);
			}
		}
		
		fill_listbox(pobj_listbox);
		//PrintNewFieldsFromThisDB(pobj_listbox);			//Imprimir nuevos valores visibles en la lista
		//MarkFieldPointed();					//Marcar actual

		//return (pobj_listbox->ptrbase_DB + pobj_listbox->count_numfields_displayable);	//elem.apuntado dentro de ThisDB
		return ListBox_get_last_elementpointed(pobj_listbox);
	}
	
	byte ListBox_get_last_elementpointed(_class_listbox *pobj_listbox)
	{
		return (pobj_listbox->ptrbase_DB + pobj_listbox->count_numfields_displayable);
	}

	/*
	///////////////////////////////////////////////////////////////////////////////////////////////////////	
	void kk(void)
	{
		BitsQconfGrupo[0][0] = 0;			//tecla 1
		BitsQconfGrupo[0][1] = 1;			//tecla 2
		BitsQconfGrupo[0][2] = 2;			//tecla 3
		BitsQconfGrupo[0][3] = 3;			//tecla 4
		BitsQconfGrupo[0][4]= END_OF_GROUPn;
		NumeroDeGruposFormados = 1;
		//
		SettingBitsInRegister(vModeShoot_FireOnKeyPressed[0],0,0,0,0,1,1,1,1);		//key8-key1
		SettingBitsInRegister(vModeShoot_FireOnKeyPressedAndKeyRelease[0],0,0,0,0,0,0,0,0);		//key8-key1
		SettingBitsInRegister(vModeShoot_FireAtTimeExpired[0],0,0,0,0,0,0,0,0);		//key8-key1
		//
		SettingBitsInRegister(vModeTimmingReptt[0],0,0,0,0,1,0,1,1);		//key8-key1
		//Acepting overriding
		TriggerRepttGlobal = _KTE_TRIGGER_REPPT_500ms_;
		HoldingRepttGlobal = 50/5;	//expresados en *ms ->cada 5ms*10 = 50ms
	}

	void testXObject_List(void)
	{
		kk();	//keyboard
	
		ks0108SelectFont(SC, ks0108ReadFontData, BLACK);	
		
		ListBox_InitParams(	128,0,63,63,
							SC_HEIGHT, 
							vAmbienteDeCasa_FLASH,_MAX_LENGTH_CADS_COMMON_,	vNUMERO_CADENAS_THIS_VECTOR[0]);
		
		//ks0108DrawRect(128,0,63,63,BLACK);		//Todo dentro de la region del CHIP3
		
		while (1)
		{
		
			if (KB_KEY1_ReadyToRead())
			{
				ListBox_Ex(LISTBOX_FORD);
				//
				PlaySound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
				KB_KEY1_HasBeenRead();
			}
			
			if (KB_KEY2_ReadyToRead())
			{
				ListBox_Ex(LISTBOX_BACK);
				//
				PlaySound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
				KB_KEY2_HasBeenRead();
			}
			
			if (KB_KEY3_ReadyToRead())
			{
				PlaySound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
				KB_KEY3_HasBeenRead();
			}
			
			if (KB_KEY4_ReadyToRead())
			{	
				PlaySound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
				KB_KEY4_HasBeenRead();
			}
		}
				
	}//end fx		
	
	*/