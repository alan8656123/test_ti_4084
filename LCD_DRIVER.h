
#ifndef I2C_MODULE_H_
#define I2C_MODULE_H_

/* Maximum size of TX packet */

/* Number of bytes to send to target device */

/* Maximum size of RX packet */
#define I2C_RX_MAX_PACKET_SIZE (16)
/* Number of bytes to received from target */
#define I2C_RX_PACKET_SIZE (16)
/* I2C Target address */
#define I2C_TARGET_ADDRESS (0x38)


/* Data sent to the Target */
uint8_t gTxPacket[64] ;


/* Counters for TX length and bytes sent */
volatile uint32_t gTxLen, gTxCount;

/* Data received from Target */
uint8_t gRxPacket[I2C_RX_MAX_PACKET_SIZE];
/* Counters for TX length and bytes sent */
uint32_t gRxLen, gRxCount;
/* Indicates status of I2C */
volatile static enum I2cControllerStatus {
    I2C_STATUS_IDLE = 0,
    I2C_STATUS_TX_STARTED,
    I2C_STATUS_TX_INPROGRESS,
    I2C_STATUS_TX_COMPLETE,
    I2C_STATUS_RX_STARTED,
    I2C_STATUS_RX_INPROGRESS,
    I2C_STATUS_RX_COMPLETE,
    I2C_STATUS_ERROR,
} gI2cControllerStatus;





void send(uint32_t I2C_TX_packet_size);
void I2C_INST_IRQHandler(void);

#endif