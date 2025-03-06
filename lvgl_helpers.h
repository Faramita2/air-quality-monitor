// lvgl_helpers.h

#ifndef LVGL_HELPERS_H
#define LVGL_HELPERS_H

#include <cstdio>
#include <lvgl.h>

void display_text(const char *text, int x, int y, lv_color_t color);

void update_sht31_sensor_data(float temperature, float humidity);

#endif