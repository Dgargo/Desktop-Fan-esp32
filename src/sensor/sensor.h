#include <Arduino.h>

class sensor {

/**
 * @brief Class members
 * @{
 */
protected:

    bool temp_mode;/**< The temperature mode to set (true for Celsius mode, false for Fahrenheit mode).*/
    
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
    virtual void set_temp_mode(bool temp_mode);
    virtual void read_data(); 
    virtual void convert_data();
    virtual void send_data(xQueueHandle xData_sensor_queue); 
};