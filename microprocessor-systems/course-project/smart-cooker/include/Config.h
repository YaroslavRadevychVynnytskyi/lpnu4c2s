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

/** @brief Cooking temperature for rice in degrees Celsius */
#define RICE_COOKING_TEMP 100

/** @brief Searing temperature for meat in degrees Celsius */
#define SEARING_TEMP 180

/** @brief Stewing temperature for pork in degrees Celsius */
#define STEWING_TEMP 85

//------------------------------------------------------------------------------
// Time constants (in minutes)
//------------------------------------------------------------------------------

/** @brief Cooking time for soft-boiled eggs in minutes */
#define SOFT_BOILED_TIME 6

/** @brief Cooking time for hard-boiled eggs in minutes */
#define HARD_BOILED_TIME 12

/** @brief Cooking time for white rice in minutes */
#define WHITE_RICE_TIME 18

/** @brief Cooking time for brown rice in minutes */
#define BROWN_RICE_TIME 40

/** @brief Searing time for meat in minutes */
#define SEARING_TIME 5

/** @brief Stewing time for pork shoulder in minutes */
#define PORK_SHOULDER_TIME 120

/** @brief Stewing time for pork belly in minutes */
#define PORK_BELLY_TIME 90

/** @brief Stewing time for pork tenderloin in minutes */
#define PORK_TENDERLOIN_TIME 45

/** @brief Resting time after cooking in minutes */
#define RESTING_TIME 15 
