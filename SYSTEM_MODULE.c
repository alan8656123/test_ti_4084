#include "ti_msp_dl_config.h"
#include "SYSTEM_MODULE.h"
#include "TIMER_MODULE.h"
#include "LCD_MODULE.h"
#include "BAT_MODULE.h"
#include "LED_MODULE.h"

bool FIRST_START_FLAG = 0;

static uint8_t SoftversionEnterCnt = 0;
static uint8_t PowerHazardOnCnt = 0;
static uint8_t PowerHazardOffCnt = 0;
static uint8_t PowerOnCnt = 0;
static uint8_t PowerOffCnt = 0;


bool pIGN = 1;
bool IGN_ON_FLAG = 0;
bool OPENING_FLAG = 0 ;
void PowerManager(void)
{
    //5ms
    if(POWER_CYCLE_FLAG){
        POWER_CYCLE_FLAG=false;

        if (pIGN == 1) // IGN ON
        {
            PowerOffCnt = 0;
            if ((FIRST_START_FLAG == 0) || (IGN_ON_FLAG == 0))
            {
                if (++PowerOnCnt >= 75)
                {
                    PowerOnCnt = 0;
                    PowerIgnOn();
                }
            }
            else
            {
                PowerOnCnt = 0;
            }
        }
        else // IGN OFF
        {
            PowerOnCnt = 0;
            if ((FIRST_START_FLAG == 0) || (IGN_ON_FLAG == 1))
            {
                if (++PowerOffCnt >= 50)
                {
                    if (OPENING_FLAG == 0)
                    {
                        PowerOffCnt = 0;
                        PowerIgnOff();
                    }
                }
            }
            else
            {
                PowerOffCnt = 0;
            }
        }


        if ((OPENING_FLAG == 1) && (IGN_ON_FLAG))
        {
            LCD_open_anime();  
        }

    }
}



void PowerIgnOn(void)
{
    //1.initial flag
    FIRST_START_FLAG = 1;
    IGN_ON_FLAG = 1;
    OPENING_FLAG = 1;

    Initial_LCD();
    InitialLed();
    InitialBat();
}

void PowerIgnOff(void)
{
}
