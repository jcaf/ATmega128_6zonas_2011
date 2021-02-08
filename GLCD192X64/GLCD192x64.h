/************************************************************************
								KS0108 (SEGMENT DRIVER)

Memoria Interna
---------------

Dot matrix lcd segment driver with 64 channel output
display data is stored in display data RAM from MPU

Capacidad interna: 512 bytes -> 4096 bits
Esto es por que en "Y" hay 64 pixel, y en "X" tenemos 8 paginas, cada una de 8 bits de 
altura,,, entonces tenemos:

"Y" = 64 x
"X" = 64
----------
4096 bits o pixels

El correspondiente chip para manejar la parte commun es el KS0107
Clock interno 
---------------------------
2 phase clock signal for internal operation.
Used to execute operations for input/output of display RAM data and others.                                                                     

************************************************************************/
#ifndef GLCD192x64_H_
#define GLCD192x64_H_
	
	/*********************************************************************
	Descomentar si se usa un pin para reset de GLCD
	Más adelente se define el PIN correspondiente
	*********************************************************************/
	#define _USING_GLCD_RST_PIN_
	#define _USING_GLCD_BACKLIGHT_PIN_	
	/*********************************************************************
	Chip Select activo en Bajo o Alto ?
	
	Default: _ACTIVE_LOW_
	*********************************************************************/
	#define _ACTIVE_LOW_ (0)
	#define _ACTIVE_HIGH_ (1)
	
	#define _GLCD192X64_CHIP_SELECT_ _ACTIVE_LOW_	
	//#define _GLCD192X64_CHIP_SELECT_ _ACTIVE_HIGH_
	
	/*********************************************************************
	
	*********************************************************************/
	#define PORTxGLCD192X64_DB0		(PORTC)
	#define PINxGLCD192X64_DB0		(PINC)
	#define DDRxGLCD192X64_DB0		(DDRC)
	//
	#define PORTxGLCD192X64_DB1		(PORTC)
	#define PINxGLCD192X64_DB1		(PINC)
	#define DDRxGLCD192X64_DB1		(DDRC)
	//
	
	#define PORTxGLCD192X64_DB2		(PORTC)
	#define PINxGLCD192X64_DB2		(PINC)
	#define DDRxGLCD192X64_DB2		(DDRC)
	//
	#define PORTxGLCD192X64_DB3		(PORTC)
	#define PINxGLCD192X64_DB3		(PINC)
	#define DDRxGLCD192X64_DB3		(DDRC)
	//
	#define PORTxGLCD192X64_DB4		(PORTC)
	#define PINxGLCD192X64_DB4		(PINC)
	#define DDRxGLCD192X64_DB4		(DDRC)
	//
	#define PORTxGLCD192X64_DB5		(PORTC)
	#define PINxGLCD192X64_DB5		(PINC)
	#define DDRxGLCD192X64_DB5		(DDRC)
	//
	#define PORTxGLCD192X64_DB6		(PORTC)
	#define PINxGLCD192X64_DB6		(PINC)
	#define DDRxGLCD192X64_DB6		(DDRC)
	//
	#define PORTxGLCD192X64_DB7		(PORTC)
	#define PINxGLCD192X64_DB7		(PINC)
	#define DDRxGLCD192X64_DB7		(DDRC)
	//
	#define PORTxGLCD192X64_RS		(PORTD)
	#define PINxGLCD192X64_RS		(PIND)
	#define DDRxGLCD192X64_RS		(DDRD)
	//
	#define PORTxGLCD192X64_RW		(PORTG)
	#define PINxGLCD192X64_RW		(PING)
	#define DDRxGLCD192X64_RW		(DDRG)
	//
	#define PORTxGLCD192X64_E		(PORTG)
	#define PINxGLCD192X64_E		(PING)
	#define DDRxGLCD192X64_E		(DDRG)
	
	//
	#define PORTxGLCD192X64_CS1		(PORTG)
	#define PINxGLCD192X64_CS1		(PING)
	#define DDRxGLCD192X64_CS1		(DDRG)
	//
	#define PORTxGLCD192X64_CS2		(PORTA)
	#define PINxGLCD192X64_CS2		(PINA)
	#define DDRxGLCD192X64_CS2		(DDRA)
	//
	#define PORTxGLCD192X64_CS3		(PORTA)
	#define PINxGLCD192X64_CS3		(PINA)
	#define DDRxGLCD192X64_CS3		(DDRA)
	//
	#ifdef _USING_GLCD_RST_PIN_
		#define PORTxGLCD192X64_RST		(PORTA)
		#define PINxGLCD192X64_RST		(PINA)
		#define DDRxGLCD192X64_RST		(DDRA)
	#endif
	
	#ifdef _USING_GLCD_BACKLIGHT_PIN_	
		#define PORTxGLCD192X64_BKLIGHT	(PORTA)
		#define PINxGLCD192X64_BKLIGHT	(PINA)
		#define DDRxGLCD192X64_BKLIGHT	(DDRA)
	#endif
	
	/*********************************************************************
	Definicion de posicion del bit correspondiente	
	*********************************************************************/
	#define GLCD192X64_DB0		(0)
	#define GLCD192X64_DB1		(1)
	#define GLCD192X64_DB2		(2)
	#define GLCD192X64_DB3		(3)
	#define GLCD192X64_DB4		(4)
	#define GLCD192X64_DB5		(5)
	#define GLCD192X64_DB6		(6)
	#define GLCD192X64_DB7		(7)
	//
	#define GLCD192X64_RS		(7)	//PD7
	#define GLCD192X64_RW		(0)	//PG0
	#define GLCD192X64_E		(1)	//PG1
	//
	#define GLCD192X64_CS1		(2)	//PG2
	#define GLCD192X64_CS2		(6)	//PA6
	#define GLCD192X64_CS3		(5)	//PA5
	//
	#ifdef _USING_GLCD_RST_PIN_
		#define GLCD192X64_RST		(7)	//PA7
	#endif
	
	#ifdef _USING_GLCD_BACKLIGHT_PIN_
		#define GLCD192X64_BKLIGHT	(4)	//PA4
	#endif
	
	/************************************************************************
	KS0108
	Modo escritura- data is latched at the falling edge of E -  BAJO
	Read mode - appears the reading data while E is at high level	- ALTO
	************************************************************************/
	//Reset time tRS = 1.0 us
	#define tRS()	do{_delay_us(1);}while(0)
	
	//E High Level Width Min 450 nS
	#define tWH()	do{_delay_us(1);}while(0)
	
	//E Low Level Width Min 450 nS
	#define tWL()	do{_delay_us(1);}while(0)
	
	//E Rise Time Max 25ns
	//#define tR()	do{}while(0)
	//E Rise Time Max 25ns
	//#define tF()	do{}while(0)

	//Address Set-Up Time Min 140 ns
	#define tASU()	do{_delay_us(1);}while(0)
	//Address Hold Time Min 10 ns
	#define tAH()	do{_delay_us(1);}while(0)
	//Data Set-up Time Min 200 ns
	#define tSU()	do{_delay_us(1);}while(0)
	//Data Delay Time Max 320 ns
	#define tD()	do{_delay_us(1);}while(0)
	//Data Hold Time (Write) Min 10ns = tAH = 10ns
	#define tDHW()	do{_delay_us(1);}while(0)
	//Data Hold Time (Read) Min 20ns
	#define tDHR()	do{_delay_us(1);}while(0)
	
	/************************************************************************

	************************************************************************/
	#define PinGLCD192X64_E_To1()	do{tASU(); PinTo1(PORTxGLCD192X64_E,GLCD192X64_E);}while(0)
	#define PinGLCD192X64_E_To0()	do{PinTo0(PORTxGLCD192X64_E,GLCD192X64_E); tAH();}while(0)

	/************************************************************************
	RS = H Data data                                               
	RS = L Instruccion data                                        
	************************************************************************/
	#define PinGLCD192X64_RS_To1() do{PinTo1(PORTxGLCD192X64_RS,GLCD192X64_RS);}while(0)
	#define PinGLCD192X64_RS_To0() do{PinTo0(PORTxGLCD192X64_RS,GLCD192X64_RS);}while(0)
	
	#define GLCD192X64_RS_DATA()	PinGLCD192X64_RS_To1()
	#define GLCD192X64_RS_CMD()		PinGLCD192X64_RS_To0()

	/************************************************************************
	Write:	Display data DB<0:7> can be written at  falling of E
	Read:	Data appears at DB<0:7> and can be read by the CPU while E=H                                              
	************************************************************************/
	#define PinGLCD192X64_RW_To1() do{PinTo1(PORTxGLCD192X64_RW,GLCD192X64_RW);}while(0)
	#define PinGLCD192X64_RW_To0() do{PinTo0(PORTxGLCD192X64_RW,GLCD192X64_RW);}while(0)
	
	#define GLCD192X64_RW_WRITE()	PinGLCD192X64_RW_To0()
	#define GLCD192X64_RW_READ()	PinGLCD192X64_RW_To1()
	
	/************************************************************************
	Chip select	
	************************************************************************/
	#define PinGLCD192X64_CS1_To1() do{PinTo1(PORTxGLCD192X64_CS1,GLCD192X64_CS1);}while(0)
	#define PinGLCD192X64_CS1_To0() do{PinTo0(PORTxGLCD192X64_CS1,GLCD192X64_CS1);}while(0)

	#define PinGLCD192X64_CS2_To1() do{PinTo1(PORTxGLCD192X64_CS2,GLCD192X64_CS2);}while(0)
	#define PinGLCD192X64_CS2_To0() do{PinTo0(PORTxGLCD192X64_CS2,GLCD192X64_CS2);}while(0)

	#define PinGLCD192X64_CS3_To1() do{PinTo1(PORTxGLCD192X64_CS3,GLCD192X64_CS3);}while(0)
	#define PinGLCD192X64_CS3_To0() do{PinTo0(PORTxGLCD192X64_CS3,GLCD192X64_CS3);}while(0)
		
	#if _GLCD192X64_CHIP_SELECT_ == _ACTIVE_LOW_
		
		#define GLCD192X64_CHIP1_ON()	PinGLCD192X64_CS1_To0()
		#define GLCD192X64_CHIP1_OFF()	PinGLCD192X64_CS1_To1()
		
		#define GLCD192X64_CHIP2_ON()	PinGLCD192X64_CS2_To0()
		#define GLCD192X64_CHIP2_OFF()	PinGLCD192X64_CS2_To1()
		
		#define GLCD192X64_CHIP3_ON()	PinGLCD192X64_CS3_To0()
		#define GLCD192X64_CHIP3_OFF()	PinGLCD192X64_CS3_To1()
	#else
	
		#define GLCD192X64_CHIP1_ON()	PinGLCD192X64_CS1_To1()
		#define GLCD192X64_CHIP1_OFF()	PinGLCD192X64_CS1_To0()
		
		#define GLCD192X64_CHIP2_ON()	PinGLCD192X64_CS2_To1()
		#define GLCD192X64_CHIP2_OFF()	PinGLCD192X64_CS2_To0()
		
		#define GLCD192X64_CHIP3_ON()	PinGLCD192X64_CS3_To1()
		#define GLCD192X64_CHIP3_OFF()	PinGLCD192X64_CS3_To0()
	
	#endif
	
	#define GLCD192X64_CHIP1_2_3_ALL_ON()	do{GLCD192X64_CHIP1_ON();GLCD192X64_CHIP2_ON();GLCD192X64_CHIP3_ON();}while(0)
	#define GLCD192X64_CHIP1_2_3_ALL_OFF()	do{GLCD192X64_CHIP1_OFF();GLCD192X64_CHIP2_OFF();GLCD192X64_CHIP3_OFF();}while(0)


