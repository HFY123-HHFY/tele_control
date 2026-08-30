#ifndef __CONTROL_TASK_H
#define __CONTROL_TASK_H

#include "Bsp.h"

extern volatile uint8_t ADC_Flag; /* ADC标志位 */
extern volatile uint8_t KEY_flag; /* 按键标志位 */
extern volatile uint8_t NRF_Flag; /* NRF24L01收发任务标志位 */
extern volatile uint8_t OLED_Flag; /* OLED刷新标志位 */

#endif
