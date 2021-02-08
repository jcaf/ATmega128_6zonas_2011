/*
* TimeDate_1.c
*
* Created: 05/03/2012 09:58:03 p.m.
*  Author: jcaf
*/
#include "Includes/InitializeAllModules.h"

	#define TIME_PRINT_K_WIDTH_FONT (8)
	#define TIME_PRINT_K_HEIGTH_FONT (ARIAL_BOLD_14_HEIGHT)//(10) -->14
	
	volatile struct _time time;
	volatile struct _time_printdisp time_printdisp;
	
	static void time_printdisp__direct(void);
	static void time_printdisp__write_update(TIME_PRINT hhmmss_apm);
	static void time_printdisp__write_update_hour(void);
	static void time_printdisp__write_update_min(void);
	//static void time_printdisp__write_update_sec(void);
	static void time_printdisp__write_update_ampm(void);

	static
	void time_printdisp__write_hour_H10(void);
	static
	void time_printdisp__write_hour_H(void);
	static
	void time_printdisp__write_min_M10(void);
	static
	void time_printdisp__write_min_M(void);
	static
	void time_printdisp__write_sec_S10(void);
	static
	void time_printdisp__write_sec_S(void);
	static
	void time_printdisp__write_ampm_AP(void);
	static
	void time_printdisp__write_ampm_M(void);


	//////////////////////////////////////////////////	
	volatile struct _date date;
	volatile struct _date_printdisp date_printdisp;	
	
	static void date_printdisp__direct(void);
	
	//static void date_printdisp__write_udpate_day(void);
	static void date_printdisp__write_update_date(void);
	static void date_printdisp__write_update_month(void);
	static void date_printdisp__write_update_year(void);
	
	static
	void date_printdisp__write_string_day(void);
	
	static
	void date_printdisp__write_date_D10(void);
	
	static
	void date_printdisp__write_date_D(void);
	
	static
	void date_printdisp__write_string_month(void);
	
	static
	void date_printdisp__write_month_M10(void);
	
	static
	void date_printdisp__write_month_M(void);
	
	static
	void date_printdisp__write_year_Y10(void);
	
	static
	void date_printdisp__write_year_Y(void);
	
	PROGMEM
	const char days_ofthe_week[7][4]={
		"Dom",
		"Lun",
		"Mar",
		"Mie",
		"Jue",
		"Vie",
		"Sab",
	};
	
	PROGMEM
	const char months_ofthe_year[12][4]={
		"Ene",
		"Feb",
		"Mar",
		"Abr",
		"May",
		"Jun",
		"Jul",
		"Ago",
		"Set",
		"Oct",
		"Nov",
		"Dic",
	};

	void time_driver__d(void)
	{
		DS3231_ReadTKRegs2Array(DS3231_SECONDS_REG, I2Ccfx_UserBuff, 3);//ya no 7
	
		time.sec.bcd.S10= I2Ccfx_UserBuff[0]>>4;
		time.sec.bcd.S	= I2Ccfx_UserBuff[0] & 0x0F;
		time.sec.num.SS = time.sec.bcd.S10*10 + time.sec.bcd.S;
		
		time.min.bcd.M10= I2Ccfx_UserBuff[1]>>4;
		time.min.bcd.M	= I2Ccfx_UserBuff[1] & 0x0F;
		time.min.num.MM = time.min.bcd.M10*10 + time.min.bcd.M;

		time.hour.bcd.H10= (I2Ccfx_UserBuff[2]>>4) & 0x01; //clear 12/24 AM/PM
		time.hour.bcd.H	 = I2Ccfx_UserBuff[2] & 0x0F;
		time.hour.num.HH = time.hour.bcd.H10*10 + time.hour.bcd.H;

		time.bf.AMPM		= (I2Ccfx_UserBuff[2] & (1<<_DS3231_AMPM_) ) >>_DS3231_AMPM_;
	}
	
	void time_printdisp__set_xy(void)
	{
		//HH
		time_printdisp.hour.bcd.posc.H10_x = 2;
		time_printdisp.hour.bcd.posc.H_x = 2 + TIME_PRINT_K_WIDTH_FONT;
		time_printdisp.hour.bcd.posc.y = 30; 

		//:
		time_printdisp.colonHHMM.character.posc.x = 2 + (TIME_PRINT_K_WIDTH_FONT*2);
		time_printdisp.colonHHMM.character.posc.y = 30;

		//MM
		time_printdisp.min.bcd.posc.M10_x = 2 + ((TIME_PRINT_K_WIDTH_FONT*2)+3);	//3 = PARENTHESIS_WIDTH
		time_printdisp.min.bcd.posc.M_x = 2 + ((TIME_PRINT_K_WIDTH_FONT*2)+3) + (TIME_PRINT_K_WIDTH_FONT*1);
		time_printdisp.min.bcd.posc.y = 30;

		if (time_printdisp.bf.print_second)
		{
			//:
			time_printdisp.colonMMSS.character.posc.x = 2 + ((TIME_PRINT_K_WIDTH_FONT*2)+3) + (TIME_PRINT_K_WIDTH_FONT*2) ;
			time_printdisp.colonMMSS.character.posc.y = 30;
			
			//SS
			time_printdisp.sec.bcd.posc.S10_x = 2 + ((TIME_PRINT_K_WIDTH_FONT*2)+3) + (TIME_PRINT_K_WIDTH_FONT*2 +3);
			time_printdisp.sec.bcd.posc.S_x = 2 + ((TIME_PRINT_K_WIDTH_FONT*2)+3) + (TIME_PRINT_K_WIDTH_FONT*2 +3) + TIME_PRINT_K_WIDTH_FONT;
			time_printdisp.sec.bcd.posc.y = 30;
			
			//ap-m
			time_printdisp.ampm.character.posc.AP_x = 2 + ((TIME_PRINT_K_WIDTH_FONT*2)+3) + (TIME_PRINT_K_WIDTH_FONT*2 +3) + TIME_PRINT_K_WIDTH_FONT*2;
			time_printdisp.ampm.character.posc.M_x = 2 + ((TIME_PRINT_K_WIDTH_FONT*2)+3) + (TIME_PRINT_K_WIDTH_FONT*2 +3) + TIME_PRINT_K_WIDTH_FONT*3;
			time_printdisp.ampm.character.posc.y = 30;
		}
		else
		{
			//ap-m
			time_printdisp.ampm.character.posc.AP_x = 2 + ((TIME_PRINT_K_WIDTH_FONT*2)+3) + (TIME_PRINT_K_WIDTH_FONT*2)+2;
			time_printdisp.ampm.character.posc.M_x = 2 + ((TIME_PRINT_K_WIDTH_FONT*2)+3) + (TIME_PRINT_K_WIDTH_FONT*3)+2;
			time_printdisp.ampm.character.posc.y = 30;
		}		
	}
	
	void time_printdisp__d(void)
	{
		time_printdisp__write_update(0); //check if date.sm ==1 restart print?
			
		//if (time_printdisp.sec.num.SS != time.sec.num.SS)
		//{
			//time_printdisp.sec.num.SS = time.sec.num.SS;
			//time_printdisp__write_update((TIME_PRINT)SEC);
		//}
		
		//
	
		if (time_printdisp.min.num.MM != time.min.num.MM)
		{
			time_printdisp.min.num.MM = time.min.num.MM;
			time_printdisp__write_update((TIME_PRINT)MIN);
		}
		if (time_printdisp.hour.num.HH != time.hour.num.HH)
		{
			time_printdisp.hour.num.HH = time.hour.num.HH;
			time_printdisp__write_update((TIME_PRINT)HOUR);
		}
		if (time.bf.AMPM_old != time.bf.AMPM)
		{
			time.bf.AMPM_old = time.bf.AMPM;
			time_printdisp__write_update((TIME_PRINT)APM);
		}			
		
	}
	//////////////////////////////////////////////////////////////////////////
	static void time_printdisp__write_update(TIME_PRINT hhmmss_apm)
	{
	//
	ks0108SelectFont(Arial_Bold_14,ks0108ReadFontData,BLACK);
		
		if (time_printdisp.sm == 1)
		{
			//presetting register of "time_printdisp"
			time_printdisp.sec.num.SS = time.sec.num.SS;
			time_printdisp.min.num.MM = time.min.num.MM;
			time_printdisp.hour.num.HH = time.hour.num.HH;
			time.bf.AMPM_old = time.bf.AMPM;
			//
			time.hour.bcd.H10_old = time.hour.bcd.H10;
			time.hour.bcd.H_old = time.hour.bcd.H;
			
			time.min.bcd.M10_old = time.min.bcd.M10;
			time.min.bcd.M_old = time.min.bcd.M;
			
			time.sec.bcd.S10_old = time.sec.bcd.S10;
			time.sec.bcd.S_old = time.sec.bcd.S;
			//

			time_printdisp__direct();
				
			time_printdisp.sm++;
			return;
		}
			
		if (time_printdisp.sm == 2)
		{
			//if (hhmmss_apm == (TIME_PRINT)SEC )
			//{
				//time_printdisp__write_update_sec();
			//}
			//else 
			if (hhmmss_apm == (TIME_PRINT)MIN )
			{
				time_printdisp__write_update_min();
			}
			else if (hhmmss_apm == (TIME_PRINT)HOUR )
			{
				time_printdisp__write_update_hour();
			}
			else if (hhmmss_apm == (TIME_PRINT)APM)
			{
				time_printdisp__write_update_ampm();
			}
	
		}
	//
	ks0108SelectFont(SC,ks0108ReadFontData,BLACK);
	}
	
	static void time_printdisp__write_update_hour(void)
	{
		if (time.hour.bcd.H10_old != time.hour.bcd.H10)
		{
			time.hour.bcd.H10_old = time.hour.bcd.H10;
			time_printdisp__write_hour_H10();
		}
		if (time.hour.bcd.H_old != time.hour.bcd.H)
		{
			time.hour.bcd.H_old = time.hour.bcd.H;
			time_printdisp__write_hour_H();
		}
	}
	static void time_printdisp__write_update_min(void)
	{
		if (time.min.bcd.M10_old != time.min.bcd.M10)
		{
			time.min.bcd.M10_old = time.min.bcd.M10;
			time_printdisp__write_min_M10();
		}
		if (time.min.bcd.M_old != time.min.bcd.M)
		{
			time.min.bcd.M_old = time.min.bcd.M;
			time_printdisp__write_min_M();
		}
	}
	/*momentaneamente deshabilito esta funcio
	static void time_printdisp__write_update_sec(void)
	{
		if (time.sec.bcd.S10_old != time.sec.bcd.S10)
		{
			time.sec.bcd.S10_old = time.sec.bcd.S10;
			time_printdisp__write_sec_S10();
		}
		if (time.sec.bcd.S_old != time.sec.bcd.S)
		{
			time.sec.bcd.S_old = time.sec.bcd.S;
			time_printdisp__write_sec_S();
		}
	}*/
	static void time_printdisp__write_update_ampm(void)
	{
		time_printdisp__write_ampm_AP();
	}
	
	/////////////////////////////////////////////////////////////
	static void time_printdisp__direct(void)
	{
		time_printdisp__write_hour_H10();
		time_printdisp__write_hour_H();
		
		ks0108GotoXY(time_printdisp.colonHHMM.character.posc.x, time_printdisp.colonHHMM.character.posc.y); ks0108PutChar(':');
		
		time_printdisp__write_min_M10();
		time_printdisp__write_min_M();
		
		if (time_printdisp.bf.print_second)
		{
			ks0108GotoXY(time_printdisp.colonMMSS.character.posc.x, time_printdisp.colonMMSS.character.posc.y); ks0108PutChar(':');
			
			time_printdisp__write_sec_S10();	
			time_printdisp__write_sec_S();	
		}

		time_printdisp__write_ampm_AP();
		time_printdisp__write_ampm_M();
	}
	
	static
	void time_printdisp__write_hour_H10(void)
	{
		ks0108FillRect(time_printdisp.hour.bcd.posc.H10_x, time_printdisp.hour.bcd.posc.y, TIME_PRINT_K_WIDTH_FONT-1, TIME_PRINT_K_HEIGTH_FONT, WHITE);
		if (time.hour.bcd.H10 > 0)
		{
			ks0108GotoXY(time_printdisp.hour.bcd.posc.H10_x, time_printdisp.hour.bcd.posc.y);
			ks0108PutChar(time.hour.bcd.H10 + 0x30);	
		}
	}
	static
	void time_printdisp__write_hour_H(void)
	{
		ks0108FillRect(time_printdisp.hour.bcd.posc.H_x, time_printdisp.hour.bcd.posc.y, TIME_PRINT_K_WIDTH_FONT-1, TIME_PRINT_K_HEIGTH_FONT, WHITE);
		ks0108GotoXY(time_printdisp.hour.bcd.posc.H_x, time_printdisp.hour.bcd.posc.y);
		ks0108PutChar(time.hour.bcd.H + 0x30);
	}
	static
	void time_printdisp__write_min_M10(void)
	{
		ks0108FillRect(time_printdisp.min.bcd.posc.M10_x, time_printdisp.min.bcd.posc.y, TIME_PRINT_K_WIDTH_FONT-1, TIME_PRINT_K_HEIGTH_FONT, WHITE);
		ks0108GotoXY(time_printdisp.min.bcd.posc.M10_x, time_printdisp.min.bcd.posc.y);
		ks0108PutChar(time.min.bcd.M10 + 0x30);
	}
	static
	void time_printdisp__write_min_M(void)
	{
		ks0108FillRect(time_printdisp.min.bcd.posc.M_x, time_printdisp.min.bcd.posc.y, TIME_PRINT_K_WIDTH_FONT-1, TIME_PRINT_K_HEIGTH_FONT, WHITE);
		ks0108GotoXY(time_printdisp.min.bcd.posc.M_x, time_printdisp.min.bcd.posc.y);
		ks0108PutChar(time.min.bcd.M + 0x30);
	}
	static
	void time_printdisp__write_sec_S10(void)
	{
		ks0108FillRect(time_printdisp.sec.bcd.posc.S10_x, time_printdisp.sec.bcd.posc.y, TIME_PRINT_K_WIDTH_FONT-1, TIME_PRINT_K_HEIGTH_FONT, WHITE);
		ks0108GotoXY(time_printdisp.sec.bcd.posc.S10_x, time_printdisp.sec.bcd.posc.y);
		ks0108PutChar(time.sec.bcd.S10 + 0x30);
	}
	static
	void time_printdisp__write_sec_S(void)
	{
		ks0108FillRect(time_printdisp.sec.bcd.posc.S_x, time_printdisp.sec.bcd.posc.y, TIME_PRINT_K_WIDTH_FONT-1, TIME_PRINT_K_HEIGTH_FONT, WHITE);
		ks0108GotoXY(time_printdisp.sec.bcd.posc.S_x, time_printdisp.sec.bcd.posc.y);
		ks0108PutChar(time.sec.bcd.S + 0x30);
	}
	static
	void time_printdisp__write_ampm_AP(void)
	{
		ks0108FillRect(time_printdisp.ampm.character.posc.AP_x, time_printdisp.ampm.character.posc.y, TIME_PRINT_K_WIDTH_FONT-1, TIME_PRINT_K_HEIGTH_FONT, WHITE);
		ks0108GotoXY(time_printdisp.ampm.character.posc.AP_x, time_printdisp.ampm.character.posc.y);
	
		if (time.bf.AMPM == 0)
		{ks0108PutChar('a');}
			else
		{ks0108PutChar('p');}
	}
	static
	void time_printdisp__write_ampm_M(void)
	{
		ks0108FillRect(time_printdisp.ampm.character.posc.M_x, time_printdisp.ampm.character.posc.y, TIME_PRINT_K_WIDTH_FONT-1, TIME_PRINT_K_HEIGTH_FONT, WHITE);
		ks0108GotoXY(time_printdisp.ampm.character.posc.M_x, time_printdisp.ampm.character.posc.y);
		ks0108PutChar('m');
	}
	
	/////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////
	void date_driver__d(void)
	{
		DS3231_ReadTKRegs2Array(DS3231_DAY_REG, I2Ccfx_UserBuff, 4);
		
		//Day 1..7
		date.day.num.day = I2Ccfx_UserBuff[0];
		
		//Date Dd
		date.date.bcd.D10 = I2Ccfx_UserBuff[1]>>4;
		date.date.bcd.D = I2Ccfx_UserBuff[1] & 0x0F;
		date.date.num.DD = (date.date.bcd.D*10) + date.date.bcd.D; 
		
		//Month Mm //01..12
		date.month.bcd.M10 = (I2Ccfx_UserBuff[2]>>4) & 0x01;	
		date.month.bcd.M = I2Ccfx_UserBuff[2] & 0x0F;
		date.month.num.MM = date.month.bcd.M10*10 + date.month.bcd.M;
		
		//Year 00..99
		date.year.bcd.Y10 = (I2Ccfx_UserBuff[3]>>4) & 0x01;
		date.year.bcd.Y = I2Ccfx_UserBuff[3] & 0x0F;
		date.year.num.YY = (date.year.bcd.Y*10) + date.year.bcd.Y; 
		
		//Clear century;	//Get century
	}
	
	#define DATE_PRINT_K_WIDTH_FONT (SC_WIDTH)	//#define SC_WIDTH	(6)
	#define DATE_PRINT_K_HEIGTH_FONT (SC_HEIGHT)	//#define SC_HEIGHT	(13)
	
	//Determinado experimentalmente para tipografia SC
	#define DATE_PRINT_SPACE_STRING_DAY		(23) //Dom..Sab
	#define DATE_PRINT_SPACE_STRING_MONTH	(24) //Ene..Dic

	void date_printdisp__set_xy(void)
	{
		if (date_printdisp.format_date == (DATE_FORMAT)sDAY_DD_sMONTH_YY)
		{
			//Dom..Sab STRING
			date_printdisp.day.string.posc.x	= 2;
			date_printdisp.day.string.posc.y	= 47;

			//D10:D 1..31 FECHA-NUMERICO
			date_printdisp.date.bcd.posc.D10_x	= 2 + (DATE_PRINT_SPACE_STRING_DAY+2);
			date_printdisp.date.bcd.posc.D_x	= 2 + (DATE_PRINT_SPACE_STRING_DAY+2)+ (DATE_PRINT_K_WIDTH_FONT);
			date_printdisp.date.bcd.posc.y		= 47;//y common

			//M10:M Ene...Dic STRING
			date_printdisp.month.string.posc.x	= 2 + (DATE_PRINT_SPACE_STRING_DAY+2)+ (DATE_PRINT_K_WIDTH_FONT*2) +2;
			date_printdisp.month.string.posc.y	= 47;

			//Y10:Y 00..99 NUMERIC
			date_printdisp.year.bcd.posc.Y10_x	= 2 + (DATE_PRINT_SPACE_STRING_DAY+2)+ (DATE_PRINT_K_WIDTH_FONT*2 +2) + (DATE_PRINT_SPACE_STRING_MONTH)+3;
			date_printdisp.year.bcd.posc.Y_x	= 2 + (DATE_PRINT_SPACE_STRING_DAY+2)+ (DATE_PRINT_K_WIDTH_FONT*2 +2) + (DATE_PRINT_SPACE_STRING_MONTH)+3 + (DATE_PRINT_K_WIDTH_FONT);
			date_printdisp.year.bcd.posc.y		= 47;//y common
		}
		else if (date_printdisp.format_date == (DATE_FORMAT)sDAY_DD_sMONTH)
		{
			//Dom..Sab STRING
			date_printdisp.day.string.posc.x	= 2;
			date_printdisp.day.string.posc.y	= 47;

			//D10:D 1..31 FECHA-NUMERICO
			date_printdisp.date.bcd.posc.D10_x	= 2 + (DATE_PRINT_SPACE_STRING_DAY+2);
			date_printdisp.date.bcd.posc.D_x	= 2 + (DATE_PRINT_SPACE_STRING_DAY+2)+ (DATE_PRINT_K_WIDTH_FONT);
			date_printdisp.date.bcd.posc.y		= 47;//y common

			//M10:M Ene...Dic STRING
			date_printdisp.month.string.posc.x	= 2 + (DATE_PRINT_SPACE_STRING_DAY+2)+ (DATE_PRINT_K_WIDTH_FONT*2) +2;
			date_printdisp.month.string.posc.y	= 47;
		}
		else if (date_printdisp.format_date == (DATE_FORMAT)DD_MM_YY)
		{
			//D10:D 1..31 
			date_printdisp.date.bcd.posc.D10_x	= 2;
			date_printdisp.date.bcd.posc.D_x	= 2 +  (DATE_PRINT_K_WIDTH_FONT);
			date_printdisp.date.bcd.posc.y		= 47;//y common
			//Slash DD-MM
			date_printdisp.slashDDMM.character.posc.x = 2 + (DATE_PRINT_K_WIDTH_FONT*2)+1;
			date_printdisp.slashDDMM.character.posc.y = 47;
			//Month M10:M
			date_printdisp.month.bcd.posc.M10_x = 2 + (DATE_PRINT_K_WIDTH_FONT*2)+1 +4;
			date_printdisp.month.bcd.posc.M_x = 2 + (DATE_PRINT_K_WIDTH_FONT*2)+1 +4 + DATE_PRINT_K_WIDTH_FONT;
			date_printdisp.month.bcd.posc.y = 47;
			//Slash MM-YY
			date_printdisp.slashMMYY.character.posc.x = 2 + (DATE_PRINT_K_WIDTH_FONT*2)+1 +5 + DATE_PRINT_K_WIDTH_FONT*2;
			date_printdisp.slashMMYY.character.posc.y = 47;

			//Y10:Y 
			date_printdisp.year.bcd.posc.Y10_x	= 2 + (DATE_PRINT_K_WIDTH_FONT*2)+1 +5 + DATE_PRINT_K_WIDTH_FONT*2 + 5;
			date_printdisp.year.bcd.posc.Y_x	= 2 + (DATE_PRINT_K_WIDTH_FONT*2)+1 +5 + DATE_PRINT_K_WIDTH_FONT*2 + 5 + (DATE_PRINT_K_WIDTH_FONT);
			date_printdisp.year.bcd.posc.y		= 47;
		}
	}

	static void date_printdisp__direct(void)
	{
		
		if (date_printdisp.format_date == (DATE_FORMAT)sDAY_DD_sMONTH_YY)
		{
			date_printdisp__write_string_day();
			
			date_printdisp__write_date_D10();
			date_printdisp__write_date_D();
			
			date_printdisp__write_string_month();
			
			date_printdisp__write_year_Y10();
			date_printdisp__write_year_Y();
		}
		else if (date_printdisp.format_date == (DATE_FORMAT)sDAY_DD_sMONTH)
		{
			date_printdisp__write_string_day();
			
			date_printdisp__write_date_D10();
			date_printdisp__write_date_D();
			
			date_printdisp__write_string_month();
		}
		else if (date_printdisp.format_date == (DATE_FORMAT)DD_MM_YY)
		{
			date_printdisp__write_date_D10();
			date_printdisp__write_date_D();

			ks0108GotoXY(date_printdisp.slashDDMM.character.posc.x, date_printdisp.slashDDMM.character.posc.y);
			ks0108PutChar('/');
			
			date_printdisp__write_month_M10();
			date_printdisp__write_month_M();
			
			ks0108GotoXY(date_printdisp.slashMMYY.character.posc.x, date_printdisp.slashMMYY.character.posc.y);
			ks0108PutChar('/');
		
			date_printdisp__write_year_Y10();
			date_printdisp__write_year_Y();
		}		
	}
	
	//////////////////////////////////////////////////////////////////////
	void date_printdisp__d(void)
	{
		//
		ks0108SelectFont(SC,ks0108ReadFontData,BLACK);

		if (date_printdisp.sm == 1)
		{
			//presetting register of "date_printdisp"
			//Note: Numericaly i'm going to pass.
			date_printdisp.day.num.DAY	= date.day.num.day;
			
			date_printdisp.date.num.DD	= date.date.num.DD;
			date_printdisp.month.num.MM = date.month.num.MM;
			date_printdisp.year.num.YY	= date.year.num.YY;
			
			//
			if (date_printdisp.format_date == (DATE_FORMAT)sDAY_DD_sMONTH_YY)
			{
				date.date.bcd.D10_old = date.date.bcd.D10;
				date.date.bcd.D_old = date.date.bcd.D;
			
				date.year.bcd.Y10_old = date.year.bcd.Y10;
				date.year.bcd.Y_old = date.year.bcd.Y;	
			}				
			else if (date_printdisp.format_date == (DATE_FORMAT)sDAY_DD_sMONTH)
			{
				date.date.bcd.D10_old = date.date.bcd.D10;
				date.date.bcd.D_old = date.date.bcd.D;
			}			
			else if (date_printdisp.format_date == (DATE_FORMAT)DD_MM_YY)
			{
				date.date.bcd.D10_old = date.date.bcd.D10;
				date.date.bcd.D_old = date.date.bcd.D;
				
				date.month.bcd.M10_old = date.month.bcd.M10;
				date.month.bcd.M_old = date.month.bcd.M;
				
				date.year.bcd.Y10_old = date.year.bcd.Y10;
				date.year.bcd.Y_old = date.year.bcd.Y;
			}

			date_printdisp__direct();
			
			date_printdisp.sm++;
			return;
		}
		
		if (date_printdisp.sm == 2)
		{
	
			if (date_printdisp.format_date == (DATE_FORMAT)sDAY_DD_sMONTH_YY)
			{
				if (date_printdisp.day.num.DAY != date.day.num.day)
				{
					date_printdisp.day.num.DAY = date.day.num.day;
					date_printdisp__write_string_day();//directo
				}
				if (date_printdisp.date.num.DD != date.date.num.DD)
				{
					date_printdisp.date.num.DD = date.date.num.DD;
					date_printdisp__write_update_date();
				}
				if (date_printdisp.month.num.MM != date.month.num.MM)
				{
					date_printdisp.month.num.MM = date.month.num.MM;
					date_printdisp__write_string_month();
				}
				if (date_printdisp.year.num.YY != date.year.num.YY)
				{
					date_printdisp.year.num.YY = date.year.num.YY;
					date_printdisp__write_update_year();
				}
			}
			else if (date_printdisp.format_date == (DATE_FORMAT)sDAY_DD_sMONTH)
			{
				if (date_printdisp.day.num.DAY != date.day.num.day)
				{
					date_printdisp.day.num.DAY = date.day.num.day;
					date_printdisp__write_string_day();//directo
				}
				if (date_printdisp.date.num.DD != date.date.num.DD)
				{
					date_printdisp.date.num.DD = date.date.num.DD;
					date_printdisp__write_update_date();
				}
				if (date_printdisp.month.num.MM != date.month.num.MM)
				{
					date_printdisp.month.num.MM = date.month.num.MM;
					date_printdisp__write_string_month();
				}
			}
			else if (date_printdisp.format_date == (DATE_FORMAT)DD_MM_YY)
			{
				if (date_printdisp.date.num.DD != date.date.num.DD)
				{
					date_printdisp.date.num.DD = date.date.num.DD;
					date_printdisp__write_update_date();
				}
				if (date_printdisp.month.num.MM != date.month.num.MM)
				{
					date_printdisp.month.num.MM = date.month.num.MM;
					date_printdisp__write_update_month();
				}
				if (date_printdisp.year.num.YY != date.year.num.YY)
				{
					date_printdisp.year.num.YY = date.year.num.YY;
					date_printdisp__write_update_year();
				}
			}
		}
	}

	//static void date_printdisp__write_udpate_day(void)
	//{}
	
	static void date_printdisp__write_update_date(void)
	{
		if (date.date.bcd.D10_old != date.date.bcd.D10)
		{
			date.date.bcd.D10_old = date.date.bcd.D10;
			date_printdisp__write_date_D10();
		}
		if (date.date.bcd.D_old != date.date.bcd.D)
		{
			date.date.bcd.D_old = date.date.bcd.D;
			date_printdisp__write_date_D();
		}
	}
	static void date_printdisp__write_update_month(void)
	{
		if (date.month.bcd.M10_old != date.month.bcd.M10)
		{
			date.month.bcd.M10_old = date.month.bcd.M10;
			date_printdisp__write_month_M10();
		}
		if (date.month.bcd.M_old != date.month.bcd.M)
		{
			date.month.bcd.M_old = date.month.bcd.M;
			date_printdisp__write_month_M();
		}
	}
	static void date_printdisp__write_update_year(void)
	{
		//ks0108Puts_P(PSTR("20"));//depende de century bit
	
		if (date.year.bcd.Y10_old != date.year.bcd.Y10)
		{
			date.year.bcd.Y10_old = date.year.bcd.Y10;
			date_printdisp__write_year_Y10();
		}
		if (date.year.bcd.Y_old != date.year.bcd.Y)
		{
			date.year.bcd.Y_old = date.year.bcd.Y;
			date_printdisp__write_year_Y();
		}
	}

	static
	void date_printdisp__write_string_day(void)
	{
		//Dom..Sab,
		ks0108FillRect(date_printdisp.day.string.posc.x, date_printdisp.day.string.posc.y, DATE_PRINT_SPACE_STRING_DAY, DATE_PRINT_K_HEIGTH_FONT, WHITE);
		ks0108GotoXY(date_printdisp.day.string.posc.x, date_printdisp.day.string.posc.y);
		ks0108Puts_P((const char *)&days_ofthe_week[date_printdisp.day.num.DAY -1]);
		//ks0108Puts_P(PSTR(" ,"));
	}

	static 
	void date_printdisp__write_date_D10(void)
	{
		ks0108FillRect(date_printdisp.date.bcd.posc.D10_x, date_printdisp.date.bcd.posc.y, DATE_PRINT_K_WIDTH_FONT-1, DATE_PRINT_K_HEIGTH_FONT, WHITE);
		if (date.date.bcd.D10 >0)
		{
			ks0108GotoXY(date_printdisp.date.bcd.posc.D10_x, date_printdisp.date.bcd.posc.y);
			ks0108PutChar(date.date.bcd.D10 + 0x30);
		}
	}

	static 
	void date_printdisp__write_date_D(void)
	{
		ks0108FillRect(date_printdisp.date.bcd.posc.D_x, date_printdisp.date.bcd.posc.y, DATE_PRINT_K_WIDTH_FONT-1, DATE_PRINT_K_HEIGTH_FONT, WHITE);
		ks0108GotoXY(date_printdisp.date.bcd.posc.D_x, date_printdisp.date.bcd.posc.y);
		ks0108PutChar(date.date.bcd.D + 0x30);
	}
	
	static
	void date_printdisp__write_string_month(void)
	{
		ks0108FillRect(date_printdisp.month.string.posc.x, date_printdisp.month.string.posc.y, DATE_PRINT_SPACE_STRING_MONTH, DATE_PRINT_K_HEIGTH_FONT, WHITE);
		ks0108GotoXY(date_printdisp.month.string.posc.x, date_printdisp.month.string.posc.y);
		ks0108Puts_P((const char *)&months_ofthe_year[date.month.num.MM -1]);
	}	

	static
	void date_printdisp__write_month_M10(void)
	{
		ks0108FillRect(date_printdisp.month.bcd.posc.M10_x, date_printdisp.month.bcd.posc.y, DATE_PRINT_K_WIDTH_FONT-1, DATE_PRINT_K_HEIGTH_FONT, WHITE);
		if (date.month.num.MM >= 10 )
		{
			ks0108GotoXY(date_printdisp.month.bcd.posc.M10_x, date_printdisp.month.bcd.posc.y);
			ks0108PutChar(date.month.bcd.M10 + 0x30);
		}
	}

	static
	void date_printdisp__write_month_M(void)
	{
		ks0108FillRect(date_printdisp.month.bcd.posc.M_x, date_printdisp.month.bcd.posc.y, DATE_PRINT_K_WIDTH_FONT-1, DATE_PRINT_K_HEIGTH_FONT, WHITE);
		ks0108GotoXY(date_printdisp.month.bcd.posc.M_x, date_printdisp.month.bcd.posc.y);
		ks0108PutChar(date.month.bcd.M + 0x30);
	}

	static 
	void date_printdisp__write_year_Y10(void)
	{

		ks0108FillRect(date_printdisp.year.bcd.posc.Y10_x, date_printdisp.year.bcd.posc.y, DATE_PRINT_K_WIDTH_FONT-1, DATE_PRINT_K_HEIGTH_FONT, WHITE);
		ks0108GotoXY(date_printdisp.year.bcd.posc.Y10_x, date_printdisp.year.bcd.posc.y);
		ks0108PutChar(date.year.bcd.Y10 + 0x30);
	}

	static 
	void date_printdisp__write_year_Y(void)
	{
		ks0108FillRect(date_printdisp.year.bcd.posc.Y_x, date_printdisp.year.bcd.posc.y, DATE_PRINT_K_WIDTH_FONT-1, DATE_PRINT_K_HEIGTH_FONT, WHITE);
		ks0108GotoXY(date_printdisp.year.bcd.posc.Y_x, date_printdisp.year.bcd.posc.y);
		ks0108PutChar(date.year.bcd.Y + 0x30);
	}

