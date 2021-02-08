/*
 * GUI_1.c
 *
 * Created: 20/04/2012 10:37:28 a.m.
 *  Author: jcaf
 */ 
#include "Includes/InitializeAllModules.h"
	
	byte vBAR_PSC_BASE_X_MD6Z[NUM_ZONAS]={	_BAR_PSC_BASE_X_+(_INTERV_ENTRE_BARR_VERT_*0),
											_BAR_PSC_BASE_X_+(_INTERV_ENTRE_BARR_VERT_*1),
											_BAR_PSC_BASE_X_+(_INTERV_ENTRE_BARR_VERT_*2),
											_BAR_PSC_BASE_X_+(_INTERV_ENTRE_BARR_VERT_*3),
											_BAR_PSC_BASE_X_+(_INTERV_ENTRE_BARR_VERT_*4),
											_BAR_PSC_BASE_X_+(_INTERV_ENTRE_BARR_VERT_*5)
											};			
	////////////////////////////////////////////////////////////////////////////////
	//Marco Principal x DM6Z + 6 barras
	////////////////////////////////////////////////////////////////////////////////
	void DrawMainFrameAndBarsToD6Z(void)
	{
		//ks0108ClearScreen();
		DrawOnlyMarcoGlobalGLCD();
		DrawOnlyDivisionAt63();
		
		//Titulos de barras	
		CaptionOfAllZones();
		DrawBarsVertOfAllZones();
	}	
	////////////////////////////////////////////////////////////////////////////////
	//dibuja el recuadro exterior
	////////////////////////////////////////////////////////////////////////////////
	void DrawBarsVertOfAllZones(void)
	{
		ks0108DrawRect(_BAR_PSC_BASE_X_+(_INTERV_ENTRE_BARR_VERT_*0) , _BAR_PSC_BASE_Y_, _BAR_PSC_BASE_W_, _BAR_PSC_BASE_H_, BLACK);
		ks0108DrawRect(_BAR_PSC_BASE_X_+(_INTERV_ENTRE_BARR_VERT_*1) , _BAR_PSC_BASE_Y_, _BAR_PSC_BASE_W_, _BAR_PSC_BASE_H_, BLACK);
		ks0108DrawRect(_BAR_PSC_BASE_X_+(_INTERV_ENTRE_BARR_VERT_*2) , _BAR_PSC_BASE_Y_, _BAR_PSC_BASE_W_, _BAR_PSC_BASE_H_, BLACK);
		ks0108DrawRect(_BAR_PSC_BASE_X_+(_INTERV_ENTRE_BARR_VERT_*3) , _BAR_PSC_BASE_Y_, _BAR_PSC_BASE_W_, _BAR_PSC_BASE_H_, BLACK);
		ks0108DrawRect(_BAR_PSC_BASE_X_+(_INTERV_ENTRE_BARR_VERT_*4) , _BAR_PSC_BASE_Y_, _BAR_PSC_BASE_W_, _BAR_PSC_BASE_H_, BLACK);
		ks0108DrawRect(_BAR_PSC_BASE_X_+(_INTERV_ENTRE_BARR_VERT_*5) , _BAR_PSC_BASE_Y_, _BAR_PSC_BASE_W_, _BAR_PSC_BASE_H_, BLACK);
	}
	////////////////////////////////////////////////////////////////////////////////
	void CaptionOfAllZones(void)
	{
		ks0108SelectFont(SC, ks0108ReadFontData, BLACK);

		ks0108GotoXY(_BAR_PSC_BASE_X_+(_INTERV_ENTRE_BARR_VERT_*0),2);	ks0108Puts_P(PSTR("Z1"));
		ks0108GotoXY(_BAR_PSC_BASE_X_+(_INTERV_ENTRE_BARR_VERT_*1),2);	ks0108Puts_P(PSTR("Z2"));
		ks0108GotoXY(_BAR_PSC_BASE_X_+(_INTERV_ENTRE_BARR_VERT_*2),2);	ks0108Puts_P(PSTR("Z3"));
		ks0108GotoXY(_BAR_PSC_BASE_X_+(_INTERV_ENTRE_BARR_VERT_*3),2);	ks0108Puts_P(PSTR("Z4"));
		ks0108GotoXY(_BAR_PSC_BASE_X_+(_INTERV_ENTRE_BARR_VERT_*4),2);	ks0108Puts_P(PSTR("Z5"));
		ks0108GotoXY(_BAR_PSC_BASE_X_+(_INTERV_ENTRE_BARR_VERT_*5),2);	ks0108Puts_P(PSTR("Z6"));
	}
	void window_Aviso(byte x, byte y)
	{
		#define _WINDOW_AVISO_PIXEL_WIDTH_	(60)	//60 PIXEL
		#define _WINDOW_AVISO_PIXEL_HEIGHT_	(60)	//60 PIXEL
		//
		#define _WINDOW_AVISO_DRAWROUNDRECT_1_X_			(0)
		#define _WINDOW_AVISO_DRAWROUNDRECT_1_Y_			(0)
		#define _WINDOW_AVISO_DRAWROUNDRECT_1_WIDTH_		(_WINDOW_AVISO_PIXEL_WIDTH_-1)
		#define _WINDOW_AVISO_DRAWROUNDRECT_1_HEIGHT_		(_WINDOW_AVISO_PIXEL_HEIGHT_-1)
		#define _WINDOW_AVISO_DRAWROUNDRECT_1_RADIO_		(3)

		#define _WINDOW_AVISO_DRAWROUNDRECT_2_X_			(1)
		#define _WINDOW_AVISO_DRAWROUNDRECT_2_Y_			(1)
		#define _WINDOW_AVISO_DRAWROUNDRECT_2_WIDTH_		(_WINDOW_AVISO_PIXEL_WIDTH_-3)
		#define _WINDOW_AVISO_DRAWROUNDRECT_2_HEIGHT_		(_WINDOW_AVISO_PIXEL_HEIGHT_-3)
		#define _WINDOW_AVISO_DRAWROUNDRECT_2_RADIO_		(2)
		//

		ks0108DrawRoundRect(x+_WINDOW_AVISO_DRAWROUNDRECT_1_X_,
		y+_WINDOW_AVISO_DRAWROUNDRECT_1_Y_,
		_WINDOW_AVISO_DRAWROUNDRECT_1_WIDTH_,
		_WINDOW_AVISO_DRAWROUNDRECT_1_HEIGHT_,
		_WINDOW_AVISO_DRAWROUNDRECT_1_RADIO_,
		BLACK);

		ks0108DrawRoundRect(x+_WINDOW_AVISO_DRAWROUNDRECT_2_X_,
		y+_WINDOW_AVISO_DRAWROUNDRECT_2_Y_,
		_WINDOW_AVISO_DRAWROUNDRECT_2_WIDTH_,
		_WINDOW_AVISO_DRAWROUNDRECT_2_HEIGHT_,
		_WINDOW_AVISO_DRAWROUNDRECT_2_RADIO_,
		BLACK);
		//
		#define _WINDOW_AVISO_TEXT_X_AVISO_	(15)
		#define _WINDOW_AVISO_TEXT_Y_AVISO_	(1)

		ks0108SelectFont(SC,ks0108ReadFontData,BLACK);
		ks0108GotoXY(x+_WINDOW_AVISO_TEXT_X_AVISO_,y+_WINDOW_AVISO_TEXT_Y_AVISO_);ks0108Puts_P(PSTR("Aviso"));
		ks0108InvertRect(x+2,y+2,55,10);
	}
	
	/********************************************************
	Direccion de inicio superior EJM: _DrawOnOffState(32, 7);
	AnchoxAlto: 7x7
	********************************************************/
	void _DrawOnOffState(byte x, byte y)
	{
		ks0108DrawCircle   (x,    y+4,   3, BLACK);
		ks0108DrawHoriLine(x-1 , y+1 , 2, WHITE);
		ks0108DrawVertLine(x , y , 3, BLACK);
	}
	/********************************************************
	Direccion de inicio superior EJM:_DrawUpTriangleState(9,9);
	AnchoxAlto: 9x5
	********************************************************/
	void _DrawUpTriangleState(byte x, byte y)	//9,9
	{
		ks0108SetDot(x, y, BLACK);
		ks0108DrawHoriLine(x-1,y+1,2,BLACK);
		ks0108DrawHoriLine(x-2,y+2,4,BLACK);
		ks0108DrawHoriLine(x-3,y+3,6,BLACK);
		ks0108DrawHoriLine(x-4,y+4,8,BLACK);
	}
	/********************************************************
	Direccion de inicio superior EJM:_DrawDownTriangleState(16,9);
	AnchoxAlto:
	********************************************************/
	void _DrawDownTriangleState(byte x, byte y)	//16,9
	{
		ks0108DrawHoriLine(x  , y ,8,BLACK);
		ks0108DrawHoriLine(x+1,y+1,6,BLACK);
		ks0108DrawHoriLine(x+2,y+2,4,BLACK);
		ks0108DrawHoriLine(x+3,y+3,2,BLACK);
		ks0108SetDot(x+4,y+4, BLACK);
	}
	
	/////////////////////////////////////////////////////////
	//x,y = la punta del triangulo
	void _draw_triangle_left(byte x, byte y)//SOLID
	{
		ks0108SetDot(x, y, BLACK);
		ks0108DrawVertLine(x+1,y-1,2,BLACK);
		ks0108DrawVertLine(x+2,y-2,4,BLACK);
		ks0108DrawVertLine(x+3,y-3,6,BLACK);
		ks0108DrawVertLine(x+4,y-4,8,BLACK);
		//EXTRA
		ks0108DrawVertLine(x+5,y-5,10,BLACK);
	}
	/////////////////////////////////////////////////////////
	//x,y = la punta del triangulo
	void _draw_triangle_rigth(byte x, byte y)//SOLID
	{
		//EXTRA
		ks0108DrawVertLine(x-5,y-5,10,BLACK);
		//
		ks0108DrawVertLine(x-4,y-4,8,BLACK);
		ks0108DrawVertLine(x-3,y-3,6,BLACK);
		ks0108DrawVertLine(x-2,y-2,4,BLACK);
		ks0108DrawVertLine(x-1,y-1,2,BLACK);
		ks0108SetDot(x, y, BLACK);
	}
	
	/////////////////////////////////////////////////////////
	//x,y = la punta del triangulo
	void _draw_triangle_rigth_contour(byte x, byte y)
	{
		//EXTRA
		ks0108DrawVertLine(x-5,y-5,10,BLACK);
		//
		ks0108DrawLine(x-4,y-4, x-4+3, y-4+3, BLACK);
		ks0108DrawLine(x-4,y+4, x-4+3, y+4-3, BLACK);
		ks0108SetDot(x, y, BLACK);
	}
	
	void _draw_triangle_left_contour(byte x, byte y)
	{
		ks0108SetDot(x, y, BLACK);
		ks0108DrawLine(x+1,y-1, x+1+3, y-1 -3, BLACK);
		ks0108DrawLine(x+1,y+1, x+1+3, y+1 +3, BLACK);
		//EXTRA
		ks0108DrawVertLine(x+5,y-5,10,BLACK);
		//
	}
	//inner to contour function-complemnt
	void _draw_triangle_left_solid_black(byte x, byte y)
	{
		ks0108SetDot(x+1, y, BLACK);
		ks0108DrawVertLine(x+1 +1, y-1, 2, BLACK);
		ks0108DrawVertLine(x+1 +2, y-2, 4, BLACK);
		ks0108DrawVertLine(x+1 +3, y-3, 6, BLACK);//EXTRA
	}
	//inner to contour function-complemnt
	void _draw_triangle_rigth_solid_black(byte x, byte y)
	{
		ks0108SetDot(x-1, y, BLACK);
		ks0108DrawVertLine(x-1 -1, y-1, 2, BLACK);
		ks0108DrawVertLine(x-1 -2, y-2, 4, BLACK);
		ks0108DrawVertLine(x-1 -3, y-3, 6, BLACK);//EXTRA
	}
	//inner to contour function-complemnt
	void _draw_triangle_left_solid_white(byte x, byte y)
	{
		ks0108SetDot(x+1, y, WHITE);
		ks0108DrawVertLine(x+1 +1, y-1, 2, WHITE);
		ks0108DrawVertLine(x+1 +2, y-2, 4, WHITE);
		ks0108DrawVertLine(x+1 +3, y-3, 6, WHITE);//EXTRA
	}
	//inner to contour function-complemnt
	void _draw_triangle_rigth_solid_white(byte x, byte y)
	{
		ks0108SetDot(x-1, y, WHITE);
		ks0108DrawVertLine(x-1 -1, y-1, 2, WHITE);
		ks0108DrawVertLine(x-1 -2, y-2, 4, WHITE);
		ks0108DrawVertLine(x-1 -3, y-3, 6, WHITE);//EXTRA
	}
	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

