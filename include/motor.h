#ifndef MOTOR_H
#define MOTOR_H
#include <Arduino.h>



// 引脚定义
#define IN1 27
#define IN2 26
#define IN3 32
#define IN4 33





// 电机控制函数声明

//初始化
void motorInit();
//A前
void motorA_forward(int speed, unsigned long ms);
//后
void motorA_backward(int speed, unsigned long ms);
//停
void motorA_stop();
//B前
void motorB_forward(int speed, unsigned long ms);
void motorB_backward(int speed, unsigned long ms);
void motorB_stop();



//运行时间检验
void motorA_check();
void motorB_check();

//中断器
void IRAM_ATTR touchISR();



#endif