#include "dht22.h"

static TIM_HandleTypeDef *dht_tim;

void DHT22_InitTimer(TIM_HandleTypeDef *htim)
{
    dht_tim = htim;
    HAL_TIM_Base_Start(dht_tim);
}

static void DHT22_DelayUs(uint16_t us)
{
    __HAL_TIM_SET_COUNTER(dht_tim, 0);
    while (__HAL_TIM_GET_COUNTER(dht_tim) < us)
        ;
}

static void DHT22_SetPin(GPIO_PinState state)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, state);
}

static GPIO_PinState DHT22_ReadPin(void)
{
    return HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12);
}

DHT22_Status DHT22_Read(float *temperature, float *humidity) {
    uint8_t data[5] = {0, 0, 0, 0, 0};
    uint32_t timeout;

    DHT22_SetPin(GPIO_PIN_RESET);
    HAL_Delay(20);              // changed from 2ms -> 20ms for DHT11
    DHT22_SetPin(GPIO_PIN_SET);
    DHT22_DelayUs(30);

    timeout = 0;
    while (DHT22_ReadPin() == GPIO_PIN_SET) {
        if (++timeout > 100) return DHT22_ERR_TIMEOUT;
        DHT22_DelayUs(1);
    }
    timeout = 0;
    while (DHT22_ReadPin() == GPIO_PIN_RESET) {
        if (++timeout > 100) return DHT22_ERR_TIMEOUT;
        DHT22_DelayUs(1);
    }
    timeout = 0;
    while (DHT22_ReadPin() == GPIO_PIN_SET) {
        if (++timeout > 100) return DHT22_ERR_TIMEOUT;
        DHT22_DelayUs(1);
    }

    for (uint8_t i = 0; i < 40; i++) {
        timeout = 0;
        while (DHT22_ReadPin() == GPIO_PIN_RESET) {
            if (++timeout > 100) return DHT22_ERR_TIMEOUT;
            DHT22_DelayUs(1);
        }
        DHT22_DelayUs(40);
        GPIO_PinState bit_val = DHT22_ReadPin();

        timeout = 0;
        while (DHT22_ReadPin() == GPIO_PIN_SET) {
            if (++timeout > 100) return DHT22_ERR_TIMEOUT;
            DHT22_DelayUs(1);
        }

        data[i / 8] <<= 1;
        if (bit_val == GPIO_PIN_SET) data[i / 8] |= 1;
    }

    uint8_t checksum = data[0] + data[1] + data[2] + data[3];
    if (checksum != data[4]) return DHT22_ERR_CHECKSUM;

    // --- DHT11 decoding: integer bytes directly, no /10 scaling ---
    *humidity = (float)data[0];
    *temperature = (float)data[2];

    return DHT22_OK;
}
