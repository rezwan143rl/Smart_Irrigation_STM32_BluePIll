
#include "rain_sensor.h"
uint8_t RainSensor_IsRaining(void)
{
    // LOW when rain , HIGH  dry
    return (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_RESET) ? 1 : 0;
}
