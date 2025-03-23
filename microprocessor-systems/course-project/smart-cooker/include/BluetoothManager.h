#pragma once

#include <BluetoothSerial.h>
#include "Enums.h"

/**
 * @file BluetoothManager.h
 * @brief Bluetooth communication management
 * 
 * This class handles the Bluetooth Serial communication for the Smart Cooker,
 * providing methods to send and receive commands via Bluetooth.
 */

/**
 * @brief Class for handling Bluetooth communication
 * 
 * This class encapsulates the BluetoothSerial functionality, providing methods
 * to initialize Bluetooth, read and parse commands, and send messages back to
 * the connected device.
 */
class BluetoothManager {
private:
    /** @brief BluetoothSerial instance for handling communication */
    BluetoothSerial serialBT;
    
    /** @brief Bluetooth device name that will be visible to other devices */
    const char* deviceName = "SmartCooker";

public:
    /**
     * @brief Constructor for BluetoothManager
     */
    BluetoothManager();
    
    /**
     * @brief Initializes the Bluetooth Serial communication
     * 
     * @return bool True if initialization was successful, false otherwise
     */
    bool begin();
    
    /**
     * @brief Checks if Bluetooth data is available to read
     * 
     * @return bool True if data is available, false otherwise
     */
    bool available();
    
    /**
     * @brief Reads a command string from Bluetooth
     * 
     * Reads characters from the Bluetooth serial buffer until a newline
     * character is encountered.
     * 
     * @return String The command string read from Bluetooth
     */
    String readCommand();
    
    /**
     * @brief Sends a message to the connected Bluetooth device
     * 
     * @param message The message string to send
     */
    void sendMessage(const String& message);
    
    /**
     * @brief Parses a command string into a CommandType enum
     * 
     * Analyzes the command string to determine its type and extracts
     * any associated value.
     * 
     * @param command The command string to parse
     * @param value Reference to a string where extracted value will be stored
     * @return CommandType The identified command type
     */
    CommandType parseCommand(const String& command, String& value);
}; 
