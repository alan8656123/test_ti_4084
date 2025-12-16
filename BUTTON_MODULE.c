#include "ti_msp_dl_config.h"
#include "BUTTON_MODULE.h"
#include "LED_MODULE.h"
#include "TIMER_MODULE.h"

uint16_t debounce_1=0;
uint16_t debounce2=0;

void ButtonManager(void){
 
    if(buttonFlag){
        buttonFlag = false;
        if (!DL_GPIO_readPins(GPIO_SWITCHES_USER_SWITCH_1_PORT, GPIO_SWITCHES_USER_SWITCH_1_PIN)) {
            if(++debounce_1>=2){
                DL_GPIO_setPins(GPIO_LEDS_PORT, GPIO_LEDS_USER_LED_1_PIN);
            }
        }
        /* Otherwise, turn the LED on */
        else {
            debounce_1 = 0;
            DL_GPIO_clearPins(GPIO_LEDS_PORT, GPIO_LEDS_USER_LED_1_PIN);
        }

        if (!DL_GPIO_readPins(GPIO_SWITCHES_USER_SWITCH_2_PORT, GPIO_SWITCHES_USER_SWITCH_2_PIN)) {
            if(++debounce2>=2){
                LedShiftController(255);
            }
        }
        /* Otherwise, turn the LED on */
        else {
            debounce2 = 0;
            LedShiftController(0);
        }   
    }
}