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

    uint32_t min_pressure;/**< Minimum pressure in Hectopascal(980)*/
    uint32_t max_pressure;/**< Maximum pressure in Hectopascal(1030)*/

    float convert_pressure/**< Converted pressure Hectopascal value in percentage for sending to the queue*/;
/** @} */ //Close BME280 
public:

    #ifdef I2C_SET
    /**
     * @brief Construct a new bme280 object using I2C protocol
     * 
     * @param temp_mode The temperature mode to set (true for Celsius mode, false for Fahrenheit mode).
     * @param min_tempC Minimum temperature in Celsius
     * @param max_tempC Maximum temperature in Celsius
     * @param min_tempF Minimum temperature in Fahrenheit
     * @param max_tempF Maximum temperature in Fahrenheit
     * @param min_pressure Minimum pressure in Hectopascal
     * @param max_pressure Maximum pressure in Hectopascal
     * 
     * @note Additionally, it calls the bme.begin() method to configure sensor
     */
    bme280(bool temp_mode,int32_t mix_tempC ,int32_t max_tempC ,int32_t min_tempF ,int32_t max_tempF,int32_t min_pressure,int32_t max_pressure);
    #endif

    #ifdef SPI_SET
    /**
     * @brief Construct a new bme280 object using SPI protocol
     * 
     * @param CS The CS (Chip Select) pin for SPI communication.
     * @param temp_mode The temperature mode to set (true for Celsius mode, false for Fahrenheit mode).
     * @param min_tempC Minimum temperature in Celsius
     * @param max_tempC Maximum temperature in Celsius
     * @param min_tempF Minimum temperature in Fahrenheit
     * @param max_tempF Maximum temperature in Fahrenheit
     * @param min_pressure Minimum pressure in Hectopascal
     * @param max_pressure Maximum pressure in Hectopascal 
     * 
     * @note Additionally, it calls the bme.begin() method to configure sensor
     */
    bme280(int8_t CS,bool temp_mode,int32_t mix_tempC ,int32_t max_tempC ,int32_t min_tempF ,int32_t max_tempF,int32_t min_pressure,int32_t max_pressure);
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

    /**
     * @brief Send the sensor data to a queue.
     *
     * This function sends the temperature, pressure, and humidity data from the sensor to the specified queue. The queue handle `xData_sensor_queue` should be provided as a parameter.
     *
     * @param xData_sensor_queue The handle of the queue to which the sensor data will be sent. It should be initialized before calling this function.
     *
     * @note The data sent to the queue should be in a specific format or structure, depending on the requirements of the consumer of the data.
     */
    void send_data(xQueueHandle xData_sensor_queue) override;

};
#endif
