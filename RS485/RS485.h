/*
 * RS485.h
 *
 * Created: 15/02/2012 10:51:50 a.m.
 *  Author: jcaf
 */ 
#ifndef RS485_H_
#define RS485_H_

	/***********************************************************************************
	DRIVER -> 1PIN'a'
	RECEIVER -> 1PIN'b' ???
	ó
	DRIVER/RECEIVER = 1 PIN
	***********************************************************************************/
	#define	_1_PIN_CTRL_DRV_RCV		(0)
	#define	_2_PIN_CTRL_DRV_RCV		(1)

	/***********************************************************************************

	***********************************************************************************/
	#define NUM_PINS_CTRL_DRV_RCV	_1_PIN_CTRL_DRV_RCV
	//#define NUM_PINS_CTRL_DRV_RCV	_2_PIN_CTRL_DRV_RCV
	
	#if	NUM_PINS_CTRL_DRV_RCV == _2_PIN_CTRL_DRV_RCV
		
		//Driver
		#define DDRxRS485_CTRLDRIVER0		(DDR)
		#define PORTxRS485_CTRLDRIVER0		(PORT)
		#define PINxRS485_CTRLDRIVER0		(PIN)
		#define RS485_pinCTRLDRIVER0		(0)	//?
		
		#define RS485_CTRLDRIVER0_HIGH()		do{PinTo1(PORTxRS485_CTRLDRIVER0,RS485_pinCTRLDRIVER0);}while(0)
		#define RS485_CTRLDRIVER0_LOW()			do{PinTo0(PORTxRS485_CTRLDRIVER0,RS485_pinCTRLDRIVER0);}while(0)
		
		#define RS485_CTRLDRIVER0_ENABLE()		RS485_CTRLDRIVER0_HIGH()
		#define RS485_CTRLDRIVER0_DISABLE()		RS485_CTRLDRIVER0_LOW()
		
		//Receiver
		#define DDRxRS485_CTRLRECEIVER0		(DDR)
		#define PORTxRS485_CTRLRECEIVER0	(PORT)
		#define PINxRS485_CTRLRECEIVER0		(PIN)
		#define RS485_pinCTRLRECEIVER0		(0)	//?
		
		#define RS485_CTRLRECEIVER0_HIGH()		do{PinTo1(PORTxRS485_CTRLRECEIVER0,RS485_pinCTRLRECEIVER0);}while(0)
		#define RS485_CTRLRECEIVER0_LOW()		do{PinTo0(PORTxRS485_CTRLRECEIVER0,RS485_pinCTRLRECEIVER0);}while(0)
		
		#define RS485_CTRLRECEIVER0_ENABLE()	RS485_CTRLRECEIVER0_LOW()
		#define RS485_CTRLRECEIVER0_DISABLE()	RS485_CTRLRECEIVER0_HIGH()
		
		//Common macros
		#define RS485_DRVEn_RCVDis()	do{RS485_CTRLRECEIVER0_DISABLE();RS485_CTRLDRIVER0_ENABLE();}while(0)
		#define RS485_RCVEn_DRVDis()	do{RS485_CTRLDRIVER0_DISABLE();RS485_CTRLRECEIVER0_ENABLE();}while(0)
		
		//Extras...
		#define RS485_RCVEn_DRVEn()		do{RS485_CTRLDRIVER0_ENABLE();RS485_CTRLRECEIVER0_ENABLE();}while(0)
		#define RS485_RCVDis_DRVDis()	do{RS485_CTRLDRIVER0_DISABLE();RS485_CTRLRECEIVER0_DISABLE();}while(0)
		//others
	
	#else	//NUM_PINS_CTRL_DRV_RCV	== _1_PIN_CTRL_DRV_RCV

		#define DDRxRS485_CTRLDRVRCV0			(DDRG)
		#define PORTxRS485_CTRLDRVRCV0			(PORTG)
		#define PINxRS485_CTRLDRVRCV0			(PING)
		#define RS485_pinCTRLDRVRCV0			(3)		//PG3
		
		#define RS485_CTRLDRVRCV0_HIGH()		do{PinTo1(PORTxRS485_CTRLDRVRCV0,RS485_pinCTRLDRVRCV0);}while(0)
		#define RS485_CTRLDRVRCV0_LOW()			do{PinTo0(PORTxRS485_CTRLDRVRCV0,RS485_pinCTRLDRVRCV0);}while(0)
		
		#define RS485_DRVEn_RCVDis()			RS485_CTRLDRVRCV0_HIGH()
		#define RS485_RCVEn_DRVDis()			RS485_CTRLDRVRCV0_LOW()

	#endif
	
	/***********************************************************************************

	***********************************************************************************/
	void InitRS845_0(void);



#endif /* RS485_H_ */
