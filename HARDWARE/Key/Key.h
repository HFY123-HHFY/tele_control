#ifndef __KEY_H
#define __KEY_H

#include "sys.h"
#include "OLED.h"

#define KEY1 PAout(5)
#define KEY2 PBout(0)
#define KEY3 PAout(6)
#define KEY4 PAout(7)

#define KEY5 PBout(7)
#define KEY6 PBout(4)
#define KEY7 PBout(6)
#define KEY8 PBout(5)

void Key_Init(void);
void Key_Tick(void);
void key_Get(void);

extern uint8_t Key;
extern uint8_t Mode;


#endif
