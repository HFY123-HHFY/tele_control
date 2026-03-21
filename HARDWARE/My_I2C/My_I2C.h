#ifndef __MY_I2C_H
#define __MY_I2C_H

#include "stm32f10x.h"
#include "Delay.h"

/* I2C引脚定义 */
#define My_I2C_PORT GPIOB
#define My_I2C_SCL GPIO_Pin_10
#define My_I2C_SDA GPIO_Pin_11

/* 引脚操作层函数声明 */
void MyI2C_W_SCL(uint8_t BitValue); // 写SCL
void MyI2C_W_SDA(uint8_t BitValue); // 写SDA
uint8_t MyI2C_R_SDA(void); // 读SDA

void MyI2C_Set_SDA_Input(void); // 设置SDA为输入模式
void MyI2C_Set_SDA_Output(void); // 设置SDA为输出模式

/* 函数声明 */
void MyI2C_Init(void);
void MyI2C_Start(void); // I2C起始
void MyI2C_Stop(void); // I2C停止
void MyI2C_SendByte(uint8_t Byte); // I2C发送一个字节
uint8_t MyI2C_Receive_Byte(unsigned char Ack); // I2C接收一个字节
void MyI2C_Ack(void); // 发送ACK应答
void MyI2C_NAck(void); // 发送NACK应答

uint8_t MyI2C_ReceiveAck(void); // 接收应答或非应答

// 向指定设备写入数据
uint8_t MyI2C_Write(uint8_t DevAddress, uint8_t RegAddress, uint8_t *Data, uint16_t Length);

// 从指定设备读取数据
uint8_t MyI2C_Read(uint8_t DevAddress, uint8_t RegAddress, uint8_t *Data, uint16_t Length);

#endif
