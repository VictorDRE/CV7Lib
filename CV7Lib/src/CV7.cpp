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

        // Parse wind data from $IIMWV frame
        if (frame.startsWith("$IIMWV")) {
            float newWindSpeed;
            sscanf(frame.c_str(), "$IIMWV,%f,R,%f,N,A", &windDirection, &newWindSpeed);
            newWindSpeed *= 3.6;  // Convert m/s to km/h

            // Store in circular buffer
            lastSpeeds[speedIndex] = newWindSpeed;
            speedIndex = (speedIndex + 1) % 3;

            windSpeed = newWindSpeed;

            Serial.printf("[CV7] Wind Speed = %.2f km/h, Wind Direction = %.2f°\n", windSpeed, windDirection);
        }
        // Parse temperature data from $WIXDR frame
        else if (frame.startsWith("$WIXDR")) {
            sscanf(frame.c_str(), "$WIXDR,C,%f,C", &temperature);
            Serial.printf("[CV7] Temperature = %.2f°C\n", temperature - 6.0);  // Apply calibration
        }
    }
}

/**
 * @brief Returns the calibrated temperature.
 */
float CV7::getTemperature() const {
    return temperature - 6.0;
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

/**
 * @brief Returns the median of the last 3 wind speed measurements.
 */
float CV7::getMedianWindSpeed() const {
    float sortedValues[3] = {lastSpeeds[0], lastSpeeds[1], lastSpeeds[2]};

    // Simple bubble sort for 3 values
    for (int i = 0; i < 2; i++) {
        for (int j = i + 1; j < 3; j++) {
            if (sortedValues[i] > sortedValues[j]) {
                float temp = sortedValues[i];
                sortedValues[i] = sortedValues[j];
                sortedValues[j] = temp;
            }
        }
    }

    return sortedValues[1];  // Middle value is median
}
