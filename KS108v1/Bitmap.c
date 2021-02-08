//************************************************************************
// Bitmap.C
//************************************************************************
#include <avr/pgmspace.h>
#include "Bitmap.h"
#include "ks0108.h"
//##########################################################
/*
void LoadBitmap(unsigned char *bitmap)
{
uint16_t i, j,by;
for(i=0; i<64; i+=8)

		for(j=0; j<128; j++)
		{
			by=pgm_read_byte(bitmap++);
			ks0108GotoXY(j, i);
			ks0108WriteData(by);
		}

}
*/ //comentado por ahora,,, viendo en cuanto reduce el codigo 41.8% con bitmap