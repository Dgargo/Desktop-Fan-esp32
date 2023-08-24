#include "controller.h"
#include "debug/debug.h"

#include <cmath>

void controller::set_setup_point(uint8_t new_value)
{
    set_point = new_value;
    #ifdef DEBUG
    Serial.println("set_setup_point");
    Serial.printf("set_point : %d",set_point);
    Serial.println("_______________________");
    #endif
}
void controller::calculate_avg_input(float array_data[LENGTH_ARRAY_DATA])
{
    #ifdef DEBUG
    Serial.printf("\n avg_input_point before : %f\n",avg_input_point);
    #endif
    if(array_data[0] >1000 || array_data[0]<-20)
    {
        Serial.println("WRONG DATA SEND TO CONTROLLER CHECK IT");
        return;
    }
    avg_input_point = 0;
    for(int i =0 ;i<lenght_array;i++)
    {
        avg_input_point +=array_data[i];
    }
    avg_input_point = avg_input_point/lenght_array;

    #ifdef DEBUG
    Serial.printf("\n avg_input_point after : %f\n",avg_input_point);
    #endif
}

uint32_t controller::smooth_controller()
{
    if(set_point > avg_input_point)
    {
        output_value +=1;
    }
    else if(set_point <avg_input_point)
    {
        output_value -=1;
    }
    else
    {
        return -1;
    }
    output_value = constrain(output_value,0,100);
    return convert_output_PWM_signal();
}

uint32_t controller::convert_output_PWM_signal()
{
    uint32_t output_valuePWM =map(output_value,0,100,minPWM,maxPWM);

    #ifdef DEBUG
    const uint32_t data_arr[] = {output_value,output_valuePWM};
    size_t num_data = sizeof(data_arr) / sizeof(data_arr[0]);
    const char* data_arr_name[] = {"output_value","output_valuePWM"};
    debug_print("convert_output_PWM_signal",data_arr,num_data,data_arr_name);
    #endif

    return output_value;
}

controller::controller(uint32_t set_point,uint32_t resolution)
{
    this->set_point = set_point ;
    this->resolution = resolution;
    minPWM = 0 ;
    maxPWM = static_cast<uint32_t>(pow(2,resolution)) - 1;

    #ifdef DEBUG
    const uint32_t data_arr[] = {set_point,resolution,maxPWM};
    size_t num_data = sizeof(data_arr) / sizeof(data_arr[0]);
    const char* data_arr_name[] = {"set_point","resolution","maxPWM"};
    debug_print("controller construct",data_arr,num_data,data_arr_name);
    #endif
}

controller:: controller()
{

}
controller::~controller()
{

}

float controller::get_input_point()const
{
  return avg_input_point;
}

uint8_t controller::get_set_point()const
{
  return set_point;
}

uint32_t controller::get_maxPWM()const
{
    return maxPWM;
}

