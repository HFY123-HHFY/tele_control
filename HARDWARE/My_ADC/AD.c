#include "AD.h"

// OLED_Printf(0, 48, OLED_8X16, "%0.1f", percentage);
// OLED_ShowChar(34,48,'%',OLED_8X16);
// OLED_Printf(64, 48, OLED_8X16, "%0.1fV", Voltage);

int8_t L_H = 0, R_H = 0 ,R_Z = 0; // 摇杆
uint8_t L_Z = 0; // 摇杆Z轴，油门
float percentage = 0, Voltage = 0;		//百分比，电压

void AD_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
		
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_Init(ADC1, &ADC_InitStructure);
	
	ADC_Cmd(ADC1, ENABLE);
	
	ADC_ResetCalibration(ADC1);
	while (ADC_GetResetCalibrationStatus(ADC1) == SET);
	ADC_StartCalibration(ADC1);
	while (ADC_GetCalibrationStatus(ADC1) == SET);
}

uint16_t AD_GetValue(uint8_t ADC_Channel)
{
	ADC_RegularChannelConfig(ADC1, ADC_Channel, 1, ADC_SampleTime_55Cycles5);
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
	return ADC_GetConversionValue(ADC1);
}

int8_t DataProcess(uint16_t ADValue)
{
	int16_t Value;
	
	Value = ADValue - 2048;
	
	//-2048 ~ 2047
	
	if (Value > 100)
	{
		Value -= 100;
	}
	else if (Value < -100)
	{
		Value += 100;
	}
	else
	{
		Value = 0;
	}
	
	//-1948 ~ 1947
	
	Value = Value * 101 / 1949;
	
	//-100 ~ 100
	
	return Value;
}

uint8_t DataProcess_2(uint16_t ADValue)
{
	int16_t Value;
	
	Value = ADValue - 2048;
	
	//-2048 ~ 2047
	
	if (Value > 100)
	{
		Value -= 100;
	}
	else if (Value < -100)
	{
		Value += 100;
	}
	else
	{
		Value = 0;
	}
	
	//-1948 ~ 1947
	
	Value = Value * 126 / 1949;
	
	//-125 ~ 125
	
	return Value + 125;
}

uint8_t CalculateSuccessRatio(uint8_t SendFlag)
{
	static uint8_t SendFlagArray[10];
	static uint8_t p;
	uint8_t i, SuccessCount;
	
	SendFlagArray[p] = SendFlag;
	p ++;
	p %= 10;
	
	SuccessCount = 0;
	for (i = 0; i < 10; i ++)
	{
		if (SendFlagArray[i] == 1)
		{
			SuccessCount ++;
		}
	}
	
	return SuccessCount;
}

//获取摇杆的值
//范围：-100 ~ +100
void rocker_Get(void)	
{
	uint16_t L_ADC0 = 0; // 油门
	uint16_t L_ADC1 = 0, R_ADC4 = 0, R_ADC3 = 0, ADValue = 0;

	L_ADC0 = AD_GetValue(ADC_Channel_0); // 获取油门ADC
	L_ADC1 = AD_GetValue(ADC_Channel_1);
	R_ADC4 = AD_GetValue(ADC_Channel_4);
	R_ADC3 = AD_GetValue(ADC_Channel_3);
	ADValue = AD_GetValue(ADC_Channel_2); // 获取电压ADC
	
	L_Z = DataProcess_2(L_ADC0); // 油门 范围0-250
	L_H = -DataProcess(L_ADC1);
	R_H = -DataProcess(R_ADC3);
	R_Z	= DataProcess(R_ADC4);
	Voltage = (float)ADValue / 4095 * 3.3;		//获取电压
	percentage = (Voltage - 1.65) * 222.22;   //获取百分比
}
