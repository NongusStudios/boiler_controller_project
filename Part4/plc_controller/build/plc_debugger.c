/*
 * DEBUGGER code
 * 
 * On "publish", when buffer is free, debugger stores arbitrary variables 
 * content into, and mark this buffer as filled
 * 
 * 
 * Buffer content is read asynchronously, (from non real time part), 
 * and then buffer marked free again.
 *  
 * 
 * */
#ifdef TARGET_DEBUG_AND_RETAIN_DISABLE

void __init_debug    (void){}
void __cleanup_debug (void){}
void __retrieve_debug(void){}
void __publish_debug (void){}

#else

#include "iec_types_all.h"
#include "POUS.h"
/*for memcpy*/
#include <string.h>
#include <stdio.h>

typedef unsigned int dbgvardsc_index_t;
typedef unsigned short trace_buf_offset_t;

#define BUFFER_EMPTY 0
#define BUFFER_FULL 1

#ifndef TARGET_ONLINE_DEBUG_DISABLE

#define TRACE_BUFFER_SIZE 4096
#define TRACE_LIST_SIZE 1024

/* Atomically accessed variable for buffer state */
static long trace_buffer_state = BUFFER_EMPTY;

typedef struct trace_item_s {
    dbgvardsc_index_t dbgvardsc_index;
} trace_item_t;

trace_item_t trace_list[TRACE_LIST_SIZE];
char trace_buffer[TRACE_BUFFER_SIZE];

/* Trace's cursor*/
static trace_item_t *trace_list_collect_cursor = trace_list;
static trace_item_t *trace_list_addvar_cursor = trace_list;
static const trace_item_t *trace_list_end = 
    &trace_list[TRACE_LIST_SIZE-1];
static char *trace_buffer_cursor = trace_buffer;
static const char *trace_buffer_end = trace_buffer + TRACE_BUFFER_SIZE;



#define FORCE_BUFFER_SIZE 1024
#define FORCE_LIST_SIZE 256

typedef struct force_item_s {
    dbgvardsc_index_t dbgvardsc_index;
    void *value_pointer_backup;
} force_item_t;

force_item_t force_list[FORCE_LIST_SIZE];
char force_buffer[FORCE_BUFFER_SIZE];

/* Force's cursor*/
static force_item_t *force_list_apply_cursor = force_list;
static force_item_t *force_list_addvar_cursor = force_list;
static const force_item_t *force_list_end = 
    &force_list[FORCE_LIST_SIZE-1];
static char *force_buffer_cursor = force_buffer;
static const char *force_buffer_end = force_buffer + FORCE_BUFFER_SIZE;


#endif

/***
 * Declare programs 
 **/
extern PLC_CONTROLLER RES0__INSTANCE0;

/***
 * Declare global variables from resources and conf 
 **/
extern       PLC_CONTROLLER   RES0__INSTANCE0;

typedef const struct {
    void *ptr;
    __IEC_types_enum type;
} dbgvardsc_t;

