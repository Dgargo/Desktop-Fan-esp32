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

    uint8_t length_queue = 3;
    xQueueHandle sensor_queue; /**< Queue for data from sensors */
    xQueueHandle controller_queue; /**< Queue for data from controller */
/** @} */
public:
    

    ~assembly();

    #ifdef DS18B20_SETTINGS_H

    assembly::assembly(ds18b20 *ds18b20_obj, controller *controller_obj, Fan_3pin *Fan_3pin_obj, xQueueHandle sensor_queue, xQueueHandle controller_queue);

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
     * @param sensor_queue Queue for data from sensors
     * @param controller_queue Queue for data from controlle
     */
    assembly(bme280 *bme280_obj,PID_controller *PID_controller_obj,Fan_3pin *Fan_3pin_obj,xQueueHandle sensor_queue,xQueueHandle controller_queue);

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


    void bme280_check();
#endif
};


