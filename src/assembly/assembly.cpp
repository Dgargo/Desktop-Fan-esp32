#include "assembly.h"

#ifdef DS18B20_SETTINGS_HD

assembly::assembly(ds18b20 *ds18b20_obj, controller *controller_obj, Fan_3pin *Fan_3pin_obj, xQueueHandle sensor_queue, xQueueHandle controller_queue)
    : ds18b20_obj(ds18b20_obj), controller_obj(controller_obj), Fan_3pin_obj(Fan_3pin_obj), fan_obj(nullptr), PID_controller_obj(nullptr) {
    this->sensor_queue = sensor_queue;
    this->controller_queue = controller_queue;

}

assembly::assembly(ds18b20 *ds18b20_obj, PID_controller *PID_controller_obj, Fan_3pin *Fan_3pin_obj, xQueueHandle sensor_queue, xQueueHandle controller_queue)
    : ds18b20_obj(ds18b20_obj), PID_controller_obj(PID_controller_obj), Fan_3pin_obj(Fan_3pin_obj), fan_obj(nullptr),controller_obj(nullptr) {
    this->sensor_queue = sensor_queue;
    this->controller_queue = controller_queue;

}

void assembly::simple_assembly()
{
    ds18b20_obj.read_data();
    ds18b20_obj.convert_data();
    ds18b20_obj.send_data(sensor_queue);
    controller_obj.set_input_paramers_arr(sensor_queue);
    controller_obj.calculate_avg_input();
    controller_obj.smooth_controller();
    uint32_t output_from_sensor= controller_obj.convert_output_PWM_signal();
    Fan_3pin_obj.set_speed(output_from_sensor);
    Fan_3pin_obj.change_speed();
    
    
}


void assembly::advanced_assembly()
{
    for(int i = 0 ;i<length_queue;i++)
    {
    ds18b20_obj.read_data();
    ds18b20_obj.convert_data();
    ds18b20_obj.send_data(sensor_queue);
    }
    PID_controller_obj.set_input_paramers_arr(sensor_queue);
    PID_controller_obj.calculate_avg_input();
    uint32_t output_from_sensor =PID_controller_obj.convert_output_PWM_signal();
    Fan_3pin_obj.set_speed(output_from_sensor);
    Fan_3pin_obj.change_speed();
    Fan_3pin_obj.calculate_RPM(); 
}
#else
assembly::assembly(bme280 *bme280_obj, PID_controller *PID_controller_obj, Fan_3pin *Fan_3pin_obj, xQueueHandle sensor_queue, xQueueHandle controller_queue)
    : bme280_obj(bme280_obj), PID_controller_obj(PID_controller_obj), Fan_3pin_obj(Fan_3pin_obj), fan_obj(nullptr), controller_obj(nullptr) {
    this->sensor_queue = sensor_queue;
    this->controller_queue = controller_queue;

}

    void  assembly ::simple_smart_assembly()
    {
        for(int i = 0 ;i<length_queue;i++)
        {
            bme280_obj->read_data();
            bme280_obj->convert_data();
            bme280_obj->send_data(sensor_queue);
        }
        PID_controller_obj->set_input_paramers_arr(sensor_queue);
        PID_controller_obj->calculate_avg_input();
        uint32_t output_from_sensor =PID_controller_obj->convert_output_PWM_signal();
        Fan_3pin_obj->set_speed(output_from_sensor);
        Fan_3pin_obj->change_speed();
        Fan_3pin_obj->calculate_RPM();
    }
        
    void assembly ::bme280_check()
    {
        Serial.println("class create successful");
    }
#endif

assembly::~assembly()
{

}

