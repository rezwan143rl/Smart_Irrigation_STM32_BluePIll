#include "soil_moisture.h"

uint8_t Soil_ToPercent(uint16_t raw)
{
    uint16_t dry = SOIL_ADC_DRY;
    uint16_t wet = SOIL_ADC_WET;
    int32_t pct;

    if (dry > wet) {
        if (raw > dry) raw = dry;
        if (raw < wet) raw = wet;
        pct = (int32_t)(dry - raw) * 100 / (dry - wet);
    } else {
        if (raw < dry) raw = dry;
        if (raw > wet) raw = wet;
        pct = (int32_t)(raw - dry) * 100 / (wet - dry);
    }
    return (uint8_t)pct;
}
