#ifndef CV7_H
#define CV7_H

#include <Arduino.h>

/**
 * @brief CV7 anemometer class for measuring wind speed, direction, and temperature.
 * This class is designed to interface with the CV7-OEM sensor using NMEA sentences.
 */
class CV7 {
public:
    /**
     * @brief Constructor with RX pin for serial communication.
     * @param rxPin Serial RX pin connected to the CV7-OEM output.
     */
    explicit CV7(int rxPin);

    /**
     * @brief Initializes serial communication and debug interface.
     */
    void initialize();

    /**
     * @brief Reads and parses a frame from the CV7 anemometer.
     * Supports both $IIMWV (wind) and $WIXDR (temperature) NMEA frames.
     */
    void readFrame();

    /**
     * @brief Returns the current measured temperature in °C.
     */
    float getTemperature() const;

    /**
     * @brief Returns the most recent wind speed in km/h.
     */
    float getWindSpeed() const;

    /**
     * @brief Returns the most recent wind direction in degrees.
     */
    float getWindDirection() const;

    /**
     * @brief Calculates the median of the last 10 wind speed readings.
     * Helps smooth out measurements and reduce the effect of outliers.
     */
    float getMedianWindSpeed() const;

private:
    int _rxPin;                        // RX pin used to receive NMEA sentences
    float temperature = 0.0f;          // Last measured temperature in °C
    float windSpeed = 0.0f;            // Last measured wind speed in km/h
    float windDirection = 0.0f;        // Last measured wind direction in degrees
    float lastSpeeds[10] = {0.0f};     // Circular buffer of the last 10 wind speed readings
    int speedIndex = 0;                // Index for the circular wind speed buffer
};

#endif // CV7_H
