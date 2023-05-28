#ifndef FAN_H
#define FAN_H

#include <Arduino.h>
#include <driver/ledc.h>

class Fan
{
/**
 * @brief Class members
 * @{
*/
private:
    gpio_num_t fan_pin;/**< pin control fan*/
    bool state; /**< true-on fan , false-off fan*/
    ledc_timer_bit_t resolution; /**< [in] LEDC channel duty resolution*/
    uint32_t freq;/**< LEDC timer frequency (Hz)*/
    uint32_t speedPWM; /**< [out]  speed in PWM value*/
    ledc_timer_t timer_num; /**< [in]  The timer source of channel*/
    ledc_channel_t channel_num;/**< [in]  LEDC channel*/
/** @} */
public:
/**
 * @brief Construct a new Fan object
 * 
 * @param fan_pin  pin control fan
 * @param resolution LEDC channel duty resolution
 * @param freq LEDC timer frequency (Hz)
 * @param timer_num The timer source of channel
 * @param channel_num LEDC channel
 * 
 * @note Additionally, it calls the setup_timer() and setup_PWM_channel() methods to configure timer and PWM channel
 */
    Fan(gpio_num_t fan_pin, ledc_timer_bit_t resolution, uint32_t freq, ledc_timer_t timer_num, ledc_channel_t channel_num);

    /**
     * @brief Destroy the Fan object
     * 
     */
    ~Fan();

    /**
    * @brief Set the state of the fan.
    *
    * @param new_state The new state of the fan (true for on, false for off).
    */
    void set_state(bool new_state);

    /**
    * @brief Set up the LEDC timer for PWM channel configuration.
    *
    * This method initializes the LEDC timer with the specified configuration
    * parameters for PWM channel operation. It sets up the timer's frequency,
    * resolution, and other relevant settings.
    *
    * @note Make sure to call this method before using the PWM channel.
    */
    void setup_timer();

    /**
    * @brief Set up the PWM channel for controlling the fan speed.
    *
    * This method initializes the necessary parameters and configurations
    * to enable PWM control for the fan. It sets up the appropriate timer,
    * channel, frequency, and resolution for the LEDC module.
    *
    * @note Make sure to call this method before attempting to control the fan speed.
    */
    void setup_PWM_channel();

    /**
     * @brief Change speed fan
     * 
     */
    void change_speed();
};

#endif