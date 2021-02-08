/*
 * DS3231.h
 *
 * Created: 13/02/2012 07:03:22 p.m.
 *  Author: jcaf
 */ 
#ifndef DS3231_H_
#define DS3231_H_

	/*************************************************
	Dallas 0xD0 I2C devices, for ever???
	*************************************************/
	#define DS3231_SLAVE_ADDRESS	(0xD0)
	
	/*************************************************
	Descomentar si se usa un pin de microprocesor como VDD
	Mas adelante se define el pin de CONTROL DE VDD
	
	NOTA: Generar delay x estabilizar correctamente DS3231
	*************************************************/
	#define _DS3231_USING_VDDCTRL_
		
	/*************************************************
	Descomentar si se usa un pin de microprocesor como RST
	Mas adelante se define el pin de CONTROL DE RST
	The RST pin has an internal 50kΩ (nominal) pullup resistor to VCC.

	*************************************************/
	#define _DS3231_USING_RSTCTRL_	
	
	/*************************************************
	Timekeeping register
	
	Note: Unless otherwise specified, the registers state 
	is not defined when power is first applied.

	*************************************************/
	#define DS3231_SECONDS_REG			(0x00)
	#define DS3231_MINUTES_REG			(0x01)
	#define DS3231_HOURS_REG			(0x02)
	#define DS3231_DAY_REG				(0x03)
	#define DS3231_DATE_REG				(0x04)
	#define DS3231_MONTHCENTURY_REG		(0x05)//The century bit(7) is toggled when the years register overflows from 99 to 00.
	#define DS3231_YEAR_REG				(0x06)
	//	
	#define DS3231_ALARM1_SECONDS_REG	(0x07)
	#define DS3231_ALARM1_MINUTES_REG	(0x08)
	#define DS3231_ALARM1_HOURS_REG		(0x09)
	#define DS3231_ALARM1_DAYDATE_REG	(0x0A)
	//
	#define DS3231_ALARM2_MINUTES_REG	(0x0B)
	#define DS3231_ALARM2_HOURS_REG		(0x0C)
	#define DS3231_ALARM2_DAYDATE_REG	(0x0D)	//Day/Date
	
	//
	#define DS3231_CONTROL_REG			(0x0E)
	#define DS3231_CONTROLSTATUS_REG	(0x0F)	//Control/Status
	#define DS3231_AGINGOFFSET_REG		(0x10)
	#define DS3231_MSBTEMP_REG			(0x11)
	#define DS3231_LSBTEMP_REG			(0x12)
	
	/*************************************************
		BIT POSITION
	*************************************************/
	//Hour register
	#define _DS3231_1224_	(6)	//1->12  0->24
	#define _DS3231_AMPM_	(5)
	
	//Month register
	#define _DS3231_CENTURY_	(7)
	
	//Commons
	#define _DS3231_A1M1_	(7)
	#define _DS3231_A1M2_	(7)
	#define _DS3231_A1M3_	(7)
	#define _DS3231_A1M4_	(7)
	//
	#define _DS3231_A2M2_	(7)
	#define _DS3231_A2M3_	(7)
	#define _DS3231_A2M4_	(7)
	//	
	#define _DS3231_DYDT_	(6)
	//
	#define _DS3231_SIGN_	(7)

	//Control register
	#define _DS3231_EOSC_		(7)
	#define _DS3231_BBSQW_		(6)
	#define _DS3231_CONV_		(5)
	#define _DS3231_RS2_		(4)
	#define _DS3231_RS1_		(3)
	#define _DS3231_INTCN_		(2)
	#define _DS3231_A2IE_		(1)
	#define _DS3231_A1IE_		(0)
	
	//Control/Status register
	#define _DS3231_OSF_		(7)
	#define _DS3231_EN32KHZ_	(3)
	#define _DS3231_BSY_		(2)
	#define _DS3231_A2F_		(1)
	#define _DS3231_A1F_		(0)

	/**************************************************
	
	**************************************************/
	#define _DS3231_DOMINGO_    (0x01)
    #define _DS3231_LUNES_      (0x02)
    #define _DS3231_MARTES_     (0x03)
    #define _DS3231_MIERCOLES_  (0x04)
    #define _DS3231_JUEVES_     (0x05)
    #define _DS3231_VIERNES_    (0x06)
    #define _DS3231_SABADO_     (0x07)
    //
    #define _DS3231_JANUARY_	(0x01)
    #define _DS3231_FEBRUARY_	(0x02)
    #define _DS3231_MARCH_		(0x03)
    #define _DS3231_APRIL_		(0x04)
    #define _DS3231_MAY_		(0x05)
    #define _DS3231_JUNE_		(0x06)
    #define _DS3231_JULY_		(0x07)
    #define _DS3231_AUGUST_		(0x08)
    #define _DS3231_SEPTEMBER_	(0x09)
    #define _DS3231_OCTOBER_	(0x10)
    #define _DS3231_NOVEMBER_	(0x11)
    #define _DS3231_DECEMBER_	(0x12)
	
	
	/*************************************************
		VDD CONTROL
	*************************************************/
	#ifdef _DS3231_USING_VDDCTRL_

		#define PORTxDS3231_VDDCTRL	(PORTF)
		#define DDRxDS3231_VDDCTRL	(DDRF)	
		#define PINxDS3231_VDDCTRL	(PINF)
		//
		#define DS3231_pinVDDCTRL	(0)	//PF0
		//
		#define DS3231_VDD_ON()		do{PinTo1(PORTxDS3231_VDDCTRL,DS3231_pinVDDCTRL);}while(0)
		#define DS3231_VDD_ON_10msESTABILIZACION() do{PinTo1(PORTxDS3231_VDDCTRL,DS3231_pinVDDCTRL);_delay_ms(10);}while(0)
		
		#define DS3231_VDD_OFF()	do{PinTo0(PORTxDS3231_VDDCTRL,DS3231_pinVDDCTRL);}while(0)

	#endif
	/*************************************************
		~RST CONTROL
	*************************************************/
	#ifdef _DS3231_USING_RSTCTRL_

		#define PORTxDS3231_RSTCTRL	(PORTF)
		#define DDRxDS3231_RSTCTRL	(DDRF)	
		#define PINxDS3231_RSTCTRL	(PINF)
		//
		#define DS3231_pinRSTCTRL	(1)	//PF1
		//
		#define DS3231_RST_HIGH()		do{PinTo1(PORTxDS3231_RSTCTRL,DS3231_pinRSTCTRL);}while(0)
		#define DS3231_RST_LOW()		do{PinTo0(PORTxDS3231_RSTCTRL,DS3231_pinRSTCTRL);}while(0)

		//ModeMonitoringVDDFall: por defecto deja el pin en entrada + pull-up desactivado.DS3231 integra su propia resistencia.
		//El programa en modo "ModeExternalReset" DEBERIA dejar el pin RST en alto,,,,para que el cambio sea "transparente", por un ciclo
		//se vera el pin como ENTRADA+Pullup, luego procede a desactivarlo
		#define DS3231_RST_ConfigModeMonitoringVDDifFall() do{ConfigInputPin(DDRxDS3231_RSTCTRL,DS3231_pinRSTCTRL);PinTo0(PORTxDS3231_RSTCTRL,DS3231_pinRSTCTRL);}while(0)
		
		//ModeExternalReset:Por defecto deja el pin en Alto. Entrada+Pull-up intermediario para pasar a pin de salida en alto.
		#define DS3231_RST_ConfigModeExternalReset() do{PinTo1(PORTxDS3231_RSTCTRL,DS3231_pinRSTCTRL);ConfigOutputPin(DDRxDS3231_RSTCTRL,DS3231_pinRSTCTRL);}while(0)
	
	#endif
	/*************************************************
		MACROS
	*************************************************/
	#define DS3231_Config_CONTROLSTATUS_REG(DATA) do{I2Ccfx_Write1Byte(DS3231_SLAVE_ADDRESS, DS3231_CONTROLSTATUS_REG,DATA);}while(0)
	
	#define DS3231_Config_CONTROL_REG(DATA) do{I2Ccfx_Write1Byte(DS3231_SLAVE_ADDRESS, DS3231_CONTROL_REG,DATA);}while(0)
	
	#define DS3231_WriteArray2TKRegs(START_ADDRESS,pDATA,NUMBYTES_TOWRITE) do{I2Ccfx_WriteArray(DS3231_SLAVE_ADDRESS,START_ADDRESS, pDATA, NUMBYTES_TOWRITE);}while(0)
	
	#define DS3231_ReadTKRegs2Array(START_ADDRESS, pDATA, NUMBYTES_TOREAD) do{I2Ccfx_ReadRegistersAtAddress(DS3231_SLAVE_ADDRESS,START_ADDRESS, pDATA, NUMBYTES_TOREAD);}while(0)
	
	void InitDS3231(void);
	void DS3231_UpdateClock(void);

	
#endif /* DS3231_H_ */
