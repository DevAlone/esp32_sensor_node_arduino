#include "config.h"
#include "globals.h"
#include "helpers.h"
#include "logger.h"
#include "process_sensors.h"

#include <Arduino.h>
#include <DHTesp.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <WiFiMulti.h>

static WiFiMulti wifiMulti;

void setup()
{
    logger::init();
    dhtSensor.setup(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);
    logger::info("esp32_sensor_node started");

    wifiMulti.addAP(ROUTER_SSID, ROUTER_PASSWORD);
}

bool sendSensorsData()
{
    bool result = false;
    HTTPClient http;

    logger::info("[HTTP] begin...");

    if (USE_HTTPS) {
        http.begin(String("https://") + SERVER_DOMAIN + "/api/v1/push_sensors_data", HTTPS_CERTIFICATE);
    } else {
        http.begin(String("http://") + SERVER_DOMAIN + "/api/v1/push_sensors_data");
    }

    String macAddr = getMacAddress();

    String postData = String("{")
        + quoteSymbol + "username" + quoteSymbol + ": " + quoteSymbol + SERVER_USERNAME + quoteSymbol + ","
        + quoteSymbol + "password" + quoteSymbol + ": " + quoteSymbol + SERVER_PASSWORD + quoteSymbol + ","
        + quoteSymbol + "node_mac_address" + quoteSymbol + ": " + quoteSymbol + macAddr + +quoteSymbol + ","
        + quoteSymbol + "sensors_data" + quoteSymbol + ": " + getSensorsDataJSON()
        + "}";

    logger::info("[HTTP] POST...\n");
    int httpCode = http.POST(postData);

    if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        logger::info("[HTTP] GET... code: %d", httpCode);
        String data = http.getString();
        logger::info("[HTTP] GET... data: %s", data);

        if (httpCode == HTTP_CODE_OK) {
            result = true;
        } else {
            logger::info("[HTTP] GET... failed, error: %s", http.errorToString(httpCode).c_str());
        }
    } else {
        logger::info("[HTTP] GET... failed, error: %s", http.errorToString(httpCode).c_str());
    }

    http.end();
    return result;
}

void loop()
{
    // wait for WiFi connection
    if (wifiMulti.run() == WL_CONNECTED) {
        auto wasSentSuccessfully = sendSensorsData();
        if (wasSentSuccessfully) {
            // TODO: go to deep sleep
        }
    }

    delay(min(
        SEND_DATA_DELAY_MS,
        dhtSensor.getMinimumSamplingPeriod()));
}
