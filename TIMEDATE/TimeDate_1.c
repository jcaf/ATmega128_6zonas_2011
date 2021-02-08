/*
* TimeDate_1.c
*
* Created: 05/03/2012 09:58:03 p.m.
*  Author: jcaf
*/
/***************************************************************************************

***************************************************************************************/
#include "Includes/InitializeAllModules.h"

	#define KwidthFont (8)
	#define KheigthFont (ARIAL_BOLD_14_HEIGHT)//(10) -->14

	volatile struct _print_time print_time;
	volatile struct _date date;
	
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

	static void Time__print_am_pm(void);

	void Time__set_xy(void)
	{
		//Hh
		print_time.hour.Hx = 2;
		print_time.hour.hx = 2 + KwidthFont;
		print_time.hour.y = 30; 
		//:
		print_time.colon.x = 2 + (KwidthFont*2);
		print_time.colon.y = 30;
		//Mm
		print_time.min.Mx = 2 + ((KwidthFont*2)+3);	//3 = PARENTHESIS_WIDTH
		print_time.min.mx = 2 + ((KwidthFont*2)+3) + (KwidthFont*1);
		print_time.min.y = 30;
		//ap-m
		print_time.ampm.apx = 2 + ((KwidthFont*2)+3) + (KwidthFont*2)+2;
		print_time.ampm.apy = 30;
		print_time.ampm.mx = 2 + ((KwidthFont*2)+3) + (KwidthFont*3)+2;
		print_time.ampm.my = 30;
	}
	
	//////////////////////////////////////////////////////////////////////////////////
	//MaskingRegister from TimeKeeping Regs
	//..cuidado con century bit,,, am/pm / 1224 bits
	//////////////////////////////////////////////////////////////////////////////////
	void Time__update_registers_from_hardware(void)
	{
		DS3231_ReadTKRegs2Array(DS3231_SECONDS_REG, I2Ccfx_UserBuff, 3);//ya no 7
	
		print_time.sec.S = (I2Ccfx_UserBuff[0]>>4);// + 0x30;
		print_time.sec.s = ((I2Ccfx_UserBuff[0] & 0x0F)  );// + 0x30);

		print_time.min.M= (I2Ccfx_UserBuff[1]>>4);// + 0x30;
		print_time.min.m= ((I2Ccfx_UserBuff[1] & 0x0F)  );// + 0x30);

		print_time.hour.H= ( (I2Ccfx_UserBuff[2]>>4) & 0x01); // + 0x30;//clear 12/24 AM/PM
		print_time.hour.h= ((I2Ccfx_UserBuff[2] & 0x0F)  );// + 0x30);

		print_time.ampm.bf.AMPM = (I2Ccfx_UserBuff[2] & (1<<_DS3231_AMPM_) )>>_DS3231_AMPM_;
	}
	void Time__print_direct_time(void)
	{
		ks0108FillRect(print_time.hour.Hx, print_time.hour.y, KwidthFont-1, KheigthFont, WHITE);
		if (print_time.hour.H > 0)	
			{ks0108GotoXY(print_time.hour.Hx, print_time.hour.y); ks0108PutChar(print_time.hour.H + 0x30);}

		ks0108FillRect(print_time.hour.hx, print_time.hour.y, KwidthFont-1, KheigthFont, WHITE);
		ks0108GotoXY(print_time.hour.hx, print_time.hour.y); ks0108PutChar(print_time.hour.h + 0x30);
		//
		ks0108GotoXY(print_time.colon.x, print_time.colon.y); ks0108PutChar(':');
		// 
		ks0108FillRect(print_time.min.Mx, print_time.min.y, KwidthFont-1, KheigthFont, WHITE);
		ks0108GotoXY(print_time.min.Mx, print_time.min.y); ks0108PutChar(print_time.min.M + 0x30);

		ks0108FillRect(print_time.min.mx, print_time.min.y, KwidthFont-1, KheigthFont, WHITE);
		ks0108GotoXY(print_time.min.mx, print_time.min.y); ks0108PutChar(print_time.min.m + 0x30);
		
		Time__print_am_pm();
	}
	
	static void Time__print_am_pm(void)
	{
		ks0108FillRect(print_time.ampm.apx, print_time.ampm.apy, KwidthFont-1, KheigthFont, WHITE);
		ks0108GotoXY(print_time.ampm.apx, print_time.ampm.apy);
		
		if (print_time.ampm.bf.AMPM == 0)	
			{ks0108PutChar('a');}
		else 
			{ks0108PutChar('p');}
		
		ks0108FillRect(print_time.ampm.mx, print_time.ampm.my, KwidthFont-1, KheigthFont, WHITE);		
		ks0108GotoXY(print_time.ampm.mx, print_time.ampm.my);ks0108PutChar('m');
	}

	void Time__printing_time_selective(void)
	{
		if (print_time.min.m_old != print_time.min.m)
		{
			print_time.min.m_old = print_time.min.m;
			
			ks0108FillRect(print_time.min.mx, print_time.min.y, KwidthFont-1, KheigthFont, WHITE);		//CLEAR(m);
			ks0108GotoXY(print_time.min.mx, print_time.min.y); ks0108PutChar(print_time.min.m + 0x30);	//print(m)
		
			if (print_time.min.m == 0)
			{
				ks0108FillRect(print_time.min.Mx, print_time.min.y, KwidthFont-1, KheigthFont, WHITE);		//clearM();
				ks0108GotoXY(print_time.min.Mx, print_time.min.y); ks0108PutChar(print_time.min.M + 0x30);	//print(M);
			
				if (print_time.min.M == 0)
				{
					//cambio de hora

					//"hour.h" siempre cambia
					ks0108FillRect(print_time.hour.hx, print_time.hour.y, KwidthFont-1, KheigthFont, WHITE);	//clear(h);
					ks0108GotoXY(print_time.hour.hx, print_time.hour.y); ks0108PutChar(print_time.hour.h + 0x30);
					//
					if (print_time.hour.H_old != print_time.hour.H)
					{
						print_time.hour.H_old = print_time.hour.H;
						
						ks0108FillRect(print_time.hour.Hx, print_time.hour.y, KwidthFont-1, KheigthFont, WHITE);//clear(H);
						if (print_time.hour.H > 0)
						{
							ks0108GotoXY(print_time.hour.Hx, print_time.hour.y); ks0108PutChar(print_time.hour.H + 0x30);//print(H)
						}
					}
					
					if (print_time.ampm.bf.AMPM_old != print_time.ampm.bf.AMPM)
					{
						print_time.ampm.bf.AMPM_old = print_time.ampm.bf.AMPM;
						Time__print_am_pm();
					}
				}
			}
		}
	}
	
	void Time__print_time(void)
	{
		if (print_time.sm > 0)
		{
			ks0108SelectFont(Arial_Bold_14,ks0108ReadFontData,BLACK);

				Time__update_registers_from_hardware();
			
				if (print_time.sm == 1)
				{
					//presetting _old values.
					print_time.min.m_old = print_time.min.m;
					print_time.hour.H_old = print_time.hour.H;
					print_time.ampm.bf.AMPM_old = print_time.ampm.bf.AMPM;
					Time__print_direct_time();

					print_time.sm++;
				}
			
				if (print_time.sm == 2)
					{Time__printing_time_selective();}	
		
			ks0108SelectFont(SC,ks0108ReadFontData,BLACK);
		}
	}
	
	/////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////
	void date__update_registers_from_hardware(void)
	{
		DS3231_ReadTKRegs2Array(DS3231_DAY_REG, I2Ccfx_UserBuff, 4);
		
		//Day 1..7
		date.day.num.day = I2Ccfx_UserBuff[0];
		
		//Date Dd
		date.ddate.bcd.D10 = I2Ccfx_UserBuff[1]>>4;
		date.ddate.bcd.D = I2Ccfx_UserBuff[1] & 0x0F;
		date.ddate.num.DD = (date.ddate.bcd.D*10) + date.ddate.bcd.D; 
		
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
	
	//#define SC_WIDTH	(6)
	//#define SC_HEIGHT	(13)
	#define DATE_KwidthFont (SC_WIDTH)
	#define DATE_KheigthFont (SC_HEIGHT)
	
	//Determinado experimentalmente para tipografia SC
	#define DATE__SPACE_STRING_DAY		(23) //Dom..Sab
	#define DATE__SPACE_STRING_MONTH	(24) //Ene..Dic

	void date__set_xy(void)//x,y for print display
	{
		//Dom..Sab STRING
		date.day.printdisp.string.posc.x = 2;
		date.day.printdisp.string.posc.y = 47;

		//Dd 1..31 FECHA-NUMERICO
		date.ddate.printdisp.bcd.posc.D10_x = 2 + (DATE__SPACE_STRING_DAY);
		date.ddate.printdisp.bcd.posc.D_x = 2 + (DATE__SPACE_STRING_DAY)+ (DATE_KwidthFont);
		date.ddate.printdisp.bcd.posc.y = 47;//y common

		//Mm Ene...Dic STRING
		date.month.printdisp.string.posc.x = 2 + (DATE__SPACE_STRING_DAY)+ (DATE_KwidthFont*2) +3;
		date.month.printdisp.string.posc.y = 47;

		//Yh 00..99 NUMERIC
		//date.year.printdisp.bcd.posc.Y10_x = 2 + (DATE__SPACE_STRING_DAY)+ (DATE_KwidthFont*2 +3) + (DATE__SPACE_STRING_MONTH);
		//date.year.printdisp.bcd.posc.Y_x = 2 + (DATE__SPACE_STRING_DAY)+ (DATE_KwidthFont*2 +3) + (DATE__SPACE_STRING_MONTH) + (DATE_KwidthFont);
		//date.year.printdisp.bcd.posc.y = 47;//y common
	}

	void date__print_direct_date(void)
	{
		//Dom..Sab,
		ks0108FillRect(date.day.printdisp.string.posc.x, date.day.printdisp.string.posc.y,DATE__SPACE_STRING_DAY, DATE_KheigthFont, WHITE);
		ks0108GotoXY(date.day.printdisp.string.posc.x, date.day.printdisp.string.posc.y); ks0108Puts_P((const char *)&days_ofthe_week[date.day.num.day -1]);
		//ks0108Puts_P(PSTR(" ,"));
		
		//Dd
		ks0108FillRect(date.ddate.printdisp.bcd.posc.D10_x, date.ddate.printdisp.bcd.posc.y, DATE_KwidthFont, DATE_KheigthFont, WHITE);
		if (date.ddate.bcd.D10 >0)	
		{
			ks0108GotoXY(date.ddate.printdisp.bcd.posc.D10_x, date.ddate.printdisp.bcd.posc.y); 
			ks0108PutChar(date.ddate.bcd.D10 + 0x30);
		}
		ks0108FillRect(date.ddate.printdisp.bcd.posc.D_x, date.ddate.printdisp.bcd.posc.y, DATE_KwidthFont, DATE_KheigthFont, WHITE);
		ks0108GotoXY(date.ddate.printdisp.bcd.posc.D_x, date.ddate.printdisp.bcd.posc.y); ks0108PutChar(date.ddate.bcd.D + 0x30);

		//Text month
		ks0108FillRect(date.month.printdisp.string.posc.x, date.month.printdisp.string.posc.y, DATE__SPACE_STRING_MONTH, DATE_KheigthFont, WHITE);
		ks0108GotoXY(date.month.printdisp.string.posc.x, date.month.printdisp.string.posc.y); ks0108Puts_P((const char *)&months_ofthe_year[date.month.num.MM -1]);
		
		
		//opcional, mostrar anio
		
		//ks0108Puts_P(PSTR("20"));//depende de century bit
		
		//ks0108FillRect(date.year.printdisp.bcd.posc.Y10_x, date.year.printdisp.bcd.posc.y, DATE_KwidthFont, DATE_KheigthFont, WHITE);
		//ks0108GotoXY(date.year.printdisp.bcd.posc.Y10_x, date.year.printdisp.bcd.posc.y); ks0108PutChar(date.year.bcd.Y10 + 0x30);
		//
		//ks0108FillRect(date.year.printdisp.bcd.posc.Y_x, date.year.printdisp.bcd.posc.y, DATE_KwidthFont, DATE_KheigthFont, WHITE);
		//ks0108GotoXY(date.year.printdisp.bcd.posc.Y_x, date.year.printdisp.bcd.posc.y); ks0108PutChar(date.year.bcd.Y + 0x30);
	}
	
	//////////////////////////////////////////////////////////////////////
	//daemon or service
	//Numerical update
	//if change day, then, check for DD-->MM-->YY
	//////////////////////////////////////////////////////////////////////
	void date_d(void)
	{
		date__print(0); //check if date.sm ==1 restart print?

		if (date.day.num.day_old != date.day.num.day)
		{
			date.day.num.day_old = date.day.num.day;
			
						date__print((DATE_PRINT)DAY);		
			
			//de hecho q la fecha ha cambiado.
			date.ddate.num.DD = date.ddate.bcd.D10*10 + date.ddate.bcd.D;
	
						date__print((DATE_PRINT)DATE);		
			
			if (date.month.bcd.M_old != date.month.bcd.M)
			{
				date.month.bcd.M_old = date.month.bcd.M;

				date.month.num.MM = date.month.bcd.M10*10 + date.month.bcd.M;
	
						date__print((DATE_PRINT)MONTH);
							
				if (date.year.bcd.Y_old != date.year.bcd.Y)
				{
					date.year.bcd.Y_old = date.year.bcd.Y;

					date.year.num.YY = date.year.bcd.Y10*10 + date.year.bcd.Y;
					
						date__print((DATE_PRINT)YEAR);
				}
			}
		}
	}
	
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	void date__print(DATE_PRINT Ddmy)
	{
		if (date.sm == 1)
		{
			date__print_direct_date();
			date.sm++;
		}
		
		if (date.sm == 2)
		{
			if (Ddmy == (DATE_PRINT)DAY )
			{
				//Dom..Sab,
				ks0108FillRect(date.day.printdisp.string.posc.x, date.day.printdisp.string.posc.y,DATE__SPACE_STRING_DAY, DATE_KheigthFont, WHITE);
				ks0108GotoXY(date.day.printdisp.string.posc.x, date.day.printdisp.string.posc.y); ks0108Puts_P((const char *)&days_ofthe_week[date.day.num.day -1]);
				//ks0108Puts_P(PSTR(" ,"));
			}
			else if (Ddmy == (DATE_PRINT)DATE )
			{
				//Dd
				ks0108FillRect(date.ddate.printdisp.bcd.posc.D10_x, date.ddate.printdisp.bcd.posc.y, DATE_KwidthFont, DATE_KheigthFont, WHITE);
				if (date.ddate.bcd.D10 >0)
				{
					ks0108GotoXY(date.ddate.printdisp.bcd.posc.D10_x, date.ddate.printdisp.bcd.posc.y);
					ks0108PutChar(date.ddate.bcd.D10 + 0x30);
				}
				ks0108FillRect(date.ddate.printdisp.bcd.posc.D_x, date.ddate.printdisp.bcd.posc.y, DATE_KwidthFont, DATE_KheigthFont, WHITE);
				ks0108GotoXY(date.ddate.printdisp.bcd.posc.D_x, date.ddate.printdisp.bcd.posc.y); ks0108PutChar(date.ddate.bcd.D + 0x30);
			}
			else if (Ddmy == (DATE_PRINT)MONTH )
			{
				//Text month
				ks0108FillRect(date.month.printdisp.string.posc.x, date.month.printdisp.string.posc.y, DATE__SPACE_STRING_MONTH, DATE_KheigthFont, WHITE);
				ks0108GotoXY(date.month.printdisp.string.posc.x, date.month.printdisp.string.posc.y); ks0108Puts_P((const char *)&months_ofthe_year[date.month.num.MM -1]);
			}
			else if (Ddmy == (DATE_PRINT)YEAR)
			{
				//opcional, mostrar anio
				
				//ks0108Puts_P(PSTR("20"));//depende de century bit
				
				//ks0108FillRect(date.year.printdisp.bcd.posc.Y10_x, date.year.printdisp.bcd.posc.y, DATE_KwidthFont, DATE_KheigthFont, WHITE);
				//ks0108GotoXY(date.year.printdisp.bcd.posc.Y10_x, date.year.printdisp.bcd.posc.y); ks0108PutChar(date.year.bcd.Y10 + 0x30);
				//
				//ks0108FillRect(date.year.printdisp.bcd.posc.Y_x, date.year.printdisp.bcd.posc.y, DATE_KwidthFont, DATE_KheigthFont, WHITE);
				//ks0108GotoXY(date.year.printdisp.bcd.posc.Y_x, date.year.printdisp.bcd.posc.y); ks0108PutChar(date.year.bcd.Y + 0x30);

			}
		}
		
	}


//Simula timming AM/PM
#ifdef __DEBUGGING_HOUR_DATE__

	void simulating_DS3231_AMPM(void)
	{
		if (++print_time.min.m==10)
		{
			print_time.min.m=0;
		
			if (++print_time.min.M==6)
			{
				print_time.min.M=0;
				if (print_time.min.M==0)
				{
					if (++print_time.hour.h==10)
					{
						print_time.hour.H++;
						print_time.hour.h=0;
					}
					if ( (print_time.hour.H == 1) && (print_time.hour.h==3) )
					{
						print_time.hour.H = 0;
						print_time.hour.h = 1;
					}
				}
			}
		}
	}
	
	void _test_time(void)
	{
		ks0108SelectFont(Arial_Bold_14,ks0108ReadFontData,BLACK);
		
		Time__set_xy();

		//DS3231_ReadTKRegs();
		print_time.hour.h = 1; //am/pm set -> Empieza desde la 1 de la tarde
		//simulating_DS3231_AMPM();
		print_time.min.m_old = print_time.min.m;
		print_time.hour.H_old = print_time.hour.H;
		Time__print_direct_time();

		while (1)
		{
			//DS3231_ReadTKRegs();
			simulating_DS3231_AMPM();
			Time__printing_time_selective();
			_delay_ms(100);
		}
	}		
	
	//Llamado desde main()
	//#ifdef __DEBUGGING_HOUR_DATE__
	//_test_time();
	//#endif
	//
#endif
