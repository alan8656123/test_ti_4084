#include "ti_msp_dl_config.h"
#include "string.h"
#include "Uci8533.h"
#include "LCD_MAP.h"
#include "LED_MODULE.h"
#include "TIMER_MODULE.h"
#include "LCD_MODULE.h"
#include "BUTTON_MODULE.h"
#include "SPEED_MODULE.h"
#include "TYPEDEF.h"

enum {
    DISPLAY_TIME,
    DISPLAY_SPEED,
    DISPLAY_DIST,
    DISPLAY_TURNSIGNAL,
    DISPLAY_FUEL,
    DISPLAY_OTHER,
    DISPLAY_END,
};
static uint8_t SwithDisplayFlag = 0;



static union GLB DISPLAY0,DISPLAY1,DISPLAY2,DISPLAY3,DISPLAY4,DISPLAY5,DISPLAY6;
union LONG32 TRIPKM, TRIPMPH;
union LONG32 ODOKM, ODOMPH;
union LONG32 SERVICEKM, SERVICEMPH;
uint32_t RealBatBuf = 130U;

uint8_t display_digit;

uint8_t SPEED=0;
uint8_t speed_digit=0;
uint8_t speed_ten=0;
uint8_t speed_hun=0;
void ProcessSpeedToDisplay(void);
void DisplaySpeed(void);

uint8_t speed_rpm[28];
int speed_rpm_count=0;
uint8_t speed_rpm_val=0;
void DisplayRPM(void);

uint32_t fuel_bar=0;
uint8_t fuel_cal=0;
void DisplayFuel(void);

uint8_t hour_ten=1;
uint8_t hour_digit=2;
uint8_t min_ten=0;
uint8_t min_digit=0;
void DisplayRTC(void);

uint8_t GEAR=0;
uint8_t GEAR_num=0;
void DisplayGear(void);

//todo
void DisplayDigital(void);

void ProcessDistToDisplay();
void ProcessTimeToDisplay();


void Initial_LCD(void){
    //delay to prevent i2c not up to 3.3V
    delay(200);
    LCD_IC_DisplayOn();
    // all light////////////////////////////////////////////////
    delay(50);
    
}

