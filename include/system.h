#ifndef SYSTEM_H
#define SYSTEM_H


#include <U8g2lib.h>
#include "wifi_udp.h"
#include "animation.h"


// 定义两种状态
#define STATE_SLEEP    0   // 睡眠
#define STATE_TABLE   1   //桌面模式
#define STATE_AI     2   // 默认AI模式
#define STATE_CTRL     3   //WiFi遥控模式

extern int is_mode ;//全局工作状态变量
extern bool screenNeedUpdate;//全局绘制变量




// 获取当前状态
int get_mode();

// 设置状态（切换状态）
void set_mode(int new_mode);

// 状态机运行（必须放 loop 里）
void run_system();


void table(const char* c);

void testTableSpeed();
//眼
void checkAndHandleEmergency();

// 电机任务：休眠等待触摸唤醒
void motorTask(void *pv);

#endif