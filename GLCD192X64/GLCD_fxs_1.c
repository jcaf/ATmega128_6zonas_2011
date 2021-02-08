/*
 * GLCD_fxs.c
 *
 * Created: 14/03/2012 10:08:25 a.m.
 *  Author: jcaf
 */ 
	#include "Includes/InitializeAllModules.h"

	void ScroolingZ_CHIP1(void)	//(byte Time);
	{
		byte i;
		for (i=1;i<=64;i++)	
		{
			ks0108WriteCommand(0xC0 | i, CHIP1);	//{ks0108FillRect(1,i-1,61,1,WHITE);}//ok limpiaaaaaaaa	//ks0108DrawLine(1,i-1,61,i-1,WHITE);
			_delay_ms(7);	
		}	
	}			

	void ScroolingCHIP1up_CHIP2down_CHIP3up(void)
	{
		byte i;
		for (i=1;i<=64;i++)
		{
			ks0108WriteCommand(0xC0 | i, CHIP1);
			ks0108WriteCommand(0xC0 | (64-i), CHIP2);
			ks0108WriteCommand(0xC0 | i, CHIP3);
			_delay_ms(15);
		}
	}	

	void PrintNewDigitInASCIIAt(byte xPos, byte yPos, byte wMaxDigit, byte hMaxDigit, byte Digit)
	{
		ks0108FillRect(xPos,yPos,wMaxDigit,hMaxDigit,WHITE);	//Borra posicion 
		ks0108GotoXY(xPos,yPos);ks0108PutChar(Digit + 0x30);	//Imprime
	}

	byte CenterText_HPix_CHIPn_fx(byte xiCHIPn, byte lTotalHpix, byte strlength, byte wFontTextPix, byte OffsetIfStartInZERO, byte OffsetIfNotStartInZERO) 
	{
		byte temp= ( lTotalHpix-(strlength*wFontTextPix) )/2;
		if (temp <= 0) 
			return xiCHIPn + OffsetIfStartInZERO;
		else
			return OffsetIfNotStartInZERO + (xiCHIPn + temp);
		
	}
	
	/***********************************************************************************
	byte y= 64/2 -1;
	byte r= 64/2 -1;
	byte wh=1;
	for (byte ii=1; ii<=(62/2); ii++)
	{
		ks0108DrawRect(r--, y--, wh, wh ,BLACK);
		wh+=2;
	}
	***********************************************************************************/
	void ClearFromCenter_GrowingSymmetric(byte xcenter, byte ycenter, byte NumberOfPixelToClear_div2)
	{
		byte i, wh=1;
		for (i=0; i<NumberOfPixelToClear_div2; i++)
		{
			ks0108DrawRect(xcenter--, ycenter--, wh, wh, WHITE);
			wh+=2;
		}
	}

/*
///////////////////////////////////////////////////////////
//Funcion desarrollada para ver el preview de dc de escena
///////////////////////////////////////////////////////////
//a la vertical
#define Y_SPACE_0 (1)
#define Y_SPACE_1 (2)
//en la horizontal
#define X_NOINTERCALADO (1)
#define X_ALINEADO (X_NOINTERCALADO)
#define X_INTERCALADO (0)

void nnn(byte x_init, byte Y, byte x_align_inter)
{
	byte i;
	byte x;
	byte y=10;
	byte off=0;
	while (y<  )
	{
		if (!x_align_inter){off = !off;}
		x = x_init+ (off & 0x01);
		for (i=0; i< 4-(off & 0x01);i++)
		{
			ks0108SetDot(x,y,BLACK);
			x+=2;
		}
		y=y+Y;
	}
}

nnn(10, Y_SPACE_1, X_ALINEADO);		//X=4 PUNTOS ALIN,  Y= ESPACIADOS EN 1
nnn(30, Y_SPACE_0, X_INTERCALADO);	//X=4/3 PUNTOS INTER,  Y= ESPACIADOS EN 0
*/