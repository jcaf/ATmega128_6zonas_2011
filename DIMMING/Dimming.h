/*
 * Dimming.h
 *
 * Created: 23/02/2012 10:58:39 p.m.
 *  Author: jcaf
 */ 
#ifndef DIMMING_H_
#define DIMMING_H_
	
	#define MAX_VAL_DUTYCYCLE (NUM_ELEM_DENTRO_BAR*FACTOR_ESCALA_DIMMING)
	
	#define OCRnx_Z1 (OCR1B)
	#define OCRnx_Z2 (OCR1C)
	#define OCRnx_Z3 (OCR3A)
	#define OCRnx_Z4 (OCR1A)
	#define OCRnx_Z5 (OCR3B)
	#define OCRnx_Z6 (OCR3C)

	#define DIMMING_UP		(+1)
	#define DIMMING_DOWN	(-1)
	
	void _PreEx_DimmingUp(byte zone);
	void _PreEx_DimmingDown(byte zone);
	void dimming(byte zone, signed char dir);
	void dimming_up(byte zone);
	void dimming_down(byte zone);
	
	void updatedc_acctypeofload(byte zone);
	void updatedc(byte zone, TYPEDC dc);
	void dcporcentz(TYPEDC dc);
	TYPEDC if_fadingactive_nextdc_else_dc(byte zone);/*getting a stable dc */
	
	//void setting_preupdate_dc(byte zone, word val);//BUG FIXED 
	void setting_preupdate_dc(byte zone, TYPEDC val_to_dc);//BUG FIXED word-> TYPEDC
 
	
	//void for_nodimmable_directupdate_barlevel(byte zone);
	void _dcporcentz_acctypeofload(byte zone);
	
	
	void RestoreOnOff_mode1(byte zone);
	void directOnOff_mode1(byte zone);
	void RestoreOnOff_mode2(byte zone);
	void directOnOff_mode2(byte zone);


	BOOL _all_current_dcs_are_lessequalthan_threshold(void);
	BOOL _all_zones_have_pto_rstr_OFF(void);


#endif /* DIMMING_H_ */

	
	
