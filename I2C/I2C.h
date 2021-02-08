/*************************************************************************************

MODIFICADO DEL ORIGINAL (PIC TRAGAMONEDAS_CHINO) LOS SIGUIENTES ITEMS

1- #define FREQ_I2C  (100000)

2- //BOOL StopCondition(void);
void StopCondition(void);

3-	//#include "I2C\I2C_BB.h"
*************************************************************************************/
#ifndef I2C_H_
#define I2C_H_

    //#include "I2C\I2C_BB.h"   //Aun no Probado bit banging I2C en AVRs.
    /*******************************************************************************

    *******************************************************************************/
    #define PREESCALER_I2C 1
    //#define PREESCALER_I2C  4
    //#define PREESCALER_I2C  16
    //#define PREESCALER_I2C  64	//NO USADO

    #if PREESCALER_I2C == 1
            #define  TWI_PREESCALER_POTENCIA (4)			//4^1
    #elif PREESCALER_I2C == 4
            #define  TWI_PREESCALER_POTENCIA (256)			//4^4
    #elif PREESCALER_I2C == 16
            #define  TWI_PREESCALER_POTENCIA (4294967296)	//4^16
    #endif

	/******
	100Khz @16Mhz/PREESCALER=1  BR = 18
	400Khz @16Mhz/PREESCALER=1  BR =  3

	100Khz @8Mhz/PREESCALER=1  BR = 8
	400Khz @8Mhz/PREESCALER=1  BR = 0.5
	
	Siempre TWSR<PREESCALER> = 00 osea Preescaler 1

	*******/
    #ifndef FREQ_SYSTEM
        #error "I2C: FREQ_SYSTEM NO DEFINIDO"
    #else
		//#define FREQ_I2C  (100000)	//100KHz
        //#define BIT_RATE_G_KTE (  (byte)( (FREQ_SYSTEM-(16*FREQ_I2C) )/(2*FREQ_I2C*TWI_PREESCALER_POTENCIA))  )
		#define BIT_RATE_G_KTE(FREQ_I2C) (  (byte)( (FREQ_SYSTEM-(16*FREQ_I2C) )/(2*FREQ_I2C*TWI_PREESCALER_POTENCIA))  )
        
		//#if BIT_RATE_G_KTE <= 1
            //#error "TWI: BIT_RATE_G_KTE menor IGUAL que 1"
        //#endif
		
    #endif
	/*******************************************************************************
				UBICACION DE PINS I2C - HARDWARE 0
	*******************************************************************************/
	#define DDRxHW0_SCL_I2C		    (DDRD)
	#define PORTWxHW0_SCL_I2C		(PORTD)
	#define PORTRxHW0_SCL_I2C		(PIND)
	#define PIN_HW0_SCL_I2C 		(0)
	//
	#define DDRxHW0_SDA_I2C		    (DDRD)
	#define PORTWxHW0_SDA_I2C		(PORTD)
	#define PORTRxHW0_SDA_I2C		(PIND)
	#define PIN_HW0_SDA_I2C 		(1)
	
    /*******************************************************************************
    //				I2C STATUS CODES
    *******************************************************************************/
    #define  I2C_STATUS_START_SUCCESS 					  (0x08)
    #define  I2C_STATUS_REPEAT_SUCCESS 					  (0x10)

    #define  I2C_STATUS_NO_RELEVANT_STATE_INFORMATION	  (0xF8)
    #define  I2C_STATUS_BUS_ERROR_ILLEGAL_START_STOP	  (0x00)

    /*******************************************************************************
    //I2C STATUS CODES x MASTER TRANSMITTER
    *******************************************************************************/
    #define  I2C_STATUS_SLA_W_SUCCESS_ACK_SUCCESS 		  (0x18)
    #define  I2C_STATUS_SLA_W_SUCCESS_ACK_UNSUCCESS 	  (0x20)

    #define  I2C_STATUS_DATA_TX_SUCCESS_ACK_SUCCESS 	  (0x28)
    #define  I2C_STATUS_DATA_TX_SUCCESS_ACK_UNSUCCESS 	  (0x30)

    #define  I2C_STATUS_ARBITRATION_LOST_IN_SLA_W 		  (0x38)

    /*******************************************************************************
    //I2C STATUS CODES x MASTER RECEIVER
    *******************************************************************************/

    #define  I2C_STATUS_ARBITRATION_LOST_IN_SLA_R 		  (0x38)

    #define  I2C_STATUS_SLA_R_SUCCESS_ACK_SUCCESS 		  (0x40)
    #define  I2C_STATUS_SLA_R_SUCCESS_ACK_UNSUCCESS 	  (0x48)

    #define  I2C_STATUS_DATA_RX_SUCCESS_ACK_SUCCESS 	  (0x50)
    #define  I2C_STATUS_DATA_RX_SUCCESS_ACK_UNSUCCESS 	  (0x58)

    /*******************************************************************************
    //Definiciones I2C - ORing
    *******************************************************************************/
    #define  WRITE_I2C_MASTER 		 	(0x00)
    #define  READ_I2C_MASTER 		 	(0x01)
   /****************************************************************
    #define _NACK_ (0)
    #define _ACK_ (1)

    output: _TWDR update si Status=TRUE
    ****************************************************************/
    #define _NACK_ (0)
    #define _ACK_ (1)
	/*******************************************************************************************

    *******************************************************************************************/
	extern volatile byte _TWDR;

    /*******************************************************************************************

    *******************************************************************************************/
	void Init_I2C_unimaster(void);
	BOOL Start_I2C_unimaster(void);
	BOOL Restart_I2C_unimaster(void);
	void Stop_I2C_unimaster(void);
	void __TxByte_I2C_unimaster(byte _Byte_);
	BOOL TxData_I2C_unimaster(byte Data);
	BOOL TxAddressSlave_I2C_unimaster(byte SlaveAddress_RW);
	BOOL RxData_I2C_unimaster(byte PrepararACK_NACK);
	void ParsingError_I2C_unimaster(byte _TWSR_ERROR_CODE_);

#endif
