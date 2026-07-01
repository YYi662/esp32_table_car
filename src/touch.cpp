#include "touch.h"
#include <Arduino.h>




// 你可以用的 ESP32 触摸引脚（选一个测试）
#define TOUCH_PIN  4 // GPIO4
#define TOUCH_num  50 //小于35则判为触摸信号 



void touchInit() {
  // 触摸不用额外初始化，空着就行
}



// ==================== 配置 ======================
unsigned long touch_press_start = 0;
bool touch_state = false;

// ==================== 触摸函数：短按=1，长按3秒=2，否则=0 ======================
int check_touch_mode() {

    bool tt = touch();
    // 没有触摸
    if (!tt) {
        Serial.print("没按 ");
        // 之前是按下的，现在松开了 → 判定【短按】
        if (touch_state == true) {
            touch_state = false;
            return 1;
        }
        return 0;
    }

    // 现在正在触摸
    else if(tt) {
        // 刚按下
        Serial.print("按了！   ");
        if (touch_state == false) {
            touch_state = true;
            touch_press_start = millis();
        }

        // 检测是否长按满 3 秒
        if (millis() - touch_press_start >= 3000) {
            touch_state = false; // 复位，防止重复触发
            return 2; // 长按3秒返回2
        }
        return 0;
    }

    return 0;
}


bool last = false;                   //用来记录上次判断结果
// 带防抖的触摸检测
bool touch() {
  uint16_t val = touchRead(TOUCH_PIN);
  
  static unsigned long last_time = 0;//计时器
  unsigned long now_time = millis();//当前时间

  
  if(now_time - last_time < 30){  // 防抖
    return last;
  }

  if (val < TOUCH_num) {  
    last_time = now_time;
    last = true;
    return true;
  }
  else{  
    last = false;
    return false;
  }
}