
#include "ti_msp_dl_config.h"
#include "string.h"
#include "Uci8533.h"
#include "LCD_MAP.h"
#include "LED_MODULE.h"
#include "TIMER_MODULE.h"
#include "LCD_MODULE.h"

typedef struct
{
    unsigned G : 1;
    unsigned F : 1;
    unsigned E : 1;
    unsigned D : 1;
    unsigned C : 1;
    unsigned B : 1;
    unsigned A : 1;
    unsigned Unused : 1;
} DISPLAY_DIGITAL_TYPE;

const uint8_t NumberToWordTable[19] =
{ //   ABCDEFG
    0b01111110 ,//0
    0b00110000 ,//1
    0b01101101 ,//2
    0b01111001 ,//3
    0b00110011 ,//4
    0b01011011 ,//5
    0b01011111 ,//6
    0b01110000 ,//7
    0b01111111 ,//8
    0b01111011 ,//9
    0b01110111 ,//A
    0b00011111 ,//b
    0b00001101 ,//c
    0b00111101 ,//d
    0b01001111 ,//E
    0b01000111 ,//F
    0b00000000 ,//Blank
    0b00000001 ,//-
    0b00110110 ,//N
};

uint8_t display_digit;

uint8_t SPEED=0;
uint8_t speed_digit;
uint8_t speed_ten;
uint8_t speed_hun;
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


