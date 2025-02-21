# BME280 Sensor Data Logger

## Overview
This project is designed for scientific research to study the effect of moisture on avionics components. The application reads temperature, humidity, and pressure data from the BME280 sensor and displays it on an LCD screen. Data is also transmitted via the serial port for further analysis.

## Features
- Reads temperature, humidity, and pressure using the BME280 sensor.
- Displays measurements on a 20x4 I2C LCD screen.
- Outputs data via the serial interface for real-time monitoring.
- Uses timers to optimize sensor reading and display refresh rates.
- Supports different measurement modes based on Bosch BME280 sensor recommendations.

## Hardware Requirements
- **Arduino Nano** or a compatible microcontroller
- **BME280 Sensor** (I2C interface)
- **20x4 LCD Display** with I2C module
- **Connecting Wires**

## Wiring Diagram
| Sensor Pin | Arduino Nano Pin |
|------------|-----------------|
| Vin        | 5V              |
| Gnd        | Gnd             |
| SDA        | A4              |
| SCL        | A5              |

## Software Requirements
- Arduino IDE
- Libraries:
  - `BME280I2C`
  - `LiquidCrystal_I2C`
  - `Wire`

## Installation & Usage
1. Install the required libraries in the Arduino IDE.
2. Connect the hardware according to the wiring diagram.
3. Upload the `.ino` sketch to the Arduino board.
4. Open the Serial Monitor (115200 baud) to view the sensor data in real-time.

## License
This project is licensed under the MIT License.

### MIT License   

## Author
Dmytro Myronov (<hattabith@gmail.com>)

