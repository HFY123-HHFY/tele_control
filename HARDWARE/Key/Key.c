#include "Key.h"

static uint8_t Key_Num = 0;
uint8_t Key = 0; // 按键状态
uint8_t Mode = 0; // 模式状态,0不回传数据，1回传数据
float Set_Alt = 0.0f; // 按键控制的高度变化 

void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
  	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

uint8_t Key_GetNum(void)
{
	uint8_t Temp;
	if (Key_Num)
	{
		Temp = Key_Num;
		Key_Num = 0;
		return Temp;
	}
	return 0;
}

uint8_t Key_GetState(void)
{
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4) == 0)
	{
		return 1;
	}
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7) == 0)
	{
		return 2;
	}
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5) == 0)
	{
		return 3;
	}
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6) == 0)
	{
		return 4;
	}
	
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5) == 0)
	{
		return 5;
	}
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0)
	{
		return 6;
	}
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6) == 0)
	{
		return 7;
	}
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7) == 0)
	{
		return 8;
	}
	
	return 0;
}

void Key_Tick(void)
{
	static uint8_t Count;
	static uint8_t CurrState, PrevState;
	
	Count ++;
	if (Count >= 20)
	{
		Count = 0;
		
		PrevState = CurrState;
		CurrState = Key_GetState();
		
		if (CurrState == 0 && PrevState != 0)
		{
			Key_Num = PrevState;
		}
	}
}

void key_Get(void)
{
	uint8_t KeyNum = 0;
	
	KeyNum = Key_GetNum();// 获取单次触发的按键值

	if(KeyNum)
	{
		Key = KeyNum; // 记录当前按下的键值
	}

	// 按键5：切换模式
	if (KeyNum == 5)
	{
		Mode = !Mode; // 切换模式
	}

	// 按键6：高度增加 0.1m
	if (KeyNum == 6)
	{
		Set_Alt += 0.1f;
	}
	
	// 按键8：高度减少 0.1m
	if (KeyNum == 8)
	{
		Set_Alt -= 0.1f;
		if (Set_Alt < 0.0f) // 最低高度为0
		{
			Set_Alt = 0.0f;
		}
	}
}
