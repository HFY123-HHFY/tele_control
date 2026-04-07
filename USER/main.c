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
		
		LED1 = 1;	LED2 = 1;
		
		key_Get();
		rocker_Get(); // 获取摇杆的值
		NRF24L01_TX_Data(); // 发送数据包
		NRF24L01_RX_Data(); // 接收数据包

		OLED_Clear();
		OLED_Printf(0,0,OLED_8X16,"T:%d",timer); //程序运行时间
		OLED_Printf(44,0,OLED_6X8,"K:%d",Key); // 按键状态
		OLED_Printf(64, 0, OLED_6X8, "M:%d", Mode); // 模式
		OLED_Printf(90,0,OLED_8X16,"%.0f",L_Z*0.4); // 油门百分比
		OLED_ShowChar(120,0,'%',OLED_8X16);

		OLED_Printf(94,54,OLED_6X8,"%d",communication_quality*10); //通信质量
		OLED_ShowChar(114,54,'%',OLED_6X8);

		OLED_Printf(0, 16, OLED_6X8, "P%.1f", Pitch); // 俯仰角
		OLED_Printf(46, 16, OLED_6X8, "R%.1f", Roll); // 横滚角
		OLED_Printf(88, 16, OLED_6X8, "Y%.1f", Yaw); // 偏航角

		OLED_Printf(0, 32, OLED_6X8, "P_O:%.1f", pid_pitch_output); // 俯仰角PID输出
		OLED_Printf(64, 32, OLED_6X8, "R_O:%.1f", pid_roll_output); // 横滚角PID输出

		OLED_Printf(54, 54, OLED_6X8, "%d", speed_temp); // 回传的速度

		OLED_Update();
	}
}
