#include "ai.h"
#include "motor.h"   // 你的电机驱动
#include "OLED.h"    // 你的屏幕/表情/图像
#include "system.h"  // 系统状态
#include <Arduino.h>
#include "touch.h"


//防频繁触发触摸加成
unsigned long last_touch = 0;
const unsigned long touch_time = 8000; //5秒 



// ========================= =========================
// 【函数1】AI初始化（开机一次）
// ========================= =========================
void ai_init(void)
{
  // 初始动机：中等舒适，低探索，低焦躁
  m_comfort   = 45.0f;
  m_explore   = 20.0f;
  m_agitation = 10.0f;

  // 初始状态
  current_mood = MOOD_IDLE;
  t_think   = millis();
  t_action  = millis();
  t_mood    = millis();

  // 初始动作：停止
  current_act = {ACT_STOP, 0, 1000, 3000, 0};
}

// ========================= =========================
// 【函数2】动机自动更新（高级生物模拟）
// 欲望不会突变，只会缓慢增减，非常自然
// ========================= =========================
void ai_update_motivation(void)
{

    // 三个维度各自的：均值、波动范围、变化速度
  //焦躁  
  const float a_mean  = 50.0f;    // A 的中心均值
  const float a_range = 25.0f;    // A 上下波动幅度
  const float a_speed = 0.45f;    // A 变化快慢
  //舒适
  const float c_mean  = 50.0f;    // C 的中心均值
  const float c_range = 25.0f;    // C 上下波动幅度
  const float c_speed = 0.46f;    // C 变化快慢
  //探索
  const float e_mean  = 50.0f;    // E 的中心均值
  const float e_range = 35.0f;    // E 上下波动幅度
  const float e_speed = 0.4f;    // E 变化快慢

  // 微小自然扰动 t（0 ~ 0.24），让数值更像生物波动
  float t = random(0, 50) / 100.0f;

  // ==============================
  // 焦躁 A：围绕 a_mean 波动
  // ==============================
  float target_a = a_mean + random(-a_range, a_range + 1);
  m_agitation += a_speed * (target_a - m_agitation) + t;

  // ==============================
  // 舒适 C：围绕 c_mean 波动
  // ==============================
  float target_c = c_mean + random(-c_range, c_range + 1);
  m_comfort += c_speed * (target_c - m_comfort) + t;

  // ==============================
  // 探索 E：围绕 e_mean 波动
  // ==============================
  float target_e = e_mean + random(-e_range, e_range + 1);
  m_explore += e_speed * (target_e - m_explore) + t;
  // =========================
  // 全局安全范围锁死
  // 绝对范围：0 ~ 100
  // 自然活动范围：20 ~ 80（不会极端）
  // =========================
  m_comfort   = constrain(m_comfort,   0.0f, 100.0f);
  m_explore   = constrain(m_explore,   0.0f, 100.0f);
  m_agitation = constrain(m_agitation, 0.0f, 100.0f);

  // 软保护：防止长期低于20，保证AI永远活泼不发呆
  if (m_comfort   < 20)  m_comfort  += 0.3f;
  if (m_explore   < 20)  m_explore  += 0.4f;
  if (m_agitation < 20)  m_agitation+= 0.2f;

  // 软保护：防止长期高于80，避免情绪极端化
  if (m_comfort   > 80)  m_comfort  *= 0.98f;
  if (m_explore   > 80)  m_explore  *= 0.97f;
  if (m_agitation > 80)  m_agitation*= 0.96f;
}

// ========================= =========================
// 【函数3】动机 → 情绪（计算得出，不是随机）
// ========================= =========================
void ai_calc_mood(void)
{
  float C = m_comfort;
  float E = m_explore;
  float A = m_agitation;

  if      (A > 60 && 	C<40)  current_mood = MOOD_ANGRY;//烦躁
  else if (E > 60 && C < 58)  current_mood = MOOD_CURIOUS;//好奇
  else if (C > 60 && A < 45)  current_mood = MOOD_HAPPY;//开心
  else if (A > 62)  current_mood = MOOD_NERVOUS;//不安
  else              current_mood = MOOD_IDLE;//发呆
}

