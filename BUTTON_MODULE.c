#include "ti_msp_dl_config.h"
#include "BUTTON_MODULE.h"
#include "SPEED_MODULE.h"
#include "TIMER_MODULE.h"
#include "TYPEDEF.h"

//button state
uint8_t NewButtonBuf=0, RealButtonBuf=0, ButtonBuf=0;
uint8_t ButtonDebounce;
uint8_t Button2sCnt;
uint16_t Button5sCnt;
//button flags
bool SOMEBUTTON_PRESSED_FLAG;
bool  MODE_PRESS_FLAG;
bool  MODE_RELEASE_FLAG;
bool  FUNC_PRESS_FLAG;
bool  FUNC_RELEASE_FLAG;
bool  MODE_FUNC_PRESS_FLAG;
bool  MODE_FUNC_RELEASE_FLAG;
//button mode control
uint8_t ButtonMode, TimeMode, MarketMode;

bool SOFT_VERSION_MODE=0;///////////////////////////

void CheckButtonStatus(void);
void ProcessButtonAction(void);
void ProcessButtonTime(void);

uint8_t Is_BtnMode_Pressed(void);
uint8_t Is_BtnFunc_Pressed(void);
static void Clock_Mode_ShortPress(void);
static void Clock_Func_ShortPress(void);
static void Button_Mode_Shortpress(void);
//static void Button_Mode_Longpress(void);
static void Button_Func_Longpress(void);
static void Button_Func_Shortpress(void);
static  void ExitSetTimeMode(void);


uint8_t Is_BtnMode_Pressed(void)
{
    return !DL_GPIO_readPins(GPIO_SWITCHES_USER_SWITCH_1_PORT, GPIO_SWITCHES_USER_SWITCH_1_PIN);
}

uint8_t Is_BtnFunc_Pressed(void)
{
    return !DL_GPIO_readPins(GPIO_SWITCHES_USER_SWITCH_2_PORT, GPIO_SWITCHES_USER_SWITCH_2_PIN);
}



void ButtonManager(void){
    CheckButtonStatus();
    ProcessButtonAction();
    ProcessButtonTime();
}


void CheckButtonStatus(void){
    
    if(BUTTON_CYCLE_FLAG){
       if (Is_BtnMode_Pressed())
        {
            //BIT0 is 0 meaning BtnMode is pressed.
            NewButtonBuf &= ~BIT0;
        }
        else
        {
            NewButtonBuf |= BIT0;            
        }

        if (Is_BtnFunc_Pressed())
        {
            //BIT1 is 0 meaning BtnFunc is pressed.
            NewButtonBuf &= ~BIT1;
        }
        else
        {
            NewButtonBuf |= BIT1;            
        }

        if (RealButtonBuf != NewButtonBuf) // if button status has some changed
        {
            ButtonBuf = (RealButtonBuf ^ NewButtonBuf); // get button change
            Button5sCnt = 0;
            Button2sCnt = 0;
            if (ButtonDebounce)
            {
                ButtonDebounce = 0;
                RealButtonBuf = NewButtonBuf;
                if (ButtonBuf == BIT0) // MODE BUTTON status ecxhange
                {
                    if ((NewButtonBuf & BIT0) == 0x00) // MODE BUTTON press
                    {
                        MODE_PRESS_FLAG = 1;          // MODE BUTTON press flag
                        if (FUNC_PRESS_FLAG)          // FUNC BUTTON press flag
                            MODE_FUNC_PRESS_FLAG = 1; // MODE & FUNC BUTTON press flag (undefined, do nothing)
                        SOMEBUTTON_PRESSED_FLAG = 1;
                    }
                    else
                    {
                        if (MODE_PRESS_FLAG)
                            MODE_RELEASE_FLAG = 1; // MODE BUTTON open flag
                        MODE_PRESS_FLAG = 0;       // MODE BUTTON press flag
                        MODE_FUNC_PRESS_FLAG = 0;  // MODE & FUNC BUTTON press flag (undefined, do nothing)
                        SOMEBUTTON_PRESSED_FLAG = 0;
                    }
                }
                else if (ButtonBuf == BIT1) // FUNC BUTTON status ecxhange
                {
                    if ((NewButtonBuf & BIT1) == 0x00) // FUNC BUTTON press
                    {
                        FUNC_PRESS_FLAG = 1;          // FUNC BUTTON press flag
                        if (MODE_PRESS_FLAG)          // MODE BUTTON press flag
                            MODE_FUNC_PRESS_FLAG = 1; // MODE & FUNC BUTTON press flag (undefined, do nothing)
                        SOMEBUTTON_PRESSED_FLAG = 1;
                    }
                    else
                    {
                        if (FUNC_PRESS_FLAG)
                            FUNC_RELEASE_FLAG = 1; // FUNC BUTTON open flag
                        FUNC_PRESS_FLAG = 0;       // FUNC BUTTON press flag
                        MODE_FUNC_PRESS_FLAG = 0;  // MODE & FUNC BUTTON press flag (undefined, do nothing)
                        SOMEBUTTON_PRESSED_FLAG = 0;
                    }
                }
                else if (ButtonBuf == BIT0 + BIT1) // FUNC & MODE BUTTON status ecxhange
                {
                    if ((NewButtonBuf & BIT0 + BIT1) == 0x00) // FUNC & MODE BUTTON press
                    {
                        MODE_FUNC_PRESS_FLAG = 1; // FUNC & MODE BUTTON press flag (undefined, do nothing)
                        SOMEBUTTON_PRESSED_FLAG = 1;
                    }
                    else
                    {
                        MODE_FUNC_PRESS_FLAG = 0;
                        MODE_PRESS_FLAG = 0;
                        FUNC_PRESS_FLAG = 0;
                        SOMEBUTTON_PRESSED_FLAG = 0;
                    }
                }
            }
            else
            {
                ButtonDebounce = 1;
            }
        }
        else
        {
            ButtonDebounce = 0;
        }
    }
}