//////unir todo a un objeto
	void _erase_barlevel(byte zone);
	void _write_barlevel(byte zone);
	void _check_consistencia_barlevel(byte zone);
	
	volatile struct _graphbarlevel graphbarlevel = {
		.write_barlevel = &_write_barlevel,
		.erase_barlevel = &_erase_barlevel,
		.check_consistencia_barlevel = &_check_consistencia_barlevel
		};
	
	//BUG FIXED: Solo inhibir ks0108DrawHoriLine()
	void _write_barlevel(byte zone)
	{
		//if (ps_fading_inbk.bf.printdisplay)	//add
		//{
			if (objzone[zone].dc >= FACTOR_ESCALA_DIMMING)
			{
				if ((objzone[zone].dc % FACTOR_ESCALA_DIMMING) == 0)
				{
					graphbarlevel.g[zone].Q =  (byte) (objzone[zone].dc / FACTOR_ESCALA_DIMMING);
					graphbarlevel.g[zone].Q--;
					
					if (ps_fading_inbk.bf.printdisplay)	//add
					{		
					ks0108DrawHoriLine(vBAR_PSC_BASE_X_MD6Z[zone]+2,(Y_BASE-graphbarlevel.g[zone].Q), (_BAR_PSC_BASE_W_-4), BLACK);
					}	
				}
			}
		//}
	}	
	
	//BUG FIXED: Solo inhibir ks0108DrawHoriLine()
	void _erase_barlevel(byte zone)
	{
		//if (ps_fading_inbk.bf.printdisplay)	//add
		//{
			if ((objzone[zone].dc % FACTOR_ESCALA_DIMMING) == 0)
			{
				graphbarlevel.g[zone].Q = (byte) (objzone[zone].dc / FACTOR_ESCALA_DIMMING);
				
				if (ps_fading_inbk.bf.printdisplay)	//add
				{				
				ks0108DrawHoriLine( (vBAR_PSC_BASE_X_MD6Z[zone]+2), (Y_BASE-graphbarlevel.g[zone].Q), (_BAR_PSC_BASE_W_-4), WHITE);
				}			
			}
		//}
	}
	
	//BUG FIXED: Solo inhibir ks0108DrawHoriLine()
	void _check_consistencia_barlevel(byte zone)
	{
		if (graphbarlevel.g[zone].bf.check_bar == 1)
		{
			graphbarlevel.g[zone].bf.check_bar = 0x00;
		
			if (graphbarlevel.g[zone].Qsaved != graphbarlevel.g[zone].Q)	//si no coinciden. ok-> imprimir lo que falta
			{
				//if (ps_fading_inbk.bf.printdisplay == ENABLE)
				//{
					if (graphbarlevel.g[zone].Q > graphbarlevel.g[zone].Qsaved )
					{
						if (ps_fading_inbk.bf.printdisplay == ENABLE)
						{
						ks0108DrawHoriLine((vBAR_PSC_BASE_X_MD6Z[zone]+2),(Y_BASE-(graphbarlevel.g[zone].Qsaved+1)),(_BAR_PSC_BASE_W_-4),WHITE);
						}		
					}						
				//}				
			}			
		}
	}
	
	//////////////////////////////////////////////////////////////////////////
	///Dibujar ::: puntos, usado para preview
	void preview_dc_barlevel(byte zone, TYPEDC dc)
	{
		//byte i;
		byte ii;
		byte x,y;
		//byte off=1;
		byte color,COLOR = BLACK;
			
		byte q = (dc / FACTOR_ESCALA_DIMMING);	//lo reduce al menor entero
			
		if (q>0)
		{
			y = Y_BASE - (q-1);
				
			graphbarlevel.g[zone].Q = (q-1);	//++ADD
				
			for (ii=0; ii<q; ii++)
			{
				COLOR = ~COLOR;//inicia desde arriba con la mayor parte de puntos
				//off = !off;
				//x = (vBAR_PSC_BASE_X_MD6Z[zone]+2) + (off);
				x = (vBAR_PSC_BASE_X_MD6Z[zone]+2);
				color = COLOR;
				//for (i=0; i<(4-off); i++)

				//optimizacion-START---------------------
				//optimizando
				//desenvuelvo este for
				/*for (i=0; i<(7); i++)
				{
					color =~color;
					ks0108SetDot(x++,y,color);
					//x+=2;
				}*/
				color =~color;
				ks0108SetDot(x++,y,color);
				color =~color;
				ks0108SetDot(x++,y,color);
				color =~color;
				ks0108SetDot(x++,y,color);
				color =~color;
				ks0108SetDot(x++,y,color);
				color =~color;
				ks0108SetDot(x++,y,color);
				color =~color;
				ks0108SetDot(x++,y,color);
				color =~color;
				ks0108SetDot(x++,y,color);

				//optimizacion-FINISH---------------------
				y++;
			}
		}
	}

	/*
	Otras funciones hacen uso de esta funcion para borrar o escribir pixeles sin importar si se escribe dentro de los bordes
	de las barras
	*/
	void direct_fillclear_barlevel(byte zone, TYPEDC dc, byte color)
	{
		byte q;

		q= (dc / FACTOR_ESCALA_DIMMING);	//lo reduce al menor entero
		
		if (q>0)
		{
			////add as bug fixed - NO SE PUEDE APLICAR DE FORMA GENERAL LA RESTRICCION de if (.printdisplay){}
			//if (ps_fading_inbk.bf.printdisplay == ENABLE)
			//{
			ks0108FillRect(vBAR_PSC_BASE_X_MD6Z[zone]+2, Y_BASE-(q-1), _BAR_PSC_BASE_W_-4, q-1,  color);
			//}
			//
		}
			//else { if (color == WHITE) borratodo();}//seria un caso especial para decir q si es 0, borre todo
		graphbarlevel.g[zone].Q = (q-1);//++ADD

	}
	
	
	///////////////////////////////////////////////////////////////
	// escribe si es mayor q factor de escala
	///////////////////////////////////////////////////////////////
	
	void _write_display_threshold_ofzone(byte zone)
	{
		word Q;
		
		Q = objzone[zone].thrshld;
		
		if (Q >= FACTOR_ESCALA_DIMMING)
		{
			Q =  (byte) (Q / FACTOR_ESCALA_DIMMING);
			Q--;
			
			//if (ps_fading_inbk.bf.printdisplay == ENABLE) .. aun no necessary
			//{
			ks0108SetDot(vBAR_PSC_BASE_X_MD6Z[zone]-1,(Y_BASE-Q), BLACK);
			//}
		}
	}

	void _write_display_threshold_allzone(void)
	{
		byte zone;
		for (zone=0; zone<NUM_ZONAS; zone++)
		{
			_write_display_threshold_ofzone(zone);
		}
	}
	
	