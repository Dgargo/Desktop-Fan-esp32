#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Arduino.h"

class controller
{
/**
 * @brief Class members
 * @{
 */
protected:
    uint32_t set_point;/**< setting the value that the controller must support .0-100%*/
    float input_parametrs_arr[3];/**< Array of input parameters from the sensor*/
    float avg_input_point;/**< average value of the input parameters */
    uint32_t output_value;/**< output value */
    uint32_t resolution;/**< LEDC channel duty resolution*/
    uint32_t minPWM;/**< the minimum value of the PWM signal*/
    uint32_t maxPWM;/**< the maximum value of the PWM signal*/
    const uint32_t lenght_queue = 3;
/**@}*/
public:

    controller();
    /**
    * @brief Construct a new controller object
    * 
    * @param set_point The desired set point value that the controller must support
    * @param resolution The resolution of the LEDC channel duty cycle
    * 
    * @note Additionally, this constructor calculates the maximum PWM value and creates a dynamic array for the sensor parameters.
    */
    controller(uint32_t set_point,uint32_t resolution);

    /**
    * @brief Destroy the controller object
    * 
    * @note Deletes the dynamic array used by the controller.
    */
    ~controller();

    /**
    * @brief Set the setup point for the controller.
    * 
    * @param new_value The new value for the setup point.
    *
    * The setup point represents the desired value that the controller aims to achieve and maintain.
    */
    void set_setup_point(uint8_t new_value);

    /** @brief Set the input parameters array.
    *
    * @param xData_queue  The handle of the queue to which the sensor data will be resieve. It should be initialized before calling this function.
    *
    * @note This method allows setting a new array of input parameters for the controller.
    */
    void set_input_paramers_arr(xQueueHandle xData_queue);

    /**
    * @brief Calculate the average value of the input parameters.
    *
    * @note This method calculates the average value of the input parameters and stores it internally.
    */
    void calculate_avg_input();

    /**
    * @brief Perform smooth control algorithm.
    *
    * This method applies a smooth control algorithm to adjust the controller's output gradually,
    * aiming for a more gradual and stable response.
    */
    void smooth_controller();

    /**
    * @brief Convert the controller's output value to a PWM signal.
    *
    * @return The converted output value as a PWM signal.
    */
    uint32_t convert_output_PWM_signal();

    /**
    * @brief Get the input point value.
    *
    * @return The value of the input point.
    */
    float get_input_point()const;

    /**
    * @brief Get the set point value.
    *
    * @return The value of the set point.
    */
    uint8_t get_set_point()const;

    /**
    * @brief Get the maximum PWM value.
    *
    * @return The maximum PWM value.
    */
    uint32_t get_maxPWM()const;
};

#endif