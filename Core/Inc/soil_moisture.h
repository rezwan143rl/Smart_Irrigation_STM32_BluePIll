#ifndef SOIL_MOISTURE_H
#define SOIL_MOISTURE_H
#include "stm32f1xx_hal.h"

#define SOIL_ADC_DRY   3300
#define SOIL_ADC_WET   3000

uint8_t Soil_ToPercent(uint16_t raw);

#endif
