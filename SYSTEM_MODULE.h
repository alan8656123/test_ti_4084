#ifndef SYSTEM_MODULE_H
#define SYSTEM_MODULE_H

void Initial_First_System_Ram(void);
void InitialSystem_Ram(void);
extern void PowerManager(void);
extern void PowerIgnOn(void);
extern void PowerIgnOff(void);
extern void CheckDashboardIntoTestMode(void);
extern void Test_Delay(void);
extern void SleepMode(void);
void PowerHazardOn(void);
void PowerHazardOff(void);
extern void UserMain(void);

extern bool IGN_ON_FLAG;
extern bool OPENING_FLAG;
extern bool FIRST_START_FLAG ;
extern bool OPENING_FLAG ;
#endif