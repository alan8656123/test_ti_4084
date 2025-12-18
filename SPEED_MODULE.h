#ifndef SPEED_MODULE_H
#define SPEED_MODULE_H

void SpeedManager(void);
void UpdateSpeedBuf(void);
extern uint16_t SpeedTimeOverBuf;
extern uint16_t RealSpeedKmhBuf, NewSpeedKmhBuf;
extern uint16_t RealSpeedMphBuf, NewSpeedMphBuf;
extern volatile uint16_t DispSpeedKmhBuf, DispSpeedMphBuf;
extern uint16_t SpeedBuf[8], AveSpeedBuf[5];
extern uint16_t Speed12bBuf[10], Speed12bCnt; 
extern volatile uint32_t REALSPEEDPULSE;
#endif