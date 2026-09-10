#include "irrigation.h"
#include "pump.h"

void Irrigation_Decide(uint8_t soil_pct, uint8_t water_low, uint8_t raining, uint8_t soil_fault, uint8_t *pump_should_run)
{
    if (water_low) {
        *pump_should_run = 0;
    } else if (raining) {
        *pump_should_run = 0;
    } else if (soil_fault) {
        *pump_should_run = 0;
    } else if (soil_pct < SOIL_DRY_THRESHOLD) {
        *pump_should_run = 1;
    } else if (soil_pct >= SOIL_WET_THRESHOLD) {
        *pump_should_run = 0;
    }
}

void Pump_SafeControl(uint8_t want_on, uint8_t soil_pct, uint8_t *timeout_flag, uint8_t *cooldown_active)
{
    static PumpState state = PUMP_STATE_NORMAL;
    static uint32_t pump_start_tick = 0;
    static uint32_t cooldown_start_tick = 0;
    static uint8_t pump_is_on = 0;

    uint32_t now = HAL_GetTick();

    if (state == PUMP_STATE_COOLDOWN) {
        if (pump_is_on) {
            Pump_Off();
            pump_is_on = 0;
        }

        uint8_t cooldown_elapsed = (now - cooldown_start_tick) >= PUMP_COOLDOWN_MS;
        uint8_t soil_recovered   = (soil_pct >= SOIL_COOLDOWN_CANCEL);

        if (cooldown_elapsed || soil_recovered) {
            state = PUMP_STATE_NORMAL;
        }

        *cooldown_active = 1;
        return;
    }

    *cooldown_active = 0;

    if (want_on && !pump_is_on) {
        pump_start_tick = now;
        pump_is_on = 1;
        Pump_On();
    } else if (want_on && pump_is_on) {
        if ((now - pump_start_tick) >= PUMP_MAX_RUNTIME_MS) {
            Pump_Off();
            pump_is_on = 0;
            *timeout_flag = 1;
            state = PUMP_STATE_COOLDOWN;
            cooldown_start_tick = now;
        }
    } else if (!want_on && pump_is_on) {
        Pump_Off();
        pump_is_on = 0;
    }
}
uint8_t SensorFaults_Check(uint16_t soil_raw, DHT22_Status dht_status, SensorFaults *faults)
{
    faults->dht_failed = (dht_status != DHT22_OK);
    faults->soil_out_of_range = (soil_raw == 0 || soil_raw >= 4095);
    return (faults->dht_failed || faults->soil_out_of_range);
}
