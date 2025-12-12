#include "ti_msp_dl_config.h"
#include "TIMER_MODULE.h"


#define millisecond_cycle 8000 

void delay(uint32_t times){
    delay_cycles(times*millisecond_cycle);
}
