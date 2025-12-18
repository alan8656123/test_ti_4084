#include "ti_msp_dl_config.h"
#include "BAT_MODULE.h"
#include "TIMER_MODULE.h"

#define ValueBuf 1576 // 13.0V
uint32_t RealBatBuf = 0U;
static uint8_t Bat3sCnt = 0U;
static uint32_t BatAdBuf = 0U;
static uint16_t ValueBuf1 = 0U;
static uint16_t BatBuf = 0U;

bool IN_TEST_MODE=0;

static uint16_t testbuf[16] = {0U};


volatile bool gCheckADC = false;
void InitialBatRam(void);

void InitialBatRam(void)
{
    BAT_CYCLE_FLAG = 0;
    Bat3sCnt = 0U;
    RealBatBuf = BatAdBuf = 0U;
    ValueBuf1 = 0U;
    BatBuf = 0U;
}

void getBatValue(void){
    DL_ADC12_enableDMA(ADC12_0_INST);
    DL_ADC12_startConversion(ADC12_0_INST);
    while (false == gCheckADC) {
        //__WFI();
    }
    gCheckADC = false;
    DL_ADC12_stopConversion(ADC12_0_INST);
    for (uint8_t LpCnt = 0; LpCnt < 12; LpCnt++)
    {
        BatAdBuf += DL_ADC12_getMemResult(ADC12_0_INST, LpCnt);
    }
    BatAdBuf = BatAdBuf /12;
}

void InitialBat(void)
{
    uint32_t CalTempBuf1, CalTempBuf2;
    uint8_t LpCnt;

    BatAdBuf = 0;
    getBatValue();

    if (BatAdBuf >= ValueBuf)
    {
        ValueBuf1 = (uint16_t)((ValueBuf / 130) * 2);
    }
    else
    {
        ValueBuf1 = (uint16_t)((ValueBuf / 130) * 3);
    }

    CalTempBuf1 = 13 * (BatAdBuf + ValueBuf1);
    CalTempBuf2 = (CalTempBuf1 * 100) / ValueBuf;
    RealBatBuf = CalTempBuf2;

    BatAdBuf = 0;


    
}

void BatManager(void)
{
    uint32_t TempCalBuf1, TempCalBuf2;

    if (BAT_CYCLE_FLAG) /* 20ms */
    {
        BAT_CYCLE_FLAG = false;
        Bat3sCnt++;

        // test mode 500ms, none_test mode 3s
        if (((IN_TEST_MODE == 1) && (Bat3sCnt >= 25)) || ((IN_TEST_MODE == 0) && (Bat3sCnt >= 150)))
        {
            Bat3sCnt = 0;
            
            getBatValue();

            // ValueBuf is the AD_value when 13V
            if (BatAdBuf >= ValueBuf)
            {
                ValueBuf1 = (uint16_t)((ValueBuf / 130) * 2);
            }
            else
            {
                ValueBuf1 = (uint16_t)((ValueBuf / 130) * 3);
            }

            TempCalBuf1 = 13 * (BatAdBuf + ValueBuf1);
            TempCalBuf2 = (TempCalBuf1 * 1000) / ValueBuf;

            // rounding
            if ((TempCalBuf2 % 10) >= 5)
            {
                TempCalBuf2 += 10;
            }
            TempCalBuf2 /= 10;
            RealBatBuf = TempCalBuf2;
            BatAdBuf = 0;
        }
    DL_ADC12_enableDMA(ADC12_0_INST);
        DL_ADC12_startConversion(ADC12_0_INST);
    }
}

void ADC12_0_INST_IRQHandler(void)
{
    switch (DL_ADC12_getPendingInterrupt(ADC12_0_INST)) {
        case DL_ADC12_IIDX_MEM11_RESULT_LOADED:
            gCheckADC = true;
            break;
        default:
            break;
    }
}
