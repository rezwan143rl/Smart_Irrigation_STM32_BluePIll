#include "irrigation.h"
#include "pump.h"

void Irrigation_Decide(uint8_t soil_pct, uint8_t water_low, uint8_t raining, uint8_t *pump_should_run)
{
    if (water_low) {
        *pump_should_run = 0;
    } else if (raining) {
        *pump_should_run = 0;
    } else if (soil_pct < SOIL_DRY_THRESHOLD) {
        *pump_should_run = 1;
    } else if (soil_pct >= SOIL_WET_THRESHOLD) {
        *pump_should_run = 0;
    }
}

void Pump_SafeControl(uint8_t want_on, uint8_t *timeout_flag)
{
    static uint32_t pump_start_tick = 0;
    static uint8_t pump_is_on = 0;
    uint32_t now = HAL_GetTick();

    if (want_on && !pump_is_on) {
        pump_start_tick = now;
        pump_is_on = 1;
        Pump_On();
    } else if (want_on && pump_is_on) {
        if ((now - pump_start_tick) >= PUMP_MAX_RUNTIME_MS) {
            Pump_Off();
            pump_is_on = 0;
            *timeout_flag = 1;
        }
    } else if (!want_on && pump_is_on) {
        Pump_Off();
        pump_is_on = 0;
    }
}
