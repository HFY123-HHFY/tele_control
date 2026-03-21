#include "usart.h"

//加入以下代码,支持printf函数,而不需要选择use MicroLIB
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
}

// 重定向 C 库函数 printf 到串口
int fputc(int ch, FILE *f)
{
    usart_send_byte(USART1, (uint8_t) ch); // 这里假设使用 USART1
    return ch;
}
/*或者：
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
*/
#endif 

// 发送一个字节
void usart_send_byte(USART_TypeDef* USARTx, uint8_t Byte)
{
    USART_SendData(USARTx, Byte);
    while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
}

// 发送一个字符串
void usart_SendString(USART_TypeDef* USARTx, const char *String)
{
    uint8_t i;
    for (i = 0; String[i] != '\0'; i++)
    {
        usart_send_byte(USARTx, String[i]);
    }
}

// 发送一个数字
void usart_send_number(USART_TypeDef* USARTx, uint32_t Number)
{
    char String[10];
    sprintf(String, "%lu", Number);
    usart_SendString(USARTx, String);
}

// 次方函数
uint32_t usart_pow(uint32_t X, uint32_t Y)
{
    uint32_t Result = 1;
    while (Y--)
    {
        Result *= X;
    }
    return Result;
}

// 发送一个数组
void usart_send_array(USART_TypeDef* USARTx, uint8_t *Array, uint16_t Length)
{
    uint16_t i;
    for (i = 0; i < Length; i++)
    {
        usart_send_byte(USARTx, Array[i]);
    }
}

// usart_printf 函数
void usart_printf(USART_TypeDef* USARTx, const char *format, ...)
{
    char String[100];
    va_list arg;
    va_start(arg, format);
    vsprintf(String, format, arg);
    va_end(arg);
    usart_SendString(USARTx, String);
}

USART_DataType USART_DataTypeStruct;

// 数据包解析函数
void usart_Dispose_Data(USART_TypeDef* USARTx, USART_DataType* USART_DataTypeStruct, uint8_t RxData)
{
    switch (USART_DataTypeStruct->state)
    {
        case 0: // 空闲状态,检测针头
            if (RxData == 's')  //针头
            {
                USART_DataTypeStruct->state = 1;       // 进入接收状态
                USART_DataTypeStruct->current_index = 0; // 初始化数据索引
                USART_DataTypeStruct->buffer_len = 0;    // 清空缓冲区
                memset(USART_DataTypeStruct->buffer, 0, sizeof(USART_DataTypeStruct->buffer));//初始化缓冲区
            }
            break;

        case 1: // 接收数据中
            if (RxData == 'e')  //针尾
            {
                // 如果是针尾则处理最后一个数据
                if (USART_DataTypeStruct->buffer_len > 0)//缓冲区有数据
                {
                    // 将接收的数据(字符串)转换为数值
                    uint16_t value = 0;
                    // 遍历缓冲区
                    for (uint8_t i = 0; i < USART_DataTypeStruct->buffer_len; i++) 
                    {
                        if (USART_DataTypeStruct->buffer[i] >= '0' && USART_DataTypeStruct->buffer[i] <= '9') 
                        {
                            value = value * 10 + (USART_DataTypeStruct->buffer[i] - '0');//将字符串转换为数值
                        } 
                        else 
                        {
                            // 无效字符，重置状态
                            USART_DataTypeStruct->state = 0;
                            break;
                        }
                    }
                    if (USART_DataTypeStruct->current_index < Data_len)//最多存储10个数据
                    {
                        USART_DataTypeStruct->data[USART_DataTypeStruct->current_index] = value;//存储数据
                        USART_DataTypeStruct->count = USART_DataTypeStruct->current_index + 1;
                    }
                }
                USART_DataTypeStruct->state = 2; // 标记2,接收完成
            } 
            else if (RxData == ',')  //分隔符","
            {
                // 同理处理当前数据
                if (USART_DataTypeStruct->buffer_len > 0) 
                {
                    uint16_t value = 0;
                    for (uint8_t i = 0; i < USART_DataTypeStruct->buffer_len; i++)
                    {
                        if (USART_DataTypeStruct->buffer[i] >= '0' && USART_DataTypeStruct->buffer[i] <= '9') 
                        {
                            value = value * 10 + (USART_DataTypeStruct->buffer[i] - '0');
                        } 
                        else 
                        {
                            USART_DataTypeStruct->state = 0;
                            break;
                        }
                    }
                    if (USART_DataTypeStruct->current_index < Data_len) 
                    {
                        USART_DataTypeStruct->data[USART_DataTypeStruct->current_index] = value;
                        USART_DataTypeStruct->current_index++;
                    }
                    USART_DataTypeStruct->buffer_len = 0; // 清空缓冲区
                    memset(USART_DataTypeStruct->buffer, 0, sizeof(USART_DataTypeStruct->buffer));//初始化缓冲区
                }
            } 
            else if (RxData >= '0' && RxData <= '9')  // 数字字符
            {
                if (USART_DataTypeStruct->buffer_len < 15)  // 限制最大数据长度
                {
                    USART_DataTypeStruct->buffer[USART_DataTypeStruct->buffer_len++] = RxData;
                } 
                else 
                {
                    USART_DataTypeStruct->state = 0; // 缓冲区溢出，重置状态
                }
            } 
            else 
            {
                USART_DataTypeStruct->state = 0; // 其他无效字符，重置状态
            }
            break;

        case 2: // 接收完成状态
            if (RxData == 's') //针头
            { // 开始新的数据包
                USART_DataTypeStruct->state = 1;
                USART_DataTypeStruct->current_index = 0;
                USART_DataTypeStruct->count = 0;
                USART_DataTypeStruct->buffer_len = 0;
                memset(USART_DataTypeStruct->buffer, 0, sizeof(USART_DataTypeStruct->buffer));
            }
            break;
    }
}

// 获取数据函数
uint16_t USART_Deal(USART_DataType* pData, uint8_t index)
{
    if (pData == NULL || index >= pData->count) 
    {
        return 0; // 返回0表示无效索引
    }
    return pData->data[index];
}


//刷新数据
/*
void usart_refresh(void)
{
    if (USART_DataTypeStruct.state == 2) 
    {
		data1 = USART_Deal(&USART_DataTypeStruct, 0); // 获取第1个数据
		data2 = USART_Deal(&USART_DataTypeStruct, 1); // 获取第2个数据
		data3 = USART_Deal(&USART_DataTypeStruct, 2); // 获取第3个数据
		data4 = USART_Deal(&USART_DataTypeStruct, 3); // 获取第4个数据
		USART_DataTypeStruct.state = 0; // 重置状态以接收新数据
        usart_printf(USART3, "fff\r\n");
    }
}
*/
