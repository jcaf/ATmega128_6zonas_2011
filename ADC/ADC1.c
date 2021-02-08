#include "Includes/InitializeAllModules.h"

/*
 * ADC1.c
 *
 * Created: 4/26/2013 11:50:51 AM
 *  Author: jc
 */ 
/*
The ADC is enabled by setting the ADC Enable bit, ADEN in ADCSRA. Voltage reference and
input channel selections will not go into effect until ADEN is set. The ADC does not consume
power when ADEN is cleared, so it is recommended to switch off the ADC before entering power saving sleep modes.

//--------------------------------------------------


Once the conversion starts, the
channel and reference selection is locked to ensure a sufficient sampling time for the ADC. Con-
tinuous updating resumes in the last ADC clock cycle before the conversion completes (ADIF in
ADCSRA is set). Note that the conversion starts on the following rising ADC clock edge after
ADSC is written. The user is thus advised not to write new channel or reference selection values
to ADMUX until one ADC clock cycle after ADSC is written.
*/

////////////////////////////////////////////////////////////////////////////////////////////////
//reading ADCH:ADCL 16bits
//If the result is left adjusted and no more than 8-bit precision is required, it is sufficient to read
//ADCH. Otherwise, ADCL must be read first, then ADCH, to ensure that the content of the data
//registers belongs to the same conversion. Once ADCL is read, ADC access to data registers is
//blocked. This means that if ADCL has been read, and a conversion completes before ADCH is
//read, neither register is updated and the result from the conversion is lost. When ADCH is read,
//ADC access to the ADCH and ADCL Registers is re-enabled.
////////////////////////////////////////////////////////////////////////////////////////////////
inline unsigned int adc_read16(void)	//adjust RIGHT
{
	uint8_t tempADCL = ADCL;			//first - latch ADCH
	return ( (((unsigned int)(ADCH & 0x03))<<8) + tempADCL);
}
inline void adc_set_channel_gain(uint8_t ch_gain)
{
	ADMUX = (ADMUX & 0xE0) | ch_gain;
}

//PF2=ADC2
void adc_init(void)
{
	ADMUX = (0<<REFS1)|(1<<REFS0)|
			(0<<ADLAR)|
			0x02;
	ADCSRA = (1<<ADEN)|(0<<ADSC)|(0<<ADFR)|
			0x07;//DIV 128
}
volatile uint16_t adc16;
void onetouch_capacitive(void)
{
	//	PinTo0(PORTF,PF2);					//pull up off
	OCR1C = 0;
	PinTo0(PORTF,PF2);	//PULLUP OFF
	ConfigInputPin(DDRF,PF2);//OC1A
	
	//BitTo0(ADCSRA,ADEN);
//while(1);
	while (1)
	{
		adc_set_channel_gain(ADC_CH_GND_OV);//tied to 0V
		ADCSRA |= (1<<ADSC);
		while (ADCSRA & (1<<ADSC));
		//cap SH descargado
		//
//BitTo0(ADCSRA,ADEN);
//		NOP();
		
		//carga capacidad externa
		PinTo1(PORTF,PF2);					//pull up on
		_delay_ms(1);
		//_delay_us(202);						//stabilize 25 clocks
		
		PinTo0(PORTF,PF2);					//pull up off
//		BitTo1(ADCSRA,ADEN);
//		NOP();
		
		adc_set_channel_gain(ADC_CH_ADC2_SINGLE);
		ADCSRA |= (1<<ADSC);
		while (ADCSRA & (1<<ADSC));
		
		adc16 = adc_read16();
		if (adc16 >=570)//550 900 -->>OK!!!!!! QUEDA 8:27pm
		{
			OCR1C = 1023;
		}
		else
		{
			OCR1C = 0;
		}
	}
}
/*
DEPURACION
when it is debuggin, NOT UPDATE ADSC, but yes ADCH:ADCL
maybe new AVRStudio6.xxxx
*/
void singleconv1(void)
{
	InitPWM();
	adc_init();
	
	PinTo0(PORTF,PF2);	//PULLUP OFF
	ConfigInputPin(DDRF,PF2);//OC1A

	onetouch_capacitive();

	///////////////////////////////
	while (1)	//OK conversion
	{
		ADCSRA |= (1<<ADSC);
		while (ADCSRA & (1<<ADSC));
		
		OCR1C = adc_read16();
	}	
}
