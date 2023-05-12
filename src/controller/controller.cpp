#include "controller.h"

void controller::set_setup_point(uint8_t new_value)
{
    set_point = new_value;
}

void controller::set_input_paramers_arr(float* newArray)
{
    memcpy(input_parametrs_arr,newArray,number_parametrs*sizeof(float));
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
    return map(output_value,0,100,minPWM,maxPWM);
}

controller::controller(uint8_t set_point,uint32_t number_parametrs ,uint8_t resolution)
{
    this->set_point = set_point ;
    this->number_parametrs = number_parametrs;
    this->resolution = resolution;
    minPWM = 0 ;
    maxPWM = 2^resolution -1;
    input_parametrs_arr = new float[number_parametrs];
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