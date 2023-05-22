#include "sensor.h"

#include <OneWire.h>
#include <DallasTemperature.h>
class ds18b20 : sensor
{
/**
 * @brief Class members
 * @{
 */
private:

    OneWire one_wire;/**< OneWire class for the sensor */
    DallasTemperature temp_sensor;/**< DallasTemperature class for the DS18B20 sensor*/
    bool temp_mode;/**< Temperature mode: true - Celsius, false - Fahrenheit*/
    
    float temperatureC;/**< Temperature in Celsius from the sensor*/
    float temperatureF;/**< Temperature in Fahrenheit from the sensor*/

    int32_t min_tempC;/**< Minimum temperature in Celsius*/
    int32_t max_tempC;/**< Maximum temperature in Celsius*/
    int32_t min_tempF;/**< Minimum temperature in Fahrenheit*/
    int32_t max_tempF;/**< Maximum temperature in Fahrenheit*/

    float convert_temperatureC;/**< Converted Celsius temperature value in percentage for sending to the queue*/
    float convert_temperatureF;/**<  Converted Fahrenheit temperature value in percentage for sending to the queue*/
/**@}*/
public:
    /**
     * @brief Construct a new ds18b20 object
     * 
     * @param sensor_pin The pin number used for the ds18b20 sensor.
     * @param temp_mode The temperature mode to set (true for Celsius, false for Fahrenheit).
     * @param min_tempC Minimum temperature in Celsius
     * @param max_tempC Maximum temperature in Celsius
     * @param min_tempF Minimum temperature in Fahrenheit
     * @param max_tempF Maximum temperature in Fahrenheit
     * 
     * @note Additionally, it calls the ds18b20() method to configure sensor
     */
    ds18b20(int sensor_pin,bool temp_mode,int32_t mix_tempC ,int32_t max_tempC ,int32_t min_tempF ,int32_t max_tempF);

    /**
     * @brief Destroy the ds18b20 object
     * 
     */
    ~ds18b20();

    /**
     * @brief Configure the sensor, start reading, and set up the resolution.
     *
     * This function configures the ds18b20 sensor, initiates temperature readings,
     * and sets up the resolution for the readings.
     */
    void ds18b20_setup();

    /**
     * @brief Set the temperature mode.
     *
     * This function sets the temperature mode for the sensor readings.
     *
     * @param temp_mode Temperature mode: true - Celsius, false - Fahrenheit
     */
    void set_temp_mode(bool temp_mode);

    /**
     * @brief Read data from the sensor in Celsius and Fahrenheit.
     *
     * This function reads the temperature data from the sensor and stores the values in both Celsius and Fahrenheit.
     * 
     * @note Additionally, return if unable to start reading from the sensor.
     */
    void read_data() override;

    /**
     * @brief Convert the temperature data from the sensor to percentage (Celsius and Fahrenheit).
     *
     * This function converts the temperature data obtained from the sensor to a percentage value, considering the defined minimum and maximum temperature ranges in both Celsius and Fahrenheit units.
     */
    void convert_data() override;

   /**
    * @brief Send the sensor data to a queue.
    *
    * This function sends the temperature data from the sensor to the specified queue. The queue handle `xData_sensor_queue` should be provided as a parameter.
    *
    * @param xData_sensor_queue The handle of the queue to which the sensor data will be sent.
    */
    void send_data(xQueueHandle xData_sensor_queue) override;
};