// ========================= =========================
// 【函数4】根据情绪 → 返回【概率加权行为表】
// 核心：不同心情，每个行为的概率不一样
// ========================= =========================
int ai_get_action_rules(AiMood mood, ActionRule *out_list)
{
  int idx = 0;

  switch (mood) {

    // ===== 开心：平稳前进、柔和转弯、舒适 =====
    case MOOD_HAPPY:
      out_list[idx++] = {ACT_FORWARD,    50, 400, 900, 50};   // 时间延长、速度校准
      out_list[idx++] = {ACT_TURN,       20, 200, 450, 40};
      out_list[idx++] = {ACT_SIDE,       15, 250, 500, 35};
      out_list[idx++] = {ACT_EXPRESSION, 10, 0, 0, 0};
      out_list[idx++] = {ACT_STOP,       10, 800, 4000, 0};
      break;

    // ===== 好奇：主动探索、频繁转向、快速移动 =====
    case MOOD_CURIOUS:
      out_list[idx++] = {ACT_TURN,       45, 300, 600, 45};
      out_list[idx++] = {ACT_FORWARD,    35, 350, 800, 50};
      out_list[idx++] = {ACT_SIDE,       20, 250, 500, 38};
      out_list[idx++] = {ACT_EXPRESSION, 10, 0, 0, 0};
      out_list[idx++] = {ACT_STOP,        5, 500, 2000, 0};
      break;

    // ===== 不安：后退、小角度转弯、警惕停顿 =====
    case MOOD_NERVOUS:
      out_list[idx++] = {ACT_BACKWARD,   40, 250, 500, 45};
      out_list[idx++] = {ACT_TURN,       30, 250, 450, 42};
      out_list[idx++] = {ACT_STOP,       25, 800, 4000, 0};
      out_list[idx++] = {ACT_EXPRESSION,  5, 0, 0, 0};
      break;

    // ===== 烦躁：快速转身、快速后退、多动不休息 =====
    case MOOD_ANGRY:
      out_list[idx++] = {ACT_TURN,       55, 300, 650, 55};   // 转弯更快
      out_list[idx++] = {ACT_BACKWARD,   35, 250, 550, 50};   // 后退更快
      out_list[idx++] = {ACT_EXPRESSION, 10, 0, 0, 0};
      out_list[idx++] = {ACT_STOP,        5, 300, 1500, 0};
      break;

    // ===== 发呆：小幅动作、偶尔转身、轻松状态 =====
    case MOOD_IDLE:
    default:
      out_list[idx++] = {ACT_STOP,       25, 1000, 2000, 0};
      out_list[idx++] = {ACT_TURN,       40, 150, 300, 40};
      out_list[idx++] = {ACT_FORWARD,    20, 200, 400, 30};
      out_list[idx++] = {ACT_EXPRESSION, 15, 0, 0, 0};
      break;
  }
  return idx;
}

// ========================= =========================
// 【函数5】加权随机选择（真正高级：轮盘赌算法）
// 权重越高，被选中概率越大，模拟生物“倾向”
// ========================= =========================
ActionRule ai_choose_action(ActionRule *list, int count)
{
  // 1. 计算总权重
  int total_weight = 0;
  for (int i = 0; i < count; i++) {
    total_weight += list[i].weight;
  }

  // 2. 生成随机数
  int rand_val = random(total_weight);

  // 3. 轮盘抽取（按概率选择）
  int accumulate = 0;
  for (int i = 0; i < count; i++) {
    accumulate += list[i].weight;
    if (rand_val < accumulate) {
      return list[i];
    }
  }

  // 默认返回停止
  return list[0];
}

// ========================= =========================
// 【函数6】执行选中的行为（调用你的电机+屏幕）
// ========================= =========================
void ai_do_action(ActionRule act)
{
  // 随机时间，让动作更自然
  int dur = random(act.dur_min, act.dur_max);

  // 先停车，再执行新动作
  motorA_stop();
  motorB_stop();

  //Serial.print("动作：");
  //Serial.print(act.type);


  switch (act.type) {

    case ACT_TURN:      // 转身：左右随机
      if(random(2) == 0){
        // 左转：A后退，B前进
        motorA_backward(act.speed, dur);
        motorB_forward(act.speed, dur);
      }else{
        // 右转：B后退，A前进
        motorB_backward(act.speed, dur);
        motorA_forward(act.speed, dur);
      }
      break;

    case ACT_SIDE:      // 侧身（左右微动）
      if(random(2) == 0){
        // 左转：A后退，B前进
        motorA_backward(act.speed, dur);
        motorB_forward(act.speed, dur);
      }else{
        // 右转：B后退，A前进
        motorB_backward(act.speed, dur);
        motorA_forward(act.speed, dur);
      }
      break;
    case ACT_FORWARD:   // 前进
      motorA_forward(act.speed, dur);
      motorB_forward(act.speed, dur);
      break;

    case ACT_BACKWARD:  // 后退
      motorA_backward(act.speed, dur);
      motorA_backward(act.speed, dur);
      break;

    case ACT_EXPRESSION: // 表情变化
      ai_update_expression();
      break;

    case ACT_STOP:       // 发呆
      break;
  }

  t_action = millis();
}

