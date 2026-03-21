#ifndef  _PWM_H
#define  _PWM_H

#include "stm32f10x.h"

void PWM_Iint(void);

void PWM_2_Init(void);
void PWM_3_Init(void);
void PWM_4_Init(void);

void PWM_1_Control(uint16_t Compare);//舵机1
void PWM_2_Control(uint16_t Compare);//舵机2
void PWM_3_Control(uint16_t Compare);//舵机3
void PWM_4_Control(uint16_t Compare);//舵机4
void PWM_5_Control(uint16_t Compare);//舵机5-尾巴

void PWM_Buzz_Control(uint16_t Compare);//蜂鸣器
void PWM_LED1_Control(uint16_t Compare);//LED1
void PWM_LED2_Control(uint16_t Compare);//LED2
void PWM_LED3_Control(uint16_t Compare);//LED3
void PWM_LED4_Control(uint16_t Compare);//LED4

#endif
