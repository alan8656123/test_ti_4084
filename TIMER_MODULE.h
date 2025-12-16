#ifndef TIMER_MODULE_H_
#define TIMER_MODULE_H_

void delay(uint32_t times);
void TIMER_0_INST_IRQHandler(void);
void TimerManager(void);
//volatile is very important! If there is no volatile, timerFlag may not work in interrupt
volatile bool timerFlag;
extern uint8_t rtcHour;
extern uint8_t rtcMin;
//rtcSec only use in timer


extern bool lcdFlag;

extern bool buttonFlag;
//uint8_t buttonCounter = 0;

#endif