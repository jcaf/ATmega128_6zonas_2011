#include "Includes/InitializeAllModules.h"

	void link_handler(void);
	//void menu_main_more0(void);
	void menu_main_config0(void);
	//void menu_main_back0(void);//replaced by general function "back_page"
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
	void set_limits_by_current_page(ClassMenu * pmenu);
	
	void _next_page(ClassMenu * pmenu);
	void _back_page(ClassMenu * pmenu);
	
	void next_page(void);
	void back_page(void);
	
	
	#define NOEXIST_LINK_ANTERIOR (-1)

	//clear menu_space
	#define cleardisp_scope_of_menu() do{ks0108FillRect(66,16, 191-66 -1,63-16 -1,WHITE);}while(0)
		
	ClassMenu menu_main=
	{
		.id_address.levelstack = MENU_STACKLEVEL_0,//id
		.background_panel = &menu_main_background_panel0,
		
		.fontForCaptions=Arial_Bold_14,
		.registro[0]={ {69,20}	,"Escenas"	,{66,16,59,20}	,{68,18,55,16}	,&scene_handler },		
		.registro[1]={ {140,20}	,"Zonas"	,{129,16,59,20}	,{131,18,55,16}	,&zone_handler },
		.registro[2]={ {79,44}	,"Crear"	,{66,40,59,20}	,{68,42,55,16}	,&scene_add_handler},//"Enlace" 
		.registro[3]={ {140,44}	,"Mas"		,{129,40,59,20}	,{131,42,55,16}	,&next_page},//menu_main_more0
		//
		.registro[4]={ {75,20}	,"Config"	,{66,16,59,20}	,{68,18,55,16}	,&menu_main_config0 },
		.registro[5]={ {135,20}	,"Volver"	,{129,16,59,20}	,{131,18,55,16}	,&back_page},//menu_main_back0 
		
		.page[0].numelem=4,//pag0: 4 
		.page[0].link_anterior=NOEXIST_LINK_ANTERIOR,//-1 NO EXISTE
		.page[0].link_deingreso=0,	//Ingreso x default
		
		.page[1].numelem=2,//pag1: 2 
		.page[1].link_anterior=3,//se ingresa a traves de opcion 3
		.page[1].link_deingreso=4,	//Ingreso x default
	};
	
	void menu_main_background_panel0(void)
	{
		DrawOnlyMarcoGlobalGLCD();
		ks0108DrawHoriLine(0,13,191,BLACK);
			
		ks0108SelectFont(SC,ks0108ReadFontData,BLACK);
		ks0108GotoXY(3,1);
		
		ks0108Puts_P(PSTR("Familia Quispe Castillo"));
			
		//__Time and date
		//ks0108SelectFont(Arial_Bold_14,ks0108ReadFontData,BLACK);
		//ks0108GotoXY(4,30);	ks0108Puts_P(PSTR("12:00 pm"));
		//ks0108SelectFont(SC,ks0108ReadFontData,BLACK);
		//ks0108GotoXY(4,47);	ks0108Puts_P(PSTR("Dom"));
		//ks0108GotoXY(30,47);	ks0108Puts_P(PSTR("25"));
		//ks0108GotoXY(42,47);	ks0108Puts_P(PSTR("Nov"));
		//__
	}
	
	ClassMenu menu_config=
	{
		.id_address.levelstack = MENU_STACKLEVEL_1,//id
		.background_panel = &menu_main_background_panel0,
	
		.fontForCaptions=Arial_Bold_14,
		.registro[0]={ {74,20}	,"Borrar"	,{66,16,59,20}	,{68,18,55,16}	,&delete_scene_handler},//"Escena"&config_scene 
		.registro[1]={ {135,20}	,"Nombre"		,{129,16,59,20}	,{131,18,55,16}	,&SettingNameToZone},//"Zona"	ok! &config_zone 
		.registro[2]={ {79,44}	,"Carga"	,{66,40,59,20}	,{68,42,55,16}	,&RG_SDNDL_Menu },//"Sistema"ok! &config_system 
		.registro[3]={ {140,44}	,"Volver"	,{129,40,59,20}	,{131,42,55,16}	,&menu_config_back0 },
		
		.page[0].numelem=4,//pag0: 4 
		.page[0].link_anterior=NOEXIST_LINK_ANTERIOR,//-1 NO EXISTE
		.page[0].link_deingreso=0,	//Ingreso x default
	};
	
	struct _menu_operational menu_operational= { .pmenu = &menu_main};
	
	//////////////////////////////////////////////////////////////////
	//El sistema de menu, el vector 0 contiene la direccion final del camino
	//desde el padre, 	
	//////////////////////////////////////////////////////////////////
	struct _target_address
	{
		byte stacklevel;
		ClassMenu *pmenu;
		signed char option;
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
		{MENU_STACKLEVEL_0, &menu_main, MENU_OPTION_0 },//direccion final
	};
	struct _target_address menu_main__zone[MENU_STACKLEVEL_MAXDEEP]=
	{
		{MENU_STACKLEVEL_0, &menu_main, MENU_OPTION_1 },
	};
	struct _target_address menu_main__link[MENU_STACKLEVEL_MAXDEEP]=
	{
		{MENU_STACKLEVEL_0, &menu_main, MENU_OPTION_2 },
	};
	//struct _target_address menu_main__more0[MENU_STACKLEVEL_MAXDEEP]=
	//{
		//{MENU_STACKLEVEL_0, &menu_main, MENU_OPTION_3 },
	//};
	//struct _target_address menu_main__config0[MENU_STACKLEVEL_MAXDEEP]=
	//{
		//{MENU_STACKLEVEL_0, &menu_main, MENU_OPTION_4 },
	//};
	//struct _target_address menu_main__back0[MENU_STACKLEVEL_MAXDEEP]=
	//{
		//{MENU_STACKLEVEL_0, &menu_main, MENU_OPTION_5 },
	//};
	
	//...................................................................
	//menu_config
	//______________
	//ESCENA(0) ZONA(1)
	//SYSTEM(2) VOLVER(3)
	//______________
	struct _target_address menu_config__scene[MENU_STACKLEVEL_MAXDEEP]=
	{
		{MENU_STACKLEVEL_1, &menu_config, MENU_OPTION_0 },//menu objeto hijo: direccion final
		{MENU_STACKLEVEL_0, &menu_config, MENU_OPTION_4 },//menu objeto padre
	};
	struct _target_address menu_config__zone[MENU_STACKLEVEL_MAXDEEP]=
	{
		{MENU_STACKLEVEL_1, &menu_config, MENU_OPTION_1 },
		{MENU_STACKLEVEL_0, &menu_config, MENU_OPTION_4 },
	};
	struct _target_address menu_config__system[MENU_STACKLEVEL_MAXDEEP]=
	{
		{MENU_STACKLEVEL_1, &menu_config, MENU_OPTION_2 },
		{MENU_STACKLEVEL_0, &menu_config, MENU_OPTION_4 },
	};
	//struct _target_address menu_config__back0[MENU_STACKLEVEL_MAXDEEP]=
	//{
		//{MENU_STACKLEVEL_1, &menu_config, MENU_OPTION_3 },
		//{MENU_STACKLEVEL_0, &menu_config, MENU_OPTION_4 },
	//};
	
	/////////////////////////////////////////////////////////////////////////	
	// SISTEMA DE DIRECCIONES - DIRECCIONES UNICAS 			               
	// ONLY FUNCTIONS EXECUTABLES!!!! NO "next/back _page"
	//
	//&menu_main__more0,	//no ejecuta
	//&menu_main__config0,	//no ejecuta
	//&menu_main__back0,	//no ejecuta
	//&menu_config__back0,	//no ejecuta
	//
	//p_target_address[0][0]->stacklevel;
	/////////////////////////////////////////////////////////////////////////	
	
	struct _target_address (*p_target_address[]) [MENU_STACKLEVEL_MAXDEEP]=
	{
		&menu_main__scene,
		&menu_main__zone,
		&menu_main__link,
		//configuration:
		&menu_config__scene,
		&menu_config__zone,
		&menu_config__system,
	};
	
	void __forward_from_root(void);
	
	void push_menu(ClassMenu *pmenu, signed char option)
	{
		menu_operational.stack_track[ menu_operational.sp ].pmenu = pmenu;
		menu_operational.stack_track[ menu_operational.sp ].option = option;
		menu_operational.sp++; 
	}
	void pop_menu(void)
	{
		menu_operational.sp--; 
		menu_operational.pmenu = menu_operational.stack_track[ menu_operational.sp ].pmenu;
		menu_operational.pmenu->option = menu_operational.stack_track[ menu_operational.sp ].option;
	}
	byte get_target_levelstack(void)
	{
		return p_target_address[menu_operational.goto_address][_MENU_FINAL_ADDRESS_]->stacklevel;
	}
	byte get_target_option(void)
	{
		return p_target_address[menu_operational.goto_address][_MENU_FINAL_ADDRESS_]->option;
	}
	void control_of_traffic(void)
	{
		byte target_levelstack = get_target_levelstack();

		if ( target_levelstack > menu_operational.pmenu->id_address.levelstack)
		{ 
			__forward_from_root();
		}
		else  if ( target_levelstack < menu_operational.pmenu->id_address.levelstack)
		{
			//desapila hasta level0
			for (;;)
			{
				pop_menu();
			}
			//i'm in the root, now execute
			__forward_from_root();
		}
		else // same level
		{
			//menu_operational.pmenu->registro[menu_operational.pmenu->option].pfx();
			menu_operational.pmenu->option = get_target_option();
		}
	}
	//////////////////////////////////////////////////////////////////////////////////////////////	
	//Leave all prepare to execute
	//////////////////////////////////////////////////////////////////////////////////////////////
	void __forward_from_root(void)
	{
		byte target_levelstack = get_target_levelstack();
		byte diff = target_levelstack - menu_operational.pmenu->id_address.levelstack;
		byte sp = diff;
		byte i;
		for (i=0; i< diff; i++ )
		{
			push_menu(	p_target_address[menu_operational.goto_address][sp]->pmenu,
						p_target_address[menu_operational.goto_address][sp]->option	);
			sp--;		//leave option next to execute
		}
		//update
		menu_operational.pmenu = p_target_address[menu_operational.goto_address][sp]->pmenu;
		menu_operational.pmenu->option = p_target_address[menu_operational.goto_address][sp]->option;
	}

	void _draw_invert_rect(ClassMenu * pmenu)
	{
		ks0108InvertRect(
		pmenu->registro[ pmenu->option ].param_invert_rect.x,
		pmenu->registro[ pmenu->option ].param_invert_rect.y,
		pmenu->registro[ pmenu->option ].param_invert_rect.w,
		pmenu->registro[ pmenu->option ].param_invert_rect.h);
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
	//recupera pagina y limites directamente desde la option
	
	/*void set_page_and_limits_by_numoption(ClassMenu *pmenu)
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
	}*/
	void set_page_by_numoption(ClassMenu *pmenu)
	{
		byte acc=0;
		pmenu->current_page = 0x00;
		for (;;)
		{
			acc += pmenu->page[pmenu->current_page].numelem;
			
			if ( pmenu->option <= (acc-1) )
				{break;}
			else
				{pmenu->current_page++;}
		}
	}

	/////////////////////////////////////////////////////////////
	//Set limits according current page
	// option is updated equal to lim.inf
	/////////////////////////////////////////////////////////////
	void set_limits_by_current_page(ClassMenu * pmenu)
	{
		byte i;
		
		pmenu->limit.inf = 0x00;
		pmenu->limit.sup = 0x00;
		
		for (i=0; i<= pmenu->current_page; i++)
			{pmenu->limit.sup += pmenu->page[i].numelem;}
		
		pmenu->limit.sup--;
		
		if (pmenu->current_page > 0)
			{pmenu->limit.inf = pmenu->page[ pmenu->current_page -1 ].numelem;}
	}
	////////////////////////////////////////////////////////////
	//To Show only is necessary the PAGE and the pointer to menu
	//NOTE: Previously, option has been presetting!
	////////////////////////////////////////////////////////////
	void _show_options_by_numpage(ClassMenu *pmenu)
	{
set_page_by_numoption(pmenu);//REDUNDANDO EN ESTE PUNTO

		set_limits_by_current_page(pmenu);
		
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
	
	////////////////////////at same stack level////////////////////
	//
	///////////////////////////////////////////////////////////////
	//#define _ONLY_USE_LINK_DEINGRESO_
	
	void next_page(void)
	{
		cleardisp_scope_of_menu();
		_next_page(menu_operational.pmenu);
		
		shell.coderet = (CODERETURN_TOSHELL)NO_CHANGES;
	}
	void back_page(void)
	{
		cleardisp_scope_of_menu();
		_back_page(menu_operational.pmenu);
		
		shell.coderet = (CODERETURN_TOSHELL)NO_CHANGES;
	}
	//..............................................................
	void _next_page(ClassMenu *pmenu)
	{
		pmenu->current_page++;
		//set new value of option for next page
		pmenu->option = pmenu->page[pmenu->current_page].link_deingreso;
		_show_options_by_numpage(pmenu);
	}
	void _back_page(ClassMenu *pmenu)
	{
		#ifdef _ONLY_USE_LINK_DEINGRESO_
			pmenu->current_page--;
			pmenu->option = pmenu->page[pmenu->current_page].link_deingreso;
		#else
			//save actual
			pmenu->page[pmenu->current_page].link_deingreso = pmenu->option;
			pmenu->option = pmenu->page[pmenu->current_page].link_anterior;
			pmenu->current_page--;
		#endif
		_show_options_by_numpage(pmenu);
	}

	void link_handler(void)
	{
		shell.coderet = (CODERETURN_TOSHELL)NO_CHANGES;
	}
	//void menu_main_more0(void){	shell.coderet = (CODERETURN_TOSHELL)NO_CHANGES;	}
	
	void menu_main_config0(void)
	{

//siempre se baja de 1 en uno
//push_menu(menu_config.id_address.levelstack, 4);
push_menu(menu_operational.pmenu, 4);
                                                                                                                                                                                                         		
		//
		menu_operational.pmenu = &menu_config;
		menu_operational.pmenu->option = menu_operational.pmenu->page[0].link_deingreso;
		cleardisp_scope_of_menu();
		_show_options_by_numpage(menu_operational.pmenu);
	
		shell.coderet = (CODERETURN_TOSHELL)NO_CHANGES;
	}
	
	//void menu_main_back0(void){shell.coderet = (CODERETURN_TOSHELL)NO_CHANGES;}//replaced by general function "back_page"
	
	//
	void config_scene(void)
	{
		/*
		TODO THIS OPTION
		I return NO_CHANGES only for testing, in reality i will should return maybe RESTORE_TO_SHELL or INTERNAL
		*/
		shell.coderet = (CODERETURN_TOSHELL)NO_CHANGES;//retorna al shell 
	}
	void config_zone(void)
	{
		/*
		TODO THIS OPTION
		*/
		shell.coderet = (CODERETURN_TOSHELL)NO_CHANGES;
	}
	void config_system(void)
	{
		/*
		TODO THIS OPTION
		*/
		shell.coderet = (CODERETURN_TOSHELL)NO_CHANGES;
	}

	void menu_config_back0(void)
	{
		pop_menu();
		cleardisp_scope_of_menu();
		_show_options_by_numpage(menu_operational.pmenu);
		
		shell.coderet = (CODERETURN_TOSHELL)NO_CHANGES;
	}
	
	
	

