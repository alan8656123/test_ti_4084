#ifndef LED_MODULE_H_
#define LED_MODULE_H_


void digitalWrite(GPIO_Regs* gpio, uint32_t pins, uint8_t val);
void InitialLed(void);
void shiftOut(GPIO_Regs* dataport,uint32_t dataPin, GPIO_Regs* clockport,uint32_t clockPin, uint8_t val);
void LedShiftController(uint8_t value);

#endif