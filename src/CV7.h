#ifndef CV7_H
#define CV7_H

#include <Arduino.h>
#include <algorithm>

/**
 * @brief CV7 anemometer class for measuring wind speed, direction, and temperature.
 * This class interfaces with the CV7-OEM sensor via NMEA sentences.
 */
class CV7 {
public:
    /**
     * @brief Constructor with specified RX pin.
     * @param rxPin Serial RX pin connected to the CV7-OEM.
     */
    explicit CV7(int rxPin);

    /**
     * @brief Initializes serial communication and debug output.
     */
    void initialize();

    /**
     * @brief Reads and parses a full NMEA frame from Serial1.
     * Handles both $IIMWV (wind) and $WIXDR (temperature) frames.
     */
    void readFrame();

    /**
     * @brief Returns the current median temperature in °C.
     */
    float getTemperature() const;

    /**
     * @brief Returns the current median wind speed in km/h.
     */
    float getWindSpeed() const;

    /**
     * @brief Returns the most recent wind direction in degrees.
     */
    float getWindDirection() const;

private:
    int _rxPin;                                ///< RX pin used for communication
    float _temperature = 0.0f;                 ///< Median temperature
    float _windSpeed = 0.0f;                   ///< Median wind speed
    float _windDirection = 0.0f;               ///< Last wind direction

    float _speedBuffer[10] = {0.0f};           ///< Last 10 wind speeds
    int _speedIndex = 0;                       ///< Circular index for wind speed

    float _tempBuffer[10] = {0.0f};            ///< Last 10 temperature readings
    int _tempIndex = 0;                        ///< Circular index for temperature

    float _rawTemp = 0.0f;                     ///< Temporary variable to store raw temperature
};

#endif // CV7_H
