#pragma once

#include <Arduino.h>

/**
 * @file Enums.h
 * @brief Common enumeration definitions for the Smart Cooker
 * 
 * This file defines various enumeration types used throughout the application,
 * including command types and cooking mode settings.
 */

/**
 * @brief Enumeration of command types received via Bluetooth
 * 
 * These values determine how the incoming command strings are interpreted
 * and processed by the cooking controller.
 */
enum CommandType {
    CMD_UNKNOWN,     /**< Unknown or invalid command */
    CMD_SET_TEMP,    /**< Set target temperature command */
    CMD_SET_TIME,    /**< Set target cooking time command */
    CMD_STATUS,      /**< Request current status command */
    CMD_OFF,         /**< Turn off cooker command */
    CMD_BOILED_EGGS  /**< Start boiled eggs program command */
};

/**
 * @brief Enumeration for egg doneness levels
 * 
 * These values define the different doneness levels for eggs,
 * which correspond to different cooking times at boiling temperature.
 */
enum EggDoneness {
    EGG_SOFT = 1,    /**< Soft-boiled eggs (runny yolk) */
    EGG_HARD = 2     /**< Hard-boiled eggs (fully cooked yolk) */
}; 
