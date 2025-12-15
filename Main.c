#include "ti_msp_dl_config.h"
#include "TIMER_MODULE.h"
#include "LCD_MODULE.h"


int main(void)
{
    SYSCFG_DL_init();
    /* Set LED to indicate start of transfer */
    NVIC_EnableIRQ(I2C_INST_INT_IRQN);
    DL_SYSCTL_disableSleepOnExit();

    NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
    DL_TimerG_startCounter(TIMER_0_INST);

    DL_RTC_enableClockControl(RTC);

    Initial_LCD();
    //LCD_demo();
    LCD_open_anime();  
    delay(1000);
    while(1){
        LcdManager();
        TimerManager();
    }
}

