#include "Control.h"

/*
PWM3-TIM3
ch1-PA6-舵机1-前左
ch2-PA7-舵机2-前右             PWM2-TIM2
ch3-PB0-舵机3-后左          ch1-PA0-舵机5-尾巴
ch4-PB1-舵机4-后右

舵机方位
	
		1	2
正面			5
		3	4
*/

/*
摇摆函数
    入口参数：
    i: 舵机编号
    angle: 摇摆的最大角度
    j: 摇摆次数
*/

//前进延时
#define Delay_temp 220

void Servo_Swing(uint8_t i , uint16_t angle , uint16_t j) 
{
    uint16_t position = 0;  // 舵机初始角度
    uint8_t direction = 1;    // 方向标志，1 表示增加角度，0 表示减少角度
    uint8_t swing_count = 0;  // 摇摆计数

    while (swing_count < j) // 摇摆 2 次
    {
        Servo_SetAngle(i, position); // 设置舵机5（尾巴）的角度

        Delay_ms(10);

        if (direction)
        {
            position += 2; // 增加位置
            if (position >= angle) // 到达最大位置（最大脉宽）
            {
                position = angle;
                direction = 0; // 改变方向
                swing_count++; // 完成一次摇摆
            }
        }
        else
        {
            position -= 2; // 减少位置
            if (position <= 0) // 到达最小位置（最小脉宽）
            {
                position = 0;
                direction = 1; // 改变方向
                swing_count++; // 完成一次摇摆
            }
        }
    }
    // 停止舵机
    Servo_SetAngle(i, 0);
}

//摇尾巴
void Servo_Swing_Tail(void)
{
    Face_Mania(); // 狂热表情    

    Servo_Swing(5, 170, 4); // 摆尾巴
}

// 前进
void Servo_forward(void)
{
    Servo_stand(); // 站立
    Face_VeryHappy(); // 非常快乐表情
    Delay_ms(Delay_temp);
 
    for ( uint8_t i = 0; i < 3; i++)
    {
        //左脚出发：
        Servo_SetAngle(1, 135);
        Servo_SetAngle(4, 45);
        Delay_ms(Delay_temp);
        Servo_SetAngle(3, 135);
        Servo_SetAngle(2, 45);
        Delay_ms(Delay_temp);
        Servo_SetAngle(1, 90);
        Servo_SetAngle(4, 90);
        Delay_ms(Delay_temp);
        Servo_SetAngle(3, 90);
        Servo_SetAngle(2, 90);
        Delay_ms(Delay_temp);

        //右脚出发：
        Servo_SetAngle(3, 45);
        Servo_SetAngle(2, 135);
        Delay_ms(Delay_temp);
        Servo_SetAngle(1, 45);
        Servo_SetAngle(4, 135);
        Delay_ms(Delay_temp);
        Servo_SetAngle(3, 90);
        Servo_SetAngle(2, 90);
        Delay_ms(Delay_temp);
        Servo_SetAngle(1, 90);
        Servo_SetAngle(4, 90);
        Delay_ms(Delay_temp);
    }
    Servo_Swing(5, 170, 2);// 摆尾巴
}

//后退
void Servo_backward(void)
{
    Servo_stand(); // 站立
    Face_VeryHappy(); // 非常快乐表情
    Delay_ms(Delay_temp);
 
    for ( uint8_t i = 0; i < 3; i++)
    {
        //左脚出发：
        Servo_SetAngle(1, 45);
        Servo_SetAngle(4, 135);
        Delay_ms(Delay_temp);
        Servo_SetAngle(3, 45);
        Servo_SetAngle(2, 135);
        Delay_ms(Delay_temp);
        Servo_SetAngle(1, 90);
        Servo_SetAngle(4, 90);
        Delay_ms(Delay_temp);
        Servo_SetAngle(3, 90);
        Servo_SetAngle(2, 90);
        Delay_ms(Delay_temp);

        //右脚出发：
        Servo_SetAngle(3, 135);
        Servo_SetAngle(2, 45);
        Delay_ms(Delay_temp);
        Servo_SetAngle(1, 135);
        Servo_SetAngle(4, 45);
        Delay_ms(Delay_temp);
        Servo_SetAngle(3, 90);
        Servo_SetAngle(2, 90);
        Delay_ms(Delay_temp);
        Servo_SetAngle(1, 90);
        Servo_SetAngle(4, 90);
        Delay_ms(Delay_temp);
    }
    Servo_Swing(5, 170, 2);// 摆尾巴
}

//左转
void Servo_turn_right(void)
{
    Servo_stand(); // 站立
    Delay_ms(Delay_temp);
    Face_VeryHappy(); // 非常快乐表情
    
    for (uint8_t i = 0; i < 3; i++)
    {
        Servo_SetAngle(3, 135);
        Servo_SetAngle(2, 135);
        Delay_ms(Delay_temp);
        Servo_SetAngle(1, 45);
        Servo_SetAngle(4, 45);
        Delay_ms(Delay_temp);
        Servo_SetAngle(3, 90);
        Servo_SetAngle(2, 90);
        Delay_ms(Delay_temp);
        Servo_SetAngle(1, 90);
        Servo_SetAngle(4, 90);
        Delay_ms(Delay_temp);
    }
    Servo_Swing(5, 170, 2);// 摆尾巴
}

