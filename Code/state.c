#include "state.h"

char req_state;
char cur_state;
char num_samples;

char disp_type;

int tare_offset;
int global_weight;

void retrieveState()
{
    cur_state = ST_WEIGH;
    req_state = ST_NONE;
    disp_type = GRAMS | DISP_LCD;
    tare_offset = 0;
    num_samples = 20;
}
void saveState()
{
    
}