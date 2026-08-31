#ifndef DHT22_H
#define DHT22_H

#include "stm32f1xx_hal.h"

typedef enum {
    DHT22_OK = 0,
    DHT22_ERR_TIMEOUT,
    DHT22_ERR_CHECKSUM
} DHT22_Status;

void DHT22_InitTimer(TIM_HandleTypeDef *htim);
DHT22_Status DHT22_Read(float *temperature, float *humidity);

#endif
