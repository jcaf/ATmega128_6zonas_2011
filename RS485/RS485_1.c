/*
 * RS485_1.c
 *
 * Created: 15/02/2012 10:51:38 a.m.
 *  Author: jcaf
 */ 
	#include "Includes/InitializeAllModules.h"
	/*******************************************************************************
	
	*******************************************************************************/
	void InitRS845_0(void)
	{
		ConfigOutputPin(DDRxRS485_CTRLDRVRCV0,RS485_pinCTRLDRVRCV0);
		RS485_DRVEn_RCVDis();
	}

//OK: comunicacion perfecta
//while (1)
//{
	//_delay_ms(1000);
	//TxByteNoWaitTXC_USART0('K');
//}