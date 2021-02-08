/*******************************************************************************************
GCC supports the following datatypes:

Quote:
(signed/unsigned) char - 1 byte
(signed/unsigned) short - 2 bytes
(signed/unsigned) int - 2 bytes
(signed/unsigned) long - 4 bytes
(signed/unsigned) long long - 8 bytes
float - 4 bytes (floating point)
double - alias to float


I suggest you get used to the alternate datatypes outlined in the C99 standard, and made avaliable to GCC. These use the convention of a "u" to denote the signedness (no "u" to denote signed), "int" to denote that it's a integer and not a float, the number of bits in the int and a trailing "_t". Examples:

Code:
int8_t - Signed Char
uint16_t - Unsigned Int
uint32_t - Unsigned Long
int64_t - Signed Long Long


 typedef signed char int8_t
 typedef unsigned char uint8_t
 typedef signed int int16_t
 typedef unsigned int uint16_t
 typedef signed long int int32_t
 typedef unsigned long int uint32_t
 typedef signed long long int int64_t
 typedef unsigned long long int uint64_t


iar:
Data type Size Range Alignment
bool 8 bits 0 to 1 1
char 8 bits 0 to 255 1
signed char 8 bits -128 to 127 1
unsigned char 8 bits 0 to 255 1
signed short 16 bits -32768 to 32767 1
unsigned short 16 bits 0 to 65535 1
signed int 16 bits -32768 to 32767 1
unsigned int 16 bits 0 to 65535 1
signed long 32 bits -231
 to 231
-1 1
unsigned long 32 bits 0 to 232
-1 1
signed long long 64 bits -263 to 263-1 1
unsigned long long 64 bits 0 to 264
-1 1
*******************************************************************************************/
#ifndef TypeDefs_H
#define TypeDefs_H

	//typedef unsigned char byte;
	//typedef unsigned int  word;
	typedef uint8_t byte;
	typedef uint16_t word;
	typedef byte BOOL;
		
	typedef byte (*PTRFXrBYTE)();
	typedef signed char (*PTRFXrSCHAR)();
	typedef void (*PTRFXrVOID)();
	typedef BOOL (*PTRFXrBOOL)();
    //
    #if defined __ICCAVR__
    typedef unsigned long uint32_t;
    #endif

	
/*
#define BUILD_BUG_ON(condition) ((void)sizeof(char[1 - 2*!!(condition)]))
With that bit of black magic, you can then put this in your code:

{
	// check that you didn't screw up mystruct 
	BUILD_BUG_ON(sizeof(struct mystruct) % 8));
}
*/

#endif
