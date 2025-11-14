void LOGGER_init__(LOGGER *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->TRIG,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->MSG,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->LEVEL,LOGLEVEL__INFO,retain)
  __INIT_VAR(data__->TRIG0,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void LOGGER_body__(LOGGER *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  if ((__GET_VAR(data__->TRIG,) && !(__GET_VAR(data__->TRIG0,)))) {
    #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
    #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)

   LogMessage(GetFbVar(LEVEL),(char*)GetFbVar(MSG, .body),GetFbVar(MSG, .len));
  
    #undef GetFbVar
    #undef SetFbVar
;
  };
  __SET_VAR(data__->,TRIG0,,__GET_VAR(data__->TRIG,));

  goto __end;

__end:
  return;
} // LOGGER_body__() 





static inline INT __PLC_CONTROLLER_MOVE__INT__INT1(BOOL EN,
  INT IN,
  PLC_CONTROLLER *data__)
{
  INT __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_MOVE177_ENO,);
  __res = MOVE__INT__INT(EN,
    &__TMP_ENO,
    IN);
  __SET_VAR(,data__->_TMP_MOVE177_ENO,,__TMP_ENO);
  return __res;
}

static inline INT __PLC_CONTROLLER_MOVE__INT__INT2(BOOL EN,
  INT IN,
  PLC_CONTROLLER *data__)
{
  INT __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_MOVE47_ENO,);
  __res = MOVE__INT__INT(EN,
    &__TMP_ENO,
    IN);
  __SET_VAR(,data__->_TMP_MOVE47_ENO,,__TMP_ENO);
  return __res;
}

static inline REAL __PLC_CONTROLLER_MOVE__REAL__REAL3(BOOL EN,
  REAL IN,
  PLC_CONTROLLER *data__)
{
  REAL __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_MOVE255_ENO,);
  __res = MOVE__REAL__REAL(EN,
    &__TMP_ENO,
    IN);
  __SET_VAR(,data__->_TMP_MOVE255_ENO,,__TMP_ENO);
  return __res;
}

static inline INT __PLC_CONTROLLER_MOVE__INT__INT4(BOOL EN,
  INT IN,
  PLC_CONTROLLER *data__)
{
  INT __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_MOVE264_ENO,);
  __res = MOVE__INT__INT(EN,
    &__TMP_ENO,
    IN);
  __SET_VAR(,data__->_TMP_MOVE264_ENO,,__TMP_ENO);
  return __res;
}

