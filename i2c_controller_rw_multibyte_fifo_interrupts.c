/*
 * Copyright (c) 2021, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "ti_msp_dl_config.h"
#include "string.h"

/* Maximum size of TX packet */

/* Number of bytes to send to target device */

/* Maximum size of RX packet */
#define I2C_RX_MAX_PACKET_SIZE (16)

/* Number of bytes to received from target */
#define I2C_RX_PACKET_SIZE (16)

/* I2C Target address */
#define I2C_TARGET_ADDRESS (0x38)

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


/* Data sent to the Target */
uint8_t gTxPacket[64] = { 0 };


/* Counters for TX length and bytes sent */
uint32_t gTxLen, gTxCount;

/* Data received from Target */
uint8_t gRxPacket[I2C_RX_MAX_PACKET_SIZE];
/* Counters for TX length and bytes sent */
uint32_t gRxLen, gRxCount;
/* Indicates status of I2C */
static enum I2cControllerStatus {
    I2C_STATUS_IDLE = 0,
    I2C_STATUS_TX_STARTED,
    I2C_STATUS_TX_INPROGRESS,
    I2C_STATUS_TX_COMPLETE,
    I2C_STATUS_RX_STARTED,
    I2C_STATUS_RX_INPROGRESS,
    I2C_STATUS_RX_COMPLETE,
    I2C_STATUS_ERROR,
} gI2cControllerStatus;


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




void send(uint32_t I2C_TX_packet_size)
{
     gI2cControllerStatus = I2C_STATUS_IDLE;

     gTxLen = I2C_TX_packet_size;
     /*
      * Fill the FIFO
      *  The FIFO is 8-bytes deep, and this function will return number
      *  of bytes written to FIFO */
     gTxCount = DL_I2C_fillControllerTXFIFO(I2C_INST, &gTxPacket[0], gTxLen);
     /* Enable TXFIFO trigger interrupt if there are more bytes to send */
     if (gTxCount < gTxLen) {
         DL_I2C_enableInterrupt(
             I2C_INST, DL_I2C_INTERRUPT_CONTROLLER_TXFIFO_TRIGGER);
     } else {
         DL_I2C_disableInterrupt(
             I2C_INST, DL_I2C_INTERRUPT_CONTROLLER_TXFIFO_TRIGGER);
     }

     /*
      * Send the packet to the controller.
      * This function will send Start + Stop automatically.
      */
     gI2cControllerStatus = I2C_STATUS_TX_STARTED;
     while (!(
         DL_I2C_getControllerStatus(I2C_INST) & DL_I2C_CONTROLLER_STATUS_IDLE))
         ;
     DL_I2C_startControllerTransfer(
         I2C_INST, I2C_TARGET_ADDRESS, DL_I2C_CONTROLLER_DIRECTION_TX, gTxLen);

     /* Wait until the Controller sends all bytes */
     while ((gI2cControllerStatus != I2C_STATUS_TX_COMPLETE) &&
            (gI2cControllerStatus != I2C_STATUS_ERROR)) {
         __WFE();
     }

     while (DL_I2C_getControllerStatus(I2C_INST) &
            DL_I2C_CONTROLLER_STATUS_BUSY_BUS)
         ;

     /* Trap if there was an error */
     if (DL_I2C_getControllerStatus(I2C_INST) &
         DL_I2C_CONTROLLER_STATUS_ERROR) {
         /* LED will remain high if there is an error */
         __BKPT(0);
     }

     while (!(
         DL_I2C_getControllerStatus(I2C_INST) & DL_I2C_CONTROLLER_STATUS_IDLE))
         ;

     /* Add delay between transfers */
     delay_cycles(1000);
}

