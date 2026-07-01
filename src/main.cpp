#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include "OLED.h"
#include "motor.h"
#include "touch.h"
#include "system.h"
#include "ai.h"
#include "animation.h"


// 你可以用的 ESP32 触摸引脚（选一个测试）
#define TOUCH_PIN  4 // GPIO4
#define TOUCH_num  50 //小于35则判为触摸信号 

//RTOS 任务
TaskHandle_t call = NULL;





void setup() {
  Wire.begin(17, 16);//初始化屏幕信号引脚
  u8g2.begin();//初始化屏幕
  touchInit();  // 初始化触摸
  motorInit(); // 电机必须初始化
  Serial.begin(9600);//串口初始化

  anim_run(welcome);
  table("T"); 
  /*
      // 初始化触摸
touchAttachInterrupt(TOUCH_PIN, touchISR, TOUCH_num);



  // 创建电机任务
xTaskCreatePinnedToCore(
    motorTask,
    "Motor",
    2048,
    NULL,
    10,
    &call,
    tskNO_AFFINITY
  );
*/


}

void loop() {

  //delay(500);
  run_system();

  //ai_run_loop();

  //测试函数运行周期
  //testTableSpeed();
  //delay(500);

  //handleUDP();



}
/*
// 中断触发时：唤醒电机任务
void IRAM_ATTR touchISR() {
  //发送消息给call
  xTaskNotifyFromISR(call, 1, eSetBits, NULL);
}*/