void LCD_open_anime(void){
     for(uint8_t LcdOpenMode = 0U; LcdOpenMode<=22U;LcdOpenMode++)
    {
        if (LcdOpenMode == 0U)
        {
            memset(Lcd_Data,0x00,40);
        }
        else if (LcdOpenMode == 1U)
        {
            LCD_A14 = LCD_A15 = LCD_X4 = LCD_X5 = LCD_X10 = LCD_X11 = 1U;
        }
        else if (LcdOpenMode == 2U)
        {
            LCD_A13 = LCD_A16 = LCD_A36 = LCD_X51 =1U;
        }
        else if (LcdOpenMode == 3U)
        {
            LCD_X48 = LCD_12B = LCD_12C = LCD_COL = LCD_13A = LCD_13D = LCD_13E = LCD_13F = LCD_13G = LCD_X3 = LCD_X9 =1U;
        }
        else if (LcdOpenMode == 4U)
        {
            LCD_A12 = LCD_A17 = 1U;
        }
        else if (LcdOpenMode == 5U)
        {
            LCD_4B = LCD_4C = LCD_X13 = LCD_X2 = LCD_X8 = LCD_X6 = LCD_X12 = LCD_X14_A = 1U;
        }
        else if (LcdOpenMode == 6U)
        {
            LCD_A11 = LCD_A18 = LCD_X52 = LCD_X50 = LCD_11A = 1U;
            LCD_11B = LCD_11C = LCD_12A = LCD_12D = LCD_12E = 1U;
            LCD_12F = LCD_12G = LCD_13B = LCD_13C = LCD_14A = 1U;
            LCD_14D = LCD_14E = LCD_14F = LCD_14G = LCD_9A = LCD_9B = LCD_9C = 1U;
        }
        else if (LcdOpenMode == 7U)
        {
            LCD_A10 = LCD_A19 = LCD_X1 = LCD_X7 = LCD_4A = LCD_4D = LCD_4G = LCD_5E = 1U;
        }
        else if (LcdOpenMode == 8U)
        {
            LCD_X53 = LCD_X49 = LCD_A9 = LCD_A20 = LCD_A37 = 1U;
            LCD_A35 = LCD_11D = LCD_11E = LCD_11G = LCD_14B = LCD_14C = LCD_9G = 1U;
        }
        else if (LcdOpenMode == 9U)
        {
            LCD_X18 = LCD_X14_C = LCD_X14_B = LCD_4E = LCD_4F = LCD_5D = LCD_5F = LCD_5G = 1U;
        }
        else if (LcdOpenMode == 10U)
        {
            LCD_A8 =LCD_A21 = LCD_9F = LCD_10F = 1U;
        }
        else if (LcdOpenMode == 11U)
        {
            LCD_X54 = LCD_X47 = LCD_A7 = LCD_A22 = LCD_X30 = 1U;
            LCD_X31 = LCD_3B = LCD_3C = LCD_3D = LCD_5A = LCD_5C = LCD_DP = LCD_X15 = 1U;
        }
        else if (LcdOpenMode == 12U)
        {
            LCD_8A = LCD_8B = LCD_10A = LCD_10E = 1U;
        }
        else if (LcdOpenMode == 13U)
        {
            LCD_A6 = LCD_A23 = LCD_X29 = LCD_3A = LCD_3E = 1U;
            LCD_3G = LCD_5B = LCD_6D = LCD_6E = LCD_X19 = LCD_X16 = 1U;
        }
        else if (LcdOpenMode == 14U)
        {
            LCD_X55 = LCD_X46 = LCD_A5 = LCD_A24 = LCD_A38 = LCD_A34 = 1U;
        }
        else if (LcdOpenMode == 15U)
        {
            LCD_10B = LCD_10G = 1U;
        }
        else if (LcdOpenMode == 16U)
        {
            LCD_A4 = LCD_A25 = LCD_A29 = LCD_X36 = LCD_2B = 1U;
            LCD_2C = LCD_2D = LCD_2E = LCD_2G = LCD_3F = 1U;
            LCD_6C = LCD_6F = LCD_6G = LCD_X22 = LCD_X20 = LCD_X17 = 1U;
        }
        else if (LcdOpenMode == 17U)
        {
            LCD_A3 = LCD_A26 = LCD_A30 = LCD_1B = LCD_1C = 1U;
            LCD_1D = LCD_1E = LCD_1G = LCD_2A = LCD_2F = 1U;
            LCD_6A = LCD_6B = LCD_X32 = LCD_X23 = LCD_X21 = 1U;
            LCD_9D = LCD_9E = LCD_X25_A = LCD_X56 = LCD_X45 = 1U;
        }
        else if (LcdOpenMode == 18U)
        {
            LCD_A2 = LCD_A27 = LCD_A31 = LCD_8C = LCD_8G = LCD_10C = LCD_10D = LCD_X42 = 1U;
        }
        else if (LcdOpenMode == 19U)
        {
            LCD_A1 = LCD_A28 = LCD_A32 = LCD_X57 = LCD_X44 = 1U;
            LCD_A39 = LCD_A33 = LCD_X38 = LCD_X37 = LCD_X35 = 1U;
            LCD_X33 = LCD_X28 = LCD_X24 = LCD_1A = LCD_1F = 1U;
            LCD_7C = LCD_7D = LCD_7E = LCD_7G = LCD_7H = 1U;
        }
        else if (LcdOpenMode == 20U)
        {
            LCD_8E = LCD_8D = LCD_X41 = LCD_X39 = LCD_X34 = 1U;
            LCD_X27 = LCD_X25_B = LCD_7A = LCD_7B = LCD_7F = LCD_7H = 1U;
        }
        else if (LcdOpenMode == 21U)
        {
            LCD_X26 = LCD_X43 = 1U;
        }
        else if (LcdOpenMode == 22U) // lcd all on - 1000ms
        {
            LCD_X40 = 1U;
        }
        delay(50);
        LCD_IC_DisplayWrite();
    }
}

