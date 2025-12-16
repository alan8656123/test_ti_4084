#include "ti_msp_dl_config.h"
#include "LED_MODULE.h"


void digitalWrite(GPIO_Regs* gpio, uint32_t pins, uint8_t val)
{
    if (val){
        DL_GPIO_setPins(gpio, pins);
    }else{
        DL_GPIO_clearPins(gpio, pins);
    }
}

void shiftOut(GPIO_Regs* dataport,uint32_t dataPin, GPIO_Regs* clockport,uint32_t clockPin, uint8_t val)
{
    uint8_t i;

    for (i = 0; i < 8; i++)  {
        digitalWrite(dataport,dataPin, (val & (1 << i)) );
        digitalWrite(clockport,clockPin, 1);
        digitalWrite(clockport,clockPin, 0);
    }
}

void InitialLed(void){
    //enable Shift controller
    DL_GPIO_setPins(GPIO_CLR_PORT, GPIO_CLR_PIN_CLR_PIN);
}


void LedShiftController(uint8_t value){
    digitalWrite(GPIO_latchPin_PORT,GPIO_latchPin_PIN_latchPin_PIN, 0);
    shiftOut(GPIO_dataPin_PORT,GPIO_dataPin_PIN_dataPin_PIN, GPIO_clockPin_PORT,GPIO_clockPin_PIN_clockPin_PIN,value);
    digitalWrite(GPIO_latchPin_PORT,GPIO_latchPin_PIN_latchPin_PIN, 1);
}