/*
 * Copyright:      Fabian Maximilian Thiele  mailto:me@apetech.de
 * Author:         Fabian Maximilian Thiele
 * Remarks:        this Copyright must be included
 * known Problems: none
 * Version:        1.1
 * Description:    Graphic Library for KS0108- (and compatible) based LCDs
 * 
 */

#include <inttypes.h>
#include <avr/pgmspace.h>

	#ifndef	KS0108_H
	#define KS0108_H

	// Ports
	//#define LCD_CMD_PORT		PORTC		// Command Output Register
	//#define LCD_CMD_DIR		DDRC		// Data Direction Register for Command Port

	#define LCD_CMD_PORT_RSTB	PORTA
	#define LCD_CMD_DIR_RSTB	DDRA
	//
	#define _RSTB_	PA7

	/*
	CTRL_BACKLIGHT
	CS3
	CS2
	*/
	#define LCD_CMD_PORT_BK_CS3_CS2		PORTA		// Command Output Register
	#define LCD_CMD_DIR_BK_CS3_CS2		DDRA		// Data Direction Register for Command Port

	#define _CTRL_BACKLIGHT_	(PA4)

	/*
	RS = D_I
	*/
	#define LCD_CMD_PORT_D_I	PORTD		// Command Output Register
	#define LCD_CMD_DIR_D_I		DDRD		// Data Direction Register for Command Port

	/*
	RW
	E
	CS1
	*/
	#define LCD_CMD_PORT_RW_E_CS1		PORTG		// Command Output Register
	#define LCD_CMD_DIR_RW_E_CS1		DDRG		// Data Direction Register for Command Port

	#define LCD_DATA_IN			PINC		// Data Input Register
	#define LCD_DATA_OUT		PORTC		// Data Output Register
	#define LCD_DATA_DIR		DDRC		// Data Direction Register for Data Port

	/*
	// Command Port Bits
	#define D_I					0x00		// D/I Bit Number
	#define R_W					0x01		// R/W Bit Number
	#define EN					0x02		// EN Bit Number
	#define CSEL1				0x03		// CS1 Bit Number
	#define CSEL2				0x04		// CS2 Bit Number
	*/

	// Command Port Bits
	#define D_I					PD7		// D/I Bit Number
	//
	#define R_W					PG0 	// R/W Bit Number
	#define EN					PG1 	// EN Bit Number
	#define CSEL1				PG2		// CS1 Bit Number
	//
	#define CSEL2				PA6		// CS2 Bit Number
	//
	#define CSEL3				PA5		// CS2 Bit Number


	// Chips
	#define CHIP1				0x00
	#define CHIP2				0x01
	#define CHIP3				0x02

	// Commands
	#define LCD_ON				0x3F
	#define LCD_OFF				0x3E
	#define LCD_SET_ADD			0x40
	#define LCD_SET_PAGE		0xB8
	#define LCD_DISP_START		0xC0

	// Colors
	#define BLACK				0xFF
	#define WHITE				0x00

	// Font Indices
	#define FONT_LENGTH			0
	#define FONT_FIXED_WIDTH	2
	#define FONT_HEIGHT			3
	#define FONT_FIRST_CHAR		4
	#define FONT_CHAR_COUNT		5
	#define FONT_WIDTH_TABLE	6

	// Uncomment for slow drawing
	// #define DEBUG

	typedef struct {
		uint8_t x;
		uint8_t y;
		uint8_t page;
	} lcdCoord;

	typedef uint8_t (*ks0108FontCallback)(const uint8_t*);

	//
	// Function Prototypes
	//

	// Graphic Functions
	void ks0108DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t color);
	void ks0108DrawRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color);
	void ks0108DrawRoundRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t radius, uint8_t color);
	void ks0108FillRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color);
	void ks0108InvertRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height);
	void ks0108SetInverted(uint8_t invert);
	void ks0108SetDot(uint8_t x, uint8_t y, uint8_t color);

	#define ks0108DrawVertLine(x, y, length, color) {ks0108FillRect(x, y, 0, length, color);}
	#define ks0108DrawHoriLine(x, y, length, color) {ks0108FillRect(x, y, length, 0, color);}
	#define ks0108DrawCircle(xCenter, yCenter, radius, color) {ks0108DrawRoundRect(xCenter-radius, yCenter-radius, 2*radius, 2*radius, radius, color);}
	
	//+++++add
	//#define ks0108ClearScreen() {ks0108FillRect(0, 0, 127, 63, WHITE);}
	//+++++add
	#define ks0108ClearScreen() {ks0108FillRect(0, 0, 191, 63, WHITE);}

	// Font Functions
	uint8_t ks0108ReadFontData(const uint8_t* ptr);		//Standard Read Callback
	//void ks0108SelectFont(const char* font, ks0108FontCallback callback, uint8_t color);
	void ks0108SelectFont(const uint8_t	* font, ks0108FontCallback callback, uint8_t color);
	int ks0108PutChar(char c);
	void ks0108Puts(char* str);
	void ks0108Puts_P(PGM_P str);
	uint8_t ks0108CharWidth(char c);
	uint16_t ks0108StringWidth(char* str);
	uint16_t ks0108StringWidth_P(PGM_P str);

	// Control Functions
	void ks0108GotoXY(uint8_t x, uint8_t y);
	void ks0108Init(uint8_t invert);
	//inline uint8_t ks0108ReadData(void);
	void ks0108WriteCommand(uint8_t cmd, uint8_t chip);
	void ks0108WriteData(uint8_t data);
	//
	int ks0108PutChar(char c);	//sacandolo al exterior
#endif
