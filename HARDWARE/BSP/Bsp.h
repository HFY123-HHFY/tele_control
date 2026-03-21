#ifndef __BSP_H
#define __BSP_H

#include "Timer_1.h"
#include "usart.h"
#include "Delay.h"

#include "usart_1.h"
#include "AD.h"
#include "Control_task.h"

#include "lED.h"
#include "Key.h"
#include "OLED.h"
#include "NRF24L01.h" 

void Bsp_Init(void);

extern uint32_t timer;

#endif