static const dbgvardsc_t dbgvardsc[] = {
{&(RES0__INSTANCE0.IN_START_STOP), BOOL_P_ENUM},
{&(RES0__INSTANCE0.IN_TEMP_UP), BOOL_P_ENUM},
{&(RES0__INSTANCE0.IN_TEMP_DOWN), BOOL_P_ENUM},
{&(RES0__INSTANCE0.IN_EMERGENCY_STOP), BOOL_P_ENUM},
{&(RES0__INSTANCE0.OUT_STATUS_LED), BOOL_O_ENUM},
{&(RES0__INSTANCE0.OUT_DISPLAY_LED0), BOOL_O_ENUM},
{&(RES0__INSTANCE0.OUT_DISPLAY_LED1), BOOL_O_ENUM},
{&(RES0__INSTANCE0.OUT_DISPLAY_LED2), BOOL_O_ENUM},
{&(RES0__INSTANCE0.OUT_DISPLAY_LED3), BOOL_O_ENUM},
{&(RES0__INSTANCE0.OUT_DISPLAY_LED4), BOOL_O_ENUM},
{&(RES0__INSTANCE0.OUT_DISPLAY_LED5), BOOL_O_ENUM},
{&(RES0__INSTANCE0.OUT_SERVO_PWM_CHANN), SINT_ENUM},
{&(RES0__INSTANCE0.SERVO_FREQ), REAL_ENUM},
{&(RES0__INSTANCE0.SERVO_ANGLE), REAL_ENUM},
{&(RES0__INSTANCE0.HEATING_ON), BOOL_ENUM},
{&(RES0__INSTANCE0.MEM_HEATING_ON), WORD_O_ENUM},
{&(RES0__INSTANCE0.ELEMENT_ON), BOOL_ENUM},
{&(RES0__INSTANCE0.EMERGENCY_STOP), BOOL_ENUM},
{&(RES0__INSTANCE0.MEM_EMERGENCY_STOP), WORD_O_ENUM},
{&(RES0__INSTANCE0.GLOBAL_ENABLE), BOOL_ENUM},
{&(RES0__INSTANCE0.DISPLAY_INDEX), INT_ENUM},
{&(RES0__INSTANCE0.TEMP_SETTING), INT_ENUM},
{&(RES0__INSTANCE0.MEM_TEMP_UP), WORD_O_ENUM},
{&(RES0__INSTANCE0.MEM_TEMP_DOWN), WORD_O_ENUM},
{&(RES0__INSTANCE0.TEMPERATURE), REAL_ENUM},
{&(RES0__INSTANCE0.MAX_TEMP_SETTING), INT_ENUM},
{&(RES0__INSTANCE0.R_TRIG0.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG0.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG0.CLK), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG0.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG0.M), BOOL_ENUM},
{&(RES0__INSTANCE0.CTUD0.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.CTUD0.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.CTUD0.CU), BOOL_ENUM},
{&(RES0__INSTANCE0.CTUD0.CD), BOOL_ENUM},
{&(RES0__INSTANCE0.CTUD0.R), BOOL_ENUM},
{&(RES0__INSTANCE0.CTUD0.LD), BOOL_ENUM},
{&(RES0__INSTANCE0.CTUD0.PV), INT_ENUM},
{&(RES0__INSTANCE0.CTUD0.QU), BOOL_ENUM},
{&(RES0__INSTANCE0.CTUD0.QD), BOOL_ENUM},
{&(RES0__INSTANCE0.CTUD0.CV), INT_ENUM},
{&(RES0__INSTANCE0.CTUD0.CD_T.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.CTUD0.CD_T.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.CTUD0.CD_T.CLK), BOOL_ENUM},
{&(RES0__INSTANCE0.CTUD0.CD_T.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.CTUD0.CD_T.M), BOOL_ENUM},
{&(RES0__INSTANCE0.CTUD0.CU_T.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.CTUD0.CU_T.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.CTUD0.CU_T.CLK), BOOL_ENUM},
{&(RES0__INSTANCE0.CTUD0.CU_T.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.CTUD0.CU_T.M), BOOL_ENUM},
{&(RES0__INSTANCE0.TON0.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.TON0.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.TON0.IN), BOOL_ENUM},
{&(RES0__INSTANCE0.TON0.PT), TIME_ENUM},
{&(RES0__INSTANCE0.TON0.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.TON0.ET), TIME_ENUM},
{&(RES0__INSTANCE0.TON0.STATE), SINT_ENUM},
{&(RES0__INSTANCE0.TON0.PREV_IN), BOOL_ENUM},
{&(RES0__INSTANCE0.TON0.CURRENT_TIME), TIME_ENUM},
{&(RES0__INSTANCE0.TON0.START_TIME), TIME_ENUM},
{&(RES0__INSTANCE0.R_TRIG1.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG1.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG1.CLK), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG1.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG1.M), BOOL_ENUM},
{&(RES0__INSTANCE0.CTUD1.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.CTUD1.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.CTUD1.CU), BOOL_ENUM},
{&(RES0__INSTANCE0.CTUD1.CD), BOOL_ENUM},
{&(RES0__INSTANCE0.CTUD1.R), BOOL_ENUM},
{&(RES0__INSTANCE0.CTUD1.LD), BOOL_ENUM},
{&(RES0__INSTANCE0.CTUD1.PV), INT_ENUM},
{&(RES0__INSTANCE0.CTUD1.QU), BOOL_ENUM},
{&(RES0__INSTANCE0.CTUD1.QD), BOOL_ENUM},
{&(RES0__INSTANCE0.CTUD1.CV), INT_ENUM},
{&(RES0__INSTANCE0.CTUD1.CD_T.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.CTUD1.CD_T.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.CTUD1.CD_T.CLK), BOOL_ENUM},
{&(RES0__INSTANCE0.CTUD1.CD_T.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.CTUD1.CD_T.M), BOOL_ENUM},
{&(RES0__INSTANCE0.CTUD1.CU_T.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.CTUD1.CU_T.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.CTUD1.CU_T.CLK), BOOL_ENUM},
{&(RES0__INSTANCE0.CTUD1.CU_T.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.CTUD1.CU_T.M), BOOL_ENUM},
{&(RES0__INSTANCE0.PID0.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.PID0.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.PID0.AUTO), BOOL_ENUM},
{&(RES0__INSTANCE0.PID0.PV), REAL_ENUM},
{&(RES0__INSTANCE0.PID0.SP), REAL_ENUM},
{&(RES0__INSTANCE0.PID0.X0), REAL_ENUM},
{&(RES0__INSTANCE0.PID0.KP), REAL_ENUM},
{&(RES0__INSTANCE0.PID0.TR), REAL_ENUM},
{&(RES0__INSTANCE0.PID0.TD), REAL_ENUM},
{&(RES0__INSTANCE0.PID0.CYCLE), TIME_ENUM},
{&(RES0__INSTANCE0.PID0.XOUT), REAL_ENUM},
{&(RES0__INSTANCE0.PID0.ERROR), REAL_ENUM},
{&(RES0__INSTANCE0.PID0.ITERM.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.PID0.ITERM.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.PID0.ITERM.RUN), BOOL_ENUM},
{&(RES0__INSTANCE0.PID0.ITERM.R1), BOOL_ENUM},
{&(RES0__INSTANCE0.PID0.ITERM.XIN), REAL_ENUM},
{&(RES0__INSTANCE0.PID0.ITERM.X0), REAL_ENUM},
{&(RES0__INSTANCE0.PID0.ITERM.CYCLE), TIME_ENUM},
{&(RES0__INSTANCE0.PID0.ITERM.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.PID0.ITERM.XOUT), REAL_ENUM},
{&(RES0__INSTANCE0.PID0.DTERM.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.PID0.DTERM.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.PID0.DTERM.RUN), BOOL_ENUM},
{&(RES0__INSTANCE0.PID0.DTERM.XIN), REAL_ENUM},
{&(RES0__INSTANCE0.PID0.DTERM.CYCLE), TIME_ENUM},
{&(RES0__INSTANCE0.PID0.DTERM.XOUT), REAL_ENUM},
{&(RES0__INSTANCE0.PID0.DTERM.X1), REAL_ENUM},
{&(RES0__INSTANCE0.PID0.DTERM.X2), REAL_ENUM},
{&(RES0__INSTANCE0.PID0.DTERM.X3), REAL_ENUM},
{&(RES0__INSTANCE0.PWM_CONTROLLER0.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.PWM_CONTROLLER0.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.PWM_CONTROLLER0.CHANNEL), SINT_ENUM},
{&(RES0__INSTANCE0.PWM_CONTROLLER0.FREQ), REAL_ENUM},
{&(RES0__INSTANCE0.PWM_CONTROLLER0.DUTY), REAL_ENUM},
{&(RES0__INSTANCE0.PWM_CONTROLLER0.SUCCESS), BOOL_ENUM},
{&(RES0__INSTANCE0.PWM_CONTROLLER0.INTERNAL_CH), SINT_ENUM},
{&(RES0__INSTANCE0.PWM_CONTROLLER0.INTERNAL_FREQ), REAL_ENUM},
{&(RES0__INSTANCE0.PWM_CONTROLLER0.INTERNAL_DUTY), REAL_ENUM},
{&(RES0__INSTANCE0.TON1.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.TON1.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.TON1.IN), BOOL_ENUM},
{&(RES0__INSTANCE0.TON1.PT), TIME_ENUM},
{&(RES0__INSTANCE0.TON1.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.TON1.ET), TIME_ENUM},
{&(RES0__INSTANCE0.TON1.STATE), SINT_ENUM},
{&(RES0__INSTANCE0.TON1.PREV_IN), BOOL_ENUM},
{&(RES0__INSTANCE0.TON1.CURRENT_TIME), TIME_ENUM},
{&(RES0__INSTANCE0.TON1.START_TIME), TIME_ENUM},
{&(RES0__INSTANCE0.R_TRIG2.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG2.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG2.CLK), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG2.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG2.M), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG3.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG3.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG3.CLK), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG3.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG3.M), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_NOT30_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_WORD_TO_BOOL81_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_OR275_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_NOT21_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_AND22_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_AND31_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG4.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG4.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG4.CLK), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG4.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG4.M), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_WORD_TO_BOOL82_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_OR80_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_AND5_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_NOT133_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_AND132_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG5.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG5.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG5.CLK), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG5.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG5.M), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_WORD_TO_BOOL268_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_OR271_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_XOR10_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_AND266_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_EQ137_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_EQ1_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_OR140_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_EQ7_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_EQ8_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_EQ2_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_OR20_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_EQ6_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_EQ29_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_EQ38_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_OR35_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_EQ41_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_EQ43_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_EQ45_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_OR46_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_EQ49_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_EQ51_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_EQ54_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_OR53_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_EQ59_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_EQ61_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_OR64_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_NOT163_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_AND159_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG6.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG6.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG6.CLK), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG6.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG6.M), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_NOT165_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_AND62_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG7.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG7.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG7.CLK), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG7.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG7.M), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_INT_TO_REAL168_OUT), REAL_ENUM},
{&(RES0__INSTANCE0._TMP_MUL166_OUT), REAL_ENUM},
{&(RES0__INSTANCE0._TMP_ADD169_OUT), REAL_ENUM},
{&(RES0__INSTANCE0._TMP_NOT176_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_AND261_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_MOVE177_ENO), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_MOVE177_OUT), INT_ENUM},
{&(RES0__INSTANCE0._TMP_SUB190_OUT), REAL_ENUM},
{&(RES0__INSTANCE0._TMP_DIV192_OUT), REAL_ENUM},
{&(RES0__INSTANCE0._TMP_INT_TO_REAL201_OUT), REAL_ENUM},
{&(RES0__INSTANCE0._TMP_MUL193_OUT), REAL_ENUM},
{&(RES0__INSTANCE0._TMP_REAL_TO_INT194_OUT), INT_ENUM},
{&(RES0__INSTANCE0._TMP_LIMIT198_OUT), INT_ENUM},
{&(RES0__INSTANCE0._TMP_MOVE47_ENO), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_MOVE47_OUT), INT_ENUM},
{&(RES0__INSTANCE0._TMP_MUL206_OUT), INT_ENUM},
{&(RES0__INSTANCE0._TMP_ADD37_OUT), INT_ENUM},
{&(RES0__INSTANCE0._TMP_INT_TO_REAL209_OUT), REAL_ENUM},
{&(RES0__INSTANCE0._TMP_LIMIT217_OUT), REAL_ENUM},
{&(RES0__INSTANCE0._TMP_REAL_TO_BOOL220_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_AND222_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_NOT68_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_NOT249_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_ADD242_OUT), REAL_ENUM},
{&(RES0__INSTANCE0._TMP_SUB243_OUT), REAL_ENUM},
{&(RES0__INSTANCE0._TMP_SEL248_OUT), REAL_ENUM},
{&(RES0__INSTANCE0._TMP_LIMIT252_OUT), REAL_ENUM},
{&(RES0__INSTANCE0._TMP_MOVE255_ENO), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_MOVE255_OUT), REAL_ENUM},
{&(RES0__INSTANCE0._TMP_WORD_TO_BOOL276_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_OR273_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_XOR74_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_NOT258_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_NOT263_OUT), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_MOVE264_ENO), BOOL_ENUM},
{&(RES0__INSTANCE0._TMP_MOVE264_OUT), INT_ENUM},
{&(RES0__INSTANCE0._TMP_DIV232_OUT), REAL_ENUM},
{&(RES0__INSTANCE0._TMP_ADD234_OUT), REAL_ENUM},
{&(RES0__INSTANCE0._TMP_DIV236_OUT), REAL_ENUM},
{&(RES0__INSTANCE0._TMP_DIV239_OUT), REAL_ENUM},
{&(RES0__INSTANCE0._TMP_MUL240_OUT), REAL_ENUM}
};

