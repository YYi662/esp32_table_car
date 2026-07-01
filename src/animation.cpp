#include "animation.h"




//位置参数配置
int ANIM_X = 0;
int ANIM_Y = 0;
int ANIM_W = 128;
int ANIM_H = 64;

// 内部状态
static uint8_t  _current_frame = 0;//帧位置
static uint8_t  _total_frames  = 1;//总帧数
static uint16_t _frame_delay    ;//每帧时间
static unsigned long _last_ms   = 0;
static bool     _anim_playing   = false;//正在播放


// ===============初始化===============
void anim_init() {
  _current_frame = 0;
  _anim_playing  = false;
}

// ===============启动=总帧数，每帧时==============
void anim_start(uint8_t total_frames, uint16_t frame_delay_ms) {
  _current_frame = 0;
  _total_frames  = total_frames;
  _frame_delay   = frame_delay_ms;
  switch(total_frames){
    case 31:
      ANIM_W = 124;
      ANIM_H = 64;
      break;
    case 58:
      ANIM_W = 70;
      ANIM_H = 60;
      break;
    case 30:
      ANIM_W = 53;
      ANIM_H = 60;
      break;
  }
  ANIM_X = (128 - ANIM_W) / 2 ; // 居中X
  ANIM_Y = (64 - ANIM_H) / 2 ;
  _anim_playing  = true;
  _last_ms       = millis();
  Serial.print("w h x y ");
  Serial.print(ANIM_W);
  Serial.print(ANIM_H);
  Serial.print(ANIM_X);
  Serial.print(ANIM_Y);
}

// ===============停止===============
void anim_stop() {
  _anim_playing = false;
  u8g2.clearBuffer();
  u8g2.sendBuffer();
}

// ===============播放一帧===============
void anim_play_frame(uint8_t icome) {
  if (!_anim_playing || _total_frames == 0) return;

  unsigned long now = millis();
  if (now - _last_ms < _frame_delay) return;
  _last_ms = now;
  //退出播放
  if (_current_frame >= _total_frames) {
    _current_frame = 0; // 循环播放
    delay(500);
    if(icome != welcome)
      anim_stop();
    else{
      delay(800);
      anim_stop();
    }
  }
  Serial.print("  icome值：");
  Serial.print(icome);
  Serial.print("\n");
  // 清屏、画当前帧
  u8g2.clearBuffer();

  switch(icome){
    case 31://开机动画
      for (int i = 0; i < dictLen_frames; i++) {
        if (anim_frames[i].num == _current_frame) {
        //打印
           u8g2.drawXBM(ANIM_X, ANIM_Y, ANIM_W, ANIM_H, anim_frames[i].data);
        }
      }
      break;

    case 30://睡眠动画
      for (int i = 0; i < dictLen_sleep; i++) {
        if ((anim_sleep[i].num - 89) == _current_frame) {
        //打印
           u8g2.drawXBM(ANIM_X, ANIM_Y, ANIM_W, ANIM_H, anim_sleep[i].data);
        }
      }
      break;

    case 58://进入睡眠动画
      for (int i = 0; i < dictLen_tosleep; i++) {
        if ((anim_tosleep[i].num - 31) == _current_frame) {
        //打印
           u8g2.drawXBM(ANIM_X, ANIM_Y, ANIM_W, ANIM_H, anim_tosleep[i].data);
        }
      }
      break;      
  }

  u8g2.sendBuffer();

  // 下一帧
  _current_frame++;

}


unsigned long sleep_time = 0;
const unsigned long min_time_sleep = 3000; 
//传入动画项目
void anim_run(uint8_t icome){
    if(icome == 30){
      if(millis() - sleep_time < min_time_sleep){
        return;
      }
      sleep_time = millis();
    }
    anim_init();
    anim_start(icome,150);
    while(_anim_playing){
    anim_play_frame(icome);
    }
}