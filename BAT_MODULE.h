#ifndef BAT_MODULE_H
#define BAT_MODULE_H

extern uint32_t RealBatBuf;		//(LCD_MODULE)display Battery volt 

void InitialBat(void);			//(SYSTEM_MODOULE)
void BatManager(void);			//(user_main)
void InitialBatRam(void);		//(RAM_MODULE)

#endif