#include "PID_controller.h"
#include "config.h"
void PID_controller :: set_coefficientPID(float newArr[3])
    {
        #ifdef DEBUG
        Serial.println("set_coefficientPID");
        #endif 
        for(int i = 0 ;i < lenght_queue;i++)
        {
            coefficientPID[i] = newArr[i];
            
            #ifdef DEBUG
            Serial.printf("%d : %d",i,coefficientPID[i]);
            #endif
        }
    }

uint32_t PID_controller :: calculatePID()
{
    float err = get_set_point() - get_input_point();
    integral = constrain(integral+(float)err*dtime*coefficientPID[1],0,get_maxPWM());
    float D =(err-prevErr)/dtime;
    prevErr = err; 
    float outputPID =constrain(err*coefficientPID[0]+integral+D*coefficientPID[2],0,get_maxPWM());

    #ifdef DEBUG
    const float data_arr[] ={err,integral,D,prevErr,outputPID};
    size_t num_data = sizeof(data_arr) / sizeof(data_arr[0]);
    const char* data_arr_name[] = {"err","integral","D","prevErr","outputPID"};
    debug_print("calculatePID",data_arr,num_data,data_arr_name);
    #endif

    return outputPID;
}

PID_controller::PID_controller(uint8_t set_point,uint8_t resolution,float* coefficientPID,float dtime):controller(set_point,resolution)
{
    for(int i = 0 ;i<lenght_queue;i++)
    {
        this->coefficientPID[i] = coefficientPID[i];
    }
    this->dtime = dtime;

    #ifdef DEBUG
    Serial.println("PID_contorller construct");
    for(int i =0 ;i<lenght_queue;i++)
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