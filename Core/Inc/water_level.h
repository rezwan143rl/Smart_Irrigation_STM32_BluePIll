
#ifndef WATER_LEVEL_H
#define WATER_LEVEL_H
#include "stm32f1xx_hal.h"

#define WATER_LEVEL_LOW_RAW   1500

uint8_t WaterLevel_IsLow(uint16_t raw);
#endif