void Initial_LCD(void){
    // open////////////////////////////////////////////////
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




void LCD_demo(void){
    LCD_open_anime();  
    delay(1000);
    
    //FIX
    //KM not mph
    LCD_X41=1;
    LCD_X42=0;
    LCD_X24=0;
    LCD_X23=0;
    LCD_X22=1;
    LCD_X21=1;
    LCD_X35=1;
    //ODO only
    LCD_X32=0;
    LCD_X34=0;
    LCD_X33=0;
    LCD_X31=0;
    LCD_X30=0;
    LCD_X29=0;
    LCD_X28=0;
    LCD_X27=0;
    LCD_X29=0;
    DisplayDigital();


    uint32_t count = 0;
    const uint8_t anime_loop = 200;
    while (1){
        //DEMO1. SPEED GEAR RPM animation
        if(count%anime_loop==0){
            speed_rpm_count=0;
            SPEED=0;
            GEAR = 0;
        }

        else if(count%anime_loop<5)
        {
            speed_rpm_count+=2;
             SPEED+=6;
             GEAR = 1;
        }
        else if(count%anime_loop<10)
        {
            speed_rpm_count++;
             SPEED+=3;
        }
        else if(count%anime_loop<20)
        {
            SPEED++;
            GEAR = 1;
        }
        else if(count%anime_loop<40)
        {
            if(count%2==0)
           SPEED++;
            if(count%15==0)
                speed_rpm_count --;
        }
        else if(count%anime_loop<45)
        {
            speed_rpm_count --;
            GEAR = 2;
        }
        else if(count%anime_loop<50)
        {
            if(count%50==0)
              SPEED--;

        }
        else if(count%anime_loop<80)
        {
            if(count%3==0)
            {
                speed_rpm_count++;
                SPEED+=3;
            }
            else{
                SPEED++;
            }
        }
        else if(count%anime_loop<85)
        {
            speed_rpm_count --;
            GEAR = 3;
        }
        else if(count%anime_loop<110)
        {
            SPEED ++;
            if(count%3==0)
            speed_rpm_count ++;

        }
        else if(count%anime_loop<115)
       {
           speed_rpm_count --;
       }
       else if(count%anime_loop<130)
       {
           SPEED ++;
           if(count%3==0)
                       speed_rpm_count ++;
       }
       else if(count%anime_loop<135)
        {
            speed_rpm_count --;
            GEAR = 4;
        }
        else if(count%anime_loop<150)
        {
            SPEED ++;
            if(count%3==0)
                        speed_rpm_count +=2;
        }
        else if(count%anime_loop<155)
        {
           speed_rpm_count --;
           GEAR = 5;
        }
       else if(count%anime_loop<170)
        {
           SPEED ++;
           if(count%3==0)
                  speed_rpm_count +=2;
        }
       else if(count%anime_loop<190)
        {
         SPEED -=7;
         speed_rpm_count -=2;
         GEAR = 0;
        }
       else{
           speed_rpm_count=-1;
                       SPEED=0;
                       GEAR = 18;
        }

        LCD_7H = 0;
        if(GEAR ==18)
        {
            LCD_7H = 1;
        }
        DisplayGear();
      
        speed_hun = SPEED/100 %10;
        speed_ten = SPEED/10 %10;
        speed_digit = SPEED %10;
        DisplaySpeed();

        if(speed_rpm_count>21 && count%2==0)
        {
            for(int i =0;i<28;i++)
            {
                speed_rpm[i]=0 ;
            }
        }else
        {
            for(int i =0;i<28;i++)
            {
               speed_rpm[i]= speed_rpm_count>=i?1:0;
            }
        }
        DisplayRPM();

        if(count%20==0){//250sec

            uint8_t hourten_temp=(count/20)%3;
            uint8_t hour_digit_temp=(count/20)%10;
            if (hourten_temp ==0)hourten_temp=16;
            if(hourten_temp ==2)hour_digit_temp%=4;
            hour_ten = NumberToWordTable[hourten_temp];
            hour_digit = NumberToWordTable[hour_digit_temp];
            min_ten = NumberToWordTable[(count/20)%6];
            min_digit = NumberToWordTable[(count/20)%6];
            DisplayRTC();
        }

        if(count%30==0){//5
                fuel_bar++;
                fuel_cal = fuel_bar %13;
                if(fuel_cal>=7)fuel_cal=12-fuel_cal;

                DisplayFuel();
                digitalWrite(GPIO_latchPin_PORT,GPIO_latchPin_PIN_latchPin_PIN, 0);
                shiftOut(GPIO_dataPin_PORT,GPIO_dataPin_PIN_dataPin_PIN, GPIO_clockPin_PORT,GPIO_clockPin_PIN_clockPin_PIN,  (count%60 ==0)?255:0  );
                digitalWrite(GPIO_latchPin_PORT,GPIO_latchPin_PIN_latchPin_PIN, 1);
        }

        if(count%30==0){
            LCD_X39 = !LCD_X39;
            LCD_X17 = !LCD_X39;
            LCD_X15 = LCD_X39;
        }
        if(count%50==0){
            LCD_X38 = !LCD_X38;
            LCD_X37 = !LCD_X38;
            LCD_X16 = LCD_X38;
        }
        if(count%40==0){
            LCD_X36 = !LCD_X36;
        }
        
        LCD_IC_DisplayWrite();
        delay(50);
        count++;
    }
}

void DisplaySpeed(void){
    speed_hun = NumberToWordTable[(speed_hun==0)?16:1];
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
    LCD_10G = (((DISPLAY_DIGITAL_TYPE *)&speed_digit)->G);
}
void DisplayFuel(void){
    LCD_X7 = fuel_cal%7<=5;
    LCD_X8 = fuel_cal%7<=4;
    LCD_X9 = fuel_cal%7<=3;
    LCD_X10 = fuel_cal%7<=2;
    LCD_X11 = fuel_cal%7<=1;
    LCD_X12 = fuel_cal%7<=0;
}

void DisplayRTC(void){
    LCD_11A = (((DISPLAY_DIGITAL_TYPE *)&hour_ten)->A);
    LCD_11B = (((DISPLAY_DIGITAL_TYPE *)&hour_ten)->B);
    LCD_11C = (((DISPLAY_DIGITAL_TYPE *)&hour_ten)->C);
    LCD_11D = (((DISPLAY_DIGITAL_TYPE *)&hour_ten)->D);
    LCD_11E = (((DISPLAY_DIGITAL_TYPE *)&hour_ten)->E);
    //LCD_8F = (((DISPLAY_DIGITAL_TYPE *)&hour_ten)->F);
    LCD_11G = (((DISPLAY_DIGITAL_TYPE *)&hour_ten)->G);

    LCD_12A = (((DISPLAY_DIGITAL_TYPE *)&hour_digit)->A);
    LCD_12B = (((DISPLAY_DIGITAL_TYPE *)&hour_digit)->B);
    LCD_12C = (((DISPLAY_DIGITAL_TYPE *)&hour_digit)->C);
    LCD_12D = (((DISPLAY_DIGITAL_TYPE *)&hour_digit)->D);
    LCD_12E = (((DISPLAY_DIGITAL_TYPE *)&hour_digit)->E);
    LCD_12F = (((DISPLAY_DIGITAL_TYPE *)&hour_digit)->F);
    LCD_12G = (((DISPLAY_DIGITAL_TYPE *)&hour_digit)->G);

    LCD_13A = (((DISPLAY_DIGITAL_TYPE *)&min_ten)->A);
    LCD_13B = (((DISPLAY_DIGITAL_TYPE *)&min_ten)->B);
    LCD_13C = (((DISPLAY_DIGITAL_TYPE *)&min_ten)->C);
    LCD_13D = (((DISPLAY_DIGITAL_TYPE *)&min_ten)->D);
    LCD_13E = (((DISPLAY_DIGITAL_TYPE *)&min_ten)->E);
    LCD_13F = (((DISPLAY_DIGITAL_TYPE *)&min_ten)->F);
    LCD_13G = (((DISPLAY_DIGITAL_TYPE *)&min_ten)->G);

    LCD_14A = (((DISPLAY_DIGITAL_TYPE *)&min_digit)->A);
    LCD_14B = (((DISPLAY_DIGITAL_TYPE *)&min_digit)->B);
    LCD_14C = (((DISPLAY_DIGITAL_TYPE *)&min_digit)->C);
    LCD_14D = (((DISPLAY_DIGITAL_TYPE *)&min_digit)->D);
    LCD_14E = (((DISPLAY_DIGITAL_TYPE *)&min_digit)->E);
    LCD_14F = (((DISPLAY_DIGITAL_TYPE *)&min_digit)->F);
    LCD_14G = (((DISPLAY_DIGITAL_TYPE *)&min_digit)->G);
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

//todo!!!!!!!!!!!!!!
void DisplayDigital(void){
    display_digit = NumberToWordTable[0];
    LCD_1A = LCD_2A = LCD_3A = LCD_4A = LCD_5A = LCD_6A = (((DISPLAY_DIGITAL_TYPE *)&display_digit)->A);
    LCD_1B = LCD_2B = LCD_3B = LCD_4B = LCD_5B = LCD_6B  = (((DISPLAY_DIGITAL_TYPE *)&display_digit)->B);
    LCD_1C = LCD_2C = LCD_3C = LCD_4C = LCD_5C = LCD_6C  = (((DISPLAY_DIGITAL_TYPE *)&display_digit)->C);
    LCD_1D = LCD_2D = LCD_3D = LCD_4D = LCD_5D = LCD_6D  = (((DISPLAY_DIGITAL_TYPE *)&display_digit)->D);
    LCD_1E = LCD_2E = LCD_3E = LCD_4E = LCD_5E = LCD_6E  = (((DISPLAY_DIGITAL_TYPE *)&display_digit)->E);
    LCD_1F = LCD_2F = LCD_3F = LCD_4F = LCD_5F = LCD_6F  = (((DISPLAY_DIGITAL_TYPE *)&display_digit)->F);
    LCD_1G = LCD_2G = LCD_3G = LCD_4G = LCD_5G = LCD_6G  = (((DISPLAY_DIGITAL_TYPE *)&display_digit)->G);
    LCD_DP=1;

    display_digit = NumberToWordTable[16];
    LCD_DP=0;
    LCD_1A = LCD_2A = LCD_3A = LCD_4A = LCD_5A = (((DISPLAY_DIGITAL_TYPE *)&display_digit)->A);
    LCD_1B = LCD_2B = LCD_3B = LCD_4B = LCD_5B = (((DISPLAY_DIGITAL_TYPE *)&display_digit)->B);
    LCD_1C = LCD_2C = LCD_3C = LCD_4C = LCD_5C = (((DISPLAY_DIGITAL_TYPE *)&display_digit)->C);
    LCD_1D = LCD_2D = LCD_3D = LCD_4D = LCD_5D = (((DISPLAY_DIGITAL_TYPE *)&display_digit)->D);
    LCD_1E = LCD_2E = LCD_3E = LCD_4E = LCD_5E = (((DISPLAY_DIGITAL_TYPE *)&display_digit)->E);
    LCD_1F = LCD_2F = LCD_3F = LCD_4F = LCD_5F = (((DISPLAY_DIGITAL_TYPE *)&display_digit)->F);
    LCD_1G = LCD_2G = LCD_3G = LCD_4G = LCD_5G = (((DISPLAY_DIGITAL_TYPE *)&display_digit)->G);
}