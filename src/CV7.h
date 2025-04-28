#ifndef CV7_H
#define CV7_H

#include <Arduino.h>

/**
 * @brief CV7 anemometer class for measuring wind speed, direction, and temperature.
 * This class is specifically designed to interface with the CV7-OEM sensor using NMEA sentences.
 */
class CV7 {
public:
    /**
     * @brief Constructor with RX pin for serial communication.
     * @param rxPin Serial RX pin connected to the CV7-OEM.
     */
    explicit CV7(int rxPin);

    /**
     * @brief Initializes serial communication and debug interface.
     */
    void initialize();

    /**
     * @brief Reads and parses a frame from the CV7 anemometer.
     * It handles both $IIMWV (wind) and $WIXDR (temperature) NMEA frames.
     */
    void readFrame();

    /**
     * @brief Returns the corrected temperature (in °C).
     * The correction applied is -6°C as per sensor calibration.
     */
    float getTemperature() const;

    /**
     * @brief Returns the latest wind speed (in km/h).
     */
    float getWindSpeed() const;

    /**
     * @brief Returns the latest wind direction (in degrees).
     */
    float getWindDirection() const;

    /**
     * @brief Calculates the median of the last 3 wind speed readings.
     * This improves stability by reducing the effect of outliers.
     */
    float getMedianWindSpeed() const;

private:
    int _rxPin;                        // Pin used to receive NMEA sentences
    float temperature = 0.0;          // Current raw temperature value
    float windSpeed = 0.0;            // Current wind speed in km/h
    float windDirection = 0.0;        // Current wind direction in degrees
    float lastSpeeds[3] = {0.0, 0.0, 0.0}; // Circular buffer of last 3 wind speeds
    int speedIndex = 0;               // Index for inserting next speed value
};

#endif // CV7_H
