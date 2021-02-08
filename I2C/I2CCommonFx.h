#ifndef I2CCOMMONFX_H_
#define I2CCOMMONFX_H_
	
    void I2Ccfx_Write1Byte(byte SLAVE_ADDRESS, byte START_ADDRESS, byte DATA);
    void I2Ccfx_WriteArray(byte SLAVE_ADDRESS, byte START_ADDRESS, volatile byte *pDATA, byte NUMBYTES_TOWRITE);
    
	void I2Ccfx_ReadRegistersAtAddress(byte SLAVE_ADDRESS, byte START_ADDRESS, volatile byte * pDATA, byte NUMBYTES_TOREAD);

	#define I2Ccfx_MAX_ELEM_USERBUFF (0x0A)
	
	extern volatile byte I2Ccfx_UserBuff[I2Ccfx_MAX_ELEM_USERBUFF];
	
#endif
