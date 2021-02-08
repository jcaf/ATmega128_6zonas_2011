/*
 * KeyboardAPI_1.h
 *
 * Created: 12/11/2012 01:26:51 p.m.
 *  Author: JCaf
 */ 


#ifndef KEYBOARDAPI_1_H_
#define KEYBOARDAPI_1_H_

	//REEMPLAZADO POR UNICO ENUM
	//typedef enum _APP_KB_LAYOUT
	//{
		//WAS_UNTOUCHED=0,
		//WAS_DIRECT_CHANGE,
		//WAS_PUSH_CHANGE
	//}APP_KB_LAYOUT;
//	BOOL KB_API_if_allreleased_clearReadyToRead(void);//hasta ahora es una funcion NO-reentrant

	_STACK_MODE synch_change_layout_kb(_STACK_MODE stack_mode, struct _key_properties * p_key_properties);

#endif /* KEYBOARDAPI_1_H_ */