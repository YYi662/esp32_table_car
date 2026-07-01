# 桌面智能小车 - ESP32 Desktop Smart Car

<div align="center">

![ESP32](https://img.shields.io/badge/ESP32-arduino-00979D?style=flat-square)
![PlatformIO](https://img.shields.io/badge/PlatformIO-IDE-FF6600?style=flat-square)
![OLED](https://img.shields.io/badge/OLED-SSD1306-00FF00?style=flat-square)
![License](https://img.shields.io/badge/license-MIT-blue?style=flat-square)

**一个基于 ESP32 的桌面智能小车，具备 AI 自主行为、WiFi 遥控、OLED 表情动画等能力。**

</div>

---

## 功能特色

| 功能 | 说明 |
|------|------|
| **AI 自主行为** | 模拟生物动机系统（舒适欲/探索欲/焦躁欲），自主决策行为与表情 |
| **WiFi 遥控** | ESP32 开热点，手机 UDP 连接，实时操控小车运动 |
| **触摸交互** | 电容触摸传感器，支持短按/长按，切换工作模式 |
| **OLED 表情屏** | 128x64 像素，多种表情、图标、逐帧动画 |
| **睡眠节能** | 15 秒无操作自动入睡，触摸唤醒 |
| **低功耗设计** | WiFi 功率限制为 2dBm，降低热点功耗 |

---

## 硬件配置

### 引脚分配

| 引脚 | 功能 |
|------|------|
| GPIO27 / GPIO26 | 电机 A 正反转 (IN1/IN2) |
| GPIO32 / GPIO33 | 电机 B 正反转 (IN3/IN4) |
| GPIO4 | 电容触摸输入 |
| GPIO17 (SDA) / GPIO16 (SCL) | OLED I2C 通信 |

### 所需硬件

- ESP32 开发板（ESP32 Dev Module）
- 双路直流电机驱动板（L298N 或类似）
- SSD1306 128x64 OLED 屏幕（I2C 接口）
- 电容触摸传感器 / 触摸弹簧
- 小车底盘 + 轮子 + 电池

---

## 快速开始

### 环境要求

- [PlatformIO IDE](https://platformio.org/)（VS Code 扩展）
- 或 Arduino IDE + ESP32 支持包

### 编译 & 烧录

### 配套手机 App

项目根目录附带了 `app-debug.apk`，是 Android 遥控客户端，安装后通过 WiFi 热点控制小车。

ash 克隆项目
git clone https://github.com/yourname/table_car.git
cd table_car

使用 PlatformIO 编译上传
pio run --target upload

项目会自动从 PlatformIO 库安装依赖 olikraus/U8g2（OLED 驱动）。

---

## 软件架构

main.cpp (入口 & 模块初始化)
    |
    +-- system (状态机)     -- Sleep/Table/AI/Ctrl 四状态切换
    |       |
    |       +-- ai (AI 行为决策)  -- 动机 → 情绪 → 行为，轮盘赌权重选择
    |       +-- touch (触摸检测)  -- 短按/长按区分，30ms 防抖
    |
    +-- motor (电机驱动)     -- 正转/反转/停止，超时自动停止
    |
    +-- OLED (屏幕显示)      -- 表情/图标/汉字，每 5 秒随机换脸
    |       |
    |       +-- animation (动画) -- 欢迎/入睡/睡眠 三组逐帧动画
    |
    +-- wifi_udp (遥控)      -- ESP32 热点，UDP 指令控制

---

## AI 行为系统

### 三层动机模型

小车像生物一样有"欲望"，它们会随时间自然波动：

- **舒适欲** (m_comfort) — 越高越想静止、开心
- **探索欲** (m_explore) — 越高越想移动、探索
- **焦躁欲** (m_agitation) — 越高越不安、乱转

### 五种情绪 → 六种行为

动机计算出当前**情绪**，情绪决定行为**权重表**，轮盘赌算法随机选行为：

| 情绪 | 触发条件 | 典型行为 |
|------|----------|----------|
| 发呆 | 默认 | 停止、小幅表情变化 |
| 开心 | 舒适>60 且 焦躁<45 | 平稳前进、柔和转弯 |
| 好奇 | 探索>60 且 舒适<58 | 频繁转向、快速移动 |
| 不安 | 焦躁>62 | 后退、警惕停顿 |
| 烦躁 | 焦躁>60 且 舒适<40 | 快速转身、暴走后退 |

行为类型：转身 / 侧身 / 前进 / 后退 / 表情变化 / 发呆

---

## WiFi 遥控

1. 长按触摸 → 进入 **AI 模式**
2. 短按触摸 → 进入 **WiFi 遥控模式**
3. 手机连接热点 ESP32_Car（密码 12345678）
4. 用 UDP 调试工具向 192.168.4.1:8888 发送指令：

| 指令 | 动作 | 说明 |
|------|------|------|
| F | 前进 | 双电机正转 |
| B | 后退 | 双电机反转 |
| L | 左转 | A正B反 |
| R | 右转 | A反B正 |
| 60 | 调速 | 设置速度 60 |
| 80 | 调速 | 设置速度 80 |
| 79 | 退出 | 返回桌面模式 |

---

## OLED 表情库

小车内置 16 个眼睛表情 + 10 个情绪表情：

**眼睛表情** — \\$ / I0I / ioi / ff / YY / _3_ / ADA / D_D / _o_ / oDo / ODO / ovo / owo / uvu ...

**情绪表情** — 开心 / 报告 / 楚楚 / 完了 / 怒 / 嘻嘻 / 支持 / good ...

---

## 状态切换流程

         ┌──────────────┐
         │   睡眠模式    │ ←──── 15秒无触摸
         │  (电机关闭)  │
         └──────┬───────┘
                │ 触摸唤醒
         ┌──────▼───────┐
         │   桌面模式    │
         │  (待机显示)   │
         └──┬───────┬───┘
    短按触摸 │       │ 长按 3 秒
      ┌─────▼───┐ ┌──▼──────┐
      │ WiFi遥控 │ │ AI 模式 │
      │ (UDP)   │ │ (自主)  │
      └─────────┘ └─────────┘
     执行完毕自动返回桌面模式

---

## 项目结构

	able_car/
├── include/          # 头文件
│   ├── ai.h          # AI 行为决策
│   ├── animation.h   # 动画播放
│   ├── motor.h       # 电机驱动
│   ├── OLED.h        # 屏幕显示（含表情字典）
│   ├── system.h      # 状态机
│   ├── touch.h       # 触摸检测
│   └── wifi_udp.h    # WiFi/UDP 遥控
├── src/              # 源文件
│   ├── main.cpp      # 入口
│   ├── ai.cpp        # AI 核心逻辑
│   ├── animation.cpp # 动画引擎
│   ├── anim_welcome.cpp  # 欢迎动画帧数据
│   ├── anim_tosleep.cpp  # 入睡动画帧数据
│   ├── anim_sleep.cpp    # 睡眠动画帧数据
│   ├── image1.cpp    # 眼睛表情位图
│   ├── image2.cpp    # 情绪表情位图
│   ├── motor.cpp     # 电机控制
│   ├── OLED.cpp      # 屏幕绘制
│   ├── system.cpp    # 状态机实现
│   ├── touch.cpp     # 触摸检测
│   └── wifi.cpp      # WiFi/UDP 通信
├── app-debug.apk      # Android 遥控客户端 APK
├── test/README       # 详细技术文档
├── platformio.ini    # PlatformIO 配置
└── README.md         # 本文件

---

## 许可

本项目基于 MIT 协议开源。
