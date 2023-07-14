#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H
#include "controller.h"

class PID_controller : public controller
{
/**
 * @brief Class members
 * @{
 */
private:
    float coefficientPID[3];/**< PID coefficients of the controller [kP, kI, kD]*/
    float dtime;/**< change in time interval in seconds*/
    float integral;/**< integral of the integral part of the controller*/ 
    float prevErr;/**< predicted error ,differential part of the controller*/
/**@}*/
public:
    /**
    * @brief Construct a new PID controller object.
    *
    * @param set_point The desired value that the controller aims to achieve and maintain.
    * @param number_parametrs The number of parameters from sensors.
    * @param resolution LEDC channel duty resolution.
    * @param coefficientPID The PID coefficients of the controller. The array size should be [3] = {kP, kI, kD}.
    * @param dtime The change in time interval in seconds.
    *
    * @note Additionally, this constructor creates an array to store the PID coefficients.
    */
    PID_controller(uint8_t set_point,uint32_t number_parametrs,uint8_t resolution,float* coefficientPID,float dtime);

    /**
     * @brief Destroy the pid controller object
     * 
     */
    ~PID_controller();

    /**
    * @brief Set the PID coefficients.
    *
    * @param newArr The coefficients array of size [3] = {kP, kI, kD}.
    */
    void set_coefficientPID(float newArr[3]);

    /**
    * @brief Perform the main calculation of the PID controller.
    *
    * @return The calculated output value.
    */
    uint32_t calculatePID();
};
#endif