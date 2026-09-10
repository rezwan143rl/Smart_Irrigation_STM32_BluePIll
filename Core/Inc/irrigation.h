#ifndef IRRIGATION_H
#define IRRIGATION_H
#include "stm32f1xx_hal.h"
#include "dht22.h"

#define SOIL_DRY_THRESHOLD     35
#define SOIL_WET_THRESHOLD     60
#define SOIL_COOLDOWN_CANCEL   65     // soil% that ends cooldown early
#define PUMP_MAX_RUNTIME_MS    3000
#define PUMP_COOLDOWN_MS       600000 // 10 minutes

typedef struct {
    uint8_t dht_failed;
    uint8_t soil_out_of_range;
} SensorFaults;

typedef enum { PUMP_STATE_NORMAL, PUMP_STATE_COOLDOWN } PumpState;

void Irrigation_Decide(uint8_t soil_pct, uint8_t water_low, uint8_t raining, uint8_t soil_fault, uint8_t *pump_should_run);
void Pump_SafeControl(uint8_t want_on, uint8_t soil_pct, uint8_t *timeout_flag, uint8_t *cooldown_active);
uint8_t SensorFaults_Check(uint16_t soil_raw, DHT22_Status dht_status, SensorFaults *faults);

#endif
