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
