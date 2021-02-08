 #include "Includes/InitializeAllModules.h"
 #ifdef _I2C_

	//Buffer I2C - general purpose
	volatile byte I2Ccfx_UserBuff[I2Ccfx_MAX_ELEM_USERBUFF];
	
	//
	static void _I2Ccfx_InitSeqReading_(byte SLAVE_ADDRESS, byte START_ADDRESS);
    /********************************************************************************
    MEMORY ADDRESS: 1 byte
    DATA: 1 byte
	********************************************************************************/
    void I2Ccfx_Write1Byte(byte SLAVE_ADDRESS, byte START_ADDRESS, byte DATA)
    {
        Start_I2C_unimaster();
		TxAddressSlave_I2C_unimaster((SLAVE_ADDRESS & 0xFE)| WRITE_I2C_MASTER);
		TxData_I2C_unimaster(START_ADDRESS);
		TxData_I2C_unimaster(DATA);
		Stop_I2C_unimaster();
    }
    /********************************************************************************
    MEMORY ADDRESS: 1 byte
    DATA: Array [max 256 elementos]
	********************************************************************************/
    void I2Ccfx_WriteArray(byte SLAVE_ADDRESS, byte START_ADDRESS, volatile byte *pDATA, byte NUMBYTES_TOWRITE)
    {
        Start_I2C_unimaster();
		TxAddressSlave_I2C_unimaster((SLAVE_ADDRESS & 0xFE)| WRITE_I2C_MASTER);
		TxData_I2C_unimaster(START_ADDRESS);
		for (volatile byte i=0; i<NUMBYTES_TOWRITE; i++)
            {TxData_I2C_unimaster(pDATA[i]);}
		Stop_I2C_unimaster();
    }

    ////////////////////////////// LECTURA ////////////////////////////
	static void _I2Ccfx_InitSeqReading_(byte SLAVE_ADDRESS, byte START_ADDRESS)
	{
		Start_I2C_unimaster();
		TxAddressSlave_I2C_unimaster(SLAVE_ADDRESS | WRITE_I2C_MASTER);
		TxData_I2C_unimaster(START_ADDRESS);	//Direccion interna
		Restart_I2C_unimaster();
		TxAddressSlave_I2C_unimaster(SLAVE_ADDRESS | READ_I2C_MASTER);
	}

    void I2Ccfx_ReadRegistersAtAddress(byte SLAVE_ADDRESS, byte START_ADDRESS, volatile byte * pDATA, byte NUMBYTES_TOREAD)
    {
			byte Count_NumBytesRead=0;

			_I2Ccfx_InitSeqReading_((SLAVE_ADDRESS & 0xFE), START_ADDRESS);

			do{
				Count_NumBytesRead++;

				//Dejar preparado el ACK/NACK para el Ste. evento
				if (Count_NumBytesRead < NUMBYTES_TOREAD)
					{RxData_I2C_unimaster(_ACK_);}
				else
					{RxData_I2C_unimaster(_NACK_);}//Finalizar recepción

				//*pDATA = _TWDR;	//RxData_I2C_unimaster	actualiza variable global _TWDR
				*pDATA = TWDR;
				pDATA++;
			}while (Count_NumBytesRead < NUMBYTES_TOREAD);

		Stop_I2C_unimaster();
    }
#endif
