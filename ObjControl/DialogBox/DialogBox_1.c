/*
 * DialogBox_1.c
 *
 * Created: 8/22/2012 6:21:01 PM
 *  Author: jcaf
 */ 
#include "Includes/InitializeAllModules.h"

    #define _THISDIALOGBOX_NUMOPTIONS_ (2)


	//++Begin x [Si] [No]
	#define _DIALOGBOX_SINO_OFFSET_CORCHETE_		(21)
	#define _DIALOGBOX_SINO_POSC_Y_WRITE_YES_OR_NO_	(44)

	#define _DIALOGBOX_SINO_WRITE_CORCH1_YES_	(4)
	#define _DIALOGBOX_SINO_WRITE_YES_			(_DIALOGBOX_SINO_WRITE_CORCH1_YES_+7)
	#define _DIALOGBOX_SINO_WRITE_CORCH2_YES_	(_DIALOGBOX_SINO_WRITE_CORCH1_YES_+_DIALOGBOX_SINO_OFFSET_CORCHETE_)
	//
	#define _DIALOGBOX_SINO_WRITE_CORCH1_NO_	(33)
	#define _DIALOGBOX_SINO_WRITE_NO_			(_DIALOGBOX_SINO_WRITE_CORCH1_NO_+5)
	#define _DIALOGBOX_SINO_WRITE_CORCH2_NO_	(_DIALOGBOX_SINO_WRITE_CORCH1_NO_+_DIALOGBOX_SINO_OFFSET_CORCHETE_)
	//--End x [Si] [No]
	
	volatile DIALOGBOX dialogbox_nb = {
		.markopt_offset_x[0] = _DIALOGBOX_SINO_WRITE_YES_-3,
		.markopt_offset_x[1] = _DIALOGBOX_SINO_WRITE_NO_-1,
		
		.dialogbox_sino_UP = &_dialogbox_sino_UP,
		.dialogbox_sino_DN = &_dialogbox_sino_DN,
		.dialogbox_sino_SEL = &_dialogbox_sino_SEL,
		.dialogbox_sino_ESC = &_dialogbox_sino_ESC,
	};
	
	void dialogbox_sino(byte x, byte y, signed char default_option)	//initializers + frame + [Si][No] + mark default option
	{
		window_Aviso(x,y);
		//++Begin x [Si] [No]
		//defines
		//--End x [Si] [No]
		
		ks0108GotoXY(x+_DIALOGBOX_SINO_WRITE_CORCH1_YES_,y+_DIALOGBOX_SINO_POSC_Y_WRITE_YES_OR_NO_-1);ks0108Puts_P(PSTR("["));
		ks0108GotoXY(x+_DIALOGBOX_SINO_WRITE_YES_,y+_DIALOGBOX_SINO_POSC_Y_WRITE_YES_OR_NO_);ks0108Puts_P(PSTR("Si"));
		ks0108GotoXY(x+_DIALOGBOX_SINO_WRITE_CORCH2_YES_,y+_DIALOGBOX_SINO_POSC_Y_WRITE_YES_OR_NO_-1);ks0108Puts_P(PSTR("]"));

		ks0108GotoXY(x+_DIALOGBOX_SINO_WRITE_CORCH1_NO_,y+_DIALOGBOX_SINO_POSC_Y_WRITE_YES_OR_NO_-1);ks0108Puts_P(PSTR("["));
		ks0108GotoXY(x+_DIALOGBOX_SINO_WRITE_NO_,y+_DIALOGBOX_SINO_POSC_Y_WRITE_YES_OR_NO_);ks0108Puts_P(PSTR("No"));
		ks0108GotoXY(x+_DIALOGBOX_SINO_WRITE_CORCH2_NO_,y+_DIALOGBOX_SINO_POSC_Y_WRITE_YES_OR_NO_-1);ks0108Puts_P(PSTR("]"));

		//Add-initializers
        dialogbox_nb.x = x;
        dialogbox_nb.y = y;

		dialogbox_nb.option = default_option;
		ks0108InvertRect(x + dialogbox_nb.markopt_offset_x[dialogbox_nb.option], y+_DIALOGBOX_SINO_POSC_Y_WRITE_YES_OR_NO_, 15, 10);

        dialogbox_nb.cr = -1;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
    //values of return in this function
    //#define _VAL_RETURN_SI_			(1)
    //#define _VAL_RETURN_NO_			(0)
    //#define _VAL_RETURN_CANCEL_		(_VAL_RETURN_NO_)
	//////////////////////////////////////////////////////////////////////////////////////////////
	void _dialogbox_sino_UP(void)
	{
		ks0108InvertRect(dialogbox_nb.x + dialogbox_nb.markopt_offset_x[dialogbox_nb.option], dialogbox_nb.y+_DIALOGBOX_SINO_POSC_Y_WRITE_YES_OR_NO_, 15, 10);//clear current

		if (++dialogbox_nb.option >= _THISDIALOGBOX_NUMOPTIONS_) {dialogbox_nb.option = 0;}

		ks0108InvertRect(dialogbox_nb.x + dialogbox_nb.markopt_offset_x[dialogbox_nb.option], dialogbox_nb.y+_DIALOGBOX_SINO_POSC_Y_WRITE_YES_OR_NO_, 15, 10);

	}
	void _dialogbox_sino_DN(void)
	{
	    ks0108InvertRect(dialogbox_nb.x + dialogbox_nb.markopt_offset_x[dialogbox_nb.option], dialogbox_nb.y+_DIALOGBOX_SINO_POSC_Y_WRITE_YES_OR_NO_, 15, 10);//clear current

	    if (--dialogbox_nb.option <0 ) {dialogbox_nb.option = (_THISDIALOGBOX_NUMOPTIONS_-1);}

	    ks0108InvertRect(dialogbox_nb.x + dialogbox_nb.markopt_offset_x[dialogbox_nb.option], dialogbox_nb.y+_DIALOGBOX_SINO_POSC_Y_WRITE_YES_OR_NO_, 15, 10);
	}
	void _dialogbox_sino_SEL(void)
	{
		if	(dialogbox_nb.option == 0)//yes
        {
            dialogbox_nb.cr = (DIALOGBOX_CR)YES;
            playsound(SOUND_BUZZER, _BUZZER_ACCEPT_SOUND0_);
        }
        else if (dialogbox_nb.option == 1)//no
        {
            dialogbox_nb.cr = (DIALOGBOX_CR)NO;
            playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
        }
        //else if (dialogbox_nb.option == _DIAGBOX_CANCEL_) 
			//{dialogbox_nb.cr = (DIALOGBOX_CR)CANCEL ;}
	}	
	void _dialogbox_sino_ESC(void)
	{
		dialogbox_nb.cr = (DIALOGBOX_CR)SCAPE;
	}		
	
	//-------------------------------------------------------------------------------
	void dialogbox_sino_keyboardhandler(void)
	{
        if (KB_KEY1_ReadyToRead())
        {
			dialogbox_nb.dialogbox_sino_UP();
            playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
            KB_KEY1_HasBeenRead();
        }
        if (KB_KEY2_ReadyToRead())
        {
			dialogbox_nb.dialogbox_sino_DN();
            playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
            KB_KEY2_HasBeenRead();
        }

        if (KB_KEY3_ReadyToRead())
        {
			dialogbox_nb.dialogbox_sino_SEL();
			//
			if	(dialogbox_nb.option == 0)//yes
				{playsound(SOUND_BUZZER, _BUZZER_ACCEPT_SOUND0_);}
			else if (dialogbox_nb.option == 1)//no
				{playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);}
            KB_KEY3_HasBeenRead();
        }

        if (KB_KEY4_ReadyToRead())
        {
            dialogbox_nb.dialogbox_sino_ESC();
            playsound(SOUND_BUZZER, _BUZZER_SIMPLE_SOUND0_);
            KB_KEY4_HasBeenRead();
        }
	}

	signed char _dialogbox_sino_B__aceptarcambios(byte x, byte y, signed char default_option)
	{
		dialogbox_sino(x,y,default_option);
		ks0108GotoXY(x+8,y+17);		ks0108Puts_P(PSTR("Aceptar"));
		ks0108GotoXY(x+8,y+17+12);	ks0108Puts_P(PSTR("cambios?"));
		do {dialogbox_sino_keyboardhandler();}while (dialogbox_nb.cr <0);
		return dialogbox_nb.cr;
	}

	signed char _dialogbox_sino_B__salir(byte x, byte y, signed char default_option)
	{
        dialogbox_sino(x,y,default_option);
		ks0108GotoXY(x+15,y+23);	ks0108Puts_P(PSTR("Salir?"));
		do {dialogbox_sino_keyboardhandler();}while (dialogbox_nb.cr <0);
		return dialogbox_nb.cr;
	}
	
	signed char _dialogbox_sino_B__generic(byte x, byte y, signed char default_option)
	{
        dialogbox_sino(x,y,default_option);
		do {dialogbox_sino_keyboardhandler();}while (dialogbox_nb.cr <0);
        return dialogbox_nb.cr;
	}

