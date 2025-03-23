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
    CMD_BOILED_EGGS, /**< Start boiled eggs program command */
    CMD_RICE,        /**< Start rice cooking program command */
    CMD_STEWED_PORK  /**< Start stewed pork program command */
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

/**
 * @brief Enumeration for rice types
 * 
 * These values define the different types of rice that can be cooked,
 * which correspond to different cooking times and instructions.
 */
enum RiceType {
    RICE_WHITE = 1,  /**< White rice (shorter cooking time) */
    RICE_BROWN = 2   /**< Brown rice (longer cooking time) */
};

/**
 * @brief Enumeration for pork cut types
 * 
 * These values define the different cuts of pork that can be stewed,
 * which correspond to different cooking times and temperatures.
 */
enum PorkCutType {
    PORK_SHOULDER = 1,   /**< Pork shoulder (longer cooking time) */
    PORK_BELLY = 2,      /**< Pork belly (medium cooking time) */
    PORK_TENDERLOIN = 3  /**< Pork tenderloin (shorter cooking time) */
};

/**
 * @brief Enumeration for cooking phase
 * 
 * These values define the different phases of cooking for multi-phase recipes.
 */
enum CookingPhase {
    PHASE_SEARING = 1,   /**< High-temperature searing phase */
    PHASE_COOKING = 2,   /**< Main cooking phase */
    PHASE_RESTING = 3    /**< Final resting phase */
}; 
