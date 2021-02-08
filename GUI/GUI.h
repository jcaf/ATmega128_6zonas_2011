/*
 * GUI.h
 *
 * Created: 20/04/2012 10:37:38 a.m.
 *  Author: jcaf
 */ 


#ifndef GUI_H_
#define GUI_H_
	
	/***********************************************************************************
		Escenas  + Dimming manual comparten la misma "vista"	
	***********************************************************************************/
	#define _BAR_PSC_BASE_X_ (72 +1)	//Psc. x de barra 1 //ADD +1 NOV 2012
	#define _BAR_PSC_BASE_Y_ (14)	//Psc. y de barra 1
	//
	#define _BAR_PSC_BASE_W_ (10)	//Ancho de barra
	//#define _BAR_PSC_BASE_H_ (41)
	
	#define _INTERV_ENTRE_BARR_VERT_	(20)	//Intervalo de pixels entre inicio de cada barr
	//
	#define _BAR_PSC_BASE_H_			(NUM_ELEM_DENTRO_BAR+1 +2)			//41
	#define _PSC_Y_FINAL_PIXEL_RECT_	(_BAR_PSC_BASE_Y_ + _BAR_PSC_BASE_H_ )	//14+47 = 61 

	/***********************************************************************************
	***********************************************************************************/
	#define DrawOnlyMarcoGlobalGLCD() do{ks0108DrawRect(0,0,191,63,BLACK);}while(0)
	#define EraseOnlyMarcoGlobalGLCD() do{ks0108DrawRect(0,0,191,63,WHITE);}while(0)
	//
	#define DrawOnlyDivisionAt63() do{ks0108DrawRect(63,0,0, 63, BLACK);}while(0)	
	#define EraseOnlyDivisionAt63() do{ks0108DrawRect(63,0,0, 63, WHITE);}while(0)	
	
	#define DrawOnlyDivisionAt64() do{ks0108DrawRect(64,0,0, 63, BLACK);}while(0)	
	#define EraseOnlyDivisionAt64() do{ks0108DrawRect(64,0,0, 63, WHITE);}while(0)	
	
	//
	#define DrawOnlyDivisionAt127() do{ks0108DrawRect(127,0,0, 63, BLACK);}while(0)	
	#define EraseOnlyDivisionAt127() do{ks0108DrawRect(127,0,0, 63, WHITE);}while(0)	

	#define DrawOnlyDivisionAt128() do{ks0108DrawRect(128,0,0, 63, BLACK);}while(0)	
	#define EraseOnlyDivisionAt128() do{ks0108DrawRect(128,0,0, 63, WHITE);}while(0)	
	/***********************************************************************************
	***********************************************************************************/
	extern volatile byte NUM_ELEM_DENTRO_BAR;
	extern volatile byte FACTOR_ESCALA_DIMMING;
	
	extern byte vBAR_PSC_BASE_X_MD6Z[NUM_ZONAS];	//global para otros modulos e.g: blinking in ISR()

	
	void DrawMainFrameAndBarsToD6Z(void);
	
	void CaptionOfAllZones(void);
	void DrawBarsVertOfAllZones(void);

	void window_Aviso(byte x, byte y);

	void _DrawOnOffState(byte x, byte y);
	//
	void _DrawUpTriangleState(byte x, byte y);
	void _DrawDownTriangleState(byte x, byte y);
	void _draw_triangle_left(byte x, byte y);//SOLID
	void _draw_triangle_rigth(byte x, byte y);//SOLID
	//
	void _draw_triangle_left_contour(byte x, byte y);
	void _draw_triangle_rigth_contour(byte x, byte y);
	void _draw_triangle_left_solid_black(byte x, byte y);
	void _draw_triangle_rigth_solid_black(byte x, byte y);
	void _draw_triangle_left_solid_white(byte x, byte y);
	void _draw_triangle_rigth_solid_white(byte x, byte y);
	//
	
	void _write_display_threshold_ofzone(byte zone);
	void _write_display_threshold_allzone(void);

//unir todo a un objeto
#define Y_BASE (_PSC_Y_FINAL_PIXEL_RECT_ -2) //(59)


	
struct _graphbarlevel
{
	//byte Qup;
	//byte Qdown;

	void (*write_barlevel) (byte);
	void (*erase_barlevel) (byte);
	void (*check_consistencia_barlevel) (byte);

	struct _g
	{
		byte Q;
		byte Qsaved;
		struct _bf_graphbarlevel{
			unsigned check_bar:1;
			unsigned __none:7;
		}bf;
	}g[NUM_ZONAS];
};

extern volatile struct _graphbarlevel graphbarlevel;
void preview_dc_barlevel(byte zone, TYPEDC dc);
void direct_fillclear_barlevel(byte zone, TYPEDC dc, byte color);

#define directfill_barlevel(zone,dc)	do{direct_fillclear_barlevel(zone, dc, BLACK);}while(0)
#define clear_and_directfill_barlevel(zone,dc)	do{directclearall_barlevel(zone);directfill_barlevel(zone,dc);}while(0)

#define directclear_barlevel(zone,dc)	do{direct_fillclear_barlevel(zone, dc, WHITE);}while(0)
#define directclearall_barlevel(zone)	do{direct_fillclear_barlevel(zone, MAX_VAL_DUTYCYCLE, WHITE);}while(0)


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	
	
#endif /* GUI_H_ */


	
