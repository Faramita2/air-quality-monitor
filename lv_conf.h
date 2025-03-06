// lv_conf.h

#if 1 /*Set it to "1" to enable content*/

#ifndef LV_CONF_H
#define LV_CONF_H

// 16-bit 颜色 (RGB565)
#define LV_COLOR_DEPTH 16
// 水平分辨率
#define LV_HOR_RES_MAX 480
// 垂直分辨率
#define LV_VER_RES_MAX 320

// 启用日志
#define LV_USE_LOG 1
#define LV_LOG_LEVEL LV_LOG_LEVEL_INFO

// 自定义滴答
#define LV_TICK_CUSTOM 1
#define LV_TICK_CUSTOM_INCLUDE "Arduino.h"
#define LV_TICK_CUSTOM_SYS_TIME_EXPR (millis())

// 启用示例小部件（可选）
#define LV_USE_DEMO_WIDGETS 1

#endif /*LV_CONF_H*/
#endif /*End of content*/