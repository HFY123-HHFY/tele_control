#ifndef __CONTROL_H
#define __CONTROL_H

#include "stm32f10x.h"
#include "Led.h"
#include "Delay.h"
#include "pwm.h"
#include "Servo.h"
#include "Face.h"

void Servo_Swing(uint8_t i , uint16_t angle , uint16_t j); // 摇摆函数

void Servo_Swing_Tail(void); // 摇尾巴
void Servo_stand(void); // 站立
void Servo_sleep(void); // 睡觉
void Servo_go_prone(void); // 趴下
void Servo_sit_down(void); // 蹲下
void Servo_hello(void); // 打招呼
void Servo_stretch(void); // 升懒腰
void Servo_forward(void); // 前进
void Servo_backward(void); // 后退
void Servo_swing_1(void); // 摇摆函数
void Servo_turn_left(void); // 左转
void Servo_turn_right(void); // 右转
void Servo_handshake(void);//握手
void Servo_run(void); //跑步
void Servo_perform(void); //表演 

#endif
