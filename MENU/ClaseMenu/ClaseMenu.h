/*
 * ClaseMenu.h
 *
 * Created: 25/10/2012 10:31:18 a.m.
 *  Author: JCaf
 */ 


#ifndef CLASEMENU_H_
#define CLASEMENU_H_
	
	///////////////////////////////////////////////////	
	#define NUMMAX_OPTION_BYMENU (10)
	#define NUMMAX_PAGES_BYMENU (4)

	struct _xy_captions
	{	byte x;
		byte y;
	};
	struct _param_rect
	{	byte x;
		byte y;
		byte w;
		byte h;
	};
	
	struct _id_address
	{
		byte levelstack;
	};
	
	struct _menu_option_limits
	{
		signed char inf;
		signed char sup;
	};
	
	typedef struct _ClassMenu
	{
		struct _id_address id_address;

		PTRFXrVOID background_panel;

		const uint8_t * fontForCaptions;
		struct _registro
		{
			struct _xy_captions xy_captions;
			char captions[10];
			struct _param_rect param_rect;
			struct _param_rect param_invert_rect;
			PTRFXrVOID pfx;
		}registro[NUMMAX_OPTION_BYMENU];//numero de opciones

		struct _page
		{
			byte numelem;
			
			signed char link_anterior;
			signed char link_deingreso;
		
		}page[NUMMAX_PAGES_BYMENU];//maximos

		//variables operativas
		signed char current_page;
		signed char option;
		struct _menu_option_limits limit;
		//
	}ClassMenu;

	#define MENU_STACKLEVEL_MAXDEEP (5)
	
	struct _menu_operational
	{
		ClassMenu *pmenu;
		byte goto_address;
	
		struct _stack_track
		{
			ClassMenu *pmenu;
			signed char option;
			//signed char current_page;
			//struct _menu_option_limits limit;
		}stack_track[MENU_STACKLEVEL_MAXDEEP];
		
		byte sp;	//stackpointer
	};

	extern ClassMenu menu_main;
	extern ClassMenu menu_config;
	extern struct _menu_operational menu_operational;
	
	//-----------------Siguiente level----------------
	//{
		//[0]= direccion = levelstackN + option
		//[1]= padreN = levelstatckN-1 + option
		//[2]= padreN-1 = levelstackN-2 + option
	//}
	#define MENU_STACKLEVEL_0 (0)
	#define MENU_STACKLEVEL_1 (1)
	#define MENU_STACKLEVEL_2 (2)
	#define MENU_STACKLEVEL_3 (3)
	#define MENU_STACKLEVEL_4 (4)
	//
	#define MENU_OPTION_0	(0)
	#define MENU_OPTION_1	(1)
	#define MENU_OPTION_2	(2)
	#define MENU_OPTION_3	(3)
	#define MENU_OPTION_4	(4)
	#define MENU_OPTION_5	(5)
	//
	#define _MENU_FINAL_ADDRESS_ (0)
	
	#define address_menu_main__scene		(0)
	#define address_menu_main__zone			(1)
	#define address_menu_main__link			(2)
	//configuration:
	#define address_menu_config__scene		(3)
	#define address_menu_config__zone		(4)
	#define address_menu_config__system		(5)
		
void control_of_traffic(void);

void _back_option(ClassMenu *pmenu);
void _forward_option(ClassMenu *pmenu);

void _show_options_by_numpage(ClassMenu *pmenu);

//por ahora este frame sera global para todos los menus
void menu_main_background_panel0(void);

#endif /* CLASEMENU_H_ */