void LcdManager(void){
    if(lcdFlag)     //5ms period == 200HZ
    {
            lcdFlag = false;
            if (SwithDisplayFlag == DISPLAY_TIME)
           {
                ProcessTimeToDisplay();
                DisplayRTC();
           }
           else if (SwithDisplayFlag == DISPLAY_SPEED)
           {
                ProcessSpeedToDisplay();
                DisplaySpeed();
           }
           else if (SwithDisplayFlag == DISPLAY_DIST)
           {
                ProcessDistToDisplay();
                DisplayDigital();
           }
           else if (SwithDisplayFlag == DISPLAY_TURNSIGNAL)
           {   
                DisplaySpeed();
                DisplayRPM();
                DisplayGear();
           }
           else if (SwithDisplayFlag == DISPLAY_FUEL)
           {
                DisplayFuel();
           }
           else if (SwithDisplayFlag == DISPLAY_OTHER)
           {
           }
        if (++SwithDisplayFlag >= DISPLAY_END)
               SwithDisplayFlag = 0x00;
        LCD_IC_DisplayWrite();
    }
}

void ProcessSpeedToDisplay(void)
{
    uint16_t TempSpeedBuf;

    if (MarketMode == MILE)
    {
        TempSpeedBuf = DispSpeedMphBuf;
        DISPLAY3.vGLB = BIT1;
    }
    else
    {
        TempSpeedBuf = DispSpeedKmhBuf;
        DISPLAY3.vGLB = BIT0;
    }

    if (TempSpeedBuf >= 199)
    {
        TempSpeedBuf = 199;
    }

    DISPLAY2.vGLB = TempSpeedBuf / 100;
    DISPLAY1.vGLB = (TempSpeedBuf % 100) / 10;
    DISPLAY0.vGLB = TempSpeedBuf % 10;

    if (DISPLAY2.vGLB == 0x00)
    {
        DISPLAY2.vGLB = 16;
        if (DISPLAY1.vGLB == 0x00)
        {
            DISPLAY1.vGLB = 16;
        }
    }

    if (TempSpeedBuf >= 199)
    {
        if (Flash500msFlag == 0)
        {
            DISPLAY2.vGLB = 16;
            DISPLAY1.vGLB = 16;
            DISPLAY0.vGLB = 16;
        }
    }

    DISPLAY2.vGLB = NumberAndWordTable[DISPLAY2.vGLB];
    DISPLAY1.vGLB = NumberAndWordTable[DISPLAY1.vGLB];
    DISPLAY0.vGLB = NumberAndWordTable[DISPLAY0.vGLB];
}

