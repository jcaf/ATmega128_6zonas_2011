/*
 * TimeDate.h
 *
 * Created: 05/03/2012 09:58:11 p.m.
 *  Author: jcaf
 */ 
#ifndef TIMEDATE_H_
#define TIMEDATE_H_
	
	struct _time//Format: HH:MM:SS
	{
		struct
		{
			struct
			{
				byte H10;
				byte H;
				
				byte H10_old;
				byte H_old;
			}bcd;
			struct
			{
				byte HH;
			}num;
		}hour;
		
		struct
		{
			struct
			{
				byte M10;
				byte M;
				
				byte M10_old;
				byte M_old;
			}bcd;
			struct
			{
				byte MM;
			}num;
		}min;
		
		struct
		{
			struct
			{
				byte S10;
				byte S;
				
				byte S10_old;
				byte S_old;
			}bcd;
			struct
			{
				byte SS;
			}num;
		}sec;

		struct
		{
			unsigned AMPM:1;
			unsigned AMPM_old:1;
			unsigned __none:6;
		}bf;
		
	};
	
	struct _time_printdisp
	{
		struct
		{
			struct
			{
				struct
				{
					TYPE_XYDISP_X H10_x;
					TYPE_XYDISP_X H_x;
					TYPE_XYDISP_Y y;	//common
				}posc;
			}bcd;
			
			struct {
				byte HH;
			}num;

		}hour;
		
		struct
		{
			struct
			{
				xy_display posc;
			}character;
		}colonHHMM;//: entre Hour:Minutes

		struct
		{
			struct
			{
				struct
				{
					TYPE_XYDISP_X M10_x;
					TYPE_XYDISP_X M_x;
					TYPE_XYDISP_Y y;	//common
				}posc;
			}bcd;
			
			struct {
				byte MM;
			}num;

		}min;
		
		struct
		{
			struct
			{
				xy_display posc;
			}character;
		}colonMMSS;//: entre Hour:Minutes


		struct
		{
			struct
			{
				struct
				{
					TYPE_XYDISP_X S10_x;
					TYPE_XYDISP_X S_x;
					TYPE_XYDISP_Y y;	//common
				}posc;
			}bcd;
			
			struct {
				byte SS;
			}num;

		}sec;
		
		struct
		{
			struct
			{
				struct
				{
					TYPE_XYDISP_X AP_x;	//am / pm
					TYPE_XYDISP_X M_x;
					TYPE_XYDISP_Y y;	//common
				}posc;
				
			}character;
			
		}ampm;
		
		byte sm;
		
		struct
		{
			unsigned print_second:1;
			unsigned __none:7;
		}bf;
		
	};
	
	extern volatile struct _time time;
	extern volatile struct _time_printdisp time_printdisp;
	
	void time_driver__d(void);
	
	//Functions por printing
	typedef enum _TIME_PRINT
	{
		SEC=1,
		MIN,
		HOUR,
		APM
	}TIME_PRINT;
	
	void time_printdisp__d(void);
	void time_printdisp__set_xy(void);
	
	#define time_printdisp__run()	do{time_printdisp.sm=1;}while(0)
	#define time_printdisp__stop()	do{time_printdisp.sm=0;}while(0)

	//////////////////////////////////////////////////////
	//////////////////////////////////////////////////////
	typedef enum _DATE_FORMAT
	{
		sDAY_DD_sMONTH = 0,
		sDAY_DD_sMONTH_YY,
		sDAY_DD_sMONTH_20YY,
		sDAY_DD_MM_20YY,
		sDAY_DD_MM_YY,
		DD_MM_YY,
		DD_MM
	}DATE_FORMAT;
		
	
	struct _date
	{
		struct
		{
			struct
			{
				byte day;//as idx for string[]
			}num;
		}day;
		
		struct
		{
			struct
			{
				byte D10;
				byte D;	
				
				byte D10_old;
				byte D_old;
			}bcd;			
			
			struct {
				byte DD;	
			}num;
		}date;

		struct
		{
			struct
			{
				byte M10;
				byte M;
				
				byte M10_old;
				byte M_old;
			}bcd;
			
			struct {
				byte MM;
			}num;
		}month;		

		struct _year
		{
			struct
			{
				byte Y10;
				byte Y;
				
				byte Y10_old;
				byte Y_old;
			}bcd;
			
			struct	{
				byte YY;
			}num;
		}year;
	};	
	
	struct _date_printdisp
	{
		struct 
		{
			struct //strictly full string/text
			{
				xy_display posc;
			}string;
			
			struct {
				byte DAY;	
			}num;
			
		}day;

		struct 
		{
			struct 
			{
				struct 
				{
					TYPE_XYDISP_X D10_x;
					TYPE_XYDISP_X D_x;
					TYPE_XYDISP_Y y;	//common
				}posc;
			}bcd;
			
			struct {
				byte DD;	
			}num;

		}date;
				
		struct
		{
			struct
			{
				xy_display posc;
			}character;
		}slashDDMM;//: / entre DATE-MONTH
		
		struct 
		{
			struct 
			{
				struct 
				{
					TYPE_XYDISP_X M10_x;
					TYPE_XYDISP_X M_x;
					TYPE_XYDISP_Y y;	//common
				}posc;
			}bcd;

			struct _string_month
			{
				xy_display posc;
			}string;

			struct {
				byte MM;
			}num;

		}month;
		
		struct
		{
			struct
			{
				xy_display posc;
			}character;
		}slashMMYY;//: / entre MONTH-YEAR
		
		struct 
		{
			struct 
			{
				struct 
				{
					TYPE_XYDISP_X Y10_x;
					TYPE_XYDISP_X Y_x;
					TYPE_XYDISP_Y y;	//common
				}posc;
			}bcd;

			struct {
				byte YY;
			}num;

		}year;
		
		DATE_FORMAT format_date;
		byte sm;

	};
	
	
	extern volatile struct _date date;
	extern volatile struct _date_printdisp date_printdisp;

	void date_driver__d(void); //service or daemon

	//Functions por printing	
	typedef enum _DATE_PRINT
	{
		DAY=1,
		DATE,
		MONTH,
		YEAR
	}DATE_PRINT;
	extern const char days_ofthe_week[7][4];
	extern const char months_ofthe_year[12][4];
	
	void date_printdisp__set_xy(void);
	void date_printdisp__d(void);
	
	#define date_printdisp__run()	do{date_printdisp.sm=1;}while(0)
	#define date_printdisp__stop()	do{date_printdisp.sm=0;}while(0)
	

	//////////////////////////////////////////////
	
	//#define __DEBUGGING_TIME__
	#ifdef __DEBUGGING_TIME__
		void simulating_DS3231_TIME_AMPM(void);
		void test_time(void);
	#endif
	
	//#define __DEBUGGING_DATE__
	#ifdef __DEBUGGING_DATE__
		void simulating_DS3231_DATE(void);
		void test_date(void);
	#endif
	//////////////////////////////////////////////
	
#endif /* TIMEDATE_H_ */