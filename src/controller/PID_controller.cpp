#include "PID_controller.h"
#include <cmath>

void PID_controller :: set_coefficientPID(float newArr[3])
    {
        #ifdef DEBUG
        Serial.println("set_coefficientPID");
        #endif 
        for(int i = 0 ;i <3;i++)
        {
            coefficientPID[i] = newArr[i];
            
            #ifdef DEBUG
            Serial.printf("%d : %d",i,coefficientPID[i]);
            #endif
        }
    }

uint32_t PID_controller :: calculatePID()
{
    if(get_input_point() >1000 || get_input_point()<-20)
    {
        Serial.println("WRONG DATA SEND TO CONTROLLER CHECK IT");
        return -999;
    }
    float err = (float)get_set_point() - get_input_point();
    
    if (fabs(err) < 0.5)
    {
        return 0;
    }
    
    integral = constrain((float)(integral+(float)err*dtime*coefficientPID[1]),0,get_maxPWM());
    float D =(err-prevErr)/dtime;
    prevErr = err; 
    float outputPID =constrain((err*coefficientPID[0]+integral+D*coefficientPID[2]),0,get_maxPWM());

    #ifdef DEBUG
    const float data_arr[] ={err,integral,D,prevErr,outputPID};
    size_t num_data = sizeof(data_arr) / sizeof(data_arr[0]);
    const char* data_arr_name[] = {"err","integral","D","prevErr","outputPID"};
    debug_print("calculatePID",data_arr,num_data,data_arr_name);
    #endif
    output_value = outputPID;
    return (uint32_t)outputPID;
}

PID_controller::PID_controller(uint32_t set_point,uint32_t resolution,float* coefficientPID,float dtime):controller(set_point,resolution)
{
    set_coefficientPID(coefficientPID);
    this->dtime = dtime;

    #ifdef DEBUG
    Serial.println("PID_contorller construct");
    for(int i =0 ;i<3;i++)
    {
        Serial.printf("%d : %d \n",i,coefficientPID[i]);
    }
    Serial.printf("dtime : %d",dtime);
    Serial.println("__________________________");
    #endif
}

PID_controller ::PID_controller()
{

}

PID_controller::~PID_controller()
{
    
}