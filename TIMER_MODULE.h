#ifndef TIMER_MODULE_H_
#define TIMER_MODULE_H_

void delay(uint32_t times);
void TIMER_0_INST_IRQHandler(void);
void TimerManager(void);
//volatile is very important! If there is no volatile, timerFlag may not work in interrupt
volatile bool timerFlag;
extern uint8_t rtcHour;
extern uint8_t rtcMin;
extern uint8_t rtcSec;
extern uint8_t HourBuf, MinBuf;

//LCD
extern bool lcdFlag;
extern bool Flash500msFlag;

//BUTTON
extern bool BUTTON_CYCLE_FLAG;
//uint8_t buttonCounter = 0;
extern bool SET_CLOCK_MODE;


//SPEED
extern uint16_t SpeedTimeOverBuf;
extern bool SPEED_CYCLE_FLAG;
extern bool AVEDISP_FLAG;
extern volatile uint16_t TMR2H;


//BAT
extern bool BAT_CYCLE_FLAG;
#endif