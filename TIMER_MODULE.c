#include "ti_msp_dl_config.h"
#include "TIMER_MODULE.h"

void delay(uint32_t times){
    delay_cycles(times*32000);
}
