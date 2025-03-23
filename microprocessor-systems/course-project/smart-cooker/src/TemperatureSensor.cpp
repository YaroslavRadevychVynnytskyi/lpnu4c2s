#include "TemperatureSensor.h"

/**
 * @brief Constructor for TemperatureSensor class
 * 
 * Initializes the OneWire and DallasTemperature objects with the
 * DS18B20_PIN defined in Config.h.
 */
TemperatureSensor::TemperatureSensor() 
    : oneWire(DS18B20_PIN), sensors(&oneWire) {
}

/**
 * @brief Initializes the temperature sensor
 * 
 * Calls the begin() method of the DallasTemperature library to
 * start communication with the DS18B20 sensor.
 */
void TemperatureSensor::begin() {
    sensors.begin();
}

/**
 * @brief Reads the current temperature from the sensor
 * 
 * Sends a command to the DS18B20 sensor to perform a temperature
 * conversion and returns the temperature in degrees Celsius.
 * 
 * @return float Current temperature in degrees Celsius
 */
float TemperatureSensor::readTemperature() {
    sensors.requestTemperatures(); // Send command to get temperatures
    return sensors.getTempCByIndex(0); // Get temperature in Celsius
} 
