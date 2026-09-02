#include "Bsp.h"

volatile uint32_t timer = 0;

void Bsp_Init(void)
{
	AD_Init();
	Timer_1_Init();
	usart_1_Init(9600);
	
	LED_Init();
	Key_Init();
	NRF24L01_Init(); // 初始化NRF24L01
	OLED_Init();
}
