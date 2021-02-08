/**********************************************************************
#include <avr/pgmspace.h>
if (BufferInROMorRAM == ROM)
{
    Status = PutNewDataAtAddressSpace( pgm_read_byte( pBufferData) );
}

I2C_01.c		Solo contiene funciones hardware de AVRs.
I2CCommonFx.c	Contiene funciones comunes de lectura y escritura para 
				muchos dispositivos I2C
***********************************************************************/
//#include "I2C\I2C.h"
#include "Includes/InitializeAllModules.h"
#ifdef _I2C_
    
	//volatile byte _TWDR;
   
    /********************************************************************
    I2C modo MASTER (1 MASTER ON THE I2C BUS)

    ********************************************************************/
    void Init_I2C_unimaster(void)
    {
		//pull-up  off
		PinTo0(PORTWxHW0_SCL_I2C,PIN_HW0_SCL_I2C);
		PinTo0(PORTWxHW0_SDA_I2C,PIN_HW0_SDA_I2C);
	    //
		TWSR = 0x00;						//TWPS1=PWPS0=0->Preescaler "1"
        TWBR = BIT_RATE_G_KTE(100*KHz);		
    }
	
    /********************************************************************************
    //Despues de enviar Start-> TWSTA debe ser borrado por software al cargar TWCR/TWDR
    ********************************************************************************/
    BOOL Start_I2C_unimaster(void)
    {
        TWCR = ( 1<<TWINT ) | ( 1<<TWSTA) | (1<<TWEN);
        while ( ! (TWCR & (1<<TWINT)) )	{;}//Esperar POR TWINT =1 x HARDWARE
		
        if ( (TWSR & 0xF8) != I2C_STATUS_START_SUCCESS)  
		{
			ParsingError_I2C_unimaster(TWSR & 0xF8);
			return	FALSE;
		}

        return TRUE;
    }
    /********************************************************************************
    //Despues de enviar Restart-> TWSTA debe ser borrado por software al cargar TWCR/TWDR
    ********************************************************************************/
    BOOL Restart_I2C_unimaster(void)
    {
		TWCR = ( 1<<TWINT ) | ( 1<<TWSTA) | (1<<TWEN);
        while ( ! (TWCR & (1<<TWINT)) )		{;}     //Esperar POR TWINT =1 x HARDWARE
		
		if ( (TWSR  & 0xF8) != I2C_STATUS_REPEAT_SUCCESS)
		{
			ParsingError_I2C_unimaster(TWSR  & 0xF8);
			return	FALSE; 
		}
        return TRUE;
    }
    /********************************************************************************
        //Note that TWINT is NOT set after a STOP condition has been sent.
        //Solo Esperar por TWSTO q sea borrado automaticamente por el hardware

    ********************************************************************************/
    void Stop_I2C_unimaster(void)
    {
        TWCR = ( 1<<TWINT ) | ( 1<<TWSTO) | ( 1<<TWEN );
        while ( TWCR & (1<<TWSTO) )	{;}
    }
    /********************************************************************************

    ********************************************************************************/
    void __TxByte_I2C_unimaster(byte _Byte_)
    {
        TWDR = _Byte_;
        TWCR = ( 1<<TWINT ) | (1<<TWEN);    //x data, despues de un direccionamiento correcto
        //TWCR = ( 1<<TWINT ) | ( 0<<TWSTA) | (1<<TWEN);    //x address, despues de START condition
        while ( !(TWCR & (1<<TWINT)) )	{;}	//Transmisión en progreso
    }
    /********************************************************************************
    ********************************************************************************/
    BOOL TxData_I2C_unimaster(byte Data)
    {
        __TxByte_I2C_unimaster(Data);

        if ( (TWSR & 0xF8) != I2C_STATUS_DATA_TX_SUCCESS_ACK_SUCCESS) 
		{
			ParsingError_I2C_unimaster(TWSR & 0xF8);
			return FALSE;
		}
        return TRUE;
    }
    /********************************************************************************
    ********************************************************************************/
    BOOL TxAddressSlave_I2C_unimaster(byte SlaveAddress_RW)
    {
        byte I2C_STATUS_CODE_R_W;
	    //Inicializar KTE para comparación de ERROR
        if ( (SlaveAddress_RW & 0x01 )== READ_I2C_MASTER )
        {
            I2C_STATUS_CODE_R_W = I2C_STATUS_SLA_R_SUCCESS_ACK_SUCCESS;//CODIGO DE STATUS PARA LA LECTURA...
        }
        else
        {
            I2C_STATUS_CODE_R_W = I2C_STATUS_SLA_W_SUCCESS_ACK_SUCCESS ;//CODIGO DE STATUS PARA LA ESCRITURA...
        }
	    __TxByte_I2C_unimaster(SlaveAddress_RW);
		
        if ( (TWSR & 0xF8) != I2C_STATUS_CODE_R_W) 
		{
			ParsingError_I2C_unimaster(TWSR & 0xF8);
			return FALSE;
		}
        return TRUE;
    }

    /****************************************************************
    #define _NACK_ (0)
    #define _ACK_ (1)

    output: _TWDR update si Status=TRUE
    ****************************************************************/
    BOOL RxData_I2C_unimaster(byte PrepararACK_NACK)
    {
        byte I2C_StatusCode_R_ACK_NACK;

        if (PrepararACK_NACK)
        {
            I2C_StatusCode_R_ACK_NACK = I2C_STATUS_DATA_RX_SUCCESS_ACK_SUCCESS;//Inicializar codigo de respuesta
            TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN) ;	//HEMOS RECIBIDO EL DATO Y HEMOS GENERADO UN "ACK PARA PROSEGUIR CON LA RECEPCION
        }
        else//Finalizar recepción
        {   
            I2C_StatusCode_R_ACK_NACK = I2C_STATUS_DATA_RX_SUCCESS_ACK_UNSUCCESS;//Inicializar codigo de respuesta para
            TWCR = (1<<TWINT) | (0<<TWEA) | (1<<TWEN) ;	////HEMOS RECIBIDO EL DATO Y HEMOS GENERADO UN "NACK PARA FINALIZAR LA RECEPCION
        }
        while ( ! (TWCR & (1<<TWINT)) ) {;}	//Esperamos por dato desde esclavo. Si TWINT=1->Se lleno TWDR

	    if	( (TWSR & 0xF8) != I2C_StatusCode_R_ACK_NACK )
        {
			ParsingError_I2C_unimaster(TWSR & 0xF8);
            return FALSE;
        }
         //_TWDR = TWDR;	//TWDR debe mantener la data recibida de manera integral, pues, si no hubo ningun caos en el bus,
							//el host no finaliza bruscamente con STOP.
        return TRUE;
    }
    /********************************************************************************

    ********************************************************************************/
	void ParsingError_I2C_unimaster(byte _TWSR_ERROR_CODE_)
	{
		Stop_I2C_unimaster();
		
		switch (_TWSR_ERROR_CODE_)
		{
			
			//I2C STATUS CODES x MASTER TRANSMITTER
			case  I2C_STATUS_SLA_W_SUCCESS_ACK_UNSUCCESS: 	//(0x20)
				break;
			case  I2C_STATUS_DATA_TX_SUCCESS_ACK_UNSUCCESS: //(0x30)
				break;
			
			//el mismo codigo para ambos W/R
			//case  I2C_STATUS_ARBITRATION_LOST_IN_SLA_W: 	//(0x38)
			//I2C STATUS CODES x MASTER RECEIVER
			//case  I2C_STATUS_ARBITRATION_LOST_IN_SLA_R: 	//(0x38)
			case 0x38: //(0x38)
				
				break;
			
			case  I2C_STATUS_SLA_R_SUCCESS_ACK_UNSUCCESS: 	//(0x48)
				break;
			case  I2C_STATUS_DATA_RX_SUCCESS_ACK_UNSUCCESS: //(0x58)
				break;
			
			//otros
			case  I2C_STATUS_NO_RELEVANT_STATE_INFORMATION:	//(0xF8)
				break;
			case  I2C_STATUS_BUS_ERROR_ILLEGAL_START_STOP:	//(0x00)
				break;
		}
	}

#endif


    
