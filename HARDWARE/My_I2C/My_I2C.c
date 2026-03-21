#include "My_I2C.h"

/* 引脚操作层 */
void MyI2C_W_SCL(uint8_t BitValue) // 写SCL
{
    GPIO_WriteBit(My_I2C_PORT, My_I2C_SCL, (BitAction)BitValue);
    delay_us(5);
}

void MyI2C_W_SDA(uint8_t BitValue) // 写SDA
{
    GPIO_WriteBit(My_I2C_PORT, My_I2C_SDA, (BitAction)BitValue);
    delay_us(5);
}

uint8_t MyI2C_R_SDA(void) // 读SDA
{
    delay_us(5);
    return GPIO_ReadInputDataBit(My_I2C_PORT, My_I2C_SDA);
}

//SDA输出模式控制
void MyI2C_Set_SDA_Output(void)//SDA输出方向配置
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	
	GPIO_InitStructure.GPIO_Pin=My_I2C_SDA;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//SDA推挽输出
	GPIO_Init(My_I2C_PORT,&GPIO_InitStructure); 						
}

void MyI2C_Set_SDA_Input(void)//SDA输入方向配置
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	
	GPIO_InitStructure.GPIO_Pin=My_I2C_SDA;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//SDA上拉输入
	GPIO_Init(My_I2C_PORT,&GPIO_InitStructure);
}

/* 初始化层 */
void MyI2C_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // 开启GPIOB时钟

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; // 开漏输出
    GPIO_InitStructure.GPIO_Pin = My_I2C_SCL | My_I2C_SDA;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(My_I2C_PORT, &GPIO_InitStructure);

    MyI2C_W_SCL(1);
    MyI2C_W_SDA(1);
}

/* 协议层 */
void MyI2C_Start(void) // I2C起始
{
		MyI2C_Set_SDA_Output();
    MyI2C_W_SDA(1);
    MyI2C_W_SCL(1);
    delay_us(4);
    MyI2C_W_SDA(0);
    delay_us(4);
    MyI2C_W_SCL(0);
}

void MyI2C_Stop(void) // I2C停止
{
		MyI2C_Set_SDA_Output();
		MyI2C_W_SCL(0);
		MyI2C_W_SDA(0);// STOP: 当SCL为高时，SDA从低变高
		delay_us(4);
		MyI2C_W_SCL(1);
		MyI2C_W_SDA(1);
		delay_us(4);
}

void MyI2C_SendByte(uint8_t Byte) // I2C发送一个字节
{
		MyI2C_Set_SDA_Output();
    for (uint8_t i = 0; i < 8; i++)
    {
        MyI2C_W_SDA((Byte & 0x80) >> 7);
        Byte <<= 1;
        delay_us(2);
        MyI2C_W_SCL(1);
        delay_us(2);
        MyI2C_W_SCL(0);
        delay_us(2);
    }
}


/***********************************************************
*	I2C 写一个字节
*	Ack : 1 发送ACK 0 发送NACK
*	返回    : 接收到的字节
***********************************************************/
uint8_t MyI2C_Receive_Byte(unsigned char Ack) // I2C接收一个字节
{
    unsigned char i, Byte = 0;
    MyI2C_Set_SDA_Input();
    for (i = 0; i < 8; i++)
    {
        MyI2C_W_SCL(0);
        delay_us(2);
        MyI2C_W_SCL(1);
        Byte <<= 1;
        if (MyI2C_R_SDA())
        {
            Byte++;
        }
        delay_us(1);
    }
    if (Ack)
    {
        MyI2C_Ack();
    }
    else
    {
        MyI2C_NAck();
    }
    return Byte;
}

void MyI2C_Ack(void) // 发送ACK应答
{
		MyI2C_W_SCL(0);
    MyI2C_Set_SDA_Output();
    MyI2C_W_SDA(0);
    delay_us(2);
    MyI2C_W_SCL(1);
    delay_us(2);
    MyI2C_W_SCL(0);
}

void MyI2C_NAck(void) // 发送NACK应答
{
		MyI2C_W_SCL(0);
    MyI2C_Set_SDA_Output();
    MyI2C_W_SDA(1);
    delay_us(2);
    MyI2C_W_SCL(1);
    delay_us(2);
    MyI2C_W_SCL(0);
}

uint8_t MyI2C_ReceiveAck(void) // 接收应答(0=应答 1=非应答)
{
	  uint8_t ErrTime = 0;
    MyI2C_Set_SDA_Input();
    MyI2C_W_SDA(1);
    delay_us(1);
    MyI2C_W_SCL(1);
    delay_us(1);
    while (MyI2C_R_SDA())
    {
        ErrTime++;
        if (ErrTime > 250)
        {
            MyI2C_Stop();
            return 1; // 超时未响应
        }
    }
    MyI2C_W_SCL(0);
    return 0; // 应答成功
}

/* 通用读写函数 */
/**
  * 函    数：MyI2C_Write
  * 描    述：向指定设备写入数据
  * 参    数：DevAddress 设备地址
  *          RegAddress 寄存器地址
  *          Data 要写入的数据
  *          Length 数据长度
  * 返 回 值：0 表示成功，1 表示失败
  */
uint8_t MyI2C_Write(uint8_t DevAddress, uint8_t RegAddress, uint8_t *Data, uint16_t Length)
{
    MyI2C_Start();
    MyI2C_SendByte(DevAddress & 0xFE); // 写操作
    if (MyI2C_ReceiveAck())
    {
        MyI2C_Stop();
        return 1; // 设备未响应
    }

    MyI2C_SendByte(RegAddress);
    if (MyI2C_ReceiveAck())
    {
        MyI2C_Stop();
        return 1; // 寄存器地址未响应
    }

    for (uint16_t i = 0; i < Length; i++)
    {
        MyI2C_SendByte(Data[i]);
        if (MyI2C_ReceiveAck())
        {
            MyI2C_Stop();
            return 1; // 数据未响应
        }
    }

    MyI2C_Stop();
    return 0; // 成功
}

/**
  * 函    数：MyI2C_Read
  * 描    述：从指定设备读取数据
  * 参    数：DevAddress 设备地址
  *          RegAddress 寄存器地址
  *          Data 存储读取数据的缓冲区
  *          Length 数据长度
  * 返 回 值：0 表示成功，1 表示失败
  */
uint8_t MyI2C_Read(uint8_t DevAddress, uint8_t RegAddress, uint8_t *Data, uint16_t Length)
{
    MyI2C_Start();
    MyI2C_SendByte(DevAddress & 0xFE); // 写操作
    if (MyI2C_ReceiveAck())
    {
        MyI2C_Stop();
        return 1; // 设备未响应
    }

    MyI2C_SendByte(RegAddress);
    if (MyI2C_ReceiveAck())
    {
        MyI2C_Stop();
        return 1; // 寄存器地址未响应
    }

    MyI2C_Start();
    MyI2C_SendByte(DevAddress | 0x01); // 读操作
    if (MyI2C_ReceiveAck())
    {
        MyI2C_Stop();
        return 1; // 设备未响应
    }

    for (uint16_t i = 0; i < Length; i++)
    {
        Data[i] = MyI2C_Receive_Byte(0);
        if (i < Length - 1)
        {
            MyI2C_Ack(); // 继续读取
        }
        else
        {
            MyI2C_NAck(); // 最后一个字节发送NACK
        }
    }
    MyI2C_Stop();
    return 0; // 成功
}
