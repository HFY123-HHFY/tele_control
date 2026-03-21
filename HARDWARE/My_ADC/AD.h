#ifndef __AD_H
#define __AD_H

#include "stm32f10x.h"

void AD_Init(void);
uint16_t AD_GetValue(uint8_t ADC_Channel);
uint8_t CalculateSuccessRatio(uint8_t SendFlag);

extern int8_t L_H, R_H, R_Z; // 摇杆
extern uint8_t L_Z; // 摇杆Z轴，油门
extern float percentage, Voltage;
void rocker_Get(void);

#endif