void DisplaySpeed(void){

    //SPEED_KMH = DISPLAY3.bits.bit0; // KM
    //SPEED_KMH = DISPLAY3.bits.bit0; // KM

    LCD_8A = DISPLAY2.bits.bit6; // DIG.6
    LCD_8B = DISPLAY2.bits.bit5;
    LCD_8C = DISPLAY2.bits.bit4;
    LCD_8D = DISPLAY2.bits.bit3;
    LCD_8E = DISPLAY2.bits.bit2;
    //LCD_8F = DISPLAY2.bits.bit1;
    LCD_8G = DISPLAY2.bits.bit0;

    LCD_9A = DISPLAY1.bits.bit6; // DIG.6
    LCD_9B = DISPLAY1.bits.bit5;
    LCD_9C = DISPLAY1.bits.bit4;
    LCD_9D = DISPLAY1.bits.bit3;
    LCD_9E = DISPLAY1.bits.bit2;
    LCD_9F = DISPLAY1.bits.bit1;
    LCD_9G = DISPLAY1.bits.bit0;

    LCD_10A = DISPLAY0.bits.bit6; // DIG.7
    LCD_10B = DISPLAY0.bits.bit5;
    LCD_10C = DISPLAY0.bits.bit4;
    LCD_10D = DISPLAY0.bits.bit3;
    LCD_10E = DISPLAY0.bits.bit2;
    LCD_10F = DISPLAY0.bits.bit1;
    LCD_10G = DISPLAY0.bits.bit0;
    /*speed_hun = NumberToWordTable[(speed_hun==0)?16:1];
    speed_ten = NumberToWordTable[(speed_ten==0&&speed_hun==0)?16:speed_ten];
    speed_digit = NumberToWordTable[speed_digit];

    LCD_8A = (((DISPLAY_DIGITAL_TYPE *)&speed_hun)->A);
    LCD_8B = (((DISPLAY_DIGITAL_TYPE *)&speed_hun)->B);
    LCD_8C = (((DISPLAY_DIGITAL_TYPE *)&speed_hun)->C);
    LCD_8D = (((DISPLAY_DIGITAL_TYPE *)&speed_hun)->D);
    LCD_8E = (((DISPLAY_DIGITAL_TYPE *)&speed_hun)->E);
    //LCD_8F = (((DISPLAY_DIGITAL_TYPE *)&speed_hun)->F);
    LCD_8G = (((DISPLAY_DIGITAL_TYPE *)&speed_hun)->G);


    LCD_9A = (((DISPLAY_DIGITAL_TYPE *)&speed_ten)->A);
    LCD_9B = (((DISPLAY_DIGITAL_TYPE *)&speed_ten)->B);
    LCD_9C = (((DISPLAY_DIGITAL_TYPE *)&speed_ten)->C);
    LCD_9D = (((DISPLAY_DIGITAL_TYPE *)&speed_ten)->D);
    LCD_9E = (((DISPLAY_DIGITAL_TYPE *)&speed_ten)->E);
    LCD_9F = (((DISPLAY_DIGITAL_TYPE *)&speed_ten)->F);
    LCD_9G = (((DISPLAY_DIGITAL_TYPE *)&speed_ten)->G);


    LCD_10A = (((DISPLAY_DIGITAL_TYPE *)&speed_digit)->A);
    LCD_10B = (((DISPLAY_DIGITAL_TYPE *)&speed_digit)->B);
    LCD_10C = (((DISPLAY_DIGITAL_TYPE *)&speed_digit)->C);
    LCD_10D = (((DISPLAY_DIGITAL_TYPE *)&speed_digit)->D);
    LCD_10E = (((DISPLAY_DIGITAL_TYPE *)&speed_digit)->E);
    LCD_10F = (((DISPLAY_DIGITAL_TYPE *)&speed_digit)->F);
    LCD_10G = (((DISPLAY_DIGITAL_TYPE *)&speed_digit)->G);*/
}
void DisplayFuel(void){
    LCD_X7 = fuel_cal%7<=5;
    LCD_X8 = fuel_cal%7<=4;
    LCD_X9 = fuel_cal%7<=3;
    LCD_X10 = fuel_cal%7<=2;
    LCD_X11 = fuel_cal%7<=1;
    LCD_X12 = fuel_cal%7<=0;
}

void ProcessTimeToDisplay(void)
{
    if (SET_CLOCK_MODE) // SET CLOCK MODE
    {
        DISPLAY5.vGLB = 1;
        DISPLAY4.vGLB = HourBuf / 10;
        DISPLAY3.vGLB = HourBuf % 10;
        DISPLAY2.vGLB = MinBuf / 10;
        DISPLAY1.vGLB = MinBuf % 10;
        DISPLAY0.vGLB = 0;
        if (TimeMode == TIME_HOUR)
        {
            if (Flash500msFlag == 0x00)
            {
                DISPLAY4.vGLB = 16;
                DISPLAY3.vGLB = 16;
            }
        }
        else if (TimeMode == TIME_MIN_TEN)
        {
            if (Flash500msFlag == 0x00)
            {
                DISPLAY2.vGLB = 16;
            }
        }
        else if (TimeMode == TIME_MIN_UNIT)
        {
            if (Flash500msFlag == 0x00)
            {
                DISPLAY1.vGLB = 16;
            }
        }
        else
        {
        }
    }
    else
    {
        if (Flash500msFlag)
        {
            DISPLAY5.vGLB = 1;
        }
        else
        {
            DISPLAY5.vGLB = 0;
        }
        DISPLAY4.vGLB = rtcHour / 10;
        DISPLAY3.vGLB = rtcHour % 10;
        DISPLAY2.vGLB = rtcMin / 10;
        DISPLAY1.vGLB = rtcMin % 10;
        DISPLAY0.vGLB = 0;
    }

    if (DISPLAY4.vGLB == 0x00)
    {
        DISPLAY4.vGLB = 16;
    }
    else
    {
        /* code */
    }

    DISPLAY4.vGLB = NumberAndWordTable[DISPLAY4.vGLB];
    DISPLAY3.vGLB = NumberAndWordTable[DISPLAY3.vGLB];
    DISPLAY2.vGLB = NumberAndWordTable[DISPLAY2.vGLB];
    DISPLAY1.vGLB = NumberAndWordTable[DISPLAY1.vGLB];
}


