#include "pwm.h"

//统一PWM初始化函数
void PWM_Iint(void)
{
	PWM_2_Init();	//初始化TIM2
	PWM_3_Init();	//初始化TIM3
	PWM_4_Init();	//初始化TIM4
}

/*
PWM2-TIM2
ch1-PA0-舵机5-尾巴
ch2-PA1-蜂鸣器
ch3-PA2-LED4
ch4-PA3-LED2
*/
void PWM_2_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	//开启TIM2时钟
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//开启GPIOA时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			//复用推挽输出模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;	//TIM2 4个CH通道
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM2);//TIM2切换为内部定时器
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//不分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 20000-1;//设置自动重装载寄存器的值，ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72-1;//设置预分频寄存器的值，PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//输出比较模式采用PWM1
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;//初始化CCR的值为0
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);//TIM2复用通道1开启
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);//TIM2复用通道2开启
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);//TIM2复用通道3开启
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);//TIM2复用通道4开启
	
	TIM_Cmd(TIM2,ENABLE);//使能TIM2
}

/*
PWM3-TIM3
舵机
*/
void PWM_3_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//开启TIM3时钟
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//开启GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//开启GPIOB时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			//复用推挽输出模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;	//TIM3 CH1/CH2
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			//复用推挽输出模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;	//TIM3 CH3/CH4
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM3);//TIM3切换为内部定时器
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//不分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 20000-1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72-1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//输出比较模式采用PWM1
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;//初始化CCR的值为0
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);//TIM3复用通道1开启
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);//TIM3复用通道2开启
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);//TIM3复用通道3开启
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);//TIM3复用通道4开启
	
	TIM_Cmd(TIM3,ENABLE);//使能TIM3
}

/*
PWM4-TIM4
ch3-PB8-LED3
ch4-PB9-LED1
*/
void PWM_4_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//开启TIM4时钟
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//开启GPIOB时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			//复用推挽输出模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;	//TIM4 2个CH通道
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM4);//TIM4切换为内部定时器
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//不分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 20000-1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72-1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//输出比较模式采用PWM1
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;//初始化CCR的值为0
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);//TIM4复用通道3开启
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);//TIM4复用通道4开启
	
	TIM_Cmd(TIM4,ENABLE);//使能TIM4
}

//tim2-ch2-蜂鸣器
void PWM_Buzz_Control(uint16_t Compare)
{	
	TIM_SetCompare2(TIM2, Compare);//设置CCR2的值
}

//tim4-ch4-LED1
void PWM_LED1_Control(uint16_t Compare)
{
	TIM_SetCompare4(TIM4, Compare);//设置CCR4的值
}

//tim2-ch4-LED2
void PWM_LED2_Control(uint16_t Compare)
{	
	TIM_SetCompare4(TIM2, Compare);//设置CCR4的值
}

//tim4-ch3-LED3
void PWM_LED3_Control(uint16_t Compare)
{
	TIM_SetCompare3(TIM4, Compare);//设置CCR3的值
}

//tim2-ch3-LED4
void PWM_LED4_Control(uint16_t Compare)
{	
	TIM_SetCompare3(TIM2, Compare);//设置CCR3的值
}

//tim3-ch3-舵机1
void PWM_1_Control(uint16_t Compare)
{
	TIM_SetCompare3(TIM3, Compare);//设置CCR3的值
}

//tim3-ch4-舵机2
void PWM_2_Control(uint16_t Compare)
{
	TIM_SetCompare4(TIM3, Compare);//设置CCR4的值
}

//tim3-ch1-舵机3
void PWM_3_Control(uint16_t Compare)
{
	TIM_SetCompare1(TIM3, Compare);//设置CCR1的值
}

//tim3-ch2-舵机4
void PWM_4_Control(uint16_t Compare)
{
	TIM_SetCompare2(TIM3, Compare);//设置CCR2的值
}

//tim2-ch1-舵机5-尾巴
void PWM_5_Control(uint16_t Compare)
{
	TIM_SetCompare1(TIM2, Compare);//设置CCR1的值		
}

/*
TIM_SetCompare1(TIM3, Compare); //设置CCR的值
TIM_PrescalerConfig(TIM3, Prescaler, TIM_PSCReloadMode_Immediate); //设置PSC的值

占空比Duty = CCR / (ARR + 1)
频率Freq = CK_PSC / (PSC + 1) / (ARR + 1)
*/