void PLC_CONTROLLER_init__(PLC_CONTROLLER *data__, BOOL retain) {
  __INIT_LOCATED(BOOL,__IX0_2,data__->IN_START_STOP,retain)
  __INIT_LOCATED_VALUE(data__->IN_START_STOP,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__IX0_0,data__->IN_TEMP_UP,retain)
  __INIT_LOCATED_VALUE(data__->IN_TEMP_UP,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__IX0_1,data__->IN_TEMP_DOWN,retain)
  __INIT_LOCATED_VALUE(data__->IN_TEMP_DOWN,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__IX0_3,data__->IN_EMERGENCY_STOP,retain)
  __INIT_LOCATED_VALUE(data__->IN_EMERGENCY_STOP,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__QX0_7,data__->OUT_STATUS_LED,retain)
  __INIT_LOCATED_VALUE(data__->OUT_STATUS_LED,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__QX0_6,data__->OUT_DISPLAY_LED0,retain)
  __INIT_LOCATED_VALUE(data__->OUT_DISPLAY_LED0,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__QX0_5,data__->OUT_DISPLAY_LED1,retain)
  __INIT_LOCATED_VALUE(data__->OUT_DISPLAY_LED1,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__QX0_4,data__->OUT_DISPLAY_LED2,retain)
  __INIT_LOCATED_VALUE(data__->OUT_DISPLAY_LED2,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__QX0_3,data__->OUT_DISPLAY_LED3,retain)
  __INIT_LOCATED_VALUE(data__->OUT_DISPLAY_LED3,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__QX0_2,data__->OUT_DISPLAY_LED4,retain)
  __INIT_LOCATED_VALUE(data__->OUT_DISPLAY_LED4,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__QX0_1,data__->OUT_DISPLAY_LED5,retain)
  __INIT_LOCATED_VALUE(data__->OUT_DISPLAY_LED5,__BOOL_LITERAL(FALSE))
  __INIT_VAR(data__->OUT_SERVO_PWM_CHANN,1,retain)
  __INIT_VAR(data__->SERVO_FREQ,50.0,retain)
  __INIT_VAR(data__->SERVO_ANGLE,0.0,retain)
  __INIT_VAR(data__->HEATING_ON,__BOOL_LITERAL(FALSE),retain)
  __INIT_LOCATED(WORD,__MW0,data__->MEM_HEATING_ON,retain)
  __INIT_LOCATED_VALUE(data__->MEM_HEATING_ON,0)
  __INIT_VAR(data__->ELEMENT_ON,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->EMERGENCY_STOP,__BOOL_LITERAL(FALSE),retain)
  __INIT_LOCATED(WORD,__MW1,data__->MEM_EMERGENCY_STOP,retain)
  __INIT_LOCATED_VALUE(data__->MEM_EMERGENCY_STOP,0)
  __INIT_VAR(data__->GLOBAL_ENABLE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->DISPLAY_INDEX,0,retain)
  __INIT_VAR(data__->TEMP_SETTING,0,retain)
  __INIT_LOCATED(WORD,__MW2,data__->MEM_TEMP_UP,retain)
  __INIT_LOCATED_VALUE(data__->MEM_TEMP_UP,0)
  __INIT_LOCATED(WORD,__MW3,data__->MEM_TEMP_DOWN,retain)
  __INIT_LOCATED_VALUE(data__->MEM_TEMP_DOWN,0)
  __INIT_VAR(data__->TEMPERATURE,0,retain)
  __INIT_VAR(data__->MAX_TEMP_SETTING,10,retain)
  R_TRIG_init__(&data__->R_TRIG0,retain);
  CTUD_init__(&data__->CTUD0,retain);
  TON_init__(&data__->TON0,retain);
  R_TRIG_init__(&data__->R_TRIG1,retain);
  CTUD_init__(&data__->CTUD1,retain);
  PID_init__(&data__->PID0,retain);
  PWM_CONTROLLER_init__(&data__->PWM_CONTROLLER0,retain);
  TON_init__(&data__->TON1,retain);
  R_TRIG_init__(&data__->R_TRIG2,retain);
  R_TRIG_init__(&data__->R_TRIG3,retain);
  __INIT_VAR(data__->_TMP_NOT30_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_WORD_TO_BOOL81_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_OR275_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_NOT21_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_AND22_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_AND31_OUT,__BOOL_LITERAL(FALSE),retain)
  R_TRIG_init__(&data__->R_TRIG4,retain);
  __INIT_VAR(data__->_TMP_WORD_TO_BOOL82_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_OR80_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_AND5_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_NOT133_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_AND132_OUT,__BOOL_LITERAL(FALSE),retain)
  R_TRIG_init__(&data__->R_TRIG5,retain);
  __INIT_VAR(data__->_TMP_WORD_TO_BOOL268_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_OR271_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_XOR10_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_AND266_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_EQ137_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_EQ1_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_OR140_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_EQ7_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_EQ8_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_EQ2_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_OR20_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_EQ6_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_EQ29_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_EQ38_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_OR35_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_EQ41_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_EQ43_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_EQ45_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_OR46_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_EQ49_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_EQ51_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_EQ54_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_OR53_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_EQ59_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_EQ61_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_OR64_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_NOT163_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_AND159_OUT,__BOOL_LITERAL(FALSE),retain)
  R_TRIG_init__(&data__->R_TRIG6,retain);
  __INIT_VAR(data__->_TMP_NOT165_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_AND62_OUT,__BOOL_LITERAL(FALSE),retain)
  R_TRIG_init__(&data__->R_TRIG7,retain);
  __INIT_VAR(data__->_TMP_INT_TO_REAL168_OUT,0,retain)
  __INIT_VAR(data__->_TMP_MUL166_OUT,0,retain)
  __INIT_VAR(data__->_TMP_ADD169_OUT,0,retain)
  __INIT_VAR(data__->_TMP_NOT176_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_AND261_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_MOVE177_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_MOVE177_OUT,0,retain)
  __INIT_VAR(data__->_TMP_SUB190_OUT,0,retain)
  __INIT_VAR(data__->_TMP_DIV192_OUT,0,retain)
  __INIT_VAR(data__->_TMP_INT_TO_REAL201_OUT,0,retain)
  __INIT_VAR(data__->_TMP_MUL193_OUT,0,retain)
  __INIT_VAR(data__->_TMP_REAL_TO_INT194_OUT,0,retain)
  __INIT_VAR(data__->_TMP_LIMIT198_OUT,0,retain)
  __INIT_VAR(data__->_TMP_MOVE47_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_MOVE47_OUT,0,retain)
  __INIT_VAR(data__->_TMP_MUL206_OUT,0,retain)
  __INIT_VAR(data__->_TMP_ADD37_OUT,0,retain)
  __INIT_VAR(data__->_TMP_INT_TO_REAL209_OUT,0,retain)
  __INIT_VAR(data__->_TMP_LIMIT217_OUT,0,retain)
  __INIT_VAR(data__->_TMP_REAL_TO_BOOL220_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_AND222_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_NOT68_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_NOT249_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_ADD242_OUT,0,retain)
  __INIT_VAR(data__->_TMP_SUB243_OUT,0,retain)
  __INIT_VAR(data__->_TMP_SEL248_OUT,0,retain)
  __INIT_VAR(data__->_TMP_LIMIT252_OUT,0,retain)
  __INIT_VAR(data__->_TMP_MOVE255_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_MOVE255_OUT,0,retain)
  __INIT_VAR(data__->_TMP_WORD_TO_BOOL276_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_OR273_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_XOR74_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_NOT258_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_NOT263_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_MOVE264_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_MOVE264_OUT,0,retain)
  __INIT_VAR(data__->_TMP_DIV232_OUT,0,retain)
  __INIT_VAR(data__->_TMP_ADD234_OUT,0,retain)
  __INIT_VAR(data__->_TMP_DIV236_OUT,0,retain)
  __INIT_VAR(data__->_TMP_DIV239_OUT,0,retain)
  __INIT_VAR(data__->_TMP_MUL240_OUT,0,retain)
}

