
#include "wifi_udp.h"
#include "motor.h"


// ==================== ESP32 热点配置 ====================
const char* AP_SSID     = "ESP32_Car";    // 手机搜到的热点名
const char* AP_PASS     = "12345678";    // 密码
const int   UDP_PORT    = 8888;          // UDP端口


// ==================== UDP 对象 ====================
WiFiUDP udp;
char    udpPacket[255];   // 接收数据缓存
int     packetSize;

// ==================== 全局控制模式 ====================
//bool isRemoteMode = true;  // false=AI自动, true=WiFi遥控


int speed = 60;
int run_time = 20;





// ==================== 启动 ESP32 热点 ====================
void initWiFiAP() {
  Serial.print("WiFi模块正在初始化。。。");
  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_SSID, AP_PASS);
  //wifi功率设定
  WiFi.setTxPower(WIFI_POWER_2dBm);
  Serial.println("ESP32 热点已开启：");
  Serial.print("SSID: ");
  Serial.println(AP_SSID);
  Serial.print("密码: ");
  Serial.println(AP_PASS);
  Serial.print("小车IP: ");
  Serial.println(WiFi.softAPIP());  // 手机要填这个IP：192.168.4.1

  udp.begin(UDP_PORT);
  Serial.print("UDP 端口: ");
  Serial.println(UDP_PORT);
  delay(50);
}



void stopWiFiAndReleaseAllResources() {
    Serial.print("WiFi模块正在关闭。。。");
    // 1. 停止 UDP 通信（必须最先关）
    udp.stop();

    // 2. 关闭 WiFi 连接
    WiFi.disconnect(true);  // true = 彻底断开
    WiFi.mode(WIFI_OFF);    // 关闭 WiFi 模块电源

    // 3. 释放 WiFi 内存资源
    WiFi.persistent(false); // 不保存 WiFi 配置

    // 4. 延时确保硬件完全关闭（非常短，不卡系统）
    delay(20);
}



// ==================== UDP 数据处理（核心！超低延迟） ====================
void handleUDP() {
  initWiFiAP();//初始化WiFi
  Serial.print("进入WiFi控制模块。。。");
  bool out = false;
  
  while(!out){

    memset(udpPacket, 0, sizeof(udpPacket));
    // 读取数据
    int len = udp.parsePacket();
    udp.read(udpPacket, len); 
    if (len > 0) {
      udpPacket[len] = '\0';
      Serial.print("数据：");
      Serial.print(udpPacket);
      Serial.print("   长度：");
      Serial.print(len);
      Serial.print("    ");
    
      // ==================== 指令解析 ====================
      String cmd = String(udpPacket);

      Serial.print("cmd的值");
      Serial.print(cmd  );
      Serial.print("\n");
      if(cmd == "78");

      else if (cmd == "79") out = true;

      else if (cmd == "F"){
        motorA_forward( speed, 10);
        motorB_forward( speed, 10);
      }

      else if (cmd == "B"){
        motorA_backward( speed, run_time);
        motorB_backward( speed, run_time);
      }

      else if (cmd == "L"){
        motorA_forward( speed, run_time);
        motorB_backward( speed, run_time);
      }

      else if (cmd == "R"){
        motorA_backward( speed, run_time);
        motorB_forward( speed, run_time);
      }

      else if(cmd == "60"){
          speed = 60;
          Serial.print("speed = 60");
        }
      else if(cmd == "80"){
          speed = 80;
          Serial.print("speed = 80");
        }
    }


   //运行时间检验
  motorA_check();
  motorB_check();
  

 /*     // 停止
    if (cmd.startsWith("S")) {
      motorA_stop();
      motorB_stop();
    }


    // 前进 F
    else if (cmd.startsWith("F")) {
      motorA_forward( speed, 10);
      motorB_forward( speed, 10);
      motorA_check();
      motorB_check();

    }

    // 后退 B
    else if (cmd.startsWith("B")) {
      motorA_backward( speed, run_time);
      motorB_backward( speed, run_time);

    }

    // 左转 L
    else if (cmd.startsWith("L")) {
      motorA_forward( speed, run_time);
      motorB_backward( speed, run_time);
     
    }

    // 右转 R
    else if (cmd.startsWith("R")) {
      motorA_backward( speed, run_time);
      motorB_forward( speed, run_time);
     
    } */

/*     // ==================== 【核心：执行一次就清空数据包】 ====================
    // 只要处理过任意指令 → 立即清空缓冲区
    // 下一轮loop就不会再重复执行

    while (udp.parsePacket() > 0) {
    udp.read(udpPacket, 255); // 把库里面的球拿出来
    }

    packetSize = 0;  
    if (hasCommand) {
        // 清空数据包内容
        memset(udpPacket, 0, sizeof(udpPacket));
        // 强制本次cmd失效，防止重复执行
        cmd = "";
    }
 */



  }
  Serial.print("退出WiFi控制模块。。。");
  stopWiFiAndReleaseAllResources();

}

