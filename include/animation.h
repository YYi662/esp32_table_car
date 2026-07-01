#ifndef ANIMATION_H
#define ANIMATION_H

#include <Arduino.h>
#include <U8g2lib.h>


extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;


//帧数定义
#define welcome  31  //124*64
#define tosleep  58  //70*60
#define sleep    30  //53*60



// 初始化动画系统
void anim_init();

// 播放下一帧（非阻塞，loop里反复调用）
void anim_play_frame(uint8_t icome);

// 启动动画，并设置总帧数、每帧延时(ms)
void anim_start(uint8_t total_frames, uint16_t frame_delay_ms);

// 停止动画
void anim_stop();

//调用函数
void anim_run(uint8_t animation);





// 每一帧 XBM 数组

//welcome
extern const uint8_t frame0[];
extern const uint8_t frame1[];
extern const uint8_t frame2[];
extern const uint8_t frame3[];
extern const uint8_t frame4[];
extern const uint8_t frame5[];
extern const uint8_t frame6[];
extern const uint8_t frame7[];
extern const uint8_t frame8[];
extern const uint8_t frame9[];
extern const uint8_t frame10[];
extern const uint8_t frame11[];
extern const uint8_t frame12[];
extern const uint8_t frame13[];
extern const uint8_t frame14[];
extern const uint8_t frame15[];
extern const uint8_t frame16[];
extern const uint8_t frame17[];
extern const uint8_t frame18[];
extern const uint8_t frame19[];
extern const uint8_t frame20[];
extern const uint8_t frame21[];
extern const uint8_t frame22[];
extern const uint8_t frame23[];
extern const uint8_t frame24[];
extern const uint8_t frame25[];
extern const uint8_t frame26[];
extern const uint8_t frame27[];
extern const uint8_t frame28[];
extern const uint8_t frame29[];
extern const uint8_t frame30[];

//tosleep
extern const uint8_t tosleep0[];
extern const uint8_t tosleep1[];
extern const uint8_t tosleep2[];
extern const uint8_t tosleep3[];
extern const uint8_t tosleep4[];
extern const uint8_t tosleep5[];
extern const uint8_t tosleep6[];
extern const uint8_t tosleep7[];
extern const uint8_t tosleep8[];
extern const uint8_t tosleep9[];
extern const uint8_t tosleep10[];
extern const uint8_t tosleep11[];
extern const uint8_t tosleep12[];
extern const uint8_t tosleep13[];
extern const uint8_t tosleep14[];
extern const uint8_t tosleep15[];
extern const uint8_t tosleep16[];
extern const uint8_t tosleep17[];
extern const uint8_t tosleep18[];
extern const uint8_t tosleep19[];
extern const uint8_t tosleep20[];
extern const uint8_t tosleep21[];
extern const uint8_t tosleep22[];
extern const uint8_t tosleep23[];
extern const uint8_t tosleep24[];
extern const uint8_t tosleep25[];
extern const uint8_t tosleep26[];
extern const uint8_t tosleep27[];
extern const uint8_t tosleep28[];
extern const uint8_t tosleep29[];
extern const uint8_t tosleep30[];
extern const uint8_t tosleep31[];
extern const uint8_t tosleep32[];
extern const uint8_t tosleep33[];
extern const uint8_t tosleep34[];
extern const uint8_t tosleep35[];
extern const uint8_t tosleep36[];
extern const uint8_t tosleep37[];
extern const uint8_t tosleep38[];
extern const uint8_t tosleep39[];
extern const uint8_t tosleep40[];
extern const uint8_t tosleep41[];
extern const uint8_t tosleep42[];
extern const uint8_t tosleep43[];
extern const uint8_t tosleep44[];
extern const uint8_t tosleep45[];
extern const uint8_t tosleep46[];
extern const uint8_t tosleep47[];
extern const uint8_t tosleep48[];
extern const uint8_t tosleep49[];
extern const uint8_t tosleep50[];
extern const uint8_t tosleep51[];
extern const uint8_t tosleep52[];
extern const uint8_t tosleep53[];
extern const uint8_t tosleep54[];
extern const uint8_t tosleep55[];
extern const uint8_t tosleep56[];
extern const uint8_t tosleep57[];

