#include "ti_msp_dl_config.h"
#include "TIMER_MODULE.h"

#define millisecond_cycle 32000 
//CLOCK
uint8_t rtcHour=12;
uint8_t rtcMin=0;
uint8_t rtcSec=0;
uint32_t rtcSecCounter = 0;
uint8_t HourBuf, MinBuf;

//LCD
bool lcdFlag =false;

//BUTTON
bool BUTTON_CYCLE_FLAG =false;
uint8_t buttonCounter = 0;
bool SET_CLOCK_MODE = 0;

//seccounter
uint8_t count500ms = 0;


bool Flash500msFlag = 0;

//SPEED
uint16_t speedcount=0;
uint16_t SpeedTimeOverBuf = 0;
bool SPEED_CYCLE_FLAG = 0;
bool AVEDISP_FLAG =0;
volatile uint16_t TMR2H=0;
volatile bool TIMER65536_flag=0;

//BAT
bool BAT_CYCLE_FLAG = false;

void delay(uint32_t times){
    delay_cycles(times*millisecond_cycle);
}

void TimerManager(void){
    if(TIMER65536_flag){
        TIMER65536_flag = false;
        TMR2H++;
    }
     if(timerFlag == true){
         ++SpeedTimeOverBuf;
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
            BAT_CYCLE_FLAG = true;
        }
        if(++speedcount>=20){//100ms
            speedcount = 0;
            SPEED_CYCLE_FLAG = 1;
            AVEDISP_FLAG = 1U;
        }
        if(++count500ms>=100){
            count500ms = 0;
            Flash500msFlag = !Flash500msFlag;
        }
    }
}


void TIMER_0_INST_IRQHandler(void)
{
    switch (DL_TimerG_getPendingInterrupt(TIMER_0_INST)) {
        case DL_TIMER_IIDX_ZERO:
            timerFlag = true;      
            break;
        default:
            break;
    }
}

void TIMER_65536_INST_IRQHandler(void)
{
    switch (DL_TimerG_getPendingInterrupt(TIMER_65536_INST)) {
        case DL_TIMER_IIDX_LOAD :
            TIMER65536_flag = 1;
            //TMR2H++;
            //DL_GPIO_togglePins(GPIO_LEDS_PORT,GPIO_LEDS_USER_LED_1_PIN );
            break;
        default:
            break;
    }
}