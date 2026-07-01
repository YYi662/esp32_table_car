# 桌面智能小车 - ESP32 Desktop Smart Car

<div align="center">

![ESP32](https://img.shields.io/badge/ESP32-arduino-00979D?style=flat-square)
![PlatformIO](https://img.shields.io/badge/PlatformIO-IDE-FF6600?style=flat-square)
![OLED](https://img.shields.io/badge/OLED-SSD1306-00FF00?style=flat-square)
![License](https://img.shields.io/badge/license-MIT-blue?style=flat-square)

**一个基于 ESP32 的桌面智能小车，具备 自主行为、WiFi 遥控、OLED 表情动画等能力。**

</div>

---

## 功能特色

| 功能 | 说明 |
|------|------|
| **自主行为** | 模拟生物动机系统（舒适欲/探索欲/焦躁欲），自主决策行为与表情 |
| **WiFi 遥控** | ESP32 开热点，手机 UDP 连接，实时操控小车运动 |
| **触摸交互** | 电容触摸传感器，支持短按/长按，切换工作模式 |
| **OLED 表情屏** | 128×64 像素，多种表情、图标、逐帧动画 |
| **睡眠节能** | 15 秒无操作自动入睡，触摸唤醒 |
| **低功耗设计** | WiFi 功率限制为 2dBm，降低热点功耗 |

---

## 硬件配置

### 引脚分配

| 引脚 | 功能 |
|------|------|
| GPIO27 / GPIO26 | 电机 A 正反转（IN1/IN2） |
| GPIO32 / GPIO33 | 电机 B 正反转（IN3/IN4） |
| GPIO4 | 电容触摸输入 |
| GPIO17 (SDA) / GPIO16 (SCL) | OLED I2C 通信 |

### 所需硬件

- ESP32 开发板（ESP32 Dev Module）
- 双路直流电机驱动板（L298N 或类似）
- SSD1306 128×64 OLED 屏幕（I2C 接口）
- 电容触摸传感器 / 触摸弹簧
- 小车底盘 + 轮子 + 电池

---

## 快速开始

### 环境要求

- [PlatformIO IDE](https://platformio.org/)（VS Code 扩展）
- 或 Arduino IDE + ESP32 支持包

### 编译 & 烧录

pash
 - git clone https://github.com/YYi662/esp32_table_car.git
  - cd esp32_table_car
  - pio run --target upload


项目会自动从 PlatformIO 库安装依赖 olikraus/U8g2（OLED 驱动）。

### 配套手机 App

项目根目录附带 app-debug.apk，安装到 Android 手机后通过 WiFi 热点控制小车。

---


---

##  探索行为系统

### 三层动机模型

小车像生物一样有"欲望"，它们会随时间自然波动：

| 动机 | 变量 | 影响 |
|------|------|------|
| 舒适欲 | m_comfort | 越高越想静止、开心 |
| 探索欲 | m_explore | 越高越想移动、探索 |
| 焦躁欲 | m_agitation | 越高越不安、乱转 |

### 五种情绪 → 六种行为

动机计算出当前**情绪**，情绪决定行为**权重表**，轮盘赌算法随机选行为：

| 情绪 | 触发条件 | 典型行为 |
|------|----------|----------|
| 😐 发呆 | 默认 | 停止、小幅表情变化 |
| 😊 开心 | 舒适>60 且 焦躁<45 | 平稳前进、柔和转弯 |
| 🤔 好奇 | 探索>60 且 舒适<58 | 频繁转向、快速移动 |
| 😰 不安 | 焦躁>62 | 后退、警惕停顿 |
| 😡 烦躁 | 焦躁>60 且 舒适<40 | 快速转身、暴走后退 |

**行为类型**：转身 / 侧身 / 前进 / 后退 / 表情变化 / 发呆


---

## WiFi 遥控

1. 短按触摸 → 进入 **WiFi 遥控模式**
2. 手机连接热点 ESP32_Car（密码 12345678）
3. 用 UDP 调试工具向 192.168.4.1:8888 发送指令：

| 指令 | 动作 | 说明 |
|------|------|------|
| 前进 | 前进 | 双电机正转 |
| 后退 | 后退 | 双电机反转 |
| 左转 | 左转 | A 正 B 反 |
| 右转 | 右转 | A 反 B 正 |
| 速度 | 调速 | 设置速度为 60\80 |
| F1 | 退出 | 返回桌面模式 |
| F3 | 切换 | 切换为探索模式 |

---

## OLED 表情库

小车内置 16 个眼睛表情 + 10 个情绪表情：

**眼睛表情** — \\$ I0I ioi f YY _3_ ADA D_D _o_ oDo ODO ovo owo uvu ...

**情绪表情** — 开心 / 报告 / 楚楚 / 完了 / 怒 / 嘻嘻 / 支持 / good ...

---


---

## 许可

本项目基于 MIT 协议开源。
