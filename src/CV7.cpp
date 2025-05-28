#include "CV7.h"

/**
 * @brief Constructor. Initializes serial communication on the given RX pin.
 */
CV7::CV7(int rxPin) : _rxPin(rxPin) {
    Serial1.begin(4800, SERIAL_8N1, _rxPin);  // Set up Serial1 with correct settings for CV7
}

/**
 * @brief Sets up debugging serial and prints initialization message.
 */
void CV7::initialize() {
    Serial.begin(115200);  // Main debug serial
    Serial.println("[CV7] Initialization completed.");
}

/**
 * @brief Reads a line from Serial1 and parses wind or temperature data.
 */
void CV7::readFrame() {
    if (Serial1.available()) {
        String frame = Serial1.readStringUntil('\n');
        frame.trim();  // Clean whitespace
        Serial.println("[CV7] Trame brute: " + frame);

        // Parse wind data from $IIMWV frame
        if (frame.startsWith("$IIMWV")) {
            float newWindSpeed;
            sscanf(frame.c_str(), "$IIMWV,%f,R,%f,N,A", &windDirection, &newWindSpeed);
            newWindSpeed *= 3.6;  // Convert m/s to km/h

            lastSpeeds[speedIndex] = newWindSpeed;
            speedIndex = (speedIndex + 1) % 10;

            float sortedSpeeds[10];
            memcpy(sortedSpeeds, lastSpeeds, sizeof(lastSpeeds));
            std::sort(sortedSpeeds, sortedSpeeds + 10);
            windSpeed = sortedSpeeds[5];  // Médiane

            Serial.printf("[CV7] Wind Speed = %.2f km/h, Wind Direction = %.2f°\n", windSpeed, windDirection);
        }
        // Parse temperature data from $WIXDR frame
        else if (frame.startsWith("$WIXDR")) {
            sscanf(frame.c_str(), "$WIXDR,C,%f,C", &newTemp);
            lastTemps[tempIndex] = newTemp;
            tempIndex = (tempIndex + 1) % 10;

            float sortedTemps[10];
            memcpy(sortedTemps, lastTemps, sizeof(lastTemps));
            std::sort(sortedTemps, sortedTemps + 10);
            temperature = sortedTemps[5];  // Médiane

            Serial.printf("[CV7] Temperature = %.2f°C\n", temperature);
        }
    }
}

/**
 * @brief Returns the latest temperature.
 */
float CV7::getTemperature() const {
    return temperature;
}

/**
 * @brief Returns the latest wind speed.
 */
float CV7::getWindSpeed() const {
    return windSpeed;
}

/**
 * @brief Returns the latest wind direction.
 */
float CV7::getWindDirection() const {
    return windDirection;
}
