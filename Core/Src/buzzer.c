
#include "buzzer.h"
void Buzzer_On(void)  { HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET); }
void Buzzer_Off(void) { HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET); }

void StatusLED_OK(uint8_t on) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, on ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
void StatusLED_Warning(uint8_t on) {
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, on ? GPIO_PIN_RESET : GPIO_PIN_SET);
}
