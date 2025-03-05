#include "i2c_config.h"
#include <Wire.h>

void initI2C() { Wire.begin(SDA_PIN, SCL_PIN); }