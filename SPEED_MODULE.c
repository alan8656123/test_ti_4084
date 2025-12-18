
#include "ti_msp_dl_config.h"
#include "SPEED_MODULE.h"
#include "TIMER_MODULE.h"

uint16_t RealSpeedKmhBuf = 0, NewSpeedKmhBuf = 0;
uint16_t RealSpeedMphBuf = 0, NewSpeedMphBuf = 0;
volatile uint16_t  DispSpeedKmhBuf = 0, DispSpeedMphBuf = 0;
uint16_t SpeedBuf[8], AveSpeedBuf[5];
uint16_t Speed12bBuf[10], Speed12bCnt; 
volatile uint32_t REALSPEEDPULSE;

bool SPEED_DOWN_FLAG = 0;


static uint32_t SpeedBuf1 = 0U;
static uint32_t SpeedBuf2 = 0U;
static uint32_t SpeedBuf3 = 0U;
static uint32_t SpeedBuf4 = 0U;
static uint8_t SpeedAveCnt = 0U;
static uint8_t SpeedPulseCnt = 0U;

#define	cSpeed60KmhValue	    113095//712500
#define	cSpeedTimeOverValue	    90 
bool SPEED_IN_FLAG = 0;
bool NEW_FRIST_PULSE_FLAG = 0;
void CaptureNewSpeedPulse(void);
void CalculatePulseChangeToSpeed(void);

void SpeedManager(void)
{
    CaptureNewSpeedPulse();
    CalculatePulseChangeToSpeed();
}

void CaptureNewSpeedPulse(void)
{
    if (SPEED_IN_FLAG) //speedFlag
    {
        SPEED_IN_FLAG = 0;

        if (NEW_FRIST_PULSE_FLAG)
        {
            SpeedBuf2++;
            SpeedBuf1 += REALSPEEDPULSE;
        }
        else
        {
            if (++SpeedPulseCnt >= 1)    /* Debounce 8 time period */
            {
                SpeedPulseCnt = 0;
                NEW_FRIST_PULSE_FLAG = 1;
                SpeedBuf1 = SpeedBuf2 = 0;
            }
        }
    }

    if (SpeedTimeOverBuf >= cSpeedTimeOverValue)
    {
        SpeedTimeOverBuf = 0U;
        SPEED_CYCLE_FLAG = 0U;
        SPEED_IN_FLAG = 0U;
        NEW_FRIST_PULSE_FLAG = 0U;
        SpeedBuf2 = 0U;
        SpeedPulseCnt = 0U;
        SpeedAveCnt = 0U;
        RealSpeedKmhBuf = 0U;
        NewSpeedKmhBuf = 0U;
        RealSpeedMphBuf = 0U;
        NewSpeedMphBuf = 0U;
        DispSpeedKmhBuf = 0U;
        DispSpeedMphBuf = 0U;
        SpeedBuf[3] = SpeedBuf[2] = SpeedBuf[1] = SpeedBuf[0] = 0U;
    }
}

void UpdateSpeedBuf(void)
{
    RealSpeedKmhBuf = NewSpeedKmhBuf;
    DispSpeedKmhBuf = NewSpeedKmhBuf;
    RealSpeedMphBuf = (uint16_t)(NewSpeedKmhBuf / 1.609);
    DispSpeedMphBuf = (uint16_t)(NewSpeedKmhBuf / 1.609);
}

