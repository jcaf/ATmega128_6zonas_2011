/***************************************************************************************
			O J O:
fuse EESAVE debe ser programado para preservar EEPROM durante ciclo de borrando antes de programar la flash

***************************************************************************************/
	/***************************************************************************************************
	CPU Clock – clkCPU
	The CPU clock is routed to parts of the system concerned with operation of the AVR core.
	Examples of such modules are the General Purpose Register File, the Status Register and the
	data memory holding the Stack Pointer. Halting the CPU clock inhibits the core from performing
	general operations and calculations.
	
	I/O Clock – clkI/O
	The I/O clock is used by the majority of the I/O modules, like Timer/Counters, SPI, and USART.
	The I/O clock is also used by the External Interrupt module, but note that some external inter-
	rupts are detected by asynchronous logic, allowing such interrupts to be detected even if the I/O
	clock is halted. Also note that address recognition in the TWI module is carried out asynchro-
	nously when clk	I/O	 is halted, enabling TWI address reception in all sleep modes.
	
	***************************************************************************************************/

#include "Includes/InitializeAllModules.h"

	/***********************************************************************************************	
	_direccion_directa_ = EEPROM_ReadByte( (const void *)0x00 );
	
	***********************************************************************************************/
	void EEPROM_WriteByte(void * pADDRESS, byte DATA)
	{
		volatile byte temp;
		while (EECR & (1<<EEWE)) {;}	//Esperar por EEWE=0The EEPROM Ready interrupt generates a constant inter-rupt when EEW E is cleared.
		//while (SPMCSR & (1<<SPMEN)) {;}	//
		EEAR = (word) pADDRESS;
		EEDR = DATA;
		//
		temp = SREG;
		cli();
		BitTo1(EECR,EEMWE);
		BitTo1(EECR,EEWE);
		SREG= temp;
	}
	/***********************************************************************************************	
	
	***********************************************************************************************/
	void EEPROM_WriteWord(void * pADDRESS, word WORD)
	{
		EEPROM_WriteByte(pADDRESS, (byte)WORD);			//parte baja
		pADDRESS = (byte*)pADDRESS +1;					//avanza 1 posicion
		EEPROM_WriteByte(pADDRESS, (byte)(WORD>>8));	//parte alta
		
	}
	/***********************************************************************************************	
	
	***********************************************************************************************/
	byte EEPROM_ReadByte(const void * pADDRESS)
	{
		while (EECR & (1<<EEWE)) {;}	//Esperar por EEWE=0The EEPROM Ready interrupt generates a constant inter-rupt when EEW E is cleared.
		//
		EEAR = (word)pADDRESS;	//fix
		BitTo1(EECR,EERE);
		return EEDR;
	}
	/***********************************************************************************************	
	
	***********************************************************************************************/
	word EEPROM_ReadWord(const void * pADDRESS)
	{
		volatile byte temp;
		temp = EEPROM_ReadByte(pADDRESS);					//parte baja
		pADDRESS = (byte *)pADDRESS +1;						//avanza 1 posicion
		return ( EEPROM_ReadByte(pADDRESS) <<8 ) | temp;	//parte alta + baja
	}

	/***************************************************
	 It is recommended to have the global interrupt flag cleared
	during the four last steps to avoid these problems.
	When the write access time has elapsed, the EEWE bit is cleared by hardware.
	The user soft-ware can poll this bit and wait for a zero before writing the next byte. When EEWE has been set,
	the CPU is halted for two cycles before the next instruction is executed

	8.5ms@1MHZ internal calibrated
	***************************************************/
	/*
	void Write_EEPROM(word ADDRESS, byte DATA)
	{
		volatile byte temp;
		while (EECR & (1<<EEWE)) {;}	//Esperar por EEWE=0The EEPROM Ready interrupt generates a constant inter-rupt when EEW E is cleared.
		//while (SPMCSR & (1<<SPMEN)) {;}	//
		EEAR = ADDRESS;
		EEDR = DATA;
		//
		temp = SREG;
		cli();
		BitTo1(EECR,EEMWE);
		BitTo1(EECR,EEWE);
		SREG= temp;
	}
	*/
	/*************************************************
	The EEPROM Read Enable Signal EERE is the read strobe to the EEPROM. W hen the correct
	address is set up in the EEAR Register, the EERE bit must be written to a logic one to trigger the
	EEPROM read. The EEPROM read access takes one instruction, and the requested data is
	available immediately. W hen the EEPROM is read, the CPU is halted for four cycles before the
	next instruction is executed.
	The user should poll the EEWE bit before starting the read operation. If a write operation is in
	progress, it is neither possible to read the EEPROM, nor to change the EEAR Register.

	The calibrated Oscillator is used to time the EEPROM accesses.
	Table 2 lists the typical pro-gramming time for EEPROM access from the CPU
	**************************************************/
	/*
	byte Read_EEPROM(word ADDRESS)
	{
		while (EECR & (1<<EEWE)) {;}	//Esperar por EEWE=0The EEPROM Ready interrupt generates a constant inter-rupt when EEW E is cleared.
		//
		EEAR = ADDRESS;
		BitTo1(EECR,EERE);
		return EEDR;
	}
	*/