//sleep
extern const uint8_t sleep0[];
extern const uint8_t sleep1[];
extern const uint8_t sleep2[];
extern const uint8_t sleep3[];
extern const uint8_t sleep4[];
extern const uint8_t sleep5[];
extern const uint8_t sleep6[];
extern const uint8_t sleep7[];
extern const uint8_t sleep8[];
extern const uint8_t sleep9[];
extern const uint8_t sleep10[];
extern const uint8_t sleep11[];
extern const uint8_t sleep12[];
extern const uint8_t sleep13[];
extern const uint8_t sleep14[];
extern const uint8_t sleep15[];
extern const uint8_t sleep16[];
extern const uint8_t sleep17[];
extern const uint8_t sleep18[];
extern const uint8_t sleep19[];
extern const uint8_t sleep20[];
extern const uint8_t sleep21[];
extern const uint8_t sleep22[];
extern const uint8_t sleep23[];
extern const uint8_t sleep24[];
extern const uint8_t sleep25[];
extern const uint8_t sleep26[];
extern const uint8_t sleep27[];
extern const uint8_t sleep28[];
extern const uint8_t sleep29[];



//结构体--用于查询

typedef struct {
  const int  num;   // 帧名
  const uint8_t* data; // 对应的字模数组
} framItem;

typedef struct {
  const int  num;   // 帧名
  const uint8_t* data; // 对应的字模数组
} tosleepItem;

typedef struct {
  const int  num;   // 帧名
  const uint8_t* data; // 对应的字模数组
} sleepItem;


// 帧列表指针
const framItem anim_frames[] = {
    {0,frame0},  {1,frame1},  {2,frame2},  {3,frame3},  {4,frame4}, {5,frame5}, 
    {6,frame6},  {7,frame7},  {8,frame8},  {9,frame9},  {10,frame10}, 
    {11,frame11},  {12,frame12},  {13,frame13},  {14,frame14},  {15,frame15}, 
    {16,frame16},  {17,frame17},  {18,frame18},  {19,frame19},  {20,frame20}, 
    {21,frame21},  {22,frame22},  {23,frame23},  {24,frame24},  {25,frame25}, 
    {26,frame26},  {27,frame27},  {28,frame28},  {29,frame29},  {30,frame30}, 
};

const tosleepItem anim_tosleep[] = {
{31,tosleep0},{32,tosleep1},{33,tosleep2},{34,tosleep3},{35,tosleep4},
{36,tosleep5},{37,tosleep6},{38,tosleep7},{39,tosleep8},{40,tosleep9},
{41,tosleep10},{42,tosleep11},{43,tosleep12},{44,tosleep13},{45,tosleep14},
{46,tosleep15},{47,tosleep16},{48,tosleep17},{49,tosleep18},{50,tosleep19},
{51,tosleep20},{52,tosleep21},{53,tosleep22},{54,tosleep23},{55,tosleep24},
{56,tosleep25},{57,tosleep26},{58,tosleep27},{59,tosleep28},{60,tosleep29},
{61,tosleep30},{62,tosleep31},{63,tosleep32},{64,tosleep33},{65,tosleep34},
{66,tosleep35},{67,tosleep36},{68,tosleep37},{69,tosleep38},{70,tosleep39},
{71,tosleep40},{72,tosleep41},{73,tosleep42},{74,tosleep43},{75,tosleep44},
{76,tosleep45},{77,tosleep46},{78,tosleep47},{79,tosleep48},{80,tosleep49},
{81,tosleep50},{82,tosleep51},{83,tosleep52},{84,tosleep53},{85,tosleep54},
{86,tosleep55},{87,tosleep56},{88,tosleep57},
};

const sleepItem anim_sleep[] = {
{89,sleep0},{90,sleep1},{91,sleep2},{92,sleep3},{93,sleep4},
{94,sleep5},{95,sleep6},{96,sleep7},{97,sleep8},{98,sleep9},
{99,sleep10},{100,sleep11},{101,sleep12},{102,sleep13},{103,sleep14},
{104,sleep15},{105,sleep16},{106,sleep17},{107,sleep18},{108,sleep19},
{109,sleep20},{110,sleep21},{111,sleep22},{112,sleep23},{113,sleep24},
{114,sleep25},{115,sleep26},{116,sleep27},{117,sleep28},{118,sleep29},
};

const int dictLen_frames = sizeof(anim_frames) / sizeof(framItem);
const int dictLen_tosleep = sizeof(anim_tosleep) / sizeof(tosleepItem);
const int dictLen_sleep = sizeof(anim_sleep) / sizeof(sleepItem);


#endif