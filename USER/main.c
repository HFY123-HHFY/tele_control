#include "Bsp.h"

/*
遥控器
*/

int main(void)               
{
	Bsp_Init();
	
	while (1)
	{		
		//printf("%d\r\n", timer);
		
		LED1 = 1;
		LED2 = 1; 
		
		key_Get();
		rocker_Get(); // 获取摇杆的值

		NRF24L01_Data();

		OLED_Clear();
		OLED_Printf(0,0,OLED_8X16,"T:%d",timer);
		OLED_Printf(52,0,OLED_8X16,"K:%d",Key);
		OLED_Printf(90,0,OLED_8X16,"%d",(L_Z*200)/500); // 油门百分比
		OLED_ShowChar(116,0,'%',OLED_8X16);

		OLED_Printf(0, 16, OLED_8X16, "L:%d", L_Z); // 油门
		OLED_Printf(80, 16, OLED_8X16, "S:%d", (L_Z*200)/250); // 速度

		OLED_Printf(90,48,OLED_8X16,"%d",communication_quality*10); //通信质量
		OLED_ShowChar(116,48,'%',OLED_8X16);

		OLED_Update();

		// OLED_Clear();
		// OLED_Printf(0,0,OLED_8X16,"T:%d",timer);	
		// OLED_Printf(64,0,OLED_8X16,"Key:%d",Key);
		// OLED_Printf(0, 16, OLED_8X16, "LH:%d", L_H);
		// OLED_Printf(64, 16, OLED_8X16, "LZ:%d", L_Z);
		// OLED_Printf(0, 32, OLED_8X16, "RH:%d", R_H);
		// OLED_Printf(64, 32, OLED_8X16, "RZ:%d", R_Z);
		// OLED_Printf(0, 48, OLED_8X16, "%0.1f", percentage);
		// OLED_ShowChar(34,48,'%',OLED_8X16);
		// OLED_Printf(64, 48, OLED_8X16, "%0.1fV", Voltage);
		OLED_Update();
	}
}
