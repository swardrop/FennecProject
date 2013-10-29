#include "state.h"

char req_state;
char cur_state;
char num_samples;
char st_chng_rs232_flag;

char disp_type;

int tare_offset;
int global_weight;
int shut_off_timer_count;

void retrieveState()
{
    cur_state = ST_COUNT_I;     // Note when get from EEPROM, if it is a Factory, default to weigh.
    req_state = ST_NONE;
    disp_type = GRAMS | DISP_LCD;
    tare_offset = 0;
    num_samples = 30;
    st_chng_rs232_flag = 0;
    shut_off_timer_count = TWO_MINUTES;
}
void saveState()
{
    
}