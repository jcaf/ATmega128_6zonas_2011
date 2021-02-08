#include "Includes/InitializeAllModules.h"

	void link_handler(void);
	void menu_main_more0(void);
	void menu_main_config0(void);
	void menu_main_back0(void);
	//
	void config_scene(void);
	void config_zone(void);
	void config_system(void);
	void menu_config_back0(void);
	
	void menu_main_background_panel0(void);
	
	void _back_option(ClassMenu *pmenu);
	void _forward_option(ClassMenu *pmenu);
	//void _show_options_thispage(ClassMenu * pmenu);
	void _draw_invert_rect(ClassMenu * pmenu);
	void set_limits_through_numpage(ClassMenu * pmenu);
	#define NOEXIST_LINK_ANTERIOR (-1)
	
	ClassMenu menu_main=
	{
		.id_address.levelstack = MENU_STACKLEVEL_0,//id
		.background_panel = &menu_main_background_panel0,
		
		.fontForCaptions=Arial_Bold_14,
		.registro[0]={ {69,20}	,"Escenas"	,{66,16,59,20}	,{68,18,55,16}	,&scene_handler },		
		.registro[1]={ {140,20}	,"Zonas"	,{129,16,59,20}	,{131,18,55,16}	,&zone_handler },
		.registro[2]={ {75,44}	,"Enlace"	,{66,40,59,20}	,{68,42,55,16}	,&link_handler },
		.registro[3]={ {140,44}	,"Mas"		,{129,40,59,20}	,{131,42,55,16}	,&menu_main_more0 },
		//
		.registro[4]={ {75,20}	,"Config"	,{66,16,59,20}	,{68,18,55,16}	,&menu_main_config0 },
		.registro[5]={ {135,20}	,"Volver"	,{129,16,59,20}	,{131,18,55,16}	,&menu_main_back0 },
		
		.page[0].numelem=4,//pag0: 4 
		.page[0].link_anterior=NOEXIST_LINK_ANTERIOR;//-1 NO EXISTE
		.page[0].link_deingreso=0;	//Ingreso x default
		
		.page[1].numelem=2,//pag1: 2 
		.page[1].link_anterior=3;//se ingresa a traves de opcion 3
		.page[1].link_deingreso=4;	//Ingreso x default
	};
	/*
	ClassMenu menu_main=
	{
	{MENU_STACKLEVEL_0},//id
		
	{Arial_Bold_14,},
	{&menu_main_background_panel0},//tal vez dentro de cada pagina
		{
		{{69,20}	,{"Escenas"}	,{66,16,59,20}	,{68,18,55,16}		,{&scene_handler}},
		{{140,20}	,{"Zonas"}		,{129,16,59,20}	,{131,18,55,16}		,{&zone_handler}},
		{{75,44}	,{"Enlace"}		,{66,40,59,20}	,{68,42,55,16}		,{&link_handler}},
		{{140,44}	,{"Mas"}		,{129,40,59,20}	,{131,42,55,16}		,{&menu_main_more0}},
			//
		{{75,20}	,{"Config"}	,	{66,16,59,20}	,{68,18,55,16}		,{&menu_main_config0}},
		{{135,20}	,{"Volver"}		,{129,16,59,20}	,{131,18,55,16}		,{&menu_main_back0}},
		},
		{
		{4},//pag0: 4
		{2},//pag1: 2
		},
	};*/
	void menu_main_background_panel0(void)
	{
		DrawOnlyMarcoGlobalGLCD();
		ks0108DrawHoriLine(0,13,191,BLACK);
			
		ks0108SelectFont(Corsiva_12,ks0108ReadFontData,BLACK);
		ks0108GotoXY(3,1);
		ks0108Puts_P(PSTR("Jaime De-Souza-Ferreyra Ugarte"));
			
		//__Time and date
		ks0108SelectFont(Arial_Bold_14,ks0108ReadFontData,BLACK);
		ks0108GotoXY(4,30);	ks0108Puts_P(PSTR("12:00 pm"));
		ks0108SelectFont(SC,ks0108ReadFontData,BLACK);
		ks0108GotoXY(4,47);	ks0108Puts_P(PSTR("Dom"));
		ks0108GotoXY(30,47);	ks0108Puts_P(PSTR("21"));
		ks0108GotoXY(42,47);	ks0108Puts_P(PSTR("Oct"));
		//__
	}
	
	ClassMenu menu_config=
	{
		.id_address.levelstack = MENU_STACKLEVEL_1,//id
		.background_panel = &menu_main_background_panel0,
	
		.fontForCaptions=Arial_Bold_14,
		.registro[0]={ {69,20}	,"Escena"	,{66,16,59,20}	,{68,18,55,16}	,&config_scene },
		.registro[1]={ {140,20}	,"Zona"		,{129,16,59,20}	,{131,18,55,16}	,&config_zone },
		.registro[2]={ {75,44}	,"Sistema"	,{66,40,59,20}	,{68,42,55,16}	,&config_system },
		.registro[3]={ {140,44}	,"Volver"	,{129,40,59,20}	,{131,42,55,16}	,&menu_config_back0 },
		.page[0].numelem=4,//pag0: 4 
	};
	/*
	ClassMenu menu_config=
	{
	{MENU_STACKLEVEL_1},//id
	{Arial_Bold_14,},
	{&menu_main_background_panel0},//tal vez dentro de cada pagina
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
	*/
	struct _menu_operational menu_operational= { .pmenu = &menu_main};
	
	//////////////////////////////////////////////////////////////////
	//El sistema de menu, el vector 0 contiene la direccion final del camino
	//desde el padre, 	
	//////////////////////////////////////////////////////////////////
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
		{MENU_STACKLEVEL_0, MENU_OPTION_0, &menu_main},//direccion final
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
		{MENU_STACKLEVEL_1, MENU_OPTION_0, &menu_config},//menu objeto hijo: direccion final
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
	/////////////////////////////////////////////////////////////////////////	
	// SISTEMA DE DIRECCIONES - DIRECCIONES UNICAS 			               
	//#define address_menu_main__scene		(0)
	//#define address_menu_main__zone			(1)
	//#define address_menu_main__link			(2)
	//#define address_menu_main__more0		(3)
	//#define address_menu_main__config0		(4)
	////
	//#define address_menu_config__scene		(5)
	//#define address_menu_config__zone		(6)
	//#define address_menu_config__system		(7)
	//#define address_menu_config__back0		(8)
	//
	//p_target_address[0][0]->stacklevel;
	/////////////////////////////////////////////////////////////////////////	
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
	
	

	///////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////
	void push_menu(	ClassMenu *pmenu,
					signed char current_page,
					signed char option,
					signed char limit_inf,
					signed char limit_sup,
					)
	{

		menu_operational.stack_track[ menu_operational.sp ].pmenu = pmenu;
		menu_operational.stack_track[ menu_operational.sp ].current_page = current_page;
		//menu_operational.stack_track[ menu_operational.sp ].option = option;
		//menu_operational.stack_track[ menu_operational.sp ].limit.inf = limit_inf;
		//menu_operational.stack_track[ menu_operational.sp ].limit.sup = limit_sup;
		
		menu_operational.sp++; 
	}
	void pop_menu(void)
	{
	}
	
	byte _target_levelstack(void)
	{
		//p_target_address[0][0]->stacklevel;
		return p_target_address[menu_operational.goto_address][_MENU_FINAL_ADDRESS_]->stacklevel;
	}
	void control_of_traffic(void)
	{
		byte target_levelstack, sp;
		
		target_levelstack = _target_levelstack();
		sp = target_levelstack;
	
		if ( target_levelstack > menu_operational.pmenu->id_address.levelstack)
		{
			__forward_from_root();
		}
		else  if ( target_levelstack < menu_operational.pmenu->id_address.levelstack)
		{
			//desapila
			for ()
			{
				pop();
			}
			//i'm in the root, now execute
			__forward_from_root();
		}
		else // same level
		{
		
		}
	}
	
	void __forward_from_root(void)
	{
		byte i;
		for (i=0; i< (target_levelstack - p_current_menu->id_address.levelstack); i++ )
		{
			
			p_target_address[0][0]->stacklevel;
			
			option = target_address[sp];
			push_menu();//pmenu, 
			sp--;
		}
		//ejecuta funcion
		target_address[0]();
	}
	
	///////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////
	
	void _draw_invert_rect(ClassMenu * pmenu)
	{
		ks0108InvertRect(
		pmenu->registro[ pmenu->option ].param_invert_rect.x,
		pmenu->registro[ pmenu->option ].param_invert_rect.y,
		pmenu->registro[ pmenu->option ].param_invert_rect.w,
		pmenu->registro[ pmenu->option ].param_invert_rect.h);
	}
	
	//recupera pagina y limites directamente desde la option
	void set_page_and_limits(ClassMenu *pmenu)
	{
		byte acc=0;
		pmenu->limit.inf=0x00;
		pmenu->limit.sup=0x00;
		
		for (;;)
		{
			acc += pmenu->page[pmenu->current_page].numelem;
			
			pmenu->limit.sup = acc-1;
			if ( pmenu->option <= pmenu->limit.sup )
				{break;}
			else
			{
				pmenu->current_page++;
				pmenu->limit.inf = acc;
			}	
		}
	}
	void _forward_option(ClassMenu *pmenu)
	{
		_draw_invert_rect(pmenu);	
		
		if (++pmenu->option > pmenu->limit.sup)	
			{pmenu->option = pmenu->limit.inf;}
		
		_draw_invert_rect(pmenu);	
	}
	
	void _back_option(ClassMenu *pmenu)
	{
		_draw_invert_rect(pmenu);	
		
		if (--pmenu->option < pmenu->limit.inf)
			{pmenu->option = pmenu->limit.sup;}
		
		_draw_invert_rect(pmenu);	
	}

	/////////////////////////////////////////////////////////////
	//Set limits according current page
	// option is updated equal to lim.inf
	/////////////////////////////////////////////////////////////
	void set_limits_through_numpage(ClassMenu * pmenu)
	{
		byte i;
		
		pmenu->limit.inf = 0x00;
		pmenu->limit.sup = 0x00;
		
		for (i=0; i<= pmenu->current_page; i++)
			{pmenu->limit.sup += pmenu->page[i].numelem;}
		
		pmenu->limit.sup--;
		
		if (pmenu->current_page > 0)
			{pmenu->limit.inf = pmenu->page[ pmenu->current_page -1 ].numelem;}
		
		pmenu->option = pmenu->limit.inf;
	}

	////////////////////////////////////////////////////////////
	//To Show only is necessary the PAGE and the pointer to menu
	////////////////////////////////////////////////////////////
	void _show_options_thispage(ClassMenu *pmenu)
	{
		set_limits_through_numpage(pmenu);
		
		ks0108SelectFont(pmenu->fontForCaptions, ks0108ReadFontData, BLACK);
		byte i;
		for (i=pmenu->limit.inf ; i<=pmenu->limit.sup ; i++)
		{
			ks0108DrawRect( pmenu->registro[i].param_rect.x, pmenu->registro[i].param_rect.y,
							pmenu->registro[i].param_rect.w, pmenu->registro[i].param_rect.h, BLACK);
			ks0108GotoXY(pmenu->registro[i].xy_captions.x, pmenu->registro[i].xy_captions.y );
			ks0108Puts(pmenu->registro[i].captions);
		}
		_draw_invert_rect(pmenu);	
	}
	
	void _next_page(void)
	{
		//page++;
		//option = set_limits(page);//devuelve lim_inf q es la opcion por defecto marcada
	}
	void _previous_page(void)
	{
		//page--;
		//option = set_limits(page);//devuelve lim_inf q es la opcion por defecto marcada
	}

	void link_handler(void){}
	void menu_main_more0(void){}
	void menu_main_config0(void){}
	void menu_main_back0(void){}
	//
	void config_scene(void){}
	void config_zone(void){}
	void config_system(void){}
	void menu_config_back0(void){}

