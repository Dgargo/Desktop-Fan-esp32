#ifndef FAN_H
#define FAN_H

#include <Arduino.h>
#include <driver/ledc.h>

class Fan
{
private:
    uint8_t fan_pin;
    bool state;
    ledc_timer_bit_t resolution;
    uint32_t freq;
    uint32_t speedPWM;
    ledc_timer_t timer_num;
    ledc_channel_t channel_num;

public:
    Fan(uint32_t fan_pin, ledc_timer_bit_t resolution, uint32_t freq, ledc_timer_t timer_num, ledc_channel_t channel_num);
    ~Fan();

    void state_fan(bool state, uint8_t fan_pin);
    void setup_timer(ledc_timer_t timer_num, ledc_timer_bit_t resolution, uint32_t freq);
    void setup_PWM_channel(uint8_t fan_pin, ledc_timer_t timer_num, ledc_channel_t channel_num, ledc_timer_bit_t resolution);
    void change_speed(ledc_channel_t channel_num, uint32_t speedPWM);
};

#endif