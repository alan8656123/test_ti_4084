#include "ti_msp_dl_config.h"
#include "LCD_MODULE.h"


int main(void)
{
    SYSCFG_DL_init();
    /* Set LED to indicate start of transfer */
    NVIC_EnableIRQ(I2C_INST_INT_IRQN);
    DL_SYSCTL_disableSleepOnExit();


    NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
    DL_TimerG_startCounter(TIMER_0_INST);

    Initial_LCD();
    LCD_demo();
}


void TIMER_0_INST_IRQHandler(void)
{
    static uint32_t timer_count = 0;
    switch (DL_TimerG_getPendingInterrupt(TIMER_0_INST)) {
        case DL_TIMER_IIDX_ZERO:
            timer_count++;
            if(timer_count%1000 == 0 ){ //5s
                DL_GPIO_togglePins(GPIO_LEDS_PORT,GPIO_LEDS_USER_LED_1_PIN );
            }
            break;
        default:
            break;
    }
}
