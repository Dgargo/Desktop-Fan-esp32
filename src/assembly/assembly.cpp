#include "assembly.h"

#ifdef DS18B20_SETTINGS_HD

assembly::assembly(ds18b20 *ds18b20_obj, controller *controller_obj, Fan_3pin *Fan_3pin_obj)
    : ds18b20_obj(ds18b20_obj), controller_obj(controller_obj), Fan_3pin_obj(Fan_3pin_obj), fan_obj(nullptr), PID_controller_obj(nullptr) {


}

assembly::assembly(ds18b20 *ds18b20_obj, PID_controller *PID_controller_obj, Fan_3pin *Fan_3pin_obj)
    : ds18b20_obj(ds18b20_obj), PID_controller_obj(PID_controller_obj), Fan_3pin_obj(Fan_3pin_obj), fan_obj(nullptr),controller_obj(nullptr) {
    

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
    ds18b20_obj.send_data();
    }
    PID_controller_obj.set_input_paramers_arr(sensor_queue);
    PID_controller_obj.calculate_avg_input();
    uint32_t output_from_sensor =PID_controller_obj.convert_output_PWM_signal();
    Fan_3pin_obj.set_speed(output_from_sensor);
    Fan_3pin_obj.change_speed();
    Fan_3pin_obj.calculate_RPM(); 
}
#else
assembly::assembly(bme280 *bme280_obj, PID_controller *PID_controller_obj, Fan_3pin *Fan_3pin_obj)
    : bme280_obj(bme280_obj), PID_controller_obj(PID_controller_obj), Fan_3pin_obj(Fan_3pin_obj), fan_obj(nullptr), controller_obj(nullptr) {
}

assembly::assembly(bme280 *bme280_obj,controller *controller_obj,Fan_3pin *Fan_3pin_obj):bme280_obj(bme280_obj),controller_obj(controller_obj),Fan_3pin_obj(Fan_3pin_obj),fan_obj(nullptr),PID_controller_obj(nullptr){

}
void assembly :: bme280_assembly()
{
   for(int i = 0 ;i<length_array;i++)
        {
            bme280_obj->read_data();
            bme280_obj->convert_data();
            save_data_in_assembly(i);
        } 
}

void assembly ::controller_assembly()
{
    controller_obj->calculate_avg_input(array_data);
    output_PWM = controller_obj->smooth_controller();
}
void assembly ::PID_controller_assembly()
{
    PID_controller_obj->calculate_avg_input(array_data);
    output_PWM = PID_controller_obj->calculatePID();
}

void assembly::Fan3pin_assembly()
{
    Fan_3pin_obj->set_speed(output_PWM);
    Fan_3pin_obj->change_speed();
    Fan_3pin_obj->calculate_RPM();
}

void  assembly ::simple_smart_assembly()
{
    for(int i = 0 ;i<length_array;i++)
    {
        bme280_obj->read_data();
        bme280_obj->convert_data();
        save_data_in_assembly(i);
    }
    PID_controller_obj->calculate_avg_input(array_data);
    uint32_t output_from_sensor = PID_controller_obj->calculatePID();
    Fan_3pin_obj->set_speed(output_from_sensor);
    Fan_3pin_obj->change_speed();
    Fan_3pin_obj->calculate_RPM();
    }
        
void assembly ::assembly_check()
{
    Serial.println("class create successful");
}

void assembly ::save_data_in_assembly(uint32_t index)
{
    #ifdef DEBUG
    Serial.println("______________________________");
    Serial.println("save_data_in_assembly \ndata array before");
    for(int i=0;i<length_array;i++)
    {   
            
        Serial.printf("%f \t",array_data[i]);
    }
    Serial.println("");
    #endif
        
    array_data[index] = bme280_obj->send_data();
        
    #ifdef DEBUG
    Serial.println("______________________________");
    Serial.println("data array after");
    for(int i=0;i<length_array;i++)
    {   
            
        Serial.printf("%f \t",array_data[i]);
    }
    Serial.println("\n______________________________");
    #endif
    }
#endif

assembly::~assembly()
{

}

