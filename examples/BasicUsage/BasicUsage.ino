#include <CV7.h>

#define RX_PIN 16
CV7 sensor(RX_PIN);

int frameCount = 0; // To track how many frames were read

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
    frameCount++;

    Serial.println("=== LIVE SENSOR DATA ===");
    Serial.printf("Temperature    : %.2f °C\n", sensor.getTemperature());
    Serial.printf("Wind Speed     : %.2f km/h\n", sensor.getWindSpeed());
    Serial.printf("Wind Direction : %.2f °\n", sensor.getWindDirection());

    if (frameCount >= 10) {
        Serial.println("--- Filtered Data (Median over last 10) ---");
        Serial.printf("Median Wind Sp.: %.2f km/h\n", sensor.getMedianWindSpeed());
    }

    Serial.println("--------------------------------------------------");
    delay(2000);
}
