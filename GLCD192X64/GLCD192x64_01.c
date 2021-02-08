	#include "Includes/InitializeAllModules.h"

#ifdef _GLCD192X64_	
	
	//static void _GLCD192X64_DB0_DB7_ConfigOutputs_(void);
	//static void _GLCD192X64_DB0_DB7_ConfigInputs_(void);
	/************************************************************************
	Config Ouput pins + clear latch
	************************************************************************/
	//defined but not used
	/*static void _GLCD192X64_DB0_DB7_ConfigOutputs_(void)
	{
		PinTo0(PORTxGLCD192X64_DB0,GLCD192X64_DB0);
		ConfigOutputPin(DDRxGLCD192X64_DB0,GLCD192X64_DB0);
		//
		PinTo0(PORTxGLCD192X64_DB1,GLCD192X64_DB1);
		ConfigOutputPin(DDRxGLCD192X64_DB1,GLCD192X64_DB1);
		//
		PinTo0(PORTxGLCD192X64_DB2,GLCD192X64_DB2);
		ConfigOutputPin(DDRxGLCD192X64_DB2,GLCD192X64_DB2);
		//
		PinTo0(PORTxGLCD192X64_DB3,GLCD192X64_DB3);
		ConfigOutputPin(DDRxGLCD192X64_DB3,GLCD192X64_DB3);
		//
		PinTo0(PORTxGLCD192X64_DB4,GLCD192X64_DB4);
		ConfigOutputPin(DDRxGLCD192X64_DB4,GLCD192X64_DB4);
		//
		PinTo0(PORTxGLCD192X64_DB5,GLCD192X64_DB5);
		ConfigOutputPin(DDRxGLCD192X64_DB5,GLCD192X64_DB5);
		//
		PinTo0(PORTxGLCD192X64_DB6,GLCD192X64_DB6);
		ConfigOutputPin(DDRxGLCD192X64_DB6,GLCD192X64_DB6);
		//
		PinTo0(PORTxGLCD192X64_DB7,GLCD192X64_DB7);
		ConfigOutputPin(DDRxGLCD192X64_DB7,GLCD192X64_DB7);
	}*/		
	/************************************************************************
	Config input pins + Pull-up disabled	
	************************************************************************/
	//defined but not used
	
	/*static void _GLCD192X64_DB0_DB7_ConfigInputs_(void)
	{
		PinTo0(PORTxGLCD192X64_DB0,GLCD192X64_DB0);
		ConfigInputPin(DDRxGLCD192X64_DB0,GLCD192X64_DB0);
		//
		PinTo0(PORTxGLCD192X64_DB1,GLCD192X64_DB1);
		ConfigInputPin(DDRxGLCD192X64_DB1,GLCD192X64_DB1);
		//
		PinTo0(PORTxGLCD192X64_DB2,GLCD192X64_DB2);
		ConfigInputPin(DDRxGLCD192X64_DB2,GLCD192X64_DB2);
		//
		PinTo0(PORTxGLCD192X64_DB3,GLCD192X64_DB3);
		ConfigInputPin(DDRxGLCD192X64_DB3,GLCD192X64_DB3);
		//
		PinTo0(PORTxGLCD192X64_DB4,GLCD192X64_DB4);
		ConfigInputPin(DDRxGLCD192X64_DB4,GLCD192X64_DB4);
		//
		PinTo0(PORTxGLCD192X64_DB5,GLCD192X64_DB5);
		ConfigInputPin(DDRxGLCD192X64_DB5,GLCD192X64_DB5);
		//
		PinTo0(PORTxGLCD192X64_DB6,GLCD192X64_DB6);
		ConfigInputPin(DDRxGLCD192X64_DB6,GLCD192X64_DB6);
		//
		PinTo0(PORTxGLCD192X64_DB7,GLCD192X64_DB7);
		ConfigInputPin(DDRxGLCD192X64_DB7,GLCD192X64_DB7);
	}*/		
	/************************************************************************
	
	************************************************************************/
	void InitGLCD192x64(void)
	{
		/*
		//OK, solo que esta inicialización se encuentra por ahora en manos de ks108.c
		PinTo0(PORTxGLCD192X64_RS,GLCD192X64_RS);
		ConfigOutputPin(DDRxGLCD192X64_RS,GLCD192X64_RS);
		//
		PinTo0(PORTxGLCD192X64_RW,GLCD192X64_RW);
		ConfigOutputPin(DDRxGLCD192X64_RW,GLCD192X64_RW);
		//
		PinTo0(PORTxGLCD192X64_E,GLCD192X64_E);
		ConfigOutputPin(DDRxGLCD192X64_E,GLCD192X64_E);
		//
		_GLCD192X64_DB0_DB7_ConfigOutputs_();
		
		PinTo0(PORTxGLCD192X64_CS1,GLCD192X64_CS1);
		ConfigOutputPin(DDRxGLCD192X64_CS1,GLCD192X64_CS1);
		//
		PinTo0(PORTxGLCD192X64_CS2,GLCD192X64_CS2);
		ConfigOutputPin(DDRxGLCD192X64_CS2,GLCD192X64_CS2);
		//
		PinTo0(PORTxGLCD192X64_CS3,GLCD192X64_CS3);
		ConfigOutputPin(DDRxGLCD192X64_CS3,GLCD192X64_CS3);
		*/
		//
		#ifdef _USING_GLCD_RST_PIN_
			PinTo0(PORTxGLCD192X64_RST,GLCD192X64_RST);
			ConfigOutputPin(DDRxGLCD192X64_RST,GLCD192X64_RST);
			//GLCD192X64_RSTB_HOLDING()
			//tRS();				//Reset time tRS = 1.0 us
			//tRS();				//Reset time tRS = 1.0 us
			//GLCD192X64_RSTB_RELEASE()
		#endif
		
		#ifdef _USING_GLCD_BACKLIGHT_PIN_
			ConfigOutputPin(DDRxGLCD192X64_BKLIGHT, GLCD192X64_BKLIGHT);
			GLCD192X64_BKLIGHT_ON();
			
			//Add Jul 17 2012, PWM on BackLight GLCD
			
			//
			//Inicia con DC 100% ->Handler always in background
			DirectForce_And_Hold_MAX_PWM_BLGLCD();
			
			//
			//ResetCounterTimmerForNewKeepingTimmingBLGLCD();	//BackLightGLCD reset-timming
			//
		#endif
		
	}
	/************************************************************************

	************************************************************************/
	void StrobeEnableGLCD192x64(void)
	{
		PinGLCD192X64_E_To1();
		tWH();
		PinGLCD192X64_E_To0();
	}
	/************************************************************************
	DISPLAY START LINE REGISTER
	Z-Address (64 bits)            
	FRM + CL -> 	
	************************************************************************/
	
	
#endif