void ProcessButtonAction(void){
    if (SET_CLOCK_MODE) 
    {
        if (RealSpeedKmhBuf <= 10)
        {
            if (MODE_RELEASE_FLAG > 0U) // MODE BUTTON short press
            {
                MODE_RELEASE_FLAG = 0;
                Clock_Mode_ShortPress();
            }
            else if (FUNC_RELEASE_FLAG > 0U) // FUNC BUTTON short press
            {
                FUNC_RELEASE_FLAG = 0;
                Button5sCnt = 0;
                Clock_Func_ShortPress();
            }
        }
        else
        {
            MODE_PRESS_FLAG = 0;
            FUNC_PRESS_FLAG = 0;
            ExitSetTimeMode();
        }
    }
    //Button MODE
    else if (BUTTON_CYCLE_FLAG) // 20ms
    {
        if (MODE_RELEASE_FLAG) // MODE BUTTON short press
        {
            MODE_RELEASE_FLAG = 0;

            if (SOFT_VERSION_MODE == 0)
            {
                Button_Mode_Shortpress();
            }
        }
        /*else if (FUNC_RELEASE_FLAG && SOFT_VERSION_MODE)
        {
            FUNC_RELEASE_FLAG = 0;

            if (++SoftResetCnt >= 3 && ODOKM.vGLB < 300) {
                // initialize ODO & TRIP variables
                ODOKM.vGLB = 0;
                ODOMPH.vGLB = 0;
                TRIPKM.vGLB = 0;
                TRIPMPH.vGLB = 0;
                TripKmhBuf = 0;
                TripMphBuf = 0;
                DistCompTripKmhCnt = 100;
                DistCompTripMphCnt = 100;

                // initialize SERVICE variables
                SERVICEKM.vGLB = 0;
                SERVICEMPH.vGLB = 0;
                SerKmhBuf = 0;
                SerMphBuf = 0;
                DistCompSerKmhCnt = 100;
                DistCompSerMphCnt = 100;

                WriteFlag = 0xff;
            }
        }*/
        else if (FUNC_RELEASE_FLAG)
        {
            FUNC_RELEASE_FLAG = 0;
            Button_Func_Shortpress();
        }
    }
}

