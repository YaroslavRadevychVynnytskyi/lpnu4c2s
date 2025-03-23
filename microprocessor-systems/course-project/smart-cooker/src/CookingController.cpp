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
    digitalWrite(RELAY_PIN, LOW); // Turn off the relay initially
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
    int riceTypeValue;
    int porkCutTypeValue;
    
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
            
        case CMD_RICE:
            riceTypeValue = value.toInt();
            if (riceTypeValue == RICE_WHITE) {
                handleRiceProgram(RICE_WHITE);
            } else if (riceTypeValue == RICE_BROWN) {
                handleRiceProgram(RICE_BROWN);
            } else {
                btManager.sendMessage("Invalid rice type. Use 1 for white rice, 2 for brown rice.");
            }
            break;
            
        case CMD_STEWED_PORK:
            porkCutTypeValue = value.toInt();
            if (porkCutTypeValue == PORK_SHOULDER) {
                handleStewedPorkProgram(PORK_SHOULDER);
            } else if (porkCutTypeValue == PORK_BELLY) {
                handleStewedPorkProgram(PORK_BELLY);
            } else if (porkCutTypeValue == PORK_TENDERLOIN) {
                handleStewedPorkProgram(PORK_TENDERLOIN);
            } else {
                btManager.sendMessage("Invalid pork cut type. Use 1 for shoulder, 2 for belly, 3 for tenderloin.");
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
    activeCookingProgram = CMD_UNKNOWN;
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
    activeCookingProgram = CMD_BOILED_EGGS;
    
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
 * @brief Configures and starts the rice cooking program
 * 
 * Sets up the appropriate temperature and time parameters for
 * the selected rice type and starts the cooking process.
 * 
 * @param type The type of rice to cook (white or brown)
 */
void CookingController::handleRiceProgram(RiceType type) {
    setTemp = RICE_COOKING_TEMP;
    riceType = type;
    activeCookingProgram = CMD_RICE;
    
    if (type == RICE_WHITE) {
        setTime = WHITE_RICE_TIME;
        btManager.sendMessage("White rice selected. " + String(WHITE_RICE_TIME) + " minutes cooking time.");
        btManager.sendMessage("Tip: Use 1.5 cups of water per 1 cup of white rice.");
    } else {
        setTime = BROWN_RICE_TIME;
        btManager.sendMessage("Brown rice selected. " + String(BROWN_RICE_TIME) + " minutes cooking time.");
        btManager.sendMessage("Tip: Use 2 cups of water per 1 cup of brown rice.");
    }
    
    cookingActive = true;
    temperatureReached = false;
    btManager.sendMessage("Starting rice cooking program. Heating to " + String(RICE_COOKING_TEMP) + "°C...");
}

/**
 * @brief Configures and starts the stewed pork program
 * 
 * Sets up the appropriate temperature and time parameters for
 * the selected pork cut type and starts the multi-phase cooking process.
 * 
 * @param cutType The type of pork cut to stew
 */
void CookingController::handleStewedPorkProgram(PorkCutType cutType) {
    porkCutType = cutType;
    activeCookingProgram = CMD_STEWED_PORK;
    currentPhase = PHASE_SEARING;
    
    // Initial searing phase
    setTemp = SEARING_TEMP;
    setTime = SEARING_TIME;
    
    String cutName;
    int totalTime = 0;
    
    switch (cutType) {
        case PORK_SHOULDER:
            cutName = "shoulder";
            totalTime = SEARING_TIME + PORK_SHOULDER_TIME + RESTING_TIME;
            break;
        case PORK_BELLY:
            cutName = "belly";
            totalTime = SEARING_TIME + PORK_BELLY_TIME + RESTING_TIME;
            break;
        case PORK_TENDERLOIN:
            cutName = "tenderloin";
            totalTime = SEARING_TIME + PORK_TENDERLOIN_TIME + RESTING_TIME;
            break;
    }
    
    btManager.sendMessage("Stewed pork " + cutName + " selected. Total estimated cooking time: " + String(totalTime) + " minutes.");
    btManager.sendMessage("Tip: Season the meat with salt, pepper, and your favorite herbs before cooking.");
    btManager.sendMessage("Phase 1: Searing at " + String(SEARING_TEMP) + "°C for " + String(SEARING_TIME) + " minutes.");
    
    cookingActive = true;
    temperatureReached = false;
    btManager.sendMessage("Starting pork stewing program. Heating to searing temperature...");
}

/**
 * @brief Moves to the next cooking phase in a multi-phase recipe
 * 
 * Updates temperature, time, and status for the new cooking phase.
 * 
 * @return bool True if moved to a new phase, false if cooking is complete
 */
bool CookingController::moveToNextPhase() {
    if (activeCookingProgram == CMD_STEWED_PORK) {
        switch (currentPhase) {
            case PHASE_SEARING:
                // Move to main cooking phase
                currentPhase = PHASE_COOKING;
                setTemp = STEWING_TEMP;
                
                // Set cooking time based on cut type
                switch (porkCutType) {
                    case PORK_SHOULDER:
                        setTime = PORK_SHOULDER_TIME;
                        break;
                    case PORK_BELLY:
                        setTime = PORK_BELLY_TIME;
                        break;
                    case PORK_TENDERLOIN:
                        setTime = PORK_TENDERLOIN_TIME;
                        break;
                }
                
                btManager.sendMessage("Phase 2: Stewing at " + String(STEWING_TEMP) + "°C for " + String(setTime) + " minutes.");
                temperatureReached = false;
                return true;
                
            case PHASE_COOKING:
                // Move to resting phase
                currentPhase = PHASE_RESTING;
                setTemp = 0; // No heat needed for resting
                setTime = RESTING_TIME;
                
                btManager.sendMessage("Phase 3: Resting for " + String(RESTING_TIME) + " minutes.");
                temperatureReached = true;
                return true;
                
            case PHASE_RESTING:
                // End of all phases
                return false;
                
            default:
                return false;
        }
    }
    
    return false; // Not a multi-phase recipe
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
            btManager.sendMessage("Target temperature reached! Starting timer for " + String(setTime) + " minutes.");
        }
        
        // If target temperature reached and timer is running
        if (temperatureReached) {
            // Calculate remaining time
            unsigned long elapsedSeconds = (millis() - cookingStartTime) / 1000;
            int remainingSeconds = (setTime * 60) - elapsedSeconds;
            
            // Send status update every 10 seconds
            if (elapsedSeconds % 10 == 0 && elapsedSeconds > 0) {
                if (activeCookingProgram == CMD_STEWED_PORK) {
                    String phaseName;
                    switch (currentPhase) {
                        case PHASE_SEARING: phaseName = "Searing"; break;
                        case PHASE_COOKING: phaseName = "Stewing"; break;
                        case PHASE_RESTING: phaseName = "Resting"; break;
                    }
                    
                    btManager.sendMessage("Phase: " + phaseName + ". " + String(remainingSeconds / 60) + ":" + 
                                     String(remainingSeconds % 60) + " remaining.");
                } else {
                    btManager.sendMessage("Cooking in progress. " + String(remainingSeconds / 60) + ":" + 
                                     String(remainingSeconds % 60) + " remaining.");
                }
            }
            
            // Check if current phase is complete
            if (remainingSeconds <= 0) {
                // For multi-phase recipes, move to next phase if available
                if (activeCookingProgram == CMD_STEWED_PORK && moveToNextPhase()) {
                    // Reset timer for the new phase
                    cookingStartTime = millis();
                } else {
                    // Cooking complete
                    digitalWrite(RELAY_PIN, LOW);
                    cookingActive = false;
                    
                    // Sending completion message based on what was being cooked
                    if (activeCookingProgram == CMD_BOILED_EGGS) {
                        btManager.sendMessage("Cooking complete! Your " + 
                                        String(eggDoneness == EGG_SOFT ? "soft" : "hard") + 
                                        "-boiled eggs are ready.");
                    } else if (activeCookingProgram == CMD_RICE) {
                        btManager.sendMessage("Cooking complete! Your " + 
                                        String(riceType == RICE_WHITE ? "white" : "brown") + 
                                        " rice is ready.");
                        btManager.sendMessage("Let it rest for 5-10 minutes before serving for best results.");
                    } else if (activeCookingProgram == CMD_STEWED_PORK) {
                        String cutName;
                        switch (porkCutType) {
                            case PORK_SHOULDER: cutName = "shoulder"; break;
                            case PORK_BELLY: cutName = "belly"; break;
                            case PORK_TENDERLOIN: cutName = "tenderloin"; break;
                        }
                        btManager.sendMessage("Cooking complete! Your stewed pork " + cutName + " is ready.");
                        btManager.sendMessage("Enjoy your delicious, tender pork dish!");
                    } else {
                        btManager.sendMessage("Cooking complete! Your food is ready.");
                    }
                    
                    activeCookingProgram = CMD_UNKNOWN;
                }
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
        // For resting phase, keep the relay off
        if (activeCookingProgram == CMD_STEWED_PORK && currentPhase == PHASE_RESTING) {
            digitalWrite(RELAY_PIN, LOW);
        } 
        // Keep the relay on while cooking is active and we haven't reached the set time
        else if (!temperatureReached || (millis() - cookingStartTime) / 1000 < (setTime * 60)) {
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
