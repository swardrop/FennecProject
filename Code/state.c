#include "state.h"

char req_state;
char cur_state;
char num_samples;

char disp_type;

int tare_offset;

char retrieve_state()
{
    cur_state = ST_WEIGH;
    req_state = ST_NONE;
    tare_offset = 0;
}
void save_state()
{
    
}