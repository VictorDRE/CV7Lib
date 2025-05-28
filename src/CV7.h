#ifndef CV7_H
#define CV7_H

#include <Arduino.h>
#include <algorithm>

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
     * @brief Returns the latest temperature (in °C).
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

private:
    int _rxPin;
    float temperature = 0.0;
    float windSpeed = 0.0;
    float windDirection = 0.0;

    float lastSpeeds[10] = {0.0};
    int speedIndex = 0;

    float lastTemps[10] = {0.0};
    int tempIndex = 0;

    float newTemp = 0.0;
};

#endif // CV7_H
