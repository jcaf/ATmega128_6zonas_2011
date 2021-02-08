/*
 * DS3231_1.c
 *
 * Created: 13/02/2012 07:03:12 p.m.
 *  Author: jcaf
 */ 
#include "Includes/InitializeAllModules.h"

#ifdef _DS3231_

	void InitDS3231(void)
	{
		#ifdef _DS3231_USING_RSTCTRL_
			//DS3231_RST_ConfigModeMonitoringVDDifFall();	//default RST='1'

DS3231_RST_ConfigModeExternalReset();	//deja a '1' ~RST

		#endif
		
		#ifdef _DS3231_USING_VDDCTRL_
			ConfigOutputPin(DDRxDS3231_VDDCTRL,DS3231_pinVDDCTRL);
			DS3231_VDD_ON_10msESTABILIZACION(); //+10ms delay Estabilizar correctamente DS3231
		#endif
		
		DS3231_Config_CONTROLSTATUS_REG((0<<_DS3231_OSF_)		|
										(0<<_DS3231_EN32KHZ_)	|
										(0<<_DS3231_BSY_)		|
										(0<<_DS3231_A2F_)		|
										(0<<_DS3231_A1F_));
		
		DS3231_Config_CONTROL_REG((0<<_DS3231_EOSC_)	|
								(0<<_DS3231_BBSQW_) |
								(0<<_DS3231_CONV_)	|
								(0<<_DS3231_RS2_)	|
								(0<<_DS3231_RS1_)	|
								(0<<_DS3231_INTCN_) |
								(0<<_DS3231_A2IE_)	|
								(0<<_DS3231_A1IE_));
		
	}
	
	/*********************************************************************************
	Actualizar al final: TxData_I2C_unimaster(DS3231_SECONDS_REG);
	pues segun datasheet, luego de escribir SECONDS, empieza un nuevo "COUNTDOWN"

	The  countdown  chain  is  reset  whenever  the  seconds
	register is written. Write transfers occur on the acknowl-
	edge  from  the  DS3231.  Once  the  countdown  chain  is
	reset,  to  avoid  rollover  issues  the  remaining  time  and
	date registers must be written within 1 second. The 1Hz
	square-wave output, if enabled, transitions high 500ms
	after the seconds data transfer, provided the oscillator
	is already running.
	*********************************************************************************/
	void DS3231_UpdateClock(void)
	{
		I2Ccfx_UserBuff[0]=0x00;	//SEG
		I2Ccfx_UserBuff[1]=0x36;	//MIN
		I2Ccfx_UserBuff[2]=(1<<_DS3231_1224_) | (1<<_DS3231_AMPM_) | 0x07;	//HOUR //AM=0 PM=1
		//
		I2Ccfx_UserBuff[3]=_DS3231_SABADO_;
		I2Ccfx_UserBuff[4]=0x06;				//FECHA-DIA
		I2Ccfx_UserBuff[5]=_DS3231_FEBRUARY_;	//MES
		I2Ccfx_UserBuff[6]=0x21;				//A�O
		//
		DS3231_WriteArray2TKRegs(DS3231_SECONDS_REG, I2Ccfx_UserBuff, 7);
	}
	
#endif

