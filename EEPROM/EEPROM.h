#ifndef _EEPROM_H_
#define _EEPROM_H_
	
	//_direccion_directa_ = EEPROM_ReadByte( (const void *)0x00 );
	
	void EEPROM_WriteByte(void * pADDRESS, byte DATA);
	void EEPROM_WriteWord(void * pADDRESS, word WORD);
	byte EEPROM_ReadByte(const void * pADDRESS);
	word EEPROM_ReadWord(const void * pADDRESS);
	
#endif

/*
Someone beat you to it. Sadly the online copy of the avr-libc manual does not seem to reflect this but the eeprom.h in WinAVR20100110 now has: 
Code:
===========================================================================
    - In addition to the write functions there is a set of update ones. 
    This functions read each byte first and skip the burning if the 
    old value is the same with new.  The scaning direction is from 
    high address to low, to obtain quick return in common cases.

and: 
Code:
*/

/** \ingroup avr_eeprom 
    Update a byte \a __value to EEPROM address \a __p. 
 */ 
//void eeprom_update_byte (uint8_t *__p, uint8_t __value); 

/** \ingroup avr_eeprom 
    Update a word \a __value to EEPROM address \a __p. 
 */ 
//void eeprom_update_word (uint16_t *__p, uint16_t __value); 

/** \ingroup avr_eeprom 
    Update a 32-bit double word \a __value to EEPROM address \a __p. 
 */ 
//void eeprom_update_dword (uint32_t *__p, uint32_t __value); 

/** \ingroup avr_eeprom 
    Update a float \a __value to EEPROM address \a __p. 
 */ 
//void eeprom_update_float (float *__p, float __value); 

/** \ingroup avr_eeprom 
    Update a block of \a __n bytes to EEPROM address \a __dst from \a __src. 
    \note The argument order is mismatch with common functions like strcpy(). 
 */ 
//void eeprom_update_block (const //void *__src, //void *__dst, size_t __n);

