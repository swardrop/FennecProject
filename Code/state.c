#include "state.h"
#include "remoteinterface/calibrate.h"

char req_state;
char cur_state;
char num_samples;
char st_chng_rs232_flag;

char disp_type;

int tare_offset;
int global_weight;
int shut_off_timer_count;

rom far char req_state_rom = ST_NONE;
rom far char cur_state_rom = ST_WEIGH;
rom far char num_samples_rom = 30;

rom far char disp_type_rom = GRAMS | DISP_LCD;

rom far int tare_offset_rom = 0;

void retrieveState()
{
    cur_state = cur_state_rom;     
    req_state = req_state_rom;
    disp_type = disp_type_rom;
    tare_offset = tare_offset_rom;
    num_samples = num_samples_rom;
    st_chng_rs232_flag = 0;
    shut_off_timer_count = TWO_MINUTES;

    // Calibrate defaults
    cal_count_ref[0] = 257;
    cal_count_ref[1] = 491;
    cal_count_ref[2] = 732;

    cal_m[0] = 17579;
    cal_m[1] = 17504;
    cal_m[2] = 16995;
    cal_m[3] = 17138;

    cal_b[0] = -26;
    cal_b[1] = -25;
    cal_b[2] = -9;
    cal_b[3] = -16;
}
void saveState()
{
    cur_state_rom = cur_state;     
    req_state_rom = req_state;
    disp_type_rom = disp_type;
    tare_offset_rom = tare_offset;
    num_samples_rom = num_samples;
}