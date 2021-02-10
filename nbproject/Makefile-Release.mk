#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-Release.mk)" "nbproject/Makefile-local-Release.mk"
include nbproject/Makefile-local-Release.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=Release
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/ATmega128_6Zonas_2011.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/ATmega128_6Zonas_2011.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=ADC/ADC1.c CommonProcess/keyboardApp/keyboard_app1.c CommonProcess/TimmerApp/TimerApp_1.c CommonProcess/CommonToProcess_1.c db_name_vocabulary/dbname_voc_1.c DimmBackLightGLCD/DimmBLGLCD_1.c DIMMING/Dimming_1.c DS3231/DS3231_1.c EFFECTS/BLINKING/Blinking_2.c ESCENAS/EliminarEscena_1.c ESCENAS/Escenas_2.c ESCENAS/ModificarEscena_1.c ESCENAS/NuevaEscena_2.c FADING/Fading_1.c GUI/GUI_1.c key/key_2.c KEYBOARD/KEYBOARD_API/KeyboardAPI_1.c KEYBOARD/DEBUG_TestKeyboard.c KEYBOARD/KeyboardHandler_1.c MENU/ClaseMenu/ClaseMenu_3.c MENU/MenuDimming6Zonas/MenuDimming6Zonas_4.c MENU/MenuScene/MenuScene_3.c MENU/MenuSelectDimmNoDimmLoad/MenuSelectDimmNoDimmLoad_1.c ObjControl/DialogBox/DialogBox_1.c ObjControl/List/ListBox_1.c ObjControl/RadioButton/RadioButton_1.c PLAYSOUND/PlaySound_1.c PWM/PWM_1.c RS485/RS485_1.c SHELL/Shell_5.c TIMEDATE/TimeDate_2.c TIMMER_NB/Timmer_nb_1.c ZONA/NamingZone/NamingZone_2.c ZONA/Zona_1.c BUZZER/Buzzer_1.c EEPROM/EEPROM.c GLCD192X64/GLCD192x64_01.c GLCD192X64/GLCD_fxs_1.c I2C/I2CCommonFx.c I2C/I2C_01.c main1.c TCNT0/TCNT0_01.c USART/USART_01.c KS108v1/ks0108.c KS108v1/FONTS/SC.c KS108v1/FONTS/arial_bold_14.c KS108v1/FONTS/corsiva_12.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/ADC/ADC1.o ${OBJECTDIR}/CommonProcess/keyboardApp/keyboard_app1.o ${OBJECTDIR}/CommonProcess/TimmerApp/TimerApp_1.o ${OBJECTDIR}/CommonProcess/CommonToProcess_1.o ${OBJECTDIR}/db_name_vocabulary/dbname_voc_1.o ${OBJECTDIR}/DimmBackLightGLCD/DimmBLGLCD_1.o ${OBJECTDIR}/DIMMING/Dimming_1.o ${OBJECTDIR}/DS3231/DS3231_1.o ${OBJECTDIR}/EFFECTS/BLINKING/Blinking_2.o ${OBJECTDIR}/ESCENAS/EliminarEscena_1.o ${OBJECTDIR}/ESCENAS/Escenas_2.o ${OBJECTDIR}/ESCENAS/ModificarEscena_1.o ${OBJECTDIR}/ESCENAS/NuevaEscena_2.o ${OBJECTDIR}/FADING/Fading_1.o ${OBJECTDIR}/GUI/GUI_1.o ${OBJECTDIR}/key/key_2.o ${OBJECTDIR}/KEYBOARD/KEYBOARD_API/KeyboardAPI_1.o ${OBJECTDIR}/KEYBOARD/DEBUG_TestKeyboard.o ${OBJECTDIR}/KEYBOARD/KeyboardHandler_1.o ${OBJECTDIR}/MENU/ClaseMenu/ClaseMenu_3.o ${OBJECTDIR}/MENU/MenuDimming6Zonas/MenuDimming6Zonas_4.o ${OBJECTDIR}/MENU/MenuScene/MenuScene_3.o ${OBJECTDIR}/MENU/MenuSelectDimmNoDimmLoad/MenuSelectDimmNoDimmLoad_1.o ${OBJECTDIR}/ObjControl/DialogBox/DialogBox_1.o ${OBJECTDIR}/ObjControl/List/ListBox_1.o ${OBJECTDIR}/ObjControl/RadioButton/RadioButton_1.o ${OBJECTDIR}/PLAYSOUND/PlaySound_1.o ${OBJECTDIR}/PWM/PWM_1.o ${OBJECTDIR}/RS485/RS485_1.o ${OBJECTDIR}/SHELL/Shell_5.o ${OBJECTDIR}/TIMEDATE/TimeDate_2.o ${OBJECTDIR}/TIMMER_NB/Timmer_nb_1.o ${OBJECTDIR}/ZONA/NamingZone/NamingZone_2.o ${OBJECTDIR}/ZONA/Zona_1.o ${OBJECTDIR}/BUZZER/Buzzer_1.o ${OBJECTDIR}/EEPROM/EEPROM.o ${OBJECTDIR}/GLCD192X64/GLCD192x64_01.o ${OBJECTDIR}/GLCD192X64/GLCD_fxs_1.o ${OBJECTDIR}/I2C/I2CCommonFx.o ${OBJECTDIR}/I2C/I2C_01.o ${OBJECTDIR}/main1.o ${OBJECTDIR}/TCNT0/TCNT0_01.o ${OBJECTDIR}/USART/USART_01.o ${OBJECTDIR}/KS108v1/ks0108.o ${OBJECTDIR}/KS108v1/FONTS/SC.o ${OBJECTDIR}/KS108v1/FONTS/arial_bold_14.o ${OBJECTDIR}/KS108v1/FONTS/corsiva_12.o
POSSIBLE_DEPFILES=${OBJECTDIR}/ADC/ADC1.o.d ${OBJECTDIR}/CommonProcess/keyboardApp/keyboard_app1.o.d ${OBJECTDIR}/CommonProcess/TimmerApp/TimerApp_1.o.d ${OBJECTDIR}/CommonProcess/CommonToProcess_1.o.d ${OBJECTDIR}/db_name_vocabulary/dbname_voc_1.o.d ${OBJECTDIR}/DimmBackLightGLCD/DimmBLGLCD_1.o.d ${OBJECTDIR}/DIMMING/Dimming_1.o.d ${OBJECTDIR}/DS3231/DS3231_1.o.d ${OBJECTDIR}/EFFECTS/BLINKING/Blinking_2.o.d ${OBJECTDIR}/ESCENAS/EliminarEscena_1.o.d ${OBJECTDIR}/ESCENAS/Escenas_2.o.d ${OBJECTDIR}/ESCENAS/ModificarEscena_1.o.d ${OBJECTDIR}/ESCENAS/NuevaEscena_2.o.d ${OBJECTDIR}/FADING/Fading_1.o.d ${OBJECTDIR}/GUI/GUI_1.o.d ${OBJECTDIR}/key/key_2.o.d ${OBJECTDIR}/KEYBOARD/KEYBOARD_API/KeyboardAPI_1.o.d ${OBJECTDIR}/KEYBOARD/DEBUG_TestKeyboard.o.d ${OBJECTDIR}/KEYBOARD/KeyboardHandler_1.o.d ${OBJECTDIR}/MENU/ClaseMenu/ClaseMenu_3.o.d ${OBJECTDIR}/MENU/MenuDimming6Zonas/MenuDimming6Zonas_4.o.d ${OBJECTDIR}/MENU/MenuScene/MenuScene_3.o.d ${OBJECTDIR}/MENU/MenuSelectDimmNoDimmLoad/MenuSelectDimmNoDimmLoad_1.o.d ${OBJECTDIR}/ObjControl/DialogBox/DialogBox_1.o.d ${OBJECTDIR}/ObjControl/List/ListBox_1.o.d ${OBJECTDIR}/ObjControl/RadioButton/RadioButton_1.o.d ${OBJECTDIR}/PLAYSOUND/PlaySound_1.o.d ${OBJECTDIR}/PWM/PWM_1.o.d ${OBJECTDIR}/RS485/RS485_1.o.d ${OBJECTDIR}/SHELL/Shell_5.o.d ${OBJECTDIR}/TIMEDATE/TimeDate_2.o.d ${OBJECTDIR}/TIMMER_NB/Timmer_nb_1.o.d ${OBJECTDIR}/ZONA/NamingZone/NamingZone_2.o.d ${OBJECTDIR}/ZONA/Zona_1.o.d ${OBJECTDIR}/BUZZER/Buzzer_1.o.d ${OBJECTDIR}/EEPROM/EEPROM.o.d ${OBJECTDIR}/GLCD192X64/GLCD192x64_01.o.d ${OBJECTDIR}/GLCD192X64/GLCD_fxs_1.o.d ${OBJECTDIR}/I2C/I2CCommonFx.o.d ${OBJECTDIR}/I2C/I2C_01.o.d ${OBJECTDIR}/main1.o.d ${OBJECTDIR}/TCNT0/TCNT0_01.o.d ${OBJECTDIR}/USART/USART_01.o.d ${OBJECTDIR}/KS108v1/ks0108.o.d ${OBJECTDIR}/KS108v1/FONTS/SC.o.d ${OBJECTDIR}/KS108v1/FONTS/arial_bold_14.o.d ${OBJECTDIR}/KS108v1/FONTS/corsiva_12.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/ADC/ADC1.o ${OBJECTDIR}/CommonProcess/keyboardApp/keyboard_app1.o ${OBJECTDIR}/CommonProcess/TimmerApp/TimerApp_1.o ${OBJECTDIR}/CommonProcess/CommonToProcess_1.o ${OBJECTDIR}/db_name_vocabulary/dbname_voc_1.o ${OBJECTDIR}/DimmBackLightGLCD/DimmBLGLCD_1.o ${OBJECTDIR}/DIMMING/Dimming_1.o ${OBJECTDIR}/DS3231/DS3231_1.o ${OBJECTDIR}/EFFECTS/BLINKING/Blinking_2.o ${OBJECTDIR}/ESCENAS/EliminarEscena_1.o ${OBJECTDIR}/ESCENAS/Escenas_2.o ${OBJECTDIR}/ESCENAS/ModificarEscena_1.o ${OBJECTDIR}/ESCENAS/NuevaEscena_2.o ${OBJECTDIR}/FADING/Fading_1.o ${OBJECTDIR}/GUI/GUI_1.o ${OBJECTDIR}/key/key_2.o ${OBJECTDIR}/KEYBOARD/KEYBOARD_API/KeyboardAPI_1.o ${OBJECTDIR}/KEYBOARD/DEBUG_TestKeyboard.o ${OBJECTDIR}/KEYBOARD/KeyboardHandler_1.o ${OBJECTDIR}/MENU/ClaseMenu/ClaseMenu_3.o ${OBJECTDIR}/MENU/MenuDimming6Zonas/MenuDimming6Zonas_4.o ${OBJECTDIR}/MENU/MenuScene/MenuScene_3.o ${OBJECTDIR}/MENU/MenuSelectDimmNoDimmLoad/MenuSelectDimmNoDimmLoad_1.o ${OBJECTDIR}/ObjControl/DialogBox/DialogBox_1.o ${OBJECTDIR}/ObjControl/List/ListBox_1.o ${OBJECTDIR}/ObjControl/RadioButton/RadioButton_1.o ${OBJECTDIR}/PLAYSOUND/PlaySound_1.o ${OBJECTDIR}/PWM/PWM_1.o ${OBJECTDIR}/RS485/RS485_1.o ${OBJECTDIR}/SHELL/Shell_5.o ${OBJECTDIR}/TIMEDATE/TimeDate_2.o ${OBJECTDIR}/TIMMER_NB/Timmer_nb_1.o ${OBJECTDIR}/ZONA/NamingZone/NamingZone_2.o ${OBJECTDIR}/ZONA/Zona_1.o ${OBJECTDIR}/BUZZER/Buzzer_1.o ${OBJECTDIR}/EEPROM/EEPROM.o ${OBJECTDIR}/GLCD192X64/GLCD192x64_01.o ${OBJECTDIR}/GLCD192X64/GLCD_fxs_1.o ${OBJECTDIR}/I2C/I2CCommonFx.o ${OBJECTDIR}/I2C/I2C_01.o ${OBJECTDIR}/main1.o ${OBJECTDIR}/TCNT0/TCNT0_01.o ${OBJECTDIR}/USART/USART_01.o ${OBJECTDIR}/KS108v1/ks0108.o ${OBJECTDIR}/KS108v1/FONTS/SC.o ${OBJECTDIR}/KS108v1/FONTS/arial_bold_14.o ${OBJECTDIR}/KS108v1/FONTS/corsiva_12.o

