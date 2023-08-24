#include "config.h"

#ifdef DS18B20_SETTINGS_H
    #include "sensor/ds18b20.h"
#else
    #include "sensor/bme280.h"
#endif

#include "controller/PID_controller.h"

#include "fan/fan_3pin.h"

class assembly
{
/**
 * @brief Class members
 * @{
 */
private:
    #ifdef DS18B20_SETTINGS_H
        ds18b20 *ds18b20_obj; /**< Object for ds18b20 sensor */
    #else
        bme280 *bme280_obj; /**< Object for bme280 sensor */
    #endif
    controller *controller_obj; /**< Object for simple controller */
    PID_controller *PID_controller_obj; /**< Object for PID controller */
    Fan *fan_obj;/**< Object for Fan*/
    Fan_3pin *Fan_3pin_obj; /**< Object for 3pin Fan */

    uint32_t output_PWM;
    const uint8_t length_array = LENGTH_ARRAY_DATA;
    float array_data[LENGTH_ARRAY_DATA];
/** @} */
public:
    

    ~assembly();

    #ifdef DS18B20_SETTINGS_H

    assembly::assembly(ds18b20 *ds18b20_obj, controller *controller_obj, Fan_3pin *Fan_3pin_obj);

    /**
     * @brief Simple assembly for desktop fan
     * 
     * This assembly uses the following components:
     * - Sensor: ds18b20
     * - Smooth controller
     * - 2-pin fan
     */
    void simple_assembly();

    /**
     * @brief Advanced assembly for desktop fan
     * 
     * This assembly uses the following components:
     * - Sensor: ds18b20
     * - PID controller
     * - 3-pin fan
     */
    void advanced_assembly();
#else
    /**
     * @brief Construct a new assembly object
     * 
     * @param bme280_obj bme280 sensor
     * @param PID_controller_obj PID controller
     * @param Fan_3pin_obj 3pin Fan
     */
    assembly(bme280 *bme280_obj,PID_controller *PID_controller_obj,Fan_3pin *Fan_3pin_obj);

    /**
     * @brief BME280 sensor assembly for data acquisition and processing
     * 
     * This method includes other methods from the BME280 class: read, convert, and send data to the queue.
     * 
     * @note Before calling this method, make sure that the BME280 sensor has been properly initialized and is ready to read data.
     */
    void bme280_assembly();

    /**
     * @brief PID controller assembly for data acquisition and processing
     * 
     * This method includes other methods from the PID_controller class for data processing.
     * 
     * 
     * @note Before calling this method, make sure that the PID controller has been properly initialized and is ready to process data.
     */
    void PID_controller_assembly();

    /**
     * @brief 3-pin Fan assembly for changing RPM and reading it from the tachosensor.
     * 
     * 
     * This method includes other methods from the Fan3pin class for changing and reading the fan's speed (RPM).
     * 
     * @note Before calling this method, ensure that the Fan 3-pin has been properly initialized to control the fan speed correctly.
     */
    void Fan3pin_assembly();

    /**
     * @brief Simple smart assembly
     * 
     * This assembly uses the following components:
     * - Sensor: bme280
     * - PID controller
     * - 3-pin fan
     */
    void simple_smart_assembly();

    /**
     * @brief IoT assembly
     * 
     * This assembly uses the following components:
     * - Sensor: bme280
     * - PID controller
     * - 3-pin fan
     * - MQTT communication
     */
    void IOT_assembly();

    void save_data_in_assembly(uint32_t i);
    void assembly_check();
#endif
};


