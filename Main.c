#include "ti_msp_dl_config.h"
#include "LCD_MODULE.h"




int main(void)
{
    SYSCFG_DL_init();
    /* Set LED to indicate start of transfer */
    NVIC_EnableIRQ(I2C_INST_INT_IRQN);
    DL_SYSCTL_disableSleepOnExit();

    Initial_LCD();
    LCD_demo();
}