//ESTAS SON LAS UNICAS MACROS QUE USO PARA ks108.c
//+++++++++++	
//Friday July 13th, 2012: Bug fixed.
//Add control of GLCD backlight, NOW IS NECESARY ATOMIzar all fx 
	#define GLCD192X64_ONLY_CHIP1_ON()	do{	SAVE_SREG_CLI(); GLCD192X64_CHIP1_ON(); \
											GLCD192X64_CHIP2_OFF();GLCD192X64_CHIP3_OFF();RESTORE_SREG();}while(0)
	
	#define GLCD192X64_ONLY_CHIP2_ON()	do{	SAVE_SREG_CLI(); GLCD192X64_CHIP1_OFF();\
											GLCD192X64_CHIP2_ON();GLCD192X64_CHIP3_OFF();RESTORE_SREG();}while(0)
	
	#define GLCD192X64_ONLY_CHIP3_ON()	do{	SAVE_SREG_CLI(); GLCD192X64_CHIP1_OFF();\
												GLCD192X64_CHIP2_OFF();GLCD192X64_CHIP3_ON();RESTORE_SREG();}while(0)

//+++++++++++

	/************************************************************************
	Reset signal - bajo
	(1) ON/OFF register becomes set by 0 (display off)
	(2) Display start line register becomes set by 0
		(Z-address 0 set, display from line 0)
		After releasing reset, this condition can be changed only by instruction
	
	Reset can be initialized system by setting RSTB terminal at low level when turning power on,
	receiving instruction from MPU
	When RSTB becomes low, following procedure is ocurred:
	
	1. Display Off
	2. Display start line register become set by 0. (Z-addres 0)
	
	While RSTB is low, any instruction except status read can be accepted. reset status appears at DB4. After DB4 is low
	any instruction can be accepted.
	The Condition of power supply at initial power up are:
	
	Reset time tRS = 1.0 us
	Rise Time tR= Maxi 200ns

	************************************************************************/
	#ifdef	_USING_GLCD_RST_PIN_
		#define PinGLCD192X64_RST_To1() do{PinTo1(PORTxGLCD192X64_RST,GLCD192X64_RST);}while(0)
		#define PinGLCD192X64_RST_To0() do{PinTo0(PORTxGLCD192X64_RST,GLCD192X64_RST);}while(0)
	
		#define GLCD192X64_RSTB_HOLDING()	PinGLCD192X64_RST_To0()
		#define GLCD192X64_RSTB_RELEASE()	PinGLCD192X64_RST_To1()
	#endif
	/*********************************************************************
		BackLight control
	*********************************************************************/
	#ifdef _USING_GLCD_BACKLIGHT_PIN_	
		#define GLCD192X64_BKLIGHT_ON()		do{PinTo0(PORTxGLCD192X64_BKLIGHT,GLCD192X64_BKLIGHT);}while(0)
		#define GLCD192X64_BKLIGHT_OFF()	do{PinTo1(PORTxGLCD192X64_BKLIGHT,GLCD192X64_BKLIGHT);}while(0)
	#endif

	/***************************************************************************************
	
	***************************************************************************************/
	#define GLCD192X64_SIZEX_CHIP1 (64)
	#define GLCD192X64_SIZEY_CHIP1 (64)
	
	#define GLCD192X64_SIZEX_CHIP2 (64)
	#define GLCD192X64_SIZEY_CHIP2 (64)
	
	#define GLCD192X64_SIZEX_CHIP3 (64)
	#define GLCD192X64_SIZEY_CHIP3 (64)
	/***************************************************************************************
	
	***************************************************************************************/
	#define xiCHIP1	(0)										//x initial
	#define yiCHIP1	(0)										//y initial
	#define xfCHIP1	(xiCHIP1 + (GLCD192X64_SIZEX_CHIP1-1))	//x final
	#define yfCHIP1	(yiCHIP1 + (GLCD192X64_SIZEY_CHIP1-1))	//y final
	
	#define xiCHIP2	(64)									//x initial
	#define yiCHIP2	(0)										//y initial
	#define xfCHIP2	(xiCHIP2 + (GLCD192X64_SIZEX_CHIP2-1))	//x final
	#define yfCHIP2	(yiCHIP2 + (GLCD192X64_SIZEY_CHIP2-1))	//y final
	
	#define xiCHIP3	(128)									//x initial
	#define yiCHIP3	(0)										//y initial
	#define xfCHIP3	(xiCHIP3 + (GLCD192X64_SIZEX_CHIP3-1))	//x final
	#define yfCHIP3	(yiCHIP3 + (GLCD192X64_SIZEY_CHIP3-1))	//y final

	
	/*********************************************************************
		Declaraciones	
	*********************************************************************/
	void InitGLCD192x64(void);
	void StrobeEnableGLCD192x64(void);
	
	
	//////////////////////////////////////////////////////////////////////
	//x,y about of dimensions of display
	//
	#define GLCD192X64_DIM_X (192)
	#define GLCD192X64_DIM_Y (64)
			
	#if GLCD192X64_DIM_X > 256 //0..255
		typedef word TYPE_XYDISP_X;
	#else
		typedef byte TYPE_XYDISP_X;
	#endif
		
	#if GLCD192X64_DIM_Y > 256 //0..255
		typedef word TYPE_XYDISP_Y;
	#else
		typedef byte TYPE_XYDISP_Y;
	#endif
	
	typedef struct _xy_display
	{
		TYPE_XYDISP_X x;
		TYPE_XYDISP_Y y;
	}xy_display;
	
#endif
