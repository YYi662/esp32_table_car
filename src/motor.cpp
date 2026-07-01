#include "motor.h"
#include "system.h"


//开始时间
unsigned long startA_time = 0;
unsigned long startB_time = 0;
//电机每次运行的最少时间
unsigned long runA_time = 0;
unsigned long runB_time = 0;











//初始化
void motorInit() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  motorA_stop();
  motorB_stop();
}

// 电机 A
void motorA_forward(int speed,unsigned long ms) {
  analogWrite(IN1, speed);
  digitalWrite(IN2, LOW);
  startA_time = millis();
  runA_time = ms;
}

void motorA_backward(int speed,unsigned long ms) {
  digitalWrite(IN1, LOW);
  analogWrite(IN2, speed);
  startA_time = millis();
  runA_time = ms;
}

void motorA_stop() {
  analogWrite(IN1, 0);
  analogWrite(IN2, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

// 检查：时间到就停（非阻塞）
void motorA_check() {
  
  if (runA_time == 0) return;

  if (millis() - startA_time >= runA_time) {
    motorA_stop();
    runA_time = 0;
  }
}


// 电机 B
void motorB_forward(int speed,unsigned long ms) {
  analogWrite(IN3, speed);
  digitalWrite(IN4, LOW);
  startB_time = millis();
  runB_time = ms;
}

void motorB_backward(int speed,unsigned long ms) {
  digitalWrite(IN3, LOW);
  analogWrite(IN4, speed);
  startB_time = millis();
  runB_time = ms;
}


void motorB_stop() {
  analogWrite(IN3, 0);
  analogWrite(IN4, 0);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// 检查：时间到就停（非阻塞）
void motorB_check() {
  if (runB_time == 0) return;

  if (millis() - startB_time >= runB_time) {
    motorB_stop();
    runB_time = 0;
  }
}

