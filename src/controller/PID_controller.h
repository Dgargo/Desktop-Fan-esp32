#include "controller.h"

class PID_controller : public controller
{
private:
    float coefficientPID[3];
    float dtime;
    float integral; 
    float prevErr;
public:
    PID_controller(uint8_t set_point,uint32_t number_parametrs,uint8_t resolution,float* coefficientPID,float dtime);
    ~PID_controller();
    void set_coefficientPID(float newArr[3]);
    uint32_t computePID();
};