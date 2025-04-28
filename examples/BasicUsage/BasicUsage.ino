#include <CV7.h>  // Include the CV7 anemometer library

// Define the RX pin used to connect to the CV7-OEM output
#define RX_PIN 16

// Create an instance of the CV7 class with the correct RX pin
CV7 sensor(RX_PIN);

void setup() {
    // Start the serial monitor for debugging
    Serial.begin(115200);

    // Initialize the CV7 sensor (debug serial and Serial1)
    sensor.initialize();
}

void loop() {
    // Read one line of data from the CV7 sensor
    sensor.readFrame();

    // Display the parsed and corrected data to the serial monitor
    Serial.printf("Temperature: %.2f°C\n", sensor.getTemperature());
    Serial.printf("Wind Speed: %.2f km/h\n", sensor.getWindSpeed());
    Serial.printf("Wind Direction: %.2f°\n", sensor.getWindDirection());
    Serial.println("----------------------------------------");

    // Wait 2 seconds before reading again to reduce output frequency
    delay(2000);
}
