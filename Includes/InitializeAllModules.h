/*************************************************************
				InitializeAllModules
				--------------------

- Incluye todos los headers.
- Incluye InitiPeripheral!

VER MACROS PREDEFINIDOS DEL COMPILADOR
http://www.avrfreaks.net/index.php?name=PNphpBB2&file=viewtopic&t=41413
. You can see all of them if 
you tell the compiler to stop right away after preprocessing, and dump 
you all the macros it knows about. This is done using the options "-E 
-dM" (plus your desired -mmcu option). Here's what I get for an empty 
C source file with -mmcu=atmega128 (sorted alphabetically, by default 
the output is semi-random): 
*************************************************************/
#ifndef _InitializeAllModules_H_
#define _InitializeAllModules_H_

	#if defined __GNUC__

		#include <avr/io.h>
		#include <avr/interrupt.h>
		//You MUST also #include <avr/interrupt.h> in the compilation.
		//It will compile without this, but the behaviour will not be correct.
        #include <avr/pgmspace.h>
        #include <avr/eeprom.h>
		#include <string.h>
		//#include <inttypes.h>
		#include <stdint.h>
		#include <math.h>
	
		#include <stdio.h>	//x sprintf
    
	#elif defined __ICCAVR__

        #include <ioavr.h>
        #include <intrinsics.h>
        #pragma language=extended     // enable use of extended keywords x defecto es habilitado

	#elif defined __PICC18__ || defined __PICC__

		#include <htc.h>

	#endif

    #include "Includes/DefinicionesGrl.h"
    #include "Includes/TypeDefs.h"
	#include "Includes/InitPeripheral.h"


#include "KS108v1/FONTS/arial_bold_14.h"
#include "KS108v1/FONTS/corsiva_12.h"
#include "KS108v1/FONTS/SC.h"
	
	#include "db_name_vocabulary/dbname_voc.h"
	
	//Process incluye las definiciones particulares del proceso embebido de turno.
	//#include "Process\Process.h"
	#include "ZONA/Zona.h"
	#include "ZONA/NamingZone/NamingZone.h"
	
	#include "DIMMING/Dimming.h"
	
	//#include "DIMMING/DIMMINGALLZONES/DimmingAllZones.h"
	
	#include "FADING/Fading.h"	
	//
	#include "ESCENAS/Escenas.h"
	#include "ESCENAS/NuevaEscena.h"
	#include "ESCENAS/EliminarEscena.h"
	
	#include "TIMEDATE/TimeDate.h"
	
	
	#include "GUI/GUI.h"	
	#include "SHELL/Shell.h"
	
	#include "key/key.h"
	
	//------------------------------------------->>> estos controles deben residir dentro debe una carpeta
	//#include "XOBJECTS/LIST/ListBox.h"
	#include "ObjControl/List/ListBox.h"
	#include "ObjControl/RadioButton/RadioButton.h"

	#include "ObjControl/DialogBox/DialogBox.h"	
	
	#include "CommonProcess/CommonToProcess.h"
	#include "CommonProcess/TimmerApp/TimerApp.h"
	
	#include "CommonProcess/keyboardApp/keyboard_app.h"
	#include "EFFECTS/BLINKING/Blinking.h"
	
	//Menúes
	#include "MENU/ClaseMenu/ClaseMenu.h"
	#include "MENU/MenuDimming6Zonas/MenuDimming6Zonas.h"
	#include "MENU/MenuScene/MenuScene.h"
	
	#include "MENU/MenuSelectDimmNoDimmLoad/MenuSelectDimmNoDimmLoad.h"

	#include "PLAYSOUND/PlaySound.h"
	
	#include "TIMMER_NB/Timmer_nb.h"
	
	#ifdef _USING_GLCD_BACKLIGHT_PIN_
		#include "DimmBackLightGLCD/DimmBLGLCD.h"
	#endif
	//
	#define SAVE_SREG_CLI() do{ _sreg_temp_main_= SREG; cli();}while(0)
	#define RESTORE_SREG()	do{SREG = _sreg_temp_main_;}while(0)
	
	extern volatile byte _sreg_temp_main_;

#endif