static void LCD_IIC_Send(uint8_t *tx_data,uint32_t tx_count){
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

uint8_t Lcd_Data[40];

void LCD_IC_DisplayWrite(void)
{
    static uint8_t tx_buffer[53]; /*PowerOn : 10 + DataWrite : 1 + lcd_Data : 40 + DisOn : 2 = 53*/

    memcpy(tx_buffer,PowerOn_Uci8533_Command,sizeof(PowerOn_Uci8533_Command));
    memcpy(tx_buffer + sizeof(PowerOn_Uci8533_Command), DataWrite_Uci8533_Command, sizeof(DataWrite_Uci8533_Command));
    memcpy(tx_buffer + sizeof(PowerOn_Uci8533_Command) + sizeof(DataWrite_Uci8533_Command), Lcd_Data, sizeof(Lcd_Data));
    memcpy(tx_buffer + sizeof(PowerOn_Uci8533_Command) + sizeof(DataWrite_Uci8533_Command) + sizeof(Lcd_Data), DisOn_Uci8533_Command, sizeof(DisOn_Uci8533_Command));
    LCD_IIC_Send(tx_buffer, sizeof(tx_buffer));
}

#define     LCD_A27              (((struct LCD_Type *) &Lcd_Data[0])->bit7)    /* SEG0 */
#define     LCD_X41  	         (((struct LCD_Type *) &Lcd_Data[0])->bit6)
#define     LCD_X43              (((struct LCD_Type *) &Lcd_Data[0])->bit5)
#define     LCD_9D               (((struct LCD_Type *) &Lcd_Data[0])->bit4)
#define     LCD_A26 		     (((struct LCD_Type *) &Lcd_Data[0])->bit3)    /* SEG1 */
#define     LCD_X42	    	     (((struct LCD_Type *) &Lcd_Data[0])->bit2)
#define     LCD_X44 	    	 (((struct LCD_Type *) &Lcd_Data[0])->bit1)
#define     LCD_10D		         (((struct LCD_Type *) &Lcd_Data[0])->bit0)

#define     LCD_A30              (((struct LCD_Type *) &Lcd_Data[1])->bit7)    /* SEG2 */
#define     LCD_10B  	         (((struct LCD_Type *) &Lcd_Data[1])->bit6)
#define     LCD_A33              (((struct LCD_Type *) &Lcd_Data[1])->bit5)
#define     LCD_10C              (((struct LCD_Type *) &Lcd_Data[1])->bit4)
#define     LCD_A29 		     (((struct LCD_Type *) &Lcd_Data[1])->bit3)    /* SEG3 */
#define     LCD_10A	    	     (((struct LCD_Type *) &Lcd_Data[1])->bit2)
#define     LCD_A25 	    	 (((struct LCD_Type *) &Lcd_Data[1])->bit1)
#define     LCD_10G		         (((struct LCD_Type *) &Lcd_Data[1])->bit0)

#define     LCD_A41              (((struct LCD_Type *) &Lcd_Data[2])->bit7)    /* SEG4 */
#define     LCD_10F  	         (((struct LCD_Type *) &Lcd_Data[2])->bit6)
#define     LCD_A24              (((struct LCD_Type *) &Lcd_Data[2])->bit5)
#define     LCD_10E              (((struct LCD_Type *) &Lcd_Data[2])->bit4)
#define     LCD_A40 		     (((struct LCD_Type *) &Lcd_Data[2])->bit3)    /* SEG5 */
#define     LCD_X45	    	     (((struct LCD_Type *) &Lcd_Data[2])->bit2)
#define     LCD_A23 	    	 (((struct LCD_Type *) &Lcd_Data[2])->bit1)
#define     LCD_14D		         (((struct LCD_Type *) &Lcd_Data[2])->bit0)

#define     LCD_A22              (((struct LCD_Type *) &Lcd_Data[3])->bit7)    /* SEG6 */
#define     LCD_14B  	         (((struct LCD_Type *) &Lcd_Data[3])->bit6)
#define     LCD_A34              (((struct LCD_Type *) &Lcd_Data[3])->bit5)
#define     LCD_14C              (((struct LCD_Type *) &Lcd_Data[3])->bit4)
#define     LCD_A21 		     (((struct LCD_Type *) &Lcd_Data[3])->bit3)    /* SEG7 */
#define     LCD_14A	    	     (((struct LCD_Type *) &Lcd_Data[3])->bit2)
#define     LCD_X46 	    	 (((struct LCD_Type *) &Lcd_Data[3])->bit1)
#define     LCD_14G		         (((struct LCD_Type *) &Lcd_Data[3])->bit0)

#define     LCD_A20              (((struct LCD_Type *) &Lcd_Data[4])->bit7)    /* SEG8 */
#define     LCD_14F  	         (((struct LCD_Type *) &Lcd_Data[4])->bit6)
#define     LCD_X47              (((struct LCD_Type *) &Lcd_Data[4])->bit5)
#define     LCD_14E              (((struct LCD_Type *) &Lcd_Data[4])->bit4)
#define     LCD_A19 		     (((struct LCD_Type *) &Lcd_Data[4])->bit3)    /* SEG9 */
#define     LCD_13B	    	     (((struct LCD_Type *) &Lcd_Data[4])->bit2)
#define     LCD_X49 	    	 (((struct LCD_Type *) &Lcd_Data[4])->bit1)
#define     LCD_13C		         (((struct LCD_Type *) &Lcd_Data[4])->bit0)

#define     LCD_A18              (((struct LCD_Type *) &Lcd_Data[5])->bit7)    /* SEG10 */
#define     LCD_13A  	         (((struct LCD_Type *) &Lcd_Data[5])->bit6)
#define     LCD_A35              (((struct LCD_Type *) &Lcd_Data[5])->bit5)
#define     LCD_13G              (((struct LCD_Type *) &Lcd_Data[5])->bit4)
#define     LCD_A17 		     (((struct LCD_Type *) &Lcd_Data[5])->bit3)    /* SEG11 */
#define     LCD_13F	    	     (((struct LCD_Type *) &Lcd_Data[5])->bit2)
#define     LCD_X50 	    	 (((struct LCD_Type *) &Lcd_Data[5])->bit1)
#define     LCD_13E		         (((struct LCD_Type *) &Lcd_Data[5])->bit0)

#define     LCD_A16              (((struct LCD_Type *) &Lcd_Data[6])->bit7)    /* SEG12 */
#define     LCD_X48  	         (((struct LCD_Type *) &Lcd_Data[6])->bit6)
#define     LCD_X51              (((struct LCD_Type *) &Lcd_Data[6])->bit5)
#define     LCD_COL              (((struct LCD_Type *) &Lcd_Data[6])->bit4)
#define     LCD_A15 		     (((struct LCD_Type *) &Lcd_Data[6])->bit3)    /* SEG13 */
#define     LCD_12B	    	     (((struct LCD_Type *) &Lcd_Data[6])->bit2)
#define     LCD_A36 	    	 (((struct LCD_Type *) &Lcd_Data[6])->bit1)
#define     LCD_12C		         (((struct LCD_Type *) &Lcd_Data[6])->bit0)

#define     LCD_A14              (((struct LCD_Type *) &Lcd_Data[7])->bit7)    /* SEG14 */
#define     LCD_12A  	         (((struct LCD_Type *) &Lcd_Data[7])->bit6)
#define     LCD_X52              (((struct LCD_Type *) &Lcd_Data[7])->bit5)
#define     LCD_12G              (((struct LCD_Type *) &Lcd_Data[7])->bit4)
#define     LCD_A13		         (((struct LCD_Type *) &Lcd_Data[7])->bit3)    /* SEG15 */
#define     LCD_12F		         (((struct LCD_Type *) &Lcd_Data[7])->bit2)
#define     LCD_X53  		     (((struct LCD_Type *) &Lcd_Data[7])->bit1)
#define     LCD_12E		         (((struct LCD_Type *) &Lcd_Data[7])->bit0)

#define     LCD_A12              (((struct LCD_Type *) &Lcd_Data[8])->bit7)    /* SEG16 */
#define     LCD_11B  	         (((struct LCD_Type *) &Lcd_Data[8])->bit6)
#define     LCD_X54              (((struct LCD_Type *) &Lcd_Data[8])->bit5)
#define     LCD_12D              (((struct LCD_Type *) &Lcd_Data[8])->bit4)
#define     LCD_A11		         (((struct LCD_Type *) &Lcd_Data[8])->bit3)    /* SEG17 */
#define     LCD_11A		         (((struct LCD_Type *) &Lcd_Data[8])->bit2)
#define     LCD_A37 		     (((struct LCD_Type *) &Lcd_Data[8])->bit1)
#define     LCD_11G		         (((struct LCD_Type *) &Lcd_Data[8])->bit0)

#define     LCD_A10              (((struct LCD_Type *) &Lcd_Data[9])->bit7)    /* SEG18 */
#define     LCD_11E  	         (((struct LCD_Type *) &Lcd_Data[9])->bit6)
#define     LCD_A9               (((struct LCD_Type *) &Lcd_Data[9])->bit5)
#define     LCD_11C              (((struct LCD_Type *) &Lcd_Data[9])->bit4)
#define     LCD_A7	             (((struct LCD_Type *) &Lcd_Data[9])->bit3)    /* SEG19 */
#define     LCD_11D		         (((struct LCD_Type *) &Lcd_Data[9])->bit2)
#define     LCD_A8  		     (((struct LCD_Type *) &Lcd_Data[9])->bit1)
#define     LCD_13D		         (((struct LCD_Type *) &Lcd_Data[9])->bit0)

#define     LCD_A6               (((struct LCD_Type *) &Lcd_Data[10])->bit7)    /* SEG20 */
#define     LCD_9B 	             (((struct LCD_Type *) &Lcd_Data[10])->bit6)
#define     LCD_A38              (((struct LCD_Type *) &Lcd_Data[10])->bit5)
#define     LCD_9C               (((struct LCD_Type *) &Lcd_Data[10])->bit4)
#define     LCD_A5	             (((struct LCD_Type *) &Lcd_Data[10])->bit3)    /* SEG21 */
#define     LCD_9A	             (((struct LCD_Type *) &Lcd_Data[10])->bit2)
#define     LCD_X55 		     (((struct LCD_Type *) &Lcd_Data[10])->bit1)
#define     LCD_9G	             (((struct LCD_Type *) &Lcd_Data[10])->bit0)

#define     LCD_A4               (((struct LCD_Type *) &Lcd_Data[11])->bit7)    /* SEG22 */
#define     LCD_9F 	  	         (((struct LCD_Type *) &Lcd_Data[11])->bit6)
#define     LCD_X56               (((struct LCD_Type *) &Lcd_Data[11])->bit5)
#define     LCD_9E               (((struct LCD_Type *) &Lcd_Data[11])->bit4)
#define     LCD_A3	  	         (((struct LCD_Type *) &Lcd_Data[11])->bit3)    /* SEG23 */
#define     LCD_8A	  	         (((struct LCD_Type *) &Lcd_Data[11])->bit2)
#define     LCD_X57		         (((struct LCD_Type *) &Lcd_Data[11])->bit1)
#define     LCD_8B	  	         (((struct LCD_Type *) &Lcd_Data[11])->bit0)

#define     LCD_A2               (((struct LCD_Type *) &Lcd_Data[12])->bit7)    /* SEG24 */
#define     LCD_8G 	             (((struct LCD_Type *) &Lcd_Data[12])->bit6)
#define     LCD_A39              (((struct LCD_Type *) &Lcd_Data[12])->bit5)
#define     LCD_8C               (((struct LCD_Type *) &Lcd_Data[12])->bit4)
#define     LCD_A1	             (((struct LCD_Type *) &Lcd_Data[12])->bit3)    /* SEG25 */
#define     LCD_8E	             (((struct LCD_Type *) &Lcd_Data[12])->bit2)
#define     LCD_X26 		     (((struct LCD_Type *) &Lcd_Data[12])->bit1)
#define     LCD_8D	             (((struct LCD_Type *) &Lcd_Data[12])->bit0)

#define     LCD_X36              (((struct LCD_Type *) &Lcd_Data[13])->bit7)    /* SEG26 */
#define     LCD_X37              (((struct LCD_Type *) &Lcd_Data[13])->bit6)
#define     LCD_X38              (((struct LCD_Type *) &Lcd_Data[13])->bit5)
#define     LCD_X39              (((struct LCD_Type *) &Lcd_Data[13])->bit4)
#define     LCD_1E               (((struct LCD_Type *) &Lcd_Data[13])->bit3)    /* SEG27 */
//#define     LCD_10C		         (((struct LCD_Type *) &Lcd_Data[13])->bit2)
#define     LCD_1F               (((struct LCD_Type *) &Lcd_Data[13])->bit1)
///#define     LCD_X12		         (((struct LCD_Type *) &Lcd_Data[13])->bit0)

#define     LCD_1D               (((struct LCD_Type *) &Lcd_Data[14])->bit7)    /* SEG28 */
#define     LCD_1A               (((struct LCD_Type *) &Lcd_Data[14])->bit6)
#define     LCD_1G               (((struct LCD_Type *) &Lcd_Data[14])->bit5)
//#define     LCD_X11             (((struct LCD_Type *) &Lcd_Data[14])->bit4)
#define     LCD_1C               (((struct LCD_Type *) &Lcd_Data[14])->bit3)    /* SEG29 */
#define     LCD_X35              (((struct LCD_Type *) &Lcd_Data[14])->bit2)
#define     LCD_1B               (((struct LCD_Type *) &Lcd_Data[14])->bit1)
#define     LCD_X34              (((struct LCD_Type *) &Lcd_Data[14])->bit0)

#define     LCD_2E               (((struct LCD_Type *) &Lcd_Data[15])->bit7)    /* SEG30 */
//#define     LCD_2F  	         (((struct LCD_Type *) &Lcd_Data[15])->bit6)
#define     LCD_2F               (((struct LCD_Type *) &Lcd_Data[15])->bit5)
//#define     LCD_1C               (((struct LCD_Type *) &Lcd_Data[15])->bit4)
#define     LCD_2D               (((struct LCD_Type *) &Lcd_Data[15])->bit3)    /* SEG31 */
#define     LCD_2A               (((struct LCD_Type *) &Lcd_Data[15])->bit2)
#define     LCD_2G               (((struct LCD_Type *) &Lcd_Data[15])->bit1)
//#define     LCD_2D	             (((struct LCD_Type *) &Lcd_Data[15])->bit0)

#define     LCD_2C               (((struct LCD_Type *) &Lcd_Data[16])->bit7)    /* SEG32 */
//#define     LCD_2G  	         (((struct LCD_Type *) &Lcd_Data[16])->bit6)
#define     LCD_2B           (((struct LCD_Type *) &Lcd_Data[16])->bit5)
//#define     LCD_2C               (((struct LCD_Type *) &Lcd_Data[16])->bit4)
#define     LCD_3E               (((struct LCD_Type *) &Lcd_Data[16])->bit3)    /* SEG33 */
#define     LCD_X32               (((struct LCD_Type *) &Lcd_Data[16])->bit2)
#define     LCD_3F               (((struct LCD_Type *) &Lcd_Data[16])->bit1)
#define     LCD_X33               (((struct LCD_Type *) &Lcd_Data[16])->bit0)

#define     LCD_3D               (((struct LCD_Type *) &Lcd_Data[17])->bit7)    /* SEG34 */
#define     LCD_3A               (((struct LCD_Type *) &Lcd_Data[17])->bit6)
#define     LCD_3G               (((struct LCD_Type *) &Lcd_Data[17])->bit5)
//#define     LCD_3C               (((struct LCD_Type *) &Lcd_Data[17])->bit4)
#define     LCD_3C               (((struct LCD_Type *) &Lcd_Data[17])->bit3)    /* SEG35 */
#define     LCD_X31               (((struct LCD_Type *) &Lcd_Data[17])->bit2)
#define     LCD_3B               (((struct LCD_Type *) &Lcd_Data[17])->bit1)
#define     LCD_X40               (((struct LCD_Type *) &Lcd_Data[17])->bit0)

#define     LCD_4E               (((struct LCD_Type *) &Lcd_Data[18])->bit7)    /* SEG36 */
#define     LCD_X30 	         (((struct LCD_Type *) &Lcd_Data[18])->bit6)
#define     LCD_4F               (((struct LCD_Type *) &Lcd_Data[18])->bit5)
#define     LCD_X29              (((struct LCD_Type *) &Lcd_Data[18])->bit4)
#define     LCD_4D               (((struct LCD_Type *) &Lcd_Data[18])->bit3)    /* SEG37 */
#define     LCD_4A               (((struct LCD_Type *) &Lcd_Data[18])->bit2)
#define     LCD_4G               (((struct LCD_Type *) &Lcd_Data[18])->bit1)
#define     LCD_X28              (((struct LCD_Type *) &Lcd_Data[18])->bit0)

#define     LCD_4C               (((struct LCD_Type *) &Lcd_Data[19])->bit7)    /* SEG38 */
//#define     LCD_5G               (((struct LCD_Type *) &Lcd_Data[19])->bit6)
#define     LCD_4B               (((struct LCD_Type *) &Lcd_Data[19])->bit5)
//#define     LCD_5C               (((struct LCD_Type *) &Lcd_Data[19])->bit4)


//#define     LCD_16E		         (((struct LCD_Type *) &Lcd_Data[29])->bit7)    /* SEG58 */
#define     LCD_X1              (((struct LCD_Type *) &Lcd_Data[29])->bit6)
//#define     LCD_16D              (((struct LCD_Type *) &Lcd_Data[29])->bit5)
#define     LCD_X2              (((struct LCD_Type *) &Lcd_Data[29])->bit4)
//#define     LCD_16G              (((struct LCD_Type *) &Lcd_Data[29])->bit3)    /* SEG59 */
#define     LCD_X7  	         (((struct LCD_Type *) &Lcd_Data[29])->bit2)
#define     LCD_X14_C          (((struct LCD_Type *) &Lcd_Data[29])->bit1)
#define     LCD_X8              (((struct LCD_Type *) &Lcd_Data[29])->bit0)

//#define     LCD_BLANK14		     (((struct LCD_Type *) &Lcd_Data[30])->bit7)    /* SEG60 */
#define     LCD_X10              (((struct LCD_Type *) &Lcd_Data[30])->bit6)
//#define     LCD_BLANK15          (((struct LCD_Type *) &Lcd_Data[30])->bit5)
#define     LCD_X9              (((struct LCD_Type *) &Lcd_Data[30])->bit4)
//#define     LCD_X46              (((struct LCD_Type *) &Lcd_Data[30])->bit3)    /* SEG61 */
#define     LCD_X4  	         (((struct LCD_Type *) &Lcd_Data[30])->bit2)
//#define     LCD_X51              (((struct LCD_Type *) &Lcd_Data[30])->bit1)
#define     LCD_X3              (((struct LCD_Type *) &Lcd_Data[30])->bit0)

#define     LCD_X13		         (((struct LCD_Type *) &Lcd_Data[31])->bit7)    /* SEG62 */
#define     LCD_X11              (((struct LCD_Type *) &Lcd_Data[31])->bit6)
#define     LCD_X14_A             (((struct LCD_Type *) &Lcd_Data[31])->bit5)
#define     LCD_X5               (((struct LCD_Type *) &Lcd_Data[31])->bit4)
//#define     LCD_BLANK16          (((struct LCD_Type *) &Lcd_Data[31])->bit3)    /* SEG63 */
#define     LCD_X12  	     (((struct LCD_Type *) &Lcd_Data[31])->bit2)
#define     LCD_X14_B          (((struct LCD_Type *) &Lcd_Data[31])->bit1)
#define     LCD_X6          (((struct LCD_Type *) &Lcd_Data[31])->bit0)

//#define     LCD_4E               (((struct LCD_Type *) &Lcd_Data[32])->bit7)    /* SEG64 */
#define     LCD_X20 	         (((struct LCD_Type *) &Lcd_Data[32])->bit6)
#define     LCD_X19               (((struct LCD_Type *) &Lcd_Data[32])->bit5)
#define     LCD_X15              (((struct LCD_Type *) &Lcd_Data[32])->bit4)
//#define     LCD_4D               (((struct LCD_Type *) &Lcd_Data[32])->bit3)    /* SEG65 */
#define     LCD_X21               (((struct LCD_Type *) &Lcd_Data[32])->bit2)
#define     LCD_X22               (((struct LCD_Type *) &Lcd_Data[32])->bit1)
#define     LCD_X16              (((struct LCD_Type *) &Lcd_Data[32])->bit0)

//#define     LCD_4E               (((struct LCD_Type *) &Lcd_Data[33])->bit7)    /* SEG66 */
#define     LCD_X24 	         (((struct LCD_Type *) &Lcd_Data[33])->bit6)
#define     LCD_X23               (((struct LCD_Type *) &Lcd_Data[33])->bit5)
#define     LCD_X17              (((struct LCD_Type *) &Lcd_Data[33])->bit4)
//#define     LCD_4D               (((struct LCD_Type *) &Lcd_Data[33])->bit3)    /* SEG67 */
#define     LCD_6C               (((struct LCD_Type *) &Lcd_Data[33])->bit2)
//#define     LCD_4G               (((struct LCD_Type *) &Lcd_Data[33])->bit1)
#define     LCD_6B              (((struct LCD_Type *) &Lcd_Data[33])->bit0)

#define     LCD_A31               (((struct LCD_Type *) &Lcd_Data[34])->bit7)    /* SEG68 */
#define     LCD_7G 	         (((struct LCD_Type *) &Lcd_Data[34])->bit6)
#define     LCD_7B               (((struct LCD_Type *) &Lcd_Data[34])->bit5)
#define     LCD_7C              (((struct LCD_Type *) &Lcd_Data[34])->bit4)
#define     LCD_A28               (((struct LCD_Type *) &Lcd_Data[34])->bit3)    /* SEG69 */
#define     LCD_7H               (((struct LCD_Type *) &Lcd_Data[34])->bit2)
#define     LCD_7A               (((struct LCD_Type *) &Lcd_Data[34])->bit1)
#define     LCD_7D               (((struct LCD_Type *) &Lcd_Data[34])->bit0)

#define     LCD_A32               (((struct LCD_Type *) &Lcd_Data[35])->bit7)    /* SEG70 */
#define     LCD_7E  	         (((struct LCD_Type *) &Lcd_Data[35])->bit6)
#define     LCD_7F               (((struct LCD_Type *) &Lcd_Data[35])->bit5)
#define     LCD_X25_B              (((struct LCD_Type *) &Lcd_Data[35])->bit4)
//#define     LCD_4D               (((struct LCD_Type *) &Lcd_Data[35])->bit3)    /* SEG71 */
//#define     LCD_4A               (((struct LCD_Type *) &Lcd_Data[35])->bit2)
//#define     LCD_4G               (((struct LCD_Type *) &Lcd_Data[35])->bit1)
#define     LCD_X25_A              (((struct LCD_Type *) &Lcd_Data[35])->bit0)

//#define     LCD_4E               (((struct LCD_Type *) &Lcd_Data[36])->bit7)    /* SEG72 */
#define     LCD_5F 	             (((struct LCD_Type *) &Lcd_Data[36])->bit6)
#define     LCD_5E               (((struct LCD_Type *) &Lcd_Data[36])->bit5)
#define     LCD_X27              (((struct LCD_Type *) &Lcd_Data[36])->bit4)
//#define     LCD_4D               (((struct LCD_Type *) &Lcd_Data[36])->bit3)    /* SEG73 */
#define     LCD_5G               (((struct LCD_Type *) &Lcd_Data[36])->bit2)
#define     LCD_5D               (((struct LCD_Type *) &Lcd_Data[36])->bit1)
#define     LCD_5A               (((struct LCD_Type *) &Lcd_Data[36])->bit0)

//#define     LCD_4E               (((struct LCD_Type *) &Lcd_Data[37])->bit7)    /* SEG74 */
#define     LCD_5C 	         (((struct LCD_Type *) &Lcd_Data[37])->bit6)
#define     LCD_DP               (((struct LCD_Type *) &Lcd_Data[37])->bit5)
#define     LCD_5B              (((struct LCD_Type *) &Lcd_Data[37])->bit4)
//#define     LCD_4D               (((struct LCD_Type *) &Lcd_Data[37])->bit3)    /* SEG75 */
#define     LCD_6E               (((struct LCD_Type *) &Lcd_Data[37])->bit2)
#define     LCD_X18               (((struct LCD_Type *) &Lcd_Data[37])->bit1)
#define     LCD_6F              (((struct LCD_Type *) &Lcd_Data[37])->bit0)

//#define     LCD_4E               (((struct LCD_Type *) &Lcd_Data[38])->bit7)    /* SEG76 */
#define     LCD_6G 	             (((struct LCD_Type *) &Lcd_Data[38])->bit6)
#define     LCD_6D               (((struct LCD_Type *) &Lcd_Data[38])->bit5)
#define     LCD_6A              (((struct LCD_Type *) &Lcd_Data[38])->bit4)


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

void delay(uint32_t times){
    delay_cycles(times*32000);
}

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


int main(void)
{

    uint32_t count = 0;
     SYSCFG_DL_init();

     /* Set LED to indicate start of transfer */

     NVIC_EnableIRQ(I2C_INST_INT_IRQN);
     DL_SYSCTL_disableSleepOnExit();

    // open////////////////////////////////////////////////
    delay_cycles(8000000);
    //send(2);
    LCD_IC_DisplayOn();


    // all light////////////////////////////////////////////////
    delay_cycles(4000000);
    //send(55);

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

     
//////////////display///////////////////
    delay(1000);


    DL_GPIO_setPins(GPIO_CLR_PORT, GPIO_CLR_PIN_CLR_PIN);
    uint8_t display_digit;

    uint8_t SPEED=0;
    uint8_t speed_digit;
    uint8_t speed_ten;
    uint8_t speed_hun;


    uint8_t speed_rpm[28];
    int speed_rpm_count=0;
    uint8_t speed_rpm_val=0;

    uint32_t fuel_bar=0;
    uint8_t fuel_cal=0;

    uint8_t hour_ten=1;
    uint8_t hour_digit=2;
    uint8_t min_ten=0;
    uint8_t min_digit=0;

    uint8_t GEAR=0;
    uint8_t GEAR_num=0;


    //KM not mph
    LCD_X41=1;
    LCD_X42=0;
    LCD_X24=0;
    LCD_X23=0;
    LCD_X22=1;
    LCD_X21=1;


    //ODO etc off
    const uint8_t anime_loop = 200;

    while (1){
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
                        speed_rpm_count ++;
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
                  speed_rpm_count ++;
        }
       else if(count%anime_loop<190)
        {
         SPEED -=7;
         speed_rpm_count --;
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
        GEAR_num = NumberToWordTable[GEAR];
       LCD_7A = (((DISPLAY_DIGITAL_TYPE *)& GEAR_num)->A);
       LCD_7B = (((DISPLAY_DIGITAL_TYPE *)& GEAR_num)->B);
       LCD_7C = (((DISPLAY_DIGITAL_TYPE *)& GEAR_num)->C);
       LCD_7D = (((DISPLAY_DIGITAL_TYPE *)& GEAR_num)->D);
       LCD_7E = (((DISPLAY_DIGITAL_TYPE *)& GEAR_num)->E);
       LCD_7F = (((DISPLAY_DIGITAL_TYPE *)& GEAR_num)->F);
       LCD_7G = (((DISPLAY_DIGITAL_TYPE *)& GEAR_num)->G);
        speed_hun = SPEED/100 %10;
        speed_ten = SPEED/10 %10;
        speed_digit = SPEED %10;

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



        LCD_X35=1;
        LCD_X32=0;
        LCD_X34=0;
        LCD_X33=0;
        LCD_X31=0;
        LCD_X30=0;
        LCD_X29=0;
        LCD_X28=0;
        LCD_X27=0;
        LCD_X29=0;


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









        if(count%20==0){//250sec

            uint8_t hourten_temp=(count/20)%3;
            uint8_t hour_digit_temp=(count/20)%10;
            if (hourten_temp ==0)hourten_temp=16;
            if(hourten_temp ==2)hour_digit_temp%=4;

                hour_ten = NumberToWordTable[hourten_temp];
                LCD_11A = (((DISPLAY_DIGITAL_TYPE *)&hour_ten)->A);
                LCD_11B = (((DISPLAY_DIGITAL_TYPE *)&hour_ten)->B);
                LCD_11C = (((DISPLAY_DIGITAL_TYPE *)&hour_ten)->C);
                LCD_11D = (((DISPLAY_DIGITAL_TYPE *)&hour_ten)->D);
                LCD_11E = (((DISPLAY_DIGITAL_TYPE *)&hour_ten)->E);
                //LCD_8F = (((DISPLAY_DIGITAL_TYPE *)&hour_ten)->F);
                LCD_11G = (((DISPLAY_DIGITAL_TYPE *)&hour_ten)->G);

                hour_digit = NumberToWordTable[hour_digit_temp];
                LCD_12A = (((DISPLAY_DIGITAL_TYPE *)&hour_digit)->A);
                LCD_12B = (((DISPLAY_DIGITAL_TYPE *)&hour_digit)->B);
                LCD_12C = (((DISPLAY_DIGITAL_TYPE *)&hour_digit)->C);
                LCD_12D = (((DISPLAY_DIGITAL_TYPE *)&hour_digit)->D);
                LCD_12E = (((DISPLAY_DIGITAL_TYPE *)&hour_digit)->E);
                LCD_12F = (((DISPLAY_DIGITAL_TYPE *)&hour_digit)->F);
                LCD_12G = (((DISPLAY_DIGITAL_TYPE *)&hour_digit)->G);

                min_ten = NumberToWordTable[(count/20)%6];
                LCD_13A = (((DISPLAY_DIGITAL_TYPE *)&min_ten)->A);
                LCD_13B = (((DISPLAY_DIGITAL_TYPE *)&min_ten)->B);
                LCD_13C = (((DISPLAY_DIGITAL_TYPE *)&min_ten)->C);
                LCD_13D = (((DISPLAY_DIGITAL_TYPE *)&min_ten)->D);
                LCD_13E = (((DISPLAY_DIGITAL_TYPE *)&min_ten)->E);
                LCD_13F = (((DISPLAY_DIGITAL_TYPE *)&min_ten)->F);
                LCD_13G = (((DISPLAY_DIGITAL_TYPE *)&min_ten)->G);

                min_digit = NumberToWordTable[(count/20)%6];
                LCD_14A = (((DISPLAY_DIGITAL_TYPE *)&min_digit)->A);
                LCD_14B = (((DISPLAY_DIGITAL_TYPE *)&min_digit)->B);
                LCD_14C = (((DISPLAY_DIGITAL_TYPE *)&min_digit)->C);
                LCD_14D = (((DISPLAY_DIGITAL_TYPE *)&min_digit)->D);
                LCD_14E = (((DISPLAY_DIGITAL_TYPE *)&min_digit)->E);
                LCD_14F = (((DISPLAY_DIGITAL_TYPE *)&min_digit)->F);
                LCD_14G = (((DISPLAY_DIGITAL_TYPE *)&min_digit)->G);
        }

        if(count%30==0){//5
                fuel_bar++;
                fuel_cal = fuel_bar %13;

                if(fuel_cal>=7)fuel_cal=12-fuel_cal;
                /*if(fuel_cal==7)fuel_cal=5;
                if(fuel_cal==8)fuel_cal=4;
                if(fuel_cal==9)fuel_cal=3;
                if(fuel_cal==10)fuel_cal=2;
                if(fuel_cal==11)fuel_cal=1;
                if(fuel_cal==12)fuel_cal=0;*/

                LCD_X7 = fuel_cal%7<=5;
                LCD_X8 = fuel_cal%7<=4;
                LCD_X9 = fuel_cal%7<=3;
                LCD_X10 = fuel_cal%7<=2;
                LCD_X11 = fuel_cal%7<=1;
                LCD_X12 = fuel_cal%7<=0;

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




        LCD_IC_DisplayWrite();
        delay(50);
        count++;
    
    }

}

void I2C_INST_IRQHandler(void)
{
    switch (DL_I2C_getPendingInterrupt(I2C_INST)) {
        case DL_I2C_IIDX_CONTROLLER_RX_DONE:
            gI2cControllerStatus = I2C_STATUS_RX_COMPLETE;
            break;
        case DL_I2C_IIDX_CONTROLLER_TX_DONE:
            DL_I2C_disableInterrupt(
                I2C_INST, DL_I2C_INTERRUPT_CONTROLLER_TXFIFO_TRIGGER);
            gI2cControllerStatus = I2C_STATUS_TX_COMPLETE;
            break;
        case DL_I2C_IIDX_CONTROLLER_RXFIFO_TRIGGER:
            gI2cControllerStatus = I2C_STATUS_RX_INPROGRESS;
            /* Receive all bytes from target */
            while (DL_I2C_isControllerRXFIFOEmpty(I2C_INST) != true) {
                if (gRxCount < gRxLen) {
                    gRxPacket[gRxCount++] =
                        DL_I2C_receiveControllerData(I2C_INST);
                } else {
                    /* Ignore and remove from FIFO if the buffer is full */
                    DL_I2C_receiveControllerData(I2C_INST);
                }
            }
            break;
        case DL_I2C_IIDX_CONTROLLER_TXFIFO_TRIGGER:
            gI2cControllerStatus = I2C_STATUS_TX_INPROGRESS;
            /* Fill TX FIFO with next bytes to send */
            if (gTxCount < gTxLen) {
                gTxCount += DL_I2C_fillControllerTXFIFO(
                    I2C_INST, &gTxPacket[gTxCount], gTxLen - gTxCount);
            }
            break;
            /* Not used for this example */
        case DL_I2C_IIDX_CONTROLLER_ARBITRATION_LOST:
        case DL_I2C_IIDX_CONTROLLER_NACK:
            if ((gI2cControllerStatus == I2C_STATUS_RX_STARTED) ||
                (gI2cControllerStatus == I2C_STATUS_TX_STARTED)) {
                /* NACK interrupt if I2C Target is disconnected */
                gI2cControllerStatus = I2C_STATUS_ERROR;
            }
        case DL_I2C_IIDX_CONTROLLER_RXFIFO_FULL:
        case DL_I2C_IIDX_CONTROLLER_TXFIFO_EMPTY:
        case DL_I2C_IIDX_CONTROLLER_START:
        case DL_I2C_IIDX_CONTROLLER_STOP:
        case DL_I2C_IIDX_CONTROLLER_EVENT1_DMA_DONE:
        case DL_I2C_IIDX_CONTROLLER_EVENT2_DMA_DONE:
        default:
            break;
    }
}
