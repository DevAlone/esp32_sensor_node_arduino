#pragma once

#include "config.h"

#include <Arduino.h>

namespace logger {

inline void init()
{
    Serial.begin(SERIAL_PORT_SPEED);
}

template <typename... Targs>
void log(const char* level, const char* format, Targs... args)
{
    // TODO: add time
    Serial.print(level);
    Serial.print(" ");
    Serial.printf(format, args...);
    Serial.println();
}

template <typename... Targs>
void error(const char* format, Targs... args)
{
    log("ERR", format, args...);
}

template <typename... Targs>
void info(const char* format, Targs... args)
{
    log("INF", format, args...);
}
}
