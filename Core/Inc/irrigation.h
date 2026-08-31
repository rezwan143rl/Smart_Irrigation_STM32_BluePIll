#ifndef IRRIGATION_H
#define IRRIGATION_H
#include "stm32f1xx_hal.h"

#define SOIL_DRY_THRESHOLD   35
#define SOIL_WET_THRESHOLD   60
#define PUMP_MAX_RUNTIME_MS  100000

void Irrigation_Decide(uint8_t soil_pct, uint8_t water_low, uint8_t raining, uint8_t *pump_should_run);
void Pump_SafeControl(uint8_t want_on, uint8_t *timeout_flag);

#endif
