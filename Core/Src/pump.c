
#include "pump.h"
#define RELAY_ACTIVE_LOW 1

void Pump_On(void)
{
#if RELAY_ACTIVE_LOW
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
#else
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
#endif
}
void Pump_Off(void)
{
#if RELAY_ACTIVE_LOW
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
#else
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
#endif
}
