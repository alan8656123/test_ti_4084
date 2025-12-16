
#ifndef USER_TYPEDEF
#define USER_TYPEDEF

struct char_bit_def {
    uint8_t bit0 : 1;
    uint8_t bit1 : 1;
    uint8_t bit2 : 1;
    uint8_t bit3 : 1;
    uint8_t bit4 : 1;
    uint8_t bit5 : 1;
    uint8_t bit6 : 1;
    uint8_t bit7 : 1;
    uint8_t bit8 : 1;
    uint8_t bit9 : 1;
    uint8_t bit10 : 1;
    uint8_t bit11 : 1;
    uint8_t bit12 : 1;
    uint8_t bit13 : 1;
    uint8_t bit14 : 1;
    uint8_t bit15 : 1;
};

struct _8_bit_def {
    uint8_t bit0 : 1;
    uint8_t bit1 : 1;
    uint8_t bit2 : 1;
    uint8_t bit3 : 1;
    uint8_t bit4 : 1;
    uint8_t bit5 : 1;
    uint8_t bit6 : 1;
    uint8_t bit7 : 1;
};


union GLB
{
    uint16_t vGLB;
    struct char_bit_def bits;
};

union BYTE
{
    uint8_t value;
    struct _8_bit_def bits;
};

union INT16
{
    uint16_t vGLB;
    struct
    {
        uint8_t byte0;
        uint8_t byte1;
    }bytes;
    struct
    {
        uint8_t bit0 : 1;
        uint8_t bit1 : 1;
        uint8_t bit2 : 1;
        uint8_t bit3 : 1;
        uint8_t bit4 : 1;
        uint8_t bit5 : 1;
        uint8_t bit6 : 1;
        uint8_t bit7 : 1;
        uint8_t bit8 : 1;
        uint8_t bit9 : 1;
        uint8_t bit10 : 1;
        uint8_t bit11 : 1;
        uint8_t bit12 : 1;
        uint8_t bit13 : 1;
        uint8_t bit14 : 1;
        uint8_t bit15 : 1;
    }bits;
};

union LONG32
{
    unsigned long vGLB;
    struct
    {
        uint16_t word0;
        uint16_t word1;
    }word;
    struct
    {
        uint8_t byte0;
        uint8_t byte1;
        uint8_t byte2;
        uint8_t byte3;
    }bytes;
    struct
    {
        uint8_t bit0 : 1;
        uint8_t bit1 : 1;
        uint8_t bit2 : 1;
        uint8_t bit3 : 1;
        uint8_t bit4 : 1;
        uint8_t bit5 : 1;
        uint8_t bit6 : 1;
        uint8_t bit7 : 1;
        uint8_t bit8 : 1;
        uint8_t bit9 : 1;
        uint8_t bit10 : 1;
        uint8_t bit11 : 1;
        uint8_t bit12 : 1;
        uint8_t bit13 : 1;
        uint8_t bit14 : 1;
        uint8_t bit15 : 1;
        uint8_t bit16 : 1;
        uint8_t bit17 : 1;
        uint8_t bit18 : 1;
        uint8_t bit19 : 1;
        uint8_t bit20 : 1;
        uint8_t bit21 : 1;
        uint8_t bit22 : 1;
        uint8_t bit23 : 1;
        uint8_t bit24 : 1;
        uint8_t bit25 : 1;
        uint8_t bit26 : 1;
        uint8_t bit27 : 1;
        uint8_t bit28 : 1;
        uint8_t bit29 : 1;
        uint8_t bit30 : 1;
        uint8_t bit31 : 1;
    }bits;
};

/////////////////////temp!!!////////////////////////
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
//user utilize
extern const uint8_t NumberToWordTable[19];
extern const unsigned char NumberAndWordTable[27];

#define BIT0	0x01U
#define BIT1	0x02U
#define BIT2	0x04U
#define BIT3	0x08U
#define BIT4	0x10U
#define BIT5	0x20U
#define BIT6	0x40U
#define BIT7	0x80U
#endif