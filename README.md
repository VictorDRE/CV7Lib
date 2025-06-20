# CV7Lib

CV7Lib is a lightweight Arduino library for reading wind speed, wind direction, and temperature from the CV7-OEM anemometer using serial (NMEA) communication.

## Installation

1. Download or clone this repository.
2. Copy the `CV7Lib` folder into your Arduino `libraries` directory.
3. Restart the Arduino IDE.
4. Open: `File > Examples > BasicUsage > BasicUsage.ino`
5. Upload to your ESP32 or other compatible board.

## Wiring

Wiring example between the CV7-OEM and an ESP32:

![image](https://github.com/user-attachments/assets/1e50244d-23dc-46f2-b316-a16dfaf5183b)


- CV7 TX → ESP32 RX (e.g. GPIO 16)
- CV7 GND → ESP32 GND
- CV7 VCC → 12V external power supply

## Usage

### Include and initialize

```cpp
#include <CV7.h>

#define RX_PIN 16
CV7 sensor(RX_PIN);

/**
 * @brief Initializes the sensor and debug serial port.
 */
void setup() {
    Serial.begin(115200);
    sensor.initialize();
}

/**
 * @brief Periodically reads sensor data and displays it.
 */
void loop() {
    sensor.readFrame();

    Serial.printf("Temperature   : %.2f °C\n", sensor.getTemperature());
    Serial.printf("Wind Speed    : %.2f km/h\n", sensor.getWindSpeed());
    Serial.printf("Wind Direction: %.2f °\n", sensor.getWindDirection());
    Serial.println("--------------------------------------------------");

    delay(2000);
}

