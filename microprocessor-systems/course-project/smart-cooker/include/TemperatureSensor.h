#pragma once

#include <OneWire.h>
#include <DallasTemperature.h>
#include "Config.h"

/**
 * @file TemperatureSensor.h
 * @brief Temperature sensor management class
 * 
 * This class encapsulates the functionality of the DS18B20 temperature sensor
 * and provides methods to initialize the sensor and read temperature values.
 */

/**
 * @brief Class for managing the DS18B20 temperature sensor
 * 
 * This class handles the communication with the DS18B20 temperature sensor
 * via the OneWire protocol. It provides methods to initialize the sensor and
 * read current temperature values in degrees Celsius.
 */
class TemperatureSensor {
private:
    /** @brief OneWire communication object for the DS18B20 sensor */
    OneWire oneWire;
    
    /** @brief DallasTemperature library object for sensor management */
    DallasTemperature sensors;

public:
    /**
     * @brief Constructor for TemperatureSensor class
     * 
     * Initializes the OneWire and DallasTemperature objects with the
     * appropriate pin configuration from Config.h.
     */
    TemperatureSensor();
    
    /**
     * @brief Initializes the temperature sensor
     * 
     * This method must be called once during setup to initialize the DS18B20 sensor.
     */
    void begin();
    
    /**
     * @brief Reads the current temperature from the sensor
     * 
     * @return float Current temperature in degrees Celsius
     */
    float readTemperature();
}; 
