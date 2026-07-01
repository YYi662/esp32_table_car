#include "OLED.h"
#include "system.h"


#define SDA_PIN 17
#define SCL_PIN 16


U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);


char txt[] = "$v$";
int x = 20;
int y = 3;
int k = 1;
int n = 1;
//定义table刷新时间
unsigned long last_fresh = 0;
const unsigned long fresh_time = 5000; // 5秒



//简单线条函数
//直线线，
//void u8g2_DrawLine(u8g2_t *u8g2, u8g2_uint_t x0, u8g2_uint_t y0, u8g2_uint_t x1, u8g2_uint_t y1)
//空矩形框
//void u8g2_DrawFrame(u8g2_t *u8g2, u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t w, u8g2_uint_t h)
//实心三角形
//void u8g2_DrawTriangle(u8g2_t *u8g2, int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2)
//圆弧
//void u8g2_DrawArc(u8g2_t *u8g2, u8g2_uint_t x0, u8g2_uint_t y0, u8g2_uint_t rad, uint8_t start, uint8_t end)
//旋转角度，U8G2_R0 0度 U8G2_R1 顺90度  U8G2_R2 顺180度 U8G2_R3 顺270度
// /void u8g2_SetDisplayRotation(u8g2_t *u8g2, const u8g2_cb_t *u8g2_cb);



/* //线条测试函数
void text_li(){

} */




//系统桌面
void table(const char* c) {

    if(millis() - last_fresh < fresh_time) return;

    int a = random(1,25);
    if(a > 16) a = random(101,111);
    u8g2.clearBuffer();//清屏

    //u8g2.setFont(u8g2_font_ncenB14_tr);粗体
    // u8g2.setFont(u8g2_font_ncenB10_tr);//正常体
    u8g2.setFont(u8g2_font_8x13_tf);
 
    u8g2.drawStr(0, 10, c);


    image_num(25,0,80,64,110);//加载中央图

    if(c[0] == 'C')
    drawicon(112,0,"wifi");

    //drawicon(0,53,"left");

    //drawicon(117,53,"right");
 
    //上传打印
    u8g2.sendBuffer();



    last_fresh == millis();
   
}




//图标16*16
void drawicon(int x,int y, const char* word) {
  // 遍历字典，找到对应汉字
  for (int i = 0; i < dictLen_icon; i++) {
    if (strcmp(iconDict[i].name, word) == 0) {
      //打印
      u8g2.drawXBM(x, y, 16, 16, iconDict[i].data);
      return;
    }
  }
}




//找汉字16*16
void drawHanzi(int x,int y, const char* word) {
  // 遍历字典，找到对应汉字
  for (int i = 0; i < dictLen; i++) {
    if (strcmp(hanziDict[i].name, word) == 0) {
      //打印
      u8g2.drawXBM(x, y, 16, 16, hanziDict[i].data);
      return;
    }
  }
}

//图像--通过名称查找,x，y起点，w，h尺寸，k图形代号
void image(int x,int y, int w,int h,const char* word) {
  // 遍历字典，找到对应图形
  for (int i = 0; i < dictLen_i; i++) {
    if (strcmp(imageDict[i].name, word) == 0) {
      //打印
      u8g2.drawXBM(x, y, w, h, imageDict[i].data);
      return;
    }
  }
}
//图像--通过序号查找,x，y起点，w，h尺寸，k图形代号
void image_num(int x,int y, int w,int h, const int k) {
  // 遍历字典，找到对应图形
  for (int i = 0; i < dictLen_i; i++) {
    if (imageDict[i].num == k) {
      //打印
      u8g2.drawXBM(x, y, w, h, imageDict[i].data);
      return;
    }
  }
}


