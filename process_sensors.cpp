#include "process_sensors.h"

#include "config.h"
#include "globals.h"
#include "logger.h"

template <typename T>
String makeSensorDataString(
    const String& type,
    uint8_t pin,
    unsigned long timestampMs,
    const T& value)
{
    String result = "{";
    result += String(R"("status":"ok",)");
    result += String(R"("type":")") + type + "\",";
    result += String(R"("pin":)") + String(pin) + ",";
    result += String(R"("timestamp_ms":)") + String(timestampMs) + ",";
    result += String(R"("value":)") + String(value);
    result += "}";
    return result;
}

String makeSensorDataErrorString(
    const String& errorMessage, int errorCode)
{
    String result = "{";
    result += String(R"("status":"error",)");
    result += String(R"("error_message":")") + errorMessage + "\",";
    result += String(R"("error_code":")") + String(errorCode) + "\"";
    result += "}";
    return result;
}

String getSensorsDataJSON()
{
    String result = "[";

    // DHT11
    auto tempAndHumidity = dhtSensor.getTempAndHumidity();

    if (dhtSensor.getStatus() != DHTesp::DHT_ERROR_t::ERROR_NONE) {
        logger::error(
            "process_sensors.cpp: error during reading dht sernsor. Error meesage: %s. Temp: %f. Humidity: %f",
            dhtSensor.getStatusString(),
            tempAndHumidity.temperature,
            tempAndHumidity.humidity);
        result += makeSensorDataErrorString(
            String("failed to read data from sensor ") + dhtSensor.getStatusString(),
            dhtSensor.getStatus());
    } else {
        logger::info(
            "temperature: %f, humidity: %f",
            tempAndHumidity.temperature,
            tempAndHumidity.humidity);
        String value = "{";
        value += R"("temperature_c":)" + String(tempAndHumidity.temperature) + ",";
        value += R"("humidity":)" + String(tempAndHumidity.humidity) + "";
        value += "}";

        result += makeSensorDataString(
            "dht",
            DHT_SENSOR_PIN,
            millis(),
            value);
    }
    // / DHT11

    result += "]";
    return result;
}
