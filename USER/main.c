#include "Bsp.h"

/*
103_遥控器
*/

int main(void)               
{
	Bsp_Init();
	
	while (1)
	{
		//printf("%d\r\n", timer);
		// LED1 = 1;	LED2 = 1;
		
		if (ADC_Flag == 1)
		{
			ADC_Flag = 0;
			rocker_Get(); // 获取摇杆的值
		}
		
		if (KEY_flag == 1)
		{
			KEY_flag = 0;
			key_Get(); // 获取按键的值
		}

		/* 人机交互: OLED刷新 */
		if(OLED_Flag == 1)
		{
			OLED_Flag = 0;
			OLED_Clear();
			OLED_Printf(0,0,OLED_6X8,"T:%d",timer); //程序运行时间
			OLED_Printf(36,0,OLED_6X8,"K:%d",Key); // 按键状态
			OLED_Printf(64,0,OLED_6X8,"%d",communication_quality*10); //通信质量
			OLED_ShowChar(84,0,'%',OLED_6X8);
			OLED_Printf(100,0,OLED_6X8,"%.0f",L_Z*0.4); // 油门百分比
			OLED_ShowChar(120,0,'%',OLED_6X8);

			OLED_Printf(0,  14, OLED_6X8,  "P%.1f", Pitch); // 俯仰角
			OLED_Printf(46, 14, OLED_6X8, "R%.1f",   Roll); // 横滚角

			OLED_Printf(0, 28, OLED_6X8,  "%d", R_Z); // 右边摇杆纵向
			OLED_Printf(46, 28, OLED_6X8, "%d", R_H); // 右边摇杆横向
			OLED_Update();
		}
	}
}
