#ifndef BUTTON_MODULE_H_
#define BUTTON_MODULE_H_

void ButtonManager(void);

extern uint8_t ButtonMode, TimeMode, MarketMode;

enum {
    MODE_ODO,
    MODE_TRIP,
    MODE_SERVICE,
    MODE_VOLT,
    EOF_BUTTON_MODE
};

enum {
    TIME_HOUR,
    TIME_MIN_TEN,
    TIME_MIN_UNIT,
    EOF_TIME_MODE
};
#define MILE	0x55
#define KM		0x00
#endif