// Code part
void PLC_CONTROLLER_body__(PLC_CONTROLLER *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->,_TMP_NOT30_OUT,,!(__GET_VAR(data__->CTUD0.QU,)));
  __SET_VAR(data__->,_TMP_WORD_TO_BOOL81_OUT,,WORD_TO_BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (WORD)__GET_LOCATED(data__->MEM_TEMP_UP,)));
  __SET_VAR(data__->,_TMP_OR275_OUT,,OR__BOOL__BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (BOOL)__GET_VAR(data__->_TMP_WORD_TO_BOOL81_OUT,),
    (BOOL)__GET_LOCATED(data__->IN_TEMP_UP,)));
  __SET_VAR(data__->,_TMP_NOT21_OUT,,!(__GET_VAR(data__->HEATING_ON,)));
  __SET_VAR(data__->,_TMP_AND22_OUT,,AND__BOOL__BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (BOOL)__GET_VAR(data__->_TMP_OR275_OUT,),
    (BOOL)__GET_VAR(data__->_TMP_NOT21_OUT,)));
  __SET_VAR(data__->,_TMP_AND31_OUT,,AND__BOOL__BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (BOOL)__GET_VAR(data__->_TMP_NOT30_OUT,),
    (BOOL)__GET_VAR(data__->_TMP_AND22_OUT,)));
  __SET_VAR(data__->R_TRIG4.,CLK,,__GET_VAR(data__->_TMP_AND31_OUT,));
  R_TRIG_body__(&data__->R_TRIG4);
  __SET_VAR(data__->,_TMP_WORD_TO_BOOL82_OUT,,WORD_TO_BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (WORD)__GET_LOCATED(data__->MEM_TEMP_DOWN,)));
  __SET_VAR(data__->,_TMP_OR80_OUT,,OR__BOOL__BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (BOOL)__GET_LOCATED(data__->IN_TEMP_DOWN,),
    (BOOL)__GET_VAR(data__->_TMP_WORD_TO_BOOL82_OUT,)));
  __SET_VAR(data__->,_TMP_AND5_OUT,,AND__BOOL__BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (BOOL)__GET_VAR(data__->_TMP_OR80_OUT,),
    (BOOL)__GET_VAR(data__->_TMP_NOT21_OUT,)));
  __SET_VAR(data__->,_TMP_NOT133_OUT,,!(__GET_VAR(data__->CTUD0.QD,)));
  __SET_VAR(data__->,_TMP_AND132_OUT,,AND__BOOL__BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (BOOL)__GET_VAR(data__->_TMP_AND5_OUT,),
    (BOOL)__GET_VAR(data__->_TMP_NOT133_OUT,)));
  __SET_VAR(data__->R_TRIG5.,CLK,,__GET_VAR(data__->_TMP_AND132_OUT,));
  R_TRIG_body__(&data__->R_TRIG5);
  __SET_VAR(data__->CTUD0.,CU,,__GET_VAR(data__->R_TRIG4.Q,));
  __SET_VAR(data__->CTUD0.,CD,,__GET_VAR(data__->R_TRIG5.Q,));
  __SET_VAR(data__->CTUD0.,PV,,__GET_VAR(data__->MAX_TEMP_SETTING,));
  CTUD_body__(&data__->CTUD0);
  __SET_VAR(data__->,TEMP_SETTING,,__GET_VAR(data__->CTUD0.CV,));
  __SET_VAR(data__->,_TMP_WORD_TO_BOOL268_OUT,,WORD_TO_BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (WORD)__GET_LOCATED(data__->MEM_HEATING_ON,)));
  __SET_VAR(data__->,_TMP_OR271_OUT,,OR__BOOL__BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (BOOL)__GET_VAR(data__->_TMP_WORD_TO_BOOL268_OUT,),
    (BOOL)__GET_LOCATED(data__->IN_START_STOP,)));
  __SET_VAR(data__->R_TRIG0.,CLK,,__GET_VAR(data__->_TMP_OR271_OUT,));
  R_TRIG_body__(&data__->R_TRIG0);
  __SET_VAR(data__->,_TMP_XOR10_OUT,,XOR__BOOL__BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (BOOL)__GET_VAR(data__->R_TRIG0.Q,),
    (BOOL)__GET_VAR(data__->HEATING_ON,)));
  __SET_VAR(data__->,_TMP_AND266_OUT,,AND__BOOL__BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (BOOL)__GET_VAR(data__->_TMP_XOR10_OUT,),
    (BOOL)__GET_VAR(data__->GLOBAL_ENABLE,)));
  __SET_VAR(data__->,HEATING_ON,,__GET_VAR(data__->_TMP_AND266_OUT,));
  __SET_VAR(data__->,_TMP_EQ137_OUT,,EQ__BOOL__INT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (INT)__GET_VAR(data__->DISPLAY_INDEX,),
    (INT)0));
  __SET_VAR(data__->,_TMP_EQ1_OUT,,EQ__BOOL__INT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (INT)__GET_VAR(data__->DISPLAY_INDEX,),
    (INT)1));
  __SET_VAR(data__->,_TMP_OR140_OUT,,OR__BOOL__BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (BOOL)__GET_VAR(data__->_TMP_EQ137_OUT,),
    (BOOL)__GET_VAR(data__->_TMP_EQ1_OUT,)));
  __SET_LOCATED(data__->,OUT_DISPLAY_LED0,,__GET_VAR(data__->_TMP_OR140_OUT,));
  __SET_VAR(data__->,_TMP_EQ7_OUT,,EQ__BOOL__INT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (INT)__GET_VAR(data__->DISPLAY_INDEX,),
    (INT)5));
  __SET_VAR(data__->,_TMP_EQ8_OUT,,EQ__BOOL__INT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (INT)__GET_VAR(data__->DISPLAY_INDEX,),
    (INT)6));
  __SET_VAR(data__->,_TMP_EQ2_OUT,,EQ__BOOL__INT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (INT)__GET_VAR(data__->DISPLAY_INDEX,),
    (INT)7));
  __SET_VAR(data__->,_TMP_OR20_OUT,,OR__BOOL__BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)3,
    (BOOL)__GET_VAR(data__->_TMP_EQ7_OUT,),
    (BOOL)__GET_VAR(data__->_TMP_EQ8_OUT,),
    (BOOL)__GET_VAR(data__->_TMP_EQ2_OUT,)));
  __SET_LOCATED(data__->,OUT_DISPLAY_LED3,,__GET_VAR(data__->_TMP_OR20_OUT,));
  __SET_VAR(data__->,_TMP_EQ6_OUT,,EQ__BOOL__INT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (INT)__GET_VAR(data__->DISPLAY_INDEX,),
    (INT)1));
  __SET_VAR(data__->,_TMP_EQ29_OUT,,EQ__BOOL__INT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (INT)__GET_VAR(data__->DISPLAY_INDEX,),
    (INT)2));
  __SET_VAR(data__->,_TMP_EQ38_OUT,,EQ__BOOL__INT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (INT)__GET_VAR(data__->DISPLAY_INDEX,),
    (INT)3));
  __SET_VAR(data__->,_TMP_OR35_OUT,,OR__BOOL__BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)3,
    (BOOL)__GET_VAR(data__->_TMP_EQ6_OUT,),
    (BOOL)__GET_VAR(data__->_TMP_EQ29_OUT,),
    (BOOL)__GET_VAR(data__->_TMP_EQ38_OUT,)));
  __SET_LOCATED(data__->,OUT_DISPLAY_LED1,,__GET_VAR(data__->_TMP_OR35_OUT,));
  __SET_VAR(data__->,_TMP_EQ41_OUT,,EQ__BOOL__INT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (INT)__GET_VAR(data__->DISPLAY_INDEX,),
    (INT)7));
  __SET_VAR(data__->,_TMP_EQ43_OUT,,EQ__BOOL__INT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (INT)__GET_VAR(data__->DISPLAY_INDEX,),
    (INT)8));
  __SET_VAR(data__->,_TMP_EQ45_OUT,,EQ__BOOL__INT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (INT)__GET_VAR(data__->DISPLAY_INDEX,),
    (INT)9));
  __SET_VAR(data__->,_TMP_OR46_OUT,,OR__BOOL__BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)3,
    (BOOL)__GET_VAR(data__->_TMP_EQ41_OUT,),
    (BOOL)__GET_VAR(data__->_TMP_EQ43_OUT,),
    (BOOL)__GET_VAR(data__->_TMP_EQ45_OUT,)));
  __SET_LOCATED(data__->,OUT_DISPLAY_LED4,,__GET_VAR(data__->_TMP_OR46_OUT,));
  __SET_VAR(data__->,_TMP_EQ49_OUT,,EQ__BOOL__INT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (INT)__GET_VAR(data__->DISPLAY_INDEX,),
    (INT)3));
  __SET_VAR(data__->,_TMP_EQ51_OUT,,EQ__BOOL__INT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (INT)__GET_VAR(data__->DISPLAY_INDEX,),
    (INT)4));
  __SET_VAR(data__->,_TMP_EQ54_OUT,,EQ__BOOL__INT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (INT)__GET_VAR(data__->DISPLAY_INDEX,),
    (INT)5));
  __SET_VAR(data__->,_TMP_OR53_OUT,,OR__BOOL__BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)3,
    (BOOL)__GET_VAR(data__->_TMP_EQ49_OUT,),
    (BOOL)__GET_VAR(data__->_TMP_EQ51_OUT,),
    (BOOL)__GET_VAR(data__->_TMP_EQ54_OUT,)));
  __SET_LOCATED(data__->,OUT_DISPLAY_LED2,,__GET_VAR(data__->_TMP_OR53_OUT,));
  __SET_VAR(data__->,_TMP_EQ59_OUT,,EQ__BOOL__INT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (INT)__GET_VAR(data__->DISPLAY_INDEX,),
    (INT)9));
  __SET_VAR(data__->,_TMP_EQ61_OUT,,EQ__BOOL__INT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (INT)__GET_VAR(data__->DISPLAY_INDEX,),
    (INT)10));
  __SET_VAR(data__->,_TMP_OR64_OUT,,OR__BOOL__BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (BOOL)__GET_VAR(data__->_TMP_EQ59_OUT,),
    (BOOL)__GET_VAR(data__->_TMP_EQ61_OUT,)));
  __SET_LOCATED(data__->,OUT_DISPLAY_LED5,,__GET_VAR(data__->_TMP_OR64_OUT,));
  __SET_VAR(data__->,_TMP_NOT163_OUT,,!(__GET_VAR(data__->R_TRIG1.Q,)));
  __SET_VAR(data__->TON0.,IN,,__GET_VAR(data__->_TMP_NOT163_OUT,));
  __SET_VAR(data__->TON0.,PT,,__time_to_timespec(1, 20, 0, 0, 0, 0));
  TON_body__(&data__->TON0);
  __SET_VAR(data__->R_TRIG1.,CLK,,__GET_VAR(data__->TON0.Q,));
  R_TRIG_body__(&data__->R_TRIG1);
  __SET_VAR(data__->,_TMP_AND159_OUT,,AND__BOOL__BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (BOOL)__GET_VAR(data__->R_TRIG1.Q,),
    (BOOL)__GET_VAR(data__->ELEMENT_ON,)));
  __SET_VAR(data__->R_TRIG6.,CLK,,__GET_VAR(data__->_TMP_AND159_OUT,));
  R_TRIG_body__(&data__->R_TRIG6);
  __SET_VAR(data__->,_TMP_NOT165_OUT,,!(__GET_VAR(data__->ELEMENT_ON,)));
  __SET_VAR(data__->,_TMP_AND62_OUT,,AND__BOOL__BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (BOOL)__GET_VAR(data__->_TMP_NOT165_OUT,),
    (BOOL)__GET_VAR(data__->R_TRIG1.Q,)));
  __SET_VAR(data__->R_TRIG7.,CLK,,__GET_VAR(data__->_TMP_AND62_OUT,));
  R_TRIG_body__(&data__->R_TRIG7);
  __SET_VAR(data__->CTUD1.,CU,,__GET_VAR(data__->R_TRIG6.Q,));
  __SET_VAR(data__->CTUD1.,CD,,__GET_VAR(data__->R_TRIG7.Q,));
  __SET_VAR(data__->CTUD1.,PV,,2000);
  CTUD_body__(&data__->CTUD1);
  __SET_VAR(data__->,_TMP_INT_TO_REAL168_OUT,,INT_TO_REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (INT)__GET_VAR(data__->CTUD1.CV,)));
  __SET_VAR(data__->,_TMP_MUL166_OUT,,MUL__REAL__REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (REAL)__GET_VAR(data__->_TMP_INT_TO_REAL168_OUT,),
    (REAL)0.1));
  __SET_VAR(data__->,_TMP_ADD169_OUT,,ADD__REAL__REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (REAL)__GET_VAR(data__->_TMP_MUL166_OUT,),
    (REAL)60.0));
  __SET_VAR(data__->,TEMPERATURE,,__GET_VAR(data__->_TMP_ADD169_OUT,));
  __SET_VAR(data__->,_TMP_NOT176_OUT,,!(__GET_VAR(data__->HEATING_ON,)));
  __SET_VAR(data__->,_TMP_AND261_OUT,,AND__BOOL__BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (BOOL)__GET_VAR(data__->GLOBAL_ENABLE,),
    (BOOL)__GET_VAR(data__->_TMP_NOT176_OUT,)));
  __SET_VAR(data__->,_TMP_MOVE177_OUT,,__PLC_CONTROLLER_MOVE__INT__INT1(
    (BOOL)__GET_VAR(data__->_TMP_AND261_OUT,),
    (INT)__GET_VAR(data__->TEMP_SETTING,),
    data__));
  if (__GET_VAR(data__->_TMP_MOVE177_ENO,)) {
    __SET_VAR(data__->,DISPLAY_INDEX,,__GET_VAR(data__->_TMP_MOVE177_OUT,));
  };
  __SET_VAR(data__->,_TMP_SUB190_OUT,,SUB__REAL__REAL__REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (REAL)__GET_VAR(data__->TEMPERATURE,),
    (REAL)80.0));
  __SET_VAR(data__->,_TMP_DIV192_OUT,,DIV__REAL__REAL__REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (REAL)__GET_VAR(data__->_TMP_SUB190_OUT,),
    (REAL)100.0));
  __SET_VAR(data__->,_TMP_INT_TO_REAL201_OUT,,INT_TO_REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (INT)__GET_VAR(data__->MAX_TEMP_SETTING,)));
  __SET_VAR(data__->,_TMP_MUL193_OUT,,MUL__REAL__REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (REAL)__GET_VAR(data__->_TMP_DIV192_OUT,),
    (REAL)__GET_VAR(data__->_TMP_INT_TO_REAL201_OUT,)));
  __SET_VAR(data__->,_TMP_REAL_TO_INT194_OUT,,REAL_TO_INT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (REAL)__GET_VAR(data__->_TMP_MUL193_OUT,)));
  __SET_VAR(data__->,_TMP_LIMIT198_OUT,,LIMIT__INT__INT__INT__INT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (INT)0,
    (INT)__GET_VAR(data__->_TMP_REAL_TO_INT194_OUT,),
    (INT)__GET_VAR(data__->MAX_TEMP_SETTING,)));
  __SET_VAR(data__->,_TMP_MOVE47_OUT,,__PLC_CONTROLLER_MOVE__INT__INT2(
    (BOOL)__GET_VAR(data__->HEATING_ON,),
    (INT)__GET_VAR(data__->_TMP_LIMIT198_OUT,),
    data__));
  if (__GET_VAR(data__->_TMP_MOVE47_ENO,)) {
    __SET_VAR(data__->,DISPLAY_INDEX,,__GET_VAR(data__->_TMP_MOVE47_OUT,));
  };
  __SET_VAR(data__->,_TMP_MUL206_OUT,,MUL__INT__INT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (INT)__GET_VAR(data__->TEMP_SETTING,),
    (INT)10));
  __SET_VAR(data__->,_TMP_ADD37_OUT,,ADD__INT__INT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (INT)__GET_VAR(data__->_TMP_MUL206_OUT,),
    (INT)80));
  __SET_VAR(data__->,_TMP_INT_TO_REAL209_OUT,,INT_TO_REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (INT)__GET_VAR(data__->_TMP_ADD37_OUT,)));
  __SET_VAR(data__->PID0.,AUTO,,__GET_VAR(data__->HEATING_ON,));
  __SET_VAR(data__->PID0.,PV,,__GET_VAR(data__->TEMPERATURE,));
  __SET_VAR(data__->PID0.,SP,,__GET_VAR(data__->_TMP_INT_TO_REAL209_OUT,));
  __SET_VAR(data__->PID0.,KP,,-0.01);
  __SET_VAR(data__->PID0.,TR,,8.0);
  __SET_VAR(data__->PID0.,TD,,0.1);
  __SET_VAR(data__->PID0.,CYCLE,,__time_to_timespec(1, 20, 0, 0, 0, 0));
  PID_body__(&data__->PID0);
  __SET_VAR(data__->,_TMP_LIMIT217_OUT,,LIMIT__REAL__REAL__REAL__REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (REAL)0.0,
    (REAL)__GET_VAR(data__->PID0.XOUT,),
    (REAL)1.0));
  __SET_VAR(data__->,_TMP_REAL_TO_BOOL220_OUT,,REAL_TO_BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (REAL)__GET_VAR(data__->_TMP_LIMIT217_OUT,)));
  __SET_VAR(data__->,_TMP_AND222_OUT,,AND__BOOL__BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (BOOL)__GET_VAR(data__->HEATING_ON,),
    (BOOL)__GET_VAR(data__->_TMP_REAL_TO_BOOL220_OUT,)));
  __SET_VAR(data__->,ELEMENT_ON,,__GET_VAR(data__->_TMP_AND222_OUT,));
  __SET_VAR(data__->,_TMP_NOT68_OUT,,!(__GET_VAR(data__->R_TRIG2.Q,)));
  __SET_VAR(data__->TON1.,IN,,__GET_VAR(data__->_TMP_NOT68_OUT,));
  __SET_VAR(data__->TON1.,PT,,__time_to_timespec(1, 100, 0, 0, 0, 0));
  TON_body__(&data__->TON1);
  __SET_VAR(data__->R_TRIG2.,CLK,,__GET_VAR(data__->TON1.Q,));
  R_TRIG_body__(&data__->R_TRIG2);
  __SET_VAR(data__->,_TMP_NOT249_OUT,,!(__GET_VAR(data__->HEATING_ON,)));
  __SET_VAR(data__->,_TMP_ADD242_OUT,,ADD__REAL__REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (REAL)__GET_VAR(data__->SERVO_ANGLE,),
    (REAL)1.8));
  __SET_VAR(data__->,_TMP_SUB243_OUT,,SUB__REAL__REAL__REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (REAL)__GET_VAR(data__->SERVO_ANGLE,),
    (REAL)1.8));
  __SET_VAR(data__->,_TMP_SEL248_OUT,,SEL__REAL__BOOL__REAL__REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (BOOL)__GET_VAR(data__->_TMP_NOT249_OUT,),
    (REAL)__GET_VAR(data__->_TMP_ADD242_OUT,),
    (REAL)__GET_VAR(data__->_TMP_SUB243_OUT,)));
  __SET_VAR(data__->,_TMP_LIMIT252_OUT,,LIMIT__REAL__REAL__REAL__REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (REAL)0.0,
    (REAL)__GET_VAR(data__->_TMP_SEL248_OUT,),
    (REAL)144.0));
  __SET_VAR(data__->,_TMP_MOVE255_OUT,,__PLC_CONTROLLER_MOVE__REAL__REAL3(
    (BOOL)__GET_VAR(data__->R_TRIG2.Q,),
    (REAL)__GET_VAR(data__->_TMP_LIMIT252_OUT,),
    data__));
  if (__GET_VAR(data__->_TMP_MOVE255_ENO,)) {
    __SET_VAR(data__->,SERVO_ANGLE,,__GET_VAR(data__->_TMP_MOVE255_OUT,));
  };
  __SET_VAR(data__->,_TMP_WORD_TO_BOOL276_OUT,,WORD_TO_BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (WORD)__GET_LOCATED(data__->MEM_EMERGENCY_STOP,)));
  __SET_VAR(data__->,_TMP_OR273_OUT,,OR__BOOL__BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (BOOL)__GET_VAR(data__->_TMP_WORD_TO_BOOL276_OUT,),
    (BOOL)__GET_LOCATED(data__->IN_EMERGENCY_STOP,)));
  __SET_VAR(data__->R_TRIG3.,CLK,,__GET_VAR(data__->_TMP_OR273_OUT,));
  R_TRIG_body__(&data__->R_TRIG3);
  __SET_VAR(data__->,_TMP_XOR74_OUT,,XOR__BOOL__BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (BOOL)__GET_VAR(data__->R_TRIG3.Q,),
    (BOOL)__GET_VAR(data__->EMERGENCY_STOP,)));
  __SET_VAR(data__->,EMERGENCY_STOP,,__GET_VAR(data__->_TMP_XOR74_OUT,));
  __SET_VAR(data__->,_TMP_NOT258_OUT,,!(__GET_VAR(data__->EMERGENCY_STOP,)));
  __SET_VAR(data__->,GLOBAL_ENABLE,,__GET_VAR(data__->_TMP_NOT258_OUT,));
  __SET_VAR(data__->,_TMP_NOT263_OUT,,!(__GET_VAR(data__->GLOBAL_ENABLE,)));
  __SET_VAR(data__->,_TMP_MOVE264_OUT,,__PLC_CONTROLLER_MOVE__INT__INT4(
    (BOOL)__GET_VAR(data__->_TMP_NOT263_OUT,),
    (INT)-1,
    data__));
  if (__GET_VAR(data__->_TMP_MOVE264_ENO,)) {
    __SET_VAR(data__->,DISPLAY_INDEX,,__GET_VAR(data__->_TMP_MOVE264_OUT,));
  };
  __SET_LOCATED(data__->,OUT_STATUS_LED,,__GET_VAR(data__->HEATING_ON,));
  __SET_VAR(data__->,_TMP_DIV232_OUT,,DIV__REAL__REAL__REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (REAL)__GET_VAR(data__->SERVO_ANGLE,),
    (REAL)90.0));
  __SET_VAR(data__->,_TMP_ADD234_OUT,,ADD__REAL__REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (REAL)__GET_VAR(data__->_TMP_DIV232_OUT,),
    (REAL)0.5));
  __SET_VAR(data__->,_TMP_DIV236_OUT,,DIV__REAL__REAL__REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (REAL)1000.0,
    (REAL)__GET_VAR(data__->SERVO_FREQ,)));
  __SET_VAR(data__->,_TMP_DIV239_OUT,,DIV__REAL__REAL__REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (REAL)__GET_VAR(data__->_TMP_ADD234_OUT,),
    (REAL)__GET_VAR(data__->_TMP_DIV236_OUT,)));
  __SET_VAR(data__->,_TMP_MUL240_OUT,,MUL__REAL__REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (REAL)__GET_VAR(data__->_TMP_DIV239_OUT,),
    (REAL)100.0));
  __SET_VAR(data__->PWM_CONTROLLER0.,CHANNEL,,__GET_VAR(data__->OUT_SERVO_PWM_CHANN,));
  __SET_VAR(data__->PWM_CONTROLLER0.,FREQ,,__GET_VAR(data__->SERVO_FREQ,));
  __SET_VAR(data__->PWM_CONTROLLER0.,DUTY,,__GET_VAR(data__->_TMP_MUL240_OUT,));
  PWM_CONTROLLER_body__(&data__->PWM_CONTROLLER0);

  goto __end;

__end:
  return;
} // PLC_CONTROLLER_body__() 