void DisplayRTC(void){

    LCD_COL = DISPLAY5.bits.bit0;
    //min digit
    LCD_14A = DISPLAY1.bits.bit6;
    LCD_14B = DISPLAY1.bits.bit5;
    LCD_14C = DISPLAY1.bits.bit4;
    LCD_14D = DISPLAY1.bits.bit3;
    LCD_14E = DISPLAY1.bits.bit2;
    LCD_14F = DISPLAY1.bits.bit1;
    LCD_14G = DISPLAY1.bits.bit0;

    //min ten
    LCD_13A = DISPLAY2.bits.bit6;
    LCD_13B = DISPLAY2.bits.bit5;
    LCD_13C = DISPLAY2.bits.bit4;
    LCD_13D = DISPLAY2.bits.bit3;
    LCD_13E = DISPLAY2.bits.bit2;
    LCD_13F = DISPLAY2.bits.bit1;
    LCD_13G = DISPLAY2.bits.bit0;

    //hour digit
    LCD_12A = DISPLAY3.bits.bit6;
    LCD_12B = DISPLAY3.bits.bit5;
    LCD_12C = DISPLAY3.bits.bit4;
    LCD_12D = DISPLAY3.bits.bit3;
    LCD_12E = DISPLAY3.bits.bit2;
    LCD_12F = DISPLAY3.bits.bit1;
    LCD_12G = DISPLAY3.bits.bit0;

    //hour ten
    LCD_11A = DISPLAY4.bits.bit6;
    LCD_11B = DISPLAY4.bits.bit5;
    LCD_11C = DISPLAY4.bits.bit4;
    LCD_11D = DISPLAY4.bits.bit3;
    LCD_11E = DISPLAY4.bits.bit2;
    //LCD_11F = DISPLAY4.bits.bit1;
    LCD_11G = DISPLAY4.bits.bit0;
}
void DisplayGear(void){
    GEAR_num = NumberToWordTable[GEAR];
    LCD_7A = (((DISPLAY_DIGITAL_TYPE *)& GEAR_num)->A);
    LCD_7B = (((DISPLAY_DIGITAL_TYPE *)& GEAR_num)->B);
    LCD_7C = (((DISPLAY_DIGITAL_TYPE *)& GEAR_num)->C);
    LCD_7D = (((DISPLAY_DIGITAL_TYPE *)& GEAR_num)->D);
    LCD_7E = (((DISPLAY_DIGITAL_TYPE *)& GEAR_num)->E);
    LCD_7F = (((DISPLAY_DIGITAL_TYPE *)& GEAR_num)->F);
    LCD_7G = (((DISPLAY_DIGITAL_TYPE *)& GEAR_num)->G);
}

void DisplayRPM(){
    LCD_A1 = speed_rpm[0];
    LCD_A2 = speed_rpm[1];
    LCD_A3 = speed_rpm[2];
    LCD_A4 = speed_rpm[3];
    LCD_A5 = speed_rpm[4];
    LCD_A6 = speed_rpm[5];
    LCD_A7 = speed_rpm[6];
    LCD_A8 = speed_rpm[7];
    LCD_A9 = speed_rpm[8];
    LCD_A10 = speed_rpm[9];
    LCD_A11 = speed_rpm[10];
    LCD_A12 = speed_rpm[11];
    LCD_A13 = speed_rpm[12];
    LCD_A14 = speed_rpm[13];
    LCD_A15 = speed_rpm[14];
    LCD_A16 = speed_rpm[15];
    LCD_A17 = speed_rpm[16];
    LCD_A18 = speed_rpm[17];
    LCD_A19 = speed_rpm[18];
    LCD_A20 = speed_rpm[19];
    LCD_A21 = speed_rpm[20];
    LCD_A22 = speed_rpm[21];
    LCD_A23 = speed_rpm[22];
    LCD_A24 = speed_rpm[23];
    LCD_A25 = speed_rpm[24];
    LCD_A26 = speed_rpm[25];
    LCD_A27 = speed_rpm[26];
    LCD_A28 = speed_rpm[27];
}

