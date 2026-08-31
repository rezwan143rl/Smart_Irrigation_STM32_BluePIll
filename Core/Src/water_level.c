
#include "water_level.h"
uint8_t WaterLevel_IsLow(uint16_t raw) {
    return (raw < WATER_LEVEL_LOW_RAW) ? 1 : 0;
}
