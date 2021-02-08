#include "Includes/InitializeAllModules.h"

	#define MENU_STACKLEVEL_MAXDEEP (5)
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

	#define NUMMAX_OPTION_BYMENU (10)
	#define NUMMAX_PAGES_BYMENU (4)
	
	void link_handler(void);
	void menu_main_more0(void);
	void menu_main_config0(void);
	void menu_main_back0(void);
	//
	void config_scene(void);
	void config_zone(void);
	void config_system(void);
	void menu_config_back0(void);
	
	void background_panel0(void);
	
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
		
	typedef struct _ClassMenu
	{
		struct _id_address id_address;
		
		const uint8_t * fontForCaptions;
		PTRFXrVOID background_panel;				

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
		}page[NUMMAX_PAGES_BYMENU];//maximos

		signed char current_page;	
		//
		byte base;
		byte offset_item;
		//

	}ClassMenu;

	void __draw_invert_rect(ClassMenu * pmenu);
	void _show_options_thispage(ClassMenu * pmenu);
	void _extractor(ClassMenu * pmenu);
	
	ClassMenu menu_main=
	{
		{MENU_STACKLEVEL_0},//id
		{Arial_Bold_14,},
		{&background_panel0},//tal vez dentro de cada pagina
		{
			{{69,20}	,{"Escenas"}	,{66,16,59,20}	,{68,18,55,16}		,{&scene_handler}},		
			{{140,20}	,{"Zonas"}		,{129,16,59,20}	,{131,18,55,16}		,{&zone_handler}},
			{{75,44}	,{"Enlace"}		,{66,40,59,20}	,{68,42,55,16}		,{&link_handler}},
			{{140,44}	,{"Mas"}		,{129,40,59,20}	,{131,42,55,16}		,{&menu_main_more0}},
			//
			{{69,20}	,{"Config"}	,	{68,18,55,16}	,{68,18,55,16}		,{&menu_main_config0}},
			{{140,20}	,{"Volver"}		,{131,18,55,16}	,{131,18,55,16}		,{&menu_main_back0}},
		},
		{
			{4},//pag0: 4 
			{2},//pag1: 2 
		},
	};
	//--------------------------------------------------------------------------------------------
	ClassMenu menu_config=
	{
		{MENU_STACKLEVEL_1},//id
		{Arial_Bold_14,},
		{&background_panel0},//tal vez dentro de cada pagina
		{
			{{69,20}	,{"Escena"}		,{66,16,59,20}	,{68,18,55,16}		,{&config_scene}},
			{{140,20}	,{"Zona"}		,{129,16,59,20}	,{131,18,55,16}		,{&config_zone}},
			{{75,44}	,{"Sistema"}	,{66,40,59,20}	,{68,42,55,16}		,{&config_system}},
			{{140,44}	,{"Volver"}		,{129,40,59,20}	,{131,42,55,16}		,{&menu_config_back0}},
		},
		{
			{4},
		},
	};
	
	////////////////////////////////////////////////////////////////////////////////////////////////
	void _extractor(ClassMenu * pmenu)//trabajo con maximos 
	{
		byte i;
		//add num of elements of pages anteriores
		pmenu->base= 0;
		if ( pmenu->current_page > 0)
		{
			for (i=0; i<pmenu->current_page;i++)//acumula desde 0..(currentpage-1)
				{pmenu->base += pmenu->page[i].numelem;}//obtiene base
		}
	}
	
	void find_page_and_limits(byte option)
	{
		byte lim_inf=0;
		byte lim_sup=0;
		byte acc=0;
		byte npage=0;
		
		for (;;)
		{
			acc += page[npage];
			
			lim_sup = acc-1;
			if ( option <= lim_sup )
				{break;}
			else
			{
				npage++;
				lim_inf = acc;
			}	
		}
	}
	
	void _show_options_thispage(ClassMenu * pmenu)
	{
		byte i,y;
		
		_extractor(pmenu);
		ks0108SelectFont(pmenu->fontForCaptions, ks0108ReadFontData,BLACK);
		i=pmenu->base;
		
		for (y=0; y<pmenu->page[ pmenu->current_page].numelem; y++)
		{
			ks0108DrawRect(	pmenu->registro[i].param_rect.x, pmenu->registro[i].param_rect.y,
							pmenu->registro[i].param_rect.w, pmenu->registro[i].param_rect.h,BLACK);
			ks0108GotoXY(pmenu->registro[i].xy_captions.x, pmenu->registro[i].xy_captions.y );
			ks0108Puts(pmenu->registro[i].captions);
			
			i++;
		}
		
		__draw_invert_rect(pmenu);	//__draw_invert_rect(pmenu->base + pmenu->offset_item);
	}
	
	void _xxx(ClassMenu * pmenu)
	{
		if (++pmenu->offset_item	> pmenu->page[ pmenu->current_page ].numelem)
			{pmenu->offset_item=0x00;}
				
		__draw_invert_rect(pmenu);
	}

	void __draw_invert_rect(ClassMenu * pmenu)
	{
		ks0108InvertRect(
		pmenu->registro[ pmenu->base + pmenu->offset_item ].param_invert_rect.x,
		pmenu->registro[ pmenu->base + pmenu->offset_item ].param_invert_rect.y,
		pmenu->registro[ pmenu->base + pmenu->offset_item ].param_invert_rect.w,
		pmenu->registro[ pmenu->base + pmenu->offset_item ].param_invert_rect.h);
	}

	
	/////////////////////////////////////
	void vicoc()
	{
		menu_main.current_page = 2;
		_show_options_thispage(&menu_main);
		while(1);
	}

	void enlace_handler(void)
	{
	}
	void config(void)
	{
		_show_options_thispage(&menu_config);
	}
	void fx_retornar(void)
	{
		//pop function
	
	}

	void config_system(void)
	{
	}
	void config_scene(void)
	{
	}
	void config_zone(void)
	{
	}
	void background_panel0(void)
	{
	}

	struct _target_address
	{
		byte stacklevel;
		byte option;
		ClassMenu *pmenu;
	};
	//menu_main
	//______________
	//ESCENA(0) ZONAS(1)
	//ENLACE(2) MAS(3)
	//______________
	//______________
	//CONFIG(4) VOLVER(5)
	//______________
	//
	struct _target_address menu_main__scene[MENU_STACKLEVEL_MAXDEEP]=
	{
		{MENU_STACKLEVEL_0, MENU_OPTION_0, &menu_main},
	};
	struct _target_address menu_main__zone[MENU_STACKLEVEL_MAXDEEP]=
	{
		{MENU_STACKLEVEL_0, MENU_OPTION_1, &menu_main},
	};
	struct _target_address menu_main__link[MENU_STACKLEVEL_MAXDEEP]=
	{
		{MENU_STACKLEVEL_0, MENU_OPTION_2, &menu_main},
	};
	struct _target_address menu_main__more0[MENU_STACKLEVEL_MAXDEEP]=
	{
		{MENU_STACKLEVEL_0, MENU_OPTION_3, &menu_main},
	};
	struct _target_address menu_main__config0[MENU_STACKLEVEL_MAXDEEP]=
	{
		{MENU_STACKLEVEL_0, MENU_OPTION_4, &menu_main},
	};
	struct _target_address menu_main__back0[MENU_STACKLEVEL_MAXDEEP]=
	{
		{MENU_STACKLEVEL_0, MENU_OPTION_5, &menu_main},
	};
	//...................................................................
	//menu_config
	//______________
	//ESCENA(0) ZONA(1)
	//SYSTEM(2) VOLVER(3)
	//______________
	struct _target_address menu_config__scene[MENU_STACKLEVEL_MAXDEEP]=
	{
		{MENU_STACKLEVEL_1, MENU_OPTION_0, &menu_config},//menu objeto hijo
		{MENU_STACKLEVEL_0, MENU_OPTION_4, &menu_config},//menu objeto padre
	};
	struct _target_address menu_config__zone[MENU_STACKLEVEL_MAXDEEP]=
	{
		{MENU_STACKLEVEL_1, MENU_OPTION_1, &menu_config},
		{MENU_STACKLEVEL_0, MENU_OPTION_4, &menu_config},
	};
	struct _target_address menu_config__system[MENU_STACKLEVEL_MAXDEEP]=
	{
		{MENU_STACKLEVEL_1, MENU_OPTION_2, &menu_config},
		{MENU_STACKLEVEL_0, MENU_OPTION_4, &menu_config},
	};
	struct _target_address menu_config__back0[MENU_STACKLEVEL_MAXDEEP]=
	{
		{MENU_STACKLEVEL_1, MENU_OPTION_3, &menu_config},
		{MENU_STACKLEVEL_0, MENU_OPTION_4, &menu_config},
	};
	/************************************************************************/
	/* SISTEMA DE DIRECCIONES - DIRECCIONES UNICAS 			               */
	/************************************************************************/
	#define address_menu_main__scene		(0)
	#define address_menu_main__zone			(1)
	#define address_menu_main__link			(2)
	#define address_menu_main__more0		(3)
	#define address_menu_main__config0		(4)
	//
	#define address_menu_config__scene		(5)
	#define address_menu_config__zone		(6)
	#define address_menu_config__system		(7)
	#define address_menu_config__back0		(8)

	struct _target_address (*p_target_address[]) [MENU_STACKLEVEL_MAXDEEP]=
	{
		&menu_main__scene,
		&menu_main__zone,
		&menu_main__link,
		&menu_main__more0,
		&menu_main__config0,
	
		&menu_config__scene,
		&menu_config__zone,
		&menu_config__system,
		&menu_config__back0,
	};
	//p_target_address[0][0]->stacklevel;
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	byte stack[10];

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	ClassMenu * p_current_menu;

	void push_menu()
	{
	}
	void pop_menu()
	{
	}
	
	byte _target_levelstack(void)
	{
		//p_target_address[0][0]->stacklevel;
		byte _target_;
		return p_target_address[_target_][0]->stacklevel;
	}
	
	void control_of_traffic(void)
	{
		byte target_levelstack, sp;
		byte i;
		byte option;
	
		target_levelstack = _target_levelstack();
		sp = target_levelstack;
	
		if ( target_levelstack > p_current_menu->id_address.levelstack)
		{
			__forward_from_root();
		}
		else  if ( target_levelstack < p_current_menu->id.levelstack )
		{
			//desapila
			for ()
			{
				pop();
			}
			//i'm in the root, now execute
			__forward_from_root();
		}
		else
		{
		
		}
	}
	//.............................................................................
	void __forward_from_root()
	{
		for (i=0; i< (target_levelstack - p_current_menu->id_address.levelstack); i++ )
		{
			option = target_address[sp];
			push_menu();//pmenu, base+option
			sp--;
		}
		//ejecuta funcion
		target_address[0]();
	}
	