void CalculatePulseChangeToSpeed(void)
{
    if (SPEED_CYCLE_FLAG == 1 && NEW_FRIST_PULSE_FLAG == 1)
    {
        SPEED_CYCLE_FLAG = 0;

        if (SpeedBuf2 > 0)
        {
            SpeedBuf3 = SpeedBuf1 / SpeedBuf2;

            SpeedBuf4 = cSpeed60KmhValue / SpeedBuf3;
            NewSpeedKmhBuf = (unsigned int)SpeedBuf4;
            if (NewSpeedKmhBuf >= 330)
                NewSpeedKmhBuf = 330;
        }

        SpeedBuf1 = SpeedBuf2 = 0;

        SpeedBuf[3] = SpeedBuf[2];
        SpeedBuf[2] = SpeedBuf[1];
        SpeedBuf[1] = SpeedBuf[0];
        SpeedBuf[0] = NewSpeedKmhBuf;

        if (++SpeedAveCnt >= 2)
            SpeedAveCnt = 2;

        NewSpeedKmhBuf = SpeedBuf[1] + SpeedBuf[0];
        NewSpeedKmhBuf = NewSpeedKmhBuf / SpeedAveCnt;

        if (RealSpeedKmhBuf <= 10)
        {
            if (NewSpeedKmhBuf >= RealSpeedKmhBuf)
                SPEED_DOWN_FLAG = 0;
            else
                SPEED_DOWN_FLAG = 1;

            RealSpeedKmhBuf = NewSpeedKmhBuf;
        }
        else
        {
            if (SPEED_DOWN_FLAG)
            {
                if (NewSpeedKmhBuf <= RealSpeedKmhBuf)		 // || (NewSpeedMphBuf < RealSpeedMphBuf)
                {
                    RealSpeedKmhBuf = NewSpeedKmhBuf;
                }
                else if (NewSpeedKmhBuf > (RealSpeedKmhBuf + 2))		// || (NewSpeedMphBuf >= (RealSpeedMphBuf + 2))
                {
                    RealSpeedKmhBuf = NewSpeedKmhBuf;
                    SPEED_DOWN_FLAG = 0;
                }
            }
            else
            {
                if (NewSpeedKmhBuf >= RealSpeedKmhBuf)				// || (NewSpeedMphBuf > RealSpeedMphBuf)
                {
                    RealSpeedKmhBuf = NewSpeedKmhBuf;
                }
                else if (NewSpeedKmhBuf < RealSpeedKmhBuf - 2)			// || (NewSpeedMphBuf + 2 <= RealSpeedMphBuf)
                {
                    RealSpeedKmhBuf = NewSpeedKmhBuf;
                    SPEED_DOWN_FLAG = 1;
                }
            }
        }
    }
    if (AVEDISP_FLAG == 1)
    {
        AVEDISP_FLAG = 0;
        AveSpeedBuf[3] = AveSpeedBuf[2];
        AveSpeedBuf[2] = AveSpeedBuf[1];
        AveSpeedBuf[1] = AveSpeedBuf[0];
        AveSpeedBuf[0] = RealSpeedKmhBuf;

        AveSpeedBuf[4] = (AveSpeedBuf[3] + AveSpeedBuf[2] + AveSpeedBuf[1] + AveSpeedBuf[0]) >> 2U;
        DispSpeedKmhBuf = AveSpeedBuf[4];

        DispSpeedMphBuf = (uint16_t)(DispSpeedKmhBuf / 1.609);
    }
}

static uint32_t tempbuf = 0U;
static uint32_t NEWPULSE = 0U;
static uint32_t NEWSPEEDPULSE = 0U;
static uint32_t OLDSPEEDPULSE = 0U;
//group0 include WWDT0,WWDT1,DEBUGSS,FLASHCTL,WUC FSUB0,WUC FSUB1,PMCU (SYSCTL)
//group1 include GPIO0,GPIO1,COMP0.COMP1,COMP2,TRNG
void GROUP1_IRQHandler(void)
{
    switch (DL_GPIO_getPendingInterrupt(GPIO_SPEED_IN_PORT)) {
        case GPIO_SPEED_IN_PIN_SPEED_IN_IIDX :
                NEWPULSE = (TIMER_65536_INST_LOAD_VALUE  - (DL_TimerG_getTimerCount(TIMER_65536_INST)));
                tempbuf = TMR2H;
                NEWPULSE += (tempbuf << 16);
                OLDSPEEDPULSE = NEWSPEEDPULSE;
                NEWSPEEDPULSE = NEWPULSE;
                if (NEWSPEEDPULSE >= OLDSPEEDPULSE)
                {
                    REALSPEEDPULSE = (NEWSPEEDPULSE - OLDSPEEDPULSE);
                    SPEED_IN_FLAG = 1U;
                }
                SpeedTimeOverBuf = 0;
            break;
        default:
            break;
    }
}
