#include "BluetoothManager.h"

/**
 * @brief Constructor for BluetoothManager
 * 
 * Default constructor that initializes the class members.
 */
BluetoothManager::BluetoothManager() {
}

/**
 * @brief Initializes the Bluetooth Serial communication
 * 
 * Starts the Bluetooth Serial service with the configured device name.
 * 
 * @return bool True if initialization was successful, false otherwise
 */
bool BluetoothManager::begin() {
    if (!serialBT.begin(deviceName)) {
        Serial.println("Bluetooth initialization failed!");
        return false;
    }
    Serial.println("Bluetooth initialized. Device name: " + String(deviceName));
    return true;
}

/**
 * @brief Checks if Bluetooth data is available to read
 * 
 * @return bool True if data is available, false otherwise
 */
bool BluetoothManager::available() {
    return serialBT.available();
}

/**
 * @brief Reads a command string from Bluetooth
 * 
 * Reads characters from the Bluetooth serial buffer until a newline
 * character is encountered.
 * 
 * @return String The command string read from Bluetooth
 */
String BluetoothManager::readCommand() {
    return serialBT.readStringUntil('\n');
}

/**
 * @brief Sends a message to the connected Bluetooth device
 * 
 * @param message The message string to send
 */
void BluetoothManager::sendMessage(const String& message) {
    serialBT.println(message);
}

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
CommandType BluetoothManager::parseCommand(const String& command, String& value) {
    if (command.startsWith("TEMP:")) {
        value = command.substring(5);
        return CMD_SET_TEMP;
    } else if (command.startsWith("TIME:")) {
        value = command.substring(5);
        return CMD_SET_TIME;
    } else if (command == "STATUS") {
        return CMD_STATUS;
    } else if (command == "OFF") {
        return CMD_OFF;
    } else if (command.startsWith("EGGS:")) {
        value = command.substring(5);
        return CMD_BOILED_EGGS;
    }
    return CMD_UNKNOWN;
} 
