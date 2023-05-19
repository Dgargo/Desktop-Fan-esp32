#include "controller.h"
#include "debug/debug.h"
#include "config.h"
void controller::set_setup_point(uint8_t new_value)
{
    set_point = new_value;
    #ifdef DEBUG
    Serial.println("set_setup_point");
    Serial.printf("set_point : %d",set_point);
    Serial.println("_______________________");
    #endif
}

void controller::set_input_paramers_arr(float* newArray)
{
    #ifdef DEBUG
    Serial.println("set_input_paramers_arr");
    Serial.println("set_input_paramers_arr before");
    for(int i=0;i<number_parametrs;i++)
    {
        Serial.printf("paramers %d : %d",i,input_parametrs_arr[i]);
    }
    Serial.println("___________________");
    #endif
    memcpy(input_parametrs_arr,newArray,number_parametrs*sizeof(float));
    
    #ifdef DEBUG
    Serial.println("set_input_paramers_arr");
    Serial.println("set_input_paramers_arr after");
    for(int i=0;i<number_parametrs;i++)
    {
        Serial.printf("paramers %d : %d",i,input_parametrs_arr[i]);
    }
    #endif
}

void controller::calculate_avg_input()
{
    float avg;
    for(int i =0 ;i<number_parametrs;i++)
    {
        avg +=input_parametrs_arr[i];
    }
    avg_input_point = avg/number_parametrs;
}

void controller::smooth_controller()
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
        return;
    }
    output_value = constrain(output_value,0,100);
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

controller::controller(uint8_t set_point,uint32_t number_parametrs ,uint8_t resolution)
{
    this->set_point = set_point ;
    this->number_parametrs = number_parametrs;
    this->resolution = resolution;
    minPWM = 0 ;
    maxPWM = 2^resolution -1;
    input_parametrs_arr = new float[number_parametrs];

    #ifdef DEBUG
    const uint32_t data_arr[] = {set_point,number_parametrs,resolution,maxPWM};
    size_t num_data = sizeof(data_arr) / sizeof(data_arr[0]);
    const char* data_arr_name[] = {"set_point","number_parametrs","resolution","maxPWM"};
    debug_print("controller construct",data_arr,num_data,data_arr_name);
    #endif
}

controller::~controller()
{
    delete[] input_parametrs_arr;
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