//右转
void Servo_turn_left(void)
{
    Servo_stand(); // 站立
    Delay_ms(Delay_temp);
    Face_VeryHappy(); // 非常快乐表情
    
    for (uint8_t i = 0; i < 3; i++)
    {
        Servo_SetAngle(1, 45);
        Servo_SetAngle(4, 45);
        Delay_ms(Delay_temp);
        Servo_SetAngle(3, 135);
        Servo_SetAngle(2, 135);
        Delay_ms(Delay_temp);
        Servo_SetAngle(1, 90);
        Servo_SetAngle(4, 90);
        Delay_ms(Delay_temp);
        Servo_SetAngle(3, 90);
        Servo_SetAngle(2, 90);
        Delay_ms(Delay_temp);
    }
    Servo_Swing(5, 170, 2);// 摆尾巴
}


//站立
void Servo_stand(void)
{
    Face_Stare(); // 瞪大眼表情
    
    Servo_SetAngle(1, 90);
    Delay_ms(10);
    Servo_SetAngle(2, 90);
    Delay_ms(100);
    Servo_SetAngle(3, 90); 
    Delay_ms(10);
    Servo_SetAngle(4, 90);
}

//睡觉
void Servo_sleep(void)
{
    Face_Sleep(); // 睡觉表情

    Servo_SetAngle(1, 0);
    Delay_ms(10);
    Servo_SetAngle(2, 0);
    Delay_ms(100);
    Servo_SetAngle(3, 180);
    Delay_ms(10);
    Servo_SetAngle(4, 180);
    LED_Control = 0;
}

//趴下
void Servo_go_prone(void)
{
    Face_OpenEyes(); //表情

    Servo_SetAngle(1, 180);   // 前左
    Delay_ms(150);
    Servo_SetAngle(2, 0);   // 前右
    Delay_ms(150);
    Servo_SetAngle(3, 0); // 后左
    Delay_ms(150);
    Servo_SetAngle(4, 180); // 后右
    Delay_ms(50);
    Servo_Swing(5, 170, 2); // 摆尾巴
}

//蹲下
void Servo_sit_down(void)
{
    Face_VeryHappy(); // 非常快乐表情

    Servo_SetAngle(1, 90);   // 前左
    Delay_ms(150);
    Servo_SetAngle(2, 0);   // 前右
    Delay_ms(150);
    Servo_SetAngle(3, 90); // 后左
    Delay_ms(150);
    Servo_SetAngle(4, 180); // 后右
    Delay_ms(50);
    Servo_Swing(5, 150, 2); // 摆尾巴
}

//升懒腰
void Servo_stretch(void)
{
    Face_Happy();

    Servo_SetAngle(1, 180);
    Delay_ms(20);
    Servo_SetAngle(3, 0);
    Delay_ms(150);
    Servo_SetAngle(2, 90);
    Delay_ms(20);
    Servo_SetAngle(4, 90);
    Delay_ms(150);
    Servo_Swing(5, 170, 2); // 摆尾巴
}

//打招呼
void Servo_hello(void)
{
    Servo_stand(); // 站立
    Delay_ms(10);
    Face_Hello(); // 打招呼表情
    Delay_ms(50);
    Servo_Swing(3, 170, 3); // 打招呼
}

//摇摆
void Servo_swing_1(void)
{
    Face_VeryHappy();

    Delay_ms(100);
    for (uint8_t i = 0; i < 3; i++)
    {

        for (uint8_t i = 30; i < 150; i++)
        {
            Servo_SetAngle(3, i); // 前左
            Servo_SetAngle(1, 180 - i); // 后左
            Servo_SetAngle(4, i); // 前右
            Servo_SetAngle(2, 180 - i); // 后右
            Delay_ms(7);
        }
        for (uint8_t i = 150; i > 30; i--)
        {
            Servo_SetAngle(3, i); // 前左
            Servo_SetAngle(1, 180 - i); // 后左
            Servo_SetAngle(4, i); // 前右
            Servo_SetAngle(2, 180 - i); // 后右
            Delay_ms(7);
        }
    }
    Servo_Swing(5, 170, 2);// 摆尾巴
}

//握手
void Servo_handshake(void)
{
    Face_Hello();

    Servo_SetAngle(1, 180);
}


// 跑步
void Servo_run(void)
{
    Servo_stand(); // 站立
    Face_Mania(); // 狂热表情
    Delay_ms(200);

    for (uint8_t i = 0; i < 3; i++)
    {
        Servo_SetAngle(1, 150);
        Delay_ms(20);
        Servo_SetAngle(2, 150);
        Delay_ms(200);
        Servo_SetAngle(3, 30);
        Delay_ms(20);
        Servo_SetAngle(4, 30);
        Delay_ms(200);
        Servo_SetAngle(1, 90);
        Delay_ms(20);
        Servo_SetAngle(2, 90);
        Delay_ms(200);
        Servo_SetAngle(3, 90);
        Delay_ms(20);
        Servo_SetAngle(4, 90);

        Delay_ms(250);

        Servo_SetAngle(3, 30);
        Delay_ms(20);
        Servo_SetAngle(4, 30);
        Delay_ms(200);
        Servo_SetAngle(1, 150);
        Delay_ms(20);
        Servo_SetAngle(2, 150);
        Delay_ms(200);
        Servo_SetAngle(3, 90);
        Delay_ms(20);
        Servo_SetAngle(4, 90);
        Delay_ms(200);
        Servo_SetAngle(1, 90);
        Delay_ms(20);
        Servo_SetAngle(2, 90);
        Delay_ms(200);
    }
}

//表演
//前进-打招呼-摇摆-蹲下
void Servo_perform(void)
{
    Servo_forward();//前进
    Delay_ms(200);
    Servo_hello();
    Delay_ms(200);
    Servo_swing_1();
    Delay_ms(200);
    Servo_sit_down();
    LED_Control = 2;
}