# Source Files
SOURCEFILES=ADC/ADC1.c CommonProcess/keyboardApp/keyboard_app1.c CommonProcess/TimmerApp/TimerApp_1.c CommonProcess/CommonToProcess_1.c db_name_vocabulary/dbname_voc_1.c DimmBackLightGLCD/DimmBLGLCD_1.c DIMMING/Dimming_1.c DS3231/DS3231_1.c EFFECTS/BLINKING/Blinking_2.c ESCENAS/EliminarEscena_1.c ESCENAS/Escenas_2.c ESCENAS/ModificarEscena_1.c ESCENAS/NuevaEscena_2.c FADING/Fading_1.c GUI/GUI_1.c key/key_2.c KEYBOARD/KEYBOARD_API/KeyboardAPI_1.c KEYBOARD/DEBUG_TestKeyboard.c KEYBOARD/KeyboardHandler_1.c MENU/ClaseMenu/ClaseMenu_3.c MENU/MenuDimming6Zonas/MenuDimming6Zonas_4.c MENU/MenuScene/MenuScene_3.c MENU/MenuSelectDimmNoDimmLoad/MenuSelectDimmNoDimmLoad_1.c ObjControl/DialogBox/DialogBox_1.c ObjControl/List/ListBox_1.c ObjControl/RadioButton/RadioButton_1.c PLAYSOUND/PlaySound_1.c PWM/PWM_1.c RS485/RS485_1.c SHELL/Shell_5.c TIMEDATE/TimeDate_2.c TIMMER_NB/Timmer_nb_1.c ZONA/NamingZone/NamingZone_2.c ZONA/Zona_1.c BUZZER/Buzzer_1.c EEPROM/EEPROM.c GLCD192X64/GLCD192x64_01.c GLCD192X64/GLCD_fxs_1.c I2C/I2CCommonFx.c I2C/I2C_01.c main1.c TCNT0/TCNT0_01.c USART/USART_01.c KS108v1/ks0108.c KS108v1/FONTS/SC.c KS108v1/FONTS/arial_bold_14.c KS108v1/FONTS/corsiva_12.c

