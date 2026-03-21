#include "Control_task.h"

void TIM1_UP_IRQHandler(void)
{
	static uint16_t time = 0, Count0 = 0;

	if (TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)
	{
		Key_Tick();
		
		Count0++;
		time++;

		if (Count0 >= 100)
		{
			Count0 = 0;
			NRF24L01_Flag = 1;		//100ms到达，置NRF24L01通信标志位为1
		}

		if (time >= 1000)
		{
			timer++;
			time = 0;
		}
	}
	TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
}
