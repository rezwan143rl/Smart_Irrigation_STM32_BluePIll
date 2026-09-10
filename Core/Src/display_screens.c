#include "display_screens.h"
#include "ssd1306.h"
#include <stdio.h>

void Display_ShowScreen(uint8_t screen_index, SystemStatus *status)
{
    SSD1306_Clear();
    char line1[20], line2[20];

    switch (screen_index) {
        case 0: // Sensor readings
            sprintf(line1, "Soil:%3d%% Water:%s", status->soil_pct, status->water_low ? "LOW" : "OK ");
            SSD1306_SetCursor(0, 0);
            SSD1306_WriteString(line1);

            if (status->dht_ok)
                sprintf(line2, "T:%2d H:%2d%%", (int)status->temp, (int)status->hum);
            else
                sprintf(line2, "DHT ERR");
            SSD1306_SetCursor(0, 16);
            SSD1306_WriteString(line2);
            break;

        case 1: // System status
            sprintf(line1, "RAIN:%s PUMP:%s", status->raining ? "YES" : "NO", status->pump_on ? "ON" : "OFF");
            SSD1306_SetCursor(0, 0);
            SSD1306_WriteString(line1);

            //sprintf(line2, "MODE:%s", status->manual_mode ? "MANUAL" : "AUTO");
            //SSD1306_SetCursor(0, 16);
            //SSD1306_WriteString(line2);
            break;

        case 2: // Warning screen
            if (status->warning) {
                SSD1306_SetCursor(0, 0);
                SSD1306_WriteString("WARNING!");
                SSD1306_SetCursor(0, 16);
                if (status->water_low)
                    SSD1306_WriteString("WATER LOW");
                else if (status->cooldown_active)
                    SSD1306_WriteString("PUMP COOLDOWN");
                else if (status->sensor_fault)
                    SSD1306_WriteString("SENSOR FAULT");
                else
                    SSD1306_WriteString("PUMP TIMEOUT");
            } else {
                SSD1306_SetCursor(0, 0);
                SSD1306_WriteString("SYSTEM OK");
            }
            break;
    }

    SSD1306_UpdateScreen();
}
