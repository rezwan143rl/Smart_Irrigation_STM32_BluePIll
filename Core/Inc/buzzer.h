
#ifndef BUZZER_H
#define BUZZER_H
#include "stm32f1xx_hal.h"
void Buzzer_On(void);
void Buzzer_Off(void);
void StatusLED_OK(uint8_t on);
void StatusLED_Warning(uint8_t on);
#endif
