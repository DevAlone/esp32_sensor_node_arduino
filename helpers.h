#pragma once

#include <Arduino.h>
#include <esp_wifi.h>

String getMacAddress()
{
    uint8_t macAddr[6];
    esp_wifi_get_mac(ESP_IF_WIFI_STA, macAddr);
    char macAddrChr[18] = { 0 };
    sprintf(
        macAddrChr,
        "%02X:%02X:%02X:%02X:%02X:%02X",
        macAddr[0],
        macAddr[1],
        macAddr[2],
        macAddr[3],
        macAddr[4],
        macAddr[5]);
    return String(macAddrChr);
}
