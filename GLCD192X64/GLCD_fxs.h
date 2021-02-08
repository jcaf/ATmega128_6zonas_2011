/* Parte de las funciones adicionales de la GLCD
 *
 * GLCD_fxs.h
 *
 * Created: 14/03/2012 10:08:25 a.m.
 *  Author: jcaf
 */ 
#ifndef _GLCD_FXS_H_
#define _GLCD_FXS_H_
		
	
	#define ClearAllPixel_CHIP1() do{ks0108FillRect(xiCHIP1,yiCHIP1,xfCHIP1,yfCHIP1,WHITE);}while(0)
	#define ClearAllPixel_CHIP2() do{ks0108FillRect(xiCHIP2,yiCHIP2,xfCHIP2,yfCHIP2,WHITE);}while(0)
	#define ClearAllPixel_CHIP3() do{ks0108FillRect(xiCHIP3,yiCHIP3,xfCHIP3,yfCHIP3,WHITE);}while(0)

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	#define direct_clearallpixel_less1border_CHIP1() do{ks0108FillRect(xiCHIP1+1,yiCHIP1+1,(xfCHIP1-1)-(xiCHIP1+1),(yfCHIP1-1)-(yiCHIP1+1),WHITE);}while(0)
	#define direct_clearallpixel_less1border_CHIP2() do{ks0108FillRect(xiCHIP2+1,yiCHIP2+1,(xfCHIP2-1)-(xiCHIP2+1),(yfCHIP2-1)-(yiCHIP2+1),WHITE);}while(0)
	#define direct_clearallpixel_less1border_CHIP3() do{ks0108FillRect(xiCHIP3+1,yiCHIP3+1,(xfCHIP3-1)-(xiCHIP3+1),(yfCHIP3-1)-(yiCHIP3+1),WHITE);}while(0)

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	#define softcentric_clearallpixel_less1border_CHIP1() do{ClearFromCenter_GrowingSymmetric(0		+(64/2)-1,  (64/2)-1, 62/2);}while(0)
	#define softcentric_clearallpixel_less1border_CHIP2() do{ClearFromCenter_GrowingSymmetric(64	+(64/2)-1,	(64/2)-1, 62/2);}while(0)
	#define softcentric_clearallpixel_less1border_CHIP3() do{ClearFromCenter_GrowingSymmetric(128	 +(64/2)-1, (64/2)-1, 62/2);}while(0)

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void ScroolingCHIP1up_CHIP2down_CHIP3up(void);
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	#define LongitudText_Hpix(text,wFontTextPix) ( (sizeof(text)-1) * wFontTextPix)
	
	//#define CenterText_HPix(lTotalHpix,text,wFontTextPix) ((LongitudText_Hpix(text,wFontTextPix)>lTotalHpix) ? (0) : ((lTotalHpix-((sizeof(text)-1)*wFontTextPix))/2))

	/***************************************************************************************
	//((LongitudText_Hpix(text,wFontTextPix)>=lTotalHpix) ? (xiCHIPn+OffsetIfStartInZERO) : OffsetIfNotStartInZERO + (xiCHIPn+((lTotalHpix-((sizeof(text)-1)*wFontTextPix))/2)))
	***************************************************************************************/
	#define CenterText_HPix_CHIPn(xiCHIPn, lTotalHpix,text,wFontTextPix, OffsetIfStartInZERO, OffsetIfNotStartInZERO)	\
	(  (((int)(  lTotalHpix-((sizeof(text)-1)*wFontTextPix))/2) <= 0) ? (xiCHIPn+OffsetIfStartInZERO) : OffsetIfNotStartInZERO + (xiCHIPn+((lTotalHpix-((sizeof(text)-1)*wFontTextPix))/2) ))

	#define CenterText_HPix_CHIP1(lTotalHpix,text,wFontTextPix, OffsetIfStartInZERO, OffsetIfNotStartInZERO) \
			CenterText_HPix_CHIPn(xiCHIP1, lTotalHpix,text,wFontTextPix, OffsetIfStartInZERO, OffsetIfNotStartInZERO)
	
	#define CenterText_HPix_CHIP2(lTotalHpix,text,wFontTextPix, OffsetIfStartInZERO, OffsetIfNotStartInZERO) \
			CenterText_HPix_CHIPn(xiCHIP2, lTotalHpix,text,wFontTextPix, OffsetIfStartInZERO, OffsetIfNotStartInZERO)

	#define CenterText_HPix_CHIP3(lTotalHpix,text,wFontTextPix, OffsetIfStartInZERO, OffsetIfNotStartInZERO) \
			CenterText_HPix_CHIPn(xiCHIP3, lTotalHpix,text,wFontTextPix, OffsetIfStartInZERO, OffsetIfNotStartInZERO)
	
	/***************************************************************************************
	
	***************************************************************************************/
	
	#define ks0108_PrintTextP_CenterH_CHIP1(y,text,wFontTextPix,OffsetIfStartInZERO, OffsetIfNotStartInZERO) do{\
			ks0108GotoXY( CenterText_HPix_CHIP1(GLCD192X64_SIZEX_CHIP1,text,wFontTextPix, OffsetIfStartInZERO, OffsetIfNotStartInZERO), y);\
			ks0108Puts_P(PSTR(text));\
	}while(0)
        
	#define ks0108_PrintTextP_CenterH_CHIP2(y,text,wFontTextPix,OffsetIfStartInZERO, OffsetIfNotStartInZERO) do{\
			ks0108GotoXY( CenterText_HPix_CHIP2(GLCD192X64_SIZEX_CHIP2,text,wFontTextPix, OffsetIfStartInZERO, OffsetIfNotStartInZERO), y);\
			ks0108Puts_P(PSTR(text));\
	}while(0)

	#define ks0108_PrintTextP_CenterH_CHIP3(y,text,wFontTextPix,OffsetIfStartInZERO, OffsetIfNotStartInZERO) do{\
			ks0108GotoXY( CenterText_HPix_CHIP3(GLCD192X64_SIZEX_CHIP3,text,wFontTextPix, OffsetIfStartInZERO, OffsetIfNotStartInZERO), y);\
			ks0108Puts_P(PSTR(text));\
	}while(0)
	
	/***************************************************************************************
	***************************************************************************************/
	void PrintNewDigitInASCIIAt(byte xPos, byte yPos, byte wMaxDigit, byte hMaxDigit, byte Digit);
	
	/***************************************************************************************
	Realizar desplazamiento(vertical) en Z
	***************************************************************************************/
	void ScroolingZ_CHIP1(void);	//(byte Time);

	/***************************************************************************************
	***************************************************************************************/
	byte CenterText_HPix_CHIPn_fx(byte xiCHIPn, byte lTotalHpix, byte strlength, byte wFontTextPix, byte OffsetIfStartInZERO, byte OffsetIfNotStartInZERO);

	void ClearFromCenter_GrowingSymmetric(byte xcenter, byte ycenter, byte NumberOfPixelToClear_div2);

#endif