static const dbgvardsc_index_t retain_list[] = {
/* RES0__INSTANCE0.R_TRIG0.M */ 30,
/* RES0__INSTANCE0.CTUD0.CD_T.M */ 45,
/* RES0__INSTANCE0.CTUD0.CU_T.M */ 50,
/* RES0__INSTANCE0.R_TRIG1.M */ 65,
/* RES0__INSTANCE0.CTUD1.CD_T.M */ 80,
/* RES0__INSTANCE0.CTUD1.CU_T.M */ 85,
/* RES0__INSTANCE0.R_TRIG2.M */ 139,
/* RES0__INSTANCE0.R_TRIG3.M */ 144,
/* RES0__INSTANCE0.R_TRIG4.M */ 155,
/* RES0__INSTANCE0.R_TRIG5.M */ 165,
/* RES0__INSTANCE0.R_TRIG6.M */ 198,
/* RES0__INSTANCE0.R_TRIG7.M */ 205
};
static unsigned int retain_list_collect_cursor = 0;
static const unsigned int retain_list_size = sizeof(retain_list)/sizeof(dbgvardsc_index_t);

typedef void(*__for_each_variable_do_fp)(dbgvardsc_t*);
void __for_each_variable_do(__for_each_variable_do_fp fp)
{
    unsigned int i;
    for(i = 0; i < sizeof(dbgvardsc)/sizeof(dbgvardsc_t); i++){
        dbgvardsc_t *dsc = &dbgvardsc[i];
        if(dsc->type != UNKNOWN_ENUM) 
            (*fp)(dsc);
    }
}

