/*
 * ADC.h
 *
 * Created: 4/26/2013 11:51:12 AM
 *  Author: jc
 */ 


#ifndef ADC_H_
#define ADC_H_
	/////////////////////////////////////////////////////////////////////////	//ADC Multiplexer Selection Register ADMUX					/////////////////////////////////////////////////////////////////////////
	//Bit 7:6 REFS1:0 Rerefence Selection Bits	#define AREF_INTERNAL_Vref_TURNED_OFF				((0x00)<<6)	#define AVCC_WITH_EXTERNAL_CAP_AT_AREF_PIN			((0x01)<<6)	#define RESERVED_REFS1_0							((0x02)<<6)	#define INTERNAL_2p56VWITH_EXTERNAL_CAP_AT_AREF_PIN ((0x03)<<6)
	//Bit 5: ADLAR: ADC Left Adjust Result	#define RIGHT_ADJUST	((0x00)<<5)	#define LEFT_ADJUST		((0x01)<<5)
	//Bit 4:0 MUX4:0 Analog Channel and Gain Selection Bits	//8 Singled Ended Inputs referenced to GND	#define	ADC_CH_ADC0_SINGLE						(0x00)		#define	ADC_CH_ADC1_SINGLE						(0x01)		#define	ADC_CH_ADC2_SINGLE						(0x02)		#define	ADC_CH_ADC3_SINGLE						(0x03)		#define	ADC_CH_ADC4_SINGLE						(0x04)		#define	ADC_CH_ADC5_SINGLE						(0x05)		#define	ADC_CH_ADC6_SINGLE						(0x06)		#define	ADC_CH_ADC7_SINGLE						(0x07)		//16 COMBINACIONES Entradas diferenciales	//2 Differential Input Channels with Optional Gain of 10x and 200x	//Two (ADC1, ADC0 and ADC3, ADC2) have a programmable gain stage with 1X, 10X, or 200X gain selectable	// 1X or 10X can expect 8 bit resolution	// 200X 7-bit resolution 	#define ADC_CH_POSDIFF_ADC0_NEGDIFF_ADC0_G10x	(0x08)		#define ADC_CH_POSDIFF_ADC1_NEGDIFF_ADC0_G10x	(0x09)	#define ADC_CH_POSDIFF_ADC0_NEGDIFF_ADC0_G200x	(0x0A)		#define ADC_CH_POSDIFF_ADC1_NEGDIFF_ADC0_G200x	(0x0B)	#define ADC_CH_POSDIFF_ADC2_NEGDIFF_ADC2_G10x	(0x0C)		#define ADC_CH_POSDIFF_ADC3_NEGDIFF_ADC2_G10x	(0x0D)	#define ADC_CH_POSDIFF_ADC2_NEGDIFF_ADC2_G200x	(0x0E)		#define ADC_CH_POSDIFF_ADC3_NEGDIFF_ADC2_G200x	(0x0F)	//1x (Referidos a ADC1(-) ) NOTA: " 7 Differential Channels in TQFP Package Only" CONFIRMAR MODELO AVR	#define ADC_CH_POSDIFF_ADC0_NEGDIFF_ADC1_G1x	(0x10)	#define ADC_CH_POSDIFF_ADC1_NEGDIFF_ADC1_G1x	(0x11)	//? ->DONT CARE DUMMY	#define ADC_CH_POSDIFF_ADC2_NEGDIFF_ADC1_G1x	(0x12)	#define ADC_CH_POSDIFF_ADC3_NEGDIFF_ADC1_G1x	(0x13)	#define ADC_CH_POSDIFF_ADC4_NEGDIFF_ADC1_G1x	(0x14)	#define ADC_CH_POSDIFF_ADC5_NEGDIFF_ADC1_G1x	(0x15)	#define ADC_CH_POSDIFF_ADC6_NEGDIFF_ADC1_G1x	(0x16)	#define ADC_CH_POSDIFF_ADC7_NEGDIFF_ADC1_G1x	(0x17)	//1x (Referidos a ADC2(-) )	#define ADC_CH_POSDIFF_ADC0_NEGDIFF_ADC2_G1x	(0x18)	#define ADC_CH_POSDIFF_ADC1_NEGDIFF_ADC2_G1x	(0x19)	#define ADC_CH_POSDIFF_ADC2_NEGDIFF_ADC2_G1x	(0x1A)	#define ADC_CH_POSDIFF_ADC3_NEGDIFF_ADC2_G1x	(0x1B)	#define ADC_CH_POSDIFF_ADC4_NEGDIFF_ADC2_G1x	(0x1C)	#define ADC_CH_POSDIFF_ADC5_NEGDIFF_ADC2_G1x	(0x1D)	//+ 2 Singled Ended Inputs	(especiales)	#define ADC_CH_VBG_1_23V						(0x1E)	//Util	#define ADC_CH_GND_OV							(0x1F)	//Util	/////////////////////////////////////////////////////////////////////////
	//ADC Control and Status Register A: ADCSRA                     	/////////////////////////////////////////////////////////////////////////
	//#define ADC_PRESCALER_2		(0x00)	//#define ADC_PRESCALER_2		(0x01)	//#define ADC_PRESCALER_4		(0x02)	//#define ADC_PRESCALER_8		(0x03)	//#define ADC_PRESCALER_16	(0x04)	//#define ADC_PRESCALER_32 	(0x05)	//#define ADC_PRESCALER_64	(0x06)	//#define ADC_PRESCALER_128	(0x07)
	/////////////////////////////////////////////////////////////////////////	//LAS SIGUIENTES Fx NO AFECTAN EN ABSOLUTO ADIF, asi es que todavia podria 	//preguntarse por ese flag si esta a '1'	/////////////////////////////////////////////////////////////////////////
	//#define ADC_Disable() do{ADCSRA &= ~( (1<<ADEN)|(1<<ADIF) );}while(0)		//#define ADC_AutoTriggerDisable() do{ADCSRA &= ~( (1<<ADATE)|(1<<ADIF) );}while(0)		//#define ADC_InterruptDisable() do{ADCSRA &= ~( (1<<ADIE)|(1<<ADIF) );}while(0)	
	/////////////////////////////////////////////////////////////////////////	//LAS SIGUIENTES Fx AFECTARIAN(LIMPIARIAN) "ADIF" SI ESTE SE ENCUENTRA A '1' Y NO HA SIDO ATENDIDO PREVIAMENTE	// Bit 4 ? ADIF: ADC Interrupt Flag	/////////////////////////////////////////////////////////////////////////
	//#define ADC_Enable_And_ADIFClear() BitTo1(ADCSRA,ADEN)	//#define ADC_StartConversion_And_ADIFClear() BitTo1(ADCSRA, ADSC)	//#define ADC_AutoTriggerEnable_And_ADIFClear() BitTo1(ADCSRA,ADATE)	//#define ADC_InterruptEnable_And_ADIFClear() BitTo1(ADCSRA,ADIE)
	/////////////////////////////////////////////////////////////////////////
	void singleconv1(void);
	void adc_init(void);
	//inline unsigned int adc_read16(void);

#endif /* ADC_H_ */

