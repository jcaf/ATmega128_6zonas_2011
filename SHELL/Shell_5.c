/*
 * Shell_1.c
 *
 * Created: 8/9/2012 3:26:49 PM
 *  Author: jcaf
 */ 
#include "Includes/InitializeAllModules.h"

	static void key1_1fmode0(void);
	static void key2_1fmode0(void);
	static void key3_1fmode0(void);
	static void key3_1fmode0_aft(void);
	static void key4_1fmode0(void);
	
	static PTRFXrVOID thisps_fxs[4][MAXNUM_MODE_BY_PS][KB_TOTALOFKEYS]={
		{
		{&key1_1fmode0, &key2_1fmode0, &key3_1fmode0, &key4_1fmode0},
		{&DUMMYFX,&DUMMYFX,&DUMMYFX,&DUMMYFX},
		{&DUMMYFX,&DUMMYFX,&DUMMYFX,&DUMMYFX},
		{&DUMMYFX,&DUMMYFX,&DUMMYFX,&DUMMYFX},
		},
		{
		{&DUMMYFX,&DUMMYFX,&key3_1fmode0_aft,&DUMMYFX},
		{&DUMMYFX,&DUMMYFX,&DUMMYFX,&DUMMYFX},
		{&DUMMYFX,&DUMMYFX,&DUMMYFX,&DUMMYFX},
		{&DUMMYFX,&DUMMYFX,&DUMMYFX,&DUMMYFX},
		},
		{
		{&DUMMYFX,&DUMMYFX,&DUMMYFX,&DUMMYFX},
		{&DUMMYFX,&DUMMYFX,&DUMMYFX,&DUMMYFX},
		{&DUMMYFX,&DUMMYFX,&DUMMYFX,&DUMMYFX},
		{&DUMMYFX,&DUMMYFX,&DUMMYFX,&DUMMYFX},
		},
		{
		{&DUMMYFX,&DUMMYFX,&DUMMYFX,&DUMMYFX},
		{&DUMMYFX,&DUMMYFX,&DUMMYFX,&DUMMYFX},
		{&DUMMYFX,&DUMMYFX,&DUMMYFX,&DUMMYFX},
		{&DUMMYFX,&DUMMYFX,&DUMMYFX,&DUMMYFX},
		}
	};
	
	static struct _thisps
	{
		byte operating_mode;
	}thisps;
		 
	struct _shell shell;
	
	void services(void);
	void service__blinkcaption(void);
	void service__fadingprocess(void);

	///////////////////////////////////////////////////////////////
	//
	///////////////////////////////////////////////////////////////
   
    
	void Shell_main(void)
	{
		thisps.operating_mode = 0;
		change_operating_mode(thisps_fxs, thisps.operating_mode);

		bfCommonProcess0.Timmer_BlinkCaption = ON;
		
		menu_main_background_panel0();
		//
		//menu_main.current_page =0;//x test
		//
		_show_options_by_numpage(menu_operational.pmenu);
		

		time_printdisp__run();
		date_printdisp__run();
		
		while (1)
		{
			time_driver__d();
			time_printdisp__d();
			
			date_driver__d();
			date_printdisp__d();
				
			//////////////////////////////////////////////////////////////////////////////////			
			
			kb_handler0();
			
			//////////////////////////////////////////////////////////////////////////////////			
			//When the function has returned this shell
			if (shell.coderet > (CODERETURN_TOSHELL)NONE_CODE)//0
			{
					ps_fading_inbk.bf.printdisplay = DISABLE;

					pop_address_fx();	

					if (shell.coderet ==  (CODERETURN_TOSHELL)INTERNAL_SELECTION)//1 seleccion interna a cualquier parte
					{
						//hacia un codigo ejecutable en concreto
						control_of_traffic();
						shell.exec_fx = (EXEC_FX)PREPARE_EXECUTING;
					}	
					else if (shell.coderet == (CODERETURN_TOSHELL)RESTORE_SHELL)//2
					{
						ks0108ClearScreen();
						
						//
						time_printdisp__run();
						date_printdisp__run();
						//
						
						//Restaura menu actual con tal solo haber guardado su numero de option
						menu_main_background_panel0();
						_show_options_by_numpage(menu_operational.pmenu);
					
						shell.exec_fx = (EXEC_FX)NONE_TO_EXECUTE;
					}
					else if (shell.coderet == (CODERETURN_TOSHELL)NO_CHANGES)//3	
					{
						//
						time_printdisp__run();
						date_printdisp__run();
						//
						
						//no efectuar ningun cambio. Normalmente next_page/back_page
						shell.exec_fx = (EXEC_FX)NONE_TO_EXECUTE;
					}
				
				shell.coderet = (CODERETURN_TOSHELL)NONE_CODE;//Default-reset state
			}			
			
			//////////////////////////////////////////////////////////////////////////////////			
			//ABSOLUTAMENTE, TODAS LAS FUNCIONES ACEPTADAS EN CUALQUIER MENU DEBE DE RETORNAR
			//CON "shell.coderet > (CODERETURN_TOSHELL)NONE_CODE", TOODOOSSSSSSS SIN EXCEPCION!
			if (shell.exec_fx > (EXEC_FX)NONE_TO_EXECUTE )//0
			{
				//
				time_printdisp__stop();
				date_printdisp__stop();
				//
				
				if (shell.exec_fx == (EXEC_FX)PREPARE_EXECUTING )//1
				{
					push_address_fx();
					shell.exec_fx++;
				}
				if (shell.exec_fx == (EXEC_FX)CONTINUOS_EXECUTING )//2 //constantemente estara llamando a la funcion,cada funcion sera responsable de organizar sus cambios de vista
				{
					menu_operational.pmenu->registro[menu_operational.pmenu->option].pfx();
					//ABSOLUTAMENTE, TODAS LAS FUNCIONES ACEPTADAS EN CUALQUIER MENU DEBE DE RETORNAR
					//CON "shell.coderet > (CODERETURN_TOSHELL)NONE_CODE", TOODOOSSSSSSS SIN EXCEPCION!
				}
			}
			
			//////////////////////////////////////////////////////////////////////////////////
			services();
		}
	}

	///////////////////////////////////////////////////////////////
	void services(void)
	{
		service__blinkcaption();
		service__fadingprocess();
	}	
	
	///////////////////////////////////////////////////////////////
	void service__blinkcaption(void)
	{
		if (bfCommonProcess0.Timmer_BlinkCaption)
		{
			if (bfCommonProcess0.SignOneTick_BlinkCaption)
			{
				bfCommonProcess0.SignOneTick_BlinkCaption = OFF;
				ObjBlink_Timming_CaptionOfBarZone();
			}
		}
	}

	//////////////////////////////////////////////////////////////////////
	//La terminacion de fading puede traer como consecuencia muchos otros eventos
	//que deben ser SERIALIZADOS, de esta manera se asegura que se "SINCRONIZA LO MAS PRONTO POSIBLE"
	//para q otros procesos ejecuten con datos actualizados 
	//////////////////////////////////////////////////////////////////////
	void service__fadingprocess(void)
	{
		byte zone;
		
		if (ps_fading_inbk.bf.sign_new_tick)
		{	
			ps_fading_inbk.bf.sign_new_tick = 0x0;
			//ii		
			//do_fadingprocess_allzone();
			for (zone=0; zone<NUM_ZONAS; zone++)
			{	
				if (objzone[zone].TypeOfLoad == Dimmable)
				{	
					if (objzone[zone].sfading.bf.fading_active == 1)
					{
						fadingprocess_inzone(zone);
						
						if (objzone[zone].sfading.bf.fading_active == OFF)//si acabo??
						{
							//++ADD patch
							graphbarlevel.check_consistencia_barlevel(zone);
							//POR AHORA LO DEJO AQUI - TAL VEZ UN FLAG Q SOLO//HABILITE CUANDO SE NECESITE...OK
							//TIENE SUS IMPLICANCIAS PASAR DE UN ZONA/ESCENA EN PLENA MOVIEMIENTO //CONSISTENCIAR
							if (ps_fading_inbk.bf.printdisplay == ENABLE)
							{
								directfill_barlevel(zone,objzone[zone].dc);
							}
							//++	
							
							//++
							if (objzone[zone].bf.changing_of_escene == 1)
							{
								objzone[zone].bf.changing_of_escene = 0x0;
							}
							//++	
						}
					}
				}
			}
			//ii
		}
	}
	
	static void key1_1fmode0(void)
	{
		_forward_option(menu_operational.pmenu);
		playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
	}
	static void key2_1fmode0(void)
	{
		_back_option(menu_operational.pmenu);
		playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
	}
	static void key3_1fmode0(void)
	{
		shell.exec_fx = (EXEC_FX)PREPARE_EXECUTING;
		//ABSOLUTAMENTE, TODAS LAS FUNCIONES ACEPTADAS EN CUALQUIER MENU DEBE DE RETORNAR
		//CON "shell.coderet > (CODERETURN_TOSHELL)NONE_CODE", TOODOOSSSSSSS SIN EXCEPCION!
		playsound(SOUND_BUZZER, _BUZZER_ACCEPT_SOUND0_);
	}
	
	static void key3_1fmode0_aft(void) 
		{key3_1fmode0();}
	
	static void key4_1fmode0(void)
	{
		//playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
	}