// ========================= =========================
// 【函数7】根据情绪切换表情
// ========================= =========================
void ai_update_expression(void)
{
  if (millis() - t_mood < MOOD_CHANGE_MS) return;
  t_mood = millis();
  //Serial.print("表情：");
  //Serial.print(current_mood);

  u8g2.clearBuffer();//清屏
  u8g2.setFont(u8g2_font_8x13_tf);
  u8g2.drawStr(0, 10, "A");

  switch (current_mood) {
    case MOOD_HAPPY:    image_num(25,0,80,64,109); break;  // 开心表情
    case MOOD_CURIOUS:  image_num(25,0,80,64,101); break;  // 好奇表情
    case MOOD_NERVOUS:  image_num(25,0,80,64,108); break;  // 不安表情
    case MOOD_ANGRY:    image_num(25,0,80,64,106); break;  // 烦躁表情
    case MOOD_IDLE:     image_num(20,3,90,60,15); break;  // 平静表情
  }


  //drawicon(112,0,"wifi");

  //drawicon(0,53,"left");

  //drawicon(117,53,"right");

    //上传打印
  u8g2.sendBuffer();

}

// ========================= =========================
// 【函数8】AI主循环（一旦进入，持续运行！）
// ========================= =========================
void ai_run_loop(void)
{
  // 初始化一次
  ai_init();
  Serial.print("AI模块已启动。。。");
  delay(1000);

  // ====================== 【AI 独立循环】 ======================
  while (1) {

    // --------------------------
    // 【退出条件】你自己设置
    // 满足条件 → 跳出循环，回到系统
    // --------------------------
    //if (;;) {
      //break;
    //}

    // 电机安全检查（必须一直跑）
    motorA_check();
    motorB_check();
    //表情更新
    ai_update_expression();

  // ======================
  // 退出AI：复位系统
  // ======================
    if(touch()){
      delay(1000);
      if(touch()) {
        motorA_stop();
        motorB_stop();
        return;
      } 
      delay(200);

   }

/*     if(millis() - last_touch >= touch_time){
      // 触摸时：提高探索欲 + 焦躁 → AI立刻变兴奋
      if(touch()){
        m_explore += 25;    // 探索欲暴涨
        m_agitation += 15;  // 焦躁小幅上涨
      }
      last_touch = millis();
    } */
      // --------------------------
    // 控制思考频率，避免太频繁
    // --------------------------
    if (millis() - t_think < AI_THINK_MS) {
      continue;
    }
    t_think = millis();

    // --------------------------
    // 【高级AI核心流程】
    // 1.更新动机 → 2.计算情绪 → 3.获取行为权重 → 4.选择行为 → 5.执行
    // --------------------------
    ai_update_motivation();
    ai_calc_mood();

    ActionRule rule_list[10];
    int rule_count = ai_get_action_rules(current_mood, rule_list);
    current_act = ai_choose_action(rule_list, rule_count);

    ai_do_action(current_act);


    Serial.print("舒适欲C:");
    Serial.print(m_comfort);
    //Serial.print("/n");
    Serial.print("探索欲E:");
    Serial.print(m_explore);
    //Serial.print("/n");
    Serial.print("焦躁欲A:");
    Serial.print(m_agitation);
    Serial.print("时间:");
    Serial.print(millis());

    if      (m_comfort > 60 && m_agitation < 45)  Serial.print("开心");
    else if (m_explore > 60 && m_comfort < 58)  Serial.print("好奇");
    else if (m_agitation > 62)  Serial.print("不安");
    else if (m_agitation > 60 && 	m_comfort < 40)             Serial.print("烦躁");
    else                        Serial.print("发呆");
    Serial.print("   \n");


  }




}

