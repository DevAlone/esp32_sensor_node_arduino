cmake_minimum_required(VERSION 3.7)

project(esp32_sensor_network_arduino)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(ARDUINO_DIR "/opt/arduino")
set(ARDUINO_LIBRARIES_DIR "/home/user/Arduino/libraries")

# INCLUDE(FindPkgConfig)

file(GLOB_RECURSE PROJECT_SOURCES
    "*.h"
    "*.hpp"
    "*.cpp"
    "*.ino"

    "${ARDUINO_DIR}/libraries/*.cpp"
    "${ARDUINO_DIR}/hardware/arduino/avr/cores/arduino/*.cpp"
    "${ARDUINO_DIR}/hardware/arduino/avr/libraries/SPI/src/*.cpp"
    "${ARDUINO_DIR}/hardware/arduino/avr/libraries/EEPROM/src/*.cpp"
    "${ARDUINO_DIR}/hardware/tools/avr/avr/include/*.cpp"
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

include_directories(
    "${ARDUINO_DIR}/libraries/"
    "/home/user/.arduino15/packages/esp32/hardware/esp32/1.0.1/libraries/WiFi/src/"
    "/home/user/.arduino15/packages/esp32/hardware/esp32/1.0.1/libraries/HTTPClient/src/"
    "/home/user/.arduino15/packages/esp32/hardware/esp32/1.0.1/tools/sdk/include/esp32/"
    "${ARDUINO_DIR}/libraries/Bridge/src/"
    "${ARDUINO_DIR}/libraries/WiFi/src/"
    "${ARDUINO_DIR}/hardware/arduino/avr/cores/arduino/"
    "${ARDUINO_DIR}/hardware/arduino/avr/libraries/SPI/src/"
    "${ARDUINO_DIR}/hardware/arduino/avr/libraries/EEPROM/src/"
    "${ARDUINO_DIR}/hardware/tools/avr/avr/include/"

    "${ARDUINO_DIR}/opt/arduino/hardware/arduino/avr/variants/standard/"
#     "/opt/arduino/hardware/arduino/avr/variants/micro/"
#     "/opt/arduino/hardware/arduino/avr/variants/yun/"
#     "/opt/arduino/hardware/arduino/avr/variants/circuitplay32u4/"
#     "/opt/arduino/hardware/arduino/avr/variants/leonardo/"
#     "/opt/arduino/hardware/arduino/avr/variants/gemma/"
#     "/opt/arduino/hardware/arduino/avr/variants/robot_control/"
#     "/opt/arduino/hardware/arduino/avr/variants/robot_motor/"
#     "/opt/arduino/hardware/arduino/avr/variants/ethernet/"
#     "/opt/arduino/hardware/arduino/avr/variants/mega/"
#     "/opt/arduino/hardware/arduino/avr/variants/eightanaloginputs/"

    "${ARDUINO_LIBRARIES_DIR}"
    "${ARDUINO_LIBRARIES_DIR}/RF24"
    "${ARDUINO_LIBRARIES_DIR}/RF24/utility/"
    "${ARDUINO_LIBRARIES_DIR}/RF24Network"
    "${ARDUINO_LIBRARIES_DIR}/RF24Mesh"
    "${ARDUINO_LIBRARIES_DIR}/DHT_sensor_library_for_ESPx"
)

# target_link_libraries(${PROJECT_NAME})
