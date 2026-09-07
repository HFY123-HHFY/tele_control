#include "Bsp.h"

/*
103_遥控器
*/

int main(void)               
{
	Bsp_Init();
	
	while (1)
	{
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

		if (NRF_Flag == 1)
		{
			NRF_Flag = 0;
			NRF24L01_TX_Data(); // 发送数据包
			NRF24L01_RX_Data(); // 接收数据包
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

			OLED_Printf(0,  14, OLED_6X8, "P%.1f", Pitch); // 俯仰角
			OLED_Printf(46, 14, OLED_6X8, "R%.1f", Roll); // 横滚角

			OLED_Printf(0,  28, OLED_6X8, "H:%.2f", (double)((float)Height/ 1000.0f)); // 高度值
			OLED_Printf(46, 28, OLED_6X8, "X:%d", OpticalFlow_X); // 光流数据
			OLED_Printf(92, 28, OLED_6X8, "Y:%d", OpticalFlow_Y); // 光流数据

			OLED_Printf(0, 42, OLED_6X8, "HO:%d", L_H);
			OLED_Printf(46, 42, OLED_6X8, "X:%d", R_H);
			OLED_Printf(92, 42, OLED_6X8, "Y:%d", R_Z);

			OLED_Printf(0,  56, OLED_6X8, "A%d,P%d", Alt_Active,Pos_Active); /* 定高环, 定点环 */
			OLED_Printf(46, 56, OLED_6X8, "FQ:%d", flow_quality); /* 光流质量 */
			OLED_Printf(92,  56, OLED_6X8, "T%d,F%d", tof_status,flow_status); /* 测距数据是否可用，光流数据是否可用 */

			OLED_Update();
		}
	}
}
