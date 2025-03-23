# Smart Cooker

A smart cooker IoT project that uses ESP32 to control a heating element via a relay. The system includes temperature monitoring with a DS18B20 sensor and can be controlled via Bluetooth.

## Project Structure

```
smart-cooker/
├── include/                     # Header files
│   ├── BluetoothManager.h       # Bluetooth communication management
│   ├── Enums.h                  # Enumeration definitions
│   ├── Config.h                 # Configuration and pin definitions
│   ├── CookingController.h      # Main cooking logic controller
│   └── TemperatureSensor.h      # Temperature sensor interface
├── src/                         # Source files
│   ├── BluetoothManager.cpp     # Bluetooth implementation
│   ├── CookingController.cpp    # Cooking logic implementation
│   ├── main.cpp                 # Main application entry point
│   └── TemperatureSensor.cpp    # Temperature sensor implementation
└── platformio.ini               # PlatformIO configuration
```

## Features

- Bluetooth control via simple text commands
- Temperature monitoring with DS18B20 sensor
- Relay control for heating element
- Predefined cooking programs:
  - Soft-boiled eggs (6 minutes at boiling temperature)
  - Hard-boiled eggs (12 minutes at boiling temperature)
  - White rice (18 minutes cooking)
  - Brown rice (40 minutes cooking)
  - Stewed pork with multi-phase cooking:
    - Phase 1: Searing (5 minutes at 180°C)
    - Phase 2: Stewing (45-120 minutes at 85°C depending on cut)
    - Phase 3: Resting (15 minutes, no heat)

## Command Interface

The system accepts the following commands via Bluetooth:

- `TEMP:X` - Set target temperature to X degrees Celsius
- `TIME:X` - Set target time to X minutes
- `STATUS` - Get current temperature and set time
- `OFF` - Turn off the cooker
- `EGGS:1` - Start the soft-boiled eggs program
- `EGGS:2` - Start the hard-boiled eggs program
- `RICE:1` - Start the white rice cooking program
- `RICE:2` - Start the brown rice cooking program
- `PORK:1` - Start the stewed pork shoulder program (longest cooking time)
- `PORK:2` - Start the stewed pork belly program (medium cooking time)
- `PORK:3` - Start the stewed pork tenderloin program (shortest cooking time)

## Hardware Requirements

- ESP32 development board
- DS18B20 temperature sensor
- 5V relay module
- Power supply for the heating element

## Circuit Diagram

The system uses the following pins:
- GPIO23: Relay control
- GPIO4: DS18B20 temperature sensor 