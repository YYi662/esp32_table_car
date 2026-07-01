#ifndef OLED_H
#define OLED_H


#include <U8g2lib.h>
#include "system.h"


extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;


//声明字模组

//icon组
extern const uint8_t icon_wifi[];
extern const uint8_t icon_right[];
extern const uint8_t icon_left[];

//汉字组
extern const uint8_t hanzi_qing[];
extern const uint8_t hanzi_tian[];
extern const uint8_t hanzi_tuyi[];

//image组
extern const uint8_t image_$v$[];
extern const uint8_t image_I0I[];
extern const uint8_t image_ioi[];
extern const uint8_t image_ff[];
extern const uint8_t image_YY[];
extern const uint8_t image__3_[];
extern const uint8_t image_ADA[];
extern const uint8_t image_D_D[];
extern const uint8_t image__o_[];
extern const uint8_t image_oDo[];
extern const uint8_t image_ODO[];
extern const uint8_t image_ovo[];
extern const uint8_t image__ovo_[];
extern const uint8_t image__ov_o[];
extern const uint8_t image_owo[];
extern const uint8_t image_uvu[];
//extern const uint8_t image_YY[];


extern const uint8_t image2_baogao[];
extern const uint8_t image2_chishoushou[];
extern const uint8_t image2_chouchang[];
extern const uint8_t image2_cuole[];
extern const uint8_t image2_good[];
extern const uint8_t image2_nu[];
extern const uint8_t image2_touxiang[];
extern const uint8_t image2_wanle[];
extern const uint8_t image2_xixi[];
extern const uint8_t image2_zhichi[];



//结构体定义
typedef struct {
  const char*  name;   // 汉字，比如 "晴"
  const uint8_t* data; // 对应的字模数组
} iconItem;

//结构体列表
const iconItem iconDict[] = {
  //16*16
  {"wifi", icon_wifi},
  {"right", icon_right},
  {"left", icon_left},
};


//结构体定义
typedef struct {
  const char*  name;   // 汉字，比如 "晴"
  const uint8_t* data; // 对应的字模数组
} HanziItem;

//结构体列表
const HanziItem hanziDict[] = {
  //16*16
  {"晴", hanzi_qing},
  {"天", hanzi_tian},
  {"图1",hanzi_tuyi},

};


//结构体定义
typedef struct {
  const int num;//序号索引
  const char*  name;   // 图像索引
  const uint8_t* data; // 对应的字模数组
} imageItem;

//结构体列表
const imageItem imageDict[] = {
  //90*60，居中建议x*y，20*3
  {1,"$v$",image_$v$},
  {2,"I0I",image_I0I},
  {3,"ioi",image_ioi},
  {4,"ff",image_ff},
  {5,"YY",image_YY},
  {6,"_3_",image__3_},
  {7,"ADA",image_ADA},
  {8,"D_D",image_D_D},
  {9,"_o_",image__o_},
  {10,"oDo",image_oDo},
  {11,"ODO",image_ODO},
  {12,"ovo",image_ovo},
  {13,"_ovo_",image__ovo_},
  {14,"_ov_o",image__ov_o},
  {15,"owo",image_owo},
  {16,"uvu",image_uvu},
  //{1,"_3_",image__3_},

//80*64,居中建议x*y，25*0
  {101,"baogao",image2_baogao},
  {102,"chishoushou",image2_chishoushou},
  {103,"chouchang",image2_chouchang},
  {104,"cuole",image2_cuole},
  {105,"good",image2_good},
  {106,"nu",image2_nu},
  {107,"touxiang",image2_touxiang},
  {108,"wanle",image2_wanle},
  {109,"xixi",image2_xixi},
  {110,"zhichi",image2_zhichi},



};





// 计算字典长度
const int dictLen_icon = sizeof(iconDict) / sizeof(iconItem);
const int dictLen = sizeof(hanziDict) / sizeof(HanziItem);
const int dictLen_i = sizeof(imageDict) / sizeof(imageItem);




//函数声明区
//void showBitmap();
void drawicon(int x,int y, const char* word);
void drawHanzi(int x,int y, const char* word);
void image(int x,int y, int w,int h, const char* word);
void image_num(int x,int y, int w,int h,  const int k);
//void drawXBM_Preempt(int x, int y, int w, int h, const uint8_t *data);

void text_li();


#endif