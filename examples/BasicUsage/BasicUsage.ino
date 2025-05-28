#include <CV7.h>  // Include the CV7 anemometer library

#define RX_PIN 16  // RX pin connected to the CV7-OEM

CV7 sensor(RX_PIN);

void setup() {
    Serial.begin(115200);    // Start the serial monitor
    sensor.initialize();     // Initialize CV7 (Serial1 + debug)
}

void loop() {
    sensor.readFrame();  // Read one frame

    Serial.printf("Temperature: %.2f°C\n", sensor.getTemperature());
    Serial.printf("Wind Speed: %.2f km/h\n", sensor.getWindSpeed());
    Serial.printf("Wind Direction: %.2f°\n", sensor.getWindDirection());
    Serial.println("----------------------------------------");

    delay(2000);  // Wait before reading next frame
}