# Pack Options 
PACK_COMPILER_OPTIONS=-I "${DFP_DIR}/include"
PACK_COMMON_OPTIONS=-B "${DFP_DIR}/gcc/dev/atmega128"



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-Release.mk dist/${CND_CONF}/${IMAGE_TYPE}/ATmega128_6Zonas_2011.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=ATmega128
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/ADC/ADC1.o: ADC/ADC1.c  .generated_files/83bb8a000c949d29f74649da6986215274f71c35.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/ADC" 
	@${RM} ${OBJECTDIR}/ADC/ADC1.o.d 
	@${RM} ${OBJECTDIR}/ADC/ADC1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/ADC/ADC1.o.d" -MT "${OBJECTDIR}/ADC/ADC1.o.d" -MT ${OBJECTDIR}/ADC/ADC1.o  -o ${OBJECTDIR}/ADC/ADC1.o ADC/ADC1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/CommonProcess/keyboardApp/keyboard_app1.o: CommonProcess/keyboardApp/keyboard_app1.c  .generated_files/c5df535f50852443565e821c61a2065bb86eb6a6.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/CommonProcess/keyboardApp" 
	@${RM} ${OBJECTDIR}/CommonProcess/keyboardApp/keyboard_app1.o.d 
	@${RM} ${OBJECTDIR}/CommonProcess/keyboardApp/keyboard_app1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/CommonProcess/keyboardApp/keyboard_app1.o.d" -MT "${OBJECTDIR}/CommonProcess/keyboardApp/keyboard_app1.o.d" -MT ${OBJECTDIR}/CommonProcess/keyboardApp/keyboard_app1.o  -o ${OBJECTDIR}/CommonProcess/keyboardApp/keyboard_app1.o CommonProcess/keyboardApp/keyboard_app1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/CommonProcess/TimmerApp/TimerApp_1.o: CommonProcess/TimmerApp/TimerApp_1.c  .generated_files/e8cbd2e33f27ceb466c692d7ee700c4de684a629.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/CommonProcess/TimmerApp" 
	@${RM} ${OBJECTDIR}/CommonProcess/TimmerApp/TimerApp_1.o.d 
	@${RM} ${OBJECTDIR}/CommonProcess/TimmerApp/TimerApp_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/CommonProcess/TimmerApp/TimerApp_1.o.d" -MT "${OBJECTDIR}/CommonProcess/TimmerApp/TimerApp_1.o.d" -MT ${OBJECTDIR}/CommonProcess/TimmerApp/TimerApp_1.o  -o ${OBJECTDIR}/CommonProcess/TimmerApp/TimerApp_1.o CommonProcess/TimmerApp/TimerApp_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/CommonProcess/CommonToProcess_1.o: CommonProcess/CommonToProcess_1.c  .generated_files/58b15eb3dbf2260148e47440ddf62be9316d3ea1.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/CommonProcess" 
	@${RM} ${OBJECTDIR}/CommonProcess/CommonToProcess_1.o.d 
	@${RM} ${OBJECTDIR}/CommonProcess/CommonToProcess_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/CommonProcess/CommonToProcess_1.o.d" -MT "${OBJECTDIR}/CommonProcess/CommonToProcess_1.o.d" -MT ${OBJECTDIR}/CommonProcess/CommonToProcess_1.o  -o ${OBJECTDIR}/CommonProcess/CommonToProcess_1.o CommonProcess/CommonToProcess_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/db_name_vocabulary/dbname_voc_1.o: db_name_vocabulary/dbname_voc_1.c  .generated_files/909de186b92b855000b3dd8061924abd563455d5.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/db_name_vocabulary" 
	@${RM} ${OBJECTDIR}/db_name_vocabulary/dbname_voc_1.o.d 
	@${RM} ${OBJECTDIR}/db_name_vocabulary/dbname_voc_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/db_name_vocabulary/dbname_voc_1.o.d" -MT "${OBJECTDIR}/db_name_vocabulary/dbname_voc_1.o.d" -MT ${OBJECTDIR}/db_name_vocabulary/dbname_voc_1.o  -o ${OBJECTDIR}/db_name_vocabulary/dbname_voc_1.o db_name_vocabulary/dbname_voc_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/DimmBackLightGLCD/DimmBLGLCD_1.o: DimmBackLightGLCD/DimmBLGLCD_1.c  .generated_files/2196227ddecb6d17e4b9c2b16386f0deec378f6a.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/DimmBackLightGLCD" 
	@${RM} ${OBJECTDIR}/DimmBackLightGLCD/DimmBLGLCD_1.o.d 
	@${RM} ${OBJECTDIR}/DimmBackLightGLCD/DimmBLGLCD_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/DimmBackLightGLCD/DimmBLGLCD_1.o.d" -MT "${OBJECTDIR}/DimmBackLightGLCD/DimmBLGLCD_1.o.d" -MT ${OBJECTDIR}/DimmBackLightGLCD/DimmBLGLCD_1.o  -o ${OBJECTDIR}/DimmBackLightGLCD/DimmBLGLCD_1.o DimmBackLightGLCD/DimmBLGLCD_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/DIMMING/Dimming_1.o: DIMMING/Dimming_1.c  .generated_files/ee946c8da93fb262a803b8da3437678bd4b14598.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/DIMMING" 
	@${RM} ${OBJECTDIR}/DIMMING/Dimming_1.o.d 
	@${RM} ${OBJECTDIR}/DIMMING/Dimming_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/DIMMING/Dimming_1.o.d" -MT "${OBJECTDIR}/DIMMING/Dimming_1.o.d" -MT ${OBJECTDIR}/DIMMING/Dimming_1.o  -o ${OBJECTDIR}/DIMMING/Dimming_1.o DIMMING/Dimming_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/DS3231/DS3231_1.o: DS3231/DS3231_1.c  .generated_files/30a6a306a5e5ca01095863e2bfa0540c580c80d9.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/DS3231" 
	@${RM} ${OBJECTDIR}/DS3231/DS3231_1.o.d 
	@${RM} ${OBJECTDIR}/DS3231/DS3231_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/DS3231/DS3231_1.o.d" -MT "${OBJECTDIR}/DS3231/DS3231_1.o.d" -MT ${OBJECTDIR}/DS3231/DS3231_1.o  -o ${OBJECTDIR}/DS3231/DS3231_1.o DS3231/DS3231_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/EFFECTS/BLINKING/Blinking_2.o: EFFECTS/BLINKING/Blinking_2.c  .generated_files/6da71d070ca1373ab7943fbe4fc9a3a055457e7f.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/EFFECTS/BLINKING" 
	@${RM} ${OBJECTDIR}/EFFECTS/BLINKING/Blinking_2.o.d 
	@${RM} ${OBJECTDIR}/EFFECTS/BLINKING/Blinking_2.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/EFFECTS/BLINKING/Blinking_2.o.d" -MT "${OBJECTDIR}/EFFECTS/BLINKING/Blinking_2.o.d" -MT ${OBJECTDIR}/EFFECTS/BLINKING/Blinking_2.o  -o ${OBJECTDIR}/EFFECTS/BLINKING/Blinking_2.o EFFECTS/BLINKING/Blinking_2.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/ESCENAS/EliminarEscena_1.o: ESCENAS/EliminarEscena_1.c  .generated_files/6c9e020e4af4b322bc98006b6a4614bd0ece0b7c.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/ESCENAS" 
	@${RM} ${OBJECTDIR}/ESCENAS/EliminarEscena_1.o.d 
	@${RM} ${OBJECTDIR}/ESCENAS/EliminarEscena_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/ESCENAS/EliminarEscena_1.o.d" -MT "${OBJECTDIR}/ESCENAS/EliminarEscena_1.o.d" -MT ${OBJECTDIR}/ESCENAS/EliminarEscena_1.o  -o ${OBJECTDIR}/ESCENAS/EliminarEscena_1.o ESCENAS/EliminarEscena_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/ESCENAS/Escenas_2.o: ESCENAS/Escenas_2.c  .generated_files/bb07ddb87d782add1acd1573267a5a86366b3983.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/ESCENAS" 
	@${RM} ${OBJECTDIR}/ESCENAS/Escenas_2.o.d 
	@${RM} ${OBJECTDIR}/ESCENAS/Escenas_2.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/ESCENAS/Escenas_2.o.d" -MT "${OBJECTDIR}/ESCENAS/Escenas_2.o.d" -MT ${OBJECTDIR}/ESCENAS/Escenas_2.o  -o ${OBJECTDIR}/ESCENAS/Escenas_2.o ESCENAS/Escenas_2.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/ESCENAS/ModificarEscena_1.o: ESCENAS/ModificarEscena_1.c  .generated_files/653a3933761ac54be0195751ae9b3a6eeb1204e0.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/ESCENAS" 
	@${RM} ${OBJECTDIR}/ESCENAS/ModificarEscena_1.o.d 
	@${RM} ${OBJECTDIR}/ESCENAS/ModificarEscena_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/ESCENAS/ModificarEscena_1.o.d" -MT "${OBJECTDIR}/ESCENAS/ModificarEscena_1.o.d" -MT ${OBJECTDIR}/ESCENAS/ModificarEscena_1.o  -o ${OBJECTDIR}/ESCENAS/ModificarEscena_1.o ESCENAS/ModificarEscena_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/ESCENAS/NuevaEscena_2.o: ESCENAS/NuevaEscena_2.c  .generated_files/6e2a6b423df4d698ad9c7ae5b50982741511e75c.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/ESCENAS" 
	@${RM} ${OBJECTDIR}/ESCENAS/NuevaEscena_2.o.d 
	@${RM} ${OBJECTDIR}/ESCENAS/NuevaEscena_2.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/ESCENAS/NuevaEscena_2.o.d" -MT "${OBJECTDIR}/ESCENAS/NuevaEscena_2.o.d" -MT ${OBJECTDIR}/ESCENAS/NuevaEscena_2.o  -o ${OBJECTDIR}/ESCENAS/NuevaEscena_2.o ESCENAS/NuevaEscena_2.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/FADING/Fading_1.o: FADING/Fading_1.c  .generated_files/f5e4042f6c984f8876875770c7a98ab6a85bfbfa.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/FADING" 
	@${RM} ${OBJECTDIR}/FADING/Fading_1.o.d 
	@${RM} ${OBJECTDIR}/FADING/Fading_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/FADING/Fading_1.o.d" -MT "${OBJECTDIR}/FADING/Fading_1.o.d" -MT ${OBJECTDIR}/FADING/Fading_1.o  -o ${OBJECTDIR}/FADING/Fading_1.o FADING/Fading_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/GUI/GUI_1.o: GUI/GUI_1.c  .generated_files/3e6a1296640cec0781f58270fb2f1978f8911a72.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/GUI" 
	@${RM} ${OBJECTDIR}/GUI/GUI_1.o.d 
	@${RM} ${OBJECTDIR}/GUI/GUI_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/GUI/GUI_1.o.d" -MT "${OBJECTDIR}/GUI/GUI_1.o.d" -MT ${OBJECTDIR}/GUI/GUI_1.o  -o ${OBJECTDIR}/GUI/GUI_1.o GUI/GUI_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/key/key_2.o: key/key_2.c  .generated_files/68e697786978ab433904b58df436508af35bc093.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/key" 
	@${RM} ${OBJECTDIR}/key/key_2.o.d 
	@${RM} ${OBJECTDIR}/key/key_2.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/key/key_2.o.d" -MT "${OBJECTDIR}/key/key_2.o.d" -MT ${OBJECTDIR}/key/key_2.o  -o ${OBJECTDIR}/key/key_2.o key/key_2.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/KEYBOARD/KEYBOARD_API/KeyboardAPI_1.o: KEYBOARD/KEYBOARD_API/KeyboardAPI_1.c  .generated_files/a87d7f723477ec25936f979d3e3547aeb835aedb.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/KEYBOARD/KEYBOARD_API" 
	@${RM} ${OBJECTDIR}/KEYBOARD/KEYBOARD_API/KeyboardAPI_1.o.d 
	@${RM} ${OBJECTDIR}/KEYBOARD/KEYBOARD_API/KeyboardAPI_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/KEYBOARD/KEYBOARD_API/KeyboardAPI_1.o.d" -MT "${OBJECTDIR}/KEYBOARD/KEYBOARD_API/KeyboardAPI_1.o.d" -MT ${OBJECTDIR}/KEYBOARD/KEYBOARD_API/KeyboardAPI_1.o  -o ${OBJECTDIR}/KEYBOARD/KEYBOARD_API/KeyboardAPI_1.o KEYBOARD/KEYBOARD_API/KeyboardAPI_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/KEYBOARD/DEBUG_TestKeyboard.o: KEYBOARD/DEBUG_TestKeyboard.c  .generated_files/82fe3af781e651d65bde0156d38c4b31c7af3f6.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/KEYBOARD" 
	@${RM} ${OBJECTDIR}/KEYBOARD/DEBUG_TestKeyboard.o.d 
	@${RM} ${OBJECTDIR}/KEYBOARD/DEBUG_TestKeyboard.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/KEYBOARD/DEBUG_TestKeyboard.o.d" -MT "${OBJECTDIR}/KEYBOARD/DEBUG_TestKeyboard.o.d" -MT ${OBJECTDIR}/KEYBOARD/DEBUG_TestKeyboard.o  -o ${OBJECTDIR}/KEYBOARD/DEBUG_TestKeyboard.o KEYBOARD/DEBUG_TestKeyboard.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/KEYBOARD/KeyboardHandler_1.o: KEYBOARD/KeyboardHandler_1.c  .generated_files/dfda49e6ac9e9e73e1646c89fc1523dc500c9ce6.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/KEYBOARD" 
	@${RM} ${OBJECTDIR}/KEYBOARD/KeyboardHandler_1.o.d 
	@${RM} ${OBJECTDIR}/KEYBOARD/KeyboardHandler_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/KEYBOARD/KeyboardHandler_1.o.d" -MT "${OBJECTDIR}/KEYBOARD/KeyboardHandler_1.o.d" -MT ${OBJECTDIR}/KEYBOARD/KeyboardHandler_1.o  -o ${OBJECTDIR}/KEYBOARD/KeyboardHandler_1.o KEYBOARD/KeyboardHandler_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/MENU/ClaseMenu/ClaseMenu_3.o: MENU/ClaseMenu/ClaseMenu_3.c  .generated_files/31311d8e71238d0ae6ec78fefff480f52e2ebed1.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/MENU/ClaseMenu" 
	@${RM} ${OBJECTDIR}/MENU/ClaseMenu/ClaseMenu_3.o.d 
	@${RM} ${OBJECTDIR}/MENU/ClaseMenu/ClaseMenu_3.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/MENU/ClaseMenu/ClaseMenu_3.o.d" -MT "${OBJECTDIR}/MENU/ClaseMenu/ClaseMenu_3.o.d" -MT ${OBJECTDIR}/MENU/ClaseMenu/ClaseMenu_3.o  -o ${OBJECTDIR}/MENU/ClaseMenu/ClaseMenu_3.o MENU/ClaseMenu/ClaseMenu_3.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/MENU/MenuDimming6Zonas/MenuDimming6Zonas_4.o: MENU/MenuDimming6Zonas/MenuDimming6Zonas_4.c  .generated_files/c0383e3f3c3cf22e102416eb0180ea931983c156.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/MENU/MenuDimming6Zonas" 
	@${RM} ${OBJECTDIR}/MENU/MenuDimming6Zonas/MenuDimming6Zonas_4.o.d 
	@${RM} ${OBJECTDIR}/MENU/MenuDimming6Zonas/MenuDimming6Zonas_4.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/MENU/MenuDimming6Zonas/MenuDimming6Zonas_4.o.d" -MT "${OBJECTDIR}/MENU/MenuDimming6Zonas/MenuDimming6Zonas_4.o.d" -MT ${OBJECTDIR}/MENU/MenuDimming6Zonas/MenuDimming6Zonas_4.o  -o ${OBJECTDIR}/MENU/MenuDimming6Zonas/MenuDimming6Zonas_4.o MENU/MenuDimming6Zonas/MenuDimming6Zonas_4.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/MENU/MenuScene/MenuScene_3.o: MENU/MenuScene/MenuScene_3.c  .generated_files/a75cf6ed324b5f8a1f08270ca84a7fc681f290cd.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/MENU/MenuScene" 
	@${RM} ${OBJECTDIR}/MENU/MenuScene/MenuScene_3.o.d 
	@${RM} ${OBJECTDIR}/MENU/MenuScene/MenuScene_3.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/MENU/MenuScene/MenuScene_3.o.d" -MT "${OBJECTDIR}/MENU/MenuScene/MenuScene_3.o.d" -MT ${OBJECTDIR}/MENU/MenuScene/MenuScene_3.o  -o ${OBJECTDIR}/MENU/MenuScene/MenuScene_3.o MENU/MenuScene/MenuScene_3.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/MENU/MenuSelectDimmNoDimmLoad/MenuSelectDimmNoDimmLoad_1.o: MENU/MenuSelectDimmNoDimmLoad/MenuSelectDimmNoDimmLoad_1.c  .generated_files/c71f6e892c025f7f8835f406fdc0c76c0e453bf8.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/MENU/MenuSelectDimmNoDimmLoad" 
	@${RM} ${OBJECTDIR}/MENU/MenuSelectDimmNoDimmLoad/MenuSelectDimmNoDimmLoad_1.o.d 
	@${RM} ${OBJECTDIR}/MENU/MenuSelectDimmNoDimmLoad/MenuSelectDimmNoDimmLoad_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/MENU/MenuSelectDimmNoDimmLoad/MenuSelectDimmNoDimmLoad_1.o.d" -MT "${OBJECTDIR}/MENU/MenuSelectDimmNoDimmLoad/MenuSelectDimmNoDimmLoad_1.o.d" -MT ${OBJECTDIR}/MENU/MenuSelectDimmNoDimmLoad/MenuSelectDimmNoDimmLoad_1.o  -o ${OBJECTDIR}/MENU/MenuSelectDimmNoDimmLoad/MenuSelectDimmNoDimmLoad_1.o MENU/MenuSelectDimmNoDimmLoad/MenuSelectDimmNoDimmLoad_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/ObjControl/DialogBox/DialogBox_1.o: ObjControl/DialogBox/DialogBox_1.c  .generated_files/19338ea0b4fcd548d92d0c7a7aad27d5ab3c7fea.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/ObjControl/DialogBox" 
	@${RM} ${OBJECTDIR}/ObjControl/DialogBox/DialogBox_1.o.d 
	@${RM} ${OBJECTDIR}/ObjControl/DialogBox/DialogBox_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/ObjControl/DialogBox/DialogBox_1.o.d" -MT "${OBJECTDIR}/ObjControl/DialogBox/DialogBox_1.o.d" -MT ${OBJECTDIR}/ObjControl/DialogBox/DialogBox_1.o  -o ${OBJECTDIR}/ObjControl/DialogBox/DialogBox_1.o ObjControl/DialogBox/DialogBox_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/ObjControl/List/ListBox_1.o: ObjControl/List/ListBox_1.c  .generated_files/526fce11ef1e86d96b01ea1ad9bcf17f840e9641.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/ObjControl/List" 
	@${RM} ${OBJECTDIR}/ObjControl/List/ListBox_1.o.d 
	@${RM} ${OBJECTDIR}/ObjControl/List/ListBox_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/ObjControl/List/ListBox_1.o.d" -MT "${OBJECTDIR}/ObjControl/List/ListBox_1.o.d" -MT ${OBJECTDIR}/ObjControl/List/ListBox_1.o  -o ${OBJECTDIR}/ObjControl/List/ListBox_1.o ObjControl/List/ListBox_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/ObjControl/RadioButton/RadioButton_1.o: ObjControl/RadioButton/RadioButton_1.c  .generated_files/155a8cab5eecb063845cecd0655abc1815cd753d.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/ObjControl/RadioButton" 
	@${RM} ${OBJECTDIR}/ObjControl/RadioButton/RadioButton_1.o.d 
	@${RM} ${OBJECTDIR}/ObjControl/RadioButton/RadioButton_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/ObjControl/RadioButton/RadioButton_1.o.d" -MT "${OBJECTDIR}/ObjControl/RadioButton/RadioButton_1.o.d" -MT ${OBJECTDIR}/ObjControl/RadioButton/RadioButton_1.o  -o ${OBJECTDIR}/ObjControl/RadioButton/RadioButton_1.o ObjControl/RadioButton/RadioButton_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/PLAYSOUND/PlaySound_1.o: PLAYSOUND/PlaySound_1.c  .generated_files/9516e662420bb01fac6219b53a9ff674be0b562a.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/PLAYSOUND" 
	@${RM} ${OBJECTDIR}/PLAYSOUND/PlaySound_1.o.d 
	@${RM} ${OBJECTDIR}/PLAYSOUND/PlaySound_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/PLAYSOUND/PlaySound_1.o.d" -MT "${OBJECTDIR}/PLAYSOUND/PlaySound_1.o.d" -MT ${OBJECTDIR}/PLAYSOUND/PlaySound_1.o  -o ${OBJECTDIR}/PLAYSOUND/PlaySound_1.o PLAYSOUND/PlaySound_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/PWM/PWM_1.o: PWM/PWM_1.c  .generated_files/1d86d6d994042348ba5686967f05131d8380efb8.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/PWM" 
	@${RM} ${OBJECTDIR}/PWM/PWM_1.o.d 
	@${RM} ${OBJECTDIR}/PWM/PWM_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/PWM/PWM_1.o.d" -MT "${OBJECTDIR}/PWM/PWM_1.o.d" -MT ${OBJECTDIR}/PWM/PWM_1.o  -o ${OBJECTDIR}/PWM/PWM_1.o PWM/PWM_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/RS485/RS485_1.o: RS485/RS485_1.c  .generated_files/667e557b1ee4e1cf1b385564823a1943b95259a4.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/RS485" 
	@${RM} ${OBJECTDIR}/RS485/RS485_1.o.d 
	@${RM} ${OBJECTDIR}/RS485/RS485_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/RS485/RS485_1.o.d" -MT "${OBJECTDIR}/RS485/RS485_1.o.d" -MT ${OBJECTDIR}/RS485/RS485_1.o  -o ${OBJECTDIR}/RS485/RS485_1.o RS485/RS485_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/SHELL/Shell_5.o: SHELL/Shell_5.c  .generated_files/96c05bed12c3d020ea64cab83502f3e9a6eea061.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/SHELL" 
	@${RM} ${OBJECTDIR}/SHELL/Shell_5.o.d 
	@${RM} ${OBJECTDIR}/SHELL/Shell_5.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/SHELL/Shell_5.o.d" -MT "${OBJECTDIR}/SHELL/Shell_5.o.d" -MT ${OBJECTDIR}/SHELL/Shell_5.o  -o ${OBJECTDIR}/SHELL/Shell_5.o SHELL/Shell_5.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/TIMEDATE/TimeDate_2.o: TIMEDATE/TimeDate_2.c  .generated_files/4bed58820733ab80941300e26db8b65ff2f896d0.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/TIMEDATE" 
	@${RM} ${OBJECTDIR}/TIMEDATE/TimeDate_2.o.d 
	@${RM} ${OBJECTDIR}/TIMEDATE/TimeDate_2.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/TIMEDATE/TimeDate_2.o.d" -MT "${OBJECTDIR}/TIMEDATE/TimeDate_2.o.d" -MT ${OBJECTDIR}/TIMEDATE/TimeDate_2.o  -o ${OBJECTDIR}/TIMEDATE/TimeDate_2.o TIMEDATE/TimeDate_2.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/TIMMER_NB/Timmer_nb_1.o: TIMMER_NB/Timmer_nb_1.c  .generated_files/e993ab53258a096c4430989254a43d660f8bd862.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/TIMMER_NB" 
	@${RM} ${OBJECTDIR}/TIMMER_NB/Timmer_nb_1.o.d 
	@${RM} ${OBJECTDIR}/TIMMER_NB/Timmer_nb_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/TIMMER_NB/Timmer_nb_1.o.d" -MT "${OBJECTDIR}/TIMMER_NB/Timmer_nb_1.o.d" -MT ${OBJECTDIR}/TIMMER_NB/Timmer_nb_1.o  -o ${OBJECTDIR}/TIMMER_NB/Timmer_nb_1.o TIMMER_NB/Timmer_nb_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/ZONA/NamingZone/NamingZone_2.o: ZONA/NamingZone/NamingZone_2.c  .generated_files/fafeafb3c8408e53e726c7b1ab23552b344b3600.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/ZONA/NamingZone" 
	@${RM} ${OBJECTDIR}/ZONA/NamingZone/NamingZone_2.o.d 
	@${RM} ${OBJECTDIR}/ZONA/NamingZone/NamingZone_2.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/ZONA/NamingZone/NamingZone_2.o.d" -MT "${OBJECTDIR}/ZONA/NamingZone/NamingZone_2.o.d" -MT ${OBJECTDIR}/ZONA/NamingZone/NamingZone_2.o  -o ${OBJECTDIR}/ZONA/NamingZone/NamingZone_2.o ZONA/NamingZone/NamingZone_2.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/ZONA/Zona_1.o: ZONA/Zona_1.c  .generated_files/991e86048693b5b00c2080e855be320c48dddc57.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/ZONA" 
	@${RM} ${OBJECTDIR}/ZONA/Zona_1.o.d 
	@${RM} ${OBJECTDIR}/ZONA/Zona_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/ZONA/Zona_1.o.d" -MT "${OBJECTDIR}/ZONA/Zona_1.o.d" -MT ${OBJECTDIR}/ZONA/Zona_1.o  -o ${OBJECTDIR}/ZONA/Zona_1.o ZONA/Zona_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/BUZZER/Buzzer_1.o: BUZZER/Buzzer_1.c  .generated_files/41453db5c5854918f74c4f8caa0f6b63fafcca0d.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/BUZZER" 
	@${RM} ${OBJECTDIR}/BUZZER/Buzzer_1.o.d 
	@${RM} ${OBJECTDIR}/BUZZER/Buzzer_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/BUZZER/Buzzer_1.o.d" -MT "${OBJECTDIR}/BUZZER/Buzzer_1.o.d" -MT ${OBJECTDIR}/BUZZER/Buzzer_1.o  -o ${OBJECTDIR}/BUZZER/Buzzer_1.o BUZZER/Buzzer_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/EEPROM/EEPROM.o: EEPROM/EEPROM.c  .generated_files/1055e3466a690a2659f6e3bd8b6c32b4fb323e4f.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/EEPROM" 
	@${RM} ${OBJECTDIR}/EEPROM/EEPROM.o.d 
	@${RM} ${OBJECTDIR}/EEPROM/EEPROM.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/EEPROM/EEPROM.o.d" -MT "${OBJECTDIR}/EEPROM/EEPROM.o.d" -MT ${OBJECTDIR}/EEPROM/EEPROM.o  -o ${OBJECTDIR}/EEPROM/EEPROM.o EEPROM/EEPROM.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/GLCD192X64/GLCD192x64_01.o: GLCD192X64/GLCD192x64_01.c  .generated_files/900ecadded84430a10b778887cbae3c86874205b.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/GLCD192X64" 
	@${RM} ${OBJECTDIR}/GLCD192X64/GLCD192x64_01.o.d 
	@${RM} ${OBJECTDIR}/GLCD192X64/GLCD192x64_01.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/GLCD192X64/GLCD192x64_01.o.d" -MT "${OBJECTDIR}/GLCD192X64/GLCD192x64_01.o.d" -MT ${OBJECTDIR}/GLCD192X64/GLCD192x64_01.o  -o ${OBJECTDIR}/GLCD192X64/GLCD192x64_01.o GLCD192X64/GLCD192x64_01.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/GLCD192X64/GLCD_fxs_1.o: GLCD192X64/GLCD_fxs_1.c  .generated_files/5fa6f73552395eff2ebff144bda487808cb8225d.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/GLCD192X64" 
	@${RM} ${OBJECTDIR}/GLCD192X64/GLCD_fxs_1.o.d 
	@${RM} ${OBJECTDIR}/GLCD192X64/GLCD_fxs_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/GLCD192X64/GLCD_fxs_1.o.d" -MT "${OBJECTDIR}/GLCD192X64/GLCD_fxs_1.o.d" -MT ${OBJECTDIR}/GLCD192X64/GLCD_fxs_1.o  -o ${OBJECTDIR}/GLCD192X64/GLCD_fxs_1.o GLCD192X64/GLCD_fxs_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/I2C/I2CCommonFx.o: I2C/I2CCommonFx.c  .generated_files/30720b9a46dc21ef84f36e97dfe8e08bb4296fb0.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/I2C" 
	@${RM} ${OBJECTDIR}/I2C/I2CCommonFx.o.d 
	@${RM} ${OBJECTDIR}/I2C/I2CCommonFx.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/I2C/I2CCommonFx.o.d" -MT "${OBJECTDIR}/I2C/I2CCommonFx.o.d" -MT ${OBJECTDIR}/I2C/I2CCommonFx.o  -o ${OBJECTDIR}/I2C/I2CCommonFx.o I2C/I2CCommonFx.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/I2C/I2C_01.o: I2C/I2C_01.c  .generated_files/b034511e4807d0cd152725c0517bd1dcee35046.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/I2C" 
	@${RM} ${OBJECTDIR}/I2C/I2C_01.o.d 
	@${RM} ${OBJECTDIR}/I2C/I2C_01.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/I2C/I2C_01.o.d" -MT "${OBJECTDIR}/I2C/I2C_01.o.d" -MT ${OBJECTDIR}/I2C/I2C_01.o  -o ${OBJECTDIR}/I2C/I2C_01.o I2C/I2C_01.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/main1.o: main1.c  .generated_files/8e6ec1dd58308a3a954b9ccda862272eb10fca00.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main1.o.d 
	@${RM} ${OBJECTDIR}/main1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/main1.o.d" -MT "${OBJECTDIR}/main1.o.d" -MT ${OBJECTDIR}/main1.o  -o ${OBJECTDIR}/main1.o main1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/TCNT0/TCNT0_01.o: TCNT0/TCNT0_01.c  .generated_files/9204f8435f89f4ca34a07e9313d3b002c6d66cef.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/TCNT0" 
	@${RM} ${OBJECTDIR}/TCNT0/TCNT0_01.o.d 
	@${RM} ${OBJECTDIR}/TCNT0/TCNT0_01.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/TCNT0/TCNT0_01.o.d" -MT "${OBJECTDIR}/TCNT0/TCNT0_01.o.d" -MT ${OBJECTDIR}/TCNT0/TCNT0_01.o  -o ${OBJECTDIR}/TCNT0/TCNT0_01.o TCNT0/TCNT0_01.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/USART/USART_01.o: USART/USART_01.c  .generated_files/ee0a0856eeabea18ea97d46b78d12619fbfe224c.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/USART" 
	@${RM} ${OBJECTDIR}/USART/USART_01.o.d 
	@${RM} ${OBJECTDIR}/USART/USART_01.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/USART/USART_01.o.d" -MT "${OBJECTDIR}/USART/USART_01.o.d" -MT ${OBJECTDIR}/USART/USART_01.o  -o ${OBJECTDIR}/USART/USART_01.o USART/USART_01.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/KS108v1/ks0108.o: KS108v1/ks0108.c  .generated_files/3c7d9c23dc5479e9986f4fbea41e95aa96005099.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/KS108v1" 
	@${RM} ${OBJECTDIR}/KS108v1/ks0108.o.d 
	@${RM} ${OBJECTDIR}/KS108v1/ks0108.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/KS108v1/ks0108.o.d" -MT "${OBJECTDIR}/KS108v1/ks0108.o.d" -MT ${OBJECTDIR}/KS108v1/ks0108.o  -o ${OBJECTDIR}/KS108v1/ks0108.o KS108v1/ks0108.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/KS108v1/FONTS/SC.o: KS108v1/FONTS/SC.c  .generated_files/cf30f6cf72dbb55c19f89415a800c8f693c2961c.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/KS108v1/FONTS" 
	@${RM} ${OBJECTDIR}/KS108v1/FONTS/SC.o.d 
	@${RM} ${OBJECTDIR}/KS108v1/FONTS/SC.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/KS108v1/FONTS/SC.o.d" -MT "${OBJECTDIR}/KS108v1/FONTS/SC.o.d" -MT ${OBJECTDIR}/KS108v1/FONTS/SC.o  -o ${OBJECTDIR}/KS108v1/FONTS/SC.o KS108v1/FONTS/SC.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/KS108v1/FONTS/arial_bold_14.o: KS108v1/FONTS/arial_bold_14.c  .generated_files/7d49f6ed6cc10455a40a01572e8140fb86cdf785.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/KS108v1/FONTS" 
	@${RM} ${OBJECTDIR}/KS108v1/FONTS/arial_bold_14.o.d 
	@${RM} ${OBJECTDIR}/KS108v1/FONTS/arial_bold_14.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/KS108v1/FONTS/arial_bold_14.o.d" -MT "${OBJECTDIR}/KS108v1/FONTS/arial_bold_14.o.d" -MT ${OBJECTDIR}/KS108v1/FONTS/arial_bold_14.o  -o ${OBJECTDIR}/KS108v1/FONTS/arial_bold_14.o KS108v1/FONTS/arial_bold_14.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/KS108v1/FONTS/corsiva_12.o: KS108v1/FONTS/corsiva_12.c  .generated_files/68cdec27e92e94dc6ec0425e7d904ae4133b0857.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/KS108v1/FONTS" 
	@${RM} ${OBJECTDIR}/KS108v1/FONTS/corsiva_12.o.d 
	@${RM} ${OBJECTDIR}/KS108v1/FONTS/corsiva_12.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/KS108v1/FONTS/corsiva_12.o.d" -MT "${OBJECTDIR}/KS108v1/FONTS/corsiva_12.o.d" -MT ${OBJECTDIR}/KS108v1/FONTS/corsiva_12.o  -o ${OBJECTDIR}/KS108v1/FONTS/corsiva_12.o KS108v1/FONTS/corsiva_12.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
