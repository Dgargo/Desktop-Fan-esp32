//#ifdef CONTROLLER_H
#define CONTROLLER_H

#include "Arduino.h"

class controller
{
private:
    uint8_t set_point;
    uint16_t number_parametrs;
    float* input_parametrs_arr;
    float avg_input_point;
    uint32_t output_value;
    uint8_t resolution;
    uint32_t minPWM;
    uint32_t maxPWM;

public:
    controller(uint8_t set_point,uint32_t number_parametrs,uint8_t resolution);
    ~controller();
    void set_setup_point(uint8_t new_value);
    void set_input_paramers_arr(float* newArray);
    void calculate_avg_input();
    void smooth_controller();
    uint32_t convert_output_PWM_signal();
    float get_input_point()const;
    uint8_t get_set_point()const;
    uint32_t get_maxPWM()const;
};




//#endif