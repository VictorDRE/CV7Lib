#include "CV7.h"

/**
 * @brief Constructor. Sets up Serial1 with the provided RX pin.
 */
CV7::CV7(int rxPin) : _rxPin(rxPin) {
    Serial1.begin(4800, SERIAL_8N1, _rxPin);
}

/**
 * @brief Initializes the debug Serial port and prints startup message.
 */
void CV7::initialize() {
    Serial.begin(115200);
    Serial.println("[CV7] Initialization completed.");
}

/**
 * @brief Reads incoming data character by character, parses NMEA frames,
 *        and updates wind/temperature data using a median of the last 10 values.
 */
void CV7::readFrame() {
    static String buffer = "";

    while (Serial1.available()) {
        char c = Serial1.read();

        if (c == '\n') {
            buffer.trim();
            Serial.println("[CV7] Raw Frame: " + buffer);

            if (buffer.startsWith("$IIMWV")) {
                float newWindSpeed;
                sscanf(buffer.c_str(), "$IIMWV,%f,R,%f,N,A", &_windDirection, &newWindSpeed);
                newWindSpeed *= 3.6f;  // Convert m/s to km/h

                _speedBuffer[_speedIndex] = newWindSpeed;
                _speedIndex = (_speedIndex + 1) % 10;

                float sorted[10];
                memcpy(sorted, _speedBuffer, sizeof(_speedBuffer));
                std::sort(sorted, sorted + 10);
                _windSpeed = sorted[5];

                Serial.printf("[CV7] Wind Speed = %.2f km/h | Wind Direction = %.2f°\n", _windSpeed, _windDirection);
            }
            else if (buffer.startsWith("$WIXDR")) {
                sscanf(buffer.c_str(), "$WIXDR,C,%f,C", &_rawTemp);
                _tempBuffer[_tempIndex] = _rawTemp;
                _tempIndex = (_tempIndex + 1) % 10;

                float sorted[10];
                memcpy(sorted, _tempBuffer, sizeof(_tempBuffer));
                std::sort(sorted, sorted + 10);
                _temperature = sorted[5];

                Serial.printf("[CV7] Temperature = %.2f°C\n", _temperature);
            }

            buffer = "";  // Clear buffer for next frame
        }
        else {
            buffer += c;
            if (buffer.length() > 120) buffer = "";  // Safety flush on overflow
        }
    }
}

/**
 * @brief Returns the current median temperature.
 */
float CV7::getTemperature() const {
    return _temperature;
}

/**
 * @brief Returns the current median wind speed.
 */
float CV7::getWindSpeed() const {
    return _windSpeed;
}

/**
 * @brief Returns the most recent wind direction.
 */
float CV7::getWindDirection() const {
    return _windDirection;
}
