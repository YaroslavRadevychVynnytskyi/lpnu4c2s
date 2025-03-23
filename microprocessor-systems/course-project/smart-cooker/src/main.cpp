/**
 * @file main.cpp
 * @brief Main application entry point for Smart Cooker
 * 
 * This file contains the setup and loop functions that initialize
 * the system components and handle the main execution flow.
 */

#include <Arduino.h>
#include "BluetoothManager.h"
#include "TemperatureSensor.h"
#include "CookingController.h"

BluetoothManager btManager;
TemperatureSensor tempSensor;
CookingController cookingController(btManager, tempSensor);

/**
 * @brief Setup function that runs once at startup
 * 
 * Initializes all system components including Serial communication,
 * Bluetooth, temperature sensor, and the cooking controller.
 */
void setup() {
    Serial.begin(115200);
    Serial.println("Smart Cooker starting up...");

    btManager.begin();
    tempSensor.begin();
    cookingController.begin();
    
    Serial.println("Smart Cooker initialized successfully");
}

/**
 * @brief Main loop function that runs repeatedly
 * 
 * Checks for incoming Bluetooth commands, updates the cooking controller,
 * and maintains a regular execution cycle with a short delay.
 */
void loop() {
    if (btManager.available()) {
        String command = btManager.readCommand();
        cookingController.processCommand(command);
    }
    
    cookingController.update();
    delay(1000);
}
