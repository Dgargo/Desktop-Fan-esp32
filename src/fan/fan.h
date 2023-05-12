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
    uint8_t fan_pin;/**< [in]  pin control fan*/
    bool state; /**< [in]  true-on fan , false-off fan*/
    ledc_timer_bit_t resolution; /**< [in] LEDC channel duty resolution*/
    uint32_t freq;/**< [in] LEDC timer frequency (Hz)*/
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
 */
    Fan(uint32_t fan_pin, ledc_timer_bit_t resolution, uint32_t freq, ledc_timer_t timer_num, ledc_channel_t channel_num);

    /**
     * @brief Destroy the Fan object
     * 
     */
    ~Fan();

    /**
     * @brief on/of fan
     * 
     * @param new_state true/false - on/of fan
     */
    void set_state(bool new_state);

    /**
     * @brief Configuration parameters of LEDC Timer timer for PWM channel
     * 
     */
    void setup_timer();
    /**
     * @brief Set the up PWM channel 
     * 
     */
    void setup_PWM_channel();

    /**
     * @brief Change speed fan
     * 
     */
    void change_speed();
};

#endif