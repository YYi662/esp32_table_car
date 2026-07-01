#ifndef AI_H
#define AI_H
#include <Arduino.h>
#include "system.h"




// ========================= 【AI 核心配置】 =========================
#define AI_THINK_MS      5000    // 思考间隔（越小反应越快，越像活物）
#define ACTION_MIN_MS    800    // 动作最小时间
#define ACTION_MAX_MS    3000    // 动作最大时间
#define MOOD_CHANGE_MS   1000   // 表情自动切换间隔
#define STOP_MAX_MS      30000   // 发呆最长时间

// ========================= 【一、底层动机系统】 =========================
// 模拟生物本能：欲望会自动增长/衰减，决定“想做什么”
static float m_comfort;    // 舒适欲（越高越想静止、开心）
static float m_explore;    // 探索欲（越高越想动、前进、转身）
static float m_agitation;  // 焦躁欲（越高越乱转、后退、不安）

// ========================= 【二、情绪状态（由动机计算得出）】 =========================
typedef enum {
  MOOD_IDLE,     // 发呆（平衡状态）
  MOOD_HAPPY,    // 开心（舒适高）
  MOOD_CURIOUS,  // 好奇（探索高）
  MOOD_NERVOUS,  // 不安（焦躁↑ 舒适↓）
  MOOD_ANGRY     // 烦躁（焦躁极高）
} AiMood;
static AiMood current_mood;  // 当前情绪

// ========================= 【三、行为枚举（你要求的6类，去掉眨眼）】 =========================
typedef enum {
  ACT_TURN,      // a 转身
  ACT_SIDE,      // b 侧身
  ACT_FORWARD,   // c 前进
  ACT_BACKWARD,  // d 后退
  ACT_EXPRESSION,// f 表情变化
  ACT_STOP       // 停止/发呆
} ActionType;

// ========================= 【四、行为权重结构体（高级加权核心）】 =========================
// 每个行为：类型 + 概率权重 + 时间范围 + 速度
typedef struct {
  ActionType  type;       // 行为类型
  int         weight;     // 概率权重（数值越大，越容易被选中）
  int         dur_min;    // 动作最小持续时间
  int         dur_max;    // 动作最大持续时间
  int         speed;      // 动作基础速度
} ActionRule;

// ========================= 【五、AI运行计时器】 =========================
static unsigned long t_think;     // 思考计时器
static unsigned long t_action;   // 动作执行计时器
static unsigned long t_mood;     // 表情切换计时器

// ========================= 【六、当前选中的行为】 =========================
static ActionRule current_act;











void ai_init(void);

void ai_update_motivation(void);

void ai_calc_mood(void);

int ai_get_action_rules(AiMood mood, ActionRule *out_list);

ActionRule ai_choose_action(ActionRule *list, int count);

void ai_do_action(ActionRule act);

void ai_update_expression(void);


void ai_run_loop();

#endif