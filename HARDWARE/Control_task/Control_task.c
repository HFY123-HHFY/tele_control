#include "Control_task.h"

volatile uint8_t ADC_Flag = 0U; /* ADC标志位 */
volatile uint8_t KEY_flag = 0U; /* 按键标志位 */
volatile uint8_t NRF_Flag = 0U; /* NRF24L01收发任务标志位 */
volatile uint8_t OLED_Flag = 0U; /* OLED刷新标志位 */

/* TIM1 中断服务函数
 * 说明：这里仅保留“时间基准”和“标志位触发”，不在中断里直接执行
 *        NRF24L01 收发、ADC 采样、OLED 刷新等较重的任务，避免中断执行时间太长。
 */
void TIM1_UP_IRQHandler(void)
{
	static uint8_t adc_tick = 0; /* ADC计数 */
	static uint8_t key_tick = 0; /* 按键计数 */
	static uint8_t nrf_tick = 0; /* NRF24L01任务计数 */
	static uint8_t oled_tick = 0; /* OLED刷新计数 */
	static uint16_t time_tick = 0; /* 时间计数 */

	if (TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)
	{
		Key_Tick(); /* 按键扫描：适合放在中断里做消抖 */
		adc_tick++;
		key_tick++;
		nrf_tick++;
		oled_tick++;
		time_tick++;

		/* ADC摇杆：10ms一次触发主循环采样 */
		if (adc_tick >= 10)
		{
			adc_tick = 0;
			ADC_Flag = 1;
		}

		/* 按键：10ms一次触发主循环读取 */
		if (key_tick >= 10)
		{
			key_tick = 0;
			KEY_flag = 1;
		}

		/* NRF24L01任务：10ms一次只触发主循环执行收发 */
		if (nrf_tick >= 10)
		{
			nrf_tick = 0;
			NRF_Flag = 1;
		}

		/* OLED刷新50ms：触发主循环刷新 */
		if (oled_tick >= 50)
		{
			oled_tick = 0;
			OLED_Flag = 1;
		}

		/* 时间计数1000ms */
		if (time_tick >= 1000)
		{
			time_tick = 0;
			timer++;
		}
	}
	TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
}
