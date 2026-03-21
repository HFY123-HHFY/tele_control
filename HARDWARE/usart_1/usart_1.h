#ifndef __USART_1_H
#define __USART_1_H

#include "stm32f10x.h"
#include "Led.h"

void usart_1_Init(u32 bound_1);

extern uint16_t USART1_Data;

#endif
