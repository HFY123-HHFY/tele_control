#include "Control_task.h"

volatile uint8_t ADC_Flag = 0U; /* ADC标志位 */
volatile uint8_t KEY_flag = 0U; /* 按键标志位 */
volatile uint8_t OLED_Flag = 0U; /* OLED刷新标志位 */

/* TIM1 中断服务函数*/
void TIM1_UP_IRQHandler(void)
{
	static uint8_t adc_tick = 0; /* ADC计数 */
	static uint8_t key_tick = 0; /* 按键计数 */
	static uint8_t nrf_tick = 0; /* NRF24L01发送计数 */
	static uint8_t oled_tick = 0; /* OLED刷新计数 */
	static uint16_t time_tick = 0; /* 时间计数 */

	if (TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)
	{
		Key_Tick(); /* 按键扫描 */
		adc_tick++;
		key_tick++;
		nrf_tick++;
		oled_tick++;
		time_tick++;

		/* ADC摇杆 */
		if (adc_tick >= 10)
		{
			adc_tick = 0;
			ADC_Flag = 1;			//置ADC标志位为1
		}

		/* 按键 */
		if (key_tick >= 10)
		{
			key_tick = 0;
			KEY_flag = 1;			//置按键标志位为1
		}

		/* NRF24L01发送 */
		if (nrf_tick >= 10)
		{
			nrf_tick = 0;
			NRF24L01_TX_Data(); // 发送数据包
			NRF24L01_RX_Data(); // 接收数据包
		}

		/* OLED刷新50ms */
		if (oled_tick >= 50)
		{
			oled_tick = 0;
			OLED_Flag = 1;			//置OLED刷新标志位为1
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
