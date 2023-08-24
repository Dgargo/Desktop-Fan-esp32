#ifndef BME280_H
#define BME280_H
#include "sensor.h"
#include "config.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#ifdef SPI_SET
#include <SPI.h>
#endif

class bme280: public sensor
{

/**
 * @brief Class members
 * @defgroup BME280 class members
 * @{
*/
private:
    Adafruit_BME280 bme;/**< Adafruit_BME280 class for the sensor*/
    float pressure;/**< Pressure in Hectopascal*/
    float humidity;/**< Humidity in procent */

/** @} */ //Close BME280 
public:

    bme280();
    #ifdef I2C_SET
    /**
     * @brief Construct a new bme280 object using I2C protocol
     * 
     * @param temp_mode The temperature mode to set (true for Celsius mode, false for Fahrenheit mode).
     * @param min_tempC Minimum temperature in Celsius
     * @param max_tempC Maximum temperature in Celsius
     * @param min_tempF Minimum temperature in Fahrenheit
     * @param max_tempF Maximum temperature in Fahrenheit
     * 
     */
    bme280(bool temp_mode,int32_t mix_tempC ,int32_t max_tempC ,int32_t min_tempF ,int32_t max_tempF);
    #endif

    #ifdef SPI_SET
    /**
     * @brief Construct a new bme280 object using SPI protocol
     * 
     * @param temp_mode The temperature mode to set (true for Celsius mode, false for Fahrenheit mode).
     * @param min_tempC Minimum temperature in Celsius
     * @param max_tempC Maximum temperature in Celsius
     * @param min_tempF Minimum temperature in Fahrenheit
     * @param max_tempF Maximum temperature in Fahrenheit
     * 
     */
    bme280(bool temp_mode,int32_t mix_tempC ,int32_t max_tempC ,int32_t min_tempF ,int32_t max_tempF);
    /**
     * @brief Set the up bme SPI object
     * 
     * @param CS The CS (Chip Select) pin for SPI communication.
     */
    void setup_bme_SPI(int8_t CS);
    #endif

    /**
     * @brief Destroy the bme280 object
     * 
     */
    ~bme280();

    /**
     * @brief Set the temperature mode.
     *
     * This function sets the temperature mode for the sensor readings.
     *
     * @param temp_mode Temperature mode: true - Celsius, false - Fahrenheit
     */
    void set_temp_mode(bool temp_mode) override;

    /**
     * @brief Read data from the sensor temperature(in Celsius and Fahrenheit),pressure,humidity.
     * 
     * This function reads the temperature ,pressure and humidity data from the sensor and stores it.
     */
    void read_data() override; 

    /**
     * @brief Convert the temperature, pressure, and humidity data from the sensor to a percentage value.
     *
     * This function converts the temperature, pressure, and humidity data obtained from the sensor to a percentage value,
     * considering the defined minimum and maximum ranges. The converted values are stored internally.
     */
    void convert_data() override;


    float send_data() override;

    /**
     * @brief Set up and start I2C communication for BME280 sensor.
     * 
     * @param Adress The I2C address of the BME280 sensor. This should be the 7-bit address of the sensor
     */
    void bme_setup_I2C(uint8_t adress);
};
#endif
