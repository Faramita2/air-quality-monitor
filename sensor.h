#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

void initSensor();
float readTemperature();
float readHumidity();

#endif