#include "ti_msp_dl_config.h"
#include "TIMER_MODULE.h"

#define millisecond_cycle 32000 
//CLOCK
uint8_t rtcHour=12;
uint8_t rtcMin=0;
uint8_t rtcSec=0;
uint32_t rtcSecCounter = 0;

//LCD
bool lcdFlag =false;

//BUTTON
bool BUTTON_CYCLE_FLAG =false;
uint8_t buttonCounter = 0;
bool SET_CLOCK_MODE = 0;

void delay(uint32_t times){
    delay_cycles(times*millisecond_cycle);
}

void TimerManager(void){
     if(timerFlag == true){
        timerFlag = false;
        
        lcdFlag = true;     //5ms period == 200HZ
        
        /*if(timer_count++%200 == 0 ){ //1s
            DL_GPIO_togglePins(GPIO_LEDS_PORT,GPIO_LEDS_USER_LED_1_PIN );
        }*/
        //simpley use timer to do rtc, it should use real RTC later! 
        if(++rtcSecCounter>=200 ){ //1s
            rtcSecCounter = 0;
            if(++rtcSec>=60){
                rtcHour = DL_RTC_getCalendarHoursBinary(RTC);
                rtcMin = DL_RTC_getCalendarMinutesBinary(RTC);
                rtcSec = DL_RTC_getCalendarSecondsBinary(RTC);
            }
        }

        if(++buttonCounter>=4){
            buttonCounter = 0;
            BUTTON_CYCLE_FLAG = true;
        }
    }
}


void TIMER_0_INST_IRQHandler(void)
{
    timerFlag = true;
    /*switch (DL_TimerG_getPendingInterrupt(TIMER_0_INST)) {
        case DL_TIMER_IIDX_ZERO:
            //timerFlag = true;      
            break;
        default:
            break;
    }*/
}
