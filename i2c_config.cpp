#include "i2c_config.h"
#include <Wire.h>

bool initI2C() {
  Wire.begin(SDA_PIN, SCL_PIN);
  return true;
}