
#include "ti_msp_dl_config.h"
#include "SPEED_MODULE.h"

uint16_t SpeedTimeOverBuf = 0;
uint16_t RealSpeedKmhBuf = 0, NewSpeedKmhBuf = 0;
uint16_t RealSpeedMphBuf = 0, NewSpeedMphBuf = 0;
uint16_t DispSpeedKmhBuf = 0, DispSpeedMphBuf = 0;
uint16_t SpeedBuf[8], AveSpeedBuf[5];
uint16_t Speed12bBuf[10], Speed12bCnt; 
uint32_t REALSPEEDPULSE;

void CaptureNewSpeedPulse(void);
void CalculatePulseChangeToSpeed(void);

void SpeedManager(void)
{

}

void CaptureNewSpeedPulse(void)
{
    
}

void UpdateSpeedBuf(void)
{
   
}

void CalculatePulseChangeToSpeed(void)
{
   
}