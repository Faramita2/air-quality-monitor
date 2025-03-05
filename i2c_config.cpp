#include "i2c_config.h"

void initI2C() {
  Wire.begin(SDA_PIN, SCL_PIN); // 初始化 I2C，指定自定义引脚
}