#pragma once

/**
 * @file Config.h
 * @brief Configuration constants and pin definitions for the Smart Cooker
 * 
 * This file contains all the hardware-related constants and configuration
 * settings used throughout the application. Centralizing these values makes
 * it easier to adapt the code to different hardware configurations.
 */

//------------------------------------------------------------------------------
// Pin Definitions
//------------------------------------------------------------------------------

/** @brief GPIO pin connected to the relay module for heating element control */
#define RELAY_PIN 23

/** @brief GPIO pin connected to the DS18B20 temperature sensor */
#define DS18B20_PIN 4

//------------------------------------------------------------------------------
// Temperature constants (in Celsius)
//------------------------------------------------------------------------------

/** @brief Boiling temperature of water in degrees Celsius */
#define BOILING_TEMP 100

//------------------------------------------------------------------------------
// Time constants (in minutes)
//------------------------------------------------------------------------------

/** @brief Cooking time for soft-boiled eggs in minutes */
#define SOFT_BOILED_TIME 6

/** @brief Cooking time for hard-boiled eggs in minutes */
#define HARD_BOILED_TIME 12 
