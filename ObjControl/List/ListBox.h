/*
 * XObjects.h
 *
 * Created: 20/03/2012 12:33:27 p.m.
 *  Author: JCaf
 */ 


#ifndef LISTBOX_H_
#define LISTBOX_H_

	#define LISTBOX_FORD	(0)
	#define LISTBOX_BACK	(1)
	
	//si en un mismo proceso se usa el mismo
	//layout(coordenadas, tipo de fuente) de la lista, entonces
	//solo habria que recargar el puntero a la DB
	typedef struct _class_listbox_
	{
		byte xipix;
		byte yipix;
		byte widthpix;
		byte heightpix;
		
		const uint8_t * font;
		byte font_heightpix;
		
		byte numfields_displayable;
		signed char count_numfields_displayable;//countinto_numfields_displayable
		//		
		void * thisDB;
		byte maxlengthofstring_thisDB;
		byte numelem_thisDB;
		signed char ptrbase_DB;
		
	}_class_listbox;

	void ListBox_init_dimension(
		_class_listbox * pobj_listbox,
		byte _xipix,
		byte _yipix,
		byte _widthpix,
		byte _heightpix,
		const uint8_t * font,
		byte _font_heightpix);
	
	void ListBox_create_box(_class_listbox * pobj_listbox);
	
	byte ListBox_LoadnewDB(
		_class_listbox * pobj_listbox,
		void * _thisDB,
		byte _maxlengthofelemstring_thisDB,
		byte _numelem_ThisDB);
	
	void ClearInnerRegionListBox(_class_listbox * pobj_listbox);
	
	void  fill_listbox(_class_listbox * pobj_listbox);
	
	byte ListBox_Ex(_class_listbox * pobj_listbox, byte Back_Ford);
	byte ListBox_get_last_elementpointed(_class_listbox *pobj_listbox);

	//void testXObject_List(void);

	extern _class_listbox listbox;//objeto re-usable 

#endif /* LISTBOX_H_ */