else
${OBJECTDIR}/ADC/ADC1.o: ADC/ADC1.c  .generated_files/ea41456601063e75d647a8cc934c8634f64da2fa.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/ADC" 
	@${RM} ${OBJECTDIR}/ADC/ADC1.o.d 
	@${RM} ${OBJECTDIR}/ADC/ADC1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/ADC/ADC1.o.d" -MT "${OBJECTDIR}/ADC/ADC1.o.d" -MT ${OBJECTDIR}/ADC/ADC1.o  -o ${OBJECTDIR}/ADC/ADC1.o ADC/ADC1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/CommonProcess/keyboardApp/keyboard_app1.o: CommonProcess/keyboardApp/keyboard_app1.c  .generated_files/acb1c460b03c2f343c4b3ede956750b03fd690a8.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/CommonProcess/keyboardApp" 
	@${RM} ${OBJECTDIR}/CommonProcess/keyboardApp/keyboard_app1.o.d 
	@${RM} ${OBJECTDIR}/CommonProcess/keyboardApp/keyboard_app1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/CommonProcess/keyboardApp/keyboard_app1.o.d" -MT "${OBJECTDIR}/CommonProcess/keyboardApp/keyboard_app1.o.d" -MT ${OBJECTDIR}/CommonProcess/keyboardApp/keyboard_app1.o  -o ${OBJECTDIR}/CommonProcess/keyboardApp/keyboard_app1.o CommonProcess/keyboardApp/keyboard_app1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/CommonProcess/TimmerApp/TimerApp_1.o: CommonProcess/TimmerApp/TimerApp_1.c  .generated_files/85fa317cfbda8ac49c679c03f5dbf40f0c647a81.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/CommonProcess/TimmerApp" 
	@${RM} ${OBJECTDIR}/CommonProcess/TimmerApp/TimerApp_1.o.d 
	@${RM} ${OBJECTDIR}/CommonProcess/TimmerApp/TimerApp_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/CommonProcess/TimmerApp/TimerApp_1.o.d" -MT "${OBJECTDIR}/CommonProcess/TimmerApp/TimerApp_1.o.d" -MT ${OBJECTDIR}/CommonProcess/TimmerApp/TimerApp_1.o  -o ${OBJECTDIR}/CommonProcess/TimmerApp/TimerApp_1.o CommonProcess/TimmerApp/TimerApp_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/CommonProcess/CommonToProcess_1.o: CommonProcess/CommonToProcess_1.c  .generated_files/6218ae497cfbc05a38e640fa8b62cd17de0f1a2e.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/CommonProcess" 
	@${RM} ${OBJECTDIR}/CommonProcess/CommonToProcess_1.o.d 
	@${RM} ${OBJECTDIR}/CommonProcess/CommonToProcess_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/CommonProcess/CommonToProcess_1.o.d" -MT "${OBJECTDIR}/CommonProcess/CommonToProcess_1.o.d" -MT ${OBJECTDIR}/CommonProcess/CommonToProcess_1.o  -o ${OBJECTDIR}/CommonProcess/CommonToProcess_1.o CommonProcess/CommonToProcess_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/db_name_vocabulary/dbname_voc_1.o: db_name_vocabulary/dbname_voc_1.c  .generated_files/9f155c316e5e258fb8eca25be6d1b56232de54ae.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/db_name_vocabulary" 
	@${RM} ${OBJECTDIR}/db_name_vocabulary/dbname_voc_1.o.d 
	@${RM} ${OBJECTDIR}/db_name_vocabulary/dbname_voc_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/db_name_vocabulary/dbname_voc_1.o.d" -MT "${OBJECTDIR}/db_name_vocabulary/dbname_voc_1.o.d" -MT ${OBJECTDIR}/db_name_vocabulary/dbname_voc_1.o  -o ${OBJECTDIR}/db_name_vocabulary/dbname_voc_1.o db_name_vocabulary/dbname_voc_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/DimmBackLightGLCD/DimmBLGLCD_1.o: DimmBackLightGLCD/DimmBLGLCD_1.c  .generated_files/65964f7d57f44e033cbb810bdca1e5aa4ab96f8b.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/DimmBackLightGLCD" 
	@${RM} ${OBJECTDIR}/DimmBackLightGLCD/DimmBLGLCD_1.o.d 
	@${RM} ${OBJECTDIR}/DimmBackLightGLCD/DimmBLGLCD_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/DimmBackLightGLCD/DimmBLGLCD_1.o.d" -MT "${OBJECTDIR}/DimmBackLightGLCD/DimmBLGLCD_1.o.d" -MT ${OBJECTDIR}/DimmBackLightGLCD/DimmBLGLCD_1.o  -o ${OBJECTDIR}/DimmBackLightGLCD/DimmBLGLCD_1.o DimmBackLightGLCD/DimmBLGLCD_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/DIMMING/Dimming_1.o: DIMMING/Dimming_1.c  .generated_files/62a03100a47a22a7874b41e901959b4961e41a25.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/DIMMING" 
	@${RM} ${OBJECTDIR}/DIMMING/Dimming_1.o.d 
	@${RM} ${OBJECTDIR}/DIMMING/Dimming_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/DIMMING/Dimming_1.o.d" -MT "${OBJECTDIR}/DIMMING/Dimming_1.o.d" -MT ${OBJECTDIR}/DIMMING/Dimming_1.o  -o ${OBJECTDIR}/DIMMING/Dimming_1.o DIMMING/Dimming_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/DS3231/DS3231_1.o: DS3231/DS3231_1.c  .generated_files/ba44457cf1390548f36be9772c9eead400f808d6.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/DS3231" 
	@${RM} ${OBJECTDIR}/DS3231/DS3231_1.o.d 
	@${RM} ${OBJECTDIR}/DS3231/DS3231_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/DS3231/DS3231_1.o.d" -MT "${OBJECTDIR}/DS3231/DS3231_1.o.d" -MT ${OBJECTDIR}/DS3231/DS3231_1.o  -o ${OBJECTDIR}/DS3231/DS3231_1.o DS3231/DS3231_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/EFFECTS/BLINKING/Blinking_2.o: EFFECTS/BLINKING/Blinking_2.c  .generated_files/819f33e06e338613cd5ae3725bf16fde0371c0c7.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/EFFECTS/BLINKING" 
	@${RM} ${OBJECTDIR}/EFFECTS/BLINKING/Blinking_2.o.d 
	@${RM} ${OBJECTDIR}/EFFECTS/BLINKING/Blinking_2.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/EFFECTS/BLINKING/Blinking_2.o.d" -MT "${OBJECTDIR}/EFFECTS/BLINKING/Blinking_2.o.d" -MT ${OBJECTDIR}/EFFECTS/BLINKING/Blinking_2.o  -o ${OBJECTDIR}/EFFECTS/BLINKING/Blinking_2.o EFFECTS/BLINKING/Blinking_2.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/ESCENAS/EliminarEscena_1.o: ESCENAS/EliminarEscena_1.c  .generated_files/7526f1e7041a0a1ba89d00739592175eee43908d.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/ESCENAS" 
	@${RM} ${OBJECTDIR}/ESCENAS/EliminarEscena_1.o.d 
	@${RM} ${OBJECTDIR}/ESCENAS/EliminarEscena_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/ESCENAS/EliminarEscena_1.o.d" -MT "${OBJECTDIR}/ESCENAS/EliminarEscena_1.o.d" -MT ${OBJECTDIR}/ESCENAS/EliminarEscena_1.o  -o ${OBJECTDIR}/ESCENAS/EliminarEscena_1.o ESCENAS/EliminarEscena_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/ESCENAS/Escenas_2.o: ESCENAS/Escenas_2.c  .generated_files/a58d143058180980b00ec8838c94eb4c004a5067.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/ESCENAS" 
	@${RM} ${OBJECTDIR}/ESCENAS/Escenas_2.o.d 
	@${RM} ${OBJECTDIR}/ESCENAS/Escenas_2.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/ESCENAS/Escenas_2.o.d" -MT "${OBJECTDIR}/ESCENAS/Escenas_2.o.d" -MT ${OBJECTDIR}/ESCENAS/Escenas_2.o  -o ${OBJECTDIR}/ESCENAS/Escenas_2.o ESCENAS/Escenas_2.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/ESCENAS/ModificarEscena_1.o: ESCENAS/ModificarEscena_1.c  .generated_files/3dbe740c413e2dad8f9a7ea75b19740b85092a2.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/ESCENAS" 
	@${RM} ${OBJECTDIR}/ESCENAS/ModificarEscena_1.o.d 
	@${RM} ${OBJECTDIR}/ESCENAS/ModificarEscena_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/ESCENAS/ModificarEscena_1.o.d" -MT "${OBJECTDIR}/ESCENAS/ModificarEscena_1.o.d" -MT ${OBJECTDIR}/ESCENAS/ModificarEscena_1.o  -o ${OBJECTDIR}/ESCENAS/ModificarEscena_1.o ESCENAS/ModificarEscena_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/ESCENAS/NuevaEscena_2.o: ESCENAS/NuevaEscena_2.c  .generated_files/1b2ff991e88c8200ef4a71678a760f7dcc3c6172.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/ESCENAS" 
	@${RM} ${OBJECTDIR}/ESCENAS/NuevaEscena_2.o.d 
	@${RM} ${OBJECTDIR}/ESCENAS/NuevaEscena_2.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/ESCENAS/NuevaEscena_2.o.d" -MT "${OBJECTDIR}/ESCENAS/NuevaEscena_2.o.d" -MT ${OBJECTDIR}/ESCENAS/NuevaEscena_2.o  -o ${OBJECTDIR}/ESCENAS/NuevaEscena_2.o ESCENAS/NuevaEscena_2.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/FADING/Fading_1.o: FADING/Fading_1.c  .generated_files/a32704e574f0fcc12e7dcd9d590d1823d75419f9.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/FADING" 
	@${RM} ${OBJECTDIR}/FADING/Fading_1.o.d 
	@${RM} ${OBJECTDIR}/FADING/Fading_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/FADING/Fading_1.o.d" -MT "${OBJECTDIR}/FADING/Fading_1.o.d" -MT ${OBJECTDIR}/FADING/Fading_1.o  -o ${OBJECTDIR}/FADING/Fading_1.o FADING/Fading_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/GUI/GUI_1.o: GUI/GUI_1.c  .generated_files/d7613cf4188d6f03092c7cc102e8d82150e45250.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/GUI" 
	@${RM} ${OBJECTDIR}/GUI/GUI_1.o.d 
	@${RM} ${OBJECTDIR}/GUI/GUI_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/GUI/GUI_1.o.d" -MT "${OBJECTDIR}/GUI/GUI_1.o.d" -MT ${OBJECTDIR}/GUI/GUI_1.o  -o ${OBJECTDIR}/GUI/GUI_1.o GUI/GUI_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/key/key_2.o: key/key_2.c  .generated_files/cab7fc930d5a21fb40062073cdccfc00ecdfc617.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/key" 
	@${RM} ${OBJECTDIR}/key/key_2.o.d 
	@${RM} ${OBJECTDIR}/key/key_2.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/key/key_2.o.d" -MT "${OBJECTDIR}/key/key_2.o.d" -MT ${OBJECTDIR}/key/key_2.o  -o ${OBJECTDIR}/key/key_2.o key/key_2.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/KEYBOARD/KEYBOARD_API/KeyboardAPI_1.o: KEYBOARD/KEYBOARD_API/KeyboardAPI_1.c  .generated_files/b83071f7ef2f39f8a5c6c99380ede1009682d482.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/KEYBOARD/KEYBOARD_API" 
	@${RM} ${OBJECTDIR}/KEYBOARD/KEYBOARD_API/KeyboardAPI_1.o.d 
	@${RM} ${OBJECTDIR}/KEYBOARD/KEYBOARD_API/KeyboardAPI_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/KEYBOARD/KEYBOARD_API/KeyboardAPI_1.o.d" -MT "${OBJECTDIR}/KEYBOARD/KEYBOARD_API/KeyboardAPI_1.o.d" -MT ${OBJECTDIR}/KEYBOARD/KEYBOARD_API/KeyboardAPI_1.o  -o ${OBJECTDIR}/KEYBOARD/KEYBOARD_API/KeyboardAPI_1.o KEYBOARD/KEYBOARD_API/KeyboardAPI_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/KEYBOARD/DEBUG_TestKeyboard.o: KEYBOARD/DEBUG_TestKeyboard.c  .generated_files/ac30b2d56e57d7b2f4141b6ac13314c8b9a4960b.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/KEYBOARD" 
	@${RM} ${OBJECTDIR}/KEYBOARD/DEBUG_TestKeyboard.o.d 
	@${RM} ${OBJECTDIR}/KEYBOARD/DEBUG_TestKeyboard.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/KEYBOARD/DEBUG_TestKeyboard.o.d" -MT "${OBJECTDIR}/KEYBOARD/DEBUG_TestKeyboard.o.d" -MT ${OBJECTDIR}/KEYBOARD/DEBUG_TestKeyboard.o  -o ${OBJECTDIR}/KEYBOARD/DEBUG_TestKeyboard.o KEYBOARD/DEBUG_TestKeyboard.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/KEYBOARD/KeyboardHandler_1.o: KEYBOARD/KeyboardHandler_1.c  .generated_files/2fea50277747670f20c70eeb997b44f72e9bec07.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/KEYBOARD" 
	@${RM} ${OBJECTDIR}/KEYBOARD/KeyboardHandler_1.o.d 
	@${RM} ${OBJECTDIR}/KEYBOARD/KeyboardHandler_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/KEYBOARD/KeyboardHandler_1.o.d" -MT "${OBJECTDIR}/KEYBOARD/KeyboardHandler_1.o.d" -MT ${OBJECTDIR}/KEYBOARD/KeyboardHandler_1.o  -o ${OBJECTDIR}/KEYBOARD/KeyboardHandler_1.o KEYBOARD/KeyboardHandler_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/MENU/ClaseMenu/ClaseMenu_3.o: MENU/ClaseMenu/ClaseMenu_3.c  .generated_files/992d0613146dde844bf0ff244faecaff1b1e3d6a.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/MENU/ClaseMenu" 
	@${RM} ${OBJECTDIR}/MENU/ClaseMenu/ClaseMenu_3.o.d 
	@${RM} ${OBJECTDIR}/MENU/ClaseMenu/ClaseMenu_3.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/MENU/ClaseMenu/ClaseMenu_3.o.d" -MT "${OBJECTDIR}/MENU/ClaseMenu/ClaseMenu_3.o.d" -MT ${OBJECTDIR}/MENU/ClaseMenu/ClaseMenu_3.o  -o ${OBJECTDIR}/MENU/ClaseMenu/ClaseMenu_3.o MENU/ClaseMenu/ClaseMenu_3.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/MENU/MenuDimming6Zonas/MenuDimming6Zonas_4.o: MENU/MenuDimming6Zonas/MenuDimming6Zonas_4.c  .generated_files/6344253c078ce9ccd617cb2f78fa88d448923f0a.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/MENU/MenuDimming6Zonas" 
	@${RM} ${OBJECTDIR}/MENU/MenuDimming6Zonas/MenuDimming6Zonas_4.o.d 
	@${RM} ${OBJECTDIR}/MENU/MenuDimming6Zonas/MenuDimming6Zonas_4.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/MENU/MenuDimming6Zonas/MenuDimming6Zonas_4.o.d" -MT "${OBJECTDIR}/MENU/MenuDimming6Zonas/MenuDimming6Zonas_4.o.d" -MT ${OBJECTDIR}/MENU/MenuDimming6Zonas/MenuDimming6Zonas_4.o  -o ${OBJECTDIR}/MENU/MenuDimming6Zonas/MenuDimming6Zonas_4.o MENU/MenuDimming6Zonas/MenuDimming6Zonas_4.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/MENU/MenuScene/MenuScene_3.o: MENU/MenuScene/MenuScene_3.c  .generated_files/e5908f2e935df039a48bff7b5892d759ca303ec5.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/MENU/MenuScene" 
	@${RM} ${OBJECTDIR}/MENU/MenuScene/MenuScene_3.o.d 
	@${RM} ${OBJECTDIR}/MENU/MenuScene/MenuScene_3.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/MENU/MenuScene/MenuScene_3.o.d" -MT "${OBJECTDIR}/MENU/MenuScene/MenuScene_3.o.d" -MT ${OBJECTDIR}/MENU/MenuScene/MenuScene_3.o  -o ${OBJECTDIR}/MENU/MenuScene/MenuScene_3.o MENU/MenuScene/MenuScene_3.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/MENU/MenuSelectDimmNoDimmLoad/MenuSelectDimmNoDimmLoad_1.o: MENU/MenuSelectDimmNoDimmLoad/MenuSelectDimmNoDimmLoad_1.c  .generated_files/8390dde57c54d5f1a49bf876816af713345a3317.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/MENU/MenuSelectDimmNoDimmLoad" 
	@${RM} ${OBJECTDIR}/MENU/MenuSelectDimmNoDimmLoad/MenuSelectDimmNoDimmLoad_1.o.d 
	@${RM} ${OBJECTDIR}/MENU/MenuSelectDimmNoDimmLoad/MenuSelectDimmNoDimmLoad_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/MENU/MenuSelectDimmNoDimmLoad/MenuSelectDimmNoDimmLoad_1.o.d" -MT "${OBJECTDIR}/MENU/MenuSelectDimmNoDimmLoad/MenuSelectDimmNoDimmLoad_1.o.d" -MT ${OBJECTDIR}/MENU/MenuSelectDimmNoDimmLoad/MenuSelectDimmNoDimmLoad_1.o  -o ${OBJECTDIR}/MENU/MenuSelectDimmNoDimmLoad/MenuSelectDimmNoDimmLoad_1.o MENU/MenuSelectDimmNoDimmLoad/MenuSelectDimmNoDimmLoad_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/ObjControl/DialogBox/DialogBox_1.o: ObjControl/DialogBox/DialogBox_1.c  .generated_files/b387d97fd0c47c72aa46c53e61b826c20aca6f7c.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/ObjControl/DialogBox" 
	@${RM} ${OBJECTDIR}/ObjControl/DialogBox/DialogBox_1.o.d 
	@${RM} ${OBJECTDIR}/ObjControl/DialogBox/DialogBox_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/ObjControl/DialogBox/DialogBox_1.o.d" -MT "${OBJECTDIR}/ObjControl/DialogBox/DialogBox_1.o.d" -MT ${OBJECTDIR}/ObjControl/DialogBox/DialogBox_1.o  -o ${OBJECTDIR}/ObjControl/DialogBox/DialogBox_1.o ObjControl/DialogBox/DialogBox_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/ObjControl/List/ListBox_1.o: ObjControl/List/ListBox_1.c  .generated_files/b7531e0c59d14a5ced543bae35816db7b951513e.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/ObjControl/List" 
	@${RM} ${OBJECTDIR}/ObjControl/List/ListBox_1.o.d 
	@${RM} ${OBJECTDIR}/ObjControl/List/ListBox_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/ObjControl/List/ListBox_1.o.d" -MT "${OBJECTDIR}/ObjControl/List/ListBox_1.o.d" -MT ${OBJECTDIR}/ObjControl/List/ListBox_1.o  -o ${OBJECTDIR}/ObjControl/List/ListBox_1.o ObjControl/List/ListBox_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/ObjControl/RadioButton/RadioButton_1.o: ObjControl/RadioButton/RadioButton_1.c  .generated_files/f911ed69c71aa13b53bf8efa505aba5ef7ae61e9.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/ObjControl/RadioButton" 
	@${RM} ${OBJECTDIR}/ObjControl/RadioButton/RadioButton_1.o.d 
	@${RM} ${OBJECTDIR}/ObjControl/RadioButton/RadioButton_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/ObjControl/RadioButton/RadioButton_1.o.d" -MT "${OBJECTDIR}/ObjControl/RadioButton/RadioButton_1.o.d" -MT ${OBJECTDIR}/ObjControl/RadioButton/RadioButton_1.o  -o ${OBJECTDIR}/ObjControl/RadioButton/RadioButton_1.o ObjControl/RadioButton/RadioButton_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/PLAYSOUND/PlaySound_1.o: PLAYSOUND/PlaySound_1.c  .generated_files/11aa49c929b5c2330c3e7dee8ce90ce5b73a77a3.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/PLAYSOUND" 
	@${RM} ${OBJECTDIR}/PLAYSOUND/PlaySound_1.o.d 
	@${RM} ${OBJECTDIR}/PLAYSOUND/PlaySound_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/PLAYSOUND/PlaySound_1.o.d" -MT "${OBJECTDIR}/PLAYSOUND/PlaySound_1.o.d" -MT ${OBJECTDIR}/PLAYSOUND/PlaySound_1.o  -o ${OBJECTDIR}/PLAYSOUND/PlaySound_1.o PLAYSOUND/PlaySound_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/PWM/PWM_1.o: PWM/PWM_1.c  .generated_files/6de26a63adceb2728285a15836e809963eaa255d.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/PWM" 
	@${RM} ${OBJECTDIR}/PWM/PWM_1.o.d 
	@${RM} ${OBJECTDIR}/PWM/PWM_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/PWM/PWM_1.o.d" -MT "${OBJECTDIR}/PWM/PWM_1.o.d" -MT ${OBJECTDIR}/PWM/PWM_1.o  -o ${OBJECTDIR}/PWM/PWM_1.o PWM/PWM_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/RS485/RS485_1.o: RS485/RS485_1.c  .generated_files/4a34c89af200fd6b91c67a9becf3958db3c38ca5.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/RS485" 
	@${RM} ${OBJECTDIR}/RS485/RS485_1.o.d 
	@${RM} ${OBJECTDIR}/RS485/RS485_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/RS485/RS485_1.o.d" -MT "${OBJECTDIR}/RS485/RS485_1.o.d" -MT ${OBJECTDIR}/RS485/RS485_1.o  -o ${OBJECTDIR}/RS485/RS485_1.o RS485/RS485_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/SHELL/Shell_5.o: SHELL/Shell_5.c  .generated_files/421b7bd2c20405734a2dc1664ed7737f3bbfcc90.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/SHELL" 
	@${RM} ${OBJECTDIR}/SHELL/Shell_5.o.d 
	@${RM} ${OBJECTDIR}/SHELL/Shell_5.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/SHELL/Shell_5.o.d" -MT "${OBJECTDIR}/SHELL/Shell_5.o.d" -MT ${OBJECTDIR}/SHELL/Shell_5.o  -o ${OBJECTDIR}/SHELL/Shell_5.o SHELL/Shell_5.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/TIMEDATE/TimeDate_2.o: TIMEDATE/TimeDate_2.c  .generated_files/540eb08e2d650ebf5d181ee3b4b0bddd87400b3d.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/TIMEDATE" 
	@${RM} ${OBJECTDIR}/TIMEDATE/TimeDate_2.o.d 
	@${RM} ${OBJECTDIR}/TIMEDATE/TimeDate_2.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/TIMEDATE/TimeDate_2.o.d" -MT "${OBJECTDIR}/TIMEDATE/TimeDate_2.o.d" -MT ${OBJECTDIR}/TIMEDATE/TimeDate_2.o  -o ${OBJECTDIR}/TIMEDATE/TimeDate_2.o TIMEDATE/TimeDate_2.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/TIMMER_NB/Timmer_nb_1.o: TIMMER_NB/Timmer_nb_1.c  .generated_files/d4df5f1a141708be5848e03dc0d2f1ef24bc8f87.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/TIMMER_NB" 
	@${RM} ${OBJECTDIR}/TIMMER_NB/Timmer_nb_1.o.d 
	@${RM} ${OBJECTDIR}/TIMMER_NB/Timmer_nb_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/TIMMER_NB/Timmer_nb_1.o.d" -MT "${OBJECTDIR}/TIMMER_NB/Timmer_nb_1.o.d" -MT ${OBJECTDIR}/TIMMER_NB/Timmer_nb_1.o  -o ${OBJECTDIR}/TIMMER_NB/Timmer_nb_1.o TIMMER_NB/Timmer_nb_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/ZONA/NamingZone/NamingZone_2.o: ZONA/NamingZone/NamingZone_2.c  .generated_files/ef37dc2e9b6319ea1fda9a0c18a0fa91c33f454c.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/ZONA/NamingZone" 
	@${RM} ${OBJECTDIR}/ZONA/NamingZone/NamingZone_2.o.d 
	@${RM} ${OBJECTDIR}/ZONA/NamingZone/NamingZone_2.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/ZONA/NamingZone/NamingZone_2.o.d" -MT "${OBJECTDIR}/ZONA/NamingZone/NamingZone_2.o.d" -MT ${OBJECTDIR}/ZONA/NamingZone/NamingZone_2.o  -o ${OBJECTDIR}/ZONA/NamingZone/NamingZone_2.o ZONA/NamingZone/NamingZone_2.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/ZONA/Zona_1.o: ZONA/Zona_1.c  .generated_files/f8387419376e1937bd64515626b67287b90cb493.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/ZONA" 
	@${RM} ${OBJECTDIR}/ZONA/Zona_1.o.d 
	@${RM} ${OBJECTDIR}/ZONA/Zona_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/ZONA/Zona_1.o.d" -MT "${OBJECTDIR}/ZONA/Zona_1.o.d" -MT ${OBJECTDIR}/ZONA/Zona_1.o  -o ${OBJECTDIR}/ZONA/Zona_1.o ZONA/Zona_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/BUZZER/Buzzer_1.o: BUZZER/Buzzer_1.c  .generated_files/dad730a20b60cc38df02dfa53836ecc01a0f8bda.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/BUZZER" 
	@${RM} ${OBJECTDIR}/BUZZER/Buzzer_1.o.d 
	@${RM} ${OBJECTDIR}/BUZZER/Buzzer_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/BUZZER/Buzzer_1.o.d" -MT "${OBJECTDIR}/BUZZER/Buzzer_1.o.d" -MT ${OBJECTDIR}/BUZZER/Buzzer_1.o  -o ${OBJECTDIR}/BUZZER/Buzzer_1.o BUZZER/Buzzer_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/EEPROM/EEPROM.o: EEPROM/EEPROM.c  .generated_files/84393d72f55d974c4187c5613c001eff01edbbd8.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/EEPROM" 
	@${RM} ${OBJECTDIR}/EEPROM/EEPROM.o.d 
	@${RM} ${OBJECTDIR}/EEPROM/EEPROM.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/EEPROM/EEPROM.o.d" -MT "${OBJECTDIR}/EEPROM/EEPROM.o.d" -MT ${OBJECTDIR}/EEPROM/EEPROM.o  -o ${OBJECTDIR}/EEPROM/EEPROM.o EEPROM/EEPROM.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/GLCD192X64/GLCD192x64_01.o: GLCD192X64/GLCD192x64_01.c  .generated_files/7b7c0acdef9410461000ed72bfc346e33bcc84c.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/GLCD192X64" 
	@${RM} ${OBJECTDIR}/GLCD192X64/GLCD192x64_01.o.d 
	@${RM} ${OBJECTDIR}/GLCD192X64/GLCD192x64_01.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/GLCD192X64/GLCD192x64_01.o.d" -MT "${OBJECTDIR}/GLCD192X64/GLCD192x64_01.o.d" -MT ${OBJECTDIR}/GLCD192X64/GLCD192x64_01.o  -o ${OBJECTDIR}/GLCD192X64/GLCD192x64_01.o GLCD192X64/GLCD192x64_01.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/GLCD192X64/GLCD_fxs_1.o: GLCD192X64/GLCD_fxs_1.c  .generated_files/16a1bc7843d361b6a4713ca8905b03ab066b2ccd.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/GLCD192X64" 
	@${RM} ${OBJECTDIR}/GLCD192X64/GLCD_fxs_1.o.d 
	@${RM} ${OBJECTDIR}/GLCD192X64/GLCD_fxs_1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/GLCD192X64/GLCD_fxs_1.o.d" -MT "${OBJECTDIR}/GLCD192X64/GLCD_fxs_1.o.d" -MT ${OBJECTDIR}/GLCD192X64/GLCD_fxs_1.o  -o ${OBJECTDIR}/GLCD192X64/GLCD_fxs_1.o GLCD192X64/GLCD_fxs_1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/I2C/I2CCommonFx.o: I2C/I2CCommonFx.c  .generated_files/fb468df67ed7c3953b4e74cf343e6489d25bb7a9.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/I2C" 
	@${RM} ${OBJECTDIR}/I2C/I2CCommonFx.o.d 
	@${RM} ${OBJECTDIR}/I2C/I2CCommonFx.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/I2C/I2CCommonFx.o.d" -MT "${OBJECTDIR}/I2C/I2CCommonFx.o.d" -MT ${OBJECTDIR}/I2C/I2CCommonFx.o  -o ${OBJECTDIR}/I2C/I2CCommonFx.o I2C/I2CCommonFx.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/I2C/I2C_01.o: I2C/I2C_01.c  .generated_files/725d5b988b9eaa4cdc03be954719c1a0b2624ac7.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/I2C" 
	@${RM} ${OBJECTDIR}/I2C/I2C_01.o.d 
	@${RM} ${OBJECTDIR}/I2C/I2C_01.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/I2C/I2C_01.o.d" -MT "${OBJECTDIR}/I2C/I2C_01.o.d" -MT ${OBJECTDIR}/I2C/I2C_01.o  -o ${OBJECTDIR}/I2C/I2C_01.o I2C/I2C_01.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/main1.o: main1.c  .generated_files/4c23318518fb3dd203c8513b52568ad56ad98a5f.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main1.o.d 
	@${RM} ${OBJECTDIR}/main1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/main1.o.d" -MT "${OBJECTDIR}/main1.o.d" -MT ${OBJECTDIR}/main1.o  -o ${OBJECTDIR}/main1.o main1.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/TCNT0/TCNT0_01.o: TCNT0/TCNT0_01.c  .generated_files/f938b2392039c8bb587958ab599f5ed41bcf131e.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/TCNT0" 
	@${RM} ${OBJECTDIR}/TCNT0/TCNT0_01.o.d 
	@${RM} ${OBJECTDIR}/TCNT0/TCNT0_01.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/TCNT0/TCNT0_01.o.d" -MT "${OBJECTDIR}/TCNT0/TCNT0_01.o.d" -MT ${OBJECTDIR}/TCNT0/TCNT0_01.o  -o ${OBJECTDIR}/TCNT0/TCNT0_01.o TCNT0/TCNT0_01.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/USART/USART_01.o: USART/USART_01.c  .generated_files/486eacedff38fe54f3cb86d66253ab7de29c7fea.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/USART" 
	@${RM} ${OBJECTDIR}/USART/USART_01.o.d 
	@${RM} ${OBJECTDIR}/USART/USART_01.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/USART/USART_01.o.d" -MT "${OBJECTDIR}/USART/USART_01.o.d" -MT ${OBJECTDIR}/USART/USART_01.o  -o ${OBJECTDIR}/USART/USART_01.o USART/USART_01.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/KS108v1/ks0108.o: KS108v1/ks0108.c  .generated_files/1e4c7942bf21a43bb0c6c50f90d26d387c5f7322.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/KS108v1" 
	@${RM} ${OBJECTDIR}/KS108v1/ks0108.o.d 
	@${RM} ${OBJECTDIR}/KS108v1/ks0108.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/KS108v1/ks0108.o.d" -MT "${OBJECTDIR}/KS108v1/ks0108.o.d" -MT ${OBJECTDIR}/KS108v1/ks0108.o  -o ${OBJECTDIR}/KS108v1/ks0108.o KS108v1/ks0108.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/KS108v1/FONTS/SC.o: KS108v1/FONTS/SC.c  .generated_files/81b883daf421635bae4e4487d74a44dca7f3fe52.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/KS108v1/FONTS" 
	@${RM} ${OBJECTDIR}/KS108v1/FONTS/SC.o.d 
	@${RM} ${OBJECTDIR}/KS108v1/FONTS/SC.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/KS108v1/FONTS/SC.o.d" -MT "${OBJECTDIR}/KS108v1/FONTS/SC.o.d" -MT ${OBJECTDIR}/KS108v1/FONTS/SC.o  -o ${OBJECTDIR}/KS108v1/FONTS/SC.o KS108v1/FONTS/SC.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/KS108v1/FONTS/arial_bold_14.o: KS108v1/FONTS/arial_bold_14.c  .generated_files/d815c0f5926507003bf1c44c8c49c26f7b3df4fc.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/KS108v1/FONTS" 
	@${RM} ${OBJECTDIR}/KS108v1/FONTS/arial_bold_14.o.d 
	@${RM} ${OBJECTDIR}/KS108v1/FONTS/arial_bold_14.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/KS108v1/FONTS/arial_bold_14.o.d" -MT "${OBJECTDIR}/KS108v1/FONTS/arial_bold_14.o.d" -MT ${OBJECTDIR}/KS108v1/FONTS/arial_bold_14.o  -o ${OBJECTDIR}/KS108v1/FONTS/arial_bold_14.o KS108v1/FONTS/arial_bold_14.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/KS108v1/FONTS/corsiva_12.o: KS108v1/FONTS/corsiva_12.c  .generated_files/5306c446204db76267cfee76c99d0c2a850c0d95.flag .generated_files/4edef3fb29499c5f3fb28ba7e61ba46aff09e6b6.flag
	@${MKDIR} "${OBJECTDIR}/KS108v1/FONTS" 
	@${RM} ${OBJECTDIR}/KS108v1/FONTS/corsiva_12.o.d 
	@${RM} ${OBJECTDIR}/KS108v1/FONTS/corsiva_12.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"./" -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I ".." -Wall -Wundef -Werror -pedantic -pedantic-errors -MD -MP -MF "${OBJECTDIR}/KS108v1/FONTS/corsiva_12.o.d" -MT "${OBJECTDIR}/KS108v1/FONTS/corsiva_12.o.d" -MT ${OBJECTDIR}/KS108v1/FONTS/corsiva_12.o  -o ${OBJECTDIR}/KS108v1/FONTS/corsiva_12.o KS108v1/FONTS/corsiva_12.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/ATmega128_6Zonas_2011.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mmcu=atmega128 ${PACK_COMMON_OPTIONS}   -gdwarf-2 -D__$(MP_PROCESSOR_OPTION)__  -Wl,-Map="dist/${CND_CONF}/${IMAGE_TYPE}/ATmega128_6Zonas_2011.X.${IMAGE_TYPE}.map"   -Wl,-section-start=.sobjscene_commonprop_epp=0x810100 -Wl,-section-start=.sobjstorage_scene_epp=0x810200 -Wl,-section-start=.sobjzone_epp=0x810400  -o dist/${CND_CONF}/${IMAGE_TYPE}/ATmega128_6Zonas_2011.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}      -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1 -Wl,--gc-sections -Wl,--start-group  -Wl,--end-group 
	
	${MP_CC_DIR}/avr-objcopy -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0 --no-change-warnings -O ihex "dist/${CND_CONF}/${IMAGE_TYPE}/ATmega128_6Zonas_2011.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "dist/${CND_CONF}/${IMAGE_TYPE}/ATmega128_6Zonas_2011.X.${IMAGE_TYPE}.eep" || exit 0
	${MP_CC_DIR}/avr-objdump -h -S "dist/${CND_CONF}/${IMAGE_TYPE}/ATmega128_6Zonas_2011.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" > "dist/${CND_CONF}/${IMAGE_TYPE}/ATmega128_6Zonas_2011.X.${IMAGE_TYPE}.lss"
	${MP_CC_DIR}/avr-objcopy -O srec -R .eeprom -R .fuse -R .lock -R .signature "dist/${CND_CONF}/${IMAGE_TYPE}/ATmega128_6Zonas_2011.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "dist/${CND_CONF}/${IMAGE_TYPE}/ATmega128_6Zonas_2011.X.${IMAGE_TYPE}.srec"
	
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/ATmega128_6Zonas_2011.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mmcu=atmega128 ${PACK_COMMON_OPTIONS}  -D__$(MP_PROCESSOR_OPTION)__  -Wl,-Map="dist/${CND_CONF}/${IMAGE_TYPE}/ATmega128_6Zonas_2011.X.${IMAGE_TYPE}.map"   -Wl,-section-start=.sobjscene_commonprop_epp=0x810100 -Wl,-section-start=.sobjstorage_scene_epp=0x810200 -Wl,-section-start=.sobjzone_epp=0x810400  -o dist/${CND_CONF}/${IMAGE_TYPE}/ATmega128_6Zonas_2011.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}      -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION) -Wl,--gc-sections -Wl,--start-group  -Wl,--end-group 
	${MP_CC_DIR}/avr-objcopy -O ihex "dist/${CND_CONF}/${IMAGE_TYPE}/ATmega128_6Zonas_2011.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "dist/${CND_CONF}/${IMAGE_TYPE}/ATmega128_6Zonas_2011.X.${IMAGE_TYPE}.hex"
	${MP_CC_DIR}/avr-objcopy -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0 --no-change-warnings -O ihex "dist/${CND_CONF}/${IMAGE_TYPE}/ATmega128_6Zonas_2011.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "dist/${CND_CONF}/${IMAGE_TYPE}/ATmega128_6Zonas_2011.X.${IMAGE_TYPE}.eep" || exit 0
	${MP_CC_DIR}/avr-objdump -h -S "dist/${CND_CONF}/${IMAGE_TYPE}/ATmega128_6Zonas_2011.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" > "dist/${CND_CONF}/${IMAGE_TYPE}/ATmega128_6Zonas_2011.X.${IMAGE_TYPE}.lss"
	${MP_CC_DIR}/avr-objcopy -O srec -R .eeprom -R .fuse -R .lock -R .signature "dist/${CND_CONF}/${IMAGE_TYPE}/ATmega128_6Zonas_2011.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "dist/${CND_CONF}/${IMAGE_TYPE}/ATmega128_6Zonas_2011.X.${IMAGE_TYPE}.srec"
	
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Release
	${RM} -r dist/Release

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