//Simula timming AM/PM
#ifdef __DEBUGGING_TIME__

	void simulating_DS3231_TIME_AMPM(void)
	{
		if (++time.sec.num.SS >=60)
		{
			time.sec.num.SS = 0x00;
			
			if (++time.min.num.MM >=60)
			{
				time.min.num.MM = 0x00;
				
				if (++time.hour.num.HH >=13)
				{
					time.hour.num.HH = 1;
					
					time.bf.AMPM = !time.bf.AMPM;
				}
			}
		}
		
		time.sec.bcd.S10 = (byte) (time.sec.num.SS / 10);
		time.sec.bcd.S	= (time.sec.num.SS >= 10)? time.sec.num.SS %10 : time.sec.num.SS;
		
		time.min.bcd.M10 = (byte) (time.min.num.MM / 10);
		time.min.bcd.M = (time.min.num.MM >= 10)? time.min.num.MM %10 : time.min.num.MM;
		
		time.hour.bcd.H10 = (byte) (time.hour.num.HH / 10);
		time.hour.bcd.H = (time.hour.num.HH >= 10)? time.hour.num.HH %10 : time.hour.num.HH;
	}
	
	//Llamado desde main()
	//#ifdef __DEBUGGING_TIME__
	//_test_time();
	//#endif
	void test_time(void)
	{
		ks0108SelectFont(Arial_Bold_14, ks0108ReadFontData, BLACK);
		
		time_printdisp.bf.print_second = 1;
		time.hour.num.HH = 1;
		time_printdisp__set_xy();
		time_printdisp__run();
		
		while (1)
		{
			//time_driver__d();
			simulating_DS3231_TIME_AMPM();
			time_printdisp__d();
			//_delay_ms(3000);
		}
	}		
	
	
