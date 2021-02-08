/*
 * DialogBox.h
 *
 * Created: 8/22/2012 6:21:09 PM
 *  Author: jcaf
 */ 


#ifndef DIALOGBOX_H_
#define DIALOGBOX_H_
	
	typedef enum _DIALOGBOX_OPTIONS
	{
		_DIALOGBOX_OPTION_SI_=0,
		_DIALOGBOX_OPTION_NO_=1,
		//_DIALOGBOX_OPTION_CANCEL_=2,
	}DIALOGBOX_OPTIONS;
	
	#define __dialogbox_cr_wasread() do{dialogbox_nb.cr = -1;}while(0)
	void _dialogbox_sino_UP(void);
	void _dialogbox_sino_DN(void);
	void _dialogbox_sino_SEL(void);
	void _dialogbox_sino_ESC(void);
	
	#define _THISDIALOGBOX_NUMOPTIONS_ (2)
	
	typedef enum _DIALOGBOX_CR
	{
		NONE	=-1,
		NO		=0,
		YES		=1,
		CANCEL	=2,
		SCAPE =3
	}DIALOGBOX_CR;
	
	typedef struct _DIALOGBOX
	{
		byte markopt_offset_x[_THISDIALOGBOX_NUMOPTIONS_];
		signed char option;
		DIALOGBOX_CR cr; //code-return
		byte x;
		byte y;
		
		//ADD
		PTRFXrVOID dialogbox_sino_UP;
		PTRFXrVOID dialogbox_sino_DN;
		PTRFXrVOID dialogbox_sino_SEL;
		PTRFXrVOID dialogbox_sino_ESC;
		//
		
	}DIALOGBOX;

	extern volatile DIALOGBOX dialogbox_nb;
	
	void dialogbox_sino(byte x, byte y, signed char default_option);
	void dialogbox_sino_keyboardhandler(void);	//prev. inicializado por dialogbox_sino
	
	//Blocking fxs
	signed char _dialogbox_sino_B__aceptarcambios(byte x, byte y, signed char default_option);
	signed char _dialogbox_sino_B__salir(byte x, byte y, signed char default_option);
	signed char _dialogbox_sino_B__generic(byte x, byte y, signed char default_option);
  
#endif /* DIALOGBOX_H_ */