void ProcessButtonTime(void)
{
    if (BUTTON_CYCLE_FLAG) // 20ms
    {
        BUTTON_CYCLE_FLAG = 0;

        if (SOMEBUTTON_PRESSED_FLAG)
        {
            if (++Button2sCnt >= 100) // Check if Some Button press for 2s
            {
                Button2sCnt = 0;
                SOMEBUTTON_PRESSED_FLAG = 0;

                if (MODE_PRESS_FLAG) // MODE BUTTON press for 2s
                {
                    MODE_PRESS_FLAG = 0U;
                    //Button_Mode_Longpress();
                }
                else if (FUNC_PRESS_FLAG) // ADJ BUTTON press for 2s
                {
                    FUNC_PRESS_FLAG = 0;
                    Button_Func_Longpress();
                }
            }
        }
        else
        {
            Button2sCnt = 0;
        }

        if (SET_CLOCK_MODE) // 5s
        {
            // if it's in SET_CLOCK_MODE and do nothing for 5s, exit SET_CLOCK_MODE
            if (++Button5sCnt >= 250)
            {
                Button5sCnt = 0;
                ExitSetTimeMode();
            }
        }
    }
}


void Button_Mode_Shortpress(void) {
    if (++ButtonMode >= EOF_BUTTON_MODE)
    {
        ButtonMode = 0;
    }
    Button5sCnt = 0;
}

void Button_Func_Shortpress(void) {
    //temp test
    rtcMin ++;
}


void Button_Func_Longpress(void) {
    if (SET_CLOCK_MODE)
    {
        SET_CLOCK_MODE = 0U;
        ExitSetTimeMode();
    }
    else
    {
        if ((SET_CLOCK_MODE == 0) && (ButtonMode == MODE_ODO) && (DispSpeedKmhBuf <= 10))
        {
            SET_CLOCK_MODE = 1; // enter Time Mode
            Button5sCnt = 0;
            HourBuf = rtcHour;
            MinBuf = rtcMin;
        }
        else if (ButtonMode == MODE_TRIP)
        {
            // initialize ODO & TRIP variables
            /*TRIPKM.vGLB = 0;
            TRIPMPH.vGLB = 0;
            TripKmhBuf = 0;
            TripMphBuf = 0;
            DistCompTripKmhCnt = 100;
            DistCompTripMphCnt = 100;
            WriteFlag = 0xff;*/
        }
        else if (ButtonMode == MODE_SERVICE)
        {
            // initialize SERVICE variables
            /*SERVICEKM.vGLB = 0;
            SERVICEMPH.vGLB = 0;
            SerKmhBuf = 0;
            SerMphBuf = 0;
            DistCompSerKmhCnt = 100;
            DistCompSerMphCnt = 100;
            SERVICE_LED = 0;
            WriteFlag = 0xff;*/
        }
    }
}

void ExitSetTimeMode(void)
{
    TimeMode = 0;
    rtcHour = HourBuf;
    rtcMin = MinBuf;
    rtcSec = 0;

    DL_RTC_setCalendarHoursBinary(RTC,rtcHour);
    DL_RTC_setCalendarMinutesBinary(RTC,rtcMin);
    DL_RTC_setCalendarSecondsBinary(RTC,rtcSec);
}

void Clock_Mode_ShortPress() {
    Button5sCnt = 0;
    if (++TimeMode >= EOF_TIME_MODE)
    {
        TimeMode = 0;
    }
}

void Clock_Func_ShortPress() {

    static uint8_t SetMinTen = 0U;
    static uint8_t SetMinUnit = 0U;

    if (TimeMode == TIME_HOUR)
    {
        if (++HourBuf >= 24)
            HourBuf = 0;
    }
    else if (TimeMode == TIME_MIN_TEN)
    {
        if (++SetMinTen >= 6)
            SetMinTen = 0;
        MinBuf = (SetMinTen * 10) + (MinBuf % 10);
    }
    else if (TimeMode == TIME_MIN_UNIT)
    {
        if (++SetMinUnit >= 10)
            SetMinUnit = 0;
        MinBuf = (MinBuf / 10) * 10 + SetMinUnit;
    }
}