#endif

#ifdef __DEBUGGING_DATE__

	void simulating_DS3231_DATE(void)
	{
		if (++date.day.num.day > 7)
		{
			date.day.num.day = 1;
		}
		if (++date.date.num.DD > 31 )
		{
			date.date.num.DD=1;
			
			if (++date.month.num.MM  > 12 )
			{
				date.month.num.MM = 1;

				if (++date.year.num.YY >= 100 )
				{
					date.year.num.YY = 0x00;
				}					
			}
		}

		date.date.bcd.D10 = (byte) (date.date.num.DD/10);
		date.date.bcd.D = (date.date.num.DD >=10)?(date.date.num.DD % 10) : (date.date.num.DD);
				
		date.month.bcd.M10 = (byte) (date.month.num.MM/10);
		date.month.bcd.M = (date.month.num.MM >=10)?(date.month.num.MM % 10) : (date.month.num.MM);
				
		date.year.bcd.Y10 = (byte) (date.year.num.YY/10);
		date.year.bcd.Y = (date.year.num.YY >=10)?(date.year.num.YY % 10) : (date.year.num.YY);
	}
	
	//Llamado desde main()
	//#ifdef __DEBUGGING_DATE__
	//_test_date();
	//#endif
	
	void test_date(void)
	{
		
		//date_printdisp.format_date = (DATE_FORMAT)sDAY_DD_sMONTH_YY;
		//date_printdisp.format_date = (DATE_FORMAT)DD_MM_YY;
		date_printdisp.format_date = (DATE_FORMAT)sDAY_DD_sMONTH;
		
		date_printdisp__set_xy();
		
		date.date.num.DD = 1;
		date.month.num.MM = 1;
		date.year.num.YY = 98;

		date_printdisp__run();
		while(1)
		{
			//date_driver__d();//este es el daemon
			simulating_DS3231_DATE();
			date_printdisp__d();
			_delay_ms(100);
		}	
	}
#endif	