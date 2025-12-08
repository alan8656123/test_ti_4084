#ifndef LCD_MODULE_H_
#define LCD_MODULE_H_


struct LCD_Type
{
    unsigned bit0 : 1;
    unsigned bit1 : 1;
    unsigned bit2 : 1;
    unsigned bit3 : 1;
    unsigned bit4 : 1;
    unsigned bit5 : 1;
    unsigned bit6 : 1;
    unsigned bit7 : 1;
};


uint8_t Lcd_Data[40];


void LCD_IIC_Send(uint8_t *tx_data,uint32_t tx_count);
void LCD_IC_DisplayOff(void);
void LCD_IC_PowerOn(void);
void LCD_IC_PowerOff(void);
void LCD_IC_DisplayOn(void);
void LCD_IC_DisplayWrite(void);


#endif