# Smart Cooker

A smart cooker IoT project that uses ESP32 to control a heating element via a relay. The system includes temperature monitoring with a DS18B20 sensor and can be controlled via Bluetooth.

## Project Structure

```
smart-cooker/
├── include/                     # Header files
│   ├── BluetoothManager.h       # Bluetooth communication management
│   ├── CommandTypes.h           # Command type enumerations
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

## Command Interface

The system accepts the following commands via Bluetooth:

- `TEMP:X` - Set target temperature to X degrees Celsius
- `TIME:X` - Set target time to X minutes
- `STATUS` - Get current temperature and set time
- `OFF` - Turn off the cooker
- `EGGS:1` - Start the soft-boiled eggs program
- `EGGS:2` - Start the hard-boiled eggs program

## Hardware Requirements

- ESP32 development board
- DS18B20 temperature sensor
- 5V relay module
- Power supply for the heating element

## Circuit Diagram

The system uses the following pins:
- GPIO23: Relay control
- GPIO4: DS18B20 temperature sensor 