#define __Unpack_desc_type dbgvardsc_t


#define __Unpack_case_t(TYPENAME)                                           \
        case TYPENAME##_ENUM :                                              \
            if(flags) *flags = ((__IEC_##TYPENAME##_t *)varp)->flags;       \
            if(value_p) *value_p = &((__IEC_##TYPENAME##_t *)varp)->value;  \
		    if(size) *size = sizeof(TYPENAME);                              \
            break;

#define __Unpack_case_p(TYPENAME)                                           \
        case TYPENAME##_O_ENUM :                                            \
        case TYPENAME##_P_ENUM :                                            \
            if(flags) *flags = ((__IEC_##TYPENAME##_p *)varp)->flags;       \
            if(value_p) *value_p = ((__IEC_##TYPENAME##_p *)varp)->value;   \
		    if(size) *size = sizeof(TYPENAME);                              \
            break;

#define __Is_a_string(dsc) (dsc->type == STRING_ENUM)   ||\
                           (dsc->type == STRING_P_ENUM) ||\
                           (dsc->type == STRING_O_ENUM)

static int UnpackVar(__Unpack_desc_type *dsc, void **value_p, char *flags, size_t *size)
{
    void *varp = dsc->ptr;
    /* find data to copy*/
    switch(dsc->type){
        __ANY(__Unpack_case_t)
        __ANY(__Unpack_case_p)
    default:
        return 0; /* should never happen */
    }
    return 1;
}



void Remind(unsigned int offset, unsigned int count, void * p);

extern int CheckRetainBuffer(void);
extern void InitRetain(void);

void __init_debug(void)
{
    /* init local static vars */
#ifndef TARGET_ONLINE_DEBUG_DISABLE
    trace_buffer_cursor = trace_buffer;
    trace_list_addvar_cursor = trace_list;
    trace_list_collect_cursor = trace_list;
    trace_buffer_state = BUFFER_EMPTY;

    force_buffer_cursor = force_buffer;
    force_list_addvar_cursor = force_list;
    force_list_apply_cursor = force_list;
#endif

    InitRetain();
    /* Iterate over all variables to fill debug buffer */
    if(CheckRetainBuffer()){
        unsigned int retain_offset = 0;
        retain_list_collect_cursor = 0;

        /* iterate over retain list */
        while(retain_list_collect_cursor < retain_list_size){
            void *value_p = NULL;
            size_t size;
            char* next_cursor;

            dbgvardsc_t *dsc = &dbgvardsc[
                retain_list[retain_list_collect_cursor]];

            UnpackVar(dsc, &value_p, NULL, &size);

            /* if buffer not full */
            Remind(retain_offset, size, value_p);
            /* increment cursor according size*/
            retain_offset += size;

            retain_list_collect_cursor++;
        }
    }else{
        char mstr[] = "RETAIN memory invalid - defaults used";
        LogMessage(LOG_WARNING, mstr, sizeof(mstr));
    }
}

extern void InitiateDebugTransfer(void);
extern void CleanupRetain(void);

extern unsigned long __tick;

void __cleanup_debug(void)
{
#ifndef TARGET_ONLINE_DEBUG_DISABLE
    trace_buffer_cursor = trace_buffer;
    InitiateDebugTransfer();
#endif    

    CleanupRetain();
}

void __retrieve_debug(void)
{
}

void Retain(unsigned int offset, unsigned int count, void * p);

/* Return size of all retain variables */
unsigned int GetRetainSize(void)
{
    unsigned int retain_size = 0;
    retain_list_collect_cursor = 0;

    /* iterate over retain list */
    while(retain_list_collect_cursor < retain_list_size){
        void *value_p = NULL;
        size_t size;
        char* next_cursor;

        dbgvardsc_t *dsc = &dbgvardsc[
            retain_list[retain_list_collect_cursor]];

        UnpackVar(dsc, &value_p, NULL, &size);

        retain_size += size;
        retain_list_collect_cursor++;
    }

    return retain_size;
}


extern void PLC_GetTime(IEC_TIME*);
extern int TryEnterDebugSection(void);
extern long AtomicCompareExchange(long*, long, long);
extern long long AtomicCompareExchange64(long long* , long long , long long);
extern void LeaveDebugSection(void);
extern void ValidateRetainBuffer(void);
extern void InValidateRetainBuffer(void);

#define __ReForceOutput_case_p(TYPENAME)                                                            \
        case TYPENAME##_P_ENUM :                                                                    \
        case TYPENAME##_O_ENUM :                                                                    \
            {                                                                                       \
                char *next_cursor = force_buffer_cursor + sizeof(TYPENAME);                         \
                if(next_cursor <= force_buffer_end ){                                               \
                    /* outputs real value must be systematically forced */                          \
                    if(vartype == TYPENAME##_O_ENUM)                                                \
                        /* overwrite value pointed by backup */                                     \
                        *((TYPENAME *)force_list_apply_cursor->value_pointer_backup) =  \
                            *((TYPENAME *)force_buffer_cursor);                                     \
                    /* inc force_buffer cursor */                                                   \
                    force_buffer_cursor = next_cursor;                                              \
                }else{                                                                              \
                    stop = 1;                                                                       \
                }                                                                                   \
            }                                                                                       \
            break;
void __publish_debug(void)
{
    InValidateRetainBuffer();
    
#ifndef TARGET_ONLINE_DEBUG_DISABLE 
    /* Check there is no running debugger re-configuration */
    if(TryEnterDebugSection()){
        /* Lock buffer */
        long latest_state = AtomicCompareExchange(
            &trace_buffer_state,
            BUFFER_EMPTY,
            BUFFER_FULL);
            
        /* If buffer was free */
        if(latest_state == BUFFER_EMPTY)
        {
            int stop = 0;
            /* Reset force list cursor */
            force_list_apply_cursor = force_list;

            /* iterate over force list */
            while(!stop && force_list_apply_cursor < force_list_addvar_cursor){
                dbgvardsc_t *dsc = &dbgvardsc[
                    force_list_apply_cursor->dbgvardsc_index];
                void *varp = dsc->ptr;
                __IEC_types_enum vartype = dsc->type;
                switch(vartype){
                    __ANY(__ReForceOutput_case_p)
                default:
                    break;
                }
                force_list_apply_cursor++;
            }

            /* Reset buffer cursor */
            trace_buffer_cursor = trace_buffer;
            /* Reset trace list cursor */
            trace_list_collect_cursor = trace_list;

            /* iterate over trace list */
            while(trace_list_collect_cursor < trace_list_addvar_cursor){
                void *value_p = NULL;
                size_t size;
                char* next_cursor;

                dbgvardsc_t *dsc = &dbgvardsc[
                    trace_list_collect_cursor->dbgvardsc_index];

                UnpackVar(dsc, &value_p, NULL, &size);

                /* copy visible variable to buffer */;
                if(__Is_a_string(dsc)){
                    /* optimization for strings */
                    /* assume NULL terminated strings */
                    size = ((STRING*)value_p)->len + 1;
                }

                /* compute next cursor positon.*/
                next_cursor = trace_buffer_cursor + size;
                /* check for buffer overflow */
                if(next_cursor < trace_buffer_end)
                    /* copy data to the buffer */
                    memcpy(trace_buffer_cursor, value_p, size);
                else
                    /* stop looping in case of overflow */
                    break;
                /* increment cursor according size*/
                trace_buffer_cursor = next_cursor;
                trace_list_collect_cursor++;
            }
            
            /* Leave debug section,
             * Trigger asynchronous transmission 
             * (returns immediately) */
            InitiateDebugTransfer(); /* size */
        }
        LeaveDebugSection();
    }
#endif
    unsigned int retain_offset = 0;
    /* when not debugging, do only retain */
    retain_list_collect_cursor = 0;

    /* iterate over retain list */
    while(retain_list_collect_cursor < retain_list_size){
        void *value_p = NULL;
        size_t size;
        char* next_cursor;

        dbgvardsc_t *dsc = &dbgvardsc[
            retain_list[retain_list_collect_cursor]];

        UnpackVar(dsc, &value_p, NULL, &size);

        /* if buffer not full */
        Retain(retain_offset, size, value_p);
        /* increment cursor according size*/
        retain_offset += size;

        retain_list_collect_cursor++;
    }
    ValidateRetainBuffer();
}

#ifndef TARGET_ONLINE_DEBUG_DISABLE

#define TRACE_LIST_OVERFLOW    1
#define FORCE_LIST_OVERFLOW    2
#define FORCE_BUFFER_OVERFLOW  3

#define __ForceVariable_case_t(TYPENAME)                                                \
        case TYPENAME##_ENUM :                                                          \
            /* add to force_list*/                                                      \
            force_list_addvar_cursor->dbgvardsc_index = idx;                            \
            ((__IEC_##TYPENAME##_t *)varp)->flags |= __IEC_FORCE_FLAG;                  \
            ((__IEC_##TYPENAME##_t *)varp)->value = *((TYPENAME *)force);               \
            break;
#define __ForceVariable_case_p(TYPENAME)                                                \
        case TYPENAME##_P_ENUM :                                                        \
        case TYPENAME##_O_ENUM :                                                        \
            {                                                                           \
                char *next_cursor = force_buffer_cursor + sizeof(TYPENAME);             \
                if(next_cursor <= force_buffer_end ){                                   \
                    /* add to force_list*/                                              \
                    force_list_addvar_cursor->dbgvardsc_index = idx;                    \
                    /* save pointer to backup */                                        \
                    force_list_addvar_cursor->value_pointer_backup =                    \
                        ((__IEC_##TYPENAME##_p *)varp)->value;                          \
                    /* store forced value in force_buffer */                            \
                    *((TYPENAME *)force_buffer_cursor) = *((TYPENAME *)force);          \
                    /* replace pointer with pointer to force_buffer */                  \
                    ((__IEC_##TYPENAME##_p *)varp)->value =                             \
                        (TYPENAME *)force_buffer_cursor;                                \
                    (((__IEC_##TYPENAME##_p *)varp)->fvalue) = *((TYPENAME *)force);    \
                    /* mark variable as forced */                                       \
                    ((__IEC_##TYPENAME##_p *)varp)->flags |= __IEC_FORCE_FLAG;          \
                    /* inc force_buffer cursor */                                       \
                    force_buffer_cursor = next_cursor;                                  \
                    /* outputs real value must be systematically forced */              \
                    if(vartype == TYPENAME##_O_ENUM)                                    \
                        *(((__IEC_##TYPENAME##_p *)varp)->value) = *((TYPENAME *)force);\
                } else {                                                                \
                    error_code = FORCE_BUFFER_OVERFLOW;                                 \
                    goto error_cleanup;                                                 \
                }                                                                       \
            }                                                                           \
            break;


void ResetDebugVariables(void);

int RegisterDebugVariable(dbgvardsc_index_t idx, void* force)
{
    int error_code = 0;
    if(idx < sizeof(dbgvardsc)/sizeof(dbgvardsc_t)){
        /* add to trace_list, inc trace_list_addvar_cursor*/
        if(trace_list_addvar_cursor <= trace_list_end){
            trace_list_addvar_cursor->dbgvardsc_index = idx;
            trace_list_addvar_cursor++;
        } else {
            error_code = TRACE_LIST_OVERFLOW;
            goto error_cleanup;
        }
        if(force){
            if(force_list_addvar_cursor <= force_list_end){
                dbgvardsc_t *dsc = &dbgvardsc[idx];
                void *varp = dsc->ptr;
                __IEC_types_enum vartype = dsc->type;

                switch(vartype){
                    __ANY(__ForceVariable_case_t)
                    __ANY(__ForceVariable_case_p)
                default:
                    break;
                }
                /* inc force_list cursor */
                force_list_addvar_cursor++;
            } else {
                error_code = FORCE_LIST_OVERFLOW;
                goto error_cleanup;
            }
        }
    }
    return 0;

error_cleanup:
    ResetDebugVariables();
    trace_buffer_state = BUFFER_EMPTY;
    return error_code;
    
}

#define ResetForcedVariable_case_t(TYPENAME)                                            \
        case TYPENAME##_ENUM :                                                          \
            ((__IEC_##TYPENAME##_t *)varp)->flags &= ~__IEC_FORCE_FLAG;                 \
            /* for local variable we don't restore original value */                    \
            /* that can be added if needed, but it was like that since ever */          \
            break;

#define ResetForcedVariable_case_p(TYPENAME)                                            \
        case TYPENAME##_P_ENUM :                                                        \
        case TYPENAME##_O_ENUM :                                                        \
            ((__IEC_##TYPENAME##_p *)varp)->flags &= ~__IEC_FORCE_FLAG;                 \
            /* restore backup to pointer */                                             \
            ((__IEC_##TYPENAME##_p *)varp)->value =                                     \
                force_list_apply_cursor->value_pointer_backup;                          \
            break;

void ResetDebugVariables(void)
{
    /* Reset trace list */
    trace_list_addvar_cursor = trace_list;

    force_list_apply_cursor = force_list;
    /* Restore forced variables */
    while(force_list_apply_cursor < force_list_addvar_cursor){
        dbgvardsc_t *dsc = &dbgvardsc[
            force_list_apply_cursor->dbgvardsc_index];
        void *varp = dsc->ptr;
        switch(dsc->type){
            __ANY(ResetForcedVariable_case_t)
            __ANY(ResetForcedVariable_case_p)
        default:
            break;
        }
        /* inc force_list cursor */
        force_list_apply_cursor++;
    } /* else TODO: warn user about failure to force */ 

    /* Reset force list */
    force_list_addvar_cursor = force_list;
    /* Reset force buffer */
    force_buffer_cursor = force_buffer;
}

void FreeDebugData(void)
{
    /* atomically mark buffer as free */
    AtomicCompareExchange(
        &trace_buffer_state,
        BUFFER_FULL,
        BUFFER_EMPTY);
}
int WaitDebugData(unsigned long *tick);
/* Wait until debug data ready and return pointer to it */
int GetDebugData(unsigned long *tick, unsigned long *size, void **buffer){
    int wait_error = WaitDebugData(tick);
    if(!wait_error){
        *size = trace_buffer_cursor - trace_buffer;
        *buffer = trace_buffer;
    }
    return wait_error;
}
#endif
#endif

