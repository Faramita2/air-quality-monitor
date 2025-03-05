#ifndef I2C_CONFIG_H
#define I2C_CONFIG_H

#include <Wire.h>

// 定义自定义 I2C 引脚
#define SDA_PIN 18 // 自定义 SDA 引脚
#define SCL_PIN 19 // 自定义 SCL 引脚

void initI2C(); // 初始化 I2C

#endif