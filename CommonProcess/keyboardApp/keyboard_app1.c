/*
 * keyboard_app1.c
 *
 * Created: 9/24/2012 8:39:01 PM
 *  Author: JCaf
 */ 
#include "Includes/InitializeAllModules.h"

	void setkb_mix0(void)
	{
		//KB_clear_all_key_properties();
		
		objkey[KB_iKEY1].key_properties.u.bf.OnKeyPressed  =1;
		objkey[KB_iKEY1].key_properties.u.bf.OnKeyPressedAndKeyRelease = 0;
		objkey[KB_iKEY1].key_properties.u.bf.AtTimeExpired =0;
		objkey[KB_iKEY1].key_properties.u.bf.Reptt = 0;
		objkey[KB_iKEY1].key_properties.group_autoexcluding = 1;
	
		objkey[KB_iKEY2].key_properties.u.bf.OnKeyPressed  =1;
		objkey[KB_iKEY2].key_properties.u.bf.OnKeyPressedAndKeyRelease = 0;
		objkey[KB_iKEY2].key_properties.u.bf.AtTimeExpired =0;
		objkey[KB_iKEY2].key_properties.u.bf.Reptt = 0;
		objkey[KB_iKEY2].key_properties.group_autoexcluding = 1;
	
		objkey[KB_iKEY3].key_properties.u.bf.OnKeyPressed  =0;
		objkey[KB_iKEY3].key_properties.u.bf.OnKeyPressedAndKeyRelease = 0;
		objkey[KB_iKEY3].key_properties.u.bf.AtTimeExpired =1;
		objkey[KB_iKEY3].key_properties.u.bf.Reptt = 0;
		objkey[KB_iKEY3].key_properties.group_autoexcluding = 1;
		
	
		objkey[KB_iKEY4].key_properties.u.bf.OnKeyPressed  =0;
		objkey[KB_iKEY4].key_properties.u.bf.OnKeyPressedAndKeyRelease = 0;
		objkey[KB_iKEY4].key_properties.u.bf.AtTimeExpired =1;
		objkey[KB_iKEY4].key_properties.u.bf.Reptt = 0;
		objkey[KB_iKEY4].key_properties.group_autoexcluding = _NO_AGRUPADO_AUTOEXCLUDING_;
			
		//Acepting overriding
		//objsharedfeatkeys.TriggerRepttGlobal = _KTE_TRIGGER_REPPT_500ms_;
		//objsharedfeatkeys.HoldingRepttGlobal = 50/5;	//expresados en *ms ->cada 5ms*10 = 50ms
	}
	
	
	
	
	
	