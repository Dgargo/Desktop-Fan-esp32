#include "PID_controller.h"

void PID_controller :: set_coefficientPID(float newArr[3])
    {
        for(int i = 0 ;i < 3;i++)
        {
            coefficientPID[i] = newArr[i];
        }
    }

uint32_t PID_controller :: computePID()
{
    float err = get_set_point() - get_input_point();
    integral = constrain(integral+(float)err*dtime*coefficientPID[1],0,get_maxPWM());
    float D =(err-prevErr)/dtime;
    prevErr = err; 
    return constrain(err*coefficientPID[0]+integral+D*coefficientPID[2],0,get_maxPWM());
}

PID_controller::PID_controller(uint8_t set_point,uint32_t number_parametrs,uint8_t resolution,float* coefficientPID,float dtime):controller(set_point,number_parametrs,resolution)
{
    for(int i = 0 ;i<3;i++)
    {
        this->coefficientPID[i] = coefficientPID[i];
    }
    this->dtime = dtime;
}

PID_controller::~PID_controller()
{
}