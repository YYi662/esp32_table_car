#include "system.h"
#include "OLED.h"
#include "motor.h"
#include "touch.h"
#include "ai.h"

//=======触摸说明==========
//短按触摸触发WIFI控制模式，
//长按3秒触发AI模块



//定义没有触摸信号的时间
unsigned long lastTouchTime = 0;
const unsigned long SLEEP_TIMEOUT = 15000; // 睡眠时间6秒


// 保存当前状态（默认开机进入工作模式）
int is_mode = STATE_TABLE;


// 屏幕刷新标志：只在需要时刷新
bool screenNeedUpdate = true;




// 获取当前状态
int get_mode(){
    return is_mode;
}

// 设置新状态（切换时可以做初始化动作）
void set_mode(int new_mode) {
    if(get_mode() != new_mode)
        is_mode = new_mode;
}



// 状态机：根据当前状态执行不同动作
void run_system() {

  //检查中心
  //电机运行时间检验
  motorA_check();
  motorB_check();
  int mode_l;





  switch (is_mode) {

    // ======================
    // 状态 1：睡眠
    // ======================
    case STATE_SLEEP:
        Serial.print("SLEEP模式。。。");
        //电机关闭
        motorA_stop();
        motorB_stop();

        anim_run(sleep);//睡眠动画
        
        //唤醒条件
        if (touch()) {
            lastTouchTime = millis();
            screenNeedUpdate = true;//屏幕更新
            delay(2000);
            set_mode(STATE_TABLE);
         }
      break;


    // ======================
    // 状态 2：普通静置状态
    // ======================
    case STATE_TABLE:
      Serial.print("TABLE模式。。。");
      if (screenNeedUpdate) {
        table("T");          // 只执行一次你的桌面
        screenNeedUpdate = false;
      } 

      //通过触摸进入AI和WIFI控制模式
      mode_l = check_touch_mode();
      Serial.print("mode_l是：");
      Serial.print(mode_l);
      Serial.print("\n");
      if(mode_l == 1){ //按了松开
          set_mode(STATE_CTRL);
          delay(2000);
          lastTouchTime = millis();
          screenNeedUpdate = true;//屏幕更新
      }
      else if(mode_l == 2){//按了3秒
        set_mode(STATE_AI);
        lastTouchTime = millis();
      }

      // 10秒没摸 → 睡眠
      if (millis() - lastTouchTime > SLEEP_TIMEOUT) {
       set_mode(STATE_SLEEP);
       delay(1000);
       anim_run(tosleep);
      }
  
      break;



    // ======================
    // 状态 3：AI控制模式
    // ======================
    case STATE_AI:
      Serial.print("AI模式。。。");
      ai_run_loop();
      set_mode(STATE_TABLE);
      screenNeedUpdate = true;//屏幕更新
      delay(2000);
      lastTouchTime = millis();//重置触摸时间
      break;


  
    // ======================
    // 状态 4：WiFi手动控制模式
    // ======================
    case STATE_CTRL:
      Serial.print("CTRL模式。。。");
      if (screenNeedUpdate) {
      table("C");          // 只执行一次你的桌面
      screenNeedUpdate = false;
      }


      handleUDP();//控制核心函数

      set_mode(STATE_TABLE);
      screenNeedUpdate = true;//屏幕更新
      delay(2000);
      lastTouchTime = millis();//重置触摸时间

      break;
 }

}





//table时间测试函数
/* void testTableSpeed() {
  unsigned long start = micros();  // 开始计时（微秒级）

  table("A");  // 执行你的屏幕函数

  unsigned long end = micros();    // 结束计时
  unsigned long time = end - start;

  // 打印结果（单位：微秒 ms = 毫秒）
  Serial.print("table() 执行耗时：");
  Serial.print(time);
  Serial.println(" 微秒 (");
  Serial.print(time / 1000);
  Serial.println(" ms)");
} */






