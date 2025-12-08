
#include "ti_msp_dl_config.h"
#include "string.h"
#include "LCD_DRIVER.h"
#include "Uci8533.h"


const uint8_t DisOn_Uci8533_Command[2]=
{
    0x80U,0xC8U     /* ModeSet */
    // 0x80U,0xCBU     /* ModeSet */
};
const uint8_t DisOff_Uci8533_Command[2]=
{
    0x80U,0xC0U,    /* ModeSet */
};
const uint8_t PowerOn_Uci8533_Command[10] =
{   /* Initial State */
    0x80U,0x83U,    /* FrameRateSelect 00b=64hz,01b=82hz,10b=110hz,11b=200hz */
    0x80U,0xe0U,    /* DeviceSelect	*/
    0x80U,0xf8U,    /* BankSelect */
    0x80U,0xf0U,    /* BlinkSelect	*/
    0x80U,0x00U,    /* LoadDataPointer */
};
const uint8_t PowerOff_Uci8533_Command[2] =
{
    0x80U,0xC0U,    /* ModeSet */
};
const uint8_t LoadDataPoint_Uci8533_Command[2] =
{
    0x80U,0x00U,    /* ModeSet */
};

const uint8_t DataWrite_Uci8533_Command[1] =
{
    0x40    /* Write */
};


void LCD_IIC_Send(uint8_t *tx_data,uint32_t tx_count){
    memset(gTxPacket,0,tx_count);
    memcpy(gTxPacket, tx_data, tx_count);
    send(tx_count);
}

void LCD_IC_DisplayOff(void)
{
    LCD_IIC_Send(DisOff_Uci8533_Command, sizeof(DisOff_Uci8533_Command));
}

void LCD_IC_PowerOn(void)
{
    LCD_IIC_Send(PowerOn_Uci8533_Command, sizeof(PowerOn_Uci8533_Command));
}

void LCD_IC_PowerOff(void)
{
    LCD_IIC_Send(PowerOff_Uci8533_Command, sizeof(PowerOff_Uci8533_Command));
}

void LCD_IC_DisplayOn(void)
{
    LCD_IIC_Send(DisOn_Uci8533_Command, sizeof(DisOn_Uci8533_Command));
}


void LCD_IC_DisplayWrite(void)
{
    static uint8_t tx_buffer[53]; /*PowerOn : 10 + DataWrite : 1 + lcd_Data : 40 + DisOn : 2 = 53*/

    memcpy(tx_buffer,PowerOn_Uci8533_Command,sizeof(PowerOn_Uci8533_Command));
    memcpy(tx_buffer + sizeof(PowerOn_Uci8533_Command), DataWrite_Uci8533_Command, sizeof(DataWrite_Uci8533_Command));
    memcpy(tx_buffer + sizeof(PowerOn_Uci8533_Command) + sizeof(DataWrite_Uci8533_Command), Lcd_Data, sizeof(Lcd_Data));
    memcpy(tx_buffer + sizeof(PowerOn_Uci8533_Command) + sizeof(DataWrite_Uci8533_Command) + sizeof(Lcd_Data), DisOn_Uci8533_Command, sizeof(DisOn_Uci8533_Command));
    LCD_IIC_Send(tx_buffer, sizeof(tx_buffer));
}