void ProcessDistToDisplay(void)
{
    union LONG32 DIST_BUF;

    // 0:ODO  1:TRIP  2:POINT  3:KM  4:X  5:X  6:VOLT  7: Oil service
    if (ButtonMode == MODE_ODO) // ODO MODE
    {
        if (MarketMode == MILE)
        {
            DIST_BUF.vGLB = ODOMPH.vGLB;
            DISPLAY6.vGLB = BIT0 + BIT4; // 0:ODO  1:TRIP  2:POINT  3:KM  4:X  5:X  6:VOLT  7: Oil service
        }
        else
        {
            DIST_BUF.vGLB = ODOKM.vGLB;
            DISPLAY6.vGLB = BIT0 + BIT3;
        }

        DISPLAY5.vGLB = (uint16_t)(DIST_BUF.vGLB / 1000000);
        DISPLAY4.vGLB = (uint16_t)((DIST_BUF.vGLB % 1000000) / 100000);
        DISPLAY3.vGLB = (uint16_t)((DIST_BUF.vGLB % 100000) / 10000);
        DISPLAY2.vGLB = (uint16_t)((DIST_BUF.vGLB % 10000) / 1000);
        DISPLAY1.vGLB = (uint16_t)((DIST_BUF.vGLB % 1000) / 100);
        DISPLAY0.vGLB = (uint16_t)((DIST_BUF.vGLB % 100) / 10);
    }
    else if (ButtonMode == MODE_TRIP) // TRIP MODE
    {
        if (MarketMode == MILE)
        {
            DIST_BUF.vGLB = TRIPMPH.vGLB;
            DISPLAY6.vGLB = BIT1 + BIT2 + BIT4; // 0:ODO  1:TRIP  2:POINT  3:KM  4:X  5:X  6:VOLT  7: Oil service
        }
        else
        {
            DIST_BUF.vGLB = TRIPKM.vGLB;
            DISPLAY6.vGLB = BIT1 + BIT2 + BIT3;
        }

        DISPLAY5.vGLB = 0;
        DISPLAY4.vGLB = 0;
        DISPLAY3.vGLB = (uint16_t)((DIST_BUF.vGLB % 10000) / 1000);
        DISPLAY2.vGLB = (uint16_t)((DIST_BUF.vGLB % 1000) / 100);
        DISPLAY1.vGLB = (uint16_t)((DIST_BUF.vGLB % 100) / 10);
        DISPLAY0.vGLB = (uint16_t)(DIST_BUF.vGLB % 10);
    }
    else if (ButtonMode == MODE_SERVICE) // SERVICE MODE
    {
        if (MarketMode == MILE)
        {
            DIST_BUF.vGLB = SERVICEMPH.vGLB;
            DISPLAY6.vGLB = BIT2 + BIT4 + BIT7; // 0:ODO  1:TRIP  2:POINT  3:KM  4:X  5:X  6:VOLT  7: Oil service
        }
        else
        {
            DIST_BUF.vGLB = SERVICEKM.vGLB;
            DISPLAY6.vGLB = BIT2 + BIT3 + BIT7;
        }

        DISPLAY5.vGLB = 0;
        DISPLAY4.vGLB = (uint16_t)((DIST_BUF.vGLB % 100000) / 10000);
        DISPLAY3.vGLB = (uint16_t)((DIST_BUF.vGLB % 10000) / 1000);
        DISPLAY2.vGLB = (uint16_t)((DIST_BUF.vGLB % 1000) / 100);
        DISPLAY1.vGLB = (uint16_t)((DIST_BUF.vGLB % 100) / 10);
        DISPLAY0.vGLB = (uint16_t)(DIST_BUF.vGLB % 10);
    }
    else if (ButtonMode == MODE_VOLT) // VOLT MODE
    {
        DISPLAY6.vGLB = BIT2 + BIT6; // 0:ODO  1:TRIP  2:POINT  3:KM  4:X  5:X  6:VOLT  7: Oil service

        DISPLAY5.vGLB = 0;
        DISPLAY4.vGLB = 0;
        DISPLAY3.vGLB = 0;
        DISPLAY2.vGLB = (uint16_t)((RealBatBuf % 10000) / 1000);
        DISPLAY1.vGLB = (uint16_t)((RealBatBuf % 1000) / 100);
        DISPLAY0.vGLB = (uint16_t)((RealBatBuf % 100) / 10);
    }

    if (DISPLAY5.vGLB == 0x00)
    {
        DISPLAY5.vGLB = 16;
        if (DISPLAY4.vGLB == 0x00)
        {
            DISPLAY4.vGLB = 16;
            if (DISPLAY3.vGLB == 0x00)
            {
                DISPLAY3.vGLB = 16;
                if (DISPLAY2.vGLB == 0x00)
                {
                    DISPLAY2.vGLB = 16;
                    if (ButtonMode == MODE_ODO)
                    {
                        if (DISPLAY1.vGLB == 0x00)
                            DISPLAY1.vGLB = 16;//OFF
                    }
                }
            }
        }
    }

    DISPLAY5.vGLB = NumberAndWordTable[DISPLAY5.vGLB];
    DISPLAY4.vGLB = NumberAndWordTable[DISPLAY4.vGLB];
    DISPLAY3.vGLB = NumberAndWordTable[DISPLAY3.vGLB];
    DISPLAY2.vGLB = NumberAndWordTable[DISPLAY2.vGLB];
    DISPLAY1.vGLB = NumberAndWordTable[DISPLAY1.vGLB];
    DISPLAY0.vGLB = NumberAndWordTable[DISPLAY0.vGLB];
}

void DisplayDigital(void){
    //tempary off
    LCD_X32=0;
    LCD_X34=0;
    LCD_X33=0;
    LCD_X31=0;
    LCD_X30=0;
    LCD_X29=0;
    LCD_X28=0;
    LCD_X27=0;
    LCD_X29=0;

    DIST_ODO = DISPLAY6.bits.bit0;
    DIST_TRIP = DISPLAY6.bits.bit1;
    DIST_DP = DISPLAY6.bits.bit2;
    DIST_KM = DISPLAY6.bits.bit3;
    DIST_VOLT = DISPLAY6.bits.bit6;
    DIST_OIL = DISPLAY6.bits.bit7;

    LCD_1A = DISPLAY5.bits.bit6;
    LCD_1B = DISPLAY5.bits.bit5;
    LCD_1C = DISPLAY5.bits.bit4;
    LCD_1D = DISPLAY5.bits.bit3;
    LCD_1E = DISPLAY5.bits.bit2;
    LCD_1F = DISPLAY5.bits.bit1;
    LCD_1G = DISPLAY5.bits.bit0;

    LCD_2A = DISPLAY4.bits.bit6;
    LCD_2B = DISPLAY4.bits.bit5;
    LCD_2C = DISPLAY4.bits.bit4;
    LCD_2D = DISPLAY4.bits.bit3;
    LCD_2E = DISPLAY4.bits.bit2;
    LCD_2F = DISPLAY4.bits.bit1;
    LCD_2G = DISPLAY4.bits.bit0;

    LCD_3A = DISPLAY3.bits.bit6;
    LCD_3B = DISPLAY3.bits.bit5;
    LCD_3C = DISPLAY3.bits.bit4;
    LCD_3D = DISPLAY3.bits.bit3;
    LCD_3E = DISPLAY3.bits.bit2;
    LCD_3F = DISPLAY3.bits.bit1;
    LCD_3G = DISPLAY3.bits.bit0;

    LCD_4A = DISPLAY2.bits.bit6;
    LCD_4B = DISPLAY2.bits.bit5;
    LCD_4C = DISPLAY2.bits.bit4;
    LCD_4D = DISPLAY2.bits.bit3;
    LCD_4E = DISPLAY2.bits.bit2;
    LCD_4F = DISPLAY2.bits.bit1;
    LCD_4G = DISPLAY2.bits.bit0;

    LCD_5A = DISPLAY1.bits.bit6;
    LCD_5B = DISPLAY1.bits.bit5;
    LCD_5C = DISPLAY1.bits.bit4;
    LCD_5D = DISPLAY1.bits.bit3;
    LCD_5E = DISPLAY1.bits.bit2;
    LCD_5F = DISPLAY1.bits.bit1;
    LCD_5G = DISPLAY1.bits.bit0;

    LCD_6A = DISPLAY0.bits.bit6;
    LCD_6B = DISPLAY0.bits.bit5;
    LCD_6C = DISPLAY0.bits.bit4;
    LCD_6D = DISPLAY0.bits.bit3;
    LCD_6E = DISPLAY0.bits.bit2;
    LCD_6F = DISPLAY0.bits.bit1;
    LCD_6G = DISPLAY0.bits.bit0;
}