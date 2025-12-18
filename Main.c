#include "ti_msp_dl_config.h"
#include "TIMER_MODULE.h"
#include "LED_MODULE.h"
#include "LCD_MODULE.h"
#include "BUTTON_MODULE.h"
#include "SPEED_MODULE.h"



int main(void)
{
    SYSCFG_DL_init();
    /* Set LED to indicate start of transfer */
    NVIC_EnableIRQ(I2C_INST_INT_IRQN);
    DL_SYSCTL_disableSleepOnExit();

    NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
    DL_TimerG_startCounter(TIMER_0_INST);

    DL_RTC_enableClockControl(RTC);

    
    NVIC_EnableIRQ(GPIO_SPEED_IN_INT_IRQN);


    NVIC_EnableIRQ(TIMER_65536_INST_INT_IRQN);
    DL_TimerA_startCounter(TIMER_65536_INST);

    Initial_LCD();
    InitialLed();
    LCD_open_anime();  
    delay(1000);
    while(1){
        TimerManager();
        LcdManager();
        ButtonManager();
        SpeedManager();
    }
}
