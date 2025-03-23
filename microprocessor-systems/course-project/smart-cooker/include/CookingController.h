#pragma once

#include <Arduino.h>
#include "Enums.h"
#include "Config.h"
#include "BluetoothManager.h"
#include "TemperatureSensor.h"

/**
 * @file CookingController.h
 * @brief Main controller for cooking operations
 * 
 * This class coordinates all cooking operations, managing temperature 
 * control, time tracking, and program execution based on user commands.
 */

/**
 * @brief Class for controlling the cooking process
 * 
 * This class is the central controller of the Smart Cooker. It processes
 * user commands, manages cooking programs, controls the heating element,
 * and tracks cooking progress.
 */
class CookingController {
private:
    /** @brief Reference to the Bluetooth manager for communication */
    BluetoothManager& btManager;
    
    /** @brief Reference to the temperature sensor */
    TemperatureSensor& tempSensor;
    
    /** @brief Current temperature reading in degrees Celsius */
    float currentTemp = 0;
    
    /** @brief Target temperature in degrees Celsius */
    int setTemp = 0;
    
    /** @brief Target cooking time in minutes */
    int setTime = 0;
    
    /** @brief Flag indicating if cooking is in progress */
    bool cookingActive = false;
    
    /** @brief Timestamp when cooking started (in milliseconds) */
    unsigned long cookingStartTime = 0;
    
    /** @brief Selected egg doneness level for egg programs */
    EggDoneness eggDoneness = EGG_SOFT;
    
    /** @brief Flag indicating if target temperature has been reached */
    bool temperatureReached = false;

    /**
     * @brief Controls the relay based on current cooking state
     * 
     * This method manages the relay that controls the heating element,
     * turning it on or off based on the current temperature and cooking state.
     */
    void controlRelay();
    
    /**
     * @brief Updates the cooking status and sends progress information
     * 
     * This method tracks cooking progress, manages timers, and sends
     * status updates via Bluetooth.
     */
    void updateCookingStatus();
    
    /**
     * @brief Configures and starts the boiled eggs program
     * 
     * @param doneness The desired egg doneness level
     */
    void handleEggsProgram(EggDoneness doneness);

public:
    /**
     * @brief Constructor for CookingController
     * 
     * @param bt Reference to the Bluetooth manager
     * @param temp Reference to the temperature sensor
     */
    CookingController(BluetoothManager& bt, TemperatureSensor& temp);
    
    /**
     * @brief Initializes the cooking controller
     * 
     * Sets up GPIO pins and initial states for cooking operations.
     */
    void begin();
    
    /**
     * @brief Processes a command received via Bluetooth
     * 
     * Interprets and executes user commands to control the cooker.
     * 
     * @param command The command string to process
     */
    void processCommand(const String& command);
    
    /**
     * @brief Main update method to be called regularly in the loop
     * 
     * This method handles temperature readings, cooking status updates,
     * and relay control.
     */
    void update();
    
    /**
     * @brief Sets the target temperature
     * 
     * @param temp Target temperature in degrees Celsius
     */
    void setTargetTemperature(int temp);
    
    /**
     * @brief Sets the target cooking time
     * 
     * @param time Target time in minutes
     */
    void setTargetTime(int time);
    
    /**
     * @brief Turns off the cooker
     * 
     * Stops any active cooking and turns off the heating element.
     */
    void turnOff();
}; 
