#ifndef __NRF24L01_H
#define __NRF24L01_H

#include "stm32f10x.h"
#include "NRF24L01_Define.h"
#include "usart_1.h"
#include "OLED.h"
#include "Key.h"
#include "AD.h"

/*外部可调用全局数组***********/

extern uint8_t NRF24L01_TxAddress[];
extern uint8_t NRF24L01_TxPacket[];

extern uint8_t NRF24L01_RxAddress[];
extern uint8_t NRF24L01_RxPacket[];

extern uint8_t NRF24L01_Flag;								//NRF24L01通信标志位
extern uint8_t SendFlag;								//发送标志位
extern uint8_t ReceiveFlag;							//接收标志位
extern uint8_t communication_quality;					//通信质量
extern float Pitch, Roll, Yaw, pid_pitch_output, pid_roll_output; // 接收的姿态角和PID输出
extern uint16_t speed_temp;
/***********外部可调用全局数组*/


/*函数声明*********************/

/*指令实现*/
uint8_t NRF24L01_ReadReg(uint8_t RegAddress);
void NRF24L01_ReadRegs(uint8_t RegAddress, uint8_t *DataArray, uint8_t Count);
void NRF24L01_WriteReg(uint8_t RegAddress, uint8_t Data);
void NRF24L01_WriteRegs(uint8_t RegAddress, uint8_t *DataArray, uint8_t Count);
void NRF24L01_ReadRxPayload(uint8_t *DataArray, uint8_t Count);
void NRF24L01_WriteTxPayload(uint8_t *DataArray, uint8_t Count);
void NRF24L01_FlushTx(void);
void NRF24L01_FlushRx(void);
uint8_t NRF24L01_ReadStatus(void);

/*功能函数*/
void NRF24L01_PowerDown(void);
void NRF24L01_StandbyI(void);
void NRF24L01_Rx(void);
void NRF24L01_Tx(void);

void NRF24L01_Init(void);
uint8_t NRF24L01_Send(void);
uint8_t NRF24L01_Receive(void);
void NRF24L01_UpdateRxAddress(void);

void NRF24L01_TX_Data(void);
void NRF24L01_RX_Data(void);

/*********************函数声明*/


#endif
