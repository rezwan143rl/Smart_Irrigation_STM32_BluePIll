#ifndef DISPLAY_SCREENS_H
#define DISPLAY_SCREENS_H
#include "stm32f1xx_hal.h"

typedef struct {
    uint8_t soil_pct;
    uint8_t water_low;
    uint8_t raining;
    float temp;
    float hum;
    uint8_t dht_ok;
    uint8_t pump_on;
    uint8_t manual_mode;
    uint8_t warning;
    uint8_t cooldown_active;
    uint8_t sensor_fault;
} SystemStatus;

void Display_ShowScreen(uint8_t screen_index, SystemStatus *status);
#define DISPLAY_NUM_SCREENS 3

#endif
