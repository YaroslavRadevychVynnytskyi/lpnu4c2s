#include "CookingController.h"

/**
 * @brief Constructor for CookingController
 * 
 * Initializes the cooking controller with references to the Bluetooth
 * manager and temperature sensor.
 * 
 * @param bt Reference to the Bluetooth manager for communication
 * @param temp Reference to the temperature sensor for readings
 */
CookingController::CookingController(BluetoothManager& bt, TemperatureSensor& temp)
    : btManager(bt), tempSensor(temp) {
}

/**
 * @brief Initializes the cooking controller
 * 
 * Sets up the relay pin as output and ensures it starts in the OFF state.
 */
void CookingController::begin() {
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW);
    Serial.println("Cooking controller initialized");
}

/**
 * @brief Processes a command received via Bluetooth
 * 
 * Parses and executes the given command, taking appropriate action
 * based on the command type.
 * 
 * @param command The command string to process
 */
void CookingController::processCommand(const String& command) {
    String value = "";
    CommandType cmdType = btManager.parseCommand(command, value);
    
    int doneness;
    
    switch (cmdType) {
        case CMD_SET_TEMP:
            setTargetTemperature(value.toInt());
            break;
        
        case CMD_SET_TIME:
            setTargetTime(value.toInt());
            break;
        
        case CMD_STATUS:
            btManager.sendMessage("STATUS:TEMP:" + String(currentTemp) + ",TIME:" + String(setTime));
            break;
        
        case CMD_OFF:
            turnOff();
            break;
        
        case CMD_BOILED_EGGS:
            doneness = value.toInt();
            if (doneness == EGG_SOFT) {
                handleEggsProgram(EGG_SOFT);
            } else if (doneness == EGG_HARD) {
                handleEggsProgram(EGG_HARD);
            } else {
                btManager.sendMessage("Invalid egg doneness selection. Use 1 for soft, 2 for hard.");
            }
            break;
        
        case CMD_UNKNOWN:
        default:
            btManager.sendMessage("Unknown command: " + command);
            break;
    }
}

/**
 * @brief Main update method to be called regularly in the loop
 * 
 * Reads current temperature, updates cooking status, and controls
 * the relay based on current conditions.
 */
void CookingController::update() {
    currentTemp = tempSensor.readTemperature();
    
    updateCookingStatus();
    controlRelay();
}

/**
 * @brief Sets the target temperature
 * 
 * Updates the target temperature and notifies the user.
 * 
 * @param temp Target temperature in degrees Celsius
 */
void CookingController::setTargetTemperature(int temp) {
    setTemp = temp;
    btManager.sendMessage("Temperature set to: " + String(setTemp));
}

/**
 * @brief Sets the target cooking time
 * 
 * Updates the target cooking time and notifies the user.
 * 
 * @param time Target time in minutes
 */
void CookingController::setTargetTime(int time) {
    setTime = time;
    btManager.sendMessage("Time set to: " + String(setTime) + " minutes");
}

/**
 * @brief Turns off the cooker
 * 
 * Stops any active cooking and turns off the heating element.
 */
void CookingController::turnOff() {
    digitalWrite(RELAY_PIN, LOW);
    cookingActive = false;
    btManager.sendMessage("Cooker turned OFF");
}

/**
 * @brief Configures and starts the boiled eggs program
 * 
 * Sets up the appropriate temperature and time parameters for
 * the selected egg doneness level and starts the cooking process.
 * 
 * @param doneness The desired egg doneness level (soft or hard)
 */
void CookingController::handleEggsProgram(EggDoneness doneness) {
    setTemp = BOILING_TEMP;
    eggDoneness = doneness;
    
    if (doneness == EGG_SOFT) {
        setTime = SOFT_BOILED_TIME;
        btManager.sendMessage("Soft-boiled eggs selected. " + String(SOFT_BOILED_TIME) + " minutes once water boils.");
    } else {
        setTime = HARD_BOILED_TIME;
        btManager.sendMessage("Hard-boiled eggs selected. " + String(HARD_BOILED_TIME) + " minutes once water boils.");
    }
    
    cookingActive = true;
    temperatureReached = false;
    btManager.sendMessage("Heating water to boiling...");
}

/**
 * @brief Updates the cooking status and sends progress information
 * 
 * Tracks cooking progress, checks if boiling point has been reached,
 * manages timers, and sends status updates via Bluetooth.
 */
void CookingController::updateCookingStatus() {
    if (cookingActive) {
        // If temperature just reached boiling point and timer hasn't started yet
        if (currentTemp >= setTemp && !temperatureReached) {
            temperatureReached = true;
            cookingStartTime = millis();
            btManager.sendMessage("Water is boiling! Starting timer for " + String(setTime) + " minutes.");
        }
        
        // If boiling point reached and timer is running
        if (temperatureReached) {
            // Calculate remaining time
            unsigned long elapsedSeconds = (millis() - cookingStartTime) / 1000;
            int remainingSeconds = (setTime * 60) - elapsedSeconds;
            
            // Send status update every 10 seconds
            if (elapsedSeconds % 10 == 0 && elapsedSeconds > 0) {
                btManager.sendMessage("Cooking in progress. " + String(remainingSeconds / 60) + ":" + 
                                 String(remainingSeconds % 60) + " remaining.");
            }
            
            // Check if cooking is complete
            if (remainingSeconds <= 0) {
                digitalWrite(RELAY_PIN, LOW);
                cookingActive = false;
                btManager.sendMessage("Cooking complete! Your " + 
                                 String(eggDoneness == EGG_SOFT ? "soft" : "hard") + 
                                 "-boiled eggs are ready.");
            }
        }
    }
}

/**
 * @brief Controls the relay based on current cooking state
 * 
 * This method manages the relay that controls the heating element,
 * turning it on or off based on the current temperature and cooking state.
 */
void CookingController::controlRelay() {
    if (cookingActive) {
        // Keep the relay on while cooking is active and we haven't reached the set time
        if (!temperatureReached || (millis() - cookingStartTime) / 1000 < (setTime * 60)) {
            digitalWrite(RELAY_PIN, HIGH); // Turn on the heater
        } else {
            digitalWrite(RELAY_PIN, LOW); // Turn off the heater
        }
    } else if (currentTemp < setTemp) {
        digitalWrite(RELAY_PIN, HIGH); // Turn on the heater for manual mode
    } else {
        digitalWrite(RELAY_PIN, LOW); // Turn off the